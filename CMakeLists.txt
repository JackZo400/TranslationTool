cmake_minimum_required(VERSION 3.16)
project(TranslationTool VERSION 1.0.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# 启用自动处理
qt_standard_project_setup()

# 设置源文件
set(SOURCES
    src/main.cpp
    src/MainWindow.cpp
    src/TranslationEngine.cpp
    src/FileHandler.cpp
    src/Settings.cpp
)

set(HEADERS
    src/MainWindow.h
    src/TranslationEngine.h
    src/FileHandler.h
    src/Settings.h
)

# 设置包含目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# 创建可执行文件
add_executable(TranslationTool ${SOURCES} ${HEADERS})

# 链接Qt模块
target_link_libraries(TranslationTool 
    Qt6::Core 
    Qt6::Widgets
)

# 设置Windows特定选项
if(WIN32)
    # 设置子系统为Windows
    set_target_properties(TranslationTool PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

# 设置编译属性
if(MSVC)
    target_compile_options(TranslationTool PRIVATE /W4)
else()
    target_compile_options(TranslationTool PRIVATE -Wall -Wextra)
endif()