cmake_minimum_required(VERSION 3.20)

project(MusicLibraryAnalysis)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES
    "cpp/*.cpp"
)

find_package(SDL3 REQUIRED CONFIG)
find_package(SDL3_image REQUIRED CONFIG)
find_package(SDL3_ttf REQUIRED CONFIG)

add_executable(MusicLibraryAnalysis ${SOURCES})

target_link_libraries(MusicLibraryAnalysis PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_ttf::SDL3_ttf
)