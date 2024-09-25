cmake_minimum_required(VERSION 3.13)
project(bmp-reader
    VERSION 0.0.1
    DESCRIPTION "Read bmp files and print them in console"
    LANGUAGES CXX
    )
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)

set(exename bmpreader)

set(readerlib src/BMPReader.cpp)

add_library(reader STATIC ${readerlib})

set(libs reader)
foreach(l ${libs} ${libname})
    if(MSVC)
        target_compile_options(${l} PRIVATE /W4 /WX)
    else()
        target_compile_options(${l} PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()       
endforeach()

add_executable(${exename} main.cpp)
set_property(TARGET ${exename} PROPERTY CXX_STANDARD 17)
if(MSVC)
    target_compile_options(${exename} PRIVATE /W4 /WX)
else()
    target_compile_options(${exename} PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

target_link_libraries(${exename} ${libs})

