/*
 * Copyright 2012 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

/*
 * This class gathers together all the test cases for the gr-filter
 * directory into a single test suite.  As you create new test cases,
 * add them here.
 */

#include "qa_ITpp.h"


#include "qa_Hamming_Encoder_par.h"
#include "qa_Hamming_Decoder_par.h"
#include "qa_BSC_Byte.h"

CppUnit::TestSuite *
qa_ITpp::suite()
{
  CppUnit::TestSuite *s = new CppUnit::TestSuite("ITpp");

  s->addTest(gr::ITpp::qa_Hamming_Encoder_par::suite());
  s->addTest(gr::ITpp::qa_Hamming_Decoder_par::suite());
  s->addTest(gr::ITpp::qa_BSC_Byte::suite());

  return s;
}
