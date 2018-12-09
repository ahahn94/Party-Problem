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

import {readFileSync} from 'fs';
import {Guest} from "./Guest";

/**
 * Program control.
 */
function main() {
    let filename: string = "guests.txt";
    let k: number = 4;
    let guests: Array<Guest> = readGuestsFromFile(filename);
    guests = party(guests, k);
    if (guests.length > 0) {
        for (let guest of guests) {
            console.log(guest.toString() + "   " + guest.getNumberOfFriends());
        }
    } else {
        console.log("No Guests on the list.");
    }
}

/**
 * Read guests from the specified file.
 * @param filename Name of the desired file.
 */
function readGuestsFromFile(filename: string): Array<Guest> {

    let guests = new Array<Guest>();
    let content = readFileSync(filename).toString();
    for (let line of content.split("\n")) {
        let parts = line.split("|");
        let id: number = Number(parts[0]);
        let name: string = parts[1];
        let surname: string = parts[2];
        let friends: Array<number> = parts[3].split(",").map(Number);
        let guest: Guest = new Guest(id, name, surname, friends);
        guests.push(guest);
    }
    return guests;
}

/**
 * Remove guests with friends count < k from the list.
 * @param guests List of the guests.
 * @param k Minimum number of friends for each guest.
 * @return Modified list.
 */
function party(guests: Array<Guest>, k: number): Array<Guest> {
    if (k == 0) return guests;
    if (guests.length <= k) return new Array<Guest>();

    for (let guest of guests) {
        if (guest.getNumberOfFriends() < k) {
            let id: number = guest.getId();
            let pos: number = guests.indexOf(guest);
            guests.splice(pos, 1);
            for (let guest1 of guests) {
                guest1.removeFriend(id);
            }
            guests = party(guests, k);
            return guests;
        }
    }

    return guests;
}

main();