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

		TEST_METHOD(Find)
		{
			BinarySearchTree binSearchTree;
			const int insertedValue = 2;
			binSearchTree.insert(5);
			binSearchTree.insert(3);
			binSearchTree.insert(insertedValue);
			binSearchTree.insert(6);

			Assert::AreEqual(insertedValue, binSearchTree.find(insertedValue)->value);
		}

		TEST_METHOD(InsertExistsLargerTree)
		{
			BinarySearchTree binSearchTree;
			binSearchTree.insert(5);
			binSearchTree.insert(3);
			binSearchTree.insert(6);
			binSearchTree.insert(2);
			binSearchTree.insert(4);
			
			bool exists1 = binSearchTree.exists(5);
			bool exists2 = binSearchTree.exists(3);
			bool exists3 = binSearchTree.exists(6);
			bool exists4 = binSearchTree.exists(2);
			bool exists5 = binSearchTree.exists(4);

			Assert::IsTrue(exists1, L"Value not found in tree");
			Assert::IsTrue(exists2, L"Value not found in tree");
			Assert::IsTrue(exists3, L"Value not found in tree");
			Assert::IsTrue(exists4, L"Value not found in tree");
			Assert::IsTrue(exists5, L"Value not found in tree");
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

		TEST_METHOD(RemovedLeaf)
		{
			BinarySearchTree binSearchTree;
			const int valueToBeRemoved = 10;
			
			binSearchTree.insert(valueToBeRemoved - 2);
			binSearchTree.insert(valueToBeRemoved);
			binSearchTree.insert(valueToBeRemoved + 2);
			int sizeBefore = binSearchTree.size();

			binSearchTree.remove(valueToBeRemoved + 2);
			int sizeAfter = binSearchTree.size();

			Assert::IsFalse(binSearchTree.exists(valueToBeRemoved + 2), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
			Assert::AreEqual(sizeBefore - 1, sizeAfter);
		}

		TEST_METHOD(RemovedWithOneChildRootLeftTreeRight)
		{
			BinarySearchTree binSearchTree;
			binSearchTree.insert(10);
			binSearchTree.insert(8);
			binSearchTree.insert(9);

			int sizeBefore = binSearchTree.size();

			binSearchTree.remove(8);
			int sizeAfter = binSearchTree.size();

			Assert::IsFalse(binSearchTree.exists(8), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
			Assert::AreEqual(sizeBefore - 1, sizeAfter);
		}

		TEST_METHOD(RemovedWithOneChildRootLeftTreeLeft)
		{
			BinarySearchTree binSearchTree;
			binSearchTree.insert(10);
			binSearchTree.insert(8);
			binSearchTree.insert(7);

			int sizeBefore = binSearchTree.size();

			binSearchTree.remove(8);
			int sizeAfter = binSearchTree.size();

			Assert::IsFalse(binSearchTree.exists(8), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
			Assert::AreEqual(sizeBefore - 1, sizeAfter);
		}

		TEST_METHOD(RemovedWithOneChildRootRightTreeLeft)
		{
			BinarySearchTree binSearchTree;
			binSearchTree.insert(10);
			binSearchTree.insert(12);
			binSearchTree.insert(11);

			int sizeBefore = binSearchTree.size();

			binSearchTree.remove(12);
			int sizeAfter = binSearchTree.size();

			Assert::IsFalse(binSearchTree.exists(12), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
			Assert::AreEqual(sizeBefore - 1, sizeAfter);
		}

		TEST_METHOD(RemovedWithOneChildRootRightTreeRight)
		{
			BinarySearchTree binSearchTree;
			binSearchTree.insert(10);
			binSearchTree.insert(12);
			binSearchTree.insert(13);

			int sizeBefore = binSearchTree.size();

			binSearchTree.remove(12);
			int sizeAfter = binSearchTree.size();

			Assert::IsFalse(binSearchTree.exists(12), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
			Assert::AreEqual(sizeBefore - 1, sizeAfter);
		}

		TEST_METHOD(RemovedWithOneChildLeftTreeRight)
		{
			BinarySearchTree binSearchTree;
			binSearchTree.insert(20);
			binSearchTree.insert(10);
			binSearchTree.insert(8);
			binSearchTree.insert(9);

			int sizeBefore = binSearchTree.size();

			binSearchTree.remove(8);
			int sizeAfter = binSearchTree.size();

			Assert::IsFalse(binSearchTree.exists(8), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
			Assert::AreEqual(sizeBefore - 1, sizeAfter);
		}

		TEST_METHOD(RemovedWithOneChildLeftTreeLeft)
		{
			BinarySearchTree binSearchTree;
			binSearchTree.insert(20);
			binSearchTree.insert(10);
			binSearchTree.insert(8);
			binSearchTree.insert(7);

			int sizeBefore = binSearchTree.size();

			binSearchTree.remove(8);
			int sizeAfter = binSearchTree.size();

			Assert::IsFalse(binSearchTree.exists(8), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
			Assert::AreEqual(sizeBefore - 1, sizeAfter);
		}

		TEST_METHOD(RemovedWithOneChildRightTreeLeft)
		{
			BinarySearchTree binSearchTree;
			binSearchTree.insert(5);
			binSearchTree.insert(10);
			binSearchTree.insert(12);
			binSearchTree.insert(11);

			int sizeBefore = binSearchTree.size();

			binSearchTree.remove(12);
			int sizeAfter = binSearchTree.size();

			Assert::IsFalse(binSearchTree.exists(12), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
			Assert::AreEqual(sizeBefore - 1, sizeAfter);
		}

		TEST_METHOD(RemovedWithOneChildRightTreeRight)
		{
			BinarySearchTree binSearchTree;
			binSearchTree.insert(5);
			binSearchTree.insert(10);
			binSearchTree.insert(12);
			binSearchTree.insert(13);

			int sizeBefore = binSearchTree.size();

			binSearchTree.remove(12);
			int sizeAfter = binSearchTree.size();

			Assert::IsFalse(binSearchTree.exists(12), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
			Assert::AreEqual(sizeBefore - 1, sizeAfter);
		}

		TEST_METHOD(RemovedWithTwoChildsFromLeft)
		{
			int deletedValue = 5;
			BinarySearchTree binSearchTree;
			binSearchTree.insert(11);
			binSearchTree.insert(deletedValue);
			binSearchTree.insert(2);
			binSearchTree.insert(7);
			binSearchTree.insert(10);

			int sizeBefore = binSearchTree.size();

			binSearchTree.remove(deletedValue);
			int sizeAfter = binSearchTree.size();

			Assert::IsFalse(binSearchTree.exists(deletedValue), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
			Assert::AreEqual(sizeBefore - 1, sizeAfter);
		}

		TEST_METHOD(RemovedWithTwoChildsFromRight)
		{
			int deletedValue = 16;
			BinarySearchTree binSearchTree;
			binSearchTree.insert(11);			
			binSearchTree.insert(deletedValue);
			binSearchTree.insert(14);
			binSearchTree.insert(23);
			binSearchTree.insert(21);
			binSearchTree.insert(24);
			binSearchTree.insert(22);

			int sizeBefore = binSearchTree.size();

			binSearchTree.remove(deletedValue);
			int sizeAfter = binSearchTree.size();

			Assert::IsFalse(binSearchTree.exists(deletedValue), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
			Assert::AreEqual(sizeBefore - 1, sizeAfter);
		}

		TEST_METHOD(InsertSameValueTwice)
		{
			BinarySearchTree binSearchTree;
			int value = 10;

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