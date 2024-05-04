#include "pch.h"
#include "CppUnitTest.h"
#include "../Project1/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(StudentTests)
    {
    public:

        TEST_METHOD(TestBinarySearchStudent)
        {
            char* fname = "test.bin";
            ofstream f(fname, ios::binary | ios::out);
            if (!f.is_open()) {
                Assert::Fail(L"Failed to create test file.");
                return;
            }

            Student students[3] = { {"o", 1, KN, 85, 90, 88},
                                   {"h", 2, ME, 75, 80, 78},
                                   {"i", 3, IN, 90, 95, 92} };
            f.write(reinterpret_cast<char*>(students), sizeof(Student) * 3);
            f.close();

            Assert::IsFalse(BinarySearch(fname, "o", 1, 58));
            Assert::IsFalse(BinarySearch(fname, "h", 2, 85));
            Assert::IsFalse(BinarySearch(fname, "i", 3, 94));
            if (remove(fname) != 0) {
                Assert::Fail(L"Failed to remove test file.");
            }
        }
    };
}
