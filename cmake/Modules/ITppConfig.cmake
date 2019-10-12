INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_ITPP ITpp)

FIND_PATH(
    ITPP_INCLUDE_DIRS
    NAMES ITpp/api.h
    HINTS $ENV{ITPP_DIR}/include
        ${PC_ITPP_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    ITPP_LIBRARIES
    NAMES gnuradio-ITpp
    HINTS $ENV{ITPP_DIR}/lib
        ${PC_ITPP_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/ITppTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(ITPP DEFAULT_MSG ITPP_LIBRARIES ITPP_INCLUDE_DIRS)
MARK_AS_ADVANCED(ITPP_LIBRARIES ITPP_INCLUDE_DIRS)
