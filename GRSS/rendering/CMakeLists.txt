add_library(rendering SHARED
    source/Object.cpp
    source/Rendering.cpp
)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Include our directory
include_directories(include)

# Include physics
include_directories(${CMAKE_SOURCE_DIR}/GRSS/physics/include)

# Link OpenGL 
target_link_libraries(rendering OpenGL::GL OpenGL::GLU)

target_include_directories(rendering
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)