#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright 2012,2013 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
#

"""
BER simulation for QPSK signals, compare to theoretical values.
Change the N_BITS value to simulate more bits per Eb/N0 value,
thus allowing to check for lower BER values.

Lower values will work faster, higher values will use a lot of RAM.
Also, this app isn't highly optimized--the flow graph is completely
reinstantiated for every Eb/N0 value.
Of course, expect the maximum value for BER to be one order of
magnitude below what you chose for N_BITS.
"""


import math
import numpy
from gnuradio import gr, digital
from gnuradio import analog
from gnuradio import blocks
import sys
from ITpp import Hamming_Encoder_par, Hamming_Decoder_par


try:
    from scipy.special import comb
    from scipy.special import erfc
except ImportError:
    print "Error: could not import scipy (http://www.scipy.org/)"
    sys.exit(1)

try:
    import pylab
except ImportError:
    print "Error: could not import pylab (http://matplotlib.sourceforge.net/)"
    sys.exit(1)

# Best to choose powers of 10
#N_BITS = 1e7
N_BITS = 1e7
RAND_SEED = 43


def Q(x):
    return (0.5 * erfc(x/(numpy.sqrt(2))))

def Pb_BPSK(EbN0):
    return Q(numpy.sqrt(2*EbN0))

def Pb_DBPSK(EbN0):
    return 2 * Q(numpy.sqrt(2*EbN0)) - 2 * Q(numpy.sqrt(2*EbN0))**2

def from_dB(x):
    return math.pow(10, x/10)

def Pb_Hard_Codes(p, N, t):
    Sum = 0
    for m in range(t+1, N + 1):
        x = (m + t) * comb(N, m, exact = True, repetition = False) * p ** (m) * (1 - p) ** (N - m)
        Sum += x
    return Sum/N

def Cota_High(Ps):
    return (1 - ((1-Ps)**7 + 7 * (1 - Ps)**6 * Ps))

def Cota_Low(Ps, k):
    return (Cota_High(Ps)/k)

def berawgn_BPSK(EbN0):
    """ Calculates theoretical bit error rate in AWGN (for BPSK and given Eb/N0) """
    return Pb_BPSK(from_dB(EbN0))

def berawgn_DBPSK(EbN0):
    """ Calculates theoretical bit error rate in AWGN (for DBPSK and given Eb/N0) """
    return Pb_DBPSK(from_dB(EbN0))

class BitErrors(gr.hier_block2):
    """ Two inputs: true and received bits. We compare them and
    add up the number of incorrect bits. Because integrate_ff()
    can only add up a certain number of values, the output is
    not a scalar, but a sequence of values, the sum of which is
    the BER. """
    def __init__(self, bits_per_byte):
        gr.hier_block2.__init__(self, "BitErrors",
                gr.io_signature(2, 2, gr.sizeof_char),
                gr.io_signature(1, 1, gr.sizeof_int))

        # Bit comparison
        comp = blocks.xor_bb()
        intdump_decim = 100000

	#print(bits_per_byte)

        if N_BITS < intdump_decim:
            intdump_decim = int(N_BITS)
        self.connect(self,
                     comp,
                     blocks.unpack_k_bits_bb(bits_per_byte),
                     blocks.uchar_to_float(),
                     blocks.integrate_ff(intdump_decim),
                     blocks.multiply_const_ff(1.0/N_BITS),
                     self)
        self.connect((self, 1), (comp, 1))

class BERAWGNSimu(gr.top_block):
    " This contains the simulation flow graph "
    def __init__(self, EbN0):
        gr.top_block.__init__(self)
        self.const = digital.bpsk_constellation()
        # Source is N_BITS bits, non-repeated

	#print("BITS PER SYMBOL: ", self.const.bits_per_symbol())
	#print("arity: ", self.const.arity())

        data = map(int, numpy.random.randint(0, self.const.arity(), int(N_BITS/self.const.bits_per_symbol())))
        src   = blocks.vector_source_b(data, False)
        mod   = digital.chunks_to_symbols_bc((self.const.points()), 1)
        add   = blocks.add_vcc()

	#print("Gaussian amplitude: ", self.EbN0_to_noise_voltage(EbN0))

        noise = analog.noise_source_c(analog.GR_GAUSSIAN,
                                      self.EbN0_to_noise_voltage(EbN0),
                                      RAND_SEED)
        demod = digital.constellation_decoder_cb(self.const.base())
        ber   = BitErrors(self.const.bits_per_symbol())
        self.sink  = blocks.vector_sink_f()
        self.connect(src, mod, add, demod, ber, self.sink)
        self.connect(noise, (add, 1))
        self.connect(src, (ber, 1))

    def EbN0_to_noise_voltage(self, EbN0):
        """ Converts Eb/N0 to a complex noise voltage (assuming unit symbol power) """
	#print("BITS PER SYMBOL: ", self.const.bits_per_symbol())
        return 1.0 / math.sqrt(self.const.bits_per_symbol() * 10**(float(EbN0)/10))

