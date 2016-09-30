#ifndef LinkedList_h
#define LinkedList_h
#include <iostream>
#include <vector>
#include <string>

class Node {

public:
	std::string data;
	Node* next;
};

class LinkedList {

private:
	
	Node* head;
	int arrsize;

public:
	//Helper Functions:
	//Deep Copying Linked Lists
	void Copy_List(const LinkedList& List);

	//Returns the length of the list.
	int size() const;

	//helper function to delete all in linked list
	void Clear();

	//======================================================


	LinkedList();

	LinkedList(const LinkedList& List);

	~LinkedList();

	LinkedList& operator=(const LinkedList& List);

	bool insert(std::string input);

	bool remove(std::string input);

	bool search(std::string input) const;
	
	std::vector<std::string> get();
};

#endif
