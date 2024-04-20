#include "MultiSet.h"
#pragma warning (disable : 4996)

// Homework 2
// Zad 1
// Vasilena Stanoyska
// fn: 4MI0600290

// Big 6
void MultiSet::copyFrom(const MultiSet& other)
{
	buckets = new uint8_t[other.bucketsCount];
	bucketsCount = other.bucketsCount;

	for (int i = 0; i < bucketsCount; i++)
		buckets[i] = other.buckets[i];

	maxNumOccurencesInBucket = other.maxNumOccurencesInBucket;
	N = other.N;
}

void MultiSet::moveFrom(MultiSet&& other)
{
	buckets = other.buckets;
	other.buckets = nullptr;

	maxNumOccurencesInBucket = other.maxNumOccurencesInBucket;
	other.maxNumOccurencesInBucket = 0;

	N = other.N;
	other.N = 0;
}

void MultiSet::free()
{
	delete[] buckets;
	buckets = nullptr;
	bucketsCount = 0;
	maxNumOccurencesInBucket = 0;
	N = 0;
}

MultiSet::MultiSet()
{
	N = 0;
	bucketsCount = 0;
	maxNumOccurencesInBucket = 0;
	maxBitsCount = 0;
	buckets = nullptr;
}

MultiSet::MultiSet(unsigned N, unsigned maxBitsCount)
{
	if (maxBitsCount < GlobalConstants::MIN_BITS_COUNT || maxBitsCount > GlobalConstants::MAX_BITS_IN_BUCKET)
	{
		maxBitsCount = GlobalConstants::DEFAULT_BITS_COUNT_VALUE;
	}

	this->N = N;
	this->maxBitsCount = maxBitsCount;
	maxNumOccurencesInBucket = std::pow(2, maxBitsCount) - 1;

	bucketsCount = ((N + 1) * maxBitsCount) / GlobalConstants::MAX_BITS_IN_BUCKET;
	if (((N + 1) * maxBitsCount) % GlobalConstants::MAX_BITS_IN_BUCKET)
	{
		bucketsCount++;
	}
	buckets = new uint8_t[bucketsCount]{ 0 };
}

MultiSet::MultiSet(const MultiSet& other)
{
	copyFrom(other);
}

MultiSet::MultiSet(MultiSet&& other) noexcept
{
	moveFrom(std::move(other));
}

