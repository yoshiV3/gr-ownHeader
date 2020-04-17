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
#include "generate_short_bb_impl.h"

namespace gr {
  namespace ownHeader {

    generate_short_bb::sptr
    generate_short_bb::make(const std::string  & len_tag_key, 
		            const std::string  & tag_payload_len,
		            const std::string  & tag_receiver_key)
    {
      return gnuradio::get_initial_sptr
        (new generate_short_bb_impl(len_tag_key, tag_payload_len, tag_receiver_key));
    }

    /*
     * The private constructor
     */
    generate_short_bb_impl::generate_short_bb_impl(const std::string & len_tag_key, 
		                                   const std::string & tag_payload_len, 
		                                   const std::string & tag_receiver_key)
      : gr::tagged_stream_block("generate_short_bb",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(char)),len_tag_key)

    {
	    set_tag_propagation_policy(TPP_DONT);
	    d_payload_tag_len = tag_payload_len; 
            d_len_tag_key     = len_tag_key; 
	    d_receiver_key    = tag_receiver_key;
    }

    /*
     * Our virtual destructor.
     */
    generate_short_bb_impl::~generate_short_bb_impl()
    {
    }

    int
    generate_short_bb_impl::calculate_output_stream_length(const gr_vector_int &ninput_items)
    {
      int noutput_items = 1;
      return noutput_items ;
    }

    int
    generate_short_bb_impl::work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const unsigned char  *in = (const unsigned char *) input_items[0];
      unsigned char  *out = (unsigned char *) output_items[0];
      unsigned char length_mask   = 16;
      unsigned char receiver      = 0; 
      unsigned char len_pay       = 0;
      pmt::pmt_t    key;
      pmt::pmt_t    value; 
      size_t pay_length = ninput_items[0];
      std::vector<tag_t> tags;
      get_tags_in_range(tags,0,nitems_read(0), nitems_read(0)+pay_length);
      for (unsigned t=0; t< tags.size(); t++)
      {
           key   = tags[t].key;
	   value = tags[t].value;
	   if (pmt::equal(key, pmt::intern(d_payload_tag_len)))
	   {
		   len_pay  = (unsigned char) pmt::to_long(value);
	   }
	   else if (pmt::equal(key, pmt::intern(d_receiver_key)))
	   {
		   receiver = (unsigned char) pmt::to_long(value);
	   }
      }
      out[0] = (unsigned char) len_pay*length_mask + receiver;
    
	

      // Do <+signal processing+>


      // Tell runtime system how many output items we produced.
      return 1;
    }

  } /* namespace ownHeader */
} /* namespace gr */

