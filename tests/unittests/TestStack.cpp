#include <gtest/gtest.h>
#include "stack/stack.h"

#ifndef TESTING_MODE_H
#define TESTING_MODE_H
#endif // TESTING_MODE_H

#include "../tests/unittests/TestWrapper.h"

using namespace customalgorithms;

TEST(TestStack, createEmptyStack)
{
	Stack<float> testObj;
	float a = 34.323f;
	cout << "Protected function from friend class " << testObj.pop() << endl;
	Stack<double> stack(6);
	for (int i = 0; i <= 100; i++)
		stack.push((double)i + 13e-4);
	cout << "Stack" << endl;
	while (stack.size() > 0) 
		cout << stack.pop() << " ";

	cout << endl <<  "EMPTY STACK " << stack.pop() << " ";
}

TEST(TestStack, charStack)
{
	Stack<char*> charPtrStack;
	Stack<char> charStack;
	char* name = "Ihor";
	char* lastname = "Mudryy";
	char* company = "HERE";
	charStack.push(*name);
	charStack.push(*lastname);
	charStack.push(*company);

	charPtrStack.push(name);
	charPtrStack.push(lastname);
	charPtrStack.push(company);

	while (charPtrStack.size() > 0)
	{
		char* val_ptr = charPtrStack.pop();
		if (val_ptr)
			cout << val_ptr;
		cout << endl;
	}
	ASSERT_TRUE(charPtrStack.pop() == NULL);
	cout << "NORMAL STACK " << endl;

	while (charStack.size() > 0)
	{
		char val = charStack.pop();
		cout << val++;
		cout << endl;
	}
}

TEST(TestStack, testOnePopAndPush)
{
	Stack<bool> boolStack;
	boolStack.push(true);
	ASSERT_TRUE(boolStack.pop());
	ASSERT_TRUE(boolStack.pop() == NULL);
	boolStack.push(false);
	ASSERT_TRUE(!boolStack.pop());
	ASSERT_TRUE(boolStack.pop() == NULL);
}