MultiSet& MultiSet::operator=(const MultiSet& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

MultiSet& MultiSet::operator=(MultiSet&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

MultiSet::~MultiSet()
{
	free();
}

// Additional functions
unsigned MultiSet::getBucketIndex(unsigned number) const
{
	return (number * maxBitsCount) / GlobalConstants::MAX_BITS_IN_BUCKET;
}

unsigned MultiSet::getStartIndexInBucket(unsigned number) const
{
	return ((number * maxBitsCount) % GlobalConstants::MAX_BITS_IN_BUCKET);
}

unsigned MultiSet::getEndIndexInBucket(unsigned startIndexInBucket) const
{
	return startIndexInBucket + (maxBitsCount - 1);
}

unsigned MultiSet::getNumberOccurences(unsigned number) const
{
	if (number > N)
	{
		throw std::out_of_range("Number is out of the valid range!");
	}

	int bucketIndex = getBucketIndex(number);
	int startIndexInBucket = getStartIndexInBucket(number);
	int endIndexInBucket = getEndIndexInBucket(startIndexInBucket);
	int carry = 0;

	// Reasigning the endIndex when our number's bits are in two buckets
	if (endIndexInBucket > 7) {
		endIndexInBucket -= GlobalConstants::MAX_BITS_IN_BUCKET;

		// Calculating carry - the amount of bits that go into the next bucket
		carry = (startIndexInBucket + maxBitsCount) - GlobalConstants::MAX_BITS_IN_BUCKET;
	}

	unsigned occurences = 0;

	if (carry > 0)
	{
		// Case when we need to count the num occurences splitted in 2 buckets
		int countOfBitsInFirstBucket = maxBitsCount - carry;
		int firstBucketMask = (1 << countOfBitsInFirstBucket) - 1;
		firstBucketMask <<= startIndexInBucket;
		int firstBucketValue = (buckets[bucketIndex] & firstBucketMask) >> startIndexInBucket;

		int secondBucketMask = (1 << carry) - 1;
		int secondBucketValue = buckets[bucketIndex + 1] & secondBucketMask;

		secondBucketValue <<= (maxBitsCount - carry);
		occurences = secondBucketValue | firstBucketValue;
	}
	else
	{
		// Default case (only working in one bucket)
		int mask = maxNumOccurencesInBucket;
		mask <<= startIndexInBucket;

		occurences = (buckets[bucketIndex] & mask) >> startIndexInBucket;
	}

	return occurences;
}

void MultiSet::addToMultiSet(unsigned number, unsigned times)
{
	if (number > N)
	{
		throw std::out_of_range("Number is out of the valid range!");
	}

	int currentNumOccurences = getNumberOccurences(number);

	if (currentNumOccurences + times > maxNumOccurencesInBucket)
		times = maxNumOccurencesInBucket - currentNumOccurences;

	int bucketIndex = getBucketIndex(number);
	int startIndexInBucket = getStartIndexInBucket(number);
	int endIndexInBucket = getEndIndexInBucket(startIndexInBucket);
	int carry = 0;

	// Reasigning the endIndex when our number's bits are in two buckets
	if (endIndexInBucket > 7) {
		endIndexInBucket -= GlobalConstants::MAX_BITS_IN_BUCKET;

		// Calculating carry - the amount of bits that go into the next bucket
		carry = (startIndexInBucket + maxBitsCount) - GlobalConstants::MAX_BITS_IN_BUCKET;
	}

	if (carry > 0)
	{
		// Case when the bits are splitted in 2 buckets
		int firstBucketMask = (1 << (GlobalConstants::MAX_BITS_IN_BUCKET - startIndexInBucket)) - 1;
		int firstBucketValue = (buckets[bucketIndex] >> startIndexInBucket) & firstBucketMask;

		int secondBucketMask = (1 << carry) - 1;
		int secondBucketValue = buckets[bucketIndex + 1] & secondBucketMask;

		int newValue = firstBucketValue + times;
		if (newValue >= (1 << (GlobalConstants::MAX_BITS_IN_BUCKET - startIndexInBucket)))
		{
			newValue -= (1 << (GlobalConstants::MAX_BITS_IN_BUCKET - startIndexInBucket));
			secondBucketValue++; // Going to the next bucket
		}

		buckets[bucketIndex] &= ~(firstBucketMask << startIndexInBucket);
		newValue <<= startIndexInBucket;
		buckets[bucketIndex] |= newValue;

		buckets[bucketIndex + 1] &= ~secondBucketMask;
		buckets[bucketIndex + 1] |= secondBucketValue;
	}
	else
	{
		// Default case (bits are only in 1 bucket)
		int mask = maxNumOccurencesInBucket;
		int currentValue = (buckets[bucketIndex] >> startIndexInBucket) & mask;
		currentValue += times;

		// Keeping the same value if it exceeds the maximum number of occurrences
		if (currentValue > maxNumOccurencesInBucket) {
			currentValue--;
		}

		buckets[bucketIndex] &= ~(mask << startIndexInBucket);
		currentValue <<= startIndexInBucket;
		buckets[bucketIndex] |= currentValue;
	}
}

void MultiSet::printMultiSet() const 
{
	std::cout << '{' << std::endl;
	for (int i = 0; i <= N; i++)
	{
		int bucketIndex = getBucketIndex(i);
		int occurencesOfI = getNumberOccurences(i);
		if (occurencesOfI != 0)
		{
			std::cout << "The number " << i << " is in bucket " << bucketIndex << " and appears " << occurencesOfI << " times" << std::endl;
		}
	}
	std::cout << '}' << std::endl;
}

void MultiSet::printMultiSetBits() const
{
	std::cout << "MultiSet Memory Representation: " << std::endl;

	for (unsigned i = 0; i < bucketsCount; ++i) {
		std::cout << "Bucket " << i << ": ";
		uint8_t bucket = buckets[i];

		for (int bit = 7; bit >= 0; bit--) {
			std::cout << ((bucket >> bit) & 1) << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void MultiSet::serializeInBinaryFile(const char* fileName)
{
	if (!fileName)
		return;

	std::ofstream file(fileName, std::ios::binary | std::ios::out);

	if (!file.is_open())
		throw std::runtime_error("Failed to open file to write to!");

	file.write((const char*)&N, sizeof(N));
	file.write((const char*)&maxBitsCount, sizeof(maxBitsCount));
	file.write((const char*)buckets, bucketsCount * sizeof(uint8_t));
}

MultiSet MultiSet::deserializeFromBinaryFile(const char* fileName)
{
	/*if (!fileName)
		return MultiSet();*/

	std::ifstream file(fileName, std::ios::binary | std::ios::in);

	if (!file.is_open())
		throw std::runtime_error("Failed to open file to write to!");

	unsigned newN;
	unsigned newMaxBitsCount;

	file.read((char*)&newN, sizeof(newN));
	file.read((char*)&newMaxBitsCount, sizeof(newMaxBitsCount));

	MultiSet deserializedSet(newN, newMaxBitsCount);
	file.read((char*)deserializedSet.buckets, deserializedSet.bucketsCount * sizeof(uint8_t));

	return deserializedSet;
}

MultiSet operator^(const MultiSet& set1, const MultiSet& set2)
{
	int resultSize = std::min(set1.N, set2.N);
	int resultBitsCount = std::min(set1.maxBitsCount, set2.maxBitsCount);

	MultiSet resultMultiSet(resultSize, resultBitsCount);

	for (int i = 0; i <= resultMultiSet.N; i++)
	{
		int occurencesInSet1 = set1.getNumberOccurences(i);
		int occurencesInSet2 = set2.getNumberOccurences(i);

		if (occurencesInSet1 > 0 && occurencesInSet2 > 0)
		{
			int minOccurencesCount = std::min(occurencesInSet1, occurencesInSet2);
			resultMultiSet.addToMultiSet(i, minOccurencesCount);
		}
	}

	return resultMultiSet;
}

MultiSet operator/(const MultiSet& set1, const MultiSet& set2)
{
	int resultSize = set1.N;
	int resultBitsCount = set1.maxBitsCount;

	MultiSet resultMultiSet(resultSize, resultBitsCount);
	for (int i = 0; i <= resultSize; i++)
	{
		int occurencesInSet1 = set1.getNumberOccurences(i);
		int occurencesInSet2 = set2.getNumberOccurences(i);

		if (occurencesInSet1 > occurencesInSet2)
		{
			int occurencesToAdd = occurencesInSet1 - occurencesInSet2;
			resultMultiSet.addToMultiSet(i, occurencesToAdd);
		}
	}
	return resultMultiSet;
}

MultiSet operator!(const MultiSet& set)
{
	MultiSet resultMultiSet(set.N, set.maxBitsCount);

	for (int i = 0; i < resultMultiSet.bucketsCount; i++)
	{
		resultMultiSet.buckets[i] = ~set.buckets[i];
	}

	return resultMultiSet;
}

