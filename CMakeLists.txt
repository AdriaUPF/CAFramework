cmake_minimum_required(VERSION 3.9)

project(ComputerAnimation LANGUAGES C CXX)

# Directories
set(DIR_ROOT       ${CMAKE_CURRENT_LIST_DIR})
set(DIR_SOURCES    "${DIR_ROOT}/src")
set(DIR_LIBS       "${DIR_ROOT}/libraries")

# Init with Debug mode
if (NOT EXISTS ${CMAKE_BINARY_DIR}/CMakeCache.txt)
    if (NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "" FORCE)
    endif()
endif()

# enable FetchContent
include(FetchContent)

# download imguizmo
FetchContent_Declare(
    imguizmo_h
    URL https://raw.githubusercontent.com/CedricGuillemet/ImGuizmo/master/ImGuizmo.h
    DOWNLOAD_DIR ${DIR_LIBS}/imguizmo
    DOWNLOAD_NO_EXTRACT TRUE
)

FetchContent_Declare(
    imguizmo_cpp
    URL https://raw.githubusercontent.com/CedricGuillemet/ImGuizmo/master/ImGuizmo.cpp
    DOWNLOAD_DIR ${DIR_LIBS}/imguizmo
    DOWNLOAD_NO_EXTRACT TRUE
)

# download cgltf
FetchContent_Declare(
    cgltf_h
    URL https://raw.githubusercontent.com/jkuhlmann/cgltf/refs/heads/master/cgltf.h
    DOWNLOAD_DIR ${DIR_LIBS}/cgltf
    DOWNLOAD_NO_EXTRACT TRUE
)

# download stb_image
FetchContent_Declare(
    stb_image_h
    URL https://raw.githubusercontent.com/nothings/stb/refs/heads/master/stb_image.h
    DOWNLOAD_DIR ${DIR_LIBS}/stb
    DOWNLOAD_NO_EXTRACT TRUE
)

FetchContent_MakeAvailable(imguizmo_h imguizmo_cpp cgltf_h stb_image_h)

# Macro to map filters to folder structure for MSVC projects
macro(GroupSources curdir)
    if(MSVC)
		file(GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${curdir} ${PROJECT_SOURCE_DIR}/${curdir}/*)

        foreach(child ${children})
            if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${curdir}/${child})
                GroupSources(${curdir}/${child})
            else()
                string(REPLACE "/" "\\" groupname ${curdir})
                source_group(${groupname} FILES ${PROJECT_SOURCE_DIR}/${curdir}/${child})
            endif()
        endforeach()
    endif()
endmacro()

GroupSources(src)

# Sources
macro(CA_SOURCES_APPEND)
    file(GLOB FILES_APPEND CONFIGURE_DEPENDS ${ARGV0}/*.h)
    list(APPEND CA_HEADERS ${FILES_APPEND})
    file(GLOB FILES_APPEND CONFIGURE_DEPENDS ${ARGV0}/*.cpp)
    list(APPEND CA_SOURCES ${FILES_APPEND})
endmacro()

CA_SOURCES_APPEND(${DIR_SOURCES})
CA_SOURCES_APPEND(${DIR_SOURCES}/framework)
CA_SOURCES_APPEND(${DIR_SOURCES}/framework/math)
CA_SOURCES_APPEND(${DIR_SOURCES}/framework/graphics)
CA_SOURCES_APPEND(${DIR_SOURCES}/framework/animations)
CA_SOURCES_APPEND(${DIR_SOURCES}/framework/loaders)

CA_SOURCES_APPEND(${DIR_LIBS}/imguizmo)
CA_SOURCES_APPEND(${DIR_LIBS}/cgltf)
CA_SOURCES_APPEND(${DIR_LIBS}/stb)

add_executable(${PROJECT_NAME} ${CA_SOURCES} ${CA_HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${DIR_SOURCES})

set_property(DIRECTORY ${DIR_ROOT} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${DIR_ROOT}")

# Properties
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD_REQUIRED ON)

# Ensure that _AMD64_ or _X86_ are defined on Microsoft Windows, as otherwise
# um/winnt.h provided since Windows 10.0.22000 will error.
if(NOT UNIX)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        add_definitions(-D_AMD64_)
        message(STATUS "64 bits detected")
    elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
        add_definitions(-D_X86_)
        message(STATUS "32 bits detected")
    endif()
endif(NOT UNIX)

# glfw
add_subdirectory(libraries/glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
set_property(TARGET glfw PROPERTY FOLDER "External/GLFW3")
set_property(TARGET uninstall PROPERTY FOLDER "External/GLFW3")
set_property(TARGET update_mappings PROPERTY FOLDER "External/GLFW3")

# glew
add_subdirectory(libraries/glew-cmake)
add_definitions(-DGLEW_STATIC)
target_link_libraries(${PROJECT_NAME} PRIVATE libglew_static)
set_property(TARGET libglew_static PROPERTY FOLDER "External/libglew")
set_property(TARGET libglew_shared PROPERTY FOLDER "External/libglew")

# imgui
add_library(imgui STATIC
    ${DIR_LIBS}/imgui/imgui.cpp
    ${DIR_LIBS}/imgui/imgui_demo.cpp
    ${DIR_LIBS}/imgui/imgui_draw.cpp
    ${DIR_LIBS}/imgui/imgui_widgets.cpp
    ${DIR_LIBS}/imgui/imgui_tables.cpp
    ${DIR_LIBS}/imgui/backends/imgui_impl_glfw.cpp
    ${DIR_LIBS}/imgui/backends/imgui_impl_opengl3.cpp
    ${DIR_LIBS}/imgui/imconfig.h
    ${DIR_LIBS}/imgui/imgui.h
    ${DIR_LIBS}/imgui/imgui_internal.h
    ${DIR_LIBS}/imgui/imstb_rectpack.h
    ${DIR_LIBS}/imgui/imstb_textedit.h
    ${DIR_LIBS}/imgui/imstb_truetype.h
)
set_property(TARGET imgui PROPERTY CXX_STANDARD 20)
target_link_libraries(imgui PUBLIC glfw libglew_static)
target_include_directories(imgui PUBLIC ${DIR_LIBS}/imgui)
target_link_libraries(${PROJECT_NAME} PUBLIC imgui)
set_property(TARGET imgui PROPERTY FOLDER "External/imgui")

# imguizmo
target_include_directories(${PROJECT_NAME} PUBLIC ${DIR_LIBS}/imguizmo)

# cgltf
target_include_directories(${PROJECT_NAME} PUBLIC ${DIR_LIBS}/cgltf)

# stb
target_include_directories(${PROJECT_NAME} PUBLIC ${DIR_LIBS}/stb)

message(STATUS "dir root: ${DIR_ROOT}")
message(STATUS "bin root: ${CMAKE_BINARY_DIR}")
