# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/Adria/OneDrive/Documentos/GitHub/CAFramework/out/build/x64-Debug/_deps/imguizmo_cpp-src"
  "C:/Users/Adria/OneDrive/Documentos/GitHub/CAFramework/out/build/x64-Debug/_deps/imguizmo_cpp-build"
  "C:/Users/Adria/OneDrive/Documentos/GitHub/CAFramework/out/build/x64-Debug/_deps/imguizmo_cpp-subbuild/imguizmo_cpp-populate-prefix"
  "C:/Users/Adria/OneDrive/Documentos/GitHub/CAFramework/out/build/x64-Debug/_deps/imguizmo_cpp-subbuild/imguizmo_cpp-populate-prefix/tmp"
  "C:/Users/Adria/OneDrive/Documentos/GitHub/CAFramework/out/build/x64-Debug/_deps/imguizmo_cpp-subbuild/imguizmo_cpp-populate-prefix/src/imguizmo_cpp-populate-stamp"
  "C:/Users/Adria/OneDrive/Documentos/GitHub/CAFramework/libraries/imguizmo"
  "C:/Users/Adria/OneDrive/Documentos/GitHub/CAFramework/out/build/x64-Debug/_deps/imguizmo_cpp-subbuild/imguizmo_cpp-populate-prefix/src/imguizmo_cpp-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/Adria/OneDrive/Documentos/GitHub/CAFramework/out/build/x64-Debug/_deps/imguizmo_cpp-subbuild/imguizmo_cpp-populate-prefix/src/imguizmo_cpp-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/Adria/OneDrive/Documentos/GitHub/CAFramework/out/build/x64-Debug/_deps/imguizmo_cpp-subbuild/imguizmo_cpp-populate-prefix/src/imguizmo_cpp-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
