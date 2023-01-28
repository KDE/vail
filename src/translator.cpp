// SPDX-FileCopyrightText: 2023 Felipe Kinoshita <kinofhek@gmail.com>
// SPDX-License-Identifier: LGPL-2.1-or-later

#include <QDebug>

#include <QString>
#include <QChar>

#include "translator.h"

Translator::Translator(QObject *parent)
    : QObject(parent)
{
    m_morseTable[QChar::fromLatin1('a')] = QString::fromLatin1(".-");
    m_morseTable[QChar::fromLatin1('b')] = QString::fromLatin1("-...");
    m_morseTable[QChar::fromLatin1('c')] = QString::fromLatin1("-.-.");
    m_morseTable[QChar::fromLatin1('d')] = QString::fromLatin1("-..");
    m_morseTable[QChar::fromLatin1('e')] = QString::fromLatin1(".");
    m_morseTable[QChar::fromLatin1('f')] = QString::fromLatin1("..-.");
    m_morseTable[QChar::fromLatin1('g')] = QString::fromLatin1("--.");
    m_morseTable[QChar::fromLatin1('h')] = QString::fromLatin1("....");
    m_morseTable[QChar::fromLatin1('i')] = QString::fromLatin1("..");
    m_morseTable[QChar::fromLatin1('j')] = QString::fromLatin1(".---");
    m_morseTable[QChar::fromLatin1('k')] = QString::fromLatin1("-.-");
    m_morseTable[QChar::fromLatin1('l')] = QString::fromLatin1(".-..");
    m_morseTable[QChar::fromLatin1('m')] = QString::fromLatin1("--");
    m_morseTable[QChar::fromLatin1('n')] = QString::fromLatin1("-.");
    m_morseTable[QChar::fromLatin1('o')] = QString::fromLatin1("---");
    m_morseTable[QChar::fromLatin1('p')] = QString::fromLatin1(".--.");
    m_morseTable[QChar::fromLatin1('q')] = QString::fromLatin1("--.-");
    m_morseTable[QChar::fromLatin1('r')] = QString::fromLatin1(".-.");
    m_morseTable[QChar::fromLatin1('s')] = QString::fromLatin1("...");
    m_morseTable[QChar::fromLatin1('t')] = QString::fromLatin1("-");
    m_morseTable[QChar::fromLatin1('u')] = QString::fromLatin1("..-");
    m_morseTable[QChar::fromLatin1('v')] = QString::fromLatin1("...-");
    m_morseTable[QChar::fromLatin1('w')] = QString::fromLatin1(".--");
    m_morseTable[QChar::fromLatin1('x')] = QString::fromLatin1("-..-");
    m_morseTable[QChar::fromLatin1('y')] = QString::fromLatin1("-.- -");
    m_morseTable[QChar::fromLatin1('z')] = QString::fromLatin1("--..");

    m_morseTable[QChar::fromLatin1('1')] = QString::fromLatin1(".----");
    m_morseTable[QChar::fromLatin1('2')] = QString::fromLatin1("..---");
    m_morseTable[QChar::fromLatin1('3')] = QString::fromLatin1("...--");
    m_morseTable[QChar::fromLatin1('4')] = QString::fromLatin1("....-");
    m_morseTable[QChar::fromLatin1('5')] = QString::fromLatin1(".....");
    m_morseTable[QChar::fromLatin1('6')] = QString::fromLatin1("-....");
    m_morseTable[QChar::fromLatin1('7')] = QString::fromLatin1("--...");
    m_morseTable[QChar::fromLatin1('8')] = QString::fromLatin1("---..");
    m_morseTable[QChar::fromLatin1('9')] = QString::fromLatin1("----.");
    m_morseTable[QChar::fromLatin1('0')] = QString::fromLatin1("-----");

    m_morseTable[QChar::fromLatin1('&')] = QString::fromLatin1(".-...");
    m_morseTable[QChar::fromLatin1('\'')] = QString::fromLatin1(".----.");
    m_morseTable[QChar::fromLatin1('@')] = QString::fromLatin1(".--.-.");
    m_morseTable[QChar::fromLatin1(')')] = QString::fromLatin1("-.--.-");
    m_morseTable[QChar::fromLatin1('(')] = QString::fromLatin1("-.--.");
    m_morseTable[QChar::fromLatin1(':')] = QString::fromLatin1("---...");
    m_morseTable[QChar::fromLatin1(',')] = QString::fromLatin1("--..--");
    m_morseTable[QChar::fromLatin1('=')] = QString::fromLatin1("-...-");
    m_morseTable[QChar::fromLatin1('!')] = QString::fromLatin1("-.-.--");
    m_morseTable[QChar::fromLatin1('.')] = QString::fromLatin1(".-.-.-");
    m_morseTable[QChar::fromLatin1('-')] = QString::fromLatin1("-....-");
    m_morseTable[QChar::fromLatin1('x')] = QString::fromLatin1("-..-");
    m_morseTable[QChar::fromLatin1('+')] = QString::fromLatin1(".-.-.");
    m_morseTable[QChar::fromLatin1('"')] = QString::fromLatin1(".-..-.");
    m_morseTable[QChar::fromLatin1('?')] = QString::fromLatin1("..--..");
    m_morseTable[QChar::fromLatin1('/')] = QString::fromLatin1("-..-.");
}

void Translator::translate(const QString &message)
{
    const QStringList words = message.toLower().split(QStringLiteral(" "));
    QString morse;

    for (const QString &word : words) {
        for (const QChar &character : word) {
            morse.append(m_morseTable.value(character));

            if (word.indexOf(character) == word.length()) {
                morse.append(QString());
            } else {
                morse.append(QStringLiteral("   "));
            }
        }

        if (words.indexOf(word) == words.length() - 1) {
            morse.append(QString());
        } else {
            morse.append(QStringLiteral(" /    "));
        }
    }

    Q_EMIT translation(morse);
}
