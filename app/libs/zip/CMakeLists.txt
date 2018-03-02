set(ZIP_SCR zip.c)

add_library(zip_static STATIC ${ZIP_SCR})

set_target_properties(zip_static
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)