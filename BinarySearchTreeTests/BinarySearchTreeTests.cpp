#include "stdafx.h"
#include "CppUnitTest.h"
#include "BinarySearchTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BinarySearchTreeTests
{		
	TEST_CLASS(BinarySearchTreeTests)
	{
	public:
		
		TEST_METHOD(InsertExists)
		{
			BinarySearchTree binSearchTree;
			const int insertedValue = 10;

			binSearchTree.insert(insertedValue);
			bool exists = binSearchTree.exists(insertedValue);

			Assert::IsTrue(exists, L"Value not found in tree");
		}

		TEST_METHOD(NewTreeIsEmpty)
		{
			BinarySearchTree binSearchTree;

			Assert::AreEqual(0, binSearchTree.size(), L"Tree not empty");
		}

		TEST_METHOD(InsertedOneAndSizeIsOne)
		{
			BinarySearchTree binSearchTree;
			const int insertedValue = 10;

			binSearchTree.insert(insertedValue);

			Assert::AreEqual(1, binSearchTree.size(), L"Value was not inserted, or size did not return correctly");
		}

		TEST_METHOD(Removed)
		{
			BinarySearchTree binSearchTree;
			const int valueToBeRemoved = 10;
			
			binSearchTree.insert(valueToBeRemoved - 2);
			binSearchTree.insert(valueToBeRemoved);
			binSearchTree.insert(valueToBeRemoved + 2);
			int sizeBefore = binSearchTree.size();

			binSearchTree.remove(valueToBeRemoved);
			int sizeAfter = binSearchTree.size();

			Assert::IsFalse(binSearchTree.exists(valueToBeRemoved), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
			Assert::AreEqual(sizeBefore - 1, sizeAfter);
		}

		TEST_METHOD(InsertSameValueTwice)
		{
			BinarySearchTree binSearchTree;
			int value = 10;

			binSearchTree.insert(value);
			binSearchTree.insert(value);

			Assert::AreEqual(1, binSearchTree.size());
		}

		TEST_METHOD(RemoveUnexistentValue)
		{
			BinarySearchTree binSearchTree;
			int value = 10;

			binSearchTree.remove(value);
			Assert::AreEqual(0, binSearchTree.size());

			binSearchTree.insert(value + 5);
			binSearchTree.remove(value);
			Assert::AreEqual(1, binSearchTree.size());
		}
	};
}