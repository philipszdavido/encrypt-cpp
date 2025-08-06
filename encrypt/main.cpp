//
//  main.cpp
//  encrypt
//
//  Created by Chidume Nnamdi on 05/08/2025.
//

#include <iostream>
#include <fstream>
#include "encryptor.hpp"
#include "File.hpp"

using namespace std;

string signature = "NNAMDI_CHIDUME_SIGN";
const char key = 0xAA;

int main(int argc, const char * argv[]) {
        
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <filename> <mode: 1 - encrypt, 2 - decrypt> <password>\n";
        return 1;
    }
    
    string filename = static_cast<string>(argv[1]);
    const char* mode = argv[2];
    string password = static_cast<string>(argv[3]);
    
    File file;
    string extension = file.getFileExtension(filename);
            
    if (password.length() == 0) {
        cout << "There is no password.";
        return 1;
    }
    
    if (!mode) {
        cout << "Specify mode";
        return 1;
    }
        
    cout << "Filename: " << filename << "\n";
    cout << "Mode: " << mode << " : " << (*mode == '1' ? "Encryption" : "Decryption") << "\n";
    
    Encryptor enc(filename, key);
    
    if(strcmp(mode, "1") == 0) {
        enc.encrypt(filename, password, signature);
    }
    
    if(strcmp(mode, "2") == 0) {
        enc.decrypt(filename, password, signature);
    }
    
    return 0;
    
}


