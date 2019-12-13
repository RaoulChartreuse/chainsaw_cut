cmake_minimum_required(VERSION 2.8)
project(chainsow_cut)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenCV  REQUIRED)

find_package( Boost COMPONENTS system  filesystem program_options REQUIRED )

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

include_directories(${PROJECT_SOURCE_DIR})



add_executable(build/chainsaw main.cpp BoucleTraitement.cpp
        Traitement.cpp Display.cpp CorrelationProvider.cpp
        CorrelationProvider.h ComputeCorrelationProvider.cpp
        ComputeCorrelationProvider.h GraphTraitement.cpp
        GraphTraitement.h WriteCorrelationTraitement.cpp
        WriteCorrelationTraitement.h readCorrelationProvider.cpp
        readCorrelationProvider.h cutTraitement.cpp
        cutTraitement.h mosaicTraitement.cpp mosaicTraitement.h
        check_dir.cpp)
target_link_libraries( build/chainsaw
        ${OpenCV_LIBS} ${Boost_LIBRARIES} )


