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

import 'dart:io';
import 'dart:core';
import 'Guest.dart';

/// Main class.
main() {
  String filename = "guests.txt";
  int k = 4;
  List<Guest> guests = readGuestsFromFile(filename);
  if (guests.length > 0) {
    guests = party(guests, k);
    if (guests.length == 0) {
      print("No guests on the list.");
    } else {
      guests.map((Guest g) => g.toString()).forEach(print);
    }
  } else {
    print("Empty list. Can not proceed.");
  }
}

/// Read guests from the specified file.
/// [filename] Name of the desired file.
/// Returns the filecontent as a list of guests.
List<Guest> readGuestsFromFile(String filename) {
  try {
    List<String> fileContents =
        new File(filename).readAsStringSync().split("\n");
    List<Guest> guests = new List();
    for (String line in fileContents) {
      List<String> parts = line.split("|");
      int id = int.parse(parts[0]);
      String name = parts[1];
      String surname = parts[2];
      List<int> friends = parts[3].split(",").map((x) => int.parse(x)).toList();
      guests.add(new Guest(name, surname, id, friends));
    }
    return guests;
  } catch (e) {
    print(e);
    return new List<Guest>();
  }
}

/// Remove guests with friends count < k from the list.
/// [guests] List of the guests.
/// [k] Minimum number of friends for each guest.
/// Returns a list of the guests with at least k friends on the list.
List<Guest> party(List<Guest> guests, int k) {
  if (k == 0) return guests;
  if (guests.length <= k) return new List();
  for (Guest guest in guests) {
    if (guest.getNumberOfFriends() < k) {
      int id = guest.getId();
      guests.remove(guest);
      for (Guest guest1 in guests) {
        guest1.removeFriend(id);
      }
      guests = party(guests, k);
      return guests;
    }
  }
  return guests;
}
