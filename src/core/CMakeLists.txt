# Set the name of the trimana_core library
set(TRIMANA_CORE_LIBRARY trimana_core)

# Set the include directory for the trimana_core library
set(
    TRIMANA_CORE_INCLUDE_DIR
    ${PROJECT_SOURCE_DIR}/src/core # Path to trimana core source files
    CACHE INTERNAL "Path to trimana core include"
)

# Set the source directories for the trimana_core library
set(
    TRIMANA_CORE_SOURCES_DIR
    ${PROJECT_SOURCE_DIR}/src/core/events # Events source directory
    ${PROJECT_SOURCE_DIR}/src/core/utils # Utils source directory
    ${PROJECT_SOURCE_DIR}/src/core/window # Window source directory
    ${PROJECT_SOURCE_DIR}/src/core/layers # Layers source directory
    ${PROJECT_SOURCE_DIR}/src/core/inputs # Inputs source directory
)

# Set the header files for the trimana_core library
set(
    TRIMANA_CORE_LIBRARY_HEADERS
    ${PROJECT_SOURCE_DIR}/src/core/events/events.hpp # Events header file
    ${PROJECT_SOURCE_DIR}/src/core/events/events_window.hpp # Events window header file
    ${PROJECT_SOURCE_DIR}/src/core/events/events_keyboard.hpp # Events keyboard header file
    ${PROJECT_SOURCE_DIR}/src/core/events/events_mouse.hpp # Events mouse header file
    ${PROJECT_SOURCE_DIR}/src/core/events/events_receiver.hpp # Events receiver header file
    ${PROJECT_SOURCE_DIR}/src/core/utils/log.hpp # Log header file
    ${PROJECT_SOURCE_DIR}/src/core/utils/platform_detection.hpp # Platform detection header file
    ${PROJECT_SOURCE_DIR}/src/core/window/window.hpp # Window header file
    ${PROJECT_SOURCE_DIR}/src/core/layers/layer.hpp # Layer header file
    ${PROJECT_SOURCE_DIR}/src/core/layers/layer_stack.hpp # Layer stack header file
    ${PROJECT_SOURCE_DIR}/src/core/layers/imgui_layer.hpp # ImGui layer header file
    ${PROJECT_SOURCE_DIR}/src/core/inputs/input.hpp # Input header file
    ${PROJECT_SOURCE_DIR}/src/core/utils/time_steps.hpp # Time steps header file

    CACHE INTERNAL "Trimana core library headers"
)

# Set the source files for the trimana_core library
set(
    TRIMANA_CORE_LIBRARY_SOURCES
    ${PROJECT_SOURCE_DIR}/src/core/utils/log.cpp # Log source file
    ${PROJECT_SOURCE_DIR}/src/core/events/events_receiver.cpp # Events receiver source file
    ${PROJECT_SOURCE_DIR}/src/core/window/window.cpp # Window source file
    ${PROJECT_SOURCE_DIR}/src/core/layers/layer_stack.cpp # Layer stack source file
    ${PROJECT_SOURCE_DIR}/src/core/layers/imgui_layer.cpp # ImGui layer source file
    ${PROJECT_SOURCE_DIR}/src/core/inputs/input.cpp # Input source file
)

# If BUILD_SHARED_LIBS is not set, create a static library
if(NOT BUILD_SHARED_LIBS)
    add_compile_definitions(TRIMANA_BUILD_STATIC) # Define the TRIMANA_BUILD_STATIC macro
    add_library(
        ${TRIMANA_CORE_LIBRARY} STATIC # Create a static library named trimana_core
        ${TRIMANA_CORE_LIBRARY_HEADERS} # Headers for the library
        ${TRIMANA_CORE_LIBRARY_SOURCES} # Sources for the library
        ${IMGUI_HEADERS} # Headers for the ImGui library
        ${STB_IMAGE_HEADER} # Header for the STB image library      
    )

# If BUILD_SHARED_LIBS is set, create a shared library
else()
    
    add_compile_definitions(TRIMANA_BUILD_SHARED) # Define the TRIMANA_BUILD_SHARED macro
    add_library(
        ${TRIMANA_CORE_LIBRARY} SHARED # Create a shared library named trimana_core
        ${TRIMANA_CORE_LIBRARY_HEADERS} # Headers for the library
        ${TRIMANA_CORE_LIBRARY_SOURCES} # Sources for the library
        ${IMGUI_HEADERS} # Headers for the ImGui library
        ${STB_IMAGE_HEADER} # Header for the STB image library
    )

    # Custom target to copy GLEW runtimes into the build directory
    add_custom_target(
        GLEW_COPY_RUNTIMES ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/build/vendors/glew-cmake/bin/${CMAKE_BUILD_TYPE}/
        ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
        COMMENT "Copying glew runtimes into build directory"
    )
    add_dependencies(${TRIMANA_CORE_LIBRARY} GLEW_COPY_RUNTIMES) # Add the GLEW_COPY_RUNTIMES target as a dependency

endif()

# Set the public include directories for the trimana_core library
target_include_directories(
    ${TRIMANA_CORE_LIBRARY} PUBLIC
    ${TRIMANA_CORE_SOURCES_DIR} # Include directories for the library sources

    # The following variables are used to specify the directories for ImGui and its backends.
    # - IMGUI_DIR: The directory for the ImGui library.
    # - IMGUI_BACKENDS_DIR: The directory for the ImGui backends.
    ${IMGUI_DIR}
    ${IMGUI_BACKENDS_DIR}    
    ${STB_IMAGE_SOURCE_DIR} # The directory for the STB image library
)

if(NOT BUILD_SHARED_LIBS)
    target_link_libraries(
        ${TRIMANA_CORE_LIBRARY} PUBLIC
        glfw # Link glfw library
        spdlog::spdlog # Link spdlog library
        libglew_static # Link glew library
        ImGui::ImGui # Link imgui library
        glm::glm # Link glm library
        gapi::header_only # Link gapi header only library
    )   
else()
    target_link_libraries(
        ${TRIMANA_CORE_LIBRARY} PUBLIC
        glfw # Link glfw library
        spdlog::spdlog # Link spdlog library
        libglew_shared # Link glew library
        ImGui::ImGui # Link imgui library
        glm::glm # Link glm library
        gapi::header_only # Link gapi header only library
    )
endif()

# Create an alias for the trimana_core library
add_library(TRIMANA::CORE ALIAS ${TRIMANA_CORE_LIBRARY})
