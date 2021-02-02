cmake_minimum_required(VERSION 3.7)

project(lvgl_sim)
set(CMAKE_EXPORT_COMPLIE_COMMANDS ON)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_compile_options(-std=c99)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

# include_directories(ui/simulator/inc)
include_directories(.)
include_directories(lvgl)

add_definitions(
    -DSIMULATOR=1
)

FILE(GLOB_RECURSE LVGL_Sources lvgl/src/*.c)
FILE(GLOB_RECURSE LVGL_Drivers_SRC lv_drivers/*.c)
FILE(GLOB_RECURSE LVGL_Examples lv_examples/*.c)
FILE(GLOB_RECURSE Main_SRC main/*.c)


add_executable(lvgl_sim ${Main_SRC} ${LVGL_Sources} ${LVGL_Drivers_SRC} ${LVGL_Examples})
target_link_libraries(lvgl_sim ${SDL2_LIBRARIES})
