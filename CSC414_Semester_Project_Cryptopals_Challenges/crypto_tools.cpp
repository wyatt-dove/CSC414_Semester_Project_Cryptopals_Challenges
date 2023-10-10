//implementation file for the crypto_tools.h header file

#include "crypto_tools.h"

//base64 characters
const string BASE_64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

//hex decoder
vector<unsigned char> hexDecode(string inString)
{
    //vector to hold the decoded hex values
    vector<unsigned char> decodedHex;

    size_t length = inString.length();

    for (int i = 0; i < length; i += 2)
    {
        //2 hex characters per byte, so isolate 2
        const string hexByte = inString.substr(i, 2);

        //convert the 2 hex chars to unsigned char (raw bytes)
        const unsigned char raw = strtol(hexByte.c_str(), 0, 16);

        //push the new bytes to the bytes vector
        decodedHex.push_back(raw);
    }

    return decodedHex;
}

//hex encoder to take the xor output and convert back to hex
string hexEncode(vector<unsigned char>& bytes)
{
    //hex values
    const char* hexValues = "0123456789abcdef";

    //delcare string to hold the result of the hex encoded bytes
    string hexString = " ";

    //iterate over each byte in the vector
    for (int i = 0; i < bytes.size(); i++)
    {
        //cut off a byte
        unsigned char byte1 = bytes[i];

        //shift right 4
        unsigned char hex1 = hexValues[(byte1 >> 4)];

        //0x0f to isoloate last 4 bits
        unsigned char hex2 = hexValues[(byte1 & 0x0f)];

        //push to the back of output
        hexString.push_back(hex1);
        hexString.push_back(hex2);
    }

    //return hex output
    return hexString;
}

//XOR function to check if both buffers are equal and XOR against each
//character in the vector to produce a vector with the XOR combination
vector<unsigned char> fixedXOR(vector<unsigned char>& hex1, vector<unsigned char>& hex2)
{
    //compare if the vectors are same length
    if (hex1.size() != hex2.size())
    {
        cout << "The input buffers need to be the same length." << endl;
    }

    //declares a vector named result, with the same size of vector hex1
    vector<unsigned char> result(hex1.size());

    //XOR against the two vectors up to the size of the vector
    for (int i = 0; i < result.size(); i++)
    {
        result[i] = hex1[i] ^ hex2[i];
    }

    return result;
}

//base 64 decoder
vector<unsigned char> b64Decode(string b64In)
{
    //length of input, variable for index, and a bool to detect padding
    unsigned int inLength = b64In.length();
    unsigned int index = 0;
    bool isPadded = false;

    //4 b64 characters make exactly 3 bytes
    unsigned char base64Chars[4] = { ' ', ' ', ' ', ' ' };
    //to store the 3 bytes
    unsigned char base64Bytes[3] = { ' ', ' ', ' ' };
    //to store the output
    vector<unsigned char> outputBytes;

    //iterate over every 4 base64 characters
    for (int i = 0; i < inLength; i += 4)
    {
        //peel off 4 chars
        for (int j = 0; j < 4; j++)
        {
            base64Chars[j] = b64In[index];
            index++;
        }


        //check if there's padding in the 4 characters because we'll need to handle it a bit differently
        for (int j = 0; j < 4; j++)
        {
            if (base64Chars[j] == '=')
            {
                isPadded = true;

            }
        }

        //proceed as normal if there's no padding
        if (isPadded == false)
        {
            //look up characters in base 64 table
            for (int j = 0; j < 4; j++)
            {
                base64Chars[j] = BASE_64.find(base64Chars[j]);
            }

            //manipulate the bits of each character into 8 bit bytes and store them in base64Bytes
            base64Bytes[0] = (base64Chars[0] << 2) + ((base64Chars[1] & 0x30) >> 4);                    //0x30 == 00110000
            base64Bytes[1] = ((base64Chars[1] & 0xf) << 4) + ((base64Chars[2] & 0x3c) >> 2);            //0xf == 1111, 0x3c == 00111100
            base64Bytes[2] = ((base64Chars[2] & 0x3) << 6) + base64Chars[3];                            //0x3 == 0011

            //push each byte to the back of the output vector
            for (int j = 0; j < 3; j++)
            {
                outputBytes.push_back(base64Bytes[j]);
            }
        }

        //deal with the padding
        else
        {
            //set padding input to 0 since that's what padding is
            for (int j = 0; j < 4; j++)
            {
                if (base64Chars[j] == '=')
                {
                    base64Chars[j] = '\0';
                }
            }
            //look up the non-padding characters
            for (int j = 0; j < 4; j++)
            {
                base64Chars[j] = BASE_64.find(base64Chars[j]);
            }

            //manipulate bits just like before
            base64Bytes[0] = (base64Chars[0] << 2) + ((base64Chars[1] & 0x30) >> 4);                    //0x30 == 00110000
            base64Bytes[1] = ((base64Chars[1] & 0xf) << 4) + ((base64Chars[2] & 0x3c) >> 2);            //0xf == 1111, 0x3c == 00111100
            base64Bytes[2] = ((base64Chars[2] & 0x3) << 6) + base64Chars[3];                            //0x3 == 0011

            //push each byte to the back of the output vector
            for (int j = 0; j < 3; j++)
            {
                outputBytes.push_back(base64Bytes[j]);
            }

        }

    }
    return outputBytes;
}

