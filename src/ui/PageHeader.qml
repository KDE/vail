// SPDX-FileCopyrightText: 2022 Felipe Kinoshita <kinofhek@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick
import QtQuick.Controls as QQC2
import QtQuick.Layouts
import org.kde.kirigami as Kirigami

import org.kde.vail

RowLayout {
    id: pageHeader

    Layout.fillWidth: true
    spacing: 0

    QQC2.ToolButton {
        action: Kirigami.Action {
            text: i18n("Copy Morse to Clipboard")
            icon.name: "edit-copy"
            shortcut: StandardKey.Copy
            onTriggered: {
                morseTextarea.selectAll()
                morseTextarea.copy()
                morseTextarea.moveCursorSelection(0, TextEdit.SelectCharacters)
                morseTextarea.deselect()
            }
        }

        QQC2.ToolTip.visible: hovered
        QQC2.ToolTip.text: "Ctrl+C"
        QQC2.ToolTip.delay: Kirigami.Units.toolTipDelay
    }

    Item {
        Layout.fillWidth: true
    }

    QQC2.ToolButton {
        id: menuButton

        focusPolicy: Qt.NoFocus

        display: QQC2.AbstractButton.IconOnly
        down: applicationMenu.opened
        action: Kirigami.Action {
            text: i18n("Menu")
            icon.name: "application-menu-symbolic"
            onTriggered: applicationMenu.popup(menuButton, 0.0, menuButton.height)
        }

        QQC2.Menu {
            id: applicationMenu
            QQC2.MenuItem {
                action: Kirigami.Action {
                    text: i18nc("@action:inmenu", "About Vail")
                    icon.name: "org.kde.vail"
                    shortcut: StandardKey.HelpContents
                    onTriggered: pageStack.layers.push(Qt.createComponent("org.kde.kirigamiaddons.formcard", "AboutPage"))
                }
            }
            QQC2.MenuItem {
                text: i18nc("@action:inmenu", "About KDE")
                icon.name: "kdeapp"
                onClicked: pageStack.layers.push(Qt.createComponent("org.kde.kirigamiaddons.formcard", "AboutKDE"))
            }
            QQC2.MenuItem {
                action: Kirigami.Action {
                    icon.name: "application-exit"
                    text: i18nc("@action:inmenu", "Quit")
                    shortcut: StandardKey.Quit
                    onTriggered: Qt.quit()
                }
            }
        }

        QQC2.ToolTip.visible: hovered
        QQC2.ToolTip.text: text
        QQC2.ToolTip.delay: Kirigami.Units.toolTipDelay
    }
}
