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

#ifndef C_GUEST_H
#define C_GUEST_H

#include <glib.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct guest {

    /*
     * Dataobjects.
     */

    int *id;
    char *name;
    char *surname;
    GArray *friends;

} Guest;

void *new_guest(int id, char *name, char *surname, GArray *friends);

int guest_get_id(struct guest *_self);

int guest_get_number_of_friends(struct guest *_self);

char *guest_to_string(struct guest *_self);

void guest_remove_friend(struct guest *_self, int friend_id);

char *guest_friends_to_string(struct guest *_self);

#endif //C_GUEST_H
