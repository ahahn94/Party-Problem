<?php

/**
 * Implements a data structure for Guests of the type ID,Name,Surname,List of Friend's IDs
 */
class Guest
{

    private $id;
    private $name;
    private $surname;
    public $friends;

    /**
     * Guest constructor.
     * @param $id int Guests ID.
     * @param $name string Guests first name.
     * @param $surname string Guests last name.
     * @param $friends int[] List of friends IDs.
     */
    public function __construct($id, $name, $surname, $friends)
    {
        $this->id = $id;
        $this->name = $name;
        $this->surname = $surname;
        $this->friends = $friends;
    }

    /**
     * Get a string of the guests data.
     * @return string "$ID, $NAME, $SURNAME, [$FRIENDS]"
     */
    public function toString()
    {
        return "$this->id, $this->name, $this->surname, " . implode(",", $this->friends);
    }

    /**
     * Remove a friends ID from the list.
     * @param $id int
     */
    public function removeFriend(int $id)
    {
        if (($key = array_search($id, $this->friends)) !== false) {
            unset($this->friends[$key]);

        }
    }

    public function getId(): int
    {
        return $this->id;
    }

    public function getNumberOfFriends()
    {
        return sizeof($this->friends);
    }

}