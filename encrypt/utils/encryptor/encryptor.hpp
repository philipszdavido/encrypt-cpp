//
//  encryptor.hpp
//  encrypt
//
//  Created by Chidume Nnamdi on 06/08/2025.
//

#ifndef encryptor_hpp
#define encryptor_hpp

#include <stdio.h>
#include <string>

using namespace std;

class Encryptor {
    
public:
    Encryptor(const string& password, const char key);
    void encrypt(const string& filename, const string& password, const string& signature);
    void decrypt(const string& filename, const string& password, const string& signature);
    bool isEncrypted(const string& signature, vector<byte>& data);
    
private:
    const string& password;
    const char key;
    
};
#endif /* encryptor_hpp */
