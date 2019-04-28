#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: Top Block
# Author: Rafael Campello
# Description: Script Top Block
# Generated: Sun Apr 28 16:03:14 2019
##################################################


from gnuradio import blocks
from gnuradio import channels
from gnuradio import digital
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from optparse import OptionParser
import os
import argparse

class top_block(gr.top_block):

    def __init__(self, noise):
        gr.top_block.__init__(self, "Top Block")

        ##################################################
        # Variables
        ##################################################
        self.path = path = "/home/rcampello/Main/FixedPath/OOT Gnuradio/gr-ITpp/examples/Scripts Python/Scripts/BPSK - Sem Correlate/red_dot.bmp"
        self.taps = taps = [1]
        self.size_packed_file = size_packed_file = os.path.getsize(path)
        self.samp_rate = samp_rate = 32000 * 20
        self.rrc_taps = rrc_taps = firdes.root_raised_cosine(32, 32, 1.0/float(2), 0.35, 11*2*32)
        self.noise = noise = noise

        self.BPSK = BPSK = digital.constellation_bpsk().base()


        ##################################################
        # Blocks
        ##################################################
        self.digital_pfb_clock_sync_xxx_0 = digital.pfb_clock_sync_ccf(4, 62.8e-3, (rrc_taps), 32, 16, 1.5, 2)
        self.digital_diff_decoder_bb_0 = digital.diff_decoder_bb(2)
        self.digital_costas_loop_cc_0 = digital.costas_loop_cc(62.8e-3, 2, False)
        self.digital_constellation_modulator_0 = digital.generic_mod(
          constellation=BPSK,
          differential=True,
          samples_per_symbol=4,
          pre_diff_code=True,
          excess_bw=0.35,
          verbose=False,
          log=False,
          )
        self.digital_constellation_decoder_cb_0 = digital.constellation_decoder_cb(BPSK)
        self.digital_cma_equalizer_cc_0 = digital.cma_equalizer_cc(15, 1, 0, 2)
        self.channels_channel_model_0 = channels.channel_model(
        	noise_voltage=noise,
        	frequency_offset=0.0,
        	epsilon=1.0,
        	taps=(taps),
        	noise_seed=0,
        	block_tags=False
        )
        self.blocks_vector_source_x_0_0 = blocks.vector_source_b((67, 255), True, 1, [])
        self.blocks_throttle_0 = blocks.throttle(gr.sizeof_char*1, samp_rate,True)
        self.blocks_stream_mux_0 = blocks.stream_mux(gr.sizeof_char*1, (2, 2))
        self.blocks_skiphead_0 = blocks.skiphead(gr.sizeof_char*1, int(size_packed_file * 0.2))
        self.blocks_pack_k_bits_bb_1 = blocks.pack_k_bits_bb(8)
        self.blocks_head_1_0 = blocks.head(gr.sizeof_char*1, size_packed_file*2)
        self.blocks_file_source_0 = blocks.file_source(gr.sizeof_char*1, path, True)
        self.blocks_file_sink_0 = blocks.file_sink(gr.sizeof_char*1, '/home/rcampello/Main/FixedPath/OOT Gnuradio/gr-ITpp/examples/Scripts Python/Scripts/BPSK - Com Correlate/output.data', False)
        self.blocks_file_sink_0.set_unbuffered(False)

        ##################################################
        # Connections
        ##################################################
        self.connect((self.blocks_file_source_0, 0), (self.blocks_throttle_0, 0))
        self.connect((self.blocks_head_1_0, 0), (self.blocks_file_sink_0, 0))
        self.connect((self.blocks_pack_k_bits_bb_1, 0), (self.blocks_skiphead_0, 0))
        self.connect((self.blocks_skiphead_0, 0), (self.blocks_head_1_0, 0))
        self.connect((self.blocks_stream_mux_0, 0), (self.digital_constellation_modulator_0, 0))
        self.connect((self.blocks_throttle_0, 0), (self.blocks_stream_mux_0, 1))
        self.connect((self.blocks_vector_source_x_0_0, 0), (self.blocks_stream_mux_0, 0))
        self.connect((self.channels_channel_model_0, 0), (self.digital_pfb_clock_sync_xxx_0, 0))
        self.connect((self.digital_cma_equalizer_cc_0, 0), (self.digital_costas_loop_cc_0, 0))
        self.connect((self.digital_constellation_decoder_cb_0, 0), (self.digital_diff_decoder_bb_0, 0))
        self.connect((self.digital_constellation_modulator_0, 0), (self.channels_channel_model_0, 0))
        self.connect((self.digital_costas_loop_cc_0, 0), (self.digital_constellation_decoder_cb_0, 0))
        self.connect((self.digital_diff_decoder_bb_0, 0), (self.blocks_pack_k_bits_bb_1, 0))
        self.connect((self.digital_pfb_clock_sync_xxx_0, 0), (self.digital_cma_equalizer_cc_0, 0))

    def get_path(self):
        return self.path

    def set_path(self, path):
        self.path = path
        self.set_size_packed_file(os.path.getsize(self.path))
        self.blocks_file_source_0.open(self.path, True)

    def get_taps(self):
        return self.taps

    def set_taps(self, taps):
        self.taps = taps
        self.channels_channel_model_0.set_taps((self.taps))

    def get_size_packed_file(self):
        return self.size_packed_file

    def set_size_packed_file(self, size_packed_file):
        self.size_packed_file = size_packed_file
        self.blocks_head_1_0.set_length(self.size_packed_file*2)

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.blocks_throttle_0.set_sample_rate(self.samp_rate)

    def get_rrc_taps(self):
        return self.rrc_taps

    def set_rrc_taps(self, rrc_taps):
        self.rrc_taps = rrc_taps
        self.digital_pfb_clock_sync_xxx_0.update_taps((self.rrc_taps))

    def get_noise(self):
        return self.noise

    def set_noise(self, noise):
        self.noise = noise
        self.channels_channel_model_0.set_noise_voltage(self.noise)

    def get_BPSK(self):
        return self.BPSK

    def set_BPSK(self, BPSK):
        self.BPSK = BPSK


def main(top_block_cls=top_block, options=None):
    parser = argparse.ArgumentParser(description='Specify Channel Noise')
    parser.add_argument('--noise', type = float, default = 0.0, help='Channel Noise')

    args = parser.parse_args() 
        
    tb = top_block_cls(args.noise)
    tb.start()
    try:
        raw_input('Press Enter to quit: ')
    except EOFError:
        pass
    tb.stop()
    tb.wait()


if __name__ == '__main__':
    main()
