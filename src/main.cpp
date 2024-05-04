#include <iostream>
#include <fstream>
#include <filesystem>
#include "directory_lister.h"

int main(int argc, char* argv[]){
    // validate that at least one argument was provided 
    if (argc < 3){
        std::cout << "This program accepts, at minimum, two arguments" << std::endl;
        return  -1;
    }
    // determine the user's action based on their provided argument
    std::string command = argv[1];
    std::ostream* out;
    std::ofstream out_file;
    int max_depth = 0;
    // determine the stream to write to based on the  command
    if (command == "print"){
        out = &std::cout;
        // read the max depth, if provided
        if (argc == 4){
            try{
                max_depth = std::stoi(argv[3]);
            }
            catch (...){
                std::cout << "Please ensure that the maximum recurssion depth is a valid integer" << std::endl;
                return -1;
            }
        }
    }
    else if (command == "save"){
        switch (argc){
            case 3:
                std::cout << "Please provide the name of a file to save the directory tree to." << std::endl;
                return -1;
                break;
            
            case 4:
                out_file.open(argv[3]);
                out = &out_file;
                break;

            case 5:
                out_file.open(argv[3]);
                out = &out_file;
                // validate the max depth
                try{
                    max_depth = std::stoi(argv[4]);
                }
                catch (...){
                    std::cout << "Please ensure that the maximum recurssion depth is a valid integer" << std::endl;
                    return -1;
                }
                break;
            default:
                std::cout << "This command accepts at most four arguments" << std::endl;
                return -1;
                break;
        }
    
    }
    else{
        std::cout << "Unrecognized Command" << std::endl;
        return -1;
    }
    // validate the directory to list
    std::filesystem::directory_entry dir(argv[2]);
    if (dir.is_directory())
        list_tree(dir, *out, max_depth);
    else{
        std::cout << "Please provide the path of a valid directory" << std::endl;
        return -1;
    }
    // close the file if need
    if (command == "save")
        out_file.close();
}