#pragma once

//this header file has functions commonly used for the Cryptopals challenges

#include <vector>
#include <string>
#include <sstream>
#include <iostream>


//openssl includes
#include <openssl\aes.h>

using namespace std;

//hex decoder (ch 1)
vector<unsigned char> hexDecode(string);

//hex encoder (ch 2)
string hexEncode(vector<unsigned char>& bytes);

//fixed xor (ch 2)
vector<unsigned char> fixedXOR(vector<unsigned char>& hex1, vector<unsigned char>& hex2);

//b64 decode (ch 6)
vector<unsigned char> b64Decode(string);

//base 64 encoder (ch 1)
string b64Encode(vector<unsigned char>);

//single-character XOR, XOR's every byte in the input buffer against a single character (ch 3)
string xorChar(vector<unsigned char>, unsigned char);

//english plaintext scorer, outputs a score based on how likely the input is to be english plaintext (ch 3)
double englishScore(string);

//hamming distance calculator (ch 6)
int calcHammingDistance(string, string);

//key size guesser (ch 6)
void guessKeySize(vector<unsigned char>, vector<int>& bestKeySizes);

//aes in ecb decrypter (ch 7)
void aes_ecbDecrypt(vector<unsigned char>, unsigned int, vector<unsigned char>& decrypted, unsigned int, unsigned char*);

//detects duplicate blocks of bytes (ch 8)
bool isECB(vector<unsigned char>);