#pragma once
#include <iostream>
#include <fstream>
#include "GlobalConstants.h"

class MultiSet
{
public:
	MultiSet();
	MultiSet(unsigned N, unsigned maxBitsCout);
	MultiSet(const MultiSet& other);
	MultiSet(MultiSet&& other) noexcept;
	MultiSet& operator=(const MultiSet& other);
	MultiSet& operator=(MultiSet&& other) noexcept;
	~MultiSet();

	unsigned getBucketIndex(unsigned number) const;
	unsigned getStartIndexInBucket(unsigned number) const;
	unsigned getEndIndexInBucket(unsigned number) const;

	void addToMultiSet(unsigned nmber, unsigned times);
	unsigned getNumberOccurences(unsigned number) const;

	void printMultiSet() const;
	void printMultiSetBits() const;

	void serializeInBinaryFile(const char* fileName);
	static MultiSet deserializeFromBinaryFile(const char* fileName);

	friend MultiSet operator^(const MultiSet& set1, const MultiSet& set2);
	friend MultiSet operator/(const MultiSet& set1, const MultiSet& set2);
	friend MultiSet operator!(const MultiSet& set);
private:
	uint8_t* buckets;
	unsigned N;
	unsigned bucketsCount;
	unsigned maxNumOccurencesInBucket;
	unsigned maxBitsCount;

	void copyFrom(const MultiSet& other);
	void moveFrom(MultiSet&& other);
	void free();
};
