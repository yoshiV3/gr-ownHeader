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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "parse_header_b_impl.h"

namespace gr {
  namespace ownHeader {

    parse_header_b::sptr
    parse_header_b::make(const std::string & len_tag_key)
    {
      return gnuradio::get_initial_sptr
        (new parse_header_b_impl(len_tag_key));
    }

    /*
     * The private constructor
     */
    parse_header_b_impl::parse_header_b_impl()
      : gr::tagged_stream_block("parse_header_b",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(char)))
    {}

    /*
     * Our virtual destructor.
     */
    parse_header_b_impl::~parse_header_b_impl()
    {
    }

    int
    parse_header_b_impl::calculate_output_stream_length ( const gr_vector_int &ninput_items)
    {
		return 0; 
    }

    int
    parse_header_b_impl::work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const unsigned char *in = (const unsigned char *) input_items[0];


      // Do <+signal processing+>
      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace ownHeader */
} /* namespace gr */

