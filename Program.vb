Imports System



Module Program
    Sub Main(args As String())
        Console.WriteLine("Hello World!")
        Console.Write("Please Enter your name:")
        Dim name = Console.ReadLine()
        Dim currentDate = DateTime.Now
        Console.WriteLine($"Hello,{name}, on {currentDate:d} at{currentDate:t}")
        Console.Write("Press any key to continue...")
        Console.ReadKey(True)
    End Sub
End Module
