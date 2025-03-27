# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/Adria/OneDrive/Documentos/GitHub/CAFramework/out/build/x64-Debug/_deps/cgltf_h-src"
  "C:/Users/Adria/OneDrive/Documentos/GitHub/CAFramework/out/build/x64-Debug/_deps/cgltf_h-build"
  "C:/Users/Adria/OneDrive/Documentos/GitHub/CAFramework/out/build/x64-Debug/_deps/cgltf_h-subbuild/cgltf_h-populate-prefix"
  "C:/Users/Adria/OneDrive/Documentos/GitHub/CAFramework/out/build/x64-Debug/_deps/cgltf_h-subbuild/cgltf_h-populate-prefix/tmp"
  "C:/Users/Adria/OneDrive/Documentos/GitHub/CAFramework/out/build/x64-Debug/_deps/cgltf_h-subbuild/cgltf_h-populate-prefix/src/cgltf_h-populate-stamp"
  "C:/Users/Adria/OneDrive/Documentos/GitHub/CAFramework/libraries/cgltf"
  "C:/Users/Adria/OneDrive/Documentos/GitHub/CAFramework/out/build/x64-Debug/_deps/cgltf_h-subbuild/cgltf_h-populate-prefix/src/cgltf_h-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/Adria/OneDrive/Documentos/GitHub/CAFramework/out/build/x64-Debug/_deps/cgltf_h-subbuild/cgltf_h-populate-prefix/src/cgltf_h-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/Adria/OneDrive/Documentos/GitHub/CAFramework/out/build/x64-Debug/_deps/cgltf_h-subbuild/cgltf_h-populate-prefix/src/cgltf_h-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
