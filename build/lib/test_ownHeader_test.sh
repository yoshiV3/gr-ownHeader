#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/yoshi/gr-ownHeader/lib
export PATH=/home/yoshi/gr-ownHeader/build/lib:$PATH
export LD_LIBRARY_PATH=/home/yoshi/gr-ownHeader/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$PYTHONPATH
test-ownHeader 
