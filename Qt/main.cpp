/*
 * Copyright (C) 2019  ahahn94
 *     This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 *
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <QDebug>
#include <QFile>

#include "Guest.h"

/**
 * Read Guests from the specified file.
 * @param filePath Name of the file.
 * @return File content as a list of Guests.
 */
QList<Guest> readGuestsFromFile(const QString &filePath) {
    QList<Guest> guests;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return guests;
    }
    QTextStream input(&file);
    while (!input.atEnd()) {
        QString line = input.readLine();
        QStringList parts = line.split("|");
        int id = parts[0].toInt();
        QString firstName = parts[1];
        QString lastName = parts[2];
        QStringList friendIdStrings = parts[3].split(",");
        QList<int> friendIDs;
        for (auto &idString: friendIdStrings) {
            friendIDs.append(idString.toInt());
        }
        guests.append(Guest(firstName, lastName, id, friendIDs));
    }
    return guests;
}

/**
 * Remove guests with friends count < k from the list.
 * @param guests List of the guests.
 * @param k Minimum number of friends for each guest.
 * @return Modified list.
 */
QList<Guest> party(QList<Guest> guests, int k) {
    if (guests.length() <= k) return QList<Guest>();
    if (k == 0) return guests;
    for (auto &guest: guests) {
        if (guest.getNumberOfFriends() < k) {
            int id = guest.getId();
            guests.removeOne(guest);
            for (auto &guest1 : guests) {
                guest1.removeFriend(id);
            }
            guests = party(guests, k);
            return guests;
        }
    }
    return guests;
}

/**
 * Program control.
 * @return 0
 */
int main() {
    QString filePath("../../res/guests.txt");
    int k = 4;
    QList<Guest> guests = readGuestsFromFile(filePath);
    guests = party(guests, k);
    if (guests.length() == 0) {
        qDebug() << QString("No guests on the list.");
    } else {
        qDebug() << "Guests:";
        for (auto &guest : guests) {
            qDebug() << guest.toString();
        }
    }
    return 0;
}