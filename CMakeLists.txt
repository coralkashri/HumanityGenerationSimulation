cmake_minimum_required(VERSION 3.12)
project(HumanityGenerationSimulation)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(BOOST_REQUIRED_COMPONENTS
        system
        thread
        regex
        coroutine
        context
        filesystem
        date_time
        )

find_package(Boost "1.54.0" REQUIRED ${BOOST_REQUIRED_COMPONENTS})
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

add_executable(HumanityGenerationSimulation src/main.cpp src/utilities/Design.cpp src/utilities/Design.hpp src/core/Board.cpp src/core/Board.h "src/data structures/enums.h" "src/data structures/Structs.h" "src/data structures/Data.cpp" "src/data structures/Data.h" "src/data structures/Human.cpp" "src/data structures/Human.h" "src/data structures/Event.cpp" "src/data structures/Event.h" "src/data structures/Games.cpp" "src/data structures/Games.h")