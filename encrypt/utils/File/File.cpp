//
//  File.cpp
//  encrypt
//
//  Created by Chidume Nnamdi on 06/08/2025.
//

#include "File.hpp"

#include <iostream>
#include <fstream>

File::File() {};

std::vector<std::byte> File::readFile(const std::string& filename) {
    
    std::ifstream in(filename, std::ios::binary);
    std::vector<std::byte> data;
    
    char c;
    
    while (in.get(c)) {
        data.push_back(static_cast<std::byte>(c));
    }
    
    in.close();
    
    return data;

}

std::string File::getFileExtension(const std::string& name) {
    
    std::string extension = "";
    bool start = false;
    
    for (int i = 0; i < name.length(); ++i) {
        
        const char c = name[i];
        const char dot[] = {"."};

        if (start) {
            extension += c;
        }
        
        if (c == *dot) {
            start = true;
        }
                
    }
    
    return extension;

}