//b64 encoder -- takes a bytes vector as input and returns a base64 encoded string
string b64Encode(vector<unsigned char> bytes)
{
    string base64output = "";
    for (int i = 0; i < bytes.size(); i += 3)
    {
        //shave off 3 bytes from the vector (24 bits / 6 bits per base64 character = 4 base64 characters)
        unsigned char byte1 = bytes[i];
        unsigned char byte2 = bytes[i + 1];
        unsigned char byte3 = bytes[i + 2];

        //shift first byte by 2 to the right to isolate the first 6 bits
        //use this result to find the index of the corresponding base64 character
        base64output.push_back(BASE_64[(byte1 & 0xfc) >> 2]);                            //0xfc = 11111100

        //isolate last 2 bits of first byte, shift left 4
        //isolate first 4 bits of second byte, shift right 4
        //add these two results together to find the index of the corresponding base64 character
        base64output.push_back(BASE_64[((byte1 & 0x03) << 4) + ((byte2 & 0xf0) >> 4)]);  //0x03 = 00000011, 0xf0 = 11110000

        //isolate last 4 bits of second byte, shift left 2
        //isolate first 2 bits of third byte, shift right 6, add these two together
        //add results, use index to find the corresponding base64 character
        base64output.push_back(BASE_64[((byte2 & 0x0f) << 2) + ((byte3 & 0xc0) >> 6)]);  //0x0f = 00001111, 0xc0 = 11000000

        //isolate last 6 bits of third byte
        //use index to find corresponding base64 character
        base64output.push_back(BASE_64[(byte3 & 0x3f)]);                                 //0x3f = 00111111

    }
    //return
    return base64output;
}

//single-character XOR, XOR's every byte in the input buffer against a single character
string xorChar(vector<unsigned char> inBytes, unsigned char cipherChar)
{
    //vector to contain the output
    string xorOut;

    //XOR each byte against the test character, push to the back of the xorOut vector
    unsigned char xorByte;
    for (int i = 0; i < inBytes.size(); i++)
    {
        xorByte = (inBytes[i] ^ cipherChar);
        xorOut += xorByte;
    }
    return xorOut;
}

//english plaintext scoring function
double englishScore(string testInput)
{
    double score = 0.0;

    //alphabet character frequency from https://en.wikipedia.org/wiki/Letter_frequency#Relative_frequencies_of_letters_in_the_English_language
    //string with alphabet plus space character with special score of 15 since they're very common in english
    string alphabet = " abcdefghijklmnopqrstuvwxyz";
    double frequency[27] = { 15.0, 8.2, 1.5, 2.8, 4.3, 12.7, 2.2, 2.0, 6.1, 7.0, 0.15, 0.77, 4.0, 2.4, 6.7, 7.5, //a-o
                             1.9, 0.095, 6.0, 6.3, 9.1, 2.8, 0.98, 2.4, 0.15, 2.0, 0.074 };
    string punctuation = ".?!,:;";

    //score the string
    int size = testInput.size();
    char current = ' ';
    for (int i = 0; i < size; i++)
    {
        current = tolower(testInput[i]);

        //english plaintext very very rarely has ascii values above 127, so throw them out
        if (current > 127)
        {
            score = 0.0;
            return score;
        }
        //increment score by corresponding frequency
        if (alphabet.find(current) != string::npos)
        {
            score += frequency[alphabet.find(current)];
        }
        //common punctuation increments by a fixed 5
        else if (punctuation.find(current) != string::npos)
        {
            score += 5;
        }

    }

    return score;
}

