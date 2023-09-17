if(PROJECT_IS_TOP_LEVEL)
  set(
      CMAKE_INSTALL_INCLUDEDIR "include/card_engine_pp-${PROJECT_VERSION}"
      CACHE PATH ""
  )
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package card_engine_pp)

install(
    DIRECTORY
    include/
    "${PROJECT_BINARY_DIR}/export/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT card_engine_pp_Development
)

install(
    TARGETS card_engine_pp_card_engine_pp
    EXPORT card_engine_ppTargets
    RUNTIME #
    COMPONENT card_engine_pp_Runtime
    LIBRARY #
    COMPONENT card_engine_pp_Runtime
    NAMELINK_COMPONENT card_engine_pp_Development
    ARCHIVE #
    COMPONENT card_engine_pp_Development
    INCLUDES #
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    card_engine_pp_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${package}"
    CACHE PATH "CMake package config location relative to the install prefix"
)
mark_as_advanced(card_engine_pp_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${card_engine_pp_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT card_engine_pp_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${card_engine_pp_INSTALL_CMAKEDIR}"
    COMPONENT card_engine_pp_Development
)

install(
    EXPORT card_engine_ppTargets
    NAMESPACE card_engine_pp::
    DESTINATION "${card_engine_pp_INSTALL_CMAKEDIR}"
    COMPONENT card_engine_pp_Development
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
