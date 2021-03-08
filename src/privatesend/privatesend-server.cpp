// Copyright (c) 2014-2020 The Lksc Core developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "privatesend-server.h"

#include "masternode/activemasternode.h"
#include "consensus/validation.h"
#include "core_io.h"
#include "init.h"
#include "masternode/masternode-meta.h"
#include "masternode/masternode-sync.h"
#include "net_processing.h"
#include "netmessagemaker.h"
#include "script/interpreter.h"
#include "txmempool.h"
#include "util.h"
#include "utilmoneystr.h"
#include "validation.h"

#include "llmq/quorums_instantsend.h"

#include <univalue.h>

CPrivateSendServer privateSendServer;

void CPrivateSendServer::ProcessMessage(CNode* pfrom, const std::string& strCommand, CDataStream& vRecv, CConnman& connman)
{
    return; 
}

void CPrivateSendServer::SetNull()
{
    // MN side
    vecSessionCollaterals.clear();
    nSessionMaxParticipants = 0;

    CPrivateSendBaseSession::SetNull();
    CPrivateSendBaseManager::SetNull();
}

//
// Check the mixing progress and send client updates if a Masternode
//
void CPrivateSendServer::CheckPool(CConnman& connman)
{
    return; 
}

void CPrivateSendServer::CreateFinalTransaction(CConnman& connman)
{
    return; 
}

void CPrivateSendServer::CommitFinalTransaction(CConnman& connman)
{
    return; 
}

//
// Charge clients a fee if they're abusive
//
// Why bother? PrivateSend uses collateral to ensure abuse to the process is kept to a minimum.
// The submission and signing stages are completely separate. In the cases where
// a client submits a transaction then refused to sign, there must be a cost. Otherwise they
// would be able to do this over and over again and bring the mixing to a halt.
//
// How does this work? Messages to Masternodes come in via NetMsgType::DSVIN, these require a valid collateral
// transaction for the client to be able to enter the pool. This transaction is kept by the Masternode
// until the transaction is either complete or fails.
//
void CPrivateSendServer::ChargeFees(CConnman& connman)
{
    return; 
}

/*
    Charge the collateral randomly.
    Mixing is completely free, to pay miners we randomly pay the collateral of users.

    Collateral Fee Charges:

    Being that mixing has "no fees" we need to have some kind of cost associated
    with using it to stop abuse. Otherwise it could serve as an attack vector and
    allow endless transaction that would bloat Lksc and make it unusable. To
    stop these kinds of attacks 1 in 10 successful transactions are charged. This
    adds up to a cost of 0.001DRK per transaction on average.
*/
void CPrivateSendServer::ChargeRandomFees(CConnman& connman)
{
    return; 
}

void CPrivateSendServer::ConsumeCollateral(CConnman& connman, const CTransactionRef& txref)
{
    LOCK(cs_main);
    CValidationState validationState;
    if (!AcceptToMemoryPool(mempool, validationState, txref, false, nullptr)) {
        LogPrint(BCLog::PRIVATESEND, "%s -- AcceptToMemoryPool failed\n", __func__);
    } else {
        connman.RelayTransaction(*txref);
        LogPrint(BCLog::PRIVATESEND, "%s -- Collateral was consumed\n", __func__);
    }
}

//
// Check for various timeouts (queue objects, mixing, etc)
//
void CPrivateSendServer::CheckTimeout(CConnman& connman)
{
    return; 
}

/*
    Check to see if we're ready for submissions from clients
    After receiving multiple dsa messages, the queue will switch to "accepting entries"
    which is the active state right before merging the transaction
*/
void CPrivateSendServer::CheckForCompleteQueue(CConnman& connman)
{
    return; 
}

