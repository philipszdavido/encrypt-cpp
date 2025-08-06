//
//  File.hpp
//  encrypt
//
//  Created by Chidume Nnamdi on 06/08/2025.
//

#ifndef File_hpp
#define File_hpp

#include <stdio.h>
#include <string>

class File {
public:
    File();
    std::vector<std::byte> readFile(const std::string& filename);
    std::string getFileExtension(const std::string& name);
    
};
#endif /* File_hpp */
