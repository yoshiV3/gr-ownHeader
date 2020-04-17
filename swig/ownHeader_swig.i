/* -*- c++ -*- */

#define OWNHEADER_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "ownHeader_swig_doc.i"

%{
#include "ownHeader/append_header_bb.h"
#include "ownHeader/generate_header_bb.h"
#include "ownHeader/parse_header_bb.h"
#include "ownHeader/send_to_multiplexer_b.h"
#include "ownHeader/generate_short_bb.h"
#include "ownHeader/parse_short_bb.h"
%}


%include "ownHeader/append_header_bb.h"
GR_SWIG_BLOCK_MAGIC2(ownHeader, append_header_bb);

%include "ownHeader/generate_header_bb.h"
GR_SWIG_BLOCK_MAGIC2(ownHeader, generate_header_bb);
%include "ownHeader/parse_header_bb.h"
GR_SWIG_BLOCK_MAGIC2(ownHeader, parse_header_bb);

%include "ownHeader/send_to_multiplexer_b.h"
GR_SWIG_BLOCK_MAGIC2(ownHeader, send_to_multiplexer_b);
%include "ownHeader/generate_short_bb.h"
GR_SWIG_BLOCK_MAGIC2(ownHeader, generate_short_bb);
%include "ownHeader/parse_short_bb.h"
GR_SWIG_BLOCK_MAGIC2(ownHeader, parse_short_bb);
