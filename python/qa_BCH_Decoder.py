#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2019 <+YOU OR YOUR COMPANY+>.
# 
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

from gnuradio import gr, gr_unittest
from gnuradio import blocks
import ITpp_swig as ITpp

class qa_BCH_Decoder (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_bch_decoder_bb(self):
        expected_result = (0, 0, 0, 0, 1, 0, 1)
        src_data = (0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1)
        src = blocks.vector_source_b(src_data)
        sqr = ITpp.BCH_Decoder(15, 2)
        dst = blocks.vector_sink_b()
        self.tb.connect(src, sqr)
        self.tb.connect(sqr, dst)
        self.tb.run()
        result_data = dst.data()
        self.assertFloatTuplesAlmostEqual(expected_result, result_data, 6)
    
    def test_002_bch_decoder_bb(self):
        expected_result = (0, 0, 0, 0, 0, 0, 0)
        src_data = (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
        src = blocks.vector_source_b(src_data)
        sqr = ITpp.BCH_Decoder(15, 2)
        dst = blocks.vector_sink_b()
        self.tb.connect(src, sqr)
        self.tb.connect(sqr, dst)
        self.tb.run()
        result_data = dst.data()
        self.assertFloatTuplesAlmostEqual(expected_result, result_data, 6)

    def test_003_bch_decoder_bb(self):
        expected_result = (1, 1, 1, 1, 1, 1, 1)
        src_data = (1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1)
        src = blocks.vector_source_b(src_data)
        sqr = ITpp.BCH_Decoder(15, 2)
        dst = blocks.vector_sink_b()
        self.tb.connect(src, sqr)
        self.tb.connect(sqr, dst)
        self.tb.run()
        result_data = dst.data()
        self.assertFloatTuplesAlmostEqual(expected_result, result_data, 6)


if __name__ == '__main__':
    gr_unittest.run(qa_BCH_Decoder, "qa_BCH_Decoder.xml")
