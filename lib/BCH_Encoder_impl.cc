/* -*- c++ -*- */
/* 
 * Copyright 2019 <+YOU OR YOUR COMPANY+>.
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
#include <itpp/comm/bch.h>

#include "BCH_Encoder_impl.h"

using namespace itpp;
using std::cout;
using std::endl;

namespace gr {
  namespace ITpp {

    BCH_Encoder::sptr
    BCH_Encoder::make(int n, int t)
    {
      return gnuradio::get_initial_sptr
        (new BCH_Encoder_impl(n, t));
    }

    /*
     * The private constructor
     */
    BCH_Encoder_impl::BCH_Encoder_impl(int n, int t)
      : gr::block("BCH_Encoder",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(1, 1, sizeof(unsigned char)))
    {
      d_N = n;
      d_T = t;
      itpp:BCH block(d_N, d_T);
      d_K = block.get_k();

      set_output_multiple(d_N);
    }

    /*
     * Our virtual destructor.
     */
    BCH_Encoder_impl::~BCH_Encoder_impl()
    {
    }

    void
    BCH_Encoder_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = (int)(noutput_items * ((float)d_K)/((float)d_N));
    }

    int
    BCH_Encoder_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const unsigned char *in = (const unsigned char *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];


      itpp::bvec uncoded, encoded;
      uncoded.set_length(d_K);
      uncoded.zeros();
      itpp::BCH block(d_N, d_T);


      for(int i = 0; i < noutput_items/d_N; i++){
        
        for(int j = 0; j < d_N; j++){
          out[d_N*i+j] = 0;
        }

        for(int j = 0; j < d_K; j++){
          uncoded(j) = in[d_K*i+j];
        }
        
        encoded = block.encode(uncoded);

        for(int j = 0; j < d_N; j++){
          out[d_N*i+j] = (int)encoded.get(j);
        }

      }

      consume(0, (int)(noutput_items * ((float)d_K)/((float)d_N)));
      return noutput_items;
    }

  } /* namespace ITpp */
} /* namespace gr */

