//
//  Logic.cpp
//  encrypt
//
//  Created by Chidume Nnamdi on 06/08/2025.
//

#include "Logic.hpp"

#include <iostream>
#include <cstring>

Logic::Logic() {};

std::byte Logic::enc_logic(std::byte data, size_t j, const std::string& password, const char key) {
    
    std::byte x = static_cast<std::byte>(password[j % password.size()]) ^ static_cast<std::byte>(key);
    
    const std::byte xored = data ^ x;
    
    return xored;
    
}
