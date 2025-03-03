// FILE: pqueue2.cxx
// IMPLEMENTS: PriorityQueue (See pqueue2.h for documentation.)

// NOTE: You will need -lm at the end of your compile line to pick up the math library!

// INVARIANT for the PriorityQueue Class:
// 1. The member variable many_items is the number of items in the PriorityQueue.
// 2.The items themselves are stored in the member variable heap, which is a partially filled array organized to follow the usual heap storage rules from Chapter 11 of the class notes.

// NOTE: Private helper functions are implemented at the bottom of this file along with their precondition/postcondition contracts.

#include <cassert>    // Provides assert function
#include <iomanip>    // Provides setw
#include <iostream>   // Provides cin, cout
#include <cmath>      // Provides log2
#include "pqueue2.h"
using namespace std;

PriorityQueue::PriorityQueue( )
{
    many_items = 0;
}

void PriorityQueue::insert(const Item& entry, unsigned int priority)
{
    //ensure there is space in the heap
    assert(size()<CAPACITY);

    //insert new item at end of heap
    heap[many_items].data = entry;
    heap[many_items].priority = priority;
    size_t i = many_items;
    many_items+=1;

    //adjust the heap
      while(i > 0 && (heap[i].priority>parent_priority(i)))
    {
        size_t j = parent_index(i);
        swap_with_parent(i);
        i = j;
    }
}

PriorityQueue::Item PriorityQueue::get_front( )
{
    //ensure heap not empty
    assert(size( ) > 0);

    //get the front item
    Item r = heap[0].data;

    //replace the root with the last item
    size_t i = 0;
    heap[i].data = heap[many_items-1].data;
    heap[i].priority = heap[many_items-1].priority;
    many_items-=1;

    //if heap is not empty, adjust it
    if(many_items>0)
    {while(!(is_leaf(i)) &&
        heap[i].priority<big_child_priority(i))
        {   size_t j = big_child_index(i);
            swap_with_parent(big_child_index(i));
            i = j;}
    }
    return r;
}

bool PriorityQueue::is_leaf(size_t i) const
// Precondition: (i < many_items)
// Postcondition: If heap[i] has no children in the heap, then the function returns true. Otherwise the function returns false.
{
    if((2*i+1)>=many_items)  return 1;
    else return 0;
}

size_t PriorityQueue::parent_index(size_t i) const
// Precondition: (i > 0) && (i < many_items)
// Postcondition: The return value is the index of the parent of heap[i].
{
    assert((i > 0) && (i < many_items));
    return ((i-1)/2);
}

unsigned int PriorityQueue::parent_priority(size_t i) const
// Precondition: (i > 0) && (i < many_items)
// Postcondition: The return value is the priority of the parent of heap[i].
{
    assert((i > 0) && (i < many_items));
    return (heap[(i-1)/2].priority);
}

size_t PriorityQueue::big_child_index(size_t i) const
// Precondition: !is_leaf(i)
// Postcondition: The return value is the index of one of heap[i]'s children. This is the child with the larger priority.
{
    assert(!(is_leaf(i)));
    if(((2*i+2)<many_items) && (heap[2*i+1].priority<heap[2*i+2].priority))
        return (2*i+2);
    else return (2*i+1);
}

unsigned int PriorityQueue::big_child_priority(size_t i) const
// Precondition: !is_leaf(i)
// Postcondition: The return value heap[big_child_index(i)].priority
{
    assert(!(is_leaf(i)));
    return (heap[big_child_index(i)].priority);
}

void PriorityQueue::swap_with_parent(size_t i)
// Precondition: (i > 0) && (i < many_items)
// Postcondition: heap[i] has been swapped with heap[parent_index(i)]
{
    assert((i > 0) && (i < many_items));
    Item d = heap[i].data;
    unsigned int p = heap[i].priority;

    heap[i].data = heap[parent_index(i)].data;
    heap[i].priority = heap[parent_index(i)].priority;

    heap[parent_index(i)].data = d;
    heap[parent_index(i)].priority = p;
}