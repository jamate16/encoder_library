# This allows to link libraries to main project from current library
if(POLICY CMP0079 )
  cmake_policy(SET CMP0079 NEW)
endif()

add_library(encoder STATIC
    encoder.h
    encoder.cpp
)

# This will link all the required libraries from RP2040's SDK
# in case it has already been linked from another proprietary
# library, the guard clauses in the preprocesor directives
# will avoid duplicate code
target_link_libraries(encoder PRIVATE
    pico_stdlib
    hardware_pio # For .pio.h file
    hardware_gpio # For .pio.h file
    hardware_clocks # For .pio.h file
    )

target_include_directories(encoder PUBLIC ${CMAKE_CURRENT_LIST_DIR})


