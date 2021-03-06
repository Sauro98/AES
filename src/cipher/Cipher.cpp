//
// Created by Ivano on 06/09/2018.
//

#include "Cipher.h"

void Cipher::crypt(fast_uint8 *input) const {
    State::addRoundKey(input, key.getKeyForRound(0));
    for (fast_uint8 round = 1; round < key.rounds; round++) {
        State::subBytes(input);
        State::shiftRows(input);
        State::mixColumns(input);
        State::addRoundKey(input, key.getKeyForRound(round));
    }
    State::subBytes(input);
    State::shiftRows(input);
    State::addRoundKey(input, key.getKeyForRound(key.rounds));
}

void Cipher::decrypt(fast_uint8 *input) const {
    State::addRoundKey(input,key.getEqInvKeyForRound(key.rounds));
    for (auto round = static_cast<fast_uint8>(key.rounds - 1); round > 0; round--) {
        State::invSubBytes(input);
        State::invShiftRows(input);
        State::invMixColumns(input);
        State::addRoundKey(input,key.getEqInvKeyForRound(round));
    }
    State::invSubBytes(input);
    State::invShiftRows(input);
    State::addRoundKey(input,key.getEqInvKeyForRound(0));
}

std::unique_ptr<fast_uint8[]> Cipher::cryptFile(const char *filename) const {
    size_t lenght;
    fast_uint8 *fileContent = readFile(filename, &lenght);
    fast_uint8* currHead = &fileContent[0];
    size_t loopTop = lenght/STATE_DIM;
    std::cout<<"start crypting: "<<lenght/STATE_DIM<<" iterations"<<std::endl;
    for (size_t index = 0; index < loopTop; index++) {
        crypt(currHead);
        currHead = &currHead[STATE_DIM];
    }
    std::cout<<"Finished"<<std::endl;
    writeToFile(filename, fileContent, lenght);
    return std::unique_ptr<fast_uint8[]>( fileContent);
}

std::unique_ptr<fast_uint8[]> Cipher::decryptFile(const char *filename) const {
    size_t lenght;
    fast_uint8 *fileContent = readFile(filename, &lenght);
    fast_uint8* currHead = &fileContent[0];
    std::cout<<"start decrypting: "<<lenght/STATE_DIM<<" iterations"<<std::endl;
    for (size_t index = 0; index < lenght; index += STATE_DIM) {
        decrypt(currHead);
        currHead = &currHead[STATE_DIM];
    }
    std::cout<<"Finished"<<std::endl;
    writeToFile(filename, fileContent, lenght);
    return std::unique_ptr<fast_uint8[]>(fileContent);
}

fast_uint8 *Cipher::readFile(const char *fileName, size_t *lenght) const {
    FILE * pFile;
    size_t lSize;
    fast_uint8 * buffer;
    size_t result;
    pFile = fopen(fileName, "rb");
    if (pFile == NULL) {
        std::stringstream ss;
        ss << "Error: could not open file" << fileName;
        throw std::runtime_error(ss.str());
    }
    // obtain file size:
    fseek(pFile, 0, SEEK_END);
    lSize = static_cast<size_t >(ftell(pFile));
    rewind(pFile);
    *lenght = lSize;
    while((*lenght)%16 != 0)
        (*lenght)++;
    // allocate memory to contain the whole file:
    buffer = new fast_uint8[*lenght];
    // copy the file into the buffer:
    result = fread(buffer, 1, lSize, pFile);
    if (result != lSize) {
        std::stringstream ss;
        ss << "An error occourred while reading the file" << fileName;
        throw std::runtime_error(ss.str());
    }
    /* the whole file is now loaded in the memory buffer. */
    // terminate
    fclose(pFile);
    return buffer;
}

void Cipher::writeToFile(const char *fileName, const fast_uint8 *content, size_t lenght) const {

    std::ofstream output_file;
    output_file.open(fileName, std::ios::binary);
    output_file.write(reinterpret_cast<const char*>(content), lenght);
    output_file.close();
}
