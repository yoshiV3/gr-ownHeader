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

#ifndef INCLUDED_OWNHEADER_PARSE_HEADER_BB_IMPL_H
#define INCLUDED_OWNHEADER_PARSE_HEADER_BB_IMPL_H

#include <ownHeader/parse_header_bb.h>

namespace gr {
  namespace ownHeader {

    class parse_header_bb_impl : public parse_header_bb
    {
     private:
      std::string d_frame_len_key;
      std::string d_len_tag_key; 
      unsigned char d_own_id;
      unsigned char d_max_symbols; 
      unsigned char d_max_padding; 
      size_t        d_header_length; 
      size_t        d_out_length;
      int           d_index_sym_cnt; 
      int           d_index_seq_num; 
      int           d_index_send_id; 
      int           d_index_recv_id;
      int           d_index_pad_cnt; 
      int           d_index_mode; 

     protected:
      int calculate_output_stream_length(const gr_vector_int &ninput_items);

     public:
      parse_header_bb_impl( const std::string & len_tag_key,
		            const std::string & frame_len_key,
		            unsigned char max_symbols, unsigned char own_id,
		             unsigned char max_padding );
      ~parse_header_bb_impl();

      // Where all the action really happens
      int work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
    };

  } // namespace ownHeader
} // namespace gr

#endif /* INCLUDED_OWNHEADER_PARSE_HEADER_BB_IMPL_H */

