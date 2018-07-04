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

using System.Collections.Generic;
using System.Text;

namespace CSharp
{
    /// <summary>
    /// Implements a data structure for Guests of the type ID, Name, Surname, List of Friends IDs.
    /// </summary>
    public class Guest
    {
        private int id;
        private string name;
        private string surname;
        private List<int> friends;

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="id">Guests ID.</param>
        /// <param name="name">Guests first name.</param>
        /// <param name="surname">Guests last name.</param>
        /// <param name="friends">List of friends IDs.</param>
        public Guest(int id, string name, string surname, List<int> friends)
        {
            this.id = id;
            this.name = name;
            this.surname = surname;
            this.friends = friends;
        }

        /// <summary>
        /// Get a string version of the guests data.
        /// </summary>
        /// <returns>"$ID, $NAME $SURNAME, [$FRIENDS]"</returns>
        public override string ToString()
        {
            string result = id.ToString() + ", " + name + " " + surname + ", " + FriendsToString();
            return result;
        }

        /// <summary>
        /// Get a string version of the list of friends.
        /// </summary>
        /// <returns>"[$friend1, $friend2, ... $friendn]"</returns>
        private string FriendsToString()
        {
            if (friends.Count == 0)
            {
                return "[]";
            }

            StringBuilder result = new StringBuilder();

            result.Append("[");

            for (int i = 0; i < friends.Count; i++)
            {
                if (i > 0)
                {
                    result.Append(" ");
                }

                result.Append(friends[i]);

                if (i != friends.Count - 1)
                {
                    result.Append(",");
                }
            }

            result.Append("]");

            return result.ToString();
        }

        /// <summary>
        /// Remove a friends ID from the list.
        /// </summary>
        /// <param name="friendId">ID of the friend to remove.</param>
        public void RemoveFriend(int friendId)
        {
            friends.Remove(friendId);
        }

        /// <summary>
        /// Get the guests ID.
        /// </summary>
        /// <returns>Guests ID.</returns>
        public int GetId()
        {
            return id;
        }

        /// <summary>
        /// Get the number of the guests friends.
        /// </summary>
        /// <returns>Number of friends.</returns>
        public int GetNumberOfFriends()
        {
            return friends.Count;
        }
    }
}