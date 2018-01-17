/*
 * Copyright (C) 2018  ahahn94
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

#include <algorithm>

/**
 * Constructor.
 * @param id Guests ID.
 * @param surname Guests last name.
 * @param name Guests first name.
 * @param friends List of friends IDs.
 */
Guest::Guest(int id, std::string surname, std::string name, std::vector<std::string> friends) {
    this->id = id;
    this->name = name;
    this->surname = surname;
    this->friends = friends;
}

Guest::Guest(){}

/**
 * Get a string of the guests data.
 * @return "$ID, $NAME, $SURNAME, [$FRIENDS]"
 */
std::string Guest::toString() {
    return std::to_string(id) + ": " + name + ", " + surname + ", " + toString(friends);
}

/**
 * Remove a friends ID from the list.
 * @param id ID of the friend to remove.
 */
void Guest::removeFriend(int id) {
    remove(&friends, std::to_string(id));
}

/**
 * Remove a string from a vector of strings.
 * @param vec Vector to modify.
 * @param element Element to remove.
 */
void Guest::remove(std::vector<std::string> *vec, std::string element) {
    vec->erase(std::remove(vec->begin(), vec->end(), element), vec->end());
}

/**
 * Turn a vector of strings into a single string like "[$item1,$item2,...]".
 * @param vec Vector to turn into a string
 * @return Resulting string.
 */
std::string Guest::toString(std::vector<std::string> vec) {
    std::string result = "[";
    if (vec.size() != 0){
        for (int i = 0; i < vec.size()-1; i++){
            result += vec[i] + ", ";
        }
        result += vec.back();
    }
    result += "]";
    return result;
}

int Guest::getId() {
    return id;
}

int Guest::getNumberOfFriends() {
    return friends.size();
}
