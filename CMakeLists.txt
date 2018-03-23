cmake_minimum_required(VERSION 3.5)
project (vps)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig)
pkg_check_modules(PC_ZBAR QUIET zbar)
set(ZBAR_DEFINITIONS ${PC_ZBAR_CFLAGS_OTHER})
find_library(ZBAR_LIBRARIES NAMES zbar 
             HINTS ${PC_ZBAR_LIBDIR} ${PC_ZBAR_LIBRARY_DIRS} )
find_path(ZBAR_INCLUDE_DIR Decoder.h
          HINTS ${PC_ZBAR_INCLUDEDIR} ${PC_ZBAR_INCLUDE_DIRS}
          PATH_SUFFIXES zbar )
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ZBAR  DEFAULT_MSG  ZBAR_LIBRARIES ZBAR_INCLUDE_DIR)

add_executable(vps_zbar_test vps_zbar_test.cpp)
target_link_libraries(vps_zbar_test ${ZBAR_LIBRARIES})


find_package( OpenCV )

add_executable(vps_opencv_test vps_opencv_test.cpp)
target_link_libraries(vps_opencv_test ${OpenCV_LIBS})
