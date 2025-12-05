cmake_minimum_required(VERSION 3.20)
project(JellyFish LANGUAGES CXX)

# C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set Debug build type
set(CMAKE_BUILD_TYPE Debug)

# Prefer Homebrew-installed SDL3/SDL3_image
set(CMAKE_PREFIX_PATH
    /usr/local/opt/sdl3
    /usr/local/opt/sdl3_image
)

# Find SDL3 and SDL3_image
find_package(SDL3 REQUIRED CONFIG)
find_package(SDL3_image REQUIRED CONFIG)

# Gather all source files
file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# Create executable (MUST be before target_* options)
add_executable(JellyFish ${SOURCES})

# Copy resources to build directory
add_custom_command(TARGET JellyFish POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/res
    $<TARGET_FILE_DIR:JellyFish>/res
    COMMENT "Copying resources to build directory"
)

# Enable ASan only for Debug
if (CMAKE_BUILD_TYPE MATCHES Debug)
    message(STATUS "Using AddressSanitizer")

    target_compile_options(JellyFish PRIVATE
        -fsanitize=address
        -fno-omit-frame-pointer
    )

    target_link_options(JellyFish PRIVATE
        -fsanitize=address
    )
endif()

# Link SDL3 libraries
target_link_libraries(JellyFish
    PRIVATE SDL3::SDL3 SDL3_image::SDL3_image
)

# Include your project's headers
target_include_directories(JellyFish PRIVATE src)

target_compile_options(JellyFish PRIVATE
    -stdlib=libc++
)


#mkdir build-ninja
#cd build-ninja
#cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug ..
#cmake --build .

#cd /Users/andrewborisov/Dev/JellyFish10/build
#cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ..
#cmake --build .
