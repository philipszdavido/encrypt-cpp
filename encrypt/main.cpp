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
void encrypt(string);
void decrypt(string);

int main(int argc, const char * argv[]) {
        
    string filename = static_cast<string>(argv[1]);
    string extension = getFileExtension(filename);
    
    if (extension != "jpg") {
        cout << "Unsupported file type";
        return 1;
    }
    
    const char * mode = argv[2];
    
    cout << filename << "\n";
    cout << mode << "\n";

    
    if(strcmp(mode, "1") == 0) {
        encrypt(filename);
    }
    
    if(strcmp(mode, "2") == 0) {
        decrypt(filename);
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

void encrypt(string filename) {
    
    std::ifstream in(filename, std::ios::binary);
    std::vector<std::byte> data;
    
    char c;
    const char key = 0xAA;
    
    while (in.get(c)) {
        data.push_back(static_cast<byte>(c));
    }
    
    in.close();
    
    std::ofstream out(filename,
                      std::ios::binary);

    for (int i = 0; i < data.size(); ++i) {
        const byte v = data[i] ^ static_cast<byte>(key);
        out.put((char)v);
    }
    
    out.close();

}

void decrypt(string filename) {
    
    encrypt(filename);

}
