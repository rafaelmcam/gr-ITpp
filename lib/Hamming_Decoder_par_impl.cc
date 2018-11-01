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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>

#include <itpp/itbase.h>
#include <itpp/comm/hammcode.h>

#include "Hamming_Decoder_par_impl.h"

using namespace itpp;
using std::cout;
using std::endl;

namespace gr {
  namespace ITpp {

    Hamming_Decoder_par::sptr
    Hamming_Decoder_par::make(int m)
    {
      return gnuradio::get_initial_sptr
        (new Hamming_Decoder_par_impl(m));
    }

    /*
     * The private constructor
     */
    Hamming_Decoder_par_impl::Hamming_Decoder_par_impl(int m)
      : gr::block("Hamming_Decoder_par",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(1, 1, sizeof(unsigned char)))
    {
      d_m = m;

      itpp::Hamming_Code block(d_m);
      d_K = block.get_k();
      d_N = block.get_n();


      set_output_multiple(d_K);
      }

    /*
     * Our virtual destructor.
     */
    Hamming_Decoder_par_impl::~Hamming_Decoder_par_impl()
    {
    }

    void
    Hamming_Decoder_par_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = (int)(noutput_items * ((float)d_N)/((float)d_K));
    }

    int
    Hamming_Decoder_par_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const unsigned char *in = (const unsigned char *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];

      itpp::bvec decoded, encoded;
      encoded.set_length(d_N);
      encoded.zeros();
      itpp::Hamming_Code block(d_m);

      for(int i = 0; i < noutput_items/d_K; i++){
        for(int j = 0; j < d_K; j++){
          out[d_K*i+j] = 0;
        }

        for(int j = 0; j < d_N; j++){
          encoded(j) = in[d_N*i+j];
        }

        decoded = block.decode(encoded);

        for(int j = 0; j < d_K; j++){
          out[d_K*i+j] = (int)decoded.get(j);
        }
      }

      consume(0, (int)(noutput_items * ((float)d_N)/((float)d_K)));
      return noutput_items;
    }

  } /* namespace ITpp */
} /* namespace gr */

