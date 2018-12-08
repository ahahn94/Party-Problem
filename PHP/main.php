<?php

require("Guest.php");

main();

/**
 * Program control.
 */
function main()
{
    $filename = "guests.txt";
    $k = 4;
    $guests = readGuestsFromFile($filename);
    $guests = party($guests, $k);
    if (sizeof($guests) != 0) {
        foreach ($guests as $guest) {
            print($guest->toString() . "\n");
        }
    } else {
        print("No Guests on the list.");
    }
}

/**
 * Read guests from the specified file.
 * @param $filename string Name of the desired file.
 * @return Guest[] Filecontent as a list of guests.
 */
function readGuestsFromFile(string $filename)
{
    if (($filecontent = file_get_contents($filename)) !== false) {
        $lines = explode("\n", $filecontent);
        $guests = array();
        foreach ($lines as $line) {
            $parts = explode("|", $line);
            $id = $parts[0];
            $name = $parts[1];
            $surname = $parts[2];
            $friends = explode(",", $parts[3]);
            $guest = new Guest($id, $name, $surname, $friends);
            array_push($guests, $guest);
        }
        return $guests;
    } else {
        return array();
    }
}

/**
 * Remove guests with friends count < k from the list.
 * @param $guests Guest[] List of the guests.
 * @param $k int Minimum number of friends for each guest.
 * @return Guest[] Modified list.
 */
function party($guests, $k)
{
    if ($k == 0) {
        print("k=0");
        return $guests;
    }
    if (sizeof($guests) <= $k) {
        return array();
    }
    foreach ($guests as $guest) {
        if ($guest->getNumberOfFriends() < $k) {
            $id = $guest->getId();
            $pos = array_search($guest, $guests);
            unset($guests[$pos]);
            foreach ($guests as $guest1) {
                $guest1->removeFriend($id);
            }
            $guests = party($guests, $k);
            return $guests;
        }
    }
    return $guests;
}