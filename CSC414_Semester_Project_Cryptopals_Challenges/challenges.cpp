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
    string hex1 = "1c0111001f010100061a024b53535009181c";
    string hex2 = "686974207468652062756c6c277320657965";

    //decode buffers
    vector<unsigned char> byte1 = hexDecode(hex1);
    vector<unsigned char> byte2 = hexDecode(hex2);

    //XOR both buffers
    vector<unsigned char> xorResult = fixedXOR(byte1, byte2);

    //encode XOR Result
    string output = hexEncode(xorResult);

    //display output
    cout << "\nChallenge 2: Fixed XOR" << endl << endl;
    cout << "Hex string #1: " << hex1 << endl;
    cout << "Hex string #2: " << hex2 << endl;
    cout << "The XOR Result of the two buffers is: " << output << endl;
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
    //given string and repeating xor key
    string asciiInput = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
    string key = "ICE";

    //input string is ascii, so just put all the characters in a vector to store the bytes -- no decoding needed
    vector <unsigned char> bytes;
    for (int i = 0; i < asciiInput.length(); i++)
    {
        bytes.push_back(asciiInput[i]);
    }

    //variables for repeating key encryption
    vector<unsigned char> output;       //store the output
    unsigned int position = 0;          //keep track of position in the repeating key "ICE"
    unsigned int size = bytes.size();   //size of the input
    //sequentially loop through the byte vector, encoding each byte sequentially with a character in the key
    for (unsigned int i = 0; i < size; i++)
    {
        //byte of the input
        unsigned char byte1 = bytes[i];
        //byte of the key
        unsigned char byte2 = key[position];
        //XOR them together
        unsigned char xorByte = (byte1 ^ byte2);
        //push result to the back of output vector
        output.push_back(xorByte);

        //update position in key as needed
        if (position == (key.length() - 1)) //if position is at the last index, reset to 0
        {
            position = 0;
        }
        else                                //else just increment position
        {
            position++;
        }
    }

    //hex encode the output bytes
    string hexOutput = hexEncode(output);

    //output the resulting string
    cout << "Challenge 5: Implement Repeating-Key XOR" << endl;
    cout << "\nInput String: " << endl << asciiInput << endl;
    cout << "\nRepeating-key Cipher: " << key << endl;
    cout << "\nEncrypted Hex String: " << endl << hexOutput << endl;
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
    //read input from input file
    ifstream inFile;
    inFile.open("cryptopals.com_static_challenge-data_8.txt");
    if (!inFile.is_open())
    {
        cout << "Error opening input file. Ensure it is in the correct directory." << endl;
        return;
    }

    //start testing each line for ECB encryption
    string line = "";
    string encLine = "";
    int currLine = 1;           //tracks current line
    int lineFound = 0;          //tracks line where ECB encryption is found
    bool detectedECB = false;   //flagged true when ECB encryption is found
    vector<unsigned char> bytes;

    //loop through the lines in the file until one is found with ECB encryption patterns
    while (detectedECB == false)
    {
        //get a line and hex decode it into bytes
        getline(inFile, line);
        bytes = hexDecode(line);

        //test if it has ECB encryption patterns
        //Note from challenge: "Remember that the problem with ECB is that it is stateless and deterministic; 
        //the same 16 byte plaintext block will always produce the same 16 byte ciphertext."
        //meaning we just need to find the string that has duplicate 16 byte blocks
        if (isECB(bytes))
        {
            lineFound = currLine;
            encLine = line;
            detectedECB = true;
        }

        currLine++;

    }

    inFile.close();

    cout << "Challenge 8: Detect AES in ECB" << endl;
    if (detectedECB == true)
    {
        cout << "\nECB Detected!" << endl;
        cout << "Duplicate blocks of ciphertext located in line: " << lineFound << endl;
        cout << "ECB-Encrypted ciphertext: " << encLine;
    }
    else
    {
        cout << "Could not detect an ECB-encrypted line in the input file" << endl;
    }
}
