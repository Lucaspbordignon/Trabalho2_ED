#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <iostream>

std::string read_file(std::string filename);

std::vector<std::string> split(std::string str, const char* c);

template<typename T>
void print_vector(std::vector<T> v);

void show_progress(float percentage);

#endif
