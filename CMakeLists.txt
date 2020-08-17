cmake_minimum_required(VERSION 3.17)
project(cookie_game)

set(CMAKE_CXX_STANDARD 20)

add_executable(cookie_game main.cpp attracting_element.h attracting_element.cpp player.h player.cpp)

include_directories( allegro5/include )
link_directories( allegro5/lib )
TARGET_LINK_LIBRARIES(cookie_game allegro_acodec
        allegro_audio
        allegro_color
        allegro_dialog
        allegro_image
        allegro_main
        allegro_memfile
        allegro_physfs
        allegro_primitives
        allegro_ttf
        allegro_font
        allegro)