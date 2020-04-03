/* -*- c++ -*- */

#define OWNHEADER_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "ownHeader_swig_doc.i"

%{
#include "ownHeader/append_header_bb.h"
#include "ownHeader/parse_header_b.h"
#include "ownHeader/generate_header_bb.h"
%}


%include "ownHeader/append_header_bb.h"
GR_SWIG_BLOCK_MAGIC2(ownHeader, append_header_bb);
%include "ownHeader/parse_header_b.h"
GR_SWIG_BLOCK_MAGIC2(ownHeader, parse_header_b);
%include "ownHeader/generate_header_bb.h"
GR_SWIG_BLOCK_MAGIC2(ownHeader, generate_header_bb);
