cmake_minimum_required(VERSION 3.5)
project (vps)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package( OpenCV )

add_executable(vps_opencv_test vps_opencv_test.cpp)
target_link_libraries(vps_opencv_test ${OpenCV_LIBS})

add_executable(vps_generate_markers vps_generate_markers.cpp)
target_link_libraries(vps_generate_markers ${OpenCV_LIBS})
