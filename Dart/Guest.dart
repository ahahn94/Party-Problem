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

/// Implements a data structure for Guests of the type ID, Name, Surname, List of Friend's IDs.
class Guest {
  String _name, _surname;
  int _id;
  List<int> _friends;

  /// Constructor.
  /// [id] Guests ID.
  /// [name] Guests first name.
  /// [surname] Guests last name.
  /// [friends] List of friends IDs.
  Guest(this._name, this._surname, this._id, this._friends);

  /// Get a string of the guests data.
  /// Returns "$ID, $NAME, $SURNAME, [$FRIENDS]".
  @override
  String toString() {
    return "$_id, $_name, $_surname, $_friends";
  }

  /// Remove a friends ID from the list.
  /// [id] ID of the friend to remove.
  removeFriend(int id) {
    this._friends.remove(id);
  }

  /// The ID of the guest.
  getId() {
    return _id;
  }

  /// The number of friends of the guest.
  getNumberOfFriends() {
    return _friends.length;
  }
}
