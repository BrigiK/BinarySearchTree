#include "stdafx.h"
#include "CppUnitTest.h"
#include "RedBlackTree.h"

#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RedBlackTreeTests
{
	TEST_CLASS(RedBlackTreeTests)
	{
	public:

		TEST_METHOD(InsertExists)
		{
			RedBlackTree<int, std::string> redBlackTree;
			const int insertedValue = 10;

			redBlackTree.insert(insertedValue, "");
			bool exists = redBlackTree.exists(insertedValue);

			Assert::IsTrue(exists, L"Value not found in tree");
		}

		TEST_METHOD(InsertExistsLargerTree)
		{
			RedBlackTree<int, std::string> redBlackTree;
			redBlackTree.insert(7, "");
			redBlackTree.insert(3, "");
			redBlackTree.insert(18, "");
			redBlackTree.insert(10, "");
			redBlackTree.insert(22, "");
			redBlackTree.insert(8, "");
			redBlackTree.insert(11, "");
			redBlackTree.insert(26, "");

			bool exists = redBlackTree.exists(18);
			Assert::IsTrue(exists, L"Value not found in tree");
		}

		TEST_METHOD(InsertExistsLargerTree2)
		{
			RedBlackTree<int, std::string> redBlackTree;
			redBlackTree.insert(11, "");
			redBlackTree.insert(1, "");
			redBlackTree.insert(14, "");
			redBlackTree.insert(2, "");
			redBlackTree.insert(7, "");
			redBlackTree.insert(15, "");

			bool exists = redBlackTree.exists(14);
			Assert::IsTrue(exists, L"Value not found in tree");
		}

		TEST_METHOD(InsertAllCases)
		{
			RedBlackTree<int, std::string> redBlackTree;
			redBlackTree.insert(8, "");
			redBlackTree.insert(5, "");
			redBlackTree.insert(15, "");
			redBlackTree.insert(12, "");
			redBlackTree.insert(19, "");
			redBlackTree.insert(9, "");
			redBlackTree.insert(13, "");
			redBlackTree.insert(23, "");

			redBlackTree.insert(10, "");
			bool exists = redBlackTree.exists(10);
			Assert::IsTrue(exists, L"Value not found in tree");

			std::stringstream strStream;
			strStream << redBlackTree;

			std::string expected = "5 8 9 10 12 13 15 19 23 ";
			Assert::AreEqual(expected, strStream.str());
		}

		TEST_METHOD(InsertAllCasesStrings)
		{
			RedBlackTree<std::string, int> redBlackTree;
			redBlackTree.insert("hagyma", 0);
			redBlackTree.insert("embor", 0);
			redBlackTree.insert("pityi", 0);
			redBlackTree.insert("lukas", 0);
			redBlackTree.insert("trutyi", 0);
			redBlackTree.insert("ize", 0);
			redBlackTree.insert("mami", 0);
			redBlackTree.insert("yambikus", 0);

			redBlackTree.insert("jubi", 0);
			bool exists = redBlackTree.exists("jubi");
			Assert::IsTrue(exists, L"Value not found in tree");

			std::stringstream strStream;
			strStream << redBlackTree;

			std::string expected = "embor hagyma ize jubi lukas mami pityi trutyi yambikus ";
			Assert::AreEqual(expected, strStream.str());
		}

		TEST_METHOD(LeftRotateWithRoot)
		{
			RedBlackTree<int, std::string> redBlackTree;
			redBlackTree.insert(5, "");
			redBlackTree.insert(2, "");
			redBlackTree.insert(10, "");
			redBlackTree.insert(8, "");
			redBlackTree.insert(12, "");
			redBlackTree.insert(6, "");
			redBlackTree.insert(9, "");

			RedBlackTreePrivate<int, std::string>::RotateLeftRoot(redBlackTree);

			std::stringstream strStream;
			strStream << redBlackTree;

			std::string expected = "2 5 6 8 9 10 12 ";
			Assert::AreEqual(expected, strStream.str());
		}

		TEST_METHOD(LeftRotateNotRoot)
		{
			RedBlackTree<int, std::string> redBlackTree;
			redBlackTree.insert(10, "");
			redBlackTree.insert(5, "");
			redBlackTree.insert(2, "");
			redBlackTree.insert(8, "");
			redBlackTree.insert(6, "");
			redBlackTree.insert(9, "");
			redBlackTree.insert(12, "");

			RedBlackTreePrivate<int, std::string>::RotateLeftRootLeft(redBlackTree);

			std::stringstream strStream;
			strStream << redBlackTree;

			std::string expected = "2 5 6 8 9 10 12 ";
			Assert::AreEqual(expected, strStream.str());
		}

		TEST_METHOD(RightRotateWithRoot)
		{
			RedBlackTree<int, std::string> redBlackTree;
			redBlackTree.insert(10, "");
			redBlackTree.insert(5, "");
			redBlackTree.insert(2, "");
			redBlackTree.insert(8, "");
			redBlackTree.insert(6, "");
			redBlackTree.insert(9, "");
			redBlackTree.insert(12, "");

			RedBlackTreePrivate<int, std::string>::RotateRightRoot(redBlackTree);

			std::stringstream strStream;
			strStream << redBlackTree;

			std::string expected = "2 5 6 8 9 10 12 ";
			Assert::AreEqual(expected, strStream.str());
		}

		TEST_METHOD(RightRotateNotRoot)
		{
			RedBlackTree<int, std::string> redBlackTree;
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
			redBlackTree.insert(5, "");
			redBlackTree.insert(2, "");
			redBlackTree.insert(10, "");
			redBlackTree.insert(8, "");
			redBlackTree.insert(6, "");
			redBlackTree.insert(9, "");
			redBlackTree.insert(12, "");

			RedBlackTreePrivate<int, std::string>::RotateRightRootRight(redBlackTree);

			std::stringstream strStream;
			strStream << redBlackTree;

			std::string expected = "2 5 6 8 9 10 12 ";
			Assert::AreEqual(expected, strStream.str());
		}

		TEST_METHOD(RotateLeft)
		{
			RedBlackTree<int, std::string> tree;
			tree.insert(5, "");
			tree.insert(6, "");
			tree.insert(3, "");
			tree.insert(4, "");
			tree.insert(2, "");

			std::stringstream strStream;
			strStream << tree;

			std::string expected = "2 3 4 5 6 ";
			Assert::AreEqual(expected, strStream.str());
		}

		TEST_METHOD(RemovedLeaf)
		{
			RedBlackTree<int, std::string> redBlackTree;
			const int valueToBeRemoved = 10;

			redBlackTree.insert(valueToBeRemoved - 2, "");
			redBlackTree.insert(valueToBeRemoved, "");
			redBlackTree.insert(valueToBeRemoved + 2, "");
			int sizeBefore = redBlackTree.size();

			redBlackTree.remove(valueToBeRemoved + 2);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(valueToBeRemoved + 2), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
			Assert::AreEqual(sizeBefore - 1, sizeAfter);
		}

		TEST_METHOD(RemovedWithOneChildRootLeftTreeRight)
		{
			RedBlackTree<int, std::string> redBlackTree;
			redBlackTree.insert(10, "");
			redBlackTree.insert(8, "");
			redBlackTree.insert(9, "");

			int sizeBefore = redBlackTree.size();

			redBlackTree.remove(8);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(8), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
			Assert::AreEqual(sizeBefore - 1, sizeAfter);
		}

		TEST_METHOD(RemovedWithOneChildRootLeftTreeLeft)
		{
			RedBlackTree<int, std::string> redBlackTree;
			redBlackTree.insert(10, "");
			redBlackTree.insert(8, "");
			redBlackTree.insert(7, "");

			int sizeBefore = redBlackTree.size();

			redBlackTree.remove(8);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(8), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
			Assert::AreEqual(sizeBefore - 1, sizeAfter);
		}

		TEST_METHOD(RemovedWithOneChildRootRightTreeLeft)
		{
			RedBlackTree<int, std::string> redBlackTree;
			redBlackTree.insert(10, "");
			redBlackTree.insert(12, "");
			redBlackTree.insert(11, "");

			int sizeBefore = redBlackTree.size();

			redBlackTree.remove(12);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(12), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
			Assert::AreEqual(sizeBefore - 1, sizeAfter);
		}

		TEST_METHOD(RemovedWithOneChildRootRightTreeRight)
		{
			RedBlackTree<int, std::string> redBlackTree;
			redBlackTree.insert(10, "");
			redBlackTree.insert(12, "");
			redBlackTree.insert(13, "");

			int sizeBefore = redBlackTree.size();

			redBlackTree.remove(12);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(12), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
			Assert::AreEqual(sizeBefore - 1, sizeAfter);
		}

		TEST_METHOD(RemovedWithOneChildLeftTreeRight)
		{
			RedBlackTree<int, std::string> redBlackTree;
			redBlackTree.insert(20, "");
			redBlackTree.insert(10, "");
			redBlackTree.insert(8, "");
			redBlackTree.insert(9, "");

			int sizeBefore = redBlackTree.size();

			redBlackTree.remove(8);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(8), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
			Assert::AreEqual(sizeBefore - 1, sizeAfter);
		}

		TEST_METHOD(RemovedWithOneChildLeftTreeLeft)
		{
			RedBlackTree<int, std::string> redBlackTree;
			redBlackTree.insert(20, "");
			redBlackTree.insert(10, "");
			redBlackTree.insert(8, "");
			redBlackTree.insert(7, "");

			int sizeBefore = redBlackTree.size();

			redBlackTree.remove(8);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(8), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
			Assert::AreEqual(sizeBefore - 1, sizeAfter);
		}

		TEST_METHOD(RemovedWithOneChildRightTreeLeft)
		{
			RedBlackTree<int, std::string> redBlackTree;
			redBlackTree.insert(5, "");
			redBlackTree.insert(10, "");
			redBlackTree.insert(12, "");
			redBlackTree.insert(11, "");

			int sizeBefore = redBlackTree.size();

			redBlackTree.remove(12);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(12), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
			Assert::AreEqual(sizeBefore - 1, sizeAfter);
		}

		TEST_METHOD(RemovedWithOneChildRightTreeRight)
		{
			RedBlackTree<int, std::string> redBlackTree;
			redBlackTree.insert(5, "");
			redBlackTree.insert(10, "");
			redBlackTree.insert(12, "");
			redBlackTree.insert(13, "");

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
			RedBlackTree<int, std::string> redBlackTree;
			redBlackTree.insert(11, "");
			redBlackTree.insert(deletedValue, "");
			redBlackTree.insert(2, "");
			redBlackTree.insert(7, "");
			redBlackTree.insert(10, "");

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
			RedBlackTree<int, std::string> redBlackTree;
			redBlackTree.insert(11, "");
			redBlackTree.insert(deletedValue, "");
			redBlackTree.insert(14, "");
			redBlackTree.insert(23, "");
			redBlackTree.insert(21, "");
			redBlackTree.insert(24, "");
			redBlackTree.insert(22, "");

			int sizeBefore = redBlackTree.size();

			redBlackTree.remove(deletedValue);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(deletedValue), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
			Assert::AreEqual(sizeBefore - 1, sizeAfter);
		}

		TEST_METHOD(RemoveSimpleCase)
		{
			RedBlackTree<int, std::string> redBlackTree;
			redBlackTree.insert(30, "");
			redBlackTree.insert(20, "");
			redBlackTree.insert(40, "");
			redBlackTree.insert(10, "");

			int sizeBefore = redBlackTree.size();
			redBlackTree.remove(10);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(10), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
		}

		TEST_METHOD(RemoveNodeToBeDeletedBlackLeftChildBlack)
		{
			RedBlackTree<int, std::string> redBlackTree;
			redBlackTree.insert(30, "");
			redBlackTree.insert(20, "");
			redBlackTree.insert(40, "");
			redBlackTree.insert(35, "");

			int sizeBefore = redBlackTree.size();
			redBlackTree.remove(20);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(20), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
		}

		TEST_METHOD(RemoveSiblingRedAndRightChildOfParent)
		{
			RedBlackTree<int, std::string> redBlackTree;
			redBlackTree.insert(20, "");
			redBlackTree.insert(10, "");
			redBlackTree.insert(30, "");
			redBlackTree.insert(25, "");
			redBlackTree.insert(35, "");

			int sizeBefore = redBlackTree.size();
			redBlackTree.remove(10);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(10), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
		}

		TEST_METHOD(RemoveLeftLeftCase)
		{
			RedBlackTree<int, std::string> redBlackTree;
			redBlackTree.insert(30, "");
			redBlackTree.insert(20, "");
			redBlackTree.insert(40, "");
			redBlackTree.insert(15, "");
			redBlackTree.insert(25, "");

			int sizeBefore = redBlackTree.size();
			redBlackTree.remove(20);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(20), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
		}

		TEST_METHOD(RemoveLeftRightCase)
		{
			RedBlackTree<int, std::string> redBlackTree;
			redBlackTree.insert(30, "");
			redBlackTree.insert(20, "");
			redBlackTree.insert(40, "");
			redBlackTree.insert(25, "");

			int sizeBefore = redBlackTree.size();
			redBlackTree.remove(20);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(20), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
		}

		TEST_METHOD(RemoveRightRightCase)
		{
			RedBlackTree<int, std::string> redBlackTree;
			redBlackTree.insert(30, "");
			redBlackTree.insert(20, "");
			redBlackTree.insert(40, "");
			redBlackTree.insert(35, "");
			redBlackTree.insert(50, "");

			int sizeBefore = redBlackTree.size();
			redBlackTree.remove(20);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(20), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
		}

		TEST_METHOD(RemoveRightLeftCase)
		{
			RedBlackTree<int, std::string> redBlackTree;
			redBlackTree.insert(30, "");
			redBlackTree.insert(20, "");
			redBlackTree.insert(40, "");
			redBlackTree.insert(35, "");

			int sizeBefore = redBlackTree.size();
			redBlackTree.remove(20);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(20), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
		}

		TEST_METHOD(RemoveSiblingBlackBothChildrenBlack)
		{
			RedBlackTree<int, std::string> redBlackTree;
			redBlackTree.insert(61, "");
			redBlackTree.insert(52, "");
			redBlackTree.insert(85, "");
			redBlackTree.insert(20, "");
			redBlackTree.insert(55, "");

			int sizeBefore = redBlackTree.size();
			redBlackTree.remove(52);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(52), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
		}

		TEST_METHOD(RemoveSiblingRedLeftCase)
		{
			RedBlackTree<int, std::string> redBlackTree;
			redBlackTree.insert(20, "");
			redBlackTree.insert(10, "");
			redBlackTree.insert(30, "");
			redBlackTree.insert(5, "");
			redBlackTree.insert(15, "");

			int sizeBefore = redBlackTree.size();
			redBlackTree.remove(10);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(10), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
		}

		TEST_METHOD(RemoveSiblingRedRightCase)
		{
			RedBlackTree<int, std::string> redBlackTree;
			redBlackTree.insert(20, "");
			redBlackTree.insert(10, "");
			redBlackTree.insert(30, "");
			redBlackTree.insert(25, "");
			redBlackTree.insert(35, "");

			int sizeBefore = redBlackTree.size();
			redBlackTree.remove(10);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(10), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
		}
		TEST_METHOD(RemoveRoot)
		{
			RedBlackTree<int, std::string> redBlackTree;
			redBlackTree.insert(20, "");
			redBlackTree.insert(10, "");
			redBlackTree.insert(30, "");
			redBlackTree.insert(25, "");
			redBlackTree.insert(35, "");

			int sizeBefore = redBlackTree.size();
			redBlackTree.remove(20);
			int sizeAfter = redBlackTree.size();

			Assert::IsFalse(redBlackTree.exists(20), L"Value still in tree");
			Assert::AreNotEqual(sizeBefore, sizeAfter);
		}

	};
}