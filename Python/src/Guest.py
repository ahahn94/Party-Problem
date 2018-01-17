class Guest:
    """
    Implements a data structure for Guests of the type ID, Name, Surname, List of Friend's IDs
    """


    def __init__(self, id, name, surname, friends):
        """
        Constructor.
        :param id: ID of the guest.
        :param name: First name of the guest.
        :param surname: Last name of the guest.
        :param friends: List of the IDs of the guest's friends.
        """
        self.__id = id
        self.__name = name
        self.__surname = surname
        self.__friends = friends


    def toString(self):
        """
        Get a string of the guests data.
        :return: "$ID, $NAME, $SURNAME, [$FRIENDS]"
        """
        info = str(self.__id) + ", " + self.__name + ", " + self.__surname + ", " + str(self.__friends)
        print(info)


    def removeFriend(self, id):
        """
        Remove a friends ID from the list.
        :param id: ID to remove.
        :return: nothing.
        """
        if (id in self.__friends):
            self.__friends.remove(id)


    def getId(self):
        return self.__id


    def getNumberOfFriends(self):
        return len(self.__friends)