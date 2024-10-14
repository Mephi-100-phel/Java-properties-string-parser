#ifndef LIB_H
#define LIB_H

#include <iostream>
#include <string>
#include <cstring>

/**
 * \date 23.09.2024
 * \version 1.0
 * \author Alex
*/

namespace lib {

///Structure representing a MEPHI student
struct Student {
  std::string name; ///< Student's name, second name and surname
  char group[8] = {'\0'}; ///< Group, which consists of letter B/A/M/S, year and group number (e.g. B23-505)
  float grade = 0.0f; ///< Student's average grade (varies from 0.0 to 5.0)
};

/** \defgroup str_struct Converting string into structure
  @{
*/
///Wrapper function for parsers
/**
 * Reads string and mode from std::cin
 * \param student Link to structure to which data is going to be written
 * \return EOF In case of EOF
 * \return 1 In case of incorrect input
 * \return 0 In case of no error
*/
short getStructFromStr(Student& student);
///Parser for std::string
/**
 * Parses string and inputs data into structure
 * \param student Link to structure to which data is going to be written
 * \param input_str String to be parsed
 * \throw std::runtime_error In case of invalid format of provided string
*/
void __fillStudent(Student& student, const std::string& input_str);
///Parser for char*
/**
 * Parses string and inputs data into structure
 * \param student Link to structure to which data is going to be written
 * \param str String to be parsed
 * \throw std::runtime_error In case of invalid format of provided string
*/
void __fillStudent(Student&, const char* str);
///Parser for char*+size_t
/**
 * Parses string and inputs data into structure
 * \param student Link to structure to which data is going to be written
 * \param str Vector of char to be parsed
 * \param len Size of provided vector
 * \throw std::runtime_error In case of invalid format of provided string
*/
void __fillStudent(Student& student, const char* str, size_t len);
/**@}*/

/** \defgroup struct_str Converting structure into string
  @{
*/
///Wrapper function for converters
/**
 * Calls functions, which create strings, and pushes their return strings into std::cout
 * \param student Structure providing name, group and average grade of a student
*/
void printStudent(const Student& student);
///Converts structure to string
/**
 * Takes name, group and grade, provided by structure and creates a string of format:
 * \code
 * student.name=KSA
 * student.group=Б23-123
 * student.grade=4.6
 * \endcode
 * \param student Structure, providing info
*/
std::string __structToStr(const Student& student);
///Converts structure into java properties string
/**
 * Takes name, group and grade, provided by structure and creates a string of format:
 * \code
 * {name="KSA", group="Б23-123", grade=4.6}
 * \endcode
 * \param student Structure, providing info
*/
std::string __structToProperties(const Student& student);
/**@}*/

};

#endif
