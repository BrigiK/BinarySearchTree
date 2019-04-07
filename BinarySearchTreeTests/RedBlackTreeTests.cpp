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

			redBlackTree.remove(12);
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

			redBlackTree.remove(12);
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

			redBlackTree.remove(12);
		}

		TEST_METHOD(RightRotateNotRoot)
		{
			RedBlackTree redBlackTree;
			redBlackTree.insert(7);
			redBlackTree.insert(18);
			redBlackTree.insert(11);
			redBlackTree.insert(9);
			redBlackTree.insert(14);
			redBlackTree.insert(12);
			redBlackTree.insert(17);
			redBlackTree.insert(19);
			redBlackTree.insert(22);
			redBlackTree.insert(20);

			redBlackTree.remove(12);
		}
	};
}