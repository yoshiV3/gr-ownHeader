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

#ifndef INCLUDED_OWNHEADER_SEND_TO_MULTIPLEXER_B_IMPL_H
#define INCLUDED_OWNHEADER_SEND_TO_MULTIPLEXER_B_IMPL_H

#include <ownHeader/send_to_multiplexer_b.h>
#include <pmt/pmt.h>
namespace gr {
  namespace ownHeader {

    class send_to_multiplexer_b_impl : public send_to_multiplexer_b
    {
     private:
      pmt::pmt_t d_msg; 
      pmt::pmt_t d_port_id;
      std::string d_len_tag; 

     public:
      send_to_multiplexer_b_impl(const std::string & len_tag_key);
      ~send_to_multiplexer_b_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace ownHeader
} // namespace gr

#endif /* INCLUDED_OWNHEADER_SEND_TO_MULTIPLEXER_B_IMPL_H */

