/* -*- c++ -*- */
/* 
 * Copyright 2020 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_OWNHEADER_GENERATE_SHORT_BB_IMPL_H
#define INCLUDED_OWNHEADER_GENERATE_SHORT_BB_IMPL_H

#include <ownHeader/generate_short_bb.h>

namespace gr {
  namespace ownHeader {

    class generate_short_bb_impl : public generate_short_bb
    {
     private:
	     std::string d_payload_tag_len;
	     std::string d_len_tag_key; 
	     std::string d_receiver_key;

     protected:
      int calculate_output_stream_length(const gr_vector_int &ninput_items);

     public:
      generate_short_bb_impl(const std::string & tag_len_key,
		             const std::string & payload_len,
		             const std::string & tag_receiver_key);
      ~generate_short_bb_impl();

      // Where all the action really happens
      int work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
    };

  } // namespace ownHeader
} // namespace gr

#endif /* INCLUDED_OWNHEADER_GENERATE_SHORT_BB_IMPL_H */

