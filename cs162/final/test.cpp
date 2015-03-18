/*************************************************************************
 * Author:                 David Rigert
 * Date Created:           3/14/2015
 * Last Modification Date: 3/14/2015
 * Course:                 CS162_400
 * Assignment:             Final Project
 * Filename:               test.hpp
 *
 * Overview:
 *     Driver for running unit tests on all classes. Fails on assert if
 *     any of the tests fail.
 ************************************************************************/
#include "UnitTest.hpp"


int main()
{
    std::cout << "Running Command class unit tests..." << std::endl;
    UnitTest::test_Command();
    std::cout << std::endl;
    
    std::cout << "Running Item class unit tests..." << std::endl;
    UnitTest::test_Item();
    std::cout << std::endl;
    
    std::cout << "Running Room and BasicRoom class unit tests..." << std::endl;
    UnitTest::test_Room();
    std::cout << std::endl;
    
    std::cout << "Running Player class unit tests..." << std::endl;
    UnitTest::test_Player();
    std::cout << std::endl;
}

