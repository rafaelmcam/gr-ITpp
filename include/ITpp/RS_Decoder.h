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


#ifndef INCLUDED_ITPP_RS_DECODER_H
#define INCLUDED_ITPP_RS_DECODER_H

#include <ITpp/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace ITpp {

    /*!
     * \brief <+description of block+>
     * \ingroup ITpp
     *
     */
    class ITPP_API RS_Decoder : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<RS_Decoder> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of ITpp::RS_Decoder.
       *
       * To avoid accidental use of raw pointers, ITpp::RS_Decoder's
       * constructor is in a private implementation
       * class. ITpp::RS_Decoder::make is the public interface for
       * creating new instances.
       */
      static sptr make(int m, int t);
    };

  } // namespace ITpp
} // namespace gr

#endif /* INCLUDED_ITPP_RS_DECODER_H */

