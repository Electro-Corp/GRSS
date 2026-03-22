add_library(physics SHARED
    source/Mass.cpp
    source/Physics.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/GRSS)
include_directories(${CMAKE_SOURCE_DIR}/GRSS/physics)

target_include_directories(physics
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)