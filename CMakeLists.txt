cmake_minimum_required(VERSION 3.20)
project(bmp-reader
    VERSION 1.0.0
    DESCRIPTION "Read bmp files and print them in console"
    LANGUAGES CXX
    )
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)

set(exename bmpreader)

set(readerlib src/BMPReader.cpp)
set(structslib src/Structs.cpp)

add_library(reader STATIC ${readerlib})
add_library(structs STATIC ${structslib})

set(libs reader structs)

add_executable(${exename} main.cpp)
target_link_libraries(${exename} ${libs})

foreach(t ${libs} ${exename})
    if(MSVC)
        target_compile_options(${t} PRIVATE /W4 /WX)
    else()
        target_compile_options(${t} PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()       
    set_property(TARGET ${t} PROPERTY CXX_STANDARD 20)
endforeach()

