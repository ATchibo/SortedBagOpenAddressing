#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	index = 0;
}

TComp SortedBagIterator::getCurrent() {
	if (!valid())
		throw std::exception();

	return bag.hashTable[bag.elems[index]];
}

bool SortedBagIterator::valid() {
	return index < bag.keysPresent;
}

void SortedBagIterator::next() {
	if (!valid())
		throw std::exception();
	++index;
}

void SortedBagIterator::first() {
	index = 0;
}

