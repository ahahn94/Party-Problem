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

#include <iostream>
#include <fstream>
#include <sstream>

#include "Guest.h"
#include "main.h"

/**
 * Program control.
 * @return 0
 */
int main() {
    std::vector<Guest> guestslist;
    guestslist = importFromFile('|', "../res/guests.txt");
    guestslist = party(guestslist, 3);
    for (int i = 0; i < guestslist.size(); i++){
        std::cout << guestslist[i].toString() << std::endl;
    }
    return 0;
}

/**
 * Read guests from the specified file.
 * @param delimiter Separator between values in the files lines.
 * @param filename Name of the file.
 * @return filecontent as a list of guests.
 */
std::vector<Guest> importFromFile(char delimiter, std::string filename) {
    std::vector<Guest> guestslist;
    std::ifstream file (filename);
    std::string line;
    if (file.is_open()){
        while (getline(file, line)){
            std::vector<std::string> parts;
            parts = split(line, '|');
            std::vector<std::string> friends;
            friends = split(parts[3], ',');
            guestslist.push_back(Guest(std::stoi(parts[0]), parts[1], parts[2], friends));
        }
    }
    else {
        std::cout << "Error: \"" + filename + "\" not found!" << std::endl;
    }
    return guestslist;
}

/**
 * Remove guests with friends count < k from the list.
 * @param list List of the guests.
 * @param k Minimum number of friends for each guest.
 * @return Modified list.
 */
std::vector<Guest> party(std::vector<Guest> list, int k) {
    if (list.size() <= k) return std::vector<Guest>{};
    if (k == 0) return list;

    for (int i = 0; i < list.size(); i++){
        if(list[i].getNumberOfFriends() < k){
            int id = list[i].getId();
            list.erase(list.begin() + i);
            for (int j = 0; j < list.size(); j++){
                list[j].removeFriend(id);
            }
            list = party(list, k);
            return list;
        }
    }
    return list;
}

/**
 * Split a string into a vector of strings by a given delimiter.
 * @param text String to split.
 * @param delimiter Separating character.
 * @return Vector of the parts.
 */
std::vector<std::string> split(std::string text, char delimiter) {
    std::vector<std::string> result;
    std::stringstream mystream(text);
    std::string item;
    while (std::getline(mystream, item, delimiter)){
        result.push_back(item);
    }
    return result;
}
