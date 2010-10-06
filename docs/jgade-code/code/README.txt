Instructions for building the book's code:

Unpack the code bundle into <somedir> that has no spaces:
    <somedir>/BookCode
    
    
Build all examples
    cd <somedir>/BookCode
    make

Makefiles
    BookCode/Makefile - makes everything, do this first
    BookCode/CppUTest/Makefile - makes CppUTest
    BookCode/unity/Makefile - makes examples for chapters 2-4 with Unity tests
    BookCode/CppUTest/Makefile - makes examples for chapters 2-4 with CppUTest tests
    BookCode/t0/Makefile - makes code examples in t0
    BookCode/t1/Makefile - makes code examples in t1
    BookCode/t2/Makefile - makes code examples in t2
    BookCode/t3/Makefile - makes code examples in t3

For eclipse users
    For each Makefile above there is an eclipse directory.  Notice that the BookCode eclipse 
    project also includes all the sub-directories for the other projects.
    Create a workspace in <somedir>, then import each project using:
        File/Import.../General/Existing Project into Workspace

To build a specific code project from the command line
    cd <somedir>/BookCode/t2
    
