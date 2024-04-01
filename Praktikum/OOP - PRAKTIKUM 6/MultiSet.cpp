#include "MultiSet.h"
#pragma warning (disable : 4996)

//11 01 10 00 | 01 11 01 00 

void MultiSet::copyFrom(const MultiSet& other)
{
	N = other.N;
	bucketsCount = other.bucketsCount;
	buckets = new uint8_t[bucketsCount];
	for (int i = 0; i < bucketsCount; i++)
	{
		buckets[i] = other.buckets[i];
	}
}

void MultiSet::free()
{
	delete[] buckets;
}

// Big 4

MultiSet::MultiSet(unsigned newN)
{
	N = newN;
	bucketsCount = (N / 4) + 1;
	buckets = new uint8_t[bucketsCount]{0};
}

MultiSet::MultiSet(const MultiSet& other)
{
	copyFrom(other);
}

const MultiSet& MultiSet::operator=(const MultiSet& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

MultiSet::~MultiSet()
{
	free();
}

// Additional functions
int MultiSet::getBucketIndex(unsigned num) const
{
	return (num / 4) + 1;
}

void MultiSet::addToMultiSet(unsigned num)
{
	int occurences = getNumOccurences(num);
	if (num < N && occurences < 3)
	{
		int mask = 3;
		int bucketIndex = getBucketIndex(num);
		int positionInBucket = 2*(3 - (num % 4)); // from left to right
		occurences += 1;

		mask <<= positionInBucket;
		buckets[bucketIndex - 1] &= ~mask;
		occurences <<= positionInBucket;
		buckets[bucketIndex - 1] |= occurences;
	}
}

void MultiSet::addMultipleTimes(unsigned num, int times)
{
	if (times > maxNumOccurences)
		times = maxNumOccurences;

	for (int i = 0; i < times; i++)
		addToMultiSet(num);
}

void MultiSet::removeFromMultiSet(unsigned num)
{
	int occurences = getNumOccurences(num);

	if (num < N && occurences != 0)
	{
		int mask = 3;
		int bucketIndex = getBucketIndex(num);
		int positionInBucket = 2 * (3 - (num % 4)); // from left to right

		occurences -= 1;

		mask <<= positionInBucket;
		buckets[bucketIndex - 1] &= ~mask;
		occurences <<= positionInBucket;
		buckets[bucketIndex - 1] |= occurences;
	}
}

int MultiSet::getNumOccurences(unsigned num) const
{
	if (num > N)
		return false;

	int bucketIndex = getBucketIndex(num);
	int positionInBucket = 2*(3 - (num % 4)); // from left to right

	int mask = 3;

	mask <<= positionInBucket;
	mask &= buckets[bucketIndex-1];
	mask >>= positionInBucket;
	return mask;
}

MultiSet MultiSet::intersect(const MultiSet& set1, const MultiSet& set2)
{
	int sizeOfResultSet = std::min(set1.N, set2.N);
	MultiSet resultSet(sizeOfResultSet);

	for (int i = 0; i < sizeOfResultSet; i++)
	{
		int occurencesInSet1 = set1.getNumOccurences(i);
		int occurencesInSet2 = set2.getNumOccurences(i);

		if (occurencesInSet1 > 0 && occurencesInSet2 > 0)
		{
			int minCountOfOccurences = std::min(occurencesInSet1, occurencesInSet2);
			resultSet.addMultipleTimes(i, minCountOfOccurences);
		}
	}

	return resultSet;
}

MultiSet MultiSet::unify(const MultiSet& set1, const MultiSet& set2)
{
	int sizeOfResultSet = std::max(set1.N, set2.N);
	MultiSet resultSet(sizeOfResultSet);

	for (int i = 0; i < sizeOfResultSet; i++)
	{
		int occurencesSum = set1.getNumOccurences(i) + set2.getNumOccurences(i);

		if (occurencesSum > 3)
			occurencesSum = 3;

		resultSet.addMultipleTimes(i, occurencesSum);
	}

	return resultSet;
}

void MultiSet::printMultiSet() const
{
	std::cout << '{' << std::endl;
	for (int i = 0; i < N; i++)
	{
		int bucketIndex = getBucketIndex(i);
		int occurencesOfI = getNumOccurences(i);
		if(occurencesOfI != 0)
		{
			std::cout << "The number " << i <<  " is in bucket " << bucketIndex <<  " and appears " << occurencesOfI << " times" << std::endl;
		}
	}
	std::cout << '}';
}

int main()
{
	MultiSet set(10);
	set.addToMultiSet(3);
	set.addToMultiSet(3);
	set.addToMultiSet(7);
	set.addToMultiSet(9);
	set.addToMultiSet(5);		
	set.addToMultiSet(5);	
	set.addToMultiSet(6);
	set.removeFromMultiSet(5);
	set.printMultiSet();

	MultiSet set2(8);
	set2.addToMultiSet(3);
	set2.addToMultiSet(4);
	set2.addToMultiSet(3);
	set2.addToMultiSet(6);
	set2.addToMultiSet(7);
	set2.printMultiSet();

	MultiSet intersectionSet(0);
	intersectionSet  = set.intersect(set, set2);
	intersectionSet.printMultiSet();

	MultiSet unifySet(0);
	unifySet = set.unify(set, set2);
	unifySet.printMultiSet();
}