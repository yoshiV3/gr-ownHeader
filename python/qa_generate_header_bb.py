#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2020 <+YOU OR YOUR COMPANY+>.
# 
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

from gnuradio import gr, gr_unittest
from gnuradio import blocks
import ownHeader_swig as ownHeader
import pmt



def make_tags(offset):
    tags = []
    tag1        = gr.tag_t()
    tag1.key    = pmt.intern("number_of_symbols")
    tag1.value  = pmt.to_pmt(1)
    tag1.offset = offset
    tags.append(tag1) 
    tag2        = gr.tag_t()
    tag2.key    = pmt.intern("sequence_number")
    tag2.value  = pmt.to_pmt(1)
    tag2.offset = offset
    tags.append(tag2)
    tag3        = gr.tag_t()
    tag3.key    = pmt.intern("sender_id")
    tag3.value  = pmt.to_pmt(1)
    tag3.offset = offset
    tags.append(tag3)
    tag4        = gr.tag_t()
    tag4.key    = pmt.intern("receiver_id")
    tag4.value  = pmt.to_pmt(0)
    tag4.offset = offset
    tags.append(tag4)
    tag5        = gr.tag_t()
    tag5.key    = pmt.intern("padding")
    tag5.value  = pmt.to_pmt(0)
    tag5.offset = offset
    tags.append(tag5)
    tag6        = gr.tag_t()
    tag6.key    = pmt.intern("mode")
    tag6.value  = pmt.to_pmt(0)
    tag6.offset = offset
    tags.append(tag6)
    tag7        = gr.tag_t()
    tag7.key    = pmt.intern("packet_len")
    tag7.value  = pmt.to_pmt(12)
    tag7.offset = offset
    tags.append(tag7)
    return tuple(tags)




class qa_generate_header_bb (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        src_data = [193 for x in range(12)]
        src_tags = make_tags(0) 
        source = blocks.vector_source_b(src_data,repeat = False, tags = src_tags)        
        dest   = blocks.tsb_vector_sink_b(tsb_key="packet_len")
        header = ownHeader.generate_header_bb("packet_len")
        self.tb.connect(source,header,dest)
        self.tb.run ()

        result_data = dest.data()[0]

        self.assertEqual(len(result_data),6)
        self.assertEqual(result_data, tuple([1,1,1,0,0,0]))
        # check data

if __name__ == '__main__':
    gr_unittest.run(qa_generate_header_bb, "qa_generate_header_bb.xml")
