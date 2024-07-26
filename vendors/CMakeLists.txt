# glfw Configuration
add_subdirectory("glfw" EXCLUDE_FROM_ALL)

# spdlog Configuration
add_subdirectory("spdlog" EXCLUDE_FROM_ALL)

# # glm lib Configuration
# set(GLM_BUILD_TESTS OFF)
# add_subdirectory("glm" EXCLUDE_FROM_ALL)

#glew lib Configuration
if(NOT BUILD_SHARED_LIBS)
    set(glew-cmake_BUILD_SHARED OFF)
    set(glew-cmake_BUILD_STATIC ON)
else()
    set(glew-cmake_BUILD_SHARED ON)
    set(glew-cmake_BUILD_STATIC OFF)
endif()

set(ONLY_LIBS ON)
add_subdirectory("glew-cmake" EXCLUDE_FROM_ALL)


# # assimp lib configuration
# add_subdirectory("assimp" EXCLUDE_FROM_ALL)

# # Importing STB image lib configure
# set(STB_IMAGE_SOURCE_DIR ${PROJECT_SOURCE_DIR}/Vendor/stb CACHE PATH "Path to stb image library")
# set(STB_IMAGE_HEADER ${PROJECT_SOURCE_DIR}/Vendor/stb/stb_image.h CACHE INTERNAL "Path to stb_image header")

# #imgui configure
set(IMGUI_LIBRARY imgui CACHE INTERNAL "Imgui library name")
set(IMGUI_DIR ${PROJECT_SOURCE_DIR}/vendors/imgui CACHE PATH "Path to imgui library directory")
set(IMGUI_BACKENDS_DIR ${PROJECT_SOURCE_DIR}/vendors/imgui/backends CACHE PATH "Path to imgui library backends directory")

set(
    IMGUI_HEADERS
    ${IMGUI_DIR}/imconfig.h 
    ${IMGUI_DIR}/imgui_internal.h
    ${IMGUI_DIR}/imgui.h
    ${IMGUI_DIR}/imstb_rectpack.h
    ${IMGUI_DIR}/imstb_textedit.h 
    ${IMGUI_DIR}/imstb_truetype.h
    ${IMGUI_BACKENDS_DIR}/imgui_impl_glfw.h 
    ${IMGUI_BACKENDS_DIR}/imgui_impl_opengl3.h 
    CACHE INTERNAL "Imgui library headers"
)

set(
    IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp 
    ${IMGUI_DIR}/imgui_draw.cpp 
    ${IMGUI_DIR}/imgui_widgets.cpp 
    ${IMGUI_DIR}/imgui_tables.cpp 
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_BACKENDS_DIR}/imgui_impl_glfw.cpp
    ${IMGUI_BACKENDS_DIR}/imgui_impl_opengl3.cpp
    CACHE INTERNAL "Imgui library sources"
)

# Check if BUILD_SHARED_LIBS is enabled
if(BUILD_SHARED_LIBS)
    message(STATUS "Building shared imgui library is not supported")
endif()

# Add the imgui library as a static library
add_library(
    ${IMGUI_LIBRARY} STATIC EXCLUDE_FROM_ALL
    ${IMGUI_HEADERS} # Headers for the library
    ${IMGUI_SOURCES} # Sources for the library
)

target_include_directories(${IMGUI_LIBRARY} PUBLIC ${IMGUI_DIR} ${IMGUI_BACKENDS_DIR})
target_link_libraries(${IMGUI_LIBRARY} PRIVATE glfw)
add_library(ImGui::ImGui ALIAS ${IMGUI_LIBRARY})

# # enTT library configuration
# set(ENTT_BUILD_TESTING OFF)
# add_subdirectory("entt" EXCLUDE_FROM_ALL)