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
#include <pmt/pmt.h>
#include "parse_short_bb_impl.h"

namespace gr {
  namespace ownHeader {
    parse_short_bb::sptr 
    parse_short_bb::make(const std::string   & len_tag_key, 
		         const std::string   & tag_len_payload, 
		         const unsigned char   own_id,
		         const unsigned char   max_payload_len)
    {
      return gnuradio::get_initial_sptr
        (new parse_short_bb_impl(len_tag_key, tag_len_payload, own_id, max_payload_len));
    }

    /*
     * The private constructor
     */
    parse_short_bb_impl::parse_short_bb_impl(const std::string   & len_tag_key, 
		                             const std::string   & tag_len_payload, 
		                             const unsigned char   own_id,
		                             const unsigned char   max_payload_len)
      : gr::tagged_stream_block("append_short_bb",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(char)),len_tag_key),
	d_own_id(own_id),
	d_max_payload_len(max_payload_len)

    {
	    set_tag_propagation_policy(TPP_DONT);
	    d_tag_len_payload = tag_len_payload; 
            d_len_tag_key     = len_tag_key; 
	    d_header_length   = 1;
    }

    /*
     * Our virtual destructor.
     */
    parse_short_bb_impl::~parse_short_bb_impl()
    {
    }

    int
    parse_short_bb_impl::calculate_output_stream_length(const gr_vector_int &ninput_items)
    {
      int noutput_items = 1;
      return noutput_items ;
    }

    int
    parse_short_bb_impl::work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const unsigned char   *in = (const unsigned char *)  input_items[0];
      unsigned char        *out = (unsigned char *)       output_items[0];
      size_t      header_length =                         ninput_items[0];
      unsigned char    len_mask =                                     240;
      unsigned char   recv_mask =                                      15;
      std::vector<tag_t>   tags                                          ;  
      unsigned char     pay_len                                          ;
      unsigned char    receiver                                          ;
      if (header_length > d_header_length)
      {
	      out[0] = (unsigned char) 0; 
      }
      else 
      {
	      pay_len  = (unsigned char) (in[0]  &  len_mask)/16;
	      receiver = (unsigned char) in[0]  & recv_mask;
	      if ((pay_len > d_max_payload_len) | !(receiver == d_own_id))
	      {
		      out[0] = (unsigned char) 0; 
	      }
	      else 
	      {
		      out[0] = (unsigned char) 1;
		      get_tags_in_range(tags, 0, nitems_read(0), nitems_read(0) + d_header_length);
		      for (unsigned t =0; t < tags.size(); t++)
		      { 
			      if( !(pmt::equal(tags[t].key, pmt::intern(d_len_tag_key))
					| pmt::equal(tags[t].key, pmt::intern(d_tag_len_payload))))
			      {
				      tags[t].offset = nitems_written(0);
				      add_item_tag(0,tags[t]);
			      }
		      }
		      add_item_tag(0,
				    nitems_written(0), 
				    pmt::intern(d_tag_len_payload),
				    pmt::from_long( (long int) pay_len));  
	      }
      }
      return 1; 


    }
  }/* namespace ownHeader */
} /* namespace gr */

