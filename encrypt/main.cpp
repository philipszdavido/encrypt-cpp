//
//  main.cpp
//  encrypt
//
//  Created by Chidume Nnamdi on 05/08/2025.
//

#include <iostream>
#include <fstream>

using namespace std;

string getFileExtension(string);
void encrypt(string, const string&);
void decrypt(string, const string&);
vector<byte> readfile(const string&);
byte logic(byte, size_t, const string&, const char);

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
    
    string extension = getFileExtension(filename);
            
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
    
    if(strcmp(mode, "1") == 0) {
        encrypt(filename, password);
    }
    
    if(strcmp(mode, "2") == 0) {
        decrypt(filename, password);
    }
    
    return 0;
    
}

string getFileExtension(string name) {
    
    string extension = "";
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

vector<byte> readfile(const string& filename) {
    
    std::ifstream in(filename, std::ios::binary);
    std::vector<std::byte> data;
    
    char c;
    
    while (in.get(c)) {
        data.push_back(static_cast<byte>(c));
    }
    
    in.close();
    
    return data;

}

void encrypt(string filename, const string& password) {
    
    vector<byte> data = readfile(filename);
    
    std::ofstream out(filename, std::ios::binary | std::ios::trunc);
    
    // add file sign
    for (int i = 0; i < signature.length(); ++i) {
        out.put(signature[i]);
    }

    for (int i = 0; i < data.size(); ++i) {
        
        const byte xored = logic(data[i], i, password, key);
        
        out.put((char)xored);
        
    }
    
    out.close();

}

void decrypt(string filename, const string& password) {
    
    vector<byte> data = readfile(filename);
    
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

        const byte xored = logic(data[i], j, password, key);
        
        out.put((char)xored);
        
    }
    
    out.close();
    
}

byte logic(byte data, size_t j, const string& password, const char key) {

    byte x = static_cast<byte>(password[j % password.size()]) ^ static_cast<byte>(key);
    
    const byte xored = data ^ x;
    
    return xored;

}
