// SPDX-FileCopyrightText: 2022 Felipe Kinoshita <kinofhek@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick 2.15
import QtQuick.Controls 2.15 as QQC2
import QtQuick.Layouts 1.15
import org.kde.kirigami 2.19 as Kirigami

import org.kde.vail 1.0

Kirigami.ApplicationWindow {
    id: root

    title: i18n("Vail")

    width: Kirigami.Units.gridUnit * 34
    height: Kirigami.Units.gridUnit * 21
    minimumWidth: Kirigami.Units.gridUnit * 20
    minimumHeight: Kirigami.Units.gridUnit * 20

    Timer {
        id: saveWindowGeometryTimer
        interval: 1000
        onTriggered: Controller.saveWindowGeometry(root)
    }

    Connections {
        id: saveWindowGeometryConnections
        enabled: false // Disable on startup to avoid writing wrong values if the window is hidden
        target: root

        function onClosing() { Controller.saveWindowGeometry(root); }
        function onWidthChanged() { saveWindowGeometryTimer.restart(); }
        function onHeightChanged() { saveWindowGeometryTimer.restart(); }
        function onXChanged() { saveWindowGeometryTimer.restart(); }
        function onYChanged() { saveWindowGeometryTimer.restart(); }
    }

    Loader {
        active: !Kirigami.Settings.isMobile
        sourceComponent: GlobalMenu {}
    }

    pageStack.initialPage: Kirigami.Page {
        id: page

        padding: Kirigami.Units.gridUnit
        titleDelegate: PageHeader {}

        ColumnLayout {
            anchors.fill: parent

            Kirigami.Heading {
                text: i18n("Message:")
                type: Kirigami.Heading.Primary
            }

            QQC2.ScrollView {
                Layout.fillWidth: true
                Layout.fillHeight: true

                QQC2.TextArea {
                    id: messageTextarea

                    focus: !Kirigami.InputMethod.willShowOnActive

                    wrapMode: Text.Wrap

                    onTextChanged: {
                        Controller.translate(text)
                    }
                }
            }

            Item {
                Layout.preferredHeight: Kirigami.Units.largeSpacing
            }

            Kirigami.Heading {
                text: i18n("Morse Code:")
                type: Kirigami.Heading.Primary
            }

            QQC2.ScrollView {
                Layout.fillWidth: true
                Layout.fillHeight: true

                QQC2.TextArea {
                    id: morseTextarea

                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    readOnly: true
                    wrapMode: Text.Wrap

                    Connections {
                        target: Controller

                        function onTranslation(translation) {
                            morseTextarea.text = translation
                        }
                    }
                }
            }
        }
    }

    Component.onCompleted: {
        if (!Kirigami.Settings.isMobile) {
            saveWindowGeometryConnections.enabled = true
        }
    }
}