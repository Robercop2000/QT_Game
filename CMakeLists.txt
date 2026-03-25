cmake_minimum_required(VERSION 3.16)

project(GameQT VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

# -------------------------
# Executable
# -------------------------
qt_add_executable(appGameQT
    src/main.cpp
)

# -------------------------
# QML Module
# -------------------------
qt_add_qml_module(appGameQT
    URI GameQT
    VERSION 1.0

    SOURCES
        src/core/Controller.cpp
        src/core/Controller.h
        src/entities/Enemy.cpp
        src/entities/Enemy.h
        src/entities/Bullet.cpp
        src/entities/Bullet.h

    QML_FILES
        qml/Main.qml
        qml/Enemy.qml
        qml/Bullet.qml

    RESOURCES
        assets/assets.qrc
)
target_include_directories(appGameQT
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core
    ${CMAKE_CURRENT_SOURCE_DIR}/src/entities
)
# -------------------------
# Links
# -------------------------
target_link_libraries(appGameQT
    PRIVATE
        Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appGameQT
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})