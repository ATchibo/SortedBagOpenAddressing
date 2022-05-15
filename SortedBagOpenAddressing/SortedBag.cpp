#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>

SortedBag::SortedBag(Relation r) : r(r) {
	TABLE_SIZE = 5;
	ciur();

	PRIME = TABLE_SIZE - 1;
	while (isPrime[PRIME] == 1)
		PRIME--;

	keysPresent = 0;

	hashTable = new TComp[TABLE_SIZE];
	elems = new TComp[TABLE_SIZE];

	for (int i = 0; i < TABLE_SIZE; i++)
		hashTable[i] = elems[i] = NULL_TC;
}

void SortedBag::add(TComp e) {
	if (isFull()) {
		resize();
	}

	// hashing
	int probe = hash1(e), offset = hash2(e);

	while (hashTable[probe] != NULL_TC) {
		if (DELETED_TC == hashTable[probe])
			break;                                  
		probe = (probe + offset) % TABLE_SIZE;
	}

	hashTable[probe] = e;

	// inserting
	int i = keysPresent - 1;

	while (i >= 0 && !r(hashTable[elems[i]], hashTable[probe])) {
		elems[i + 1] = elems[i];
		--i;
	}

	elems[i + 1] = probe;
	keysPresent += 1;
}


bool SortedBag::remove(TComp e) {
	for (int i = 0; i < keysPresent; ++i)
		if (hashTable[elems[i]] == e) {
			hashTable[elems[i]] = DELETED_TC;
			while (i < keysPresent - 1) {
				elems[i] = elems[i + 1];
				++i;
			}

			elems[i] = NULL_TC;
			--keysPresent;
			return true;
		}
			
	return false;
}


bool SortedBag::search(TComp elem) const {
	for (int i = 0; i < keysPresent; ++i)
		if (hashTable[elems[i]] == elem)
			return true;
	return false;
}


int SortedBag::nrOccurrences(TComp elem) const {
	int nr = 0;
	for (int i = 0; i < keysPresent; ++i)
		if (hashTable[elems[i]] == elem)
			++nr;

	return nr;
}



int SortedBag::size() const {
	return keysPresent;
}


bool SortedBag::isEmpty() const {
	return keysPresent == 0;
}

void SortedBag::resize() {
	TABLE_SIZE *= 2;
	TComp* tempHt = new TComp[TABLE_SIZE];
	TComp* tempElems = new TComp[TABLE_SIZE];

	for (int i = 0; i < TABLE_SIZE; i++)
		tempHt[i] = tempElems[i] = NULL_TC;

	int tempKp = 0;

	for (int i = 0; i < keysPresent; ++i) {
		TComp e = hashTable[elems[i]];

		int probe = hash1(e), offset = hash2(e);

		while (tempHt[probe] != NULL_TC) {
			if (DELETED_TC == tempHt[probe])
				break;                                  
			probe = (probe + offset) % TABLE_SIZE;
		}

		tempHt[probe] = e;

		// inserting
		int index = tempKp - 1;

		while (index >= 0 && !r(tempHt[tempElems[index]], tempHt[probe])) {
			tempElems[index + 1] = tempElems[index];
			--index;
		}

		tempElems[index + 1] = probe;
		++tempKp;
	}

	delete[] hashTable;
	delete[] elems;

	hashTable = tempHt;
	elems = tempElems;
}

void SortedBag::ciur() {
	isPrime[0] = isPrime[1] = 1;
	for (long long i = 2; i * i <= MAX_SIZE; i++)
		if (isPrime[i] == 0)
			for (long long j = i * i; j <= MAX_SIZE; j += i)
				isPrime[j] = 1;
}


SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}


SortedBag::~SortedBag() {
	delete[] elems;
	delete[] hashTable;
}
