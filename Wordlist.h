// Wordlist.h

#pragma once

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : <Jaime Miguel Saraza>
// St.# : <301462218>
// Email: <jms40@sfu.ca>
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////

//
// Do not use any other #includes
//
#include "Wordlist_base.h"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Wordlist : public Wordlist_base
{
    //
    // Use this Node to implement the doubly-linked list for the word list.
    // Don't change it any way!
    //
    struct Node
    {
        string word;
        Node *next;
        Node *prev;
    };

    int indice = 0;
    Node* head;
    Node* tail;
    bool frozen = false;

public:

    Wordlist(){
        head = nullptr;
        tail = nullptr;
        indice = 0;
        frozen = false;
    }

    Wordlist(const Wordlist& other) // copy constructor deep copying a new object
    {   
        Node* newNode = nullptr;

        for(Node* current = other.head; current != nullptr; current = current->next)
        {
            if (current == nullptr)
            {
                newNode = new Node;
                newNode = nullptr;
            }
            else
            {
                newNode = new Node{current->word, nullptr, current};
            }
        }
        if (newNode == nullptr)
        {
            newNode = new Node{"", nullptr, nullptr};   
        }

    }

    Wordlist(const string& filename){
        ifstream file(filename);    // open file 

        if (!file.is_open())    // if file is not open throw an error
        {
            throw runtime_error("\nError opening file\n");
        }
        else
        {
            string word;

            while (file >> word)    // using methods already made, check if the word in the file is inside the node list already 
            {
                    add_word(word); // if word is not inside the node list then add it to the list
                    //we don't have to check if that word is in the list because the add_word() function does that already and does nothing if it encounters a duplicate 
            }
        }
        file.close();   // don't forget to close the file

    }

    
    bool is_frozen() const override{
        return frozen;  // returns whether list object is frozen or not
    }

    bool contains(const string& w) const override {
        for(Node* ptr = head; ptr != nullptr; ptr = ptr->next)
        {
            if (ptr->word == w)
            {
                return true;    // traverses whole list until the word given as the arguement is found
            }
        }
        return false;
    }

    int length() const override {
        return indice;
    }

    string first_word() const {
        return head->word;
    }

    string last_word() const {
        for(Node* ptr = head; ptr != nullptr; ptr = ptr->next)
        {
            if (ptr->next == nullptr)
            {
                return ptr->word; // traverses list until at the end and returns the last word
            }
        }
        return "";

    }


    string get_word(int index) const override{
        int get_word_index = 0;
        if (index >= 0 && index < length())
        {
            for(Node* ptr = head; ptr != nullptr; ptr = ptr->next)
            {
                if(get_word_index == index)
                {
                    return ptr->word;
                }
                else
                {
                    get_word_index++;
                }
            }
        }
        else
        {
            return "\nError\n";
            throw runtime_error("Invalid Index Provided");  
        }
        return "\nError\n";
    }

    void add_word(const string& w) override{
        if (!is_frozen())
        {   
            if(!contains(w)) // if not in list
            {   
                Node* newNode = new Node{w, nullptr, nullptr};
            
                if (head == nullptr)
                {
                    tail = newNode;         // if there are no nodes
                    head = newNode;

                }
                else
                {
                    tail->next = newNode;
                    newNode->prev = tail;
                    tail = newNode;
                }
                
                indice++;     // adds new node if word is not found in list and then increases index by one
                
            }


        }
    }

    void remove_word(const string& w) override{
        if (!is_frozen())
        {
            Node* current = head; 
            while (current != nullptr)
            { 

                if (current->word == w) // if word found 
                { 
                    if (current->prev == nullptr)    // and the node it is the head
                    { 
                        head = current->next;
                        delete current;
                        current = head;
                        indice--;
                    }
                    else if (current->next == nullptr)
                    {
                        tail = current->prev;       // move tail to previous 
                        delete current;         // delete last node
                        current = tail;         // update current
                        indice--;                  // decrease indice
                    }
                    else
                    {           // deleting in the middle of the list
                        current->next->prev = current->prev;
                        current->prev->next = current->next;                 
                        delete current;
                        current = current->next;
                        indice--;

                    }
                }
                else
                {
                        // else: traverse
                    current = current->next;
                }
            }
        }
    }

    vector<string *> get_sorted_index() override{
        this->frozen = true;        // freezing the word list


        Node* current = head;       
        vector<string*> wordPointers; 

        while (current != nullptr){
            wordPointers.push_back(&(current->word));
            current = current->next;
        }

        sort(wordPointers.begin(), wordPointers.end(), [](const string* a, const string* b) {
            return *a < *b;
        }); // sorting the vector lexicographically using comparison method, with the sort function

        return wordPointers;
    }



   ~Wordlist() override{
        Node* current = head;
        while(current->next != nullptr)
        {    
            delete current->prev;
            current = current->next;
        }
        delete current;
        current = nullptr;

        head = nullptr;
        tail = nullptr;
        
    }



    //
    // ... your code goes here ...
    //

    //
    // ... you can write helper methods if you need them ...
    //

}; // class Wordlist

//
// ... you can write helper functions here (or before Wordlist) if you need them
// ...
//