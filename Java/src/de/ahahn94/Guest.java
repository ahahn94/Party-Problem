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

package de.ahahn94;

import java.util.ArrayList;

/**
 * Implements a data structure for Guests of the type ID,Name,Surname,List of Friend's IDs
 */
public class Guest {

    private String name, surname;
    private int id;
    private ArrayList<Integer> friends;

    /**
     * Constructor.
     * @param id Guests ID.
     * @param name Guests first name.
     * @param surname Guests last name.
     * @param friends List of friends IDs.
     */
    public Guest(int id, String name, String surname, ArrayList<Integer> friends) {
        this.name = name;
        this.surname = surname;
        this.id = id;
        this.friends = friends;
    }

    /**
     * Remove a friends ID from the list.
     * @param id ID of the friend to remove.
     */
    public void removeFriend(int id){
        friends.remove(new Integer(id));
    }

    /**
     * Get a string of the guests data.
     * @return "$ID, $NAME, $SURNAME, [$FRIENDS]"
     */
    @Override
    public String toString(){
        return id + ", " + name + ", " + surname + ", " + friends;
    }

    public int getId(){
        return id;
    }

    public int getNumberOfFriends(){
        return friends.size();
    }

}
