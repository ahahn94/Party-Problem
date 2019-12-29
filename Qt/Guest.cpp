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

#include "Guest.h"

/**
 * Constructor.
 * @param firstName Guests first name.
 * @param lastName Guests last name.
 * @param id Guests ID.
 * @param friends List of friends IDs.
 */
Guest::Guest(QString firstName, QString lastName, int id, QList<int> friends){
    this->firstName = firstName;
    this->lastName = lastName;
    this->id = id;
    this->friends = friends;
}

/**
 * Get a QString of the guests data.
 * @return "$firstName, $lastName, $id, [$friends]"
 */
QString Guest::toString(){
    return firstName + ", " + lastName + ", " + QString::number(id) + ", " + friendsToString();
}

/**
 * Remove a friends ID from the list.
 * @param friendID ID of the friend to remove.
 */
void Guest::removeFriend(int friendID) {
        friends.removeOne(friendID);
}

/**
 * Get the id of the Guest.
 * @return ID of the Guest.
 */
int Guest::getId() {
    return this->id;
}

/**
 * Get the number of friends on the guests list.
 * @return Number of friends of the Guest.
 */
int Guest::getNumberOfFriends() {
    return this->friends.length();
}

/**
 * Compare-operator.
 * Two Guests are identical if they have the same ID.
 * @param guest Guest to compare to.
 * @return true if the guests are identical, else false.
 */
bool Guest::operator==(const Guest &guest){
    return this->id == guest.id;
}

/**
 * Get a QString of the list of friends of the Guest.
 * @return "[$friends]".
 */
QString Guest::friendsToString() {
    QString friendsString;
    friendsString.append("[");
            for(auto &friendID: this->friends){
            friendsString.append(QString::number(friendID) + ",");
        }
    friendsString = friendsString.left(friendsString.length() - 1);
    friendsString.append("]");
    return friendsString;
}
