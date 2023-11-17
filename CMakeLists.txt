cmake_minimum_required(VERSION 3.26)
project(AutoSens)

set(CMAKE_CXX_STANDARD 14)

add_executable(AutoSens

        main.cpp
        interface/ui.cpp
        interface/ui.h

        games/games.cpp
        games/CounterStrike2/CounterStrike2.cpp
        games/ApexLegends/ApexLegends.cpp
        games/Minecraft/Minecraft.cpp

        games/games.h
        games/CounterStrike2/CounterStrike2.h
        games/ApexLegends/ApexLegends.h
        games/Minecraft/Minecraft.h
)
