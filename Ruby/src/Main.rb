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

require './Guest'

def main(minFriendsCount, filename)
  # Program controll.
  guests = readGuestsFromFile(filename, [])
  guests = party(guests, minFriendsCount)
  for guest in guests
    puts guest.toString
  end
end

def readGuestsFromFile(filename, list)
  # Read the guests from the specified file to the given list.
  # @param filename Name of the file with the guests data.
  # @param list List to append new guests to.
  file = File.new(filename, "r")
  while (line = file.gets)
    parts = line.split("|")
    id = parts[0]
    name = parts[1]
    surname = parts[2]
    friendIDs = parts[3].split(",").map(&:to_i)
    list.push(Guest.new(id, name, surname, friendIDs))
  end
  return list
end

def party(list, k)
    #
    # Remove guests with friends count < k from the list.
    # @param list List of the guests.
    # @param k Minimum number of friends for each guest.
    # @return Modified list.
    #
    if (k == 0)
        return list
    end
    if (list.length <= k)
        return []
    end
    for entry in list
      if (entry.friends.length < k)
        id = entry.id
        list.delete(entry)
        for entry1 in list
          entry1.removeFriend(id)
        end
        list = party(list, k)
        return list
      end
    end
    return list
end

main(4, "../../res/guests.txt")