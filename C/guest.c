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

#include "guest.h"

#define MAX_NAME_SIZE 100

/**
 * Create a new guest and assign values.
 * @param id Guest ID.
 * @param name First name.
 * @param surname Last name.
 * @param friends List of friends IDs.
 * @return New guest.
 */
void *new_guest(int id, char *name, char *surname, GArray *friends) {

    // Allocate memory.
    Guest *new_guest = malloc(sizeof(Guest));
    new_guest->id = malloc(sizeof(int));
    new_guest->name = malloc(sizeof(char) * MAX_NAME_SIZE);
    new_guest->surname = malloc(sizeof(char) * MAX_NAME_SIZE);

    // Bind Data
    *new_guest->id = id;
    strcpy(new_guest->name, name);
    strcpy(new_guest->surname, surname);
    new_guest->friends = friends;

    return new_guest;
}

/**
 * Get the guests ID.
 * @param _self This guest.
 * @return ID.
 */
int guest_get_id(struct guest *_self) {
    return *_self->id;
}

/**
 * Get the number of friends of the guest.
 * @param _self This guest.
 * @return Number of friends.
 */
int guest_get_number_of_friends(struct guest *_self) {
    return _self->friends->len;
}

/**
 * Get a string of the guests data.
 * @param _self This guest.
 * @return "$ID, $NAME $SURNAME, [$FRIENDS]"
 */
char *guest_to_string(struct guest *_self) {
    char *string = malloc(sizeof(char));
    sprintf(string, "%d, %s %s, %s", *_self->id, _self->name, _self->surname, guest_friends_to_string(_self));
    return string;
}

/**
 * Remove a friends ID from the list.
 * @param _self This guest.
 * @param friend_id ID of the friend to remove.
 */
void guest_remove_friend(struct guest *_self, int friend_id) {

    for (int i = 0; i < _self->friends->len; ++i) {
        if (g_array_index(_self->friends, int, i) == friend_id) {
            g_array_remove_index(_self->friends, (guint) i);
            break;
        }
    }

}

/**
 * Get a string of the guests friends list.
 * @param _self This guest.
 * @return "[$FRIENDS]"
 */
char *guest_friends_to_string(struct guest *_self) {
    char *string = malloc(sizeof(char));
    strcpy(string, "\0");   // Init with terminating 0.

    if (_self->friends->len == 0) {
        strcat(string, "[]");
    } else {

        for (int i = 0; i < _self->friends->len; ++i) {
            char *string_from_int = malloc(sizeof(char));
            sprintf(string_from_int, " %d,", g_array_index(_self->friends, int, i));
            strcat(string, string_from_int);
        }

        // Add list signs.
        string[0] = '[';
        string[strlen(string) - 1] = ']';
    }

    return string;
}