class BERAWGNSimu2(gr.top_block):
    " This contains the simulation flow graph "
    def __init__(self, EbN0):
        gr.top_block.__init__(self)
        self.const = digital.bpsk_constellation()
        # Source is N_BITS bits, non-repeated

	#print("BITS PER SYMBOL: ", self.const.bits_per_symbol())
	#print("arity: ", self.const.arity())

        data = map(int, numpy.random.randint(0, self.const.arity(), int(N_BITS/self.const.bits_per_symbol())))
        src   = blocks.vector_source_b(data, False)
	enc   = Hamming_Encoder_par(3)
        mod   = digital.chunks_to_symbols_bc((self.const.points()), 1)
        add   = blocks.add_vcc()

	#print("Gaussian amplitude: ", self.EbN0_to_noise_voltage(EbN0))

        noise = analog.noise_source_c(analog.GR_GAUSSIAN,
                                      self.EbN0_to_noise_voltage(EbN0),
                                      RAND_SEED)
        demod = digital.constellation_decoder_cb(self.const.base())
	dec = Hamming_Decoder_par(3)
        ber   = BitErrors(self.const.bits_per_symbol())
        self.sink  = blocks.vector_sink_f()
        self.connect(src, enc, mod, add, demod, dec, ber, self.sink)
        self.connect(noise, (add, 1))
        self.connect(src, (ber, 1))

    def EbN0_to_noise_voltage(self, EbN0):
        """ Converts Eb/N0 to a complex noise voltage (assuming unit symbol power) """
	#print("BITS PER SYMBOL: ", self.const.bits_per_symbol())
        return 1.0 / math.sqrt(self.const.bits_per_symbol() * 10**(float(EbN0-2.43)/10))#conversão para EbN0 com código (-10log(7/4)) porque o erro que estamos interessados é da palavra não codificada(k) e estamos adicionando ruído em cima da palavra codificada(n)


def simulate_ber(EbN0):
    """ All the work's done here: create flow graph, run, read out BER """
    print "Eb/N0 = {} dB".format(EbN0)
    fg = BERAWGNSimu(EbN0)
    fg.run()
    res = numpy.sum(fg.sink.data())
    print("BER: {}\n".format(res))
    return res

def simulate_ber2(EbN0):
    """ All the work's done here: create flow graph, run, read out BER """
    print "Eb/N0 = {} dB".format(EbN0)
    fg = BERAWGNSimu2(EbN0)
    fg.run()
    res = numpy.sum(fg.sink.data())
    print("BER: {}\n".format(res))
    return res

if __name__ == "__main__":
    EbN0_min = 0
    EbN0_max = 10
    EbN0_range = range(EbN0_min, EbN0_max+1)
    #EbN0_range = [0.5*x for x in range(EbN0_min*2, (EbN0_max+1)*2)]
    ber_theory = [berawgn_BPSK(float(x))      for x in EbN0_range]
    ber_theory2 = [Pb_Hard_Codes(Pb_BPSK(from_dB(float(x) - 10 * math.log10(float(7)/float(4)))), 7, 1)  for x in EbN0_range]
    cota_high = [Cota_High(Pb_BPSK(from_dB(float(x) - 10 * math.log10(float(7)/float(4))))) for x in EbN0_range]
    cota_low = [Cota_Low(Pb_BPSK(from_dB(float(x) - 10 * math.log10(float(7)/float(4)))), 4) for x in EbN0_range]
    print(ber_theory)
    print(ber_theory2)
    print(cota_high)
    print(cota_low)
    print "Simulating..."
    ber_simu   = [simulate_ber(x) for x in EbN0_range]
    ber_simu2  = [simulate_ber2(x) for x in EbN0_range]

    f = pylab.figure()
    s = f.add_subplot(1,1,1)
    s.semilogy(EbN0_range, ber_theory, 'g-.', label="Theoretical BPSK")
    s.semilogy(EbN0_range, ber_theory2, 'y-.', label="Theoretical BPSK + Hamming")
    s.semilogy(EbN0_range, ber_simu, 'b-o', label="Simulated BPSK")
    s.semilogy(EbN0_range, ber_simu2, 'r-o', label="Simulated BPSK - Hamming")
    s.semilogy(EbN0_range, cota_high, 'm-.', label="Cota High")
    s.semilogy(EbN0_range, cota_low, 'c-.', label="Cota Low")
    s.set_title('BER Simulation - BPSK')
    s.set_xlabel('Eb/N0 (dB)')
    s.set_ylabel('BER')
    s.legend()
    s.grid()
    pylab.show()

