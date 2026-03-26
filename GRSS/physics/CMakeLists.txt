add_library(physics SHARED
    source/Mass.cpp
    source/Physics.cpp
)

find_package(OpenCL REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/GRSS)
include_directories(${CMAKE_SOURCE_DIR}/GRSS/physics)

target_include_directories(physics
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(physics
    OpenCL::OpenCL
)