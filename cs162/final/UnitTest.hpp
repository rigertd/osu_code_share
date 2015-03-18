/*************************************************************************
 * Author:                 David Rigert
 * Date Created:           3/14/2015
 * Last Modification Date: 3/14/2015
 * Course:                 CS162_400
 * Assignment:             Final Project
 * Filename:               UnitTest.hpp
 *
 * Overview:
 *     Represents unit tests for the final project.
 ************************************************************************/
#ifndef UNITTEST_HPP
#define UNITTEST_HPP

#include <iostream>
#include <cassert>

class UnitTest
{
public:
    // unit tests for the Command class
    static void test_Command();

    // unit tests for the Item class
    static void test_Item();

    // unit tests for the Room and BasicRoom classes
    static void test_Room();
    
    // unit tests for the Player class
    static void test_Player();
};

#endif
