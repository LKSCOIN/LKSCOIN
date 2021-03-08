#!/bin/bash
# use testnet settings,  if you need mainnet,  use ~/.lkscore/lksd.pid file instead
lks_pid=$(<~/.lkscore/testnet3/lksd.pid)
sudo gdb -batch -ex "source debug.gdb" lksd ${lks_pid}
