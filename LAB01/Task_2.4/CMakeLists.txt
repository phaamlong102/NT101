# CMakeList.txt : CMake project for bai_1.4, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (bai_1.4 "bai_1.4.cpp" "bai_1.4.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET bai_1.4 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
