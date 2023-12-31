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

add_executable(board_test source/board_test.cpp)
target_link_libraries(
    board_test PRIVATE
    card_engine_pp::card_engine_pp
    Catch2::Catch2WithMain
)
target_compile_features(board_test PRIVATE cxx_std_20)

add_executable(operation_test source/operation_test.cpp)
target_link_libraries(
    operation_test PRIVATE
    card_engine_pp::card_engine_pp
    Catch2::Catch2WithMain
)
target_compile_features(operation_test PRIVATE cxx_std_20)

add_executable(constraint_test source/constraint_test.cpp)
target_link_libraries(
    constraint_test PRIVATE
    card_engine_pp::card_engine_pp
    Catch2::Catch2WithMain
)
target_compile_features(constraint_test PRIVATE cxx_std_20)

catch_discover_tests(card_engine_pp_test)
catch_discover_tests(card_test)
catch_discover_tests(board_test)
catch_discover_tests(operation_test)
catch_discover_tests(constraint_test)

# ---- End-of-file commands ----

add_folders(Test)
