cmake_minimum_required(VERSION 3.12)
project(manaCalc)

set(CMAKE_CXX_STANDARD 17)


add_executable(manaCalc Mana.cpp Mana.h manaCalc.cpp)
add_executable(main main.cpp Deck.cpp Deck.h)