#include "stdafx.h"
#include "CppUnitTest.h"
#include "BinarySearchTree.h"

#include <sstream>

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

		TEST_METHOD(InsertedFiveAndSizeIsFive)
		{
			BinarySearchTree binSearchTree;
			binSearchTree.insert(5);
			binSearchTree.insert(3);
			binSearchTree.insert(6);
			binSearchTree.insert(2);
			binSearchTree.insert(4);

			Assert::AreEqual(5, binSearchTree.size(), L"Value was not inserted, or size did not return correctly");
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

			// MEGKELL CSINALNI HOGY NE LEHESSEN TOBB EGYFORMA SZAMOT BETENNI
			binSearchTree.insert(value + 5);
			binSearchTree.insert(value + 5);
			binSearchTree.insert(value + 3);
			binSearchTree.insert(value + 3);
			binSearchTree.insert(value);
			binSearchTree.insert(value);

			Assert::AreEqual(3, binSearchTree.size());
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

		TEST_METHOD(Print)
		{
			BinarySearchTree binSTree;
			binSTree.insert(5);
			binSTree.insert(6);
			binSTree.insert(3);
			binSTree.insert(4);
			binSTree.insert(2);

			std::stringstream strStream;
			strStream << binSTree;
			
			std::string expected = "2 3 4 5 6 ";
			Assert::AreEqual(expected, strStream.str());
		}

		TEST_METHOD(PrintEmpty)
		{
			BinarySearchTree binSTree;

			std::stringstream strStream;
			strStream << binSTree;

			std::string expected = "";
			Assert::AreEqual(expected, strStream.str());
		}
	};
}