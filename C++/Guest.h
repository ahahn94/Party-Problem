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

#ifndef PARTYPROBLEM_PERSON_H
#define PARTYPROBLEM_PERSON_H

#include <string>
#include <vector>

class Guest {

private:
    int id;
    std::string name, surname;
    std::vector<std::string> friends;

public:
    Guest(int id, std::string surname, std::string name, std::vector<std::string> friends);
    Guest();
    int getId();
    int getNumberOfFriends();
    std::string toString();
    void removeFriend(int id);
    std::string toString(std::vector<std::string> vec);
    void remove(std::vector<std::string> *vec, std::string element);
};


#endif //PARTYPROBLEM_PERSON_H
