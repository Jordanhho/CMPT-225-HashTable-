#include <iostream>
#include <cctype>
#include <stdexcept>
#include <vector>
#include <string>
#include <cstddef>
#include "HashTable.h"

//Helper Functions

//Deep copies a hashtable
void HashTable::deepCopy(const HashTable& original) {
	if (Table != NULL) {
		delete Table;
	}
	currsize = original.size();
	max_size = original.maxsize();
	Table = new LinkedList[max_size];
	for (int i = 0; i< max_size; i++)
		Table[i] = original.Table[i];
}





//Checking if String only contains alphabet letters lower or upper case
bool HashTable::IsAlpha(std::string input) const {
	//Creating a char array then copying data from string to it.
	char * char_Arr = new char[input.size() + 1];
	std::copy(input.begin(), input.end(), char_Arr);
	char_Arr[input.size()] = '\0';

	//Checking if there are non alpha characters in char array. If so, throw invalid argument
	for (int i = 0; i < input.length(); i++) {
		if (std::isalpha(char_Arr[i]) == false) {
			return false;
		}
	}
	return true;
}





// Returns an array location for a given item key.
int HashTable::Hash(std::string input) const {
	if (IsAlpha(input) == false) {
		throw std::invalid_argument("Invalid Argument");
	}
	else {
		char * char_Arr = new char[input.size() + 1];
		std::copy(input.begin(), input.end(), char_Arr);
		char_Arr[input.size()] = '\0';
		for (int i = 0; i < input.length(); i++) {
			char_Arr[i] = std::tolower(char_Arr[i]);
		}
		int length = input.length();
		unsigned long hash = 0;
		unsigned long ascii_value;
		if (length == 1) {
			ascii_value = char_Arr[0] - 96 + 1;
			hash = ascii_value;
			return (hash);
		}
		unsigned long expo_value;
		int count = length - 2;
		int j = 0;
		for (int i = length - 1; i >= 0; i--) {
			expo_value = 37;
			ascii_value = char_Arr[j] - 96;
			j++;
			if (i == 0) {
				expo_value = 1;
			}
			else if (i == 1) {
				expo_value = 37;
			}
			else {
				for (int i = 0; i < count; i++) {
					expo_value = expo_value * 37;
				}
				count--;
			}
			hash = hash + ascii_value * expo_value;
		}
		unsigned long compressed = compress(hash, length);
		return compressed;
	}
}



//find the smallest prime number greater than 2n
int HashTable::FindPrime(int n) const {
	int new_size = n + 1;
	while (1) {
		if (IsPrime(new_size) == true) {
			break;
		}
		new_size++;
	}
	return new_size;
}


//Check if prime number
bool HashTable::IsPrime(int n) const {
	for (int i = 2; i < n; i++) {
		int value = n % i;
		if (value == 0) {
			return false;
		}
	}
	return true;
}



//Compression of Hash number
unsigned long HashTable::compress(unsigned long hash_num, int length) const {
		return hash_num % length;
}




//Returns the vector array for the whole hashtable
std::vector<std::string> HashTable::getArr() const {
	std::vector<std::string> hash_arr;
	for (int i = 0; i < max_size; i++) {
		if (Table[i].size() > 0) {
			std::vector<std::string> temp = (Table[i].get());
			for (int i = 0; i < temp.size(); i++) {
				hash_arr.push_back(temp[i]);
			}
		}
	}
	return hash_arr;
}





//==============================================================================






//Default Constructor: creates default HashTable with size of 101
HashTable::HashTable() {
	Table = new LinkedList[101];
	currsize = 0;
	max_size = 101;
}


//Constructor: creates a hashtable with the size of 2n
HashTable::HashTable(int n) {
	Table = new LinkedList[FindPrime(2 * n)];
	currsize = 0;
	max_size = FindPrime(2 * n);
}


//Constructor with HashTable parameter
HashTable::HashTable(const HashTable& original) {
	deepCopy(original);
}



//Deconstructor of hashtable
HashTable::~HashTable() {
	for (int i = 0; i < max_size; i++) {
		Table[i].Clear();
	}
	delete[] Table;
}


//Operator
HashTable&HashTable :: operator=(const HashTable& original) {
	if (this != &original){
		if (original.Table != NULL)
			delete Table;
		deepCopy(original);
	}
	return *this;
}




// Adds an item to the Hash Table.
bool HashTable::insert(std::string input) {
	if (search(input) == false) {
		int index = Hash(input);
		if (Table[index].insert(input) == true) {
			currsize++;
			return true;
		}
		return false;
	}
	else {
		return false;
	}
}




//Removes an item from hash table if table is not empty
bool HashTable::remove(std::string input) {
	if (search(input) == true) {
		int index = Hash(input);
		if (Table[index].remove(input) == true) {
			currsize--;
			return true;
		}
		return false;
	}
	else {
		return false;
	}
}





//Searches the Hash table for string input
bool HashTable::search(std::string input) const {
	if (IsAlpha(input) == false) {
		throw std::invalid_argument("Invalid Argument");
		return false;
	}
	else {
		//lowers the string parameter then reinsert into hashing function
		std::string lowerinput = input;
		for (int i = 0; lowerinput[i]; i++) {
			lowerinput[i] = tolower(lowerinput[i]);
		}
		int index = Hash(lowerinput);
		if (Table[index].search(lowerinput) == true) {
			return true;
		}
		return false;
	}
}




//Returns current size of Table
int HashTable::size() const {
	return currsize;
}




// Returns the number of locations in the Hash Table.
int HashTable::maxsize() const {
	return max_size;
}




//Returns Lamda, LoadFactor
float HashTable::loadFactor() const {
	return (float)currsize / (float)max_size;
}




//Returns intersection between 2 hashtables Big O Complexity: O(n)
std::vector<std::string> HashTable::intersection(const HashTable& para) {
	std::vector<std::string> first_arr = getArr();
	std::vector<std::string> result;
	for (int i = 0; i < first_arr.size(); i++) {
		if (para.search(first_arr[i]) == true) {
			result.push_back(first_arr[i]);
		}
	}
	return result;
}



//Returns setunion between 2 hashtables Big O Complexity: O(n)
std::vector<std::string> HashTable::setunion(const HashTable& para) {
	std::vector<std::string> first_arr = getArr();
	std::vector<std::string> second_arr = para.getArr();
	std::vector<std::string> result = second_arr;
	for (int i = 0; i < first_arr.size(); i++) {
		if (para.search(first_arr[i]) == false) {
			result.push_back(first_arr[i]);
		}
	}
	return result;
}




//Returns difference between 2 hashtables Big O Complexity: O(n)
std::vector<std::string> HashTable::difference(const HashTable& para) {
	std::vector<std::string> first_arr = getArr();
	std::vector<std::string> result;
	for (int i = 0; i < first_arr.size(); i++) {
		if (para.search(first_arr[i]) == false) {
			result.push_back(first_arr[i]);
		}
	}
	return result;
}






