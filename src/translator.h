// SPDX-FileCopyrightText: 2023 Felipe Kinoshita <kinofhek@gmail.com>
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <QHash>
#include <QObject>

class QQuickWindow;

class Translator : public QObject
{
    Q_OBJECT

public:
    explicit Translator(QObject* parent = nullptr);

    Q_INVOKABLE void translate(const QString &message);
    Q_SIGNAL void translation(const QString &morse);

private:
    QHash<QChar, QString> m_morseTable;
};
