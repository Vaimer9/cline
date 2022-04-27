cmake_minimum_required(VERSION 3.10)

# set the project name
project(main)

# add the executable
add_executable(${PROJECT_NAME} main.c cline.c)

target_link_libraries(main ncurses)
