set(TRIMANA_CORE_LIBRARY trimana_core)

set(
    TRIMANA_CORE_INCLUDE_DIR
    ${PROJECT_SOURCE_DIR}/src/core
    CACHE INTERNAL "Path to trimana core sources files"
)

set(
    TRIMANA_CORE_SOURCES_DIR
    ${PROJECT_SOURCE_DIR}/src/core/events
    ${PROJECT_SOURCE_DIR}/src/core/utils
)

set(
    TRIMANA_CORE_LIBRARY_HEADERS
    ${PROJECT_SOURCE_DIR}/src/core/events/events.hpp
    ${PROJECT_SOURCE_DIR}/src/core/events/events_window.hpp
    ${PROJECT_SOURCE_DIR}/src/core/events/events_keyboard.hpp
    ${PROJECT_SOURCE_DIR}/src/core/events/events_mouse.hpp
    ${PROJECT_SOURCE_DIR}/src/core/utils/log.hpp
    ${PROJECT_SOURCE_DIR}/src/core/utils/platform_detection.hpp
    CACHE INTERNAL "Trimana core libaray headers"
)

set(
    TRIMANA_CORE_LIBRARY_SOURCES
    ${PROJECT_SOURCE_DIR}/src/core/utils/log.cpp
)

if(NOT BUILD_SHARED_LIBS)

    add_library(
        ${TRIMANA_CORE_LIBRARY} STATIC 
        ${TRIMANA_CORE_LIBRARY_HEADERS} 
        ${TRIMANA_CORE_LIBRARY_SOURCES}
    )
    
else()

    add_compile_definitions(TRIMANA_BUILD_SHARED)
    add_library(
        ${TRIMANA_CORE_LIBRARY} SHARED 
        ${TRIMANA_CORE_LIBRARY_HEADERS}
        ${TRIMANA_CORE_LIBRARY_SOURCES}
    )

endif()

target_include_directories(
    ${TRIMANA_CORE_LIBRARY} PUBLIC 
    ${TRIMANA_CORE_SOURCES_DIR} 
)

target_link_libraries(
    ${TRIMANA_CORE_LIBRARY} PUBLIC 
    glfw
    spdlog::spdlog_header_only
    libglew_static
)

add_library(TRIMANA::CORE ALIAS ${TRIMANA_CORE_LIBRARY})

