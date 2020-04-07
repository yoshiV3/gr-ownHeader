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



def make_tags():
    tag1        = gr.tag_t()
    tag1.key    = pmt.intern("foo")
    tag1.value  = pmt.from_long(6)
    tag1.offset = 0
    tag2        = gr.tag_t()
    tag2.key    = pmt.intern("boo")
    tag2.value  = pmt.from_long(6)
    tag2.offset = 0
    tag3        = gr.tag_t()
    tag3.key    = pmt.intern("foo")
    tag3.value  = pmt.from_long(6)
    tag3.offset = 1
    tag4        = gr.tag_t()
    tag4.key    = pmt.intern("packet_len")
    tag4.value    = pmt.from_long(1)
    tag4.offset = 0
    tags = [tag1,tag2,tag3, tag4]
    return tags 
    
class qa_send_to_multiplexer_b (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        len_tag_key       = "packet_len"
        len_frame_tag_key = "frame_length"
        sequence          = [1,0,1,0]
        src_tags          = make_tags()
        src               = blocks.vector_source_b(sequence, repeat = False, tags = src_tags)
        sender            = ownHeader.send_to_multiplexer_b(len_tag_key)
        dest              = blocks.message_debug()
        self.tb.connect(src, sender)
        self.tb.msg_connect(sender, "header", dest, "store")
        self.tb.start()
        self.tb.wait()
        number_of_messages = dest.num_messages() 
        self.assertEqual(number_of_messages,4)
        msg1 = pmt.to_python(dest.get_message(0)) 
        msg2 = pmt.to_python(dest.get_message(1))
        msg3 = pmt.to_python(dest.get_message(2))
        msg4 = pmt.to_python(dest.get_message(3))
        self.assertEqual(msg2, False)
        self.assertEqual(msg4, False)
        self.assertEqual(len(msg1), 2)

if __name__ == '__main__':
    gr_unittest.run(qa_send_to_multiplexer_b, "qa_send_to_multiplexer_b.xml")
