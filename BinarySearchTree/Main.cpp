#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <set>
#include "CSquare.h"
#include "CRectangle.h"
#include "CCircle.h"
#include "CShapeMap.h"
#include "CShape.h"

void InheritanceCompletion()
{
	CShapeMap map;

	map.insert(new CSquare("My favorite square", /*width=*/10));
	map.insert(new CRectangle("Some rectangle", /*l1=*/2, /*l2=*/3));
	map.insert(new CCircle("Main circle", 20));
	map.insert(new CCircle("Secondary circle", 21));

	for(auto shape : map)
	{
		std::cout << "Name: " << shape->Name() << ", Area: " << shape->GetSurfaceArea() << std::endl;
	}

	auto favorite = map["My favorite square"];

	std::cout << "favorite Name: " << favorite->Name() << ", favorite Area: " << favorite->GetSurfaceArea() << std::endl;

	try
	{
		map.insert(new CSquare("My favorite square", /*width=*/20));
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl; //expected [Cannot add duplicate entry “My favorite square”]
	}

	for (auto shape : map)
	{
		delete shape;
	}
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	InheritanceCompletion();

	_CrtDumpMemoryLeaks();
	return 0;

}