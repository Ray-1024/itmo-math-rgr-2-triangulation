cmake_minimum_required(VERSION 3.22)
project(ear-triangulation)

set(CMAKE_CXX_STANDARD 17)
set(SFML_STATIC TRUE)
set(SFML_DIR "PATH")
find_package(SFML 2.5.1 COMPONENTS system graphics REQUIRED)

add_executable(ear-triangulation "main.cpp" "src/Application.cpp" "src/Application.h" "src/Polygon/Polygon.cpp" "src/Polygon/Polygon.h" "src/Utils/Utils.h" "src/Polygon/Vertex/Vert.cpp" "src/Polygon/Vertex/Vert.h")
target_link_libraries(ear-triangulation sfml-graphics sfml-system)