// Check to make sure a given input matches an input in the pool and its scriptSig is valid
bool CPrivateSendServer::IsInputScriptSigValid(const CTxIn& txin)
{
    CMutableTransaction txNew;
    txNew.vin.clear();
    txNew.vout.clear();

    int i = 0;
    int nTxInIndex = -1;
    CScript sigPubKey = CScript();

    for (const auto& entry : vecEntries) {
        for (const auto& txout : entry.vecTxOut) {
            txNew.vout.push_back(txout);
        }
        for (const auto& txdsin : entry.vecTxDSIn) {
            txNew.vin.push_back(txdsin);

            if (txdsin.prevout == txin.prevout) {
                nTxInIndex = i;
                sigPubKey = txdsin.prevPubKey;
            }
            i++;
        }
    }

    if (nTxInIndex >= 0) { //might have to do this one input at a time?
        txNew.vin[nTxInIndex].scriptSig = txin.scriptSig;
        LogPrint(BCLog::PRIVATESEND, "CPrivateSendServer::IsInputScriptSigValid -- verifying scriptSig %s\n", ScriptToAsmStr(txin.scriptSig).substr(0, 24));
        // TODO we're using amount=0 here but we should use the correct amount. This works because Lksc ignores the amount while signing/verifying (only used in Bitcoin/Segwit)
        if (!VerifyScript(txNew.vin[nTxInIndex].scriptSig, sigPubKey, SCRIPT_VERIFY_P2SH | SCRIPT_VERIFY_STRICTENC, MutableTransactionSignatureChecker(&txNew, nTxInIndex, 0))) {
            LogPrint(BCLog::PRIVATESEND, "CPrivateSendServer::IsInputScriptSigValid -- VerifyScript() failed on input %d\n", nTxInIndex);
            return false;
        }
    } else {
        LogPrint(BCLog::PRIVATESEND, "CPrivateSendServer::IsInputScriptSigValid -- Failed to find matching input in pool, %s\n", txin.ToString());
        return false;
    }

    LogPrint(BCLog::PRIVATESEND, "CPrivateSendServer::IsInputScriptSigValid -- Successfully validated input and scriptSig\n");
    return true;
}

//
// Add a client's transaction inputs/outputs to the pool
//
bool CPrivateSendServer::AddEntry(CConnman& connman, const CPrivateSendEntry& entry, PoolMessage& nMessageIDRet)
{
    if (!fMasternodeMode) return false;

    if (GetEntriesCount() >= nSessionMaxParticipants) {
        LogPrint(BCLog::PRIVATESEND, "CPrivateSendServer::%s -- ERROR: entries is full!\n", __func__);
        nMessageIDRet = ERR_ENTRIES_FULL;
        return false;
    }

    if (!CPrivateSend::IsCollateralValid(*entry.txCollateral)) {
        LogPrint(BCLog::PRIVATESEND, "CPrivateSendServer::%s -- ERROR: collateral not valid!\n", __func__);
        nMessageIDRet = ERR_INVALID_COLLATERAL;
        return false;
    }

    if (entry.vecTxDSIn.size() > PRIVATESEND_ENTRY_MAX_SIZE) {
        LogPrint(BCLog::PRIVATESEND, "CPrivateSendServer::%s -- ERROR: too many inputs! %d/%d\n", __func__, entry.vecTxDSIn.size(), PRIVATESEND_ENTRY_MAX_SIZE);
        nMessageIDRet = ERR_MAXIMUM;
        ConsumeCollateral(connman, entry.txCollateral);
        return false;
    }

    std::vector<CTxIn> vin;
    for (const auto& txin : entry.vecTxDSIn) {
        LogPrint(BCLog::PRIVATESEND, "CPrivateSendServer::%s -- txin=%s\n", __func__, txin.ToString());

        for (const auto& entry : vecEntries) {
            for (const auto& txdsin : entry.vecTxDSIn) {
                if (txdsin.prevout == txin.prevout) {
                    LogPrint(BCLog::PRIVATESEND, "CPrivateSendServer::%s -- ERROR: already have this txin in entries\n", __func__);
                    nMessageIDRet = ERR_ALREADY_HAVE;
                    // Two peers sent the same input? Can't really say who is the malicious one here,
                    // could be that someone is picking someone else's inputs randomly trying to force
                    // collateral consumption. Do not punish.
                    return false;
                }
            }
        }
        vin.emplace_back(txin);
    }

    bool fConsumeCollateral{false};
    if (!IsValidInOuts(vin, entry.vecTxOut, nMessageIDRet, &fConsumeCollateral)) {
        LogPrint(BCLog::PRIVATESEND, "CPrivateSendServer::%s -- ERROR! IsValidInOuts() failed: %s\n", __func__, CPrivateSend::GetMessageByID(nMessageIDRet));
        if (fConsumeCollateral) {
            ConsumeCollateral(connman, entry.txCollateral);
        }
        return false;
    }

    vecEntries.push_back(entry);

    LogPrint(BCLog::PRIVATESEND, "CPrivateSendServer::%s -- adding entry %d of %d required\n", __func__, GetEntriesCount(), nSessionMaxParticipants);
    nMessageIDRet = MSG_ENTRIES_ADDED;

    return true;
}

