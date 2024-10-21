cmake_minimum_required(VERSION 3.10)
project(Project)

# 设置项目架构
set(CMAKE_GENERATOR_PLATFORM x64)

# 配置输出目录
set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/${CMAKE_SYSTEM_NAME}-${CMAKE_GENERATOR_PLATFORM}")

# 设置构建配置
set(CMAKE_CONFIGURATION_TYPES Debug Release Dist CACHE STRING "")

# 包含目录
set(IncludeDir_glfw "Illusion/Lib/glfw/include")
set(IncludeDir_Glad "Illusion/Lib/Glad/include")
set(IncludeDir_ImGui "Illusion/Lib/imgui")
set(IncludeDir_glm "Illusion/Lib/glm")
set(IncludeDir_stb_image "Illusion/Lib/stb_image")
set(IncludeDir_EnTT "Illusion/Lib/EnTT/include")
set(IncludeDir_Json "Illusion/Lib/nlohmann/include")

# 添加子目录
add_subdirectory(Illusion/Lib/glfw)
add_subdirectory(Illusion/Lib/Glad)
add_subdirectory(Illusion/Lib/imgui)

file(GLOB_RECURSE ILLUSION_SOURCES "Illusion/src/*.cpp")
file(GLOB_RECURSE ILLUSION_HEADERS "Illusion/src/*.h")
file(GLOB_RECURSE STB_SOURCES "Illusion/Lib/stb_image/*.cpp")
file(GLOB_RECURSE STB_HEADERS "Illusion/Lib/stb_image/*.h")
file(GLOB_RECURSE GLM_INLINES "Illusion/Lib/glm/glm/*.inl")
file(GLOB_RECURSE GLM_HEADERS "Illusion/Lib/glm/glm/*.hpp")

# 项目 "Illusion"
add_library(Illusion STATIC
    ${ILLUSION_SOURCES}
    ${ILLUSION_HEADERS}
    ${STB_SOURCES}
    ${STB_HEADERS}
    ${GLM_INLINES}
    ${GLM_HEADERS}
)

target_precompile_headers(Illusion PRIVATE illusion/src/pch.h)

# 设置编译选项
target_compile_features(Illusion PRIVATE cxx_std_17)

# 指定输出目录
set_target_properties(Illusion PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_DIR}/Illusion")

# 设置包含目录
target_include_directories(Illusion PRIVATE
    Illusion/src
    Illusion/Lib/spdlog/include
    ${IncludeDir_glfw}
    ${IncludeDir_Glad}
    ${IncludeDir_ImGui}
    ${IncludeDir_glm}
    ${IncludeDir_stb_image}
    ${IncludeDir_EnTT}
    ${IncludeDir_Json}
)

# 定义宏
target_compile_definitions(Illusion PRIVATE
    _CRT_SECURE_NO_WARNINGS
)

# 链接库
target_link_libraries(Illusion PRIVATE glfw Glad ImGui opengl32)

# Windows 系统特定设置
if (WIN32)
    target_compile_definitions(Illusion PRIVATE
        ILLUSION_PLATFORM_WINDOWS
        GLFW_INCLUDE_NONE
    )
endif()

# 调整构建选项
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    target_compile_definitions(Illusion PRIVATE ILLUSION_DEBUG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}/Illusion")
elseif (CMAKE_BUILD_TYPE MATCHES "Release")
    target_compile_definitions(Illusion PRIVATE ILLUSION_RELEASE)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}/Illusion")
elseif (CMAKE_BUILD_TYPE MATCHES "Dist")
    target_compile_definitions(Illusion PRIVATE ILLUSION_DIST)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DIST "${OUTPUT_DIR}/Illusion")
endif()

file(GLOB_RECURSE GAME_SOURCES "Game/src/*.cpp")
file(GLOB_RECURSE GAME_HEADERS "Game/src/*.h")

# 项目 "Game"
add_executable(Game
    ${GAME_SOURCES}
    ${GAME_HEADERS}
)

# 配置vs的本地windows调试器的工作目录
set_target_properties(Game PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Game"
)

# 设置编译选项
target_compile_features(Game PRIVATE cxx_std_17)

# 设置包含目录
target_include_directories(Game PRIVATE
    Illusion/Lib/spdlog/include
    Illusion/src
    Illusion/Lib
    ${IncludeDir_glm}
    ${IncludeDir_glfw}
    ${IncludeDir_EnTT}
)

# 链接库
target_link_libraries(Game PRIVATE Illusion)

# Windows 系统特定设置
if (WIN32)
    target_compile_definitions(Game PRIVATE ILLUSION_PLATFORM_WINDOWS)
endif()

# 调整构建选项
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    target_compile_definitions(Game PRIVATE ILLUSION_DEBUG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}/Game")
elseif (CMAKE_BUILD_TYPE MATCHES "Release")
    target_compile_definitions(Game PRIVATE ILLUSION_RELEASE)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}/Game")
elseif (CMAKE_BUILD_TYPE MATCHES "Dist")
    target_compile_definitions(Game PRIVATE ILLUSION_DIST)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DIST "${OUTPUT_DIR}/Game")
endif()

file(GLOB_RECURSE EDITOR_SOURCES "Editor/src/*.cpp")
file(GLOB_RECURSE EDITOR_HEADERS "Editor/src/*.h")

# 项目 "Editor"
add_executable(Editor
    ${EDITOR_SOURCES}
    ${EDITOR_HEADERS}
)

# 配置vs的本地windows调试器的工作目录
set_target_properties(Editor PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Editor"
)

# 设置编译选项
target_compile_features(Editor PRIVATE cxx_std_17)

# 设置包含目录
target_include_directories(Editor PRIVATE
    Illusion/Lib/spdlog/include
    Illusion/src
    Illusion/Lib
    ${IncludeDir_glm}
    ${IncludeDir_glfw}
    ${IncludeDir_EnTT}
)

# 链接库
target_link_libraries(Editor PRIVATE Illusion)

# Windows 系统特定设置
if (WIN32)
    target_compile_definitions(Editor PRIVATE ILLUSION_PLATFORM_WINDOWS)
endif()

# 调整构建选项
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    target_compile_definitions(Editor PRIVATE ILLUSION_DEBUG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}/Editor")
elseif (CMAKE_BUILD_TYPE MATCHES "Release")
    target_compile_definitions(Editor PRIVATE ILLUSION_RELEASE)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}/Editor")
elseif (CMAKE_BUILD_TYPE MATCHES "Dist")
    target_compile_definitions(Editor PRIVATE ILLUSION_DIST)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DIST "${OUTPUT_DIR}/Editor")
endif()
