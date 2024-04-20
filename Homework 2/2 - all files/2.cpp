#include <iostream>
#include "ModifiableIntegersFunction.h"

int16_t testFunc1(int16_t x)
{
	return x * 3;
}

int16_t testFunc2(int16_t x)
{
	return std::pow(x, 2);
}

int16_t testFunc3(int16_t x)
{
	return x + 5;
}

int main()
{
	ModifiableIntegersFunction myFunc(testFunc1);
	ModifiableIntegersFunction otherFunc(testFunc2);
	ModifiableIntegersFunction thirdFunc(testFunc3);

	/*myFunc.setModification(9, 18);
	otherFunc.setModification(9, 18);
	myFunc.disableValue(4);
	otherFunc.disableValue(5);
	thirdFunc.disableValue(9);
	thirdFunc.setModification(11, 22);*/


	try
	{
		//ModifiableIntegersFunction func = myFunc - otherFunc;
		//ModifiableIntegersFunction func = myFunc(thirdFunc);
	    //ModifiableIntegersFunction func = myFunc ^ -1; // checks also if it zero(works)
		//std::cout << func(3);
		//-32768
		//std::cout << (myFunc == thirdFunc); // When we sum the y values, in nums arr they go over the max value of int: 32768...
		//std::cout << (thirdFunc || otherFunc);
		//ModifiableIntegersFunction func = inverse(thirdFunc);
		/*std::cout << isInjective(otherFunc);
		std::cout << isSurjective(otherFunc);
		std::cout << isBijective(otherFunc);*/
		//myFunc.printInInterval(6, 6);
		/*otherFunc.serializeInBinaryFile("ModifiableIntegersFunction.txt");
		ModifiableIntegersFunction func;
		func.deserializeFromBinaryFile("ModifiableIntegersFunction.txt");*/
		//std::cout << func(3);
	}
	catch (const std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
}