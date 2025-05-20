cmake_minimum_required(VERSION 3.31)
project(coursework)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(coursework main.cpp
        personlistwidget.h
        personlistwidget.cpp
        mainwindow.h
        mainwindow.cpp
        mainwindow.ui
        person.h
        person.cpp
        inputdialog.h
        inputdialog.cpp
        inputdialog.ui
        )

target_link_libraries(coursework
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