bool CPrivateSendServer::AddScriptSig(const CTxIn& txinNew)
{
    LogPrint(BCLog::PRIVATESEND, "CPrivateSendServer::AddScriptSig -- scriptSig=%s\n", ScriptToAsmStr(txinNew.scriptSig).substr(0, 24));

    for (const auto& entry : vecEntries) {
        for (const auto& txdsin : entry.vecTxDSIn) {
            if (txdsin.scriptSig == txinNew.scriptSig) {
                LogPrint(BCLog::PRIVATESEND, "CPrivateSendServer::AddScriptSig -- already exists\n");
                return false;
            }
        }
    }

    if (!IsInputScriptSigValid(txinNew)) {
        LogPrint(BCLog::PRIVATESEND, "CPrivateSendServer::AddScriptSig -- Invalid scriptSig\n");
        return false;
    }

    LogPrint(BCLog::PRIVATESEND, "CPrivateSendServer::AddScriptSig -- scriptSig=%s new\n", ScriptToAsmStr(txinNew.scriptSig).substr(0, 24));

    for (auto& txin : finalMutableTransaction.vin) {
        if (txin.prevout == txinNew.prevout && txin.nSequence == txinNew.nSequence) {
            txin.scriptSig = txinNew.scriptSig;
            LogPrint(BCLog::PRIVATESEND, "CPrivateSendServer::AddScriptSig -- adding to finalMutableTransaction, scriptSig=%s\n", ScriptToAsmStr(txinNew.scriptSig).substr(0, 24));
        }
    }
    for (int i = 0; i < GetEntriesCount(); i++) {
        if (vecEntries[i].AddScriptSig(txinNew)) {
            LogPrint(BCLog::PRIVATESEND, "CPrivateSendServer::AddScriptSig -- adding to entries, scriptSig=%s\n", ScriptToAsmStr(txinNew.scriptSig).substr(0, 24));
            return true;
        }
    }

    LogPrint(BCLog::PRIVATESEND, "CPrivateSendServer::AddScriptSig -- Couldn't set sig!\n");
    return false;
}

// Check to make sure everything is signed
bool CPrivateSendServer::IsSignaturesComplete()
{
    for (const auto& entry : vecEntries) {
        for (const auto& txdsin : entry.vecTxDSIn) {
            if (!txdsin.fHasSig) return false;
        }
    }

    return true;
}

bool CPrivateSendServer::IsAcceptableDSA(const CPrivateSendAccept& dsa, PoolMessage& nMessageIDRet)
{
    if (!fMasternodeMode) return false;

    // is denom even smth legit?
    std::vector<int> vecBits;
    if (!CPrivateSend::GetDenominationsBits(dsa.nDenom, vecBits)) {
        LogPrint(BCLog::PRIVATESEND, "CPrivateSendServer::%s -- denom not valid!\n", __func__);
        nMessageIDRet = ERR_DENOM;
        return false;
    }

    // check collateral
    if (!fUnitTest && !CPrivateSend::IsCollateralValid(dsa.txCollateral)) {
        LogPrint(BCLog::PRIVATESEND, "CPrivateSendServer::%s -- collateral not valid!\n", __func__);
        nMessageIDRet = ERR_INVALID_COLLATERAL;
        return false;
    }

    return true;
}

