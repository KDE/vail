# SPDX-FileCopyrightText: 2022 Felipe Kinoshita <kinofhek@gmail.com>
# SPDX-License-Identifier: BSD-2-Clause

add_executable(${CMAKE_PROJECT_NAME}
    main.cpp
    controller.cpp
    resources.qrc)

target_link_libraries(${CMAKE_PROJECT_NAME}
PRIVATE
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
    Qt::QuickControls2
    Qt::Svg
    KF5::I18n
    KF5::CoreAddons
    KF5::ConfigCore
    KF5::ConfigGui)

if(TARGET KF5::DBusAddons)
    target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE KF5::DBusAddons)
    target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE -DHAVE_KDBUSADDONS)
endif()

install(TARGETS ${CMAKE_PROJECT_NAME} ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
