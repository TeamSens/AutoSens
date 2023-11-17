cmake_minimum_required(VERSION 3.26)
project(AutoSens)

set(CMAKE_CXX_STANDARD 14)

add_executable(AutoSens

        interface/ui.cpp
        main.cpp
        games/games.cpp
        games/CounterStrike2/CounterStrike2.cpp
        games/ApexLegends/ApexLegends.cpp)
