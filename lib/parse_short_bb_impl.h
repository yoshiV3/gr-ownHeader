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

#ifndef INCLUDED_OWNHEADER_PARSE_SHORT_BB_IMPL_H
#define INCLUDED_OWNHEADER_PARSE_SHORT_BB_IMPL_H

#include <ownHeader/parse_short_bb.h>

namespace gr {
  namespace ownHeader {

    class parse_short_bb_impl : public parse_short_bb
    {
     private:
	     std::string    d_len_tag_key;
	     std::string    d_tag_len_payload;
	     size_t         d_header_length; 
	     unsigned char  d_own_id;
	     unsigned char  d_max_payload_len; 

     protected:
      int calculate_output_stream_length(const gr_vector_int &ninput_items);

     public:
      parse_short_bb_impl(const std::string   & len_tag_key,
		          const std::string   & tag_len_payload,
		          const unsigned char   own_id,
		          const unsigned char   max_payload_len);
      ~parse_short_bb_impl();

      // Where all the action really happens
      int work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
    };

  } // namespace ownHeader
} // namespace gr

#endif /* INCLUDED_OWNHEADER_PARSE_SHORT_BB_IMPL_H */

