#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include <iterator>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <memory>
#include <unistd.h>

std::string read_file(std::string filename);

// executes a linux command
std::string exec(const std::string cmd);

std::vector<std::string> split(std::string str, const char* c);

template<typename T>
void print_vector(std::vector<T> v);

#endif
