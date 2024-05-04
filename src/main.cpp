#include <iostream>
#include <fstream>
#include <filesystem>
#include "directory_lister.h"

int main(int argc, char* argv[]){
    // validate that at least one argument was provided 
    if (argc < 4){
        std::cout << "This program accepts, at minimum, one arguments" << std::endl;
        return  -1;
    }
    // determine the user's action based on their provided argument
    std::string command = argv[1];
    std::ostream* out;
    std::ofstream out_file;
    // determine the stream to write to based on the  command
    if (command == "print")
        out = &std::cout;
    else if (command == "save"){
        // ensure that the the name of a file to save was provided
        if (argc < 4){
            std::cout << "Please provide the name of a file to save the directory tree to." << std::endl;
            return -1;
        }
        out_file.open(argv[3]);
        out = &out_file;
    }
    else{
        std::cout << "Unrecognized Command" << std::endl;
        return -1;
    }
    // validate the directory to list
    std::filesystem::directory_entry dir(argv[2]);
    if (dir.is_directory())
        list_tree(dir, *out);
    else{
        std::cout << "Please provide the path of a valid directory" << std::endl;
        return -1;
    }
    // close the file if need
    if (command == "save")
        out_file.close();
}