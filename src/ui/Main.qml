// SPDX-FileCopyrightText: 2022 Felipe Kinoshita <kinofhek@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick
import QtQuick.Controls as QQC2
import QtQuick.Layouts
import org.kde.kirigami as Kirigami
import org.kde.config as KConfig

import org.kde.vail

Kirigami.ApplicationWindow {
    id: root

    title: i18n("Vail")

    width: Kirigami.Units.gridUnit * 34
    height: Kirigami.Units.gridUnit * 21
    minimumWidth: Kirigami.Units.gridUnit * 20
    minimumHeight: Kirigami.Units.gridUnit * 20

    KConfig.WindowStateSaver {
        configGroupName: "Main"
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
                        Translator.translate(text)
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
                        target: Translator

                        function onTranslation(translation) {
                            morseTextarea.text = translation
                        }
                    }
                }
            }
        }
    }
}
