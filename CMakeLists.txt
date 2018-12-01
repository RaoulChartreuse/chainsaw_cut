cmake_minimum_required(VERSION 2.8)
project(chainsow_cut)
include_directories(/home/laurent/media/opencv/inc)
link_directories(/home/laurent/media/opencv/lib)

find_package(OpenCV 4.0 REQUIRED)

find_package( Boost COMPONENTS system  filesystem REQUIRED )

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_executable(analyser analyser.cpp)
target_link_libraries( analyser ${OpenCV_LIBS}  )

add_executable(graph graph.cpp)
target_link_libraries( graph ${OpenCV_LIBS}  )

add_executable(cut_file cut.cpp) 
target_link_libraries( cut_file ${OpenCV_LIBS} ${Boost_FILESYSTEM_LIBRARY}  ${Boost_SYSTEM_LIBRARY})
