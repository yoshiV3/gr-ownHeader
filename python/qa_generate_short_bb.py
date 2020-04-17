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

class qa_generate_short_bb (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        len_tag_key      = "packet_len"
        receiver_key     = 'recv_id'
        pay_len_key      = "pay_len"
        debug_key        ="test"
        tag_debug        = gr.tag_t()
        tag_debug.key    = pmt.intern(debug_key)
        tag_debug.value  = pmt.from_long(400)
        tag_debug.offset = 2
        tag1             = gr.tag_t() 
        tag1.key         = pmt.intern(len_tag_key)
        tag1.value       = pmt.from_long(2)
        tag1.offset      = 0
        tag2             = gr.tag_t() 
        tag2.key         = pmt.intern(len_tag_key)
        tag2.value       = pmt.from_long(2)
        tag2.offset      = 2  
        tag1r            = gr.tag_t()
        tag1r.key        = pmt.intern(receiver_key)
        tag1r.value      = pmt.from_long(3)
        tag1r.offset     = 0
        tag2r            = gr.tag_t()
        tag2r.key        = pmt.intern(receiver_key)
        tag2r.value      = pmt.from_long(3)
        tag2r.offset     = 2 
        tag1l            = gr.tag_t()
        tag1l.key        = pmt.intern(pay_len_key)
        tag1l.value      = pmt.from_long(2)
        tag1l.offset     = 0
        tag2l            = gr.tag_t()
        tag2l.key        = pmt.intern(pay_len_key)
        tag2l.value      = pmt.from_long(2)
        tag2l.offset     = 2 
        packet1          = [10,10]
        packet2          = [10,20] 
        src_data         = packet1 + packet2
        src_tags         = tuple([tag_debug, tag1, tag2, tag1l, tag1r, tag2l, tag2r])
        #blocks
        source = blocks.vector_source_b(src_data,repeat = False, tags = src_tags)
        dest   = blocks.tsb_vector_sink_b(tsb_key="packet_len")
        gen    = ownHeader.generate_short_bb(len_tag_key, pay_len_key, receiver_key) 
        #connections
        self.tb.connect(source, gen, dest)
        self.tb.run()
        #retrieve fdata
        dest_data = dest.data()
        dest_tags = dest.tags() 
        # check data
        self.assertEqual(len(dest_data),2)
        self.assertEqual(dest_data[0], (35,))
        self.assertEqual(dest_data[1], (35,))
        self.assertEqual(len(dest_tags), 0) 



if __name__ == '__main__':
    gr_unittest.run(qa_generate_short_bb, "qa_generate_short_bb.xml")
