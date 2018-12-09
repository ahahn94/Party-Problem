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

/**
 * Implements a data structure for Guests of the type ID, Name, Surname, List of Friend's IDs.
 */
export class Guest {

    private id: number;
    private name: string;
    private surname: string;
    private friends: Array<number>;

    /**
     * Constructor.
     * @param id Guests ID.
     * @param name Guests first name.
     * @param surname Guests last name.
     * @param friends List of friends IDs.
     */
    public constructor(id: number, name: string, surname: string, friends: Array<number>) {
        this.id = id;
        this.name = name;
        this.surname = surname;
        this.friends = friends;
    }

    /**
     * Remoe a friends ID from the list.
     * @param id ID of the friend to remove.
     */
    public removeFriend(id: number): void {
        let pos = this.friends.indexOf(id);
        if (pos > -1) {
            this.friends.splice(pos, 1);
        }
    }

    /**
     * Get a string of the guests data.
     * @return "$ID, $NAME, $SURNAME, [$FRIENDS]".
     */
    public toString(): string {
        return this.id + ", " + this.name + ", " + this.surname + ", [" + this.friends + "]";
    }

    public getNumberOfFriends(): number {
        return this.friends.length;
    }

    public getId(): number {
        return this.id;
    }
}

