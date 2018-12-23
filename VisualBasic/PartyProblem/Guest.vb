''' <summary>
'''     Implements a data structure for Guests of the type ID, Name, Surname, List of Friends IDs.
''' </summary>
Public Class Guest
    Private ReadOnly _id As Short
    Private ReadOnly _name As String
    Private ReadOnly _surname As String
    Private ReadOnly _friends As List(Of Short)

    Public ReadOnly Property Id As Short
        Get
            Return _id
        End Get
    End Property

    ''' <summary>
    '''     Constructor.
    ''' </summary>
    ''' <param name="id">Guests ID.</param>
    ''' <param name="name">Guests first name.</param>
    ''' <param name="surname">Guests last name.</param>
    ''' <param name="friends">List of friends IDs.</param>
    Public Sub New(id As Short, name As String, surname As String, friends As List(Of Short))
        Me._id = id
        Me._name = name
        Me._surname = surname
        Me._friends = friends
    End Sub

    ''' <summary>
    '''     Remove a friends ID from the list.
    ''' </summary>
    ''' <param name="id">ID of the friend to remove.</param>
    Public Sub RemoveFriend(id As Short)
        Me._friends.Remove(id)
    End Sub

    ''' <summary>
    '''     Get a string version of the guests data.
    ''' </summary>
    ''' <returns>"$ID, $NAME $SURNAME, [$FRIENDS]"</returns>
    Public Overrides Function ToString() As String
        Return Me._id.ToString() + ", " + Me._name + ", " + Me._surname + ", [" + String.Join(", ", Me._friends) +
               "]"
    End Function

    ''' <summary>
    '''     Get the number of the guests friends.
    ''' </summary>
    ''' <returns>Number of friends.</returns>
    Public Function GetNumberOfFriends() As Short
        Return Me._friends.Count
    End Function
End Class