bool CPrivateSendServer::CreateNewSession(const CPrivateSendAccept& dsa, PoolMessage& nMessageIDRet, CConnman& connman)
{
    if (!fMasternodeMode || nSessionID != 0) return false;

    // new session can only be started in idle mode
    if (nState != POOL_STATE_IDLE) {
        nMessageIDRet = ERR_MODE;
        LogPrint(BCLog::PRIVATESEND, "CPrivateSendServer::CreateNewSession -- incompatible mode: nState=%d\n", nState);
        return false;
    }

    if (!IsAcceptableDSA(dsa, nMessageIDRet)) {
        return false;
    }

    // start new session
    nMessageIDRet = MSG_NOERR;
    nSessionID = GetRandInt(999999) + 1;
    nSessionDenom = dsa.nDenom;
    nSessionMaxParticipants = CPrivateSend::GetMinPoolParticipants() + GetRandInt(CPrivateSend::GetMaxPoolParticipants() - CPrivateSend::GetMinPoolParticipants() + 1);

    SetState(POOL_STATE_QUEUE);

    if (!fUnitTest) {
        //broadcast that I'm accepting entries, only if it's the first entry through
        CPrivateSendQueue dsq(nSessionDenom, activeMasternodeInfo.outpoint, GetAdjustedTime(), false);
        LogPrint(BCLog::PRIVATESEND, "CPrivateSendServer::CreateNewSession -- signing and relaying new queue: %s\n", dsq.ToString());
        dsq.Sign();
        dsq.Relay(connman);
        vecPrivateSendQueue.push_back(dsq);
    }

    vecSessionCollaterals.push_back(MakeTransactionRef(dsa.txCollateral));
    LogPrint(BCLog::PRIVATESEND, "CPrivateSendServer::CreateNewSession -- new session created, nSessionID: %d  nSessionDenom: %d (%s)  vecSessionCollaterals.size(): %d  nSessionMaxParticipants: %d\n",
        nSessionID, nSessionDenom, CPrivateSend::GetDenominationsToString(nSessionDenom), vecSessionCollaterals.size(), nSessionMaxParticipants);

    return true;
}

bool CPrivateSendServer::AddUserToExistingSession(const CPrivateSendAccept& dsa, PoolMessage& nMessageIDRet)
{
    if (!fMasternodeMode || nSessionID == 0 || IsSessionReady()) return false;

    if (!IsAcceptableDSA(dsa, nMessageIDRet)) {
        return false;
    }

    // we only add new users to an existing session when we are in queue mode
    if (nState != POOL_STATE_QUEUE) {
        nMessageIDRet = ERR_MODE;
        LogPrint(BCLog::PRIVATESEND, "CPrivateSendServer::AddUserToExistingSession -- incompatible mode: nState=%d\n", nState);
        return false;
    }

    if (dsa.nDenom != nSessionDenom) {
        LogPrint(BCLog::PRIVATESEND, "CPrivateSendServer::AddUserToExistingSession -- incompatible denom %d (%s) != nSessionDenom %d (%s)\n",
            dsa.nDenom, CPrivateSend::GetDenominationsToString(dsa.nDenom), nSessionDenom, CPrivateSend::GetDenominationsToString(nSessionDenom));
        nMessageIDRet = ERR_DENOM;
        return false;
    }

    // count new user as accepted to an existing session

    nMessageIDRet = MSG_NOERR;
    vecSessionCollaterals.push_back(MakeTransactionRef(dsa.txCollateral));

    LogPrint(BCLog::PRIVATESEND, "CPrivateSendServer::AddUserToExistingSession -- new user accepted, nSessionID: %d  nSessionDenom: %d (%s)  vecSessionCollaterals.size(): %d  nSessionMaxParticipants: %d\n",
        nSessionID, nSessionDenom, CPrivateSend::GetDenominationsToString(nSessionDenom), vecSessionCollaterals.size(), nSessionMaxParticipants);

    return true;
}

bool CPrivateSendServer::IsSessionReady()
{
    return nSessionMaxParticipants != 0 && (int)vecSessionCollaterals.size() >= nSessionMaxParticipants;
}

void CPrivateSendServer::RelayFinalTransaction(const CTransaction& txFinal, CConnman& connman)
{
    LogPrint(BCLog::PRIVATESEND, "CPrivateSendServer::%s -- nSessionID: %d  nSessionDenom: %d (%s)\n",
        __func__, nSessionID, nSessionDenom, CPrivateSend::GetDenominationsToString(nSessionDenom));

    // final mixing tx with empty signatures should be relayed to mixing participants only
    for (const auto& entry : vecEntries) {
        bool fOk = connman.ForNode(entry.addr, [&txFinal, &connman, this](CNode* pnode) {
            CNetMsgMaker msgMaker(pnode->GetSendVersion());
            connman.PushMessage(pnode, msgMaker.Make(NetMsgType::DSFINALTX, nSessionID, txFinal));
            return true;
        });
        if (!fOk) {
            // no such node? maybe this client disconnected or our own connection went down
            RelayStatus(STATUS_REJECTED, connman);
            break;
        }
    }
}

void CPrivateSendServer::PushStatus(CNode* pnode, PoolStatusUpdate nStatusUpdate, PoolMessage nMessageID, CConnman& connman)
{
    if (!pnode) return;
    CPrivateSendStatusUpdate psssup(nSessionID, nState, 0, nStatusUpdate, nMessageID);
    connman.PushMessage(pnode, CNetMsgMaker(pnode->GetSendVersion()).Make(NetMsgType::DSSTATUSUPDATE, psssup));
}

