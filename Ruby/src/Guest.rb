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

class Guest

  attr_reader :id, :friends

  def initialize(id, name, surname, friends)
    # Constructor.
    # @param id Guests ID.
    # @param name Guests first name.
    # @param surname Guests last name.
    # @param friends List of the friends IDs.
    @id = id
    @name = name
    @surname = surname
    @friends = friends
  end

  def toString()
    # Get a string of the guests data.
    # @return "$ID, $NAME, $SURNAME, [$FRIENDS]"
  return @id.to_s + ", " + @name + ", " + @surname + ", " + @friends.to_s
  end

  def removeFriend(id)
    # Remove a friends ID from the list.
    # @param id The ID to remove.
    @friends.delete(id)
  end

end