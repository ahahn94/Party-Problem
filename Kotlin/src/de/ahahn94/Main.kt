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

package de.ahahn94

import java.io.File

object Main {

    @JvmStatic
    fun main(args: Array<String>) {
        val k = 4
        val filename = "guests.txt"
        var guests = readGuestsFromFile(filename)
        guests = party(guests, k)
        if (guests.size == 0) {
            println("No guests on the list!")
        } else {
            for (guest: Guest in guests) {
                println(guest.toString())
            }
        }
    }

    /**
     * Read guests from the specified file.
     * @param filename Name of the desired file.
     * @return List of guests from the file.
     */
    private fun readGuestsFromFile(filename: String): ArrayList<Guest> {
        val guests: ArrayList<Guest> = ArrayList()
        val lines: List<String> = File(filename).readLines()
        for (line in lines) {
            val parts = line.split("|")
            val id = Integer.parseInt(parts[0])
            val name = parts[1]
            val surname = parts[2]
            val friends = ArrayList(parts[3].split(",").map(String::toInt))
            guests.add(Guest(name, surname, id, friends))
        }
        return guests
    }

    /**
     * Remove guests with friends count < k from the list.
     * @param guests List of the guests.
     * @param k Minimum number of friends for each guest.
     * @return Modified list.
     */
    private fun party(guests: ArrayList<Guest>, k: Int): ArrayList<Guest> {
        var tmpGuest = guests
        if (k == 0) return tmpGuest
        if (tmpGuest.size <= k) return ArrayList()
        for (guest in tmpGuest) {
            if (guest.getNumberOfFriends() < k) {
                val id = guest.getId()
                tmpGuest.remove(guest)
                for (guest1 in tmpGuest) {
                    guest1.removeFriend(id)
                }
                tmpGuest = party(tmpGuest, k)
                return tmpGuest
            }
        }
        return tmpGuest
    }

}