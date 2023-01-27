// SPDX-FileCopyrightText: 2022 Felipe Kinoshita <kinofhek@gmail.com>
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <QObject>

class QQuickWindow;

class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(QObject* parent = nullptr);

    Q_INVOKABLE void restoreWindowGeometry(QQuickWindow* window);
    Q_INVOKABLE void saveWindowGeometry(QQuickWindow* window);

    Q_INVOKABLE void translate(const QString &message);

    QString getMorseFromCharacter(const QString &character);

Q_SIGNALS:
    void translation(const QString &translated);

private:
};
