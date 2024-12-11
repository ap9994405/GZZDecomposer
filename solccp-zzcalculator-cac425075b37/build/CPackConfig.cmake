# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BUILD_SOURCE_DIRS "/home/porsche2/ZZ_calculator2/solccp-zzcalculator-cac425075b37;/home/porsche2/ZZ_calculator2/solccp-zzcalculator-cac425075b37/build")
set(CPACK_CMAKE_GENERATOR "Unix Makefiles")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Chien-Pin Chou")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_FILE "/usr/local/share/cmake-3.20/Templates/CPack.GenericDescription.txt")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_SUMMARY "ZZCalculator built using CMake")
set(CPACK_GENERATOR "STGZ;DEB")
set(CPACK_INSTALL_CMAKE_PROJECTS "/home/porsche2/ZZ_calculator2/solccp-zzcalculator-cac425075b37/build;ZZCalculator;ALL;/")
set(CPACK_INSTALL_PREFIX "/home/porsche2/ZZ_calculator2/solccp-zzcalculator-cac425075b37/build/build")
set(CPACK_MODULE_PATH "/home/porsche2/ZZ_calculator2/solccp-zzcalculator-cac425075b37/cmake/modules")
set(CPACK_NSIS_DISPLAY_NAME "ZZCalculator 1.0.0")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
set(CPACK_NSIS_PACKAGE_NAME "ZZCalculator 1.0.0")
set(CPACK_NSIS_UNINSTALL_NAME "Uninstall")
set(CPACK_OUTPUT_CONFIG_FILE "/home/porsche2/ZZ_calculator2/solccp-zzcalculator-cac425075b37/build/CPackConfig.cmake")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION_FILE "/usr/local/share/cmake-3.20/Templates/CPack.GenericDescription.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "ZZCalculator built using CMake")
set(CPACK_PACKAGE_FILE_NAME "ZZCalculator-1.0.0-Linux-amd64")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "ZZCalculator 1.0.0")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "ZZCalculator 1.0.0")
set(CPACK_PACKAGE_NAME "ZZCalculator")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "NCTU")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_RESOURCE_FILE_LICENSE "/home/porsche2/ZZ_calculator2/solccp-zzcalculator-cac425075b37/LICENSE")
set(CPACK_RESOURCE_FILE_README "/usr/local/share/cmake-3.20/Templates/CPack.GenericDescription.txt")
set(CPACK_RESOURCE_FILE_WELCOME "/usr/local/share/cmake-3.20/Templates/CPack.GenericWelcome.txt")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_GENERATOR "TBZ2;TGZ;TXZ;TZ")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "/home/porsche2/ZZ_calculator2/solccp-zzcalculator-cac425075b37/build/CPackSourceConfig.cmake")
set(CPACK_SOURCE_RPM "OFF")
set(CPACK_SOURCE_TBZ2 "ON")
set(CPACK_SOURCE_TGZ "ON")
set(CPACK_SOURCE_TXZ "ON")
set(CPACK_SOURCE_TZ "ON")
set(CPACK_SOURCE_ZIP "OFF")
set(CPACK_SYSTEM_NAME "Linux-amd64")
set(CPACK_THREADS "1")
set(CPACK_TOPLEVEL_TAG "Linux-amd64")
set(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "/home/porsche2/ZZ_calculator2/solccp-zzcalculator-cac425075b37/build/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()
