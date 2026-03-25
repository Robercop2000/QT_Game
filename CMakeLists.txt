cmake_minimum_required(VERSION 3.16)

project(GameQT VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Qml Core)

# =========================
# Executable
# =========================
qt_add_executable(appGameQT
    src/main.cpp
)

# =========================
# QML Module
# =========================

qt_add_qml_module(gameCore
    URI GameCore

    SOURCES
        src/core/Controller.cpp
        src/core/Controller.h
        src/entities/Enemy.cpp
        src/entities/Enemy.h
        src/entities/Bullet.cpp
        src/entities/Bullet.h
)

target_include_directories(gameCore
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core
        ${CMAKE_CURRENT_SOURCE_DIR}/src/entities
)

qt_add_qml_module(appGameQT
    URI GameQT
    VERSION 1.0

    QML_FILES
        qml/main.qml
        qml/Enemy.qml
        qml/Bullet.qml

    RESOURCES
        assets/assets.qrc

)

# =========================
# Link
# =========================
target_link_libraries(appGameQT
    PRIVATE Qt6::Quick gameCore
)

# =========================
# Finalize
# =========================
qt_finalize_executable(appGameQT)