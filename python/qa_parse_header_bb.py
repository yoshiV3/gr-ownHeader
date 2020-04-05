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

def make_tags(len_tag_key):
    tags        = []
    tag1        = gr.tag_t()
    tag1.key    = pmt.intern(len_tag_key)
    tag1.value  = pmt.from_long(6)
    tag1.offset = 0
    tag2        = gr.tag_t()
    tag2.key    = pmt.intern(len_tag_key)
    tag2.value  = pmt.from_long(6)
    tag2.offset = 6
    tag3        = gr.tag_t()
    tag3.key    = pmt.intern(len_tag_key)
    tag3.value  = pmt.from_long(6)
    tag3.offset = 12
    tag4        = gr.tag_t()
    tag4.key    = pmt.intern(len_tag_key)
    tag4.value  = pmt.from_long(6)
    tag4.offset = 18
    return tuple([tag1,tag2,tag3,tag4])
 
    

class qa_parse_header_bb (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        len_tag_key       ="packet_len"
        len_frame_tag_key = "frame_len"
        maxS              = 3
        ownID             = 2
        maxPad            = 1
        header_one        = [1,0,1,2,0,0]
        header_two        = [100,1,1,2,0,0] #too long
        header_three      = [1,2,1,3,0,0]  #wrong receiver 
        header_four       = [1,0,1,2,10,0] #too much padding 
        scr_data          = header_one + header_two + header_three + header_four
        src_tags          = make_tags()
        src               = blocks.vector_source_b(src_data, repeat == False, tags = src_tags)
        parser            = ownHeader.parse_header_bb(len_tag_key,frame_len,  maxS, ownID, maxPad)
        dest              = blocks.tsb_vector_sink_b(tag_len_key)
        self.tb.connect(src,parser,dest)
        self.tb.run ()
        dest_data = dest.data()
        dest_tags = dest.tags()

        self.assertEqual(len(dest_data),4)
        self.assertEqual(dest_data, tuple([1,0,0,0]))
        tags = [gr.tag_to_python(x) for x in dest_tags]
        self.assertEqual(len(tags),10)
        zero  = []
        one   = []
        two   = []
        three = []
        for tag in tags:
            if tag.offset ==0:
                zero.append(tag)
            elif tag.offset ==1:
                one.append(tag)
            elif tag.offset == 2:
                two.append(tag)
            else :
                three.append(tag)
       self.assertEqual(len(zero),7)
       self.assertEqual(len(one),1)
       self.assertEqual(len(two),1)
       self.assertEqual(len(three),1)

        # check data


if __name__ == '__main__':
    gr_unittest.run(qa_parse_header_bb, "qa_parse_header_bb.xml")
