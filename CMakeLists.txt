# CMakeList.txt : CMake project for BSS, include source and define
cmake_minimum_required (VERSION 3.8)

set(CMAKE_C_STANDARD 99)


project ("BSS")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})

include_directories(
    "${CMAKE_SOURCE_DIR}"
    "${CMAKE_SOURCE_DIR}/pa"
)

link_directories(
    "${CMAKE_SOURCE_DIR}/lib"
)

set(SOURCE_FILES
    main.c
    audio.c
    algo.c
    linalg.c
    matrix.c
    generals.c
    waveform_test.c
    audio_test.c
 
    headers.h
    definitions.h
)

add_executable (app ${SOURCE_FILES})

target_link_libraries(app
    gsl
    gslcblas
    portaudio
)

add_custom_command(TARGET app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${CMAKE_SOURCE_DIR}/lib/gsl.dll"
    "${CMAKE_SOURCE_DIR}/lib/gslcblas.dll"
    "${CMAKE_SOURCE_DIR}/lib/portaudio.dll"
    $<TARGET_FILE_DIR:app>
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET app PROPERTY CXX_STANDARD 20)
endif()
