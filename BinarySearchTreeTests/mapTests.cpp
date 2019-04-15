#include "stdafx.h"
#include "CppUnitTest.h"
#include "map.h"

#include <iostream>
#include <map>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace kb;

namespace mapTests
{
	TEST_CLASS(mapTests)
	{
	public:
		TEST_METHOD(OperatorTestIfKeyFoundReturnValue)
		{
			map<std::string, int> map;
			map["Something"] = 1;

			Assert::AreEqual(map["Something"], 1);
		}

		TEST_METHOD(OperatorTestIfKeyNotFoundInsert)
		{
			map<std::string, int> map;
			map["Something"] = 1;

			Assert::AreEqual(map["Nothing"], 0);
		}

		TEST_METHOD(OperatorTestIfKeyFoundReturnValueLargerMap)
		{
			map<std::string, int> map;
			map["Something"] = 1;
			map["Nothing"] = 2;
			map["Someone"] = 3;
			map["No one"] = 4;

			Assert::AreEqual(map["No one"], 4);
		}

		TEST_METHOD(OperatorTestKeyAsInt)
		{
			map<int, std::string> map;
			map[1] = "Something";
			map[2] = "Nothing";
			map[3] = "Someone";
			map[4] = "No one";

			Assert::AreEqual(map[4], (std::string)"No one");
		}

		TEST_METHOD(Size)
		{
			map<int, std::string> map;
			std::string insval = "hello";
			map.insert(15, insval);

			Assert::AreEqual(map.size(), 1);
		}

		TEST_METHOD(SizeLargerMap)
		{
			map<int, std::string> map;
			std::string insval = "hello";
			map.insert(15, insval);
			map[8] = "hi";
			map[7] = "low";

			Assert::AreEqual(map.size(), 3);
		}

		TEST_METHOD(SizeEmptyMap)
		{
			map<int, std::string> map;
			Assert::AreEqual(map.size(), 0);
		}

		TEST_METHOD(Insert)
		{
			map<int, std::string> map;
			std::string insval = "InsertedValue";
			map.insert(5, insval);

			Assert::AreEqual(map.size(), 1);
		}

		TEST_METHOD(InsertLargerMap)
		{
			map<int, std::string> map;
			map.insert(5, "inserted");
			map.insert(4, "hey");
			map.insert(8, "hello");
			map.insert(77, "hi");
			map[78] = "helllo";

			Assert::AreEqual(map.size(), 5);
		}

		TEST_METHOD(InsertDuplicate)
		{
			map<int, std::string> map;
			map.insert(5, "inserted");
			map.insert(4, "hey");
			map.insert(8, "hello");
			map.insert(77, "hi");
			map[77] = "helllo";

			Assert::AreNotEqual(map.size(), 5);
		}

		TEST_METHOD(Remove)
		{
			map<int, std::string> map;
			std::string insval = "InsertedValue";
			map.insert(5, insval);

			int sizeBefore = map.size();
			map.remove(5);
			int sizeAfter = map.size();

			Assert::AreNotEqual(sizeBefore, sizeAfter);
		}

		TEST_METHOD(RemoveLargerMap)
		{
			map<int, std::string> map;
			std::string insval = "InsertedValue";
			map.insert(5, insval);
			map.insert(88, "now");
			map[97] = "or";
			map[7] = "never";

			int sizeBefore = map.size();
			map.remove(97);
			int sizeAfter = map.size();

			Assert::AreNotEqual(sizeBefore, sizeAfter);
		}

		TEST_METHOD(RemoveUnexistentKey)
		{
			map<int, std::string> map;
			std::string insval = "InsertedValue";
			map.insert(5, insval);
			map.insert(88, "now");
			map[97] = "or";
			map[7] = "never";

			int sizeBefore = map.size();
			map.remove(100);
			int sizeAfter = map.size();

			Assert::AreEqual(sizeBefore, sizeAfter);
		}

		TEST_METHOD(Exists)
		{
			map<int, std::string> map;
			map.insert(5, "string");

			Assert::IsTrue(map.exists(5));
		}

		TEST_METHOD(ExistsLargerMap)
		{
			map<int, std::string> map;
			map.insert(5, "string");
			map[88] = "string";
			map[4] = "string";
			map.insert(44, "string");

			Assert::IsTrue(map.exists(4));
		}

		TEST_METHOD(ExistsFalse)
		{
			map<int, std::string> map;
			map.insert(5, "string");
			map[88] = "string";
			map[4] = "string";
			map.insert(44, "string");

			Assert::IsFalse(map.exists(120));
		}

		TEST_METHOD(ForEach)
		{
			map<std::string, int> myMap;
			myMap.insert("Tuenty Five", 25);
			myMap["Didd"] = 4;
			myMap.insert("Brigi", 1);
			myMap["Tways"] = 74;
			myMap.insert("Diss", 8);
			myMap["Iwn"] = 14;

			std::stringstream strStream;

			std::string expected = "Brigi 1 Didd 4 Diss 8 Iwn 14 Tuenty Five 25 Tways 74 ";

			for (auto pair : myMap)
			{
				strStream << pair.first << " " << pair.second << " ";
			}

			Assert::AreEqual(expected, strStream.str());
		}
	};
}