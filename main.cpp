//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {
    // TODO:
    // 1. Create a MinHeap object.
    // 2. Push all leaf node indices into the heap.
    // 3. While the heap size is greater than 1:
    //    - Pop two smallest nodes
    //    - Create a new parent node with combined weight
    //    - Set left/right pointers
    //    - Push new parent index back into the heap
    // 4. Return the index of the last remaining node (root)

    MinHeap tree = MinHeap(); //Satisfy p1
                              //
    for(int i = 0; i < nextFree; i++) { //Satisfy p2, nextFree based on the createLeafNodes() is the number of leafs there are
      tree.push(i, weightArr);
    }

    int leftIndex, rightIndex, parentNode;
    //Create helper function to return the heap size, within heap.h
    // Refactored from small1 & small2 to leftIndex & rightIndex for readability

    //Satisfy p3
    while (tree.sizeHeap() > 1) {
      // 1st condition of p3 satisfied
      leftIndex  = tree.pop(weightArr);
      rightIndex = tree.pop(weightArr);


      // 2nd condition of p3 satisfied
      parentNode = nextFree;
      weightArr[parentNode] = weightArr[leftIndex] + weightArr[rightIndex];//Properly implement weight


      // 3rd condition of p3 satisfied
      leftArr[parentNode] = leftIndex;
      rightArr[parentNode] = rightIndex;


      // 4th condition of p3 satisfied
      tree.push(parentNode, weightArr);
      nextFree++; //<-- update the number of leaf nodes
    }


    //Loop exits leaving size = 0, popping again returns that index's value
    //Satify p4
    int root = tree.pop(weightArr);
    return root;

 
    //tree is the sum of the left & right arrays, so the "weight"
    //left & right arrays are the children
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    // TODO:
    // Use stack<pair<int, string>> to simulate DFS traversal.
    // Left edge adds '0', right edge adds '1'.
    // Record code when a leaf node is reached.

    if (leftArr[root] == -1 && rightArr[root] == -1) {
        // Single-node tree, edge case Mnaju talked about
        codes[charArr[root] - 'a'] = "0";
        return;
    }
    stack<pair<int, string>> huffStack; //Simulate DFS traversal
    huffStack.push(pair<int, string>(root, ""));

    while(!huffStack.empty()) { //Start of pairing assingments
      pair<int, string> huffcode = huffStack.top();
        int index = huffcode.first;
        string huffmanCode = huffcode.second;
      huffStack.pop();


      if (leftArr[index] == -1 && rightArr[index] == -1) { //If the matching letter is found
        codes[charArr[index] - 'a'] = huffmanCode;
      } else {
        //Make a check for left node
        if (leftArr[index] != -1) {
          huffStack.push(pair<int, string>(leftArr[index], huffmanCode + "0"));
        }
        //Make a check for right node
        if (rightArr[index] != -1) {
          huffStack.push(pair<int, string>(rightArr[index], huffmanCode + "1"));
        }
      }
    }
// DO case for single char in a bit
}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}
