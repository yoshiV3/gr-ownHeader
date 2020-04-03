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


#ifndef INCLUDED_OWNHEADER_PARSE_HEADER_B_H
#define INCLUDED_OWNHEADER_PARSE_HEADER_B_H

#include <ownHeader/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace ownHeader {

    /*!
     * \brief <+description of block+>
     * \ingroup ownHeader
     *
     */
    class OWNHEADER_API parse_header_b : virtual public gr::tagged_stream_block
    {
     public:
      typedef boost::shared_ptr<parse_header_b> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of ownHeader::parse_header_b.
       *
       * To avoid accidental use of raw pointers, ownHeader::parse_header_b's
       * constructor is in a private implementation
       * class. ownHeader::parse_header_b::make is the public interface for
       * creating new instances.
       */
      static sptr make(const std::string& len_tag_key);
    };

  } // namespace ownHeader
} // namespace gr

#endif /* INCLUDED_OWNHEADER_PARSE_HEADER_B_H */

