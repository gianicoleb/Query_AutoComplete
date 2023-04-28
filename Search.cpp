#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

const int ALPHABET_SIZE = 28;
// Define a Trie class
class Trie {
private:
// Define a TrieNode struct
    struct TrieNode { //Node struct which contains a a child node for each letter of the alphabet
        TrieNode* children[ALPHABET_SIZE];
        bool isEndOfWord;
 // Constructor for TrieNode
        TrieNode() { //constructor to initially set every child node to empty, and bool to false
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                children[i] = nullptr;
            }
            isEndOfWord = false;
        }
 // Destructor for TrieNode
        ~TrieNode() {
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                if (children[i] != nullptr) {
                    delete children[i];
                }
            }
        }
    };

    TrieNode* root; ////pointer to point to first letter in word

public:
 // Constructor for Trie
    Trie() {
        root = new TrieNode(); //new node is created for first letter inserted
    }
 // Destructor for Trie
    ~Trie() {
        delete root;
    }
 //this function inserts every word in the dictionary to the trie to create a path from first letter to last letter.
    //make root=first letter, see if the next letter exists as a child of root, if it doesnt create it, and move current to the next letter in word

    void insert(const std::string& word) {
        TrieNode* current = root; //pointer to point to current letter, which begins at root node(bc its the first letter)
        for (char c : word) {
            int index; 
            if(c == '_') {
                index = ALPHABET_SIZE - 1;
            } else {
                index = c - 'a';
            }
            if (current->children[index] == nullptr) { //check if the next letter in the word currently exists as a child of the current node
                current->children[index] = new TrieNode(); //if it doesnt create a new node and assign it to the child(next letter)
            }
            current = current->children[index]; //make current the node it was pointing to(next letter). now the current node is the next letter
        }
        current->isEndOfWord = true; //after looping through each letter, current points to last letter so change its bool to true
    }
// Search for a word in the Trie
    bool search(const std::string& word) {
        TrieNode* current = root;
        for (char c : word) {
            int index;
            if(c == '_') {
                index = ALPHABET_SIZE - 1;
            } else {
                index = c - 'a';
            }
            if (current->children[index] == nullptr) {
                return false; //if the next letter isnt a child of current node, return false aka theres no more searching to be done
            }
            current = current->children[index];
        }
        return current->isEndOfWord; //if we get all the way through the search word without returning false, signal the last letter as the end of the word.
    }
// Autocomplete words with a given prefix
    std::vector<std::string> autocomplete(const std::string& prefix) {
        std::vector<std::string> results;
        TrieNode* current = root;
          //the user input will be stored in prefix.
       //traverse the tree to see if each letter in prefix lines with with a word
            //functions similarly to search function but traverses user input instead of dictionary word and doesnt alter the isendofword bool
        for (char c : prefix) {
            int index;
            if(c == '_') {
                index = ALPHABET_SIZE - 1;
            } else {
                index = c - 'a';
            }
            if (current->children[index] == nullptr) {
                return results;
            }
            current = current->children[index];
        }
         //if we makeit through the loop that means there is a path in tree the aligns with user input prefix.
            //current will now be pointing to the last letter in the prefix

        dfs(current, prefix, results);
        return results;
    }

private:
 //function for depth first search.
    //from the starting letter, it looks at input, checks if the full input is a word
    void dfs(TrieNode* node, const std::string& prefix, std::vector<std::string>& results) {
        if (node->isEndOfWord) {
            results.push_back(prefix); //checks if full prefix input is a word, and if it is adds it to the result vector
        }
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (node->children[i] != nullptr) {//for each letter in alphabet check if the current node has that letter as a child
                char c = i + 'a'; //if it does exist, assign that letter to char c, add it to the prefix, and redo the traversal
                dfs(node->children[i], prefix + c, results);
            }
        }
    }
};

// Implement a recommendation search. When you search a term that is not in the Trie, recommend the top 3 most similar entries in the Trie:

int editDistance(const std::string& word1, const std::string& word2) {
    int m = word1.size();
    int n = word2.size();
    int dp[m + 1][n + 1];
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0) {
                dp[i][j] = j;
            } else if (j == 0) {
                dp[i][j] = i;
            } else if (word1[i - 1] == word2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + std::min(dp[i][j - 1], std::min(dp[i - 1][j], dp[i - 1][j - 1]));
            }
        }
    }
    return dp[m][n];
}

int main() {
    Trie trie;
    std::ifstream file("Dictionary.txt");
    if (file.is_open()) {
        std::string word;
        while (file >> word) {
            trie.insert(word);
        }
        file.close();
    }

        std::cout << "Please type your search: \n";

    std::string query;
    while (std::getline(std::cin, query)) {
       std::vector<std::string> options = trie.autocomplete(query);
std::cout << "Possible searches include: ";
for (int i = 0; i < options.size(); i++) {
    std::cout << options[i];
    if (i != options.size() - 1) {
        std::cout << ", ";
    }
}
        if (options.empty()) {
            std::vector<std::string> allWords = trie.autocomplete("");
            std::vector<std::pair<int, std::string>> distances;
            for (const std::string& word : allWords) {
                int distance = editDistance(query, word);
                distances.push_back({distance, word});
            }
            std::sort(distances.begin(), distances.end());
           
            for (int i = 0; i < 3; i++) {
                   std::cout << distances[i].second;
        for (int i = 0; i < options.size(); i++) {
                   std::cout << options[i];
                   if (i != options.size() - 1) {
                       std::cout << ", ";
                   }
               }
        std::cout << '\n';
        
    }

    return 0;
}
  }
  }