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
 Program control.
 
 Loads the guests list from a file and removes all guests from the
 list that have fewer than k friends on the guests list.
 Prints the resulting list or a message if the list is empty.
 
 filePath is the path to the file with the guests list.
 k is the number of friends each guest needs to have to stay on the list.
 */
func main() {
    let filePath = "../res/guests.txt"
    let k = 4

    var guests = importGuestsFromFile(filePath: filePath)
    guests = party(guests: guests, k: k)
    if guests.count == 0 {
        print("No guests on the list.")
    } else {
        for guest in guests {
            print(guest.description)
        }
    }
}

/**
 Imports the initial list of guests from a file.
 
 - Parameter filePath: Path to the file with the list of guests.
 
 - Returns: List of Guest|s read and parsed from the specified file or empty list.
 */
func importGuestsFromFile(filePath: String) -> [Guest] {
    let content = try? String(contentsOfFile: filePath)
    if let lines = content?.split(separator: "\n") {
        let guests: [Guest] = lines.map({ (line) -> Guest in
            let parts = line.split(separator: "|")
            let id = Int(parts[0]) ?? -1
            let firstName = String(parts[1])
            let lastName = String(parts[2])
            let friendsList = parts[3].split(separator: ",").map({ Int($0) ?? -1 })
            let guest = Guest(firstName: firstName, lastName: lastName, id: id, friends: friendsList)
            return guest
        })
        return guests
    }
    return []
}

/**
 Removes all guests from the list that have fewer than k friends on said list.
 
 - Parameter guests: List of Guest|s the algorithm should work on.
 - Parameter k: Number of friends each guest must have on the guests list.
 
 - Returns: Processed list. May be empty.
 */
func party(guests: [Guest], k: Int) -> [Guest] {

    var tmpGuests = guests

    if k == 0 {
        return tmpGuests
    }
    if guests.count <= k {
        return []
    }

    for guest in tmpGuests {
        if guest.numberOfFriends < k {
            let id = guest.id
            if let index = tmpGuests.firstIndex(of: guest) {
                tmpGuests.remove(at: index)
            }
            for guest1 in tmpGuests {
                guest1.removeFriend(id: id)
            }
            tmpGuests = party(guests: tmpGuests, k: k)
            return tmpGuests
        }
    }
    return tmpGuests
}

// Start the main program.
main()