//hamming distance calculator
int calcHammingDistance(string s1, string s2)
{
    unsigned char c1 = ' ';
    unsigned char c2 = ' ';

    //count for number of differences
    int count = 0;

    //loop through, find differences, increment at each difference
    for (int i = 0; i < s1.length(); i++)
    {
        //looks at individual bits and checks if they're the same using the XOR operator
        int partial = (s1[i] & 0xFF) ^ (s2[i] & 0xFF);
        //if xor returns true (meaning the bits don't match), increment count
        while (partial)
        {
            count += partial & 1;
            partial = partial >> 1;
        }
    }

    //return the number of differences tracked between the strings
    return count;
}

//key size guesser 
void guessKeySize(vector<unsigned char> input, vector<int>& bestKeySizes)
{
    //store input vector as a string since being able to use substr() is nice later
    string inputString = "";
    for (int i = 0; i < input.size(); i++)
    {
        inputString.push_back(input[i]);
    }

    //parallel vectors for keySizes and their normalized distances
    vector<double> normalizedDistances;
    vector<int> keySizes;

    //as the challenge states, try key sizes starting at 2 and going all the way to 40
    for (int i = 2; i <= 40; i++)
    {
        int keySize = i;

        //break the input into blocks of keySize length
        string b1, b2, b3, b4;
        b1 = inputString.substr(0, keySize);
        b2 = inputString.substr(keySize, keySize);
        b3 = inputString.substr((2 * keySize), keySize);
        b4 = inputString.substr((3 * keySize), keySize);

        //calc hamming distance between the blocks and normalize it
        int hamDist1 = calcHammingDistance(b1, b2);
        int hamDist2 = calcHammingDistance(b2, b3);
        int hamDist3 = calcHammingDistance(b3, b4);
        int sumHam = hamDist1 + hamDist2 + hamDist3;

        double normalized = (((double)sumHam) / (keySize * 3.0));

        normalizedDistances.push_back(normalized);
        keySizes.push_back(keySize);
    }
    //vector to store the 3 best key sizes
    int size = normalizedDistances.size();
    int index = 0;
    double minimum = normalizedDistances[0];

    for (int i = 0; i < 3; i++)
    {
        for (int j = 1; j < size; j++)
        {
            if (normalizedDistances[j] < minimum)
            {
                minimum = normalizedDistances[j];
                index = j;
            }
        }
        //save the smallest keysizes
        bestKeySizes.push_back(keySizes[index]);
        //set this normalized distance to a large number so it doesn't get chosen again
        normalizedDistances[index] = 100.0;
        //reset min and index
        minimum = normalizedDistances[0];
        index = 0;
    }
}

//aes in ecb decrypter
void aes_ecbDecrypt(vector<unsigned char> encrypted, unsigned int lenEncrypted, vector<unsigned char>& decrypted, unsigned int lenDecrypted, unsigned char* key)
{
    AES_KEY aesKey;
    AES_set_decrypt_key(key, 8 * AES_BLOCK_SIZE, &aesKey);

    //loop through the encrypted input
    for (unsigned int i = 0; i < lenEncrypted; i += 16)
    {
        //OPENSSL function: takes parameters (encrypted data input, decrypted data output, the AES key, and AES_DECRYPT to tell it to decrypt it)
        AES_ecb_encrypt(&encrypted[i], &decrypted[i], &aesKey, AES_DECRYPT);
    }
}

//detects duplicate chunks of bytes in the input
bool isECB(vector<unsigned char> rawBytes)
{
    //the given key length of 16 bytes
    const int KEY_LENGTH = 16;

    int size = rawBytes.size();
    string bytesStr = "";

    //store the raw bytes in a string so we can use substr
    for (int i = 0; i < size; i++)
    {
        bytesStr += rawBytes[i];
    }

    //will be broken into 16-byte blocks
    int numBlocks = bytesStr.length() / KEY_LENGTH;

    //loop through the 16-byte chunks and check for duplicates
    string b1 = "";
    string b2 = "";
    for (int i = 0; i < numBlocks; i++)
    {
        //first block of 16 bytes
        b1 = bytesStr.substr(i * KEY_LENGTH, KEY_LENGTH);
        for (int j = i + 1; j < numBlocks; j++)
        {
            //second block of 16 bytes
            b2 = bytesStr.substr(j * KEY_LENGTH, KEY_LENGTH);

            //return true if duplicates are found
            if (b1 == b2)
            {
                return true;
            }
        }
    }

    //return false if no duplicates were found
    return false;
}