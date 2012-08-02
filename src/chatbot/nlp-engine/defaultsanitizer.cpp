/*
 * Copyright (C) 2012 Andres Pagliano, Gabriel Miretti, Gonzalo Buteler,
 * Nestor Bustamante, Pablo Perez de Angelis
 *
 * This file is part of LVK Chatbot.
 *
 * LVK Chatbot is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LVK Chatbot is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LVK Chatbot.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "nlp-engine/defaultsanitizer.h"

#include <QtDebug>

#define utf8_a_acute                    "\xc3\xa1"
#define utf8_e_acute                    "\xc3\xa9"
#define utf8_i_acute                    "\xc3\xad"
#define utf8_o_acute                    "\xc3\xb3"
#define utf8_u_acute                    "\xc3\xba"
#define utf8_A_acute                    "\xc3\x81"
#define utf8_E_acute                    "\xc3\x89"
#define utf8_I_acute                    "\xc3\x8d"
#define utf8_O_acute                    "\xc3\x93"
#define utf8_U_acute                    "\xc3\x9a"
#define utf8_u_diaeresis                "\xc3\xbc"
#define utf8_U_diaeresis                "\xc3\x9c"
#define utf8_inverted_exclamation_mark  "\xc2\xa1"
#define utf8_inverted_question_mark     "\xc2\xbf"


//--------------------------------------------------------------------------------------------------
// DefaultSanitizer
//--------------------------------------------------------------------------------------------------

Lvk::Nlp::DefaultSanitizer::DefaultSanitizer()
    : m_options(0xffff)
{
}

//--------------------------------------------------------------------------------------------------

Lvk::Nlp::DefaultSanitizer::DefaultSanitizer(Options options)
    : m_options(options)
{
}

//--------------------------------------------------------------------------------------------------

QString Lvk::Nlp::DefaultSanitizer::sanitize(const QString &str) const
{
    if (str.isEmpty()) {
        return str;
    }

    // TODO optimize!

    QString szStr= str;

    if (m_options.testFlag(RemoveDiacritic)) {
        szStr.replace(QString::fromUtf8(utf8_a_acute),     QString("a"));
        szStr.replace(QString::fromUtf8(utf8_e_acute),     QString("e"));
        szStr.replace(QString::fromUtf8(utf8_i_acute),     QString("i"));
        szStr.replace(QString::fromUtf8(utf8_o_acute),     QString("o"));
        szStr.replace(QString::fromUtf8(utf8_u_acute),     QString("u"));
        szStr.replace(QString::fromUtf8(utf8_A_acute),     QString("A"));
        szStr.replace(QString::fromUtf8(utf8_E_acute),     QString("E"));
        szStr.replace(QString::fromUtf8(utf8_I_acute),     QString("I"));
        szStr.replace(QString::fromUtf8(utf8_O_acute),     QString("O"));
        szStr.replace(QString::fromUtf8(utf8_U_acute),     QString("U"));
        szStr.replace(QString::fromUtf8(utf8_u_diaeresis), QString("u"));
        szStr.replace(QString::fromUtf8(utf8_U_diaeresis), QString("U"));
    }

    if (m_options.testFlag(RemovePunctuation)) {
        szStr.remove(",");
        szStr.remove(";");
        szStr.remove(".");
        szStr.remove("!");
        szStr.remove("?");
        szStr.remove(QString::fromUtf8(utf8_inverted_exclamation_mark));
        szStr.remove(QString::fromUtf8(utf8_inverted_question_mark));
    }

    if (m_options.testFlag(RemoveDupChars)) {
        int rcount = 0;             // repeat count
        QChar prev;                 // previous char
        QChar cur;                  // current char
        QString tmp;

        QSet<QChar> rSet;           // Chars allowed to repeat once
        rSet.insert('r');
        rSet.insert('l');
        //repSet.insert('o');

        tmp.append(szStr[0]);

        for (int i = 1; i < szStr.size(); ++i) {
            prev = szStr[i-1];
            cur = szStr[i];

             if (cur.isLetter() && cur.toLower() == prev.toLower()) {
                ++rcount;
             } else {
                 rcount = 0;
             }

             bool append = rcount == 0 || (rcount == 1 && rSet.contains(cur));

             if (append) {
                 tmp.append(cur);
             }
        }

        szStr = tmp;
    }

    qDebug() << "   - Sanitized:" << str << "->" << szStr;

    return szStr;
}

