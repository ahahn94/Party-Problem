Imports System.IO

Module Program
    ''' <summary>
    ''' Program control
    ''' </summary>
    ''' <param name="args">List of the command line arguments.</param>
    Sub Main(args As String())

        Dim filename = "guests.txt"
        Dim k As Short = 4

        Dim guests = readGuestsFromFile(filename)

        guests = party(guests, k)

        If guests.Count > 0
            For Each guest As Guest In guests
                Console.WriteLine(guest.toString())
            Next
        Else
            Console.WriteLine("No Guests on the list!")
        End If
    End Sub

    ''' <summary>
    ''' Read guests from specified file.
    ''' </summary>
    ''' <param name="filename">Name of the file to read from.</param>
    ''' <returns>Filecontent as a list of guest objects.</returns>
    Function readGuestsFromFile(filename As String) As List(Of Guest)
        Dim guests = New List(Of Guest)()
        Dim streamReader As StreamReader
        Dim line As String
        streamReader = New StreamReader(filename)
        line = streamReader.ReadLine()
        Do While Not line Is Nothing
            Dim parts = line.Split("|")
            Dim id = Short.Parse(parts(0))
            Dim name = parts(1)
            Dim surname = parts(2)
            Dim friends As List(Of Short) = parts(3).Split(",").Select(Function(x) Short.Parse(x)).ToList()
            Dim guest = New Guest(id, name, surname, friends)
            guests.Add(guest)
            line = streamReader.ReadLine()
        Loop
        streamReader.Close()
        Return guests
    End Function

    ''' <summary>
    ''' Remove guests with less than k friends from the list.
    ''' </summary>
    ''' <param name="guests">List of the guests.</param>
    ''' <param name="k">Minimum number of friends for each guest.</param>
    ''' <returns>Modified list.</returns>
    Function party(guests As List(Of Guest), k As Short) As List(Of Guest)
        If k = 0
            Return guests
        End If
        If guests.Count <= k
            Return New List(Of Guest)()
        End If
        For Each guest As Guest In guests
            If guest.getNumberOfFriends() < k
                Dim id = guest.Id
                guests.Remove(guest)
                For Each guest1 As Guest In guests
                    guest1.RemoveFriend(id)
                Next
                guests = party(guests, k)
                Return guests
            End If
        Next
        Return guests
    End Function
End Module
