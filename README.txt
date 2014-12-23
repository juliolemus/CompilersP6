Name: Julio Lemus
Perm: 5650569
Email(Google groups): julio165guy@gmail.com
Umail: juliolemus@umail.ucsb.edu

Explanation:

For this project, I first implemented the print function to test my for loops and if statements. I used the nextLabel function provided to make unique labels within my assembly to account for multiple use of the same statments.
After finishing control flow, I worked on the codegeneration's Method Call where I implemented the precall and postreturn. I first pushed in my method's params backwards and then I pushed my local variables in the post return and finally performed a call to the specific label that represents the current function I am trying to call (i also changed the offset of my params to 12 to accomidate the addition of the self pointer). Also, I checked to see if the method wasnt being called by an object, and if it wasn't I pushed in the self pointer on to the stack.

For my Variable and Assignment nodes, I had to modify them to be able to check wether the variables being assigned and allocated where located in the current method or if they were members of the curretn Class. Finally, for inheritance, I took the first option that was provided in the discussion slides and I inserted the local variables of the SuperClass into the symbol table of the child class before it ever inserts any of its own members into the symbol table. I do this by checking whether the current class has a super class name.

The way I handle the methods is obtain the the objectClassName for the object and I use that to check that class's classInfo and if the doesnot exist within the class, I save the sssuper classe's name into a string, and use that string to access the label of that particular class which contains the method we are trying to use. after that, I use call to jump to that function to activate it.
