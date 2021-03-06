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
#include "send_to_multiplexer_b_impl.h"
#include <pmt/pmt.h>

namespace gr {
  namespace ownHeader {

    send_to_multiplexer_b::sptr
    send_to_multiplexer_b::make(const std::string & len_tag_key)
    {
      return gnuradio::get_initial_sptr
        (new send_to_multiplexer_b_impl(len_tag_key));
    }

    /*
     * The private constructor
     */
    send_to_multiplexer_b_impl::send_to_multiplexer_b_impl(const std::string & len_tag_key)
      : gr::sync_block("send_to_multiplexer_b",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(0, 0, 0))
    {
	    d_len_tag = len_tag_key; 
	    d_port_id = pmt::intern(std::string ("header"));
	    message_port_register_out(d_port_id); 
    
    }

    /*
     * Our virtual destructor.
     */
    send_to_multiplexer_b_impl::~send_to_multiplexer_b_impl()
    {
    }

    int
    send_to_multiplexer_b_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const unsigned char *in  = (const unsigned char *) input_items[0];
      size_t number_of_headers = noutput_items; 
      for (int header = 0; header < number_of_headers; header++)
      {
	      if (in[header] == (unsigned char) 0)
	      {
		      d_msg = pmt::PMT_F;
	      }
	      else 
	      {
		      std::vector<tag_t> tags;
		      d_msg = pmt::make_dict();  
		      get_tags_in_range(tags,0, nitems_read(0) + header, nitems_read(0) + header+1);
		      for (const auto & tag: tags)

		      {
			      if (!pmt::equal(tag.key , pmt::intern(d_len_tag)))
			      { 
				    d_msg = dict_add(d_msg, tag.key, tag.value); 
			      }

		      }  


	      }
	      message_port_pub(d_port_id, d_msg);
      }

      // Do <+signal processing+>

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace ownHeader */
} /* namespace gr */

