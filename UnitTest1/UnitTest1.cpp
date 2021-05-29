#include "pch.h"
#include "CppUnitTest.h"
#include "../lab_10_4/lab_10_4.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			ofstream f("test.txt");
			Goods goods;
			goods.price = 200; // 5580 UAH
			f.write((char*)&goods, sizeof(Goods));
			f.close();
			Exchange("test.txt", "test2.txt");
			ifstream file("test2.txt");
			while (file.read((char*)&goods, sizeof(Goods))) {
				Assert::AreEqual(goods.priceUAH, 5580.0);
			}
			file.close();

		}
	};
}
