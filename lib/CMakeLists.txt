# Copyright 2011,2012,2016 Free Software Foundation, Inc.
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

########################################################################
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})
list(APPEND ITpp_sources
    nada_impl.cc
    Hamming_Encoder_impl.cc
    teste_general_impl.cc
    teste_general_par2_impl.cc
    teste_general_par3_impl.cc
    Hamming_Encoder_par_impl.cc
    Hamming_Decoder_par_impl.cc
    BSC_Byte_impl.cc )

set(ITpp_sources "${ITpp_sources}" PARENT_SCOPE)
if(NOT ITpp_sources)
	MESSAGE(STATUS "No C++ sources... skipping lib/")
	return()
endif(NOT ITpp_sources)

add_library(gnuradio-ITpp SHARED ${ITpp_sources})
target_link_libraries(gnuradio-ITpp ${Boost_LIBRARIES} ${GNURADIO_ALL_LIBRARIES} ${ITPP_LIBRARIES})
set_target_properties(gnuradio-ITpp PROPERTIES DEFINE_SYMBOL "gnuradio_ITpp_EXPORTS")

if(APPLE)
    set_target_properties(gnuradio-ITpp PROPERTIES
        INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib"
    )
endif(APPLE)

########################################################################
# Install built library files
########################################################################
include(GrMiscUtils)
GR_LIBRARY_FOO(gnuradio-ITpp RUNTIME_COMPONENT "ITpp_runtime" DEVEL_COMPONENT "ITpp_devel")

########################################################################
# Build and register unit test
########################################################################
include(GrTest)

include_directories(${CPPUNIT_INCLUDE_DIRS})
list(APPEND test_ITpp_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/test_ITpp.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_ITpp.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_BSC_Byte.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_Hamming_Decoder_par.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_Hamming_Encoder_par.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_teste_general_par3.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_teste_general_par2.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_teste_general.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_Hamming_Encoder.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_nada.cc
)

add_executable(test-ITpp ${test_ITpp_sources})

target_link_libraries(
  test-ITpp
  ${GNURADIO_RUNTIME_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CPPUNIT_LIBRARIES}
  gnuradio-ITpp
)

GR_ADD_TEST(test_ITpp test-ITpp)

########################################################################
# Print summary
########################################################################
message(STATUS "Using install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Building for version: ${VERSION} / ${LIBVER}")

