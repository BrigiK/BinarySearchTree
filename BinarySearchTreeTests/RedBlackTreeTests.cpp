#include "stdafx.h"
#include "CppUnitTest.h"
#include "RedBlackTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RedBlackTreeTests
{
	TEST_CLASS(RedBlackTreeTests)
	{
	public:

		TEST_METHOD(InsertExists)
		{
			RedBlackTree redBlackTree;
			const int insertedValue = 10;

			redBlackTree.insert(insertedValue);
			bool exists = redBlackTree.exists(insertedValue);

			Assert::IsTrue(exists, L"Value not found in tree");
		}

		TEST_METHOD(InsertExistsLargerTree)
		{
			RedBlackTree redBlackTree;
			redBlackTree.insert(7);
			redBlackTree.insert(3);
			redBlackTree.insert(18);
			redBlackTree.insert(10);
			redBlackTree.insert(22);
			redBlackTree.insert(8);
			redBlackTree.insert(11);
			redBlackTree.insert(26);

			bool exists = redBlackTree.exists(18);
			Assert::IsTrue(exists, L"Value not found in tree");
		}

		TEST_METHOD(InsertExistsLargerTree2)
		{
			RedBlackTree redBlackTree;
			redBlackTree.insert(11);
			redBlackTree.insert(1);
			redBlackTree.insert(14);
			redBlackTree.insert(2);
			redBlackTree.insert(7);
			redBlackTree.insert(15);

			bool exists = redBlackTree.exists(14);
			Assert::IsTrue(exists, L"Value not found in tree");
		}

		TEST_METHOD(InsertAllCases)
		{
			RedBlackTree redBlackTree;
			redBlackTree.insert(8);
			redBlackTree.insert(5);
			redBlackTree.insert(15);
			redBlackTree.insert(12);
			redBlackTree.insert(19);
			redBlackTree.insert(9);
			redBlackTree.insert(13);
			redBlackTree.insert(23);

			redBlackTree.insert(10);
			bool exists = redBlackTree.exists(10);
			Assert::IsTrue(exists, L"Value not found in tree");

			std::stringstream strStream;
			strStream << redBlackTree;

			std::string expected = "5 8 9 10 12 13 15 19 23 ";
			Assert::AreEqual(expected, strStream.str());
		}

		TEST_METHOD(LeftRotateWithRoot)
		{
			RedBlackTree redBlackTree;
			redBlackTree.insert(5);
			redBlackTree.insert(2);
			redBlackTree.insert(10);
			redBlackTree.insert(8);
			redBlackTree.insert(12);
			redBlackTree.insert(6);
			redBlackTree.insert(9);

			RedBlackTreePrivate::RotateLeftRoot(redBlackTree);

			std::stringstream strStream;
			strStream << redBlackTree;

			std::string expected = "2 5 6 8 9 10 12 ";
			Assert::AreEqual(expected, strStream.str());
		}

		TEST_METHOD(LeftRotateNotRoot)
		{
			RedBlackTree redBlackTree;
			redBlackTree.insert(10);
			redBlackTree.insert(5);
			redBlackTree.insert(2);
			redBlackTree.insert(8);
			redBlackTree.insert(6);
			redBlackTree.insert(9);
			redBlackTree.insert(12);

			RedBlackTreePrivate::RotateLeftRootLeft(redBlackTree);

			std::stringstream strStream;
			strStream << redBlackTree;

			std::string expected = "2 5 6 8 9 10 12 ";
			Assert::AreEqual(expected, strStream.str());
		}

		TEST_METHOD(RightRotateWithRoot)
		{
			RedBlackTree redBlackTree;
			redBlackTree.insert(10);
			redBlackTree.insert(5);
			redBlackTree.insert(2);
			redBlackTree.insert(8);
			redBlackTree.insert(6);
			redBlackTree.insert(9);
			redBlackTree.insert(12);

			RedBlackTreePrivate::RotateRightRoot(redBlackTree);

			std::stringstream strStream;
			strStream << redBlackTree;

			std::string expected = "2 5 6 8 9 10 12 ";
			Assert::AreEqual(expected, strStream.str());
		}

		TEST_METHOD(RightRotateNotRoot)
		{
			RedBlackTree redBlackTree;
			/*redBlackTree.insert(7);
			redBlackTree.insert(18);
			redBlackTree.insert(11);
			redBlackTree.insert(9);
			redBlackTree.insert(14);
			redBlackTree.insert(12);
			redBlackTree.insert(17);
			redBlackTree.insert(19);
			redBlackTree.insert(22);
			redBlackTree.insert(20);*/
			redBlackTree.insert(5);
			redBlackTree.insert(2);
			redBlackTree.insert(10);
			redBlackTree.insert(8);
			redBlackTree.insert(6);
			redBlackTree.insert(9);
			redBlackTree.insert(12);

			RedBlackTreePrivate::RotateRightRootRight(redBlackTree);

			std::stringstream strStream;
			strStream << redBlackTree;

			std::string expected = "2 5 6 8 9 10 12 ";
			Assert::AreEqual(expected, strStream.str());
		}

		TEST_METHOD(RotateLeft)
		{
			RedBlackTree tree;
			tree.insert(5);
			tree.insert(6);
			tree.insert(3);
			tree.insert(4);
			tree.insert(2);

			std::stringstream strStream;
			strStream << tree;

			std::string expected = "2 3 4 5 6 ";
			Assert::AreEqual(expected, strStream.str());
		}

		TEST_METHOD(RemovedLeaf)
		{
			RedBlackTree redBlackTree;
			const int valueToBeRemoved = 10;

			redBlackTree.insert(valueToBeRemoved - 2);
			redBlackTree.insert(valueToBeRemoved);
			redBlackTree.insert(valueToBeRemoved + 2);
			int sizeBefore = redBlackTree.size();

			redBlackTree.remove(valueToBeRemoved + 2);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(valueToBeRemoved + 2), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
			Assert::AreEqual(sizeBefore - 1, sizeAfter);
		}

		TEST_METHOD(RemovedWithOneChildRootLeftTreeRight)
		{
			RedBlackTree redBlackTree;
			redBlackTree.insert(10);
			redBlackTree.insert(8);
			redBlackTree.insert(9);

			int sizeBefore = redBlackTree.size();

			redBlackTree.remove(8);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(8), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
			Assert::AreEqual(sizeBefore - 1, sizeAfter);
		}

		TEST_METHOD(RemovedWithOneChildRootLeftTreeLeft)
		{
			RedBlackTree redBlackTree;
			redBlackTree.insert(10);
			redBlackTree.insert(8);
			redBlackTree.insert(7);

			int sizeBefore = redBlackTree.size();

			redBlackTree.remove(8);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(8), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
			Assert::AreEqual(sizeBefore - 1, sizeAfter);
		}

		TEST_METHOD(RemovedWithOneChildRootRightTreeLeft)
		{
			RedBlackTree redBlackTree;
			redBlackTree.insert(10);
			redBlackTree.insert(12);
			redBlackTree.insert(11);

			int sizeBefore = redBlackTree.size();

			redBlackTree.remove(12);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(12), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
			Assert::AreEqual(sizeBefore - 1, sizeAfter);
		}

		TEST_METHOD(RemovedWithOneChildRootRightTreeRight)
		{
			RedBlackTree redBlackTree;
			redBlackTree.insert(10);
			redBlackTree.insert(12);
			redBlackTree.insert(13);

			int sizeBefore = redBlackTree.size();

			redBlackTree.remove(12);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(12), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
			Assert::AreEqual(sizeBefore - 1, sizeAfter);
		}

		TEST_METHOD(RemovedWithOneChildLeftTreeRight)
		{
			RedBlackTree redBlackTree;
			redBlackTree.insert(20);
			redBlackTree.insert(10);
			redBlackTree.insert(8);
			redBlackTree.insert(9);

			int sizeBefore = redBlackTree.size();

			redBlackTree.remove(8);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(8), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
			Assert::AreEqual(sizeBefore - 1, sizeAfter);
		}

		TEST_METHOD(RemovedWithOneChildLeftTreeLeft)
		{
			RedBlackTree redBlackTree;
			redBlackTree.insert(20);
			redBlackTree.insert(10);
			redBlackTree.insert(8);
			redBlackTree.insert(7);

			int sizeBefore = redBlackTree.size();

			redBlackTree.remove(8);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(8), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
			Assert::AreEqual(sizeBefore - 1, sizeAfter);
		}

		TEST_METHOD(RemovedWithOneChildRightTreeLeft)
		{
			RedBlackTree redBlackTree;
			redBlackTree.insert(5);
			redBlackTree.insert(10);
			redBlackTree.insert(12);
			redBlackTree.insert(11);

			int sizeBefore = redBlackTree.size();

			redBlackTree.remove(12);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(12), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
			Assert::AreEqual(sizeBefore - 1, sizeAfter);
		}

		TEST_METHOD(RemovedWithOneChildRightTreeRight)
		{
			RedBlackTree redBlackTree;
			redBlackTree.insert(5);
			redBlackTree.insert(10);
			redBlackTree.insert(12);
			redBlackTree.insert(13);

			int sizeBefore = redBlackTree.size();

			redBlackTree.remove(12);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(12), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
			Assert::AreEqual(sizeBefore - 1, sizeAfter);
		}

		TEST_METHOD(RemovedWithTwoChildsFromLeft)
		{
			int deletedValue = 5;
			RedBlackTree redBlackTree;
			redBlackTree.insert(11);
			redBlackTree.insert(deletedValue);
			redBlackTree.insert(2);
			redBlackTree.insert(7);
			redBlackTree.insert(10);

			int sizeBefore = redBlackTree.size();

			redBlackTree.remove(deletedValue);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(deletedValue), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
			Assert::AreEqual(sizeBefore - 1, sizeAfter);
		}

		TEST_METHOD(RemovedWithTwoChildsFromRight)
		{
			int deletedValue = 16;
			RedBlackTree redBlackTree;
			redBlackTree.insert(11);
			redBlackTree.insert(deletedValue);
			redBlackTree.insert(14);
			redBlackTree.insert(23);
			redBlackTree.insert(21);
			redBlackTree.insert(24);
			redBlackTree.insert(22);

			int sizeBefore = redBlackTree.size();

			redBlackTree.remove(deletedValue);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(deletedValue), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
			Assert::AreEqual(sizeBefore - 1, sizeAfter);
		}

		TEST_METHOD(RemoveSimpleCase)
		{
			RedBlackTree redBlackTree;
			redBlackTree.insert(30);
			redBlackTree.insert(20);
			redBlackTree.insert(40);
			redBlackTree.insert(10);

			int sizeBefore = redBlackTree.size();
			redBlackTree.remove(10);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(10), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
		}

		TEST_METHOD(RemoveNodeToBeDeletedBlackLeftChildBlack)
		{
			RedBlackTree redBlackTree;
			redBlackTree.insert(30);
			redBlackTree.insert(20);
			redBlackTree.insert(40);
			redBlackTree.insert(35);

			int sizeBefore = redBlackTree.size();
			redBlackTree.remove(20);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(20), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
		}

		TEST_METHOD(RemoveSiblingRedAndRightChildOfParent)
		{
			RedBlackTree redBlackTree;
			redBlackTree.insert(20);
			redBlackTree.insert(10);
			redBlackTree.insert(30);
			redBlackTree.insert(25);
			redBlackTree.insert(35);

			int sizeBefore = redBlackTree.size();
			redBlackTree.remove(10);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(10), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
		}

		TEST_METHOD(RemoveLeftLeftCase)
		{
			RedBlackTree redBlackTree;
			redBlackTree.insert(30);
			redBlackTree.insert(20);
			redBlackTree.insert(40);
			redBlackTree.insert(15);
			redBlackTree.insert(25);

			int sizeBefore = redBlackTree.size();
			redBlackTree.remove(20);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(20), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
		}

		TEST_METHOD(RemoveLeftRightCase)
		{
			RedBlackTree redBlackTree;
			redBlackTree.insert(30);
			redBlackTree.insert(20);
			redBlackTree.insert(40);
			redBlackTree.insert(25);

			int sizeBefore = redBlackTree.size();
			redBlackTree.remove(20);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(20), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
		}

		TEST_METHOD(RemoveRightRightCase)
		{
			RedBlackTree redBlackTree;
			redBlackTree.insert(30);
			redBlackTree.insert(20);
			redBlackTree.insert(40);
			redBlackTree.insert(35);
			redBlackTree.insert(50);

			int sizeBefore = redBlackTree.size();
			redBlackTree.remove(20);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(20), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
		}

		TEST_METHOD(RemoveRightLeftCase)
		{
			RedBlackTree redBlackTree;
			redBlackTree.insert(30);
			redBlackTree.insert(20);
			redBlackTree.insert(40);
			redBlackTree.insert(35);

			int sizeBefore = redBlackTree.size();
			redBlackTree.remove(20);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(20), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
		}

		TEST_METHOD(RemoveSiblingBlackBothChildrenBlack)
		{
			RedBlackTree redBlackTree;
			redBlackTree.insert(61);
			redBlackTree.insert(52);
			redBlackTree.insert(85);
			redBlackTree.insert(20);
			redBlackTree.insert(55);

			int sizeBefore = redBlackTree.size();
			redBlackTree.remove(52);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(52), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
		}

		TEST_METHOD(RemoveSiblingRedLeftCase)
		{
			RedBlackTree redBlackTree;
			redBlackTree.insert(20);
			redBlackTree.insert(10);
			redBlackTree.insert(30);
			redBlackTree.insert(5);
			redBlackTree.insert(15);

			int sizeBefore = redBlackTree.size();
			redBlackTree.remove(10);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(10), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
		}

		TEST_METHOD(RemoveSiblingRedRightCase)
		{
			RedBlackTree redBlackTree;
			redBlackTree.insert(20);
			redBlackTree.insert(10);
			redBlackTree.insert(30);
			redBlackTree.insert(25);
			redBlackTree.insert(35);

			int sizeBefore = redBlackTree.size();
			redBlackTree.remove(10);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(10), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
		}
		TEST_METHOD(RemoveRoot)
		{
			RedBlackTree redBlackTree;
			redBlackTree.insert(20);
			redBlackTree.insert(10);
			redBlackTree.insert(30);
			redBlackTree.insert(25);
			redBlackTree.insert(35);

			int sizeBefore = redBlackTree.size();
			redBlackTree.remove(20);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(20), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
		}

	};
}