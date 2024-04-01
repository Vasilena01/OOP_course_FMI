#pragma once
#include <iostream>


class MultiSet
{
private:
	uint8_t* buckets;
	unsigned N;
	unsigned bucketsCount;
	const unsigned elementsCountInBucket = 4;
	const unsigned maxNumOccurences = 3;

	void copyFrom(const MultiSet& other);
	void free();
public:
	explicit MultiSet(unsigned newN);
	MultiSet(const MultiSet& other);
	const MultiSet& operator=(const MultiSet& other);
	~MultiSet();
	int getBucketIndex(unsigned num) const;
	int getNumOccurences(unsigned num) const;
	void addToMultiSet(unsigned num);
	void addMultipleTimes(unsigned num, int times);
	void removeFromMultiSet(unsigned num);
	MultiSet intersect(const MultiSet& set1, const MultiSet& set2);
	MultiSet unify(const MultiSet& set1, const MultiSet& set2);
	void printMultiSet() const;
};
