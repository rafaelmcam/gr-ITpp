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
#include "teste_general_impl.h"
#include <stdio.h>

namespace gr {
  namespace ITpp {

    teste_general::sptr
    teste_general::make()
    {
      return gnuradio::get_initial_sptr
        (new teste_general_impl());
    }

    /*
     * The private constructor
     */
    teste_general_impl::teste_general_impl()
      : gr::block("teste_general",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(1, 1, sizeof(unsigned char)))
    {
      
      set_output_multiple(5);
      set_max_noutput_items(5);
      //set_fixed_rate(true); //dá erro...
      //printf("TESTE\n");
      //printf("output multiple=%d\n", output_multiple() );
    }

    /*
     * Our virtual destructor.
     */
    teste_general_impl::~teste_general_impl()
    {
    }

    void
    teste_general_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */

      // unsigned ninputs = ninput_items_required.size (); //esse size retorna 1 se só tiver 1 entrada, não é o tamanho do tipo ou algo parecido.
      // // for(unsigned i = 0; i < ninputs; i++){
      // //     ninput_items_required[i] = (int) ((float)noutput_items * ((float)3)/((float)5)); //esse loop é inútil para 1 entrada apenas, só é a implementação geral. [0]-> entrada número 1, só faz sentido o loop se tivesse mais de uma entrada. mas vou deixar porque é a implementação geral.
      // // }
       ninput_items_required[0] = (int)(noutput_items * (3.0f/5.0f));
       //ninput_items_required[0] = (int)(noutput_items);
    }

    int
    teste_general_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const unsigned char *in = (const unsigned char *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];

      // Do <+signal processing+>

    // for(int i = 0; i < noutput_items; i++){
    //     out[i] = 0;
        
    //     // for(int j = 0; j < 3; j++){
    //     //    out[i] = in[i] + j + 1;
    //     // }

    // }
    for(int i = 0; i < noutput_items; i++){
      //out[i] = i;
      out[i] = 0;
    }


      out[0] = in[0];
      out[1] = in[1];
      out[2] = in[2];
      out[3] = in[2];
      out[4] = in[2];


      // out[0] = 4;
      // out[1] = 6;

      //printf("noutput=%d\nninput=%d\n\n", noutput_items, ninput_items[0]);
      //printf("%d", (int)(noutput_items * (3.0f/5.0f)));
      //printf("%d\n", (int) ((float)noutput_items * ((float)3)/((float)5)));
      //printf("%lf", (double) ((float)20*((float)3)/((float)5)));
      // Tell runtime system how many input items we consumed on
      // each input stream.
      //consume_each (((int) ((float)noutput_items * ((float)3)/((float)5))));
      consume_each(3);
      //produce(0, 5);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace ITpp */
} /* namespace gr */

