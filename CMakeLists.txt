cmake_minimum_required(VERSION 3.16)
project(GRSS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Add subdirectories for libraries
add_subdirectory(GRSS/physics)
add_subdirectory(GRSS/rendering)

# UI
find_package(wxWidgets CONFIG REQUIRED core gl)
if(wxWidgets_USE_FILE)
    include(${wxWidgets_USE_FILE})
endif()

include_directories(GRSS)

# Main executable
add_executable(GRSS
    GRSS/common/Universe.cpp
    GRSS/interface/FrameMain.cpp
    GRSS/interface/EnvironmentPage.cpp
    GRSS/interface/TopPanel.cpp
    GRSS/interface/OpenGLPanel.cpp
    GRSS/interface/main.cpp
)

# Link libraries to executable
target_link_libraries(GRSS
    PRIVATE
        physics
        rendering

    ${wxWidgets_LIBRARIES}
)

# Copy assets to build
file(GLOB assets ${CMAKE_SOURCE_DIR}/GRSS/assets/*)
foreach(in_file IN LISTS assets)
    get_filename_component(out_file ${in_file} NAME)
    file(COPY_FILE ${in_file} ${CMAKE_BINARY_DIR}/assets/${out_file})
endforeach()