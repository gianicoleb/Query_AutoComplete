# Query Autocomplete and Recommendation System

I created this project to gain a deeper understanding and get a better grasp on Trie structures, while also exploring the practical application of it in query autocomplete systems.

## Introduction

This program provides a robust query autocomplete feature. When users input a prefix, the system scans its dictionary to offer potential word completions. Furthermore, if a query doesn't find any direct matches in our dictionary, the system recommends the top 3 most similar entries based on an edit distance algorithm.

## Features:

### 1. Trie-based Autocompletion

Our autocomplete system utilizes a Trie (prefix tree) for efficient word retrieval, making the process of finding words with a common prefix fast and resource-efficient.

### 2. Edit Distance Recommendations

For unmatched queries, the program computes the edit (Levenshtein) distance between the query and all words in the dictionary, recommending the closest matches.

## Code Breakdown:

- **Trie Class:** 
  - The backbone of the program, it includes the inner `TrieNode` struct which represents each node in the Trie. Each node can have as many children as there are letters in our alphabet (including an underscore). 
  - Main methods include:
    - `insert()`: Inserts a word into the Trie.
    - `search()`: Searches for a word in the Trie.
    - `autocomplete()`: Finds words that start with the given prefix.

- **DFS (Depth-First Search):** 
  - Used in conjunction with the `autocomplete` method to traverse the Trie and gather all words that share the given prefix.

- **Edit Distance Function:** 
  - Computes the edit distance between two strings, allowing us to find the closest matches to a given query when no direct matches are found.

## Usage:

1. Load the dictionary file named `Dictionary.txt` with one word per line.
2. Run the main program.
3. Enter a search query.
4. The program will display potential matches or, if none are found, it will recommend the three closest words from the dictionary.
