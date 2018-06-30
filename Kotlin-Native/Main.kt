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

import kotlinx.cinterop.ByteVar
import kotlinx.cinterop.allocArray
import kotlinx.cinterop.memScoped
import kotlinx.cinterop.toKString
import platform.posix.*

fun main(args: Array<String>) {
    var filename = ""
    var k: int32_t = 0

    if (args.size == 2) {
        filename = args[0]
        k = args[1].toInt()
    } else {
        println("Please enter the filename of the guests list:")
        filename = readLine().toString()
        var k_buffer = ""
        println("Please enter the minimum number of friends 'k':")
        k = readLine().toString().toInt()
    }

    printf("Running program with filename '%s' and k = %d\n", filename, k)

    var guests = readGuestsFromFile(filename)

    printf("List of guests imported from file '%s':\n", filename);

    for (guest in guests) {
        println(guest.toString())
    }

    guests = party(guests, k);

    printf("\nList of guests with at least k=%d friends:\n", k);

    for (guest in guests) {
        println(guest.toString())
    }
}

/**
 * Read guests from the specified file.
 * @param filename Name of the desired file.
 * @return List of guests from the file.
 */
private fun readGuestsFromFile(filename: String): ArrayList<Guest> {
    val guests: ArrayList<Guest> = ArrayList()
    val file = fopen(filename, "r")
    try {
        memScoped {
            val buffer_length = 64 * 1024;
            val buffer = allocArray<ByteVar>(buffer_length);
            while (true) {
                val line = fgets(buffer, buffer_length, file)?.toKString()
                if (line == null || line.isEmpty()) {
                    break
                }
                val parts = line.split("|")
                var id = parts[0].toInt()
                val name = parts[1]
                val surname = parts[2]
                val friends_ids: List<String>

                // Last dataset does not contain a newline character.
                if (parts[3].contains("\n")) {
                    friends_ids = parts[3].dropLast(1).split(",")
                } else {
                    friends_ids = parts[3].split(",")
                }

                val friends = ArrayList<int32_t>()

                for (x in friends_ids) {
                    val friend_id = x.toInt()
                    friends.add(friend_id)
                }

                guests.add(Guest(name, surname, id, friends))
            }

        }
    } finally {
        fclose(file)
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