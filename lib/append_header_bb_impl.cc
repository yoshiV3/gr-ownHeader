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
#include <string>
#include <vector>
#include "append_header_bb_impl.h"
#include "pmt/pmt.h"

namespace gr {
  namespace ownHeader {

    append_header_bb::sptr
    append_header_bb::make(const std::string& len_tag_key)
    {
      return gnuradio::get_initial_sptr
        (new append_header_bb_impl(len_tag_key));
    }

    /*
     * The private constructor
     */
    append_header_bb_impl::append_header_bb_impl(const std::string& len_tag_key)
      : tagged_stream_block("append_header_bb",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(char)),
	      len_tag_key)
    {
    	set_tag_propagation_policy(TPP_DONT);
    }

    /*
     * Our virtual destructor.
     */
    append_header_bb_impl::~append_header_bb_impl()
    {}

    void 
    append_header_bb_impl::create_header(unsigned char  result[6])
    {
	    std::vector<tag_t> tags ;
	    pmt::pmt_t keyTag = pmt::intern(std::string ("number_of_symbols"));
	    get_tags_in_window(
			    tags, 
			    0,
			    0,
			    12,
			    keyTag
	    );
	    result[0] = (unsigned char) pmt::to_uint64(tags[0].value); 
	    keyTag = pmt::intern(std::string ("sequence_number"));
	    get_tags_in_window(
			    tags,
			    0,
			    0,
			    12,
			    keyTag
	    );
	    result[1] = (unsigned char) pmt::to_uint64(tags[0].value); 
	    keyTag = pmt::intern(std::string ("sender_id"));
	    get_tags_in_window(
			    tags,
			    0,
			    0,
			    12,
			    keyTag
	    );
	    result[2] = (unsigned char) pmt::to_uint64(tags[0].value); 
	    keyTag = pmt::intern(std::string( "receiver_id"));
	    get_tags_in_window(
			    tags, 
			    0,
			    0,
			    12,
			    keyTag
	    );
	    result[3] = (unsigned char) pmt::to_uint64(tags[0].value); 
	    keyTag = pmt::intern(std::string ("padding"));
	    get_tags_in_window(
			    tags,
			    0,
			    0,
			    12,
			    keyTag
	    );
	    result[4] = (unsigned char) pmt::to_uint64(tags[0].value);             
	    keyTag = pmt::intern(std::string( "mode"));
	    get_tags_in_window(
			    tags, 
			    0,
			    0,
			    12,
			    keyTag
	    );
	    result[5] = (unsigned char) pmt::to_uint64(tags[0].value);    
    }
    int
    append_header_bb_impl::calculate_output_stream_length(const gr_vector_int& ninput_items)
    {
	    return ninput_items[0] +6;
    }

    int
    append_header_bb_impl::work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const unsigned char *in = (const unsigned char *) input_items[0];
      unsigned char *out = (unsigned char  *) output_items[0];

      size_t packet_length = ninput_items[0];
      unsigned char header[6];
      create_header(header); 
      memcpy((void *) out, &header, 6);
      memcpy((void *)(out+6), (const void*)in,packet_length);
      return packet_length + 6;
    }

  } /* namespace ownHeader */
} /* namespace gr */

