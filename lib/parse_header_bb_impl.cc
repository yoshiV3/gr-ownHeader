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
#include "parse_header_bb_impl.h"
#include <pmt/pmt.h>

namespace gr {
  namespace ownHeader {

    parse_header_bb::sptr
    parse_header_bb::make(const std::string & len_tag_key, const std::string & frame_len_key,
		    	  unsigned char max_symbols, unsigned char own_id,
			  unsigned char max_padding)
    {
      return gnuradio::get_initial_sptr
        (new parse_header_bb_impl(len_tag_key, frame_len_key, max_symbols, own_id, max_padding));
    }

    /*
     * The private constructor
     */
    parse_header_bb_impl::parse_header_bb_impl(const std::string & len_tag_key,
		          const std::string & frame_len_key,
		    	  unsigned char max_symbols, unsigned char own_id,
			  unsigned char max_padding)
      : gr::tagged_stream_block("parse_header_bb",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(char)), len_tag_key),
	d_max_symbols(max_symbols), 
	d_own_id(own_id), 
	d_max_padding(max_padding)
    {
	d_frame_len_key = frame_len_key;
   	d_len_tag_key   = len_tag_key;	
    	d_header_length = 6;
        d_out_length    = 1;
	d_index_sym_cnt = 0;
	d_index_seq_num = 1;
	d_index_send_id = 2;
	d_index_recv_id = 3;
	d_index_pad_cnt = 4;
	d_index_mode    = 5;
	set_tag_propagation_policy(TPP_DONT); 	
    }

    /*
     * Our virtual destructor.
     */
    parse_header_bb_impl::~parse_header_bb_impl()
    {
    }

    int
    parse_header_bb_impl::calculate_output_stream_length(const gr_vector_int &ninput_items)
    {
      int noutput_items = d_out_length;
      return noutput_items ;
    }

    int
    parse_header_bb_impl::work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const unsigned char *in = (const unsigned char *) input_items[0];
      unsigned char *out      = (unsigned char *) output_items[0];
      size_t header_length    = ninput_items[0];
      bool   correct_length = false ; 
      bool   correct_id     = false ; 
      bool   correct_symbol_count = false ; 
      bool   correct_padding_count = false ;
      bool   correct = false;  
      // check header and parse header
      correct_length = (header_length == d_header_length); 
      if (correct_length)
      {
	      correct_symbol_count  = (in[d_index_sym_cnt] <= d_max_symbols);
	      correct_id            = (in[d_index_recv_id] == d_own_id); 
	      correct_padding_count = (in[d_index_pad_cnt] <= d_max_padding);
	      correct = (correct_symbol_count && correct_id && correct_padding_count); 
	      if (correct)
	      {
		     out[0] = (unsigned char) 1;
		     //Propagate tags
		     std::vector<gr::tag_t> tags; 
		     get_tags_in_range(tags, 0, nitems_read(0), nitems_read(0) + d_header_length);
		     for (unsigned t =0; t < tags.size(); t++)
		     {
			     if (!pmt::equal(tags[t].key, pmt::intern(d_frame_len_key)))
			     {
			    	 tags[t].offset = nitems_written(0); 
			   	  add_item_tag(0,tags[t]) ;
			     } 
		     } 
		     //Add new tags
		     add_item_tag(0,
				  nitems_written(0),
				  pmt::intern(d_frame_len_key), 
				  pmt::from_long( (long int) in[d_index_sym_cnt]));
   		     add_item_tag(0,
				  nitems_written(0),
	     			  pmt::intern(std::string ("sequence_number")), 
				  pmt::from_long( (long int) in[d_index_seq_num])); 
		     add_item_tag(0,
   				  nitems_written(0), 
     				  pmt::intern(std::string ("sender_id")),
				  pmt::from_long( (long int) in[d_index_send_id]));
		     add_item_tag(0,
			          nitems_written(0),
	     			  pmt::intern(std::string ("padding")),
				  pmt::from_long( (long int) in[d_index_pad_cnt]));
		    add_item_tag(0,
	       			 nitems_written(0),
     				 pmt::intern(std::string ("mode")),
				 pmt::from_long(( long int )	in[d_index_mode]));			 
	      }
	      else 
	      {
		      out[0] = (unsigned char) 0; 
	      }

      } 

      // Do <+signal processing+>

      // Tell runtime system how many output items we produced.
      return d_out_length;
    }

  } /* namespace ownHeader */
} /* namespace gr */

