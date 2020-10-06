/* -*- c++ -*- */
/*
 * Copyright 2019 Rafael Campello.
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

#ifndef INCLUDED_ITPP_BSC_BYTE_H
#define INCLUDED_ITPP_BSC_BYTE_H

#include <ITpp/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace ITpp {

    /*!
     * \brief <+description of block+>
     * \ingroup ITpp
     *
     */
    class ITPP_API BSC_Byte : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<BSC_Byte> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of ITpp::BSC_Byte.
       *
       * To avoid accidental use of raw pointers, ITpp::BSC_Byte's
       * constructor is in a private implementation
       * class. ITpp::BSC_Byte::make is the public interface for
       * creating new instances.
       */
      static sptr make(int bits, float probability);

        virtual void set_p(float update_p) = 0;
    };

  } // namespace ITpp
} // namespace gr

#endif /* INCLUDED_ITPP_BSC_BYTE_H */

