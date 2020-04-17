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


#ifndef INCLUDED_OWNHEADER_GENERATE_SHORT_BB_H
#define INCLUDED_OWNHEADER_GENERATE_SHORT_BB_H

#include <ownHeader/api.h>
#include <gnuradio/tagged_stream_block.h>

namespace gr {
  namespace ownHeader {

    /*!
     * \brief <+description of block+>
     * \ingroup ownHeader
     *
     */
    class OWNHEADER_API generate_short_bb : virtual public gr::tagged_stream_block
    {
     public:
      typedef boost::shared_ptr<generate_short_bb> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of ownHeader::generate_short_bb.
       *
       * To avoid accidental use of raw pointers, ownHeader::generate_short_bb's
       * constructor is in a private implementation
       * class. ownHeader::generate_short_bb::make is the public interface for
       * creating new instances.
       */
      static sptr make(const std::string &      tag_len_key="packet_len", 
		       const std::string &  tag_payload_len="payload_len",
		       const std::string & tag_receiver_key="receiver_id");
    };

  } // namespace ownHeader
} // namespace gr

#endif /* INCLUDED_OWNHEADER_GENERATE_SHORT_BB_H */

