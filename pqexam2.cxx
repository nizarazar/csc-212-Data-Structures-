// FILE: tests10.cxx
// Written by: Michael Main (main@colorado.edu), Oct 20, 1996
// Each function tests part of the PriorityQueue class,
// returning some number of
// points to indicate how much of the test was passed.

#include <iostream>
#include <cstdlib>
#include <string>
#include "pqueue2.h"
using namespace std;

const size_t TESTSIZE = 3000;

// Function to determine if a PriorityQueue is correct.
bool correct(PriorityQueue& test, size_t n, int items[])
// Postcondition: Some tests have been run on the test priority queue.
// If this priority queue has n items, and these items are items[0]
// through items[n-1] (in that order), then the function has printed
// "Test passed." to cout and returned true. Otherwise the function
// has printed "Test failed." to cout and returned false.
// NOTE: If all tests were passed, then the test PriorityQueue has
// also been emptied.
{
    size_t i;
    bool answer = true;
    if (test.size( ) != n)
        answer = false;
    else if (test.is_empty( ) != (n == 0))
        answer = false;
    else
        for (i = 0; answer && (i < n); i++)
	{
            if (items[i] != test.get_front( ))
                answer = false;
        }
    cout << (answer ? "Test passed.\n" : "Test failed.\n") << endl;
    return answer;
}

int compar(const void* ptr1, const void* ptr2)
// Precondition: Neither ptr1 nor ptr2 is NULL.
// Postcondition: The function returns (*ptr2) - (*ptr1), which is useful
// for the quicksort used in test1.
{
    return *static_cast<const int*>(ptr2) - *static_cast<const int*>(ptr1);
}

int test1( )
// Postcondition: A handful of simple tests have been run on the 
// PriorityQueue data type. If all tests are passed, then the function
// returns 100. Otherwise the function returns zero.
{
    PriorityQueue test;
    int items[8] = { 100, 200, 3, 4, 5, 6, 8, 7 };
    int rand_items[TESTSIZE];
    char test_letter = 'A';
    unsigned int i;

    cout << test_letter++ << ". ";
    cout << "Testing size and is_empty for an empty priority queue.";
    cout << endl;
    if (!correct(test, 0, items)) return 0;

    cout << test_letter++ << ". ";
    cout << "Adding one item to the queue, and then testing\n";
    cout << "   is_empty, size, and get_front.";
    cout << endl;
    test.insert(100, 1);
    if (!correct(test, 1, items)) return 0;

    cout << test_letter++ << ". ";
    cout << "Inserting two items (first has higher priority).\n";
    cout << "   Then checking that both items come out correctly.";
    cout << endl;
    test.insert(100, 10);
    test.insert(200, 5);
    if (!correct(test, 2, items)) return 0;

    cout << test_letter++ << ". ";
    cout << "Inserting two items (second has higher priority).\n";
    cout << "   Then checking that both items come out correctly.";
    cout << endl;
    test.insert(200, 5);
    test.insert(100, 10);
    if (!correct(test, 2, items)) return 0;

    cout << test_letter++ << ". ";
    cout << "Inserting eight items with priorities of\n";
    cout << "   8, 10, 4, 3, 7, 6, 9, 5 (in that order)\n";
    cout << "   Then checking that all items come out correctly.";
    cout << endl;
    test.insert(3, 8);
    test.insert(100, 10);
    test.insert(8, 4);
    test.insert(7, 3);
    test.insert(4, 7);
    test.insert(5, 6);
    test.insert(200, 9);
    test.insert(6, 5);
    if (!correct(test, 8, items)) return 0;

    cout << test_letter++ << ". ";
    cout << "Inserting " << TESTSIZE << " random items with random\n";
    cout << "   priorities, and checking that all items come out right.";
    cout << endl;
    for (i = 0; i < TESTSIZE; i++)
    {
        // Insert a bunch of random items, using items themselves as priorities
        rand_items[i] = rand( ) % 100;
        test.insert(rand_items[i], unsigned(rand_items[i]));
    }
    qsort(rand_items, TESTSIZE, sizeof(int), compar); // Sorts from high-low
    if (!correct(test, TESTSIZE, rand_items)) return 0;

    return 100;
}

int test5( )
// Postcondition: A FIFO test has been run on the
// PriorityQueue data type. If the test is passed, then the function
// returns 25. Otherwise the function returns zero.
{
    PriorityQueue test;
    int items[8] = { 100, 200, 3, 4, 5, 6, 8, 7 };

    cout << "Running bonus test for FIFO behavior." << endl;
    cout << endl;
    test.insert(100, 10);
    test.insert(200, 10);
    test.insert(3, 10);
    test.insert(4, 10);
    test.insert(5, 10);
    test.insert(6, 10);
    test.insert(8, 10);
    test.insert(7, 10);
    if (!correct(test, 8, items)) return 0;

    return 25;
}

int main( )
{
 
    cout << "Running priority queue tests:" << endl;
 
    cout << "TEST 1:" << endl;
    if (test1( ) > 0) cout << "Test 1 passed." << endl << endl;
    else cout << "Test 1 failed." << endl << endl; 
 
    cout << "\nTEST 5 (BONUS):" << endl;
    if (test5( ) > 0) cout << "Test 5 passed." << endl << endl;
    else cout << "Test 5 failed." << endl << endl; 

    return 0;

}