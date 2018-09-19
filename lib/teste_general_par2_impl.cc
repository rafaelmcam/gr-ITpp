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
#include "teste_general_par2_impl.h"

namespace gr {
  namespace ITpp {

    teste_general_par2::sptr
    teste_general_par2::make(int rep, int last_value)
    {
      return gnuradio::get_initial_sptr
        (new teste_general_par2_impl(rep, last_value));
    }

    /*
     * The private constructor
     */
    teste_general_par2_impl::teste_general_par2_impl(int rep, int last_value)
      : gr::block("teste_general_par2",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(1, 1, sizeof(unsigned char)))
    {
      d_rep = rep;
      d_last_value = last_value;
      set_output_multiple(3+d_rep+1); //+1 é por causa do last_value
      set_max_noutput_items(3+d_rep+1);
      }

    /*
     * Our virtual destructor.
     */
    teste_general_par2_impl::~teste_general_par2_impl()
    {
    }

    void
    teste_general_par2_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = (int)(noutput_items * (3.0f/((float)(3+d_rep))));
    }

    int
    teste_general_par2_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const unsigned char *in = (const unsigned char *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];

      for(int i = 0; i < noutput_items; i++){
      //out[i] = i;
      out[i] = 0;
    }


      out[0] = in[0];
      out[1] = in[1];
      out[2] = in[2];
      for(int i = 3; i < noutput_items-1; i++){
        out[i] = in[2];
      }
      out[noutput_items-1] = d_last_value;
      // out[3] = in[2];
      // out[4] = in[2];

      consume_each (3);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace ITpp */
} /* namespace gr */

