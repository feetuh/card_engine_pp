cmake_minimum_required(VERSION 3.14)

project(card_engine_ppTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

# ---- Dependencies ----

if(PROJECT_IS_TOP_LEVEL)
  find_package(card_engine_pp REQUIRED)
  enable_testing()
endif()

find_package(Catch2 REQUIRED)
include(Catch)

# ---- Tests ----

add_executable(card_engine_pp_test source/card_engine_pp_test.cpp)
target_link_libraries(
    card_engine_pp_test PRIVATE
    card_engine_pp::card_engine_pp
    Catch2::Catch2WithMain
)
target_compile_features(card_engine_pp_test PRIVATE cxx_std_20)

add_executable(card_test source/card_test.cpp)
target_link_libraries(
    card_test PRIVATE
    card_engine_pp::card_engine_pp
    Catch2::Catch2WithMain
)
target_compile_features(card_test PRIVATE cxx_std_20)

catch_discover_tests(card_engine_pp_test)
catch_discover_tests(card_test)

# ---- End-of-file commands ----

add_folders(Test)
