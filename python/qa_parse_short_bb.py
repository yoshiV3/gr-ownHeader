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
def make_tags(len_tag_key,debug_key, payload_key): 
    debug_tag         = gr.tag_t()
    debug_tag.key     = pmt.intern(debug_key)
    debug_tag.value   = pmt.from_long(400)
    debug_tag.offset  = 5
    remove_tag        = gr.tag_t()
    remove_tag.key    = pmt.intern(payload_key)
    remove_tag.value  = pmt.from_long(400)
    remove_tag.offset = 6               
    tags        = [debug_tag, remove_tag]
    tag1        = gr.tag_t()
    tag1.key    = pmt.intern(len_tag_key)
    tag1.value  = pmt.from_long(1)
    tag1.offset = 0
    tags.append(tag1)
    tag2        = gr.tag_t()
    tag2.key    = pmt.intern(len_tag_key)
    tag2.value  = pmt.from_long(1)
    tag2.offset = 1
    tags.append(tag2)
    tag3        = gr.tag_t()
    tag3.key    = pmt.intern(len_tag_key)
    tag3.value  = pmt.from_long(1) 
    tag3.offset = 2
    tags.append(tag3)
    tag4        = gr.tag_t()
    tag4.key    = pmt.intern(len_tag_key)
    tag4.value  = pmt.from_long(2)
    tag4.offset = 3
    tags.append(tag4)
    tag5        = gr.tag_t()
    tag5.key    = pmt.intern(len_tag_key)
    tag5.value  = pmt.from_long(1)
    tag5.offset = 5
    tags.append(tag5)
    tag6        = gr.tag_t()
    tag6.key    = pmt.intern(len_tag_key)
    tag6.value  = pmt.from_long(1)
    tag6.offset = 6
    tags.append(tag6)
    return tuple(tags)
class qa_parse_short_bb (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        len_tag_key   =  "header_len"
        debug_tag_key =  "test"
        payload_key   =  "packet_size"
        own_id        =   4
        maxS          =   3
        header_one    =   [20]
        header_two    =   [17]
        header_three  =   [132]
        header_four   =   [20,20]
        header_five   =   [20]
        header_six    =   [20]
        src_data = header_one + header_two  + header_three + header_four
        src_data = src_data   + header_five + header_six
        src_tags = make_tags(len_tag_key, debug_tag_key, payload_key)
        #blocks
        src       = blocks.vector_source_b(src_data, repeat = False, tags = src_tags)
        parser    = ownHeader.parse_short_bb(len_tag_key, payload_key, own_id, maxS)
        dest      = blocks.tsb_vector_sink_b(1, len_tag_key)
        #connection
        self.tb.connect(src, parser, dest)
        self.tb.run() 
        # retrieve data
        dest_data = dest.data()
        dest_tags = dest.tags() 
        #testing 
        #receiver data 
        self.assertEqual(len(dest_data),6)
        self.assertEqual(dest_data, ((1,),(0,),(0,),(0,),(1,),(1,)))
        #tags
        tags = [gr.tag_to_python(x) for x in dest_tags]
        self.assertEqual(len(tags),4)
        zero = []
        four = []
        five = []
        rest = []
        for tag in tags:
            if tag.offset  == 0:
                zero.append(tag)
            elif tag.offset == 4:
                four.append(tag)
            elif tag.offset == 5:
                five.append(tag)
            else:
                rest.appned(tag) 
        self.assertEqual(len(rest),0)
        self.assertEqual(len(zero),1)
        self.assertEqual(len(four),2)
        self.assertEqual(len(five),1)
        self.assertEqual(zero[0].value, 1)
        for tag in four:
            if tag.key == debug_tag_key:
                self.assertEqual(tag.value, 400)
            elif tag.key == payload_key:
                self.assertEqual(tag.value,1)
            else:
                self.assertEqual(False, True)
        self.assertEqual(five[0].value,1)
if __name__ == '__main__':
    gr_unittest.run(qa_parse_short_bb, "qa_parse_short_bb.xml")
