#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: Top Block
# Generated: Thu Jun 27 11:05:29 2019
##################################################


from gnuradio import blocks
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from optparse import OptionParser
import ITpp


class top_block(gr.top_block):

    def __init__(self):
        gr.top_block.__init__(self, "Top Block")

        ##################################################
        # Variables
        ##################################################
        self.samp_rate = samp_rate = 32000
        self.delay = delay = 0

        ##################################################
        # Blocks
        ##################################################
        self.blocks_unpack_k_bits_bb_0 = blocks.unpack_k_bits_bb(8)
        self.blocks_throttle_0 = blocks.throttle(gr.sizeof_char*1, samp_rate * 20,True)
        self.blocks_pack_k_bits_bb_1 = blocks.pack_k_bits_bb(8)
        self.blocks_head_1 = blocks.head(gr.sizeof_char*1, int(7 * 200e3 * 15/15))
        self.blocks_file_source_0 = blocks.file_source(gr.sizeof_char*1, '/home/rcampello/Main/FixedPath/OOT Gnuradio/gr-ITpp/examples/BPSK Ladams/27-06-2019 (BER Sem Diff)/Com C\xc3\xb3digo/output2.data', True)
        self.blocks_file_sink_0 = blocks.file_sink(gr.sizeof_char*1, '/home/rcampello/Main/FixedPath/OOT Gnuradio/gr-ITpp/examples/BPSK Ladams/27-06-2019 (BER Sem Diff)/Com C\xc3\xb3digo/output3.data', False)
        self.blocks_file_sink_0.set_unbuffered(False)
        self.blocks_delay_0 = blocks.delay(gr.sizeof_char*1, int(delay))
        self.ITpp_BCH_Decoder_0 = ITpp.BCH_Decoder(15, 2)

        ##################################################
        # Connections
        ##################################################
        self.connect((self.ITpp_BCH_Decoder_0, 0), (self.blocks_pack_k_bits_bb_1, 0))
        self.connect((self.blocks_delay_0, 0), (self.ITpp_BCH_Decoder_0, 0))
        self.connect((self.blocks_file_source_0, 0), (self.blocks_throttle_0, 0))
        self.connect((self.blocks_head_1, 0), (self.blocks_file_sink_0, 0))
        self.connect((self.blocks_pack_k_bits_bb_1, 0), (self.blocks_head_1, 0))
        self.connect((self.blocks_throttle_0, 0), (self.blocks_unpack_k_bits_bb_0, 0))
        self.connect((self.blocks_unpack_k_bits_bb_0, 0), (self.blocks_delay_0, 0))

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.blocks_throttle_0.set_sample_rate(self.samp_rate * 20)

    def get_delay(self):
        return self.delay

    def set_delay(self, delay):
        self.delay = delay
        self.blocks_delay_0.set_dly(int(self.delay))


def main(top_block_cls=top_block, options=None):

    tb = top_block_cls()
    tb.start()
    tb.wait()


if __name__ == '__main__':
    main()
