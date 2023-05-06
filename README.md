# specialList-and-special-Compression-AsciiArt-System
A linked List and Compression System using our Special Linked List with c language 

implementing A linked list with the following methods:

N- represent number of chars from the input, at my implementation each consecutive identical chars consume one NODE.

1)RLEListCreate()- making an empty Linked list with O(1)

2)RLEListDestroy(RLEList list)- deleting the list with O(N)

3)RLEListAppend(RLEList list, char value)- adding new char to the end of the list with O(1)

4)RLEListSize(RLEList list)- returning number of all chars in the list with O(N)

5)RLEListRemove(RLEList list, int index)- removing char at given index with O(N)

6)RLEListGet(RLEList list, int index, RLEListResult *result)- returning an char at given index and give information if succed or not int result parameter with O(N)

7)RLEListMap(RLEList list, MapFunction map_function)- the function gets a pointer to a function and apply the function on each char in the list with O(N)

8)RLEListExportToString(RLEList list, RLEListResult* result)- returning all the chars in the list in string in format:
                     <char >< number of consecutive apperance >
                     <char >< number of consecutive apperance >
                     
                     
In addition there is a code  that takes a File and stores it in the special linked list as above so we can use less space
the functions:

1)RLEList asciiArtRead(FILE* in_stream)- the function reads the file and saves it as the special list method.

2)RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)- the function prints the real file that was given.

3)RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)- the function print the given file in the special linked list method into another file
