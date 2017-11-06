cmake_minimum_required(VERSION 3.5.1)
project(train_control)

find_package(Threads REQUIRED)

include_directories(include)

add_library(display SHARED
    src/Display.cpp
    src/ConsoleDisplay.cpp
    src/LCDDisplay.cpp
    src/lcd.cpp
    src/DisplayFactory.cpp
 )

add_executable(train_control src/main.cpp)

target_link_libraries(train_control 
    display
    -lpthread
)
