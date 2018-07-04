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

using System;
using System.Collections.Generic;
using System.IO;

namespace CSharp
{
    internal static class Program
    {
        
        /// <summary>
        /// Program control
        /// </summary>
        /// <param name="args">List of the command line arguments.</param>
        public static void Main(string[] args)
        {
            string filename;
            int k;

            if (args.Length == 2)
            {
                filename = args[0];
                k = Convert.ToInt32(args[1]);
                Console.Out.WriteLine("Running program with filename '" + filename + "' and k = " + k);
            }
            else
            {
                Console.Out.WriteLine("Please enter the filename of the guests list:");
                filename = Console.ReadLine();
                Console.Out.WriteLine("Please enter the minimum number of friends 'k':");
                k = Convert.ToInt32(Console.ReadLine());
            }

            List<Guest> guests = ReadGuestsFromFile(filename);

            Console.Out.WriteLine("\nList of guests imported from file '" + filename + "':");

            foreach (Guest guest in guests)
            {
                Console.Out.WriteLine(guest.ToString());
            }

            guests = Party(guests, k);

            Console.Out.WriteLine("\nList of guests with at least k = " + k + " friends:");

            foreach (Guest guest in guests)
            {
                Console.Out.WriteLine(guest.ToString());
            }
        }

        /// <summary>
        /// Read guests from specified file.
        /// </summary>
        /// <param name="filename"></param>
        /// <returns>Filecontent as a list of guest objects.</returns>
        static List<Guest> ReadGuestsFromFile(string filename)
        {
            List<Guest> guests = new List<Guest>();

            string[] lines = File.ReadAllLines(filename);
            foreach (string line in lines)
            {
                string[] parts = line.Split('|');
                int id = Convert.ToInt32(parts[0]);
                string name = parts[1];
                string surname = parts[2];
                List<int> friends = new List<int>();
                foreach (string part in parts[3].Split(','))
                {
                    friends.Add(Convert.ToInt32(part));
                }

                guests.Add(new Guest(id, name, surname, friends));
            }

            return guests;
        }

        /// <summary>
        /// Remove guests with less than k friends from the list.
        /// </summary>
        /// <param name="guests">List of the guests.</param>
        /// <param name="k">Minimum number of friends for each guest.</param>
        /// <returns>Modified list.</returns>
        static List<Guest> Party(List<Guest> guests, int k)
        {
            if (k == 0)
            {
                return guests;
            }

            if (guests.Count <= k)
            {
                return new List<Guest>();
            }

            foreach (Guest guest in guests)
            {
                if (guest.GetNumberOfFriends() < k)
                {
                    int id = guest.GetId();
                    guests.Remove(guest);
                    foreach (Guest guest1 in guests)
                    {
                        guest1.RemoveFriend(id);
                    }

                    guests = Party(guests, k);
                    return guests;
                }
            }

            return guests;
        }
    }
}