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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>

#include <itpp/itbase.h>
#include <itpp/comm/channel.h>

#include "BSC_Byte_impl.h"

using namespace itpp;
using std::cout;
using std::endl;

namespace gr {
  namespace ITpp {

    BSC_Byte::sptr
    BSC_Byte::make(int bits, float probability)
    {
      return gnuradio::get_initial_sptr
        (new BSC_Byte_impl(bits, probability));
    }

    /*
     * The private constructor
     */
    BSC_Byte_impl::BSC_Byte_impl(int bits, float probability)
      : gr::sync_block("BSC_Byte",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(1, 1, sizeof(unsigned char)))
    {
      d_probability = probability;
      d_bits = bits;

      RNG_randomize();

    }

    /*
     * Our virtual destructor.
     */
    BSC_Byte_impl::~BSC_Byte_impl()
    {
    }

    void BSC_Byte_impl::set_p(float update_p){
        d_probability = update_p;
    }

    int
    BSC_Byte_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const unsigned char *in = (const unsigned char *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];

      itpp::bvec entrada_bits;
      entrada_bits.set_length(d_bits);
      entrada_bits.zeros();

      for(int j = 0; j < noutput_items; j++){
        out[j] = 0;

      //RNG_randomize();
      ittp:BSC bsc(d_probability);

      for(int i = 0; i < d_bits; i++){
        entrada_bits(i) = (in[j] >> i) & 0x01;
      }

      entrada_bits = bsc(entrada_bits);

      for(int i = 0; i < d_bits; i++){
        out[j] |= ((int)entrada_bits.get(i) << i);
      }

      //cout << entrada_bits << endl;

      }

     // cout << entrada_bits << endl;
      //cout << noutput_items << endl;

      return noutput_items;
    }

  } /* namespace ITpp */
} /* namespace gr */

