//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
        if (size >= 64) {
            cout << "\n Could not insert, too many objects in heap" << endl;
            return;
        }
        data[size] = idx;//Inserts at the next empty index, size - 1 would return the last initialized index
        size++;
        upheap(size - 1, weightArr);
        //Case 1: the heap's size is bigger than or equal to 64, stack overflow because we are going over the max.
        //Probably should only check if its equal to 64, as it would already have an error being greater than 64
        //Case 2: No issues with input so we can push.
        //
        //Later consideration: I assume main.cpp has a filtering for non-alphabetical characters e.g. special symbols and numerical values are cleansed before calling push
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        if (size <= 0) {
          return -1; // -1 serves as a placeholder/indicator for furture debugging
        }
        //At this point can assume heap has 1 or more items
        int rootIndex = data[0];
        data[0] = data[size - 1];
        size--;
        downheap(0, weightArr);//Start downheap from root
        return rootIndex;
        //Case 1: the array is empty
        //Case 2: array is not empty
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        int temp;
        while (pos >= 0 && (data[pos] < weightArr[pos])) {//Comparison, 
          // Checks if the heap is empty, breaks out if so
          //Make sure index is within 0 to 64, the higher bound already checked within push
          // Keeps looping while the child "pos" is less than parent
          
          //start of swap
          temp = data[pos];//Save child's value 
          data[pos] = data[(pos - 1)/2];//Set child to parent
          data[(pos - 1)/2] = temp;//Finalize swap, set parent to child's value
          pos = (pos -1) /2; //Move position alongside swap
        }
        // There is in inbuilt swap() function, but requires additional headers not allowed. <algorithm>
    }
 
    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        if (size <= 0) { //Incase somehow downheap gets called when empty
          cout << "\nHeap is empty" << endl;
          return;
        }

        int temp;
        int smallerChild;
        while (((pos - 1) / 2) < size) { //While the left index is less than the heap's size
          smallerChild = !(((2 * pos) + 1)<((2 * pos) + 2))?((2 * pos) + 1):((2 * pos + 2)); //Ternary operator to check which child is smaller than the other
          if (weightArr[data[pos]] < weightArr[data[smallerChild]]) { //If downheap is completed already, breakout before any swaps occur
            break;
          }

          temp = data[pos]; //save parent value
          data[pos] = data[smallerChild]; //Set parent to child
          data[(2 * pos) + 2] = temp;//Finalize swap
          pos = smallerChild; //update positon's height to to continue check
        }
    //While loop 
    //Check if left child is less than the total size of heap, if it is equal to size of heap it can be assumed to be the smaller child already
    //After check determine if the left or right is smaller, save tat value
    //The Heap might already be completed at this stage, so check if it is already properly sorted
    //If not completed the swap starts between the smaller child and parent, downward
    //Update position to child & restart cycle
    }
};

#endif
