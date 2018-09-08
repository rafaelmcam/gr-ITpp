/* -*- c++ -*- */
/* 
 * Copyright 2018 <+YOU OR YOUR COMPANY+>.
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


#ifndef INCLUDED_ITPP_HAMMING_ENCODER_H
#define INCLUDED_ITPP_HAMMING_ENCODER_H

#include <ITpp/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace ITpp {

    /*!
     * \brief <+description of block+>
     * \ingroup ITpp
     *
     */
    class ITPP_API Hamming_Encoder : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<Hamming_Encoder> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of ITpp::Hamming_Encoder.
       *
       * To avoid accidental use of raw pointers, ITpp::Hamming_Encoder's
       * constructor is in a private implementation
       * class. ITpp::Hamming_Encoder::make is the public interface for
       * creating new instances.
       */
      static sptr make();
    };

  } // namespace ITpp
} // namespace gr

#endif /* INCLUDED_ITPP_HAMMING_ENCODER_H */

