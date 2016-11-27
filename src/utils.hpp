#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <iostream>

std::string read_file(const std::string& filename);

std::vector<std::string> split(const std::string& str, const char* c);

template<typename T>
void print_vector(const std::vector<T>& v);

void show_progress(float percentage);

#endif
