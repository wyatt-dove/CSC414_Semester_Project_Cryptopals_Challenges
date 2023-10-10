// This is the main menu interface program for the Cryptopals challenges.
// Group members: Cole Brady, Jordan Livingston, Wyatt Dove, Daphney Davis, Kristopher Gavin

#include "challenges.h"
#include "crypto_tools.h"

using namespace std;

//display menu
void displayMenu();

int main()
{
    unsigned char selection = 'a';
    string in;

    while (selection != '0')
    {
        //display the menu
        displayMenu();

        getline(cin, in);
        selection = in[0];

        switch (selection)
        {
            //runs the code for challenge 1 (hex to base64) and outputs the solution
        case '1':
            challenge1();
            break;

            //runs the code for challenge 2 (fixed XOR) and outputs the solution
        case '2':
            challenge2();
            break;

            //runs the code for challenge 3 (single byte XOR cipher) and outputs the solution
        case '3':
            challenge3();
            break;

            //runs the code for challenge 4 (detect single-character XOR) and outputs the solution
        case '4':
            challenge4();
            break;

            //runs the code for challenge 5 (implement repeating-key XOR) and outputs the solution
        case '5':
            challenge5();
            break;

            //runs the code for challenge 6 (detect repeating-key XOR) and outputs the solution
        case '6':
            challenge6();
            break;

            //runs the code for challenge 7 (AES in ECB mode)
        case '7':
            challenge7();
            break;

            //runs the code for challenge 8 (detect AES in ECB mode)
        case'8':
            challenge8();
            break;

            //exit case
        case '0':
            cout << "Exiting." << endl;
            return 0;

            //invalid input
        default:
            cout << "Invalid input, please try again." << endl;
        }

        cout << "\nPress enter to return to menu selection." << endl;
        getline(cin, in);
        system("cls");

    }

    return 0;
}

void displayMenu()
{
    cout << "Cryptopals Cryptography Challenges Set 1 Solution Navigator" << endl << endl;

    cout << "1 - Convert Hex to Base64" << endl;
    cout << "2 - Fixed XOR" << endl;
    cout << "3 - Single-byte XOR cipher" << endl;
    cout << "4 - Detect single-character XOR" << endl;
    cout << "5 - Implement repeating-key XOR" << endl;
    cout << "6 - Break repeating-key XOR" << endl;
    cout << "7 - AES in ECB mode" << endl;
    cout << "8 - Detect AES in ECB mode" << endl << endl;

    cout << "Please select the challenge you wish to view (enter a number 1-8, or 0 to exit): ";
}