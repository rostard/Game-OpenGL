cmake_minimum_required(VERSION 3.8)
project(Game-OpenGL)

set(SOURCE_FILES main.cpp glad.c font.h shader.h shader.cpp stb_image.h stb_image.cpp game.h game.cpp)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/${SOURCE_FILES} texture.cpp texture.h resource_mager.cpp resource_mager.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

target_link_libraries(${PROJECT_NAME} -L/usr/local/lib -I/usr/include/freetype2 -lfreetype -lz -lpng12 -lm -lharfbuzz -lglfw3 -lrt -ldl -lXrandr -lXinerama -lXxf86vm -lXext -lXcursor -lXrender -lXfixes -lX11 -lpthread -lxcb -lXau -lassimp -lstdc++)