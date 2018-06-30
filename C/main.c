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

#include "main.h"

#define DATASIZE 10
#define LISTSIZE 5

/**
 * Program control.
 * @return 0
 */
int main(int argc, char *argv[]) {

    char *filename = malloc(sizeof(char));
    int k;

    if (argc >= 3) {
        filename = argv[1];
        k = (int) strtol(argv[2], NULL, 10);
        printf("Running program with filename '%s' and k = %d\n\n", filename, k);
    } else {
        printf("Please enter the filename of the guests list: \n");
        scanf("%s", filename);
        printf("Please enter the minimum number of friends 'k':\n");
        char *k_as_string = malloc(sizeof(char));
        scanf("%s", k_as_string);
        k = (int) strtol(k_as_string, NULL, 10);
    }


    GArray *guests = import_from_file('|', filename);

    printf("List of guests imported from file '%s':\n", filename);

    for (int i = 0; i < guests->len; ++i) {
        printf("%s\n", guest_to_string(g_array_index(guests, struct guest *, i)));
    }

    guests = party(guests, k);

    printf("\nList of guests with at least k=%d friends:\n", k);

    for (int i = 0; i < guests->len; ++i) {
        printf("%s\n", guest_to_string(g_array_index(guests, struct guest *, i)));
    }

    return 0;
}

/**
 * Turn a line imported from the guests file into a guest.
 * @param string Line from the guests file like "$ID|$NAME|$SURNAME|$FRIEND1,$FRIEND2,..."
 * @return New guest with the data from the string.
 */
Guest *string_to_guest(char *string) {

    char *id_string = malloc(sizeof(char));
    char *name_string = malloc(sizeof(char));
    char *surname_string = malloc(sizeof(char));
    char *friends_string = malloc(sizeof(char));

    // Split into parts.
    id_string = strtok(string, "|");
    name_string = strtok(NULL, "|");
    surname_string = strtok(NULL, "|");
    friends_string = strtok(NULL, "|");

    // Turn ID into an int.
    int id = (int) strtol(id_string, NULL, 10);

    // Turn list of friends IDs into a GArray.
    char *friend_id_string = malloc(sizeof(char));
    GArray *friends = g_array_new(FALSE, FALSE, sizeof(int));
    friend_id_string = strtok(friends_string, ",");
    while (friend_id_string != NULL) {
        char *int_end;
        int x = (int) strtol(friend_id_string, NULL, 10);
        g_array_append_val(friends, x);
        friend_id_string = strtok(NULL, ",");
    }

    Guest *result = new_guest(id, name_string, surname_string, friends);
    return result;
}

/**
 * Read guests from the specified file.
 * @param delimiter Separator between values in the files lines.
 * @param filename Name of the file.
 * @return filecontent as a list of guests.
 */
GArray *import_from_file(char delimiter, char *filename) {
    FILE *data_file;
    data_file = fopen(filename, "r");
    size_t length = 0;

    char *line;

    GArray *guests = g_array_new(FALSE, FALSE, sizeof(struct guest *));

    while (getline(&line, &length, data_file) != -1) {
        Guest *tmp = string_to_guest(line);
        g_array_append_val(guests, tmp);
    }

    fclose(data_file);

    return guests;
}

/**
 * Remove guests with friends count < k from the list.
 * @param list List of the guests.
 * @param k Minimum number of friends for each guest.
 * @return Modified list.
 */
GArray *party(GArray *list, int k) {
    if (list->len <= k) {
        return g_array_new(FALSE, FALSE, sizeof(struct guest *));
    }
    if (k == 0) {
        return list;
    }

    for (int i = 0; i < list->len; ++i) {

        if (guest_get_number_of_friends(g_array_index(list, struct guest *, i)) < k) {

            int id = guest_get_id(g_array_index(list, struct guest *, i));
            g_array_remove_index(list, i);
            for (int j = 0; j < list->len; ++j) {
                guest_remove_friend(g_array_index(list, struct guest *, j), id);
            }

            list = party(list, k);
            return list;
        }

    }

    return list;
}
