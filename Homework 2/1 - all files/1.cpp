#include <iostream>
#include "MultiSet.h"

int main()
{
	MultiSet multiset1(12, 3);
	MultiSet multiset2(15, 5);

	try {
		multiset1.addToMultiSet(0, 1);
		multiset1.addToMultiSet(1, 1);
		multiset1.addToMultiSet(2, 2);
		multiset1.addToMultiSet(3, 3);
		multiset1.addToMultiSet(12, 4);

		multiset2.addToMultiSet(1, 2);
		multiset2.addToMultiSet(2, 1);
		multiset2.addToMultiSet(5, 3);
		multiset2.addToMultiSet(12, 5);

		//multiset1.serializeInBinaryFile("multiset.txt");
		MultiSet deserializedSet = MultiSet::deserializeFromBinaryFile("multiset.txt");
		std::cout << "Deserialized set: " << std::endl;
		deserializedSet.printMultiSet();
		deserializedSet.printMultiSetBits();
	}
	catch (const std::out_of_range& e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << "An error occured: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "An exception occurred: " << e.what() << std::endl;
	}

	std::cout << "First Set: " << std::endl;
	multiset1.printMultiSet();
	multiset1.printMultiSetBits();

	std::cout << "Second Set: " << std::endl;
	multiset2.printMultiSet();
	multiset2.printMultiSetBits();

	std::cout << "Intersection: " << std::endl;
	MultiSet intersectSet = operator^(multiset1, multiset2);
	intersectSet.printMultiSet();
	intersectSet.printMultiSetBits();

	std::cout << "Difference: " << std::endl;
	MultiSet differenceSet = operator/(multiset1, multiset2);
	differenceSet.printMultiSet();
	differenceSet.printMultiSetBits();

	std::cout << "Complement set: " << std::endl;
	MultiSet complementSet = operator!(multiset1);
	complementSet.printMultiSet();
	complementSet.printMultiSetBits();
}

