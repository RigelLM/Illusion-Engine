# 添加项目 "Glad"
add_library(Glad STATIC
    src/glad.c
)

# 设置编程语言
set_target_properties(Glad PROPERTIES
    LANGUAGE C
)

# 指定输出目录
set_target_properties(Glad PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_DIR}/Glad"
)

# 设置目标的中间文件目录
set_target_properties(Glad PROPERTIES
    OBJECT_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin-int/${OUTPUT_DIR}/Glad"
)

# 添加包含目录
target_include_directories(Glad PUBLIC
    include
)

# Windows 特定设置
if (WIN32)
    target_compile_definitions(Glad PRIVATE
        WIN32_LEAN_AND_MEAN  # 推荐的 Windows 定义
    )
endif()

# 调整构建选项
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    target_compile_options(Glad PRIVATE
        /MTd  # Debug 模式下的静态运行时
    )
elseif (CMAKE_BUILD_TYPE MATCHES "Release")
    target_compile_options(Glad PRIVATE
        /MT  # Release 模式下的静态运行时
    )
endif()
