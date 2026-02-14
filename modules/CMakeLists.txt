# This isn't and amazing solution
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/mint) 

add_library(mtInternalModule ./internal/mtInternalModule.c)
target_include_directories(mtInternalModule PUBLIC ${include})

add_library(io SHARED io.c)
target_include_directories(io PUBLIC ${include})
