#pragma once
#include <bitset>
#include <vector>
//DO NOT INCLUDE SORTEDBAGITERATOR

//DO NOT CHANGE THIS PART
typedef int TComp;
typedef TComp TElem;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TCOMP -11111;

#define MAX_SIZE 10001

class SortedBagIterator;

class SortedBag {
	friend class SortedBagIterator;

private:
	//TODO - Representation
	Relation r;

	int TABLE_SIZE;
	int keysPresent;
	int PRIME;
	TComp* hashTable;
	bool isPrime[MAX_SIZE];

	TComp* elems;
	const TComp NULL_TC = -11111;
	const TComp DELETED_TC = -11111;

	inline int hash1(TComp value) { while (value < 0) value += TABLE_SIZE;  return value % TABLE_SIZE; }

	inline int hash2(TComp value) { while (value < 0) value += PRIME; return PRIME - (value % PRIME); }

	inline bool isFull() { return (keysPresent*2 >= TABLE_SIZE); }

public:
	//constructor
	SortedBag(Relation r);

	//adds an element to the sorted bag
	void add(TComp e);

	//removes one occurence of an element from a sorted bag
	//returns true if an eleent was removed, false otherwise (if e was not part of the sorted bag)
	bool remove(TComp e);

	//checks if an element appearch is the sorted bag
	bool search(TComp e) const;

	//returns the number of occurrences for an element in the sorted bag
	int nrOccurrences(TComp e) const;

	//returns the number of elements from the sorted bag
	int size() const;

	//returns an iterator for this sorted bag
	SortedBagIterator iterator() const;

	//checks if the sorted bag is empty
	bool isEmpty() const;

	void resize();

	void ciur();

	//destructor
	~SortedBag();
};