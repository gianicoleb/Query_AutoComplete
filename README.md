
Autocomplete and Recommendation Search using Trie
This code implements a Trie data structure to provide autocomplete suggestions and recommendation search for a given input string. The Trie is initialized with a dictionary of words and then each word is inserted into the Trie to create a path from the first letter to the last. The Trie can then be used to search for a word or autocomplete a prefix. When a search query is made for a word that does not exist in the Trie, it provides the top 3 most similar entries in the Trie using edit distance.

Code
The code consists of the following files:

main.cpp: contains the main function to run the program
Trie.h: contains the class and function declarations for the Trie
Trie.cpp: contains the function definitions for the Trie
Usage
To use the program, simply compile and run the main.cpp file. When prompted, enter a word or prefix to search for. The program will either provide autocomplete suggestions or recommendation search results.

Dependencies
This code requires a C++ compiler and the standard C++ libraries. No additional libraries or dependencies are necessary.
