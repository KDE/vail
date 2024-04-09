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
        display: QQC2.AbstractButton.IconOnly
        action: Kirigami.Action {
            text: i18n("About Vail")
            icon.name: "help-about"
            shortcut: StandardKey.HelpContents
            onTriggered: pageStack.layers.push(Qt.createComponent("org.kde.kirigamiaddons.formcard", "AboutPage"))
            enabled: pageStack.layers.depth <= 1
        }

        QQC2.ToolTip.visible: hovered
        QQC2.ToolTip.text: text
        QQC2.ToolTip.delay: Kirigami.Units.toolTipDelay
    }
}
