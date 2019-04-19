#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: Top Block
# Generated: Fri Apr 19 11:25:15 2019
##################################################


from gnuradio import blocks
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from optparse import OptionParser

import matplotlib.pyplot as plt
import numpy as np

class top_block(gr.top_block):

    def __init__(self, source_array):
        gr.top_block.__init__(self, "Top Block")

        ##################################################
        # Variables
        ##################################################
        self.samp_rate = samp_rate = 32000
        self.source_tuple = source_array

        ##################################################
        # Blocks
        ##################################################
        self.blocks_vector_source_x_0 = blocks.vector_source_b(self.source_tuple, True, 1, [])
        self.blocks_unpack_k_bits_bb_0 = blocks.unpack_k_bits_bb(8)
        # self.blocks_uchar_to_float_0 = blocks.uchar_to_float()
        self.blocks_throttle_0 = blocks.throttle(gr.sizeof_char*1, samp_rate,True)
        # self.blocks_null_sink_0 = blocks.null_sink(gr.sizeof_float*1)
        self.blocks_head_0 = blocks.head(gr.sizeof_char*1, 8*3)
        self.sink = blocks.vector_sink_b()
        ##################################################
        # Connections
        ##################################################
        self.connect((self.blocks_head_0, 0), (self.sink, 0))
        self.connect((self.blocks_throttle_0, 0), (self.blocks_unpack_k_bits_bb_0, 0))
        # self.connect((self.blocks_uchar_to_float_0, 0), (self.blocks_head_0, 0))
        self.connect((self.blocks_unpack_k_bits_bb_0, 0), (self.blocks_head_0, 0))
        self.connect((self.blocks_vector_source_x_0, 0), (self.blocks_throttle_0, 0))

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.blocks_throttle_0.set_sample_rate(self.samp_rate)


def main(top_block_cls=top_block, options=None):

    tb = top_block_cls()
    tb.start()
    tb.wait()

    print(np.sum(tb.sink.data()))
    return 

def simulate(source_array):
    fg = top_block(source_array = source_array)
    fg.run()
    #print(np.sum(fg.sink.data()))
    print(np.array(fg.sink.data()).shape)
    return


if __name__ == '__main__':
    simulate((0, 4, 0))
    # simulate((255, 255, 255))
    # simulate((1, 1, 1))
