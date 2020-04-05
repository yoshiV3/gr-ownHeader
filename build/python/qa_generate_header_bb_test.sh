#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/yoshi/gr-ownHeader/python
export PATH=/home/yoshi/gr-ownHeader/build/python:$PATH
export LD_LIBRARY_PATH=/home/yoshi/gr-ownHeader/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=/home/yoshi/gr-ownHeader/build/swig:$PYTHONPATH
/usr/bin/python2 /home/yoshi/gr-ownHeader/python/qa_generate_header_bb.py 
