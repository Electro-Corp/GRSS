add_library(rendering SHARED
    source/Rendering.cpp
)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Include our directory
include_directories(include)

# Link OpenGL 
target_link_libraries(rendering OpenGL::GL OpenGL::GLU)

target_include_directories(rendering
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)