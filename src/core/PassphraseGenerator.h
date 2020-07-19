/*
 *  Copyright (C) 2017 KeePassXC Team <team@keepassxc.org>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 or (at your option)
 *  version 3 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KEEPASSX_PASSPHRASEGENERATOR_H
#define KEEPASSX_PASSPHRASEGENERATOR_H

#include <QFlags>
#include <QString>
#include <QVector>

class PassphraseGenerator
{
public:
    enum PassphraseWordCase
    {
        LOWERCASE,
        UPPERCASE,
        TITLECASE
    };

    enum WordClass
    {
        Words = (1 << 0),
        Numbers = (1 << 1),
        Special = (1 << 3),
        DefaultWordset = Words
    };
    Q_DECLARE_FLAGS(WordClasses, WordClass)

    enum GeneratorFlag
    {
        ExcludeLookAlike = (1 << 0),
        DefaultFlags = ExcludeLookAlike
    };
    Q_DECLARE_FLAGS(GeneratorFlags, GeneratorFlag)

public:
    PassphraseGenerator();
    Q_DISABLE_COPY(PassphraseGenerator)

    double estimateEntropy(int wordCount = 0);
    void setWordCount(int wordCount);
    void setWordList(const QString& path);
    void setWordCase(PassphraseWordCase wordCase);
    void setWordClasses(const WordClasses& classes);
    void setDigitCount(int digitCount);
    void setFlags(const GeneratorFlags& flags);
    void setDefaultWordList();
    void setWordSeparator(const QString& separator);
    bool isValid() const;

    QString generatePassphrase() const;

    static constexpr int DefaultWordCount = 7;
    static constexpr int DefaultDigitCount = 3;
    static const char* DefaultSeparator;
    static const char* DefaultWordList;

private:
    QChar generateDigit() const;
    QChar generateSpecial() const;

    int m_wordCount;
    int m_digitCount;
    WordClasses m_classes;
    GeneratorFlags m_flags;
    PassphraseWordCase m_wordCase;
    QString m_separator;
    QVector<QString> m_wordlist;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(PassphraseGenerator::WordClasses)

#endif // KEEPASSX_PASSPHRASEGENERATOR_H
