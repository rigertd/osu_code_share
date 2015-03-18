/*************************************************************************
 * Author:                 David Rigert
 * Date Created:           3/13/2015
 * Last Modification Date: 3/13/2015
 * Course:                 CS162_400
 * Assignment:             Final Project
 * Filename:               Result.hpp
 *
 * Overview:
 *     Represents the result of an operation. 
 ************************************************************************/
#ifndef RESULT_HPP
#define RESULT_HPP
struct Result
{
    // enumerates different types of results
    enum ResultType
    {
        FAILURE,
        SUCCESS,
        ABORT,
        EXIT
    };
    
    ResultType type;        // type of result
    std::string message;    // result message
    
    // constructors
    Result()                { type = FAILURE; }
    Result(ResultType rt)   { type = rt; }
};
#endif  // end of RESULT_HPP definition
