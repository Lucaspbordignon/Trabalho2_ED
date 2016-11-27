#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <iostream>

/**
 * @brief Reads a whole file to a std::string
 * @param filename Path to the file that'll be readed
 */
std::string read_file(const std::string& filename);

/**
 * @brief Splits a std::string into a std::vector
 * @details For example split("aaa/b/ce", "/") returns {"aaa", "b", "ce"}
 *
 * @param str The string that'll be splitted
 * @param c The char where the string will be splitted
 */
std::vector<std::string> split(const std::string& str, const char* c);

/**
 * @brief Overloads the << operator for std::vector for printing
 */
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v);

/**
 * @brief A basic progress bar is shown
 * @details Every time you call, it'll overwrite the previously shown bar.
 *
 * @param percentage A number from 0 to 1, representing the percentage of the
 * bar that'll be filled
 */
void show_progress(float percentage);

#endif
