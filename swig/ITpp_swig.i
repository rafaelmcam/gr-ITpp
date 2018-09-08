/* -*- c++ -*- */

#define ITPP_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "ITpp_swig_doc.i"

%{
#include "ITpp/nada.h"
#include "ITpp/Hamming_Encoder.h"
%}


%include "ITpp/nada.h"
GR_SWIG_BLOCK_MAGIC2(ITpp, nada);
%include "ITpp/Hamming_Encoder.h"
GR_SWIG_BLOCK_MAGIC2(ITpp, Hamming_Encoder);
