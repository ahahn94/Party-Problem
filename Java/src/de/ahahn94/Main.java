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

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

/**
 * Main Class.
 */
public class Main {

    static ArrayList<Guest> guests;

    /**
     * Progran controll.
     * @param args Commandline arguments.
     */
    public static void main(String[] args) {
        String filename = "guests.txt";
        int k = 4;
        guests = new ArrayList<>();
        readGuestsFromFile(filename);
        guests = party(guests, k);
        if (guests.size() == 0) {
            System.out.println("No Guests on the list!");
            return;
        }
        for (Guest guest: guests){
            System.out.println(guest.toString());
        }
    }

    /**
     * Read guests from the specified file.
     * @param filename Name of the desired file.
     */
    public static void readGuestsFromFile(String filename){
        try {
            BufferedReader bufferedReader = new BufferedReader(new FileReader(filename));
            try{
                String line;
                while((line = bufferedReader.readLine()) != null){
                    String[] parts = line.split("\\|");
                    int id = Integer.parseInt(parts[0]);
                    String name = parts[1];
                    String surname = parts[2];
                    ArrayList<Integer> friends = new ArrayList<>();
                    parts = parts[3].split(",");
                    for (String s: parts){
                        friends.add(new Integer (Integer.parseInt(s)));
                    }
                    guests.add(new Guest(id, name, surname, friends));
                }
            }catch (IOException e){
                System.out.println("Error while reading from file!");
            }
        } catch (FileNotFoundException e) {
            System.out.printf("File not found!");
            e.printStackTrace();
        }
    }

    /**
     * Remove guests with friends count < k from the list.
     * @param guests List of the guests.
     * @param k Minimum number of friends for each guest.
     * @return Modified list.
     */
    public static ArrayList<Guest> party(ArrayList<Guest> guests, int k){
        if (k == 0) return guests;
        if (guests.size() <= k) return new ArrayList<Guest>();
        for (Guest guest: guests){
            if (guest.getNumberOfFriends() < k){
                int id = guest.getId();
                guests.remove(guest);
                for (Guest guest1: guests){
                    guest1.removeFriend(id);
                }
                guests = party(guests, k);
                return guests;
            }
        }
        return guests;
    }
}
