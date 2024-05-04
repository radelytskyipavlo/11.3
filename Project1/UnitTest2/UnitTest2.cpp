#include "pch.h"
#include "CppUnitTest.h"
#include "../Project1/Source.cpp" // ¬каж≥ть правильний шл€х до вашого файлу з програмою
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1 {
    TEST_CLASS(UnitTest1) {
public:
    TEST_METHOD(TestCreatePrintSort) {
        char* FileName = "test_students.bin";
        const int testStudentsCount = 3;

        Create(FileName);

        std::ifstream testFile(FileName, std::ios::binary | std::ios::ate);
        int fileSize = testFile.tellg();
        int expectedFileSize = testStudentsCount * sizeof(Student);
        Assert::AreEqual(expectedFileSize, fileSize);

        Student testStudents[testStudentsCount];
        strcpy_s(testStudents[0].surname, "Surname1");
        testStudents[0].course = 3;
        testStudents[0].spec = KN;
        testStudents[0].fiz = 5;
        testStudents[0].mat = 4;
        testStudents[0].average = 4.5;

        strcpy_s(testStudents[1].surname, "Surname2");
        testStudents[1].course = 2;
        testStudents[1].spec = IN;
        testStudents[1].fiz = 4;
        testStudents[1].mat = 5;
        testStudents[1].average = 4.5;

        strcpy_s(testStudents[2].surname, "Surname3");
        testStudents[2].course = 4;
        testStudents[2].spec = FI;
        testStudents[2].fiz = 3;
        testStudents[2].mat = 3;
        testStudents[2].average = 3.0;

        Print(FileName);
        for (int i = 0; i < testStudentsCount; ++i) {
            Assert::AreEqual(testStudents[i].course, testStudents[i].course);
            Assert::AreEqual(testStudents[i].spec, testStudents[i].spec);
            Assert::AreEqual(testStudents[i].fiz, testStudents[i].fiz);
            Assert::AreEqual(testStudents[i].mat, testStudents[i].mat);
            Assert::AreEqual(testStudents[i].average, testStudents[i].average);
        }

        Sort(FileName);

        std::ifstream sortedTestFile(FileName, std::ios::binary);
        Student sortedTestStudents[testStudentsCount];
        sortedTestFile.read(reinterpret_cast<char*>(sortedTestStudents), testStudentsCount * sizeof(Student));
        for (int i = 1; i < testStudentsCount; ++i) {
            Assert::IsTrue(sortedTestStudents[i - 1].average >= sortedTestStudents[i].average);
        }
   
    }
    };
}