void CPrivateSendServer::RelayStatus(PoolStatusUpdate nStatusUpdate, CConnman& connman, PoolMessage nMessageID)
{
    unsigned int nDisconnected{};
    // status updates should be relayed to mixing participants only
    for (const auto& entry : vecEntries) {
        // make sure everyone is still connected
        bool fOk = connman.ForNode(entry.addr, [&nStatusUpdate, &nMessageID, &connman, this](CNode* pnode) {
            PushStatus(pnode, nStatusUpdate, nMessageID, connman);
            return true;
        });
        if (!fOk) {
            // no such node? maybe this client disconnected or our own connection went down
            ++nDisconnected;
        }
    }
    if (nDisconnected == 0) return; // all is clear

    // smth went wrong
    LogPrint(BCLog::PRIVATESEND, "CPrivateSendServer::%s -- can't continue, %llu client(s) disconnected, nSessionID: %d  nSessionDenom: %d (%s)\n",
        __func__, nDisconnected, nSessionID, nSessionDenom, CPrivateSend::GetDenominationsToString(nSessionDenom));

    // notify everyone else that this session should be terminated
    for (const auto& entry : vecEntries) {
        connman.ForNode(entry.addr, [&connman, this](CNode* pnode) {
            PushStatus(pnode, STATUS_REJECTED, MSG_NOERR, connman);
            return true;
        });
    }

    if (nDisconnected == vecEntries.size()) {
        // all clients disconnected, there is probably some issues with our own connection
        // do not charge any fees, just reset the pool
        SetNull();
    }
}

void CPrivateSendServer::RelayCompletedTransaction(PoolMessage nMessageID, CConnman& connman)
{
    LogPrint(BCLog::PRIVATESEND, "CPrivateSendServer::%s -- nSessionID: %d  nSessionDenom: %d (%s)\n",
        __func__, nSessionID, nSessionDenom, CPrivateSend::GetDenominationsToString(nSessionDenom));

    // final mixing tx with empty signatures should be relayed to mixing participants only
    for (const auto& entry : vecEntries) {
        bool fOk = connman.ForNode(entry.addr, [&nMessageID, &connman, this](CNode* pnode) {
            CNetMsgMaker msgMaker(pnode->GetSendVersion());
            connman.PushMessage(pnode, msgMaker.Make(NetMsgType::DSCOMPLETE, nSessionID, nMessageID));
            return true;
        });
        if (!fOk) {
            // no such node? maybe client disconnected or our own connection went down
            RelayStatus(STATUS_REJECTED, connman);
            break;
        }
    }
}

void CPrivateSendServer::SetState(PoolState nStateNew)
{
    if (!fMasternodeMode) return;

    if (nStateNew == POOL_STATE_ERROR || nStateNew == POOL_STATE_SUCCESS) {
        LogPrint(BCLog::PRIVATESEND, "CPrivateSendServer::SetState -- Can't set state to ERROR or SUCCESS as a Masternode. \n");
        return;
    }

    LogPrint(BCLog::PRIVATESEND, "CPrivateSendServer::SetState -- nState: %d, nStateNew: %d\n", nState, nStateNew);
    nTimeLastSuccessfulStep = GetTime();
    nState = nStateNew;
}

void CPrivateSendServer::DoMaintenance(CConnman& connman)
{
    if (fLiteMode) return;        // disable all Lksc specific functionality
    if (!fMasternodeMode) return; // only run on masternodes

    if (!masternodeSync.IsBlockchainSynced() || ShutdownRequested()) return;

    privateSendServer.CheckTimeout(connman);
    privateSendServer.CheckForCompleteQueue(connman);
}

void CPrivateSendServer::GetJsonInfo(UniValue& obj) const
{
    obj.clear();
    obj.setObject();
    obj.push_back(Pair("queue_size",    GetQueueSize()));
    CAmount amount{0};
    if (nSessionDenom) {
        ParseFixedPoint(CPrivateSend::GetDenominationsToString(nSessionDenom), 8, &amount);
    }
    obj.push_back(Pair("denomination",  ValueFromAmount(amount)));
    obj.push_back(Pair("state",         GetStateString()));
    obj.push_back(Pair("entries_count", GetEntriesCount()));
}
