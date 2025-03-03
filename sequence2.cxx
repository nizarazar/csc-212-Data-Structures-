//Name: Nizar Azar
#include <iostream>   
#include <cassert>     
#include <cstdlib>     
#include "sequence2.h" 

using namespace std;

namespace main_savitch_4 {

    // default constructor - can be giving a wanted capacity or it gives a default
    sequence::sequence(size_type initital_capacity) {
        data = new value_type[initital_capacity];
        capacity = initital_capacity;
        used = 0;
        current_index = 0;
    }

    // copy constructor
    sequence::sequence(const sequence& source) {
        data = new value_type[source.capacity];
        capacity = source.capacity;
        used = source.used;
        current_index = source.current_index;
        copy(source.data, source.data + used, data);
    }

    // destructor
    sequence::~sequence() {
        delete[] data;
    }

    void sequence::start( ) {
        current_index = 0;
    }

    bool sequence::is_item( ) const
    {
        return (current_index < used);
    }

    sequence::value_type sequence::current( ) const
    // assert for pre
    {
        assert(is_item( ));
        return data[current_index];
    }

     void sequence::advance( ) {
        // assert for pre
        assert(is_item( ));
        current_index++;
    }
    
    void sequence::resize(size_type new_capacity) {
        value_type* larger_array;
        if (new_capacity == capacity) return; // checks if current size is already the preferred size
        if (new_capacity < used) new_capacity = used; // is preferred size < current sequence??
        larger_array = new value_type[new_capacity];
        copy(data, data + used, larger_array);
        delete [ ] data;
        data = larger_array;
        capacity = new_capacity;
    }

    sequence::size_type sequence::size( ) const
    { 
        return used;
    }

    void sequence::insert(const value_type &entry) {
        // before inserting we have to make sure that there is room for new item
        if(capacity <= used) {
            resize(used+1);
            }
        if (!is_item()) {
            current_index = 0;
            }
        for (size_type i = used; i > current_index; i--) {
            data[i] = data[i - 1];
            }
        data[current_index] = entry;
        used++;
        }

    void sequence::attach(const value_type &entry) {
        if(capacity <= used) {
    resize(used+1);
    }
    if (!is_item()) {
    current_index = used;
    }
    else {
    current_index++;
    for (size_type i = used; i > current_index; i--) {
      data[i] = data[i - 1];
    }
    }
    data[current_index] = entry;
    used++;
    }
    
    void sequence::remove_current( ) {
        // assert for precondition
        size_type i;    
        assert(is_item( ));
        for (i = current_index+1; i < used; i++)
            data[i-1] = data[i];    
        used--;
    }

    void sequence::operator=(const sequence& source) {
        value_type *new_data;
        
        if (this == &source)
            return;
        // if we need to allocate new array
        if (capacity != source.capacity) { 
	    new_data = new value_type[source.capacity];
	    delete [ ] data; // are we able to delete?
	    data = new_data;
	    capacity = source.capacity;
        }
        // Copying the data
        used = source.used;
        current_index = source.current_index;
        copy(source.data, source.data + used, data);
        }
    
}