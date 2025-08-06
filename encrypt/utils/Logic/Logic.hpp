//
//  Logic.hpp
//  encrypt
//
//  Created by Chidume Nnamdi on 06/08/2025.
//

#ifndef Logic_hpp
#define Logic_hpp

#include <stdio.h>
#include <iostream>

class Logic {
public:
    Logic();
    std::byte enc_logic(std::byte data, size_t j, const std::string& password, const char key);
};
#endif /* Logic_hpp */
