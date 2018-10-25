cmake_minimum_required(VERSION 3.12)
project(manaCalc)

set(CMAKE_CXX_STANDARD 17)

add_executable(manaCalc main.cpp Deck.cpp Deck.h Mana.cpp Mana.h)