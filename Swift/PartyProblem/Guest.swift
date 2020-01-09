/*
Copyright (c) 2020 ahahn94
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

import Foundation

/**
 Class that organizes information on guests into objects.
 
 A Guest has:
 - a first name
 - a last name
 - a unique ID
 - a list of friends, represented by their IDs
 */
class Guest: CustomStringConvertible, Equatable {

    // Attributes

    /// First name of the Guest.
    private let firstName: String
    /// Last name of the Guest.
    private let lastName: String
    /// Unique ID of the Guest.
    private let _id: Int
    /// List of the IDs of the Guest|s friends.
    private var friends: [Int]

    /**
     Getter for the private constant _id.
     */
    var id: Int {
        get {
            _id
        }
    }

    /**
     Getter for the number of IDs on the friends list.
     */
    var numberOfFriends: Int {
        get {
            friends.count
        }
    }

    /**
     Get a description of the Guest.
     */
    var description: String {
        "Guest(firstName: \(firstName), lastName: \(lastName), id: \(id), friends: \(friends))"
    }

    /**
     Constructor for a new Guest.
     
     Initializes a new Guest with the provided information.
     - Parameters:
        - firstName: First name of the Guest.
        - lastName: Last name of the Guest.
        - id: Unique ID of the Guest.
        - friends: List of the IDs of the Guest|s friends.
     
     - Returns: A new Guest that contains the provided information.
    */
    init(firstName: String, lastName: String, id: Int, friends: [Int]) {
        self.firstName = firstName
        self.lastName = lastName
        self._id = id
        self.friends = friends
    }

    /**
     Remove a friends ID from the friends list.
     
     - Parameter id: ID of the friend to remove from the list.
     */
    func removeFriend(id: Int) {
        if let index = friends.firstIndex(of: id) {
            friends.remove(at: index)
        }
    }

    /**
     Equality function. Two Guest|s are equal if their IDs match.
     
     - Returns: True if IDs match, else false.
     */
    static func ==(lhs: Guest, rhs: Guest) -> Bool {
        lhs.id == rhs.id
    }

}
