/* -*- c++ -*- */

#define ITPP_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "ITpp_swig_doc.i"

%{
#include "ITpp/nada.h"
#include "ITpp/Hamming_Encoder.h"
#include "ITpp/teste_general.h"
#include "ITpp/teste_general_par2.h"
#include "ITpp/teste_general_par3.h"
%}


%include "ITpp/nada.h"
GR_SWIG_BLOCK_MAGIC2(ITpp, nada);
%include "ITpp/Hamming_Encoder.h"
GR_SWIG_BLOCK_MAGIC2(ITpp, Hamming_Encoder);
%include "ITpp/teste_general.h"
GR_SWIG_BLOCK_MAGIC2(ITpp, teste_general);

%include "ITpp/teste_general_par2.h"
GR_SWIG_BLOCK_MAGIC2(ITpp, teste_general_par2);
%include "ITpp/teste_general_par3.h"
GR_SWIG_BLOCK_MAGIC2(ITpp, teste_general_par3);
