#include "node1.h"
#include "sequence3.h"
#include <cassert>
#include <cstdlib>
namespace main_savitch_5
{
    sequence::sequence(){   //constructor       
        //initialize pointers and vars
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        many_nodes = 0;
    }
    
    sequence::sequence(const sequence& source){    //copy constructor         
        list_copy(source.head_ptr, head_ptr, tail_ptr);  //copy the linked list
        many_nodes = source.many_nodes;
        if (source.cursor == NULL){
            cursor = NULL;
            precursor = NULL;}
        else{
            node* temp = source.head_ptr;
            node* temp2 = head_ptr;
            while (temp != source.cursor){    // Traverse to find corresponding cursor and precursor
                temp = temp -> link();
                temp2 = temp2 -> link();}
            cursor = temp2;
            precursor = cursor -> link();}
    }
    sequence::~sequence(){      // Destructor
        list_clear(head_ptr); //clea the list
        many_nodes = 0;
    }
    
    void sequence::start(){                     
        if(many_nodes != 0){
            cursor = head_ptr;
            precursor = NULL;
        }    
    }
    
    void sequence::advance(){               
        assert(is_item());
        precursor = cursor;
        cursor = cursor -> link();
    }
    void sequence::insert(const value_type& entry){   //insert new node with certian value    
        if (is_item()){
            if (precursor == NULL || cursor == NULL){
                list_head_insert(head_ptr, entry);
                cursor = head_ptr;
                precursor = NULL;
            }
            else{
                list_insert(precursor, entry);
                cursor = precursor -> link();
            }
        }
        else{
            list_head_insert(head_ptr, entry); ///if empty insert at head
            cursor = head_ptr;
            precursor = NULL;
        }
        ++many_nodes;
    }
    void sequence::attach(const value_type& entry){ //new node     
        if (is_item()){
            precursor = cursor;
            list_insert(cursor, entry);
            cursor = cursor -> link();
        }
        else{
            if (head_ptr == NULL){ //insert at end if no curent item
                list_head_insert(head_ptr, entry);
                cursor = head_ptr;
                precursor = NULL;
            }
            else{
                precursor = list_locate(head_ptr, list_length(head_ptr));
                list_insert(precursor, entry);
                cursor = precursor -> link();
            }
        }
        ++many_nodes;
    }
    void sequence::remove_current(){       //remove current 
        assert(is_item());
        if (cursor == head_ptr){
            list_head_remove(head_ptr);
            cursor = head_ptr;
            precursor = NULL;}
        else
        {
            precursor->set_link(cursor->link());
            delete cursor;
            cursor = precursor->link();}
        --many_nodes;
    }
    void sequence::operator=(const sequence& source){  //overloaded assignment operator  
        if (this == &source){
            return;}
        list_clear(head_ptr);
        list_copy(source.head_ptr, head_ptr, tail_ptr);
        many_nodes = source.many_nodes;
        cursor = head_ptr;
        precursor = NULL;
        node* temp = source.head_ptr;
        while(temp != NULL && temp != source.cursor){
            temp = temp -> link();
            precursor = cursor;
            cursor = cursor -> link();}
    }

    sequence::value_type sequence::current() const{         
        if(is_item()){
            return cursor->data();
        }
        else
        {
            return 0;
        }
}
}   