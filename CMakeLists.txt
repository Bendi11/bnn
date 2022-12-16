cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
    bnn
    LANGUAGES CXX
)

find_package(Eigen3 3.4 REQUIRED NO_MODULE)

set(
    SRC
    "src/main.cpp"
    "src/layer.cpp"
)

add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(${PROJECT_NAME} Eigen3::Eigen)
