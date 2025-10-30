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
        if (size == 64) {
            cout << "\n Could not insert, too many objects in heap" << endl;
            return;
        }
        weightArr[size] = idx;
        size++;
        //Call upheap 
        upheap(size - 1, weightArr);
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        if (size <= 0) {
          return -1; // -1 serves as a placeholder/indicator for furture debugging
        }
        //At this point can assume heap has 1 or more items
        int rootIndex = weightArr[0];
        weightArr[0] = weightArr[size - 1];
        size--;
        downheap(0, weightArr);
        return rootIndex;
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        int temp;
        while (pos > 0 && (weightArr[pos] < weightArr[(pos - 1) /2])) {
          // Checks if the heap is empty, breaks out if so
          // Make sure index is not root
          // Keeps looping while the child "pos" is less than parent node
          temp = weightArr[pos];
          weightArr[pos] = weightArr[(pos - 1)/2];
          weightArr[(pos - 1)/2] = temp;
        }
    }
 
    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        int temp;
        while(pos > 0 && ((weightArr[pos] > weightArr[(2 * pos) + 1]) || (weightArr[pos] > weightArr[(2 * pos) + 2]))) {
          //Check that the heap is empty or contains a single value does not loop if true
          //Loop while parent is bigger than the left child or the right child
          if (weightArr[pos] > weightArr[(2 * pos) + 1]) { //Check if the parent is larger than the left node
              temp = weightArr[(2 * pos) + 1];
              weightArr[(2 * pos) + 1] = weightArr[pos];
              weightArr[pos] = temp;
          }else { //at this point its safe to assume the right child is smaller than the parent node
              temp = weightArr[(2 * pos) + 2];
              weightArr[(2 * pos) + 2] = weightArr[pos];
              weightArr[pos] = temp;
          }//Same logic as left child, just have to change the index to the right by one.
        }

        //Debug statements for later testing, to ensure things work properly
        if (size == 0) {
          cout << "No items to downheap" << endl;
        }
    }
};

#endif
