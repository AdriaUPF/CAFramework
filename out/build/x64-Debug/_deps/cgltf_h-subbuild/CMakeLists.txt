# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.27.2-msvc1)

# Reject any attempt to use a toolchain file. We must not use one because
# we could be downloading it here. If the CMAKE_TOOLCHAIN_FILE environment
# variable is set, the cache variable will have been initialized from it.
unset(CMAKE_TOOLCHAIN_FILE CACHE)
unset(ENV{CMAKE_TOOLCHAIN_FILE})

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(cgltf_h-populate NONE)



include(ExternalProject)
ExternalProject_Add(cgltf_h-populate
                     "UPDATE_DISCONNECTED" "False" "EXTERNALPROJECT_INTERNAL_ARGUMENT_SEPARATOR" "URL" "https://raw.githubusercontent.com/jkuhlmann/cgltf/refs/heads/master/cgltf.h" "DOWNLOAD_DIR" "C:/Users/Adria/OneDrive/Documentos/GitHub/CAFramework/libraries/cgltf" DOWNLOAD_NO_EXTRACT YES
                    SOURCE_DIR          "C:/Users/Adria/OneDrive/Documentos/GitHub/CAFramework/out/build/x64-Debug/_deps/cgltf_h-src"
                    BINARY_DIR          "C:/Users/Adria/OneDrive/Documentos/GitHub/CAFramework/out/build/x64-Debug/_deps/cgltf_h-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
                    USES_TERMINAL_PATCH     YES
)


ExternalProject_Get_Property(cgltf_h-populate DOWNLOADED_FILE)
get_filename_component(dlFileName "${DOWNLOADED_FILE}" NAME)

ExternalProject_Add_Step(cgltf_h-populate copyfile
  COMMAND    "C:/Program Files/Microsoft Visual Studio/2022/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe" -E copy_if_different
             "<DOWNLOADED_FILE>" "C:/Users/Adria/OneDrive/Documentos/GitHub/CAFramework/out/build/x64-Debug/_deps/cgltf_h-src"
  DEPENDEES  patch
  DEPENDERS  configure
  BYPRODUCTS "C:/Users/Adria/OneDrive/Documentos/GitHub/CAFramework/out/build/x64-Debug/_deps/cgltf_h-src/${dlFileName}"
  COMMENT    "Copying file to SOURCE_DIR"
)

