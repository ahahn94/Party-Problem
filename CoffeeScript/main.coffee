###
Copyright (C) 2019  ahahn94
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https:www.gnu.org/licenses/>.
###

# Required for reading the file with the guests list.
fs = require 'fs'

###
  Implements a data structure for Guests of the type ID, Name, Surname, List of Friend's IDs.
###
class Guest

  ###
  Constructor.
  firstName Guests first name.
  lastName Guests last name.
  id Guests ID.
  friends List of the friends IDs.
  ###
  constructor: (
    @firstName, # Guests first name.
    @lastName, # Guests last name.
    @id, # Guests ID.
    @friends # List of friends IDs.
  ) ->

  ###
  Get a string of the guests data.
  return "$firstName, $lastName, $id, [$friends]".
  ###
  toString: () -> return "#{this.firstName}, #{this.lastName}, #{this.id}, [#{this.friends}]"

  ###
  Remove a friends ID from the list.
  id ID of the friend to remove from the list.
  ###
  removeFriend: (id) ->
    index = this.friends.indexOf(id)
    if index != -1
      this.friends.splice(index, 1)

  ###
  Get the number of friends which are on the guests list.
  ###
  getNumberOfFriends: () -> return this.friends.length

###
Read guests from the specified file.
filePath Path to the file.
encoding Encoding of the file.
return Array of Guests from the file.
###
readGuestsFromFile = (filePath, encoding) ->
  # Read data from file.
  content = fs.readFileSync(filePath, encoding)
  guests = []
  # Split into lines.
  lines = content.split("\n")
  lines.forEach((line) ->
    # Parse lines into Guests.
    parts = line.split("|")
    id = parseInt(parts[0])
    firstName = parts[1]
    lastName = parts[2]
    friends = parts[3].split(",").map(Number)
    guest = new Guest(firstName, lastName, id, friends)
    guests.push(guest)
  )
  return guests

###
Remove guests with friends count < k from the list.
guests List of the guests.
k Minimum number of friends for each guest.
return Modified list.
###
party = (guests, k) ->
  if k == 0
    return guests
  if guests.length <= k
    return []
  guests.forEach((guest) ->
    if guest.getNumberOfFriends() < k
      id = guest.id
      index = guests.indexOf(guest)
      guests.splice(index, 1)
      guests.forEach((guest1) ->
        guest1.removeFriend(id)
      )
      guests = party(guests, k)
      return guests
  )
  return guests

###
Program control.
###
main = () ->
  filePath = "../res/guests.txt"
  encoding = "utf8"
  k = 4
  guests = readGuestsFromFile(filePath, encoding)
  guests = party(guests, k)
  if guests.length != 0
    console.log(guests.map (x) -> x.toString())
  else
    console.log("No Guests on the list")

main()