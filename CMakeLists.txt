cmake_minimum_required(VERSION 3.0.0)
project(quartz VERSION 0.1.0)

include(CTest)
enable_testing()

# find_package(OpenMP REQUIRED)
add_executable(quartz quartz/main.cc)
target_include_directories(quartz PUBLIC ./include)
# target_link_libraries(quartz PRIVATE OpenMP::OpenMP_CXX)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
