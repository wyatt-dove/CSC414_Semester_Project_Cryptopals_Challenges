//implementation file for the challenges.h header file

#include "challenges.h"
#include "crypto_tools.h"

//the given key "YELLOW SUBMARINE" in hex for challenge 7
unsigned char CH7_KEY[16] = { 0x59, 0x45, 0x4C, 0x4C, 0x4F, 0x57, 0x20, 0x53, 0x55, 0x42, 0x4D, 0x41, 0x52, 0x49, 0x4E, 0x45 };

//logic for challenge 1: Hex to Base64 (jordan livingston)
void challenge1()
{

}

//logic for challenge 2: Fixed XOR (cole brady)
void challenge2()
{

}

//logic for challenge 3: Single-byte XOR cipher (wyatt dove)
void challenge3()
{
    //input hex string
    string input = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

    //hex decode input
    vector<unsigned char> inputBytes = hexDecode(input);

    //variables to track current and high score for english plaintext, as well as the cipher key
    double hiScore = 0;
    double currScore = 0;
    unsigned char key = ' ';

    //vectors to store current and best english plaintext so far
    string bestEnglish;
    string currEnglish;

    //test all possible character values (0-255) as the cipher key
    for (unsigned int i = 0; i < 256; i++)
    {
        // char being used as the cipher
        unsigned char cipher = i;

        //xor the decoded input against current cipher to produce a plaintext candidate
        currEnglish = xorChar(inputBytes, cipher);

        //score the output based on english-ness
        currScore = englishScore(currEnglish);

        //track the english plaintext with the highest score alongside its cipher character
        if (currScore > hiScore)
        {
            hiScore = currScore;
            bestEnglish = currEnglish;
            key = cipher;
        }
    }

    //bestEnglish should now have the most english-like plaintext stored in it
    //output results
    cout << "\nChallenge 3: Single-byte XOR Cipher" << endl;      //header
    cout << "\nHex Input: " << input << endl;                   //hex input string
    cout << "Decrypted Output: " << bestEnglish << endl;        //decrypted english plaintext string
    cout << "Cipher Key: " << key << endl;                      //character used for encryption
}

//logic for challenge 4: Detect single-character XOR (kristopher gavin)
void challenge4()
{

}

//logic for challenge 5: Implement Repeating-key XOR (daphney davis)
void challenge5()
{

}

//logic for challenge 6: Break Repeating-key XOR (kristopher gavin and daphney davis)
void challenge6()
{

}

//logic for challenge 7: AES in ECB Mode (wyatt dove)
void challenge7()
{
    //read input data from the file
    ifstream inFile;
    inFile.open("cryptopals.com_static_challenge-data_7.txt");
    if (!inFile.is_open())
    {
        cout << "Error reading file." << endl;
        return;
    }

    string line;
    string inText;
    while (getline(inFile, line))
    {
        inText += line;
    }
    inFile.close();

    //base 64 decode the input
    vector<unsigned char> cipherText = b64Decode(inText);
    //size of the input
    unsigned int enLen = cipherText.size();

    //allocate space for the decrypted text (should be equal to the encrypted text size)
    vector<unsigned char> decryptedText;
    decryptedText.resize(enLen);
    unsigned int lenDec = decryptedText.size();

    //decrypt
    //will need the cipher text, decrypted text output vector, length of both, and the KEY given by the challenge
    aes_ecbDecrypt(cipherText, enLen, decryptedText, lenDec, CH7_KEY);

    //update length if needed
    lenDec = decryptedText.size();

    //store the output in a string for easy output
    string output;
    for (int i = 0; i < lenDec; i++)
    {
        output += decryptedText[i];
    }

    cout << "\nChallenge 7: AES in ECB Mode" << endl << endl;
    cout << "Given AES Key: YELLOW SUBMARINE" << endl << endl;
    cout << "Decrypted output is long. Press enter to display." << endl;
    cin.get();
    cout << output;
}

//logic for challenge 8: Detect AES in ECB Mode (cole brady and jordan livingston)
void challenge8()
{

}