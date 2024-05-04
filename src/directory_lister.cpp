#include <iostream>
#include <fstream>
#include <filesystem> 
#include <stdexcept>
#include "directory_lister.h"

// indents a string with a provided number of spaces
std::string indent(std::string str, int indentation){
    std::string indented;
    for (int i = 0; i < indentation; i++)
        indented += '\t';
    indented += str;
    return indented;
}

// returns a string of a file path with leading paths stripped
std::string get_base_path(std::filesystem::path file_path){
    std::string file_str = file_path.string();
    return file_str.substr(file_str.find_last_of("\\") + 1);
}

// recursively lists the entries and subdirectories of a directory
void list_tree(std::filesystem::path directory, std::ostream& out, int max_depth, int indentation){
    out << indent(get_base_path(directory), indentation) <<  "\\" << std::endl;
    for (auto const& i : std::filesystem::directory_iterator(directory)){
        if (i.is_directory() && (max_depth > indentation || max_depth == 0))
            list_tree(i.path(), out, max_depth, indentation + 1);
        else
            out << indent(get_base_path(i.path()), indentation + 1) << std::endl;
    }
}