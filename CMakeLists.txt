cmake_minimum_required(VERSION 3.10)
project(game LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Encontra Allegro 5 e addons
find_package(PkgConfig REQUIRED)

pkg_check_modules(ALLEGRO5 REQUIRED allegro-5)
pkg_check_modules(ALLEGRO5_PRIMITIVES REQUIRED allegro_primitives-5)
pkg_check_modules(ALLEGRO5_IMAGE REQUIRED allegro_image-5)
pkg_check_modules(ALLEGRO5_FONT REQUIRED allegro_font-5)
pkg_check_modules(ALLEGRO5_TTF REQUIRED allegro_ttf-5)
pkg_check_modules(ALLEGRO5_AUDIO REQUIRED allegro_audio-5)
pkg_check_modules(ALLEGRO5_ACODEC REQUIRED allegro_acodec-5)

add_executable(game
    src/main.cpp

    src/core/algame.cpp
    src/core/graphics.cpp
    src/core/texture.cpp
    src/core/vector2.cpp
    src/core/key.cpp
    src/core/input.cpp
    src/core/joystick.cpp
    src/core/texturemanager.cpp

    src/game.cpp

    src/game/gameobject.cpp
    src/game/player.cpp
    src/game/gui.cpp
    src/game/tilemap.cpp
    src/game/level.cpp
    src/game/camera.cpp
    src/game/maploader.cpp
)

target_include_directories(game PRIVATE
    ${ALLEGRO5_INCLUDE_DIRS}
)

target_link_libraries(game
    ${ALLEGRO5_LIBRARIES}
    ${ALLEGRO5_PRIMITIVES_LIBRARIES}
    ${ALLEGRO5_IMAGE_LIBRARIES}
    ${ALLEGRO5_FONT_LIBRARIES}
    ${ALLEGRO5_TTF_LIBRARIES}
    ${ALLEGRO5_AUDIO_LIBRARIES}
    ${ALLEGRO5_ACODEC_LIBRARIES}
)

target_compile_options(game PRIVATE
    ${ALLEGRO5_CFLAGS_OTHER}
)
