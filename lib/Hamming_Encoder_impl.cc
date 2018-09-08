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
#include "Hamming_Encoder_impl.h"

#include <iostream>
#include <itpp/itcomm.h>
#include <itpp/itbase.h>
#include <itpp/comm/hammcode.h>

namespace gr {
  namespace ITpp {

    Hamming_Encoder::sptr
    Hamming_Encoder::make()
    {
      return gnuradio::get_initial_sptr
        (new Hamming_Encoder_impl());
    }

    /*
     * The private constructor
     */
    Hamming_Encoder_impl::Hamming_Encoder_impl()
      : gr::sync_block("Hamming_Encoder",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(1 , 1, sizeof(unsigned char)))
    {}

    /*
     * Our virtual destructor.
     */
    Hamming_Encoder_impl::~Hamming_Encoder_impl()
    {
    }

    int
    Hamming_Encoder_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const unsigned char *in = (const unsigned char *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];


      itpp::bvec uncoded = "0 0 0 0";
      itpp::bvec encoded;

      itpp::Hamming_Code block(3);

      for(int j = 0; j < noutput_items; j++){
        //printf("In = %d\n", in[j]);
       for (int i = 0; i<4; i++){
         uncoded(3-i) = in[j] >> i & 0x01;
         //printf("%d ", in[j] >> i & 0x01);
      }
      //printf("\n");


      encoded = block.encode(uncoded);



      for (int i = 0; i<7; i++){
         out[j] |= encoded(6-i) << i;
         //printf("%d ", encoded(6-i) << i);
      }

      //printf("\n");
      //printf("Out = %d\n", out[j]);
      }
    
      return noutput_items;
    }

  } /* namespace ITpp */
} /* namespace gr */

