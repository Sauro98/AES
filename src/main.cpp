#include <iostream>
#include "cipher/Cipher.h"
#include <ctime>

#define FILE_NAME "../testFile.txt"

int main() {
    static const uint8_t key128[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d,
                                     0x0e, 0x0f};
    std::clock_t start;

    start = std::clock();
    Cipher cipher(key128, 16);
    std::cout << "key exp time: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;

    start = std::clock();
    cipher.cryptFile(FILE_NAME);
    std::cout << "crypting time: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;

    start = std::clock();
    cipher.decryptFile(FILE_NAME);
    std::cout << "decrypting time: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;

    return 0;
}