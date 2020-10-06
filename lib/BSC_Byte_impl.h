/* -*- c++ -*- */
/* 
 * Copyright 2018 Rafael Campello.
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

#ifndef INCLUDED_ITPP_BSC_BYTE_IMPL_H
#define INCLUDED_ITPP_BSC_BYTE_IMPL_H

#include <ITpp/BSC_Byte.h>

namespace gr {
  namespace ITpp {

    class BSC_Byte_impl : public BSC_Byte
    {
     private:
      int d_bits;
      float d_probability;

     public:
      BSC_Byte_impl(int bits, float probability);
      ~BSC_Byte_impl();
      void set_p(float update_p) override;

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace ITpp
} // namespace gr

#endif /* INCLUDED_ITPP_BSC_BYTE_IMPL_H */

