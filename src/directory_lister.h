#include <iostream>
#include <string>
#include <filesystem>

std::string indent(std::string str, int indentation);
std::string get_base_path(std::filesystem::path file_path);
void list_tree(std::filesystem::path directory, std::ostream& out, int max_depth = 0, int indentation = 0);
