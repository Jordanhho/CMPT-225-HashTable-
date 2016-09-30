#pragma once
#ifndef HashTable_h
#define HashTable_h
#include "LinkedList.h"

class HashTable {

private:

	//linked list table
	LinkedList * Table;

	//number of items in array
	int currsize;  

	//Deep copies a hashtable
	void deepCopy(const HashTable& original);

	//size of array
	int max_size; 

	// Returns an array location for a given item key.
	int Hash(std::string input) const;

	bool IsAlpha(std::string input) const;

	int FindPrime(int n) const;

	bool IsPrime(int n) const;

	unsigned long compress(unsigned long hash_num, int length) const;



public:
	//Helper Function to return a vector array of all strings in that linked list
	std::vector<std::string> getArr() const;

	HashTable();

	HashTable(int n);

	HashTable(const HashTable& para);

	~HashTable();

	HashTable& operator=(const HashTable& original);

	bool insert(std::string input);

	bool remove(std::string input);

	bool search(std::string input) const;

	int size() const;

	int maxsize() const;

	float loadFactor() const;

	std::vector<std::string> intersection(const HashTable& para);

	std::vector<std::string> setunion(const HashTable& para);

	std::vector<std::string> difference(const HashTable& para);
};
#endif
