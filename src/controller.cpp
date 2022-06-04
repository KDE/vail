// SPDX-FileCopyrightText: 2022 Felipe Kinoshita <kinofhek@gmail.com>
// SPDX-License-Identifier: LGPL-2.1-or-later

#include <QQuickWindow>

#include <KConfig>
#include <KConfigGroup>
#include <KWindowConfig>

#include "controller.h"

Controller::Controller(QObject *parent)
    : QObject(parent)
{
}

Controller::~Controller()
{
}

void Controller::restoreWindowGeometry(QQuickWindow *window)
{
    KConfig dataResource("data", KConfig::SimpleConfig, QStandardPaths::AppDataLocation);
    KConfigGroup windowGroup(&dataResource, "Window");
    KWindowConfig::restoreWindowSize(window, windowGroup);
    KWindowConfig::restoreWindowPosition(window, windowGroup);
}

void Controller::saveWindowGeometry(QQuickWindow *window)
{
    KConfig dataResource("data", KConfig::SimpleConfig, QStandardPaths::AppDataLocation);
    KConfigGroup windowGroup(&dataResource, "Window");
    KWindowConfig::saveWindowPosition(window, windowGroup);
    KWindowConfig::saveWindowSize(window, windowGroup);
    dataResource.sync();
}

void Controller::translate(QString message)
{
    QStringList words = message.split(" ");
    QString translatedMessage;

    for (auto word : words) {
        for (auto character : word) {
            translatedMessage.append(getMorseFromCharacter(character));

            if (word.indexOf(character) == word.length()) {
                translatedMessage.append("");
            } else {
                translatedMessage.append("   ");
            }
        }

        if (words.indexOf(word) == words.length() - 1) {
            translatedMessage.append("");
        } else {
            translatedMessage.append(" /    ");
        }
    }



    Q_EMIT translation(translatedMessage);
}

QString Controller::getMorseFromCharacter(QChar character)
{
    QString morse;

    if (character == 'a' || character == 'A') {
        morse = QString(". -");
    } else if (character == 'b' || character == 'B') {
        morse = QString("- . . .");
    } else if (character == 'c' || character == 'C') {
        morse = QString("- . - .");
    } else if (character == 'd' || character == 'D') {
        morse = QString("- . .");
    } else if (character == 'e' || character == 'E') {
        morse = QString(".");
    } else if (character == 'f' || character == 'F') {
        morse = QString(". . - .");
    } else if (character == 'g' || character == 'G') {
        morse = QString("- - .");
    } else if (character == 'h' || character == 'H') {
        morse = QString(". . . .");
    } else if (character == 'i' || character == 'I') {
        morse = QString(". .");
    } else if (character == 'j' || character == 'J') {
        morse = QString(". - - -");
    } else if (character == 'k' || character == 'K') {
        morse = QString("- . -");
    } else if (character == 'l' || character == 'L') {
        morse = QString(". - . .");
    } else if (character == 'm' || character == 'M') {
        morse = QString("- -");
    } else if (character == 'n' || character == 'N') {
        morse = QString("- .");
    } else if (character == 'o' || character == 'O') {
        morse = QString("- - -");
    } else if (character == 'p' || character == 'P') {
        morse = QString(". - - .");
    } else if (character == 'q' || character == 'Q') {
        morse = QString("- - . -");
    } else if (character == 'r' || character == 'R') {
        morse = QString(". - .");
    } else if (character == 's' || character == 'S') {
        morse = QString(". . .");
    } else if (character == 't' || character == 'T') {
        morse = QString("-");
    } else if (character == 'u' || character == 'U') {
        morse = QString(". . -");
    } else if (character == 'v' || character == 'V') {
        morse = QString(". . . -");
    } else if (character == 'w' || character == 'W') {
        morse = QString(". - -");
    } else if (character == 'x' || character == 'X') {
        morse = QString("- . . -");
    } else if (character == 'y' || character == 'Y') {
        morse = QString("- . - -");
    } else if (character == 'z' || character == 'Z') {
        morse = QString("- - . .");
    } else if (character == '0') {
        morse = QString("- - - - -");
    } else if (character == '1') {
        morse = QString(". - - - -");
    } else if (character == '2') {
        morse = QString(". . - - -");
    } else if (character == '3') {
        morse = QString(". . . - -");
    } else if (character == '4') {
        morse = QString(". . . . -");
    } else if (character == '5') {
        morse = QString(". . . . .");
    } else if (character == '6') {
        morse = QString("- . . . .");
    } else if (character == '7') {
        morse = QString("- - . . .");
    } else if (character == '8') {
        morse = QString("- - - . .");
    } else if (character == '9') {
        morse = QString("- - - - .");
    }

    return morse;
}
