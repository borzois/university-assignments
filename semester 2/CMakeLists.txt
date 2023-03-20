cmake_minimum_required(VERSION 3.21)
project(Lab10_11)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(Qt6_DIR /Users/rob/Qt/6.2.4/macos/lib/cmake/Qt6)


find_package(Qt6 COMPONENTS
        Core
        Widgets
        REQUIRED)

add_executable(Lab10_11
        main.cpp
        ui.cpp
        ui.h
        Car.cpp
        Car.h
        CarRepository.cpp
        CarRepository.h
        Service.cpp
        Service.h
        Validators.h
        WashList.cpp
        WashList.h
        Undo.cpp
        Undo.h qtui.cpp qtui.h qtui.ui gui.cpp gui.h Observer.h WashListGUI.cpp WashListGUI.h)
target_link_libraries(Lab10_11
        Qt::Core
        Qt::Widgets
        )

