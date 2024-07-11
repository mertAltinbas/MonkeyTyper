cmake_minimum_required(VERSION 3.28)
project(MonkeyTyper)

set(CMAKE_CXX_STANDARD 20)

# Disable shared libraries
set(BUILD_SHARED_LIBS FALSE)

include(FetchContent)

# Fetch SFML and fmt
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1
)
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 10.2.1
)

FetchContent_MakeAvailable(SFML fmt)

# Add executable and link libraries
add_executable(MonkeyTyper
        main.cpp
        Game.cpp
        Word.cpp
)

target_link_libraries(MonkeyTyper
        sfml-graphics
        sfml-window
        sfml-system
        fmt
)

# Include directories for header files
target_include_directories(MonkeyTyper PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/ai
        ${sfml_SOURCE_DIR}/include
        ${fmt_SOURCE_DIR}/include
)

