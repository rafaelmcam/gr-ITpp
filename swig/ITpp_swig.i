/* -*- c++ -*- */

#define ITPP_API

%include "gnuradio.i"           // the common stuff

//load generated python docstrings
%include "ITpp_swig_doc.i"

%{
#include "ITpp/BCH_Encoder.h"
#include "ITpp/BCH_Decoder.h"
#include "ITpp/BSC_Byte.h"
%}

%include "ITpp/BCH_Encoder.h"
GR_SWIG_BLOCK_MAGIC2(ITpp, BCH_Encoder);
%include "ITpp/BCH_Decoder.h"
GR_SWIG_BLOCK_MAGIC2(ITpp, BCH_Decoder);
%include "ITpp/BSC_Byte.h"
GR_SWIG_BLOCK_MAGIC2(ITpp, BSC_Byte);
