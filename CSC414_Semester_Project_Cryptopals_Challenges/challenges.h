#pragma once

//this header file has definitions that execute code for each of the cryptopals challenges, to be 
//called as functions in the main Crytpopals Project.cpp file

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

//challenge 1: hex to base64 
void challenge1();

//challenge 2: fixed XOR 
void challenge2();

//challenge 3: Single-byte XOR Cipher 
void challenge3();

//challenge 4: Detect single-character XOR 
void challenge4();

//challenge 5: Implement Repeating-key XOR 
void challenge5();

//challenge 6: Break Repeating-key XOR 
void challenge6();

//challenge 7: AES in ECB
void challenge7();

//challenge 8: Detect AES in ECB
void challenge8();