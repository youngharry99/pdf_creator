cmake_minimum_required(VERSION 3.10)
project(pdf_creator)

add_executable(${PROJECT_NAME} main.cpp)

# target_include_directories(/usr/local/include/)

target_link_libraries(${PROJECT_NAME} PUBLIC hpdf)
target_link_libraries(${PROJECT_NAME} PUBLIC m)
