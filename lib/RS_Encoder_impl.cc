/* -*- c++ -*- */
/* MIT License
 * 
 * Copyright (c) 2019 rafaelmcam
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include <itpp/itcomm.h>

#include "RS_Encoder_impl.h"

using namespace itpp;
using std::cout;
using std::endl;

namespace gr {
  namespace ITpp {

    RS_Encoder::sptr
    RS_Encoder::make(int m, int t)
    {
      return gnuradio::get_initial_sptr
        (new RS_Encoder_impl(m, t));
    }

    /*
     * The private constructor
     */
    RS_Encoder_impl::RS_Encoder_impl(int m, int t)
      : bloco(m, t), gr::block("RS_Encoder",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(1, 1, sizeof(unsigned char)))
    {
         
        d_N = m * (round_i(pow(2.0, m) - 1));
        d_K = m * (round_i(pow(2.0, m)) - 1 - 2 * t);
        // d_Q = round_i(pow(2.0, m));
        uncoded.set_length(d_K);
        set_output_multiple(d_N);
        
    }

    /*
     * Our virtual destructor.
     */
    RS_Encoder_impl::~RS_Encoder_impl()
    {
    }

    void
    RS_Encoder_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = (int)(noutput_items * ((float)d_K)/((float)d_N));
    }

    int
    RS_Encoder_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const unsigned char *in = (const unsigned char *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];

      uncoded.zeros();

      for(int i = 0; i < noutput_items/d_N; i++){
        for(int j = 0; j < d_N; j++){
            out[d_N*i+j] = 0; 
        } 
        for(int j = 0; j < d_K; j++){
            uncoded(j) = in[d_K*i+j]; 
        }

        encoded = bloco.encode(uncoded);

        for(int j = 0; j < d_N; j++){
            out[d_N*i+j] = (int)encoded.get(j);
        }
      }
      
      consume(0, (int)(noutput_items * ((float)d_K)/((float)d_N)));
      return noutput_items;
    }

  } /* namespace ITpp */
} /* namespace gr */

