cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    card_engine_pp
    VERSION 0.1.0
    DESCRIPTION "Short description"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    card_engine_pp_card_engine_pp
    source/card_engine_pp.cpp
)
add_library(card_engine_pp::card_engine_pp ALIAS card_engine_pp_card_engine_pp)

include(GenerateExportHeader)
generate_export_header(
    card_engine_pp_card_engine_pp
    BASE_NAME card_engine_pp
    EXPORT_FILE_NAME export/card_engine_pp/card_engine_pp_export.hpp
    CUSTOM_CONTENT_FROM_VARIABLE pragma_suppress_c4251
)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(card_engine_pp_card_engine_pp PUBLIC CARD_ENGINE_PP_STATIC_DEFINE)
endif()

set_target_properties(
    card_engine_pp_card_engine_pp PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME card_engine_pp
    OUTPUT_NAME card_engine_pp
)

target_include_directories(
    card_engine_pp_card_engine_pp ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(
    card_engine_pp_card_engine_pp SYSTEM
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>"
)

target_compile_features(card_engine_pp_card_engine_pp PUBLIC cxx_std_20)

find_package(fmt REQUIRED)
target_link_libraries(card_engine_pp_card_engine_pp PRIVATE fmt::fmt)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT card_engine_pp_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of card_engine_pp"
  )
endif()

include(cmake/dev-mode.cmake)
