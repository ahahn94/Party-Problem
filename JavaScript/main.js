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
 *     along with this program.  If not, see <https:www.gnu.org/licenses/>.
 */

var Guest = require("../JavaScript/Guest.js");
var fs = require("fs");

main();

/**
 * Program control.
 */
function main() {
    var filename = "guests.txt";
    var k = 4;
    var guests = readGuestsFromFile(filename);
    guests = party(guests, k);
    if (guests.length !== 0) {
        for (i = 0; i < guests.length; i++) {
            console.log(guests[i].toString());
        }
    } else {
        console.log("No Guests on the list.")
    }

}

/**
 * Read guests from the specified file.
 * @param filename Name of the desired file.
 */
function readGuestsFromFile(filename) {
    var guests = [];
    var content = fs.readFileSync(filename, "utf8");
    var lines = content.split("\n");
    lines.forEach(function (line) {
        var parts = line.split("|");
        var id = parseInt(parts[0]);
        var name = parts[1];
        var surname = parts[2];
        var friends = parts[3].split(",").map(Number);
        var guest = new Guest(id, name, surname, friends);
        guests.push(guest);
    });
    return guests;
}

/**
 * Remove guests with friends count < k from the list.
 * @param guests List of the guests.
 * @param k Minimum number of friends for each guest.
 * @return {List} Modified list.
 */
function party(guests, k) {
    if (k === 0) return guests;
    if (guests.length <= k) return [];
    guests.forEach(function (guest) {
        if (guest.getNumerOfFriends() < k) {
            var id = guest.id;
            var pos = guests.indexOf(guest);
            guests.splice(pos, 1);
            guests.forEach(function (guest1) {
                guest1.removeFriend(id);
            });
            guests = party(guests, k);
            return guests;
        }
    });
    return guests;
}