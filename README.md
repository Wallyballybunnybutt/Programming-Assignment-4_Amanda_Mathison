# Programming-Assignment-4_Amanda_Mathison

What does the Program: Colossal Airlines has one plane that has a capacity of 24 seats, where the plane does two flights a day. One inbound and the other outbound. The purpose of this assignment is to create a program that manages seat assignments through different ways, such as deleting a reservation and creating a reservation. This program will use array structures that allow the user to organize, delete, reserve, and view seat availability. This assignment is an extension of module 3 by implementing storage. Before, all the data would be lost as soon as you exit the program but now the information will be saved into a file and can be loaded when using the program.

Describe the Solution: There are several different structures that need to be implemented to make this possible. Each Seat stores a seat number, assignment status, and the first and last name of the passenger. The second level of the menu is the number of empty seats, a list of empty seats, assign a seat, organized alphabetically, and delete a seat assignment. Each input is scanned and then validated to make sure that there are no duplicates in the application. This program will continue until you choose to quit. When the program starts it will atempt to load existing data and if their is no data, it will just load the program. 

Pros: -Each flight has separate seating 
-The menu is very easy to navigate and isn't confusing 
-Overall design is very readable and easier to follow along. I also added some comments for myself when I look back at the program in the future 

Cons: 
-The seat capacity is set at 24 
-Would need to be developed further so people can book inbound and outbound flights at the same time 
-need to be careful when inputting what you want
-You can't read the binary files
-file could become corrupt
