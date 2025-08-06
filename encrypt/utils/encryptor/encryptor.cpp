//
//  encryptor.cpp
//  encrypt
//
//  Created by Chidume Nnamdi on 06/08/2025.
//

#include "encryptor.hpp"
#include "File.hpp"
#include "Logic.hpp"

#include <iostream>
#include <fstream>

Encryptor::Encryptor(const string& password, const char key)
    :password(password), key(key) {}

void Encryptor::encrypt(const string& filename, const string& password, const string& signature) {
    
    File file;
    Logic logic;

    vector<byte> data = file.readFile(filename);
    
    if (isEncrypted(signature, data)) {
        cout << "This file has already been encrypted." << endl;
        return;
    }
    
    std::ofstream out(filename, std::ios::binary | std::ios::trunc);
    
    // add file sign
    for (int i = 0; i < signature.length(); ++i) {
        out.put(signature[i]);
    }

    for (int i = 0; i < data.size(); ++i) {
        
        const byte xored = logic.enc_logic(data[i], i, password, key);
        
        out.put((char)xored);
        
    }
    
    out.close();

}

void Encryptor::decrypt(const string& filename, const string &password, const string& signature) {
    
    File file;
    Logic logic;

    vector<byte> data = file.readFile(filename);
    
    // check if signature is present
    
    size_t len = signature.length();
    string sig;
    
    if (password.empty()) {
        std::cerr << "Password cannot be empty.\n";
        return;
    }
    
    if (data.size() < signature.length()) {
        std::cerr << "File too short to contain valid signature.\n";
        return;
    }
    
    for (int i = 0; i < len; ++i) {
        cout << static_cast<char>(data[i]);
        sig += static_cast<char>(data[i]);
    }
    
    cout << "\n";
    
    cout << sig << "\n";
    cout << (sig == signature) << "\n" ;
    
    if (sig != signature) {
        std::cerr << "File is not encrypted with expected signature.\n";
        return;
    }
    
    std::ofstream out(filename, std::ios::binary | std::ios::trunc);
    
    // decrypt
    for (size_t i = len; i < data.size(); ++i) {

        size_t j = i - len;

        const byte xored = logic.enc_logic(data[i], j, password, key);
        
        out.put((char)xored);
        
    }
    
    out.close();
  
}

bool Encryptor::isEncrypted(const string& signature, vector<byte>& data) {
    
    string sig = "";
    
    for(int i = 0; i < signature.length(); ++i) {
        sig += static_cast<char>(data[i]);
    }
    
    if (sig == signature) {
        return true;
    }
    
    return false;
    
}
