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

package main

import (
	"fmt"
	"strconv"
)

// Implements a data structure for Guests of the type ID, Name, Surname, List of Friend's IDs
type Guest struct{
	id int
	name string
	surname string
	friends []int
}

// Get a string of the guests data.
func (self Guest) info() string{
	text := strconv.Itoa(self.id) + ", " + self.name + ", " + self.surname + ", " + fmt.Sprintf("%v", self.friends)
	return text
}

// Remove a friends ID from the list.
func (guest *Guest) removeFriend(id int) {
	for i, other := range guest.friends{
		if other == id {
			guest.friends = append(guest.friends[:i], guest.friends[i+1:]...)
			break
		}
	}
}

func (self Guest) getId() int{
	return self.id
}

func (self Guest) getNumberOfFriends() int{
	return len(self.friends)
}
