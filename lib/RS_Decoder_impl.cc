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

#include "RS_Decoder_impl.h"

using namespace itpp;
using std::cout;
using std::endl;

namespace gr {
  namespace ITpp {

    RS_Decoder::sptr
    RS_Decoder::make(int m, int t)
    {
      return gnuradio::get_initial_sptr
        (new RS_Decoder_impl(m, t));
    }

    /*
     * The private constructor
     */
    RS_Decoder_impl::RS_Decoder_impl(int m, int t)
      : bloco(m, t), gr::block("RS_Decoder",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(1, 1, sizeof(unsigned char)))
    {
        
        d_N = m * (round_i(pow(2.0, m) - 1));
        d_K = m * (round_i(pow(2.0, m)) - 1 - 2 * t);
        // d_Q = round_i(pow(2.0, m));
        encoded.set_length(d_N);
        decoded.set_length(d_K);
        set_output_multiple(d_K);
    }

    /*
     * Our virtual destructor.
     */
    RS_Decoder_impl::~RS_Decoder_impl()
    {
    }

    void
    RS_Decoder_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = (int)(noutput_items * ((float)d_N)/((float)d_K));
    }

    int
    RS_Decoder_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const unsigned char *in = (const unsigned char *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];

      for(int i = 0; i < noutput_items/d_K; i++){
        for(int j = 0; j < d_K; j++){
          out[d_K*i+j] = 0;
        }

        for(int j = 0; j < d_N; j++){
          encoded(j) = in[d_N*i+j];
        }

        decoded = bloco.decode(encoded);

        for(int j = 0; j < d_K; j++){
          out[d_K*i+j] = (int)decoded.get(j);
        }
      }

      consume(0, (int)(noutput_items * ((float)d_N)/((float)d_K)));
      return noutput_items;
    }

  } /* namespace ITpp */
} /* namespace gr */

