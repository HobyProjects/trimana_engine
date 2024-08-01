set(TRIMANA_APP trimana)

set(
    TRIMANA_APP_SOURCES_DIR
    ${PROJECT_SOURCE_DIR}/src/app/app
    ${PROJECT_SOURCE_DIR}/src/app/entrypoint
)

set(
    TRIMANA_APP_HEADERS
    ${PROJECT_SOURCE_DIR}/src/app/app/application.hpp
    ${PROJECT_SOURCE_DIR}/src/app/app/example_layer.hpp
)

set(
    TRIMANA_APP_SOURCES
    ${PROJECT_SOURCE_DIR}/src/app/app/application.cpp
    ${PROJECT_SOURCE_DIR}/src/app/app/example_layer.cpp
    ${PROJECT_SOURCE_DIR}/src/app/entrypoint/trimana.cpp
)

add_executable(${TRIMANA_APP} ${TRIMANA_APP_SOURCES} ${TRIMANA_APP_HEADERS})

add_custom_target(
    TRIMANA_RESOURCES ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/res
    ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}
    COMMENT "Copying resources into build directory"
)
add_dependencies(${TRIMANA_APP} TRIMANA_RESOURCES)

target_include_directories(${TRIMANA_APP} PRIVATE ${TRIMANA_APP_SOURCES_DIR} ${TRIMANA_CORE_INCLUDE_DIR})
target_link_libraries(
    ${TRIMANA_APP} PRIVATE 
    libglew_shared # Link glew library 
    TRIMANA::CORE # Link trimana core library
)