#
# Copyright (C) 2018  ahahn94
#     This program is free software: you can redistribute it and/or modify
#     it under the terms of the GNU General Public License as published by
#     the Free Software Foundation, either version 3 of the License, or
#     (at your option) any later version.
#
#     This program is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#     GNU General Public License for more details.
#
#     You should have received a copy of the GNU General Public License
#     along with this program.  If not, see <https://www.gnu.org/licenses/>.
#

from Guest import Guest


def readGuestsFromFile(filename, list):
    """
    Read the guests from the specified file to the given list.
    :param filename: Name of the file with the guests data.
    :param list: List to append new guests to.
    :return: Guests list.
    """
    file = open(filename, "r")
    for line in file:
        string = line.rstrip().split("|")
        id = int(string[0])
        name = string[1]
        surname = string[2]
        friends = [int(x) for x in string[3].split(",")]
        list.append(Guest(id, name, surname, friends))
    return list


def party(list, k):
    """
    Remove guests with friends count < k from the list.
    :param list: List of the guests.
    :param k: Minimum number of friends for each guest.
    :return: Modified list.
    """
    if (k == 0):
        return list
    if (len(list) <= k):
        return []

    for entry in list:
        if (entry.getNumberOfFriends() < k):
            id = entry.getId()
            list.remove(entry)
            for entry1 in list:
                entry1.removeFriend(id)
            list = party(list, k)
            return list
    return list


def Main(minFriendsCount, filename):
    """
    Program controll.
    :param minFriendsCount: Minimum number of friends for each guest.
    :param filename: Name of the file containing the guests data.
    :return: nothing.
    """
    guests = readGuestsFromFile(filename, [])
    guests = party(guests, minFriendsCount)
    for guest in guests:
        guest.toString()


# Entry point
Main(3, "guests.txt")
