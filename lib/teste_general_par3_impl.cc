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
#include "teste_general_par3_impl.h"

namespace gr {
  namespace ITpp {

    teste_general_par3::sptr
    teste_general_par3::make(int qtd_in, int rep, int last_value)
    {
      return gnuradio::get_initial_sptr
        (new teste_general_par3_impl(qtd_in, rep, last_value));
    }

    /*
     * The private constructor
     */
    teste_general_par3_impl::teste_general_par3_impl(int qtd_in, int rep, int last_value)
      : gr::block("teste_general_par3",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(1, 1, sizeof(unsigned char)))
    {
      d_qtd_in = qtd_in;
      d_rep = rep;
      d_last_value = last_value;

      set_output_multiple(d_qtd_in+d_rep+1); //+1 é por causa do last_value
      set_max_noutput_items(d_qtd_in+d_rep+1);
    }

    /*
     * Our virtual destructor.
     */
    teste_general_par3_impl::~teste_general_par3_impl()
    {
      //destruir as coisas setadas??
    }

    void
    teste_general_par3_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = (int)(noutput_items * (((float)(d_qtd_in))/((float)(d_qtd_in+d_rep+1))));
    }

    int
    teste_general_par3_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const unsigned char *in = (const unsigned char *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];


      //zerar anterior, ainda é necessário?
      for(int i = 0; i < noutput_items; i++){
      //out[i] = i;
      out[i] = 0;
    }

    //os primeiros "d_qtd_in" da entrada são repetidos na saída
    for(int i = 0; i < d_qtd_in; i++){
      out[i] = in[i];
    }

    //o último valor da entrada é repetido "d_rep" vezes na saída
      for(int i = d_qtd_in; i < noutput_items-1; i++){
        out[i] = in[d_qtd_in-1];
      }

      //último valor dependente do parâmetro "d_last_value"

      out[noutput_items-1] = d_last_value;

      //printf("QTD_IN: %d\nQTD_OUT: %d\n\n", d_qtd_in, noutput_items);

      //consume_each (d_qtd_in);

      consume(0, d_qtd_in);
      //produce(0, noutput_items); por que isso dá problema??

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace ITpp */
} /* namespace gr */

