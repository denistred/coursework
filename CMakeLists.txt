cmake_minimum_required(VERSION 3.31)
project(coursework)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)

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
        include/personlistwidget.h
        src/personlistwidget.cpp
        include/mainwindow.h
        src/mainwindow.cpp
        ui/mainwindow.ui
        include/person.h
        src/person.cpp
        include/inputdialog.h
        src/inputdialog.cpp
        ui/inputdialog.ui
        include/personitem.h
        src/personitem.cpp
        include/personscene.h
        src/personscene.cpp
        include/relationitem.h
        src/relationitem.cpp
)

target_link_libraries(coursework
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

