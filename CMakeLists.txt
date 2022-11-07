cmake_minimum_required(VERSION 3.23.0)

project(2DPlaneShooter)

set(DEPS_DIR ${CMAKE_SOURCE_DIR}/build/external)

add_subdirectory(external/SDL)

add_subdirectory(external/SDL_image)

add_subdirectory(external/SDL_ttf)

add_subdirectory(external/SDL_mixer)


file(GLOB SOURCE_FILES src/*.cpp)
file(GLOB HEADER_FILES include/*.h)
  
add_executable(2DPlaneShooter ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(2DPlaneShooter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/
                                            ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL/include/
                                            ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL_image/
                                            ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL_ttf/
                                            ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL_mixer/include/)

target_link_libraries(2DPlaneShooter SDL2 SDL2main SDL2_image SDL2_ttf SDL2_mixer)

add_custom_command(TARGET 2DPlaneShooter POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "${DEPS_DIR}/SDL/Debug/SDL2d.dll"
                    "${DEPS_DIR}/SDL_image/Debug/SDL2_imaged.dll"
                    "${DEPS_DIR}/SDL_ttf/Debug/SDL2_ttfd.dll"
                    "${DEPS_DIR}/SDL_mixer/Debug/SDL2_mixerd.dll"
                    $<TARGET_FILE_DIR:2DPlaneShooter>)

add_custom_command(TARGET 2DPlaneShooter POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:2DPlaneShooter>/res)