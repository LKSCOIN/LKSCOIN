Lksc Core 3.3.0.0
===========================

https://www.lkschain.io

What is Lksc?
-------------

Lksc is an digital currency that enables instant payments to anyone, 
anywhere in the world. Lksc uses peer-to-peer technology
to operate with no central authority: managing transactions and issuing money
are carried out collectively by the network. Lksc Core is the name of the open
source software which enables the use of this currency.

For more information, as well as an immediately useable, binary version of
the Lksc Core software, see https://www.lkschain.io/download.html.

License
-------

Lksc Core is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

Development Process
-------------------

The `master` branch is meant to be stable. Development is normally done in separate branches.
[Tags](https://github.com/LKSCOIN/LKSCOIN/tags) are created to indicate new official,
stable release versions of Lksc Core.


Notable changes
===============

Recovery
--------
This new release has brought a major improvement reducing the load on the 
LLMQ resulting from the signature share system.
At first, all shares are sent to a randomly chosen node which recovers the signatures and 
propagates them, allowing the members to only check and propagate recovered signatures.
After having sent the share to the node, the member has to wait for a timeout before connecting 
with another random member.
This process is repeated again and again so as to create and propagate a recovered signature.

In order to minimize the time required to generate a signature when the recovery node is 
unavailable and the resulting traffic on the network, the timeout has been set to start at two 
seconds and then increase up to 10 seconds for each node (i.e. 2,4,8,10,10).

The new `SPORK_21_QUORUM_ALL_CONNECTED`, which allows the activation of the system, has two 
different hardcoded values: 0 activates Concentrated Recovery for each LLMQ while 1 excludes 
400_60 and 400_85 quorums.

Masternode Connections and Version Checks
-----------------------------------------
The number of masternode connections has increased because all the members of a LLMQ have to 
connect to the other members of the same LLMQ. This leads to an improvement of the 
"Concentrated Recovery", but also to an increased number of masternodes connections: this is 
the reason why the hardware and network requirements will be higher.

At first, these modifications will only target the smaller LLMQs members while later they could 
be applied also to larger quorums of approximately 400 members.
The probing consists in a masternode verifying that the other port is open and this is because 
not all the LLMQ members need to be connected to each other. Probing process phases are the 
following: the masternode establishes a short lived connection, waits for the `MNAUTH` to be 
effective and then disconnects.

This process allows the LLMQ members to know who they can connect with and, eventually, 
to mark as "bad" the others.
In the new system a minimum protocol version is required: a member using a low protocol 
version can be marked as "bad".
A member who gets 80% of "bad" marks will be excluded from the final stages of the DKG and will 
be PoSe punished or banned.

Performance
-----------
The most relevant improvement made in this latest version is the introduction of the epoll, 
which eliminates most of the CPU overhead due to a not optimal use of select. 
As a matter of facts, when there are a lot of connections at the same time, the select command 
can cause an increase of up to 50/80% of the CPU time  in the network thread.
Besides this, some improvements also involve the p2p message handling code, in such a way 
that  LLMQ connections are more agile.
Since all the modifications are exclusive to linux servers, we suggest to migrate to this
system if you use Windows, which could not be able to manage the network load.

Wallet changes
--------------
The wallets no longer need to be in the `--walletdir` directory, indeed the `--wallet=<path>` option 
now accepts full paths.
The backup of the wallets is easier because users can directly archive the chosen wallet path, 
without needing to search for transaction log file in the parent directory. Indeed, if the path of 
the `--wallet=<path>` does not exist, the system will create a wallet directory in a specific 
location witch contains a wallet.dat data file, a db.log file, and database/log.?????????? files, 
rather than creating a data file at the path and storing log files in the parent directory.
Nevertheless, wallet paths referring to existing files will still be valid.
The management of the default wallet has changed and now two options are available. 
If the Lksc Core does not include any `--wallet=<path>` option, then the default wallet path name 
will be an empty string and not "wallet.dat".
On the contrary, if Lksc Core includes a `--wallet=<path>` option, then the wallet name will simply 
be a <path> string.

User experience, wallet consistency and GUI flexibility have been improved thanks to the changes 
made to dialogs, tabs, icons, colors and to the interface. When a user opens the system for 
the first time, an "Appearance setup" dialog will pop up. Besides this there is also an Appearance 
tab where the user can choose a theme and set fonts and tags.

Advanced users and developers can now specify a path to custom CSS file, using the `--custom-css-dir`. 
Moreover, the newly added `--debug-ui` will make the Lksc Core to reload the custom CSS files 
when they are updated, allowing the users to see and debug all the changes to CSS files in the 
running GUI.

RPC changes and Command-line options
------------------------------------
In this new version the members can find some changes in the RPC interface:
- `getpeerinfo` has new field masternode to indicate whether connection was due to masternode 
connection attempt 
- `listunspent` has new filter option coinType to be able to filter different 
types of coins (all, mixed etc.) 
- `protx diff` returns more detailed information about new quorums
- `quorum dkgstatus` shows quorumConnections for each LLMQ with detailed information about 
each participating masternode 
- `quorum sign` has an optional quorumHash argument to pick the exact quorum 
- `socketevents` in `getnetworkinfo` rpc shows the socket events mode, either `epoll`, 
`poll` or `select`

Some new RPC commands have now been added:

- `quorum selectquorum` returns the quorum that would/should sign a request

In addition to this, the following RPC commands have been backported from Bitcoin 0.16:

- `help-console` for more info about using console in Qt
- `loadwallet` loads a wallet from a wallet file or directory
- `rescanblockchain` rescans the local blockchain for wallet related transactions
- `savemempool` dumps the mempool to disk

The changes made to the cmd-lines options are the following:

New cmd-line options:
- `--custom-css-dir`
- `--debug-ui`
- `--disablegovernance`
- `--font-family`
- `--font-scale`
- `--font-weight-bold`
- `--font-weight-normal`
- `--llmqdevnetparams`
- `--llmqtestparams`
- `--socketevents`
 
new command-line options backported from Bitcoin Core 0.16:
- `--addrmantest`
- `--debuglogfile`
- `--deprecatedrpc`
- `--enablebip61`
- `--getinfo`
- `--stdinrpcpass`
