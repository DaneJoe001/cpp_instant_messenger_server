cmake_minimum_required(VERSION 3.22)

project(InstantMessengerServer LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
 set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
 endif()

# 设置 CMAKE_TOOLCHAIN_FILE
if(DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
    # 设置 CMAKE_PREFIX_PATH
    set(CMAKE_PREFIX_PATH "$ENV{VCPKG_ROOT}/installed/x64-linux" CACHE STRING "Path to vcpkg installed packages")
    message( STATUS "Using Vcpkg toolchain file: ${CMAKE_TOOLCHAIN_FILE}")
else()
    message(FATAL_ERROR "Please set the VCPKG_ROOT environment variable to point to your vcpkg installation.")
endif()


# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 添加调试信息
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")

# 查找源文件和头文件
file(GLOB_RECURSE SOURCES "source/*.cpp" "include/*.hpp")

# 直接指定 SQLiteCpp 和 SQLite3 库和头文件路径
set(SQLITECPP_INCLUDE_DIR /usr/local/include)
set(SQLITECPP_LIBRARY /usr/local/lib/libSQLiteCpp.a)
set(SQLITE3_INCLUDE_DIR /usr/local/include)
set(SQLITE3_LIBRARY /usr/local/lib/libsqlite3.a)

# 查找 MySQL Connector/C++
find_package(PkgConfig REQUIRED)
pkg_check_modules(MYSQL REQUIRED mysqlcppconn)

# 查找 spdlog 包
find_package(spdlog REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

# 添加可执行文件
add_executable(instance_messenger_server ${SOURCES})

# 设置包含目录
target_include_directories(instance_messenger_server PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include  # 添加项目的 include 目录
    ${SQLITECPP_INCLUDE_DIR}  # 包含 SQLiteCpp 的头文件
    ${SQLITE3_INCLUDE_DIR}    # 包含 SQLite3 的头文件
    ${MYSQL_INCLUDE_DIRS}     # 包含 MySQL Connector/C++ 的头文件
)

# 链接库 - 调整链接顺序，被依赖的库放在后面
target_link_libraries(instance_messenger_server PRIVATE 
    ${MYSQL_LIBRARIES}        # 链接 MySQL Connector/C++ 库
    ${SQLITECPP_LIBRARY}      # 直接链接 SQLiteCpp 静态库
    ${SQLITE3_LIBRARY}        # 直接链接 SQLite3 静态库
    pthread                   # 添加 pthread 库，可能需要
    dl                        # 添加 dl 库，SQLite 可能需要
)

# 链接 spdlog 库
target_link_libraries(instance_messenger_server PRIVATE spdlog::spdlog)
target_link_libraries(instance_messenger_server PRIVATE nlohmann_json::nlohmann_json)

# 可选：设置 CMake 输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)