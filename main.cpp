/*
 Created on 2019-02-05.
 Copyright © 2019 Juarez Pistore. All rights reserved.

 =======
 This is the LeetCode problem #215
 The main objective is to develop the Quick Select algorithm.
 =======
 
 Find the kth smallest element in an unsorted array. Note that it is the k-th smallest element in the sorted order, not the k-th distinct element.
 For example, given an array {7,3,1,5}, you want to find the 2nd lowest element. Enter k = 2 and the program will return 3.
 
 Note: For simplicity and focus purpose, I am assuming k is always valid, 1 ≤ k ≤ array's length
 */

#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;

int quickSelect(int A[], int low, int high, int k);
int partition(int A[], int low, int high);
void swap(int A[], int a, int b);
void generateRandomArray(int A[], int SIZE);
void printArray(int A[], int SIZE);
int getPivot(int A[], int low, int high, int mid);
int getInput(int SIZE);
void printSolution(int A[], int SIZE, int k);
void printComparison(int A[], int SIZE);

int main() {
    // Generating array
    srand(time(0));
    const int SIZE = 30;        // Size 30 is large enough to test the quick select algorithm
    int A[SIZE];
    generateRandomArray(A, SIZE);
    printArray(A, SIZE);
    // Getting K as input
    int k = getInput(SIZE);
    // Printing solution (finding the value of the k-th lowest term)
    printSolution(A, SIZE, k);
    // Sorting and printing the array (for comparation purposes only)
    printComparison(A, SIZE);
    return 0;
}//------

// Generates a random array from 1 to 100
void generateRandomArray(int A[], int SIZE) {
    for(int i = 0; i < SIZE; i++)
        A[i] = rand()%100 + 1;      // generates numbers from 1 to 100
}//------

// Prints given array
void printArray(int A[], int SIZE) {
    for(int i = 0; i < SIZE; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
}//------

// Quick Select algorithm, using the idea of a quick sort but stopping whenever the k-th lowest number is found.
int quickSelect(int A[], int low, int high, int k) {
    if (k > 0 && k <= high-low+1) {
        int mid = partition(A, low, high);
        if (mid - low == k - 1)             // when mid is exactly the term we are looking for
            return A[mid];
        else if (mid - low > k - 1)         //  when the term we are looking for is at mid's left-hand side
            return quickSelect(A, low, mid - 1, k); // Pass the left half sub-array
        else                                //  when the term we are looking for is at mid's right-hand side
            return quickSelect(A, mid + 1, high, k - (mid - low + 1 )); // Pass the right half sub-array
    }
    return INT_MAX;     // If any error is detected (not the case so far)
}//------

// Returns the correct pivot position on the sorted array and returns to the quick select function
int partition(int A[], int low, int high) {
    int mid = (low + high) / 2;
    int pivotIndex = getPivot(A, low, high, mid);
    int pivot = A[pivotIndex];
    int first = low;
    swap(A, first, pivotIndex);
    low++;
    while(true){
        while(low <= high && A[high] > pivot) high--;       // This loop approaches the pivot from the array's right-hand side
        while(low <= high && A[low] < pivot) low++;         // This loop approaches the pivot from the array's left-hand side
        if(low >= high) break;                              // Pivot's correct position found!
        if(low < high) {
            swap(A, low, high);                             // swap terms (quick sort requirement)
            low++;
            high--;
        }
    }
    swap(A, first, high);                                   // swap terms (quick sort requirement)
    return high;
}//------

// Returns the index of the best pivot by comparing the first, middle and last elements, returning the index whose value is the median between those three
int getPivot(int A[], int low, int high, int mid) {
    if((A[mid] >= A[low] && A[mid] <= A[high]) ||
       (A[mid] >= A[high] && A[mid] <= A[low])) return mid;
    else if((A[low] >= A[high] && A[low] <= A[mid]) ||
            (A[low] >= A[mid] && A[low] <= A[high])) return low;
    else return high;
}//------

// Swaps 2 items in an array, given their indexes (a and b)
void swap(int A[], int a, int b) {
    int temp = A[a];
    A[a] = A[b];
    A[b] = temp;
}//------

// Gets input (K) from the user
int getInput(int SIZE) {
    cout << "Enter K (between 1 and " << SIZE << "): ";
    int k = 0;
    cin >> k;
    return k;
}//------

// Prints the solution
void printSolution(int A[], int SIZE, int k) {
    cout << "========\n";
    cout << "The Kth lowest term is: " << quickSelect(A, 0, SIZE - 1, k) << endl;
    cout << "========\n";
}//------

// Prints the sorted array, so that the user can analyze the result
void printComparison(int A[], int SIZE) {
    cout << "For comparison purpose, here follows the same array, now sorted: " << endl;
    sort(A, A + SIZE);
    printArray(A, SIZE);
    cout << "========\n";
}//------
