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
    KConfig dataResource(QStringLiteral("data"), KConfig::SimpleConfig, QStandardPaths::AppDataLocation);
    KConfigGroup windowGroup(&dataResource, "Window");
    KWindowConfig::restoreWindowSize(window, windowGroup);
    KWindowConfig::restoreWindowPosition(window, windowGroup);
}

void Controller::saveWindowGeometry(QQuickWindow *window)
{
    KConfig dataResource(QStringLiteral("data"), KConfig::SimpleConfig, QStandardPaths::AppDataLocation);
    KConfigGroup windowGroup(&dataResource, "Window");
    KWindowConfig::saveWindowPosition(window, windowGroup);
    KWindowConfig::saveWindowSize(window, windowGroup);
    dataResource.sync();
}

void Controller::translate(QString message)
{
    QStringList words = message.split(QStringLiteral(" "));
    QString translatedMessage;

    for (auto word : words) {
        for (QString character : word) {
            translatedMessage.append(getMorseFromCharacter(character));

            if (word.indexOf(character) == word.length()) {
                translatedMessage.append(QString());
            } else {
                translatedMessage.append(QStringLiteral("   "));
            }
        }

        if (words.indexOf(word) == words.length() - 1) {
            translatedMessage.append(QString());
        } else {
            translatedMessage.append(QStringLiteral(" /    "));
        }
    }



    Q_EMIT translation(translatedMessage);
}

QString Controller::getMorseFromCharacter(QString character)
{
    QString morse;

    if (character == QLatin1Char('a') || character == QLatin1Char('A')) {
        morse = QStringLiteral(". -");
    } else if (character == QLatin1Char('b') || character == QLatin1Char('B')) {
        morse = QStringLiteral("- . . .");
    } else if (character == QLatin1Char('c') || character == QLatin1Char('C')) {
        morse = QStringLiteral("- . - .");
    } else if (character == QLatin1Char('d') || character == QLatin1Char('D')) {
        morse = QStringLiteral("- . .");
    } else if (character == QLatin1Char('e') || character == QLatin1Char('E')) {
        morse = QStringLiteral(".");
    } else if (character == QLatin1Char('f') || character == QLatin1Char('F')) {
        morse = QStringLiteral(". . - .");
    } else if (character == QLatin1Char('g') || character == QLatin1Char('G')) {
        morse = QStringLiteral("- - .");
    } else if (character == QLatin1Char('h') || character == QLatin1Char('H')) {
        morse = QStringLiteral(". . . .");
    } else if (character == QLatin1Char('i') || character == QLatin1Char('I')) {
        morse = QStringLiteral(". .");
    } else if (character == QLatin1Char('j') || character == QLatin1Char('J')) {
        morse = QStringLiteral(". - - -");
    } else if (character == QLatin1Char('k') || character == QLatin1Char('K')) {
        morse = QStringLiteral("- . -");
    } else if (character == QLatin1Char('l') || character == QLatin1Char('L')) {
        morse = QStringLiteral(". - . .");
    } else if (character == QLatin1Char('m') || character == QLatin1Char('M')) {
        morse = QStringLiteral("- -");
    } else if (character == QLatin1Char('n') || character == QLatin1Char('N')) {
        morse = QStringLiteral("- .");
    } else if (character == QLatin1Char('o') || character == QLatin1Char('O')) {
        morse = QStringLiteral("- - -");
    } else if (character == QLatin1Char('p') || character == QLatin1Char('P')) {
        morse = QStringLiteral(". - - .");
    } else if (character == QLatin1Char('q') || character == QLatin1Char('Q')) {
        morse = QStringLiteral("- - . -");
    } else if (character == QLatin1Char('r') || character == QLatin1Char('R')) {
        morse = QStringLiteral(". - .");
    } else if (character == QLatin1Char('s') || character == QLatin1Char('S')) {
        morse = QStringLiteral(". . .");
    } else if (character == QLatin1Char('t') || character == QLatin1Char('T')) {
        morse = QStringLiteral("-");
    } else if (character == QLatin1Char('u') || character == QLatin1Char('U')) {
        morse = QStringLiteral(". . -");
    } else if (character == QLatin1Char('v') || character == QLatin1Char('V')) {
        morse = QStringLiteral(". . . -");
    } else if (character == QLatin1Char('w') || character == QLatin1Char('W')) {
        morse = QStringLiteral(". - -");
    } else if (character == QLatin1Char('x') || character == QLatin1Char('X')) {
        morse = QStringLiteral("- . . -");
    } else if (character == QLatin1Char('y') || character == QLatin1Char('Y')) {
        morse = QStringLiteral("- . - -");
    } else if (character == QLatin1Char('z') || character == QLatin1Char('Z')) {
        morse = QStringLiteral("- - . .");
    } else if (character == QLatin1Char('0')) {
        morse = QStringLiteral("- - - - -");
    } else if (character == QLatin1Char('1')) {
        morse = QStringLiteral(". - - - -");
    } else if (character == QLatin1Char('2')) {
        morse = QStringLiteral(". . - - -");
    } else if (character == QLatin1Char('3')) {
        morse = QStringLiteral(". . . - -");
    } else if (character == QLatin1Char('4')) {
        morse = QStringLiteral(". . . . -");
    } else if (character == QLatin1Char('5')) {
        morse = QStringLiteral(". . . . .");
    } else if (character == QLatin1Char('6')) {
        morse = QStringLiteral("- . . . .");
    } else if (character == QLatin1Char('7')) {
        morse = QStringLiteral("- - . . .");
    } else if (character == QLatin1Char('8')) {
        morse = QStringLiteral("- - - . .");
    } else if (character == QLatin1Char('9')) {
        morse = QStringLiteral("- - - - .");
    } else if (character == QLatin1Char('!')) {
        morse = QStringLiteral("- . - . - -");
    } else if (character == QLatin1Char('"')) {
        morse = QStringLiteral(". - . . - .");
    } else if (character == QLatin1Char(39)) { // '
        morse = QStringLiteral(". - - - - .");
    } else if (character == QLatin1Char('$')) {
        morse = QStringLiteral(". . . - . . -");
    } else if (character == QLatin1Char('&')) {
        morse = QStringLiteral(". - . . .");
    } else if (character == QLatin1Char('(')) {
        morse = QStringLiteral("- . - - .");
    } else if (character == QLatin1Char(')')) {
        morse = QStringLiteral("- . - - . -");
    } else if (character == QLatin1Char('+')) {
        morse = QStringLiteral(". - . - .");
    } else if (character == QLatin1Char(',')) {
        morse = QStringLiteral("- - . . - -");
    } else if (character == QLatin1Char('-')) {
        morse = QStringLiteral("- . . . . -");
    } else if (character == QLatin1Char('.')) {
        morse = QStringLiteral(". - . - . -");
    } else if (character == QLatin1Char('/')) {
        morse = QStringLiteral("- . . - .");
    } else if (character == QLatin1Char(':')) {
        morse = QStringLiteral("- - - . . .");
    } else if (character == QLatin1Char(';')) {
        morse = QStringLiteral("- . - . - .");
    } else if (character == QLatin1Char('=')) {
        morse = QStringLiteral("- . . . -");
    } else if (character == QLatin1Char('?')) {
        morse = QStringLiteral(". . - - . .");
    } else if (character == QLatin1Char('@')) {
        morse = QStringLiteral(". - - . - .");
    } else if (character == QLatin1Char('_')) {
        morse = QStringLiteral(". . - - . -");
    }

    return morse;
}
