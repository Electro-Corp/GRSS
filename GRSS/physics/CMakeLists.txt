add_library(physics SHARED
    source/Mass.cpp
    source/Physics.cpp
)

target_include_directories(physics
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)