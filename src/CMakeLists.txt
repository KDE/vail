# SPDX-FileCopyrightText: 2022 Felipe Kinoshita <kinofhek@gmail.com>
# SPDX-License-Identifier: BSD-2-Clause

add_executable(${CMAKE_PROJECT_NAME}
    main.cpp
    app.cpp
    translator.cpp)

ecm_add_qml_module(${CMAKE_PROJECT_NAME}
        URI org.kde.vail
        VERSION 1.0
        DEPENDENCIES
        "QtQuick.Controls"
        GENERATE_PLUGIN_SOURCE)
qt_target_qml_sources(${CMAKE_PROJECT_NAME}
        QML_FILES
        ui/GlobalMenu.qml
        ui/Main.qml
        ui/PageHeader.qml)

target_link_libraries(${CMAKE_PROJECT_NAME}
PRIVATE
    Qt::Core
    Qt::Gui
    Qt::Quick
    Qt::QuickControls2
    Qt::Svg
    KF6::I18n
    KF6::CoreAddons
    KF6::ConfigCore
    KF6::ConfigGui)

if(TARGET KF6::DBusAddons)
    target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE KF6::DBusAddons)
    target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE -DHAVE_KDBUSADDONS)
endif()

if(NOT ANDROID)
    target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt::Widgets)
endif()

install(TARGETS ${CMAKE_PROJECT_NAME} ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
