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

class Guest constructor(name: String, surname: String, id: Int, friends: ArrayList<Int>) {


    private var name: String = ""
    private var surname: String = ""
    private var id: Int = 0
    private var friends: ArrayList<Int> = ArrayList()

    /**
     * Initialize the properties with the values from the class header.
     */
    init {
        this.name = name
        this.surname = surname
        this.id = id
        this.friends = friends
    }

    /**
     * Remove a friends ID from the list.
     * @param id ID of the friend to remove.
     */
    fun removeFriend(id: Int) {
        friends.remove(id)
    }

    /**
     * Get a string of the guests data.
     * @return "$ID, $NAME, $SURNAME, [ $FRIENDS ]"
     */
    override fun toString(): String {
        return id.toString() + ", " + name + ", " + surname + ", " + friends
    }

    fun getId(): Int {
        return id
    }

    fun getNumberOfFriends(): Int {
        return friends.size
    }

}