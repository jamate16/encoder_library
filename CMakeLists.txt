add_library(encoder STATIC
    quadrature_encoder.pio.h
    encoder.h
    encoder.cpp
)

# pico_generate_pio_header(encoder ${CMAKE_CURRENT_LIST_DIR}/quadrature_encoder.pio)

# This will link all the required libraries from RP2040's SDK
# in case it has already been linked from another proprietary
# library, the guard clauses in the preprocesor directives
# will avoid duplicate code
target_link_libraries(encoder PUBLIC
    pico_stdlib
    hardware_pio # For .pio.h file
    hardware_gpio # For .pio.h file
    hardware_clocks # For .pio.h file
)

target_include_directories(encoder PUBLIC ${CMAKE_CURRENT_LIST_DIR})


