/* Implement the decryption function of Caeser Cipher with custom length key and decrypt the following – the
application should ask for a key between (0-26), and then the cipher text, and shall print the decryption. 

Key = 7, Cipher = OLSSV
Key = 19, Cipher = VKRIMHZKTIAR */

#include <iostream>

int main(){
    unsigned int key;
    std::string cipher;
    std::cout << "Enter a key (0-26): " << std::endl;
    std::cin >> key;
    std::cout << "Enter the word to decrypt: " << std::endl;
    std::cin >> cipher;
    std::string encrypted;

    for (char c: cipher){
        char a = c - key;
        if (a >= 'A'){
            encrypted += a;
        }
            
        else if (a < 'A'){
            a = ('Z' + 1) - ('A' - a);
            encrypted += a;
        }
           
    }
    std::cout << "The encryption is: " << encrypted << std::endl;





}

