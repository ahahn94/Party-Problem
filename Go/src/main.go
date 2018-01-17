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

import(
	"fmt"
	"bufio"
	"os"
	"log"
	"strings"
	"strconv"
)

// Program controll.
func main(){
	var guests []*Guest
	guests = importFromFile("guests.txt", guests)

	var newGuests []*Guest
	newGuests = party(guests[0:], 3)

	for _, e := range newGuests{
		fmt.Println(e.info())
	}
}

// Import guests from file.
func importFromFile(filename string, guests  []*Guest) []*Guest{
	file, err := os.Open(filename)
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	for scanner.Scan(){
		parts := strings.Split(scanner.Text(), "|")
		id, err := strconv.Atoi(parts[0])
		name := parts[1]
		surname := parts[2]
		friendsStrings := strings.Split(parts[3], ",")
		var friends []int
		if err !=nil {
			fmt.Println("Error: The guest id provided is not a number!")
		}
		for _, element := range friendsStrings{
			num, err := strconv.Atoi(element)
			friends = append(friends, num)
			if err != nil {
				fmt.Println("Error: An id in the friends list is not a number!")
			}
		}
		guests = append(guests, &Guest{id, name, surname, friends})
	}
	return guests
}

// Remove guests with friends count < k from the list.
func party(guests []*Guest, k int) []*Guest{
	if (k==0){return guests[0:]}
	if (len(guests) <= k) {return make([]*Guest, 0)[0:]}

	for i, e := range guests{
		if (e.getNumberOfFriends() < k){
			id := e.getId()
			guests = append(guests[:i], guests[i+1:]...)
			for _, e1 := range guests{
				e1.removeFriend(id)
			}
			guests = party(guests[0:], k)
			return guests[0:]
		}
	}
	return guests[0:]
}