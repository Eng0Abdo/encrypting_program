// File name: CS112_A2_T4_S15,16_20230100_20230211_20230246.cpp

/* Purpose:
Program include 10 ciphers
[1]  Affine Cipher
[2]  Route Cipher
[3]  Atbash Cipher
[4]  Vignere Cipher
[5]  Baconian Cipher
[6]  Simple Substitution Cipher
[7]  Polybius Square Cipher
[8]  Morse Code
[9]  XOR Cipher
[10] Rail-fence Cipher
The program take message from user and user has to define which cipher he want to use
and the program can encrypt and decrypt */

// Authors:             
// Affine Cipher, Morse Code, XOR Cipher, Rail-fence Cipher                     by "Peter Gergis Sayed"         ID: 20230100      S:15,16
// Route Cipher, Atbash Cipher, Vignere Cipher and gathered the progeram        by "Abdelrhman Emad Mahmoud"    ID: 20230211      S:15,16
// Baconian Cipher, Simple Substitution Cipher, Polybius Square Cipher          by "Ammar Ali Ghazi"            ID: 20230246      S:15,16

// Emails: 
// bedoos2005@gmail.com       (Abdelrhman)
// ammaralighazi5@gmail.com   (Ammar)
// Petergergs15@gmail.com     (Peter)


#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <cctype>
#include <algorithm>
#include <array>
#include <iomanip>
#include <sstream>
using namespace std;


/// Affine Cipher [1]
void encrypt_Affine_Cipher()
{
    cout << "enter text you want to encrypt..." << endl;                            // (1)
    string my_str;
    getline(cin, my_str);
    for (char c : my_str)
    {
        c = tolower(c);
        if ((65 <= c && c <= 90) || (97 <= c && c <= 122))
        {
            int x = c - 'a';
            x = (x * 5 + 8);
            while (x > 25)
            {
                x -= 26;
            }
            cout << char(x + 'a');
        }
        else
        {
            cout << c;
        }
    }
    cout << "\n";
}

void decrypt_Affine_Cipher()
{                                                                                    // (1)
    cout << "enter text you want to decrypt..." << endl;
    string my_str;
    getline(cin, my_str);
    for (char c : my_str)
    {
        c = tolower(c);
        if ((65 <= c && c <= 90) || (97 <= c && c <= 122))
        {
            int x = c - 'a';
            x = 21 * (x - 8);
            while (x > 25 || x < 0)
            {
                if (x > 25)
                {
                    x -= 26;
                }
                else
                {
                    x += 26;
                }
            }
            cout << char(x + 'a');
        }
        else
        {
            cout << c;
        }
    }
    cout << "\n";
}

string str_lower(string str)
{                                                                      // (1)
    for (char& c : str)
    {
        c = tolower(c);
    }
    return str;
}


/// Route cipher [2]
string encrypt_Route_Cipher(const string& message, int column) {         //function to encode                      // (2)
    // Convert the message to uppercase
    string new_message;
    for (char c : message)
    {
        if (isalpha(c))
        {
            new_message += toupper(c);
        }
    }

    int rows_num = ceil(static_cast<double>(new_message.length()) / column);

    vector<vector<char>> stringMatrix;


    for (int i = 0; i < rows_num; i++)
    {
        vector<char> rowVector(column, ' '); // Initialize row with spaces
        for (int j = 0; j < column; j++)
        {
            int index = i * column + j;
            if (index >= new_message.size())
            {
                rowVector[j] = 'X';
            }
            if (index < new_message.size())
            {
                rowVector[j] = new_message[index];
            }
        }
        stringMatrix.push_back(rowVector);
    }

    string encrypted_Message = "";
    int start_col = 0;
    int end_col = column - 1;
    int start_row = 0;
    int end_row = rows_num - 1;

    while (start_col <= end_col && start_row <= end_row)
    {

        // Take rightmost column
        for (int i = start_row; i <= end_row; i++)
        {
            encrypted_Message += stringMatrix[i][end_col];
        }
        end_col--;

        // Take bottom row
        if (start_row <= end_row)
        {
            for (int i = end_col; i >= start_col; i--)
            {
                encrypted_Message += stringMatrix[end_row][i];
            }
            end_row--;
        }

        // Take leftmost column
        if (start_col <= end_col)
        {
            for (int i = end_row; i >= start_row; i--)
            {
                encrypted_Message += stringMatrix[i][start_col];
            }
            start_col++;
        }

        // Take top row
        for (int i = start_col; i <= end_col; i++)
        {
            encrypted_Message += stringMatrix[start_row][i];
        }
        start_row++;
    }
    cout << "the Encrypted_Message is : ";
    return encrypted_Message;
}

string decrypt_Route_Cipher(const string& message, int column_num) { //function to decode                         // (2)
    string new_Message;
    for (char c : message)
    {
        if (isalpha(c))
        {
            new_Message += toupper(c);
        }
    }

    int rows_num = ceil(static_cast<double>(new_Message.length()) / column_num);
    vector<vector<char>> string_matrix(rows_num, vector<char>(column_num, ' '));

    int index = 0;
    int start_col = 0;
    int end_col = column_num - 1;
    int start_row = 0;
    int end_row = rows_num - 1;

    while (start_col <= end_col && start_row <= end_row)
    {
        // fill rightmost column
        for (int i = start_row; i <= end_row; i++)
        {
            string_matrix[i][end_col] = new_Message[index++];
        }
        end_col--;

        // fill bottom row
        for (int i = end_col; i >= start_col; i--)
        {
            string_matrix[end_row][i] = new_Message[index++];
        }
        end_row--;

        // fill leftmost column
        if (start_col <= end_col)
        {
            for (int i = end_row; i >= start_row; i--)
            {
                string_matrix[i][start_col] = new_Message[index++];
            }
            start_col++;
        }

        // fill top row
        if (start_row <= end_row)
        {
            for (int i = start_col; i <= end_col; i++)
            {
                string_matrix[start_row][i] = new_Message[index++];
            }
            start_row++;
        }
    }

    string decrypted_message = "";
    for (int i = 0; i < rows_num; ++i)
    {
        for (int j = 0; j < column_num; ++j)
        {
            if (string_matrix[i][j] != 'X')
            {
                decrypted_message += string_matrix[i][j];
            }
        }
    }

    cout << "decryped_message is : ";
    return decrypted_message;
}


// Atbash Cipher [3]
// Atbash Cipher function version 1 function
string atbash_cipher_version1(string user_message)
{
    string new_message, encrypted_message;
    for (char c : user_message) {
        if (isalpha(c)) {
            new_message += toupper(c);
        }
        else if (c == ' ') {
            new_message += c;
        }
    }
    for (char c : new_message) {
        int difference;

        if (c == ' ') {
            encrypted_message += c;
            continue;
        }
        else {
            difference = c - 65;
            encrypted_message += char(90 - difference);
        }
    }
    return encrypted_message;
}

// Atbash Cipher function version 2 function
string atbash_cipher_version2(string user_message) {
    string new_message, encrypted_message;
    for (char c : user_message) {
        if (isalpha(c)) {
            new_message += toupper(c);
        }
        else if (c == ' ') {
            new_message += c;
        }
    }
    for (char c : new_message) {
        int difference;
        if (int(c) >= 65 && int(c) <= 77 || c == ' ') {
            if (c == ' ') {
                encrypted_message += c;
                continue;
            }
            difference = c - 65;
            encrypted_message += char(77 - difference);
        }
        else if (int(c) >= 78 && int(c) <= 90) {
            if (c == ' ') {
                encrypted_message += c;
                continue;
            }
            difference = c - 78;
            encrypted_message += char(90 - difference);

        }

    }
    return	encrypted_message;
}


// Vignere Cipher [4]
// function to repeat keyword till it have the same new_message length
string repeat_vignereCipher(string keyWord, string new_message)
{
    string keyMessage = "";
    int message_length = new_message.length();
    for (int i = 0; i < message_length; ++i)
    {
        keyMessage += toupper(keyWord[i % keyWord.length()]);
    }
    return keyMessage;
}

// Function to encode using Vigenere Cipher
string encode_vignereCipher(const string& user_message, const string& keyWord) {
    string new_message, encrypted_message;
    for (char c : user_message) {
        if (isalpha(c) || isdigit(c) || c == ' ') {
            new_message += toupper(c);
        }
    }
    string keyMessage = repeat_vignereCipher(keyWord, new_message);

    for (int i = 0; i < new_message.length(); ++i) {
        if (new_message[i] == ' ' || isdigit(new_message[i])) {
            encrypted_message += new_message[i];
        }
        else {
            int encryptedChar = ((new_message[i] + keyMessage[i]) % 26) + 'A';
            encrypted_message += encryptedChar;
        }
    }
    return encrypted_message;
}

// Function to decode using Vigenere Cipher
string decode_vignereCipher(const string& user_message, const string& keyWord) {
    string new_message, decrypted_message;
    for (char c : user_message) {
        if (isalpha(c) || isdigit(c) || c == ' ') {
            new_message += toupper(c);
        }
    }
    string keyMessage = repeat_vignereCipher(keyWord, new_message);

    for (int i = 0; i < new_message.length(); ++i) {
        if (new_message[i] == ' ' || isdigit(new_message[i])) {
            decrypted_message += new_message[i];
        }
        else {
            int decryptedChar = ((new_message[i] - keyMessage[i] + 26) % 26) + 'A';
            decrypted_message += decryptedChar;
        }
    }
    return decrypted_message;
}


// Baconian Cipher [5]
string table_cipher[26][2] = {                                                            // cipher table
                                {"A", "aaaaa"}, {"B", "aaaab"}, {"C", "aaaba"}, {"D", "aaabb"}, {"E", "aabaa"},
                                {"F", "aabab"}, {"G", "aabba"}, {"H", "aabbb"}, {"I", "abaaa"}, {"J", "abaab"},
                                {"K", "ababa"}, {"L", "ababb"}, {"M", "abbaa"}, {"N", "abbab"}, {"O", "abbba"},
                                {"P", "abbbb"}, {"Q", "baaaa"}, {"R", "baaab"}, {"S", "baaba"}, {"T", "baabb"},
                                {"U", "babaa"}, {"V", "babab"}, {"W", "babba"}, {"X", "babbb"}, {"Y", "bbaaa"},
                                {"Z", "bbaab"}
};

string baconian_encode(string plaintext) {
    string ciphertext = "";
    for (char c : plaintext) {
        if (isalpha(c)) {
            ciphertext += table_cipher[toupper(c) - 65][1] + ' ';
        }
        else {
            ciphertext += c;
            ciphertext += ' ';
        }
    }
    return ciphertext;
}

string baconian_decode(string ciphertext) {
    string plaintext = "";
    string binary = "";
    for (char c : ciphertext) {
        if (c == ' ') {
            if (!binary.empty()) {
                plaintext += char(stoi(binary, 0, 2) + 65);
                binary.clear();
            }
        }
        else if (c == 'a' || c == 'b') {
            binary += (c == 'a') ? '0' : '1';
        }
        else {
            plaintext += c;
        }
    }
    if (!binary.empty()) {
        plaintext += char(stoi(binary, 0, 2) + 65);
    }
    return plaintext;
}


// Simple Substitution Cipher [6]
string cipher_alpha_create(string key) {
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string cipherAlphabet;
    for (char c : key) {
        cipherAlphabet += c;
        alphabet.erase(remove(alphabet.begin(), alphabet.end(), c), alphabet.end());
    }
    cipherAlphabet += alphabet;
    return cipherAlphabet;
}

bool isalpha1(string str) {
    for (char c : str) {
        if (!isalpha(c)) {
            return false;
        }
    }
    return true;
}

string encrypt(string plaintext, string cipher_alpha) {
    string ciphertext;
    for (char c : plaintext) {
        if (isalpha(c)) {
            char newChar = islower(c) ? tolower(cipher_alpha[c - 'a']) : toupper(cipher_alpha[c - 'A']);
            ciphertext += newChar;
        }
        else {
            ciphertext += c;
        }
    }
    return ciphertext;
}

string decrypt(string ciphertext, string cipher_alpha) {
    string plaintext;
    for (char c : ciphertext) {
        if (isalpha(c)) {
            plaintext += islower(c) ? 'a' + distance(cipher_alpha.begin(), find(cipher_alpha.begin(), cipher_alpha.end(), tolower(c))) :
                'A' + distance(cipher_alpha.begin(), find(cipher_alpha.begin(), cipher_alpha.end(), tolower(c)));
        }
        else {
            plaintext += c;
        }
    }
    return plaintext;
}


// Polybius Square Cipher [7]
string encrypt_polybiusSquare_Cipher(string key, char alpha_array[5][5], string message) {
    string n_message = "";
    for (char c : message) {
        c = toupper(c);
        if (c == 'J') { c = 'I'; }
        if (isalpha(c)) {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    if (alpha_array[i][j] == c) {
                        n_message += key[i];
                        n_message += key[j];
                    }
                }
            }
        }
        else {
            n_message += c;
        }
    }
    return n_message;
}

string decrypt_polybiusSquare_Cipher(string key, char alpha_array[5][5], string message) {
    string n_message = "";
    int n = size(message);
    for (int i = 0; i < n; i++) {
        if (isdigit(message[i]) && isdigit(message[i + 1])) {
            for (int j = 0; j < 5; j++) {
                if (message[i] == key[j]) {
                    for (int k = 0; k < 5; k++) {
                        if (message[i + 1] == key[k]) {
                            n_message += alpha_array[j][k];
                            break;
                        }
                    }
                    break;
                }
            }
            i++;
        }
        else {
            n_message += message[i];
        }
    }
    return n_message;
}


// Morse Code [8]
vector<string> split_string(const string& str) {
    vector<string> result;
    string delimiter = " "; // Three spaces as delimiter
    size_t pos = 0;
    size_t prev = 0;

    while ((pos = str.find(delimiter, prev)) != string::npos) {
        result.push_back(str.substr(prev, pos - prev));
        prev = pos + delimiter.length();
    }
    // Push back the last part of the string
    result.push_back(str.substr(prev));

    return result;
}

int findIndex(const std::string arr[], int size, const std::string& target) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == target) {
            return i; // Return the index where the target string is found
        }
    }
    return -1; // Return -1 if the target string is not found in the array
}

void morse_cipher() {
    cout << "enter text to encrypt" << endl;
    array<string, 37> morseCodeArray = {
        ".-",
        "-...",
        "-.-.",
        "-..",
        ".",
        "..-.",
        "--.",
        "....",
        "..",
        ".---",
        "-.-",
        ".-..",
        "--",
        "-.",
        "---",
        ".--.",
        "--.-",
        ".-.",
        "...",
        "-",
        "..-",
        "...-",
        ".--",
        "-..-",
        "-.--"
        "--..",
        "-----",
        ".----",
        "..---",
        "...--",
        "....-",
        ".....",
        "-....",
        "--...",
        "---..",
        "----.",
        " "
    };

    string text;
    string ciphered_text = "";
    getline(cin >> ws, text);
    for (char c : text) {
        c = tolower(c);
        if (isalpha(c)) {
            ciphered_text += (morseCodeArray[c - 'a'] + " ");
        }
        else if (isdigit(c)) {
            ciphered_text += (morseCodeArray[c - '0' + 25] + " ");
        }
        else if (c == ' ') {
            ciphered_text += "  ";
        }
    }
    cout << ciphered_text << endl;
}

void morse_decipher() {
    cout << "enter text to decrypt" << endl;

    string morseCodeArray[37] = {
    ".-",
    "-...",
    "-.-.",
    "-..",
    ".",
    "..-.",
    "--.",
    "....",
    "..",
    ".---",
    "-.-",
    ".-..",
    "--",
    "-.",
    "---",
    ".--.",
    "--.-",
    ".-.",
    "...",
    "-",
    "..-",
    "...-",
    ".--",
    "-..-",
    "-.--",
    "--..",
    "-----",
    ".----",
    "..---",
    "...--",
    "....-",
    ".....",
    "-....",
    "--...",
    "---..",
    "----.",
    ""
    };
    string text;
    string deciphered_text = "";
    getline(cin >> ws, text);
    vector<string> chars = split_string(text);
    bool valid = false;
    for (int i = 0; i < chars.size(); i++) {
        if (findIndex(morseCodeArray, 37, chars[i]) != -1) {
            valid = true;
        }
        else {
            valid = false;
            cout << "Please enter valid morse code";
            break;
        }
    }
    if (valid) {
        for (int i = 0; i < chars.size(); i++) {
            if (size(chars[i]) == 5) {
                cout << char(findIndex(morseCodeArray, 37, chars[i]) + '0' - 26);
            }
            else if (chars[i] == "") {
                cout << " ";
            }
            else if (size(chars[i]) < 5) {
                cout << char(findIndex(morseCodeArray, 37, chars[i]) + 'a');
            }
        }
    }
    cout << '\n';
}


// XOR Cipher [9]
string remove_spaces(string text) {
    string new_string;
    for (char c : text) {
        if (isdigit(c) || isalpha(c)) {
            new_string += c;
        }
    }
    return new_string;
}

string xor_encrypt(const string& message, const string& key) {
    string encrypted_text;
    int key_length = key.length();
    int j = 0;
    for (char c : message) {
        encrypted_text += char(c ^ key[j]);
        j = (j + 1) % key_length;
    }
    return encrypted_text;
}

string xor_decrypt(const string& hex_data, const string& key) {
    stringstream ss;
    string decrypted_text;
    int key_length = key.length();
    int j = 0;

    // Iterate over pairs of characters (representing hex values)
    for (size_t i = 0; i < hex_data.length(); i += 2) {
        // Convert hex pair to integer
        int hex_value;
        stringstream(hex_data.substr(i, 2)) >> hex >> hex_value;

        // Perform XOR operation with corresponding key character
        decrypted_text += hex_value ^ key[j];

        // Increment key index and loop around if necessary
        j = (j + 1) % key_length;
    }

    return decrypted_text;
}


// Rail fence Cipher [10]
string rail_fence_encrypt(string& plaintext, int rails) {
    plaintext = remove_spaces(plaintext);
    string ciphertext;
    int n = plaintext.length();
    vector<vector<char>> railMatrix(rails, vector<char>(n, ' '));

    int row = 0;
    bool down = false;
    for (int i = 0; i < n; i++) {
        if (row == 0 || row == rails - 1)
            down = !down;
        railMatrix[row][i] = plaintext[i];
        down ? row++ : row--;
    }
    for (int i = 0; i < rails; i++)
        for (int j = 0; j < n; j++)
            if (railMatrix[i][j] != ' ')
                ciphertext.push_back(railMatrix[i][j]);

    return ciphertext;
}

string rail_fence_decrypt(const string& ciphertext, int rails) {
    string plaintext;
    int n = ciphertext.length();
    vector<vector<char>> railMatrix(rails, vector<char>(n, ' '));
    int index = 0;
    for (int i = 0; i < rails; i++) {
        int row = 0;
        bool down = false;
        for (int j = 0; j < n; j++) {
            if (row == 0 || row == rails - 1)
                down = !down;

            if (row == i) {
                railMatrix[row][j] = ciphertext[index++];
            }

            down ? row++ : row--;
        }
    }
    int index2 = 0;
    for (int i = 0; i < n; i++) {
        int row = 0;
        bool down = false;
        for (int j = 0; j < rails; j++) {
            if (row == 0 || row == rails - 1)
                down = !down;

            if (row == j) {
                plaintext.push_back(railMatrix[row][i]);
                index2++;
            }

            down ? row++ : row--;
        }
    }
    plaintext = remove_spaces(plaintext);
    return plaintext;
}


int main() {
    cout << "Welcome, this program intclude 10 program to cipher and decipher message," << endl;
    while (true) {
        cout << "(A)Affine Cipher           (B)Route Cipher                (C)Atbash Cipher.";
        cout << "\n(D)Vignere Cipher          (E)Baconian Cipher             (F)Simple Substitution Cipher.";
        cout << "\n(G)Polybius Square Cipher  (H)Morse Code                  (I)XOR Cipher.";
        cout << "\n(J)Rail-fence Cipher       (K)exit.\n";
        string choice;
        cin >> choice;
        //-----------------------------------------------------------------------------------------------------
        if (choice == "a" || choice == "A") {                                                                  // program 1
            cout << "Welcome to this program" << endl;
            cout << "Please enter your choice" << endl;
            cin.ignore(100, '\n');
            while (true) {
                cout << "a- Cipher a message" << endl;
                cout << "b- Decipher a message" << endl;
                cout << "c- End" << endl;
                string choice2 = "";

                getline(cin, choice2);
                choice2 = str_lower(choice2);
                if (choice2 == "a") {
                    encrypt_Affine_Cipher();
                }
                else if (choice2 == "b") {
                    decrypt_Affine_Cipher();
                }
                else if (choice2 == "c") {
                    break;
                }
                else {
                    cout << "please enter valid choice" << endl;
                }
            }
        }
        //----------------------------------------------------------------------------------------------------------
        else if (choice == "b" || choice == "B")                                                                 // program 2
        {
            while (true)
            {
                string message;
                int keyNum;
                string choice;
                cout << "\nwhat do you want?\n";
                cout << "[a] encode\n";
                cout << "[b] decode\n";
                cout << "[c] exit\n";
                cin >> choice;
                cin.ignore();
                if (choice == "a" || choice == "A")
                {
                    cout << "\nplease enter your message: \n";
                    getline(cin, message);
                    cout << "please enter your key number: \n";
                    cin >> keyNum;
                    cout << encrypt_Route_Cipher(message, keyNum);
                }
                else if (choice == "b" || choice == "B")
                {
                    cout << "\nplease enter your message: \n";
                    getline(cin, message);
                    cout << "please enter your key number: \n";
                    cin >> keyNum;
                    cout << decrypt_Route_Cipher(message, keyNum);
                }
                else if (choice == "c" || choice == "C")
                {
                    break;
                }
                else
                {
                    cout << "Invalid input. Please enter a valid choice.\n";
                }
            }
        }

        //----------------------------------------------------------------------------------------------------------
        else if (choice == "c" || choice == "C") {                                                                 // program 3
            while (true) {
                cout << "Welcome to Atbash Cipher program\n";
                cout << "[a] Enter \n";
                cout << "[b] Exit\n";

                string choice;
                cin >> choice;

                if (choice == "a" || choice == "A") {
                    string choice1;
                    cout << "please choose the version you want to use\n";
                    cout << "[a] version 1\n";
                    cout << "[b] version 2\n";
                    cin >> choice1;

                    cin.ignore(100, '\n');
                    if (choice1 == "a" || choice1 == "A")
                    {
                        string message;
                        cout << "Enter the message you want to encrypt or decrypt: ";
                        getline(cin, message);
                        cout << "your message is :" << atbash_cipher_version1(message) << endl;
                    }
                    else if (choice1 == "b" || choice1 == "B")
                    {
                        string message;
                        cout << "Enter the message you want to encrypt or decrypt: ";
                        getline(cin, message);
                        cout << "your message is :" << atbash_cipher_version2(message) << endl;
                    }

                }
                else if (choice == "b" || choice == "B") {
                    break;
                }
                else {
                    cout << "Enter a valid choice\n";
                }
            }
        }
        //----------------------------------------------------------------------------------------------------------
        else if (choice == "d" || choice == "D") {                                                             // program 4

            while (true)
            {
                string choice, message, keyWord;
                cout << "choose what do you want\n";
                cout << "[A] encode\n";
                cout << "[B] decode\n";
                cout << "[C] exit\n";
                cin >> choice;
                cin.ignore();
                if (choice == "a" || choice == "A") {
                    cout << "Enter your message(maximum 80 characters): \n";
                    while (true)
                    {
                        getline(cin, message);
                        if (message.length() > 80)
                        {
                            cout << "your message must be less than 80 characters:\n";
                            cin.ignore();
                            continue;
                        }
                        else { break; }
                    }
                    cout << "Enter your key word(maximum 8 characters): \n";
                    while (true)
                    {
                        cin >> keyWord;
                        if (keyWord.length() > 8)
                        {
                            cout << "your key word must be less than 8 characters:\n";
                            cin.ignore();
                            continue;
                        }
                        else { break; }
                    }
                    cout << "Encrypted message: " << encode_vignereCipher(message, keyWord) << endl;
                }
                else if (choice == "b" || choice == "B")
                {
                    cout << "Enter your message(maximum 80 characters): \n";
                    while (true)
                    {
                        getline(cin, message);
                        if (message.length() > 80)
                        {
                            cout << "your message must be less than 80 characters:\n";
                            cin.ignore();
                            continue;
                        }
                        else { break; }
                    }
                    cout << "Enter your key word(maximum 8 characters): \n";
                    while (true)
                    {
                        cin >> keyWord;
                        if (keyWord.length() > 8)
                        {
                            cout << "your key word must be less than 8 characters:\n";
                            cin.ignore();
                            continue;
                        }
                        else { break; }
                    }
                    cout << "Decrypted message: " << decode_vignereCipher(message, keyWord) << endl;
                }
                else if (choice == "c" || choice == "C")
                {
                    break;
                }
                else {
                    continue;
                }
                cin.ignore(100, '\n');
            }
        }
        //----------------------------------------------------------------------------------------------------------
        else if (choice == "e" || choice == "E") {                                                             // program 5
            cout << "# Welcome to Baconian Cipher program," << endl;                                  // welcome message
            cin.ignore();
            while (true) {
                cout << "1)Cipher a message.\n2)Decipher a message.\n3)End.\n>> ";
                string c = "";
                getline(cin, c);
                if (size(c) != 1) { c = "5"; }
                if (c[0] != '1' && c[0] != '2' && c[0] != '3') { cout << "enter valid choice,\n"; continue; }
                if (c[0] == '3') { break; }
                if (c[0] == '1') {
                    cout << "Enter your message: ";
                    string message = "";
                    getline(cin, message);                                                                    // get message
                    cout << "Encrypted message: " << baconian_encode(message) << endl;
                }
                else if (c[0] == '2') {
                    cout << "Enter your message: ";
                    string message = "";
                    getline(cin, message);                                                                    // get message
                    cout << "Decrypted message: " << baconian_decode(message) << endl;
                }
            }

        }
        //----------------------------------------------------------------------------------------------------------
        else if (choice == "f" || choice == "F") {                                                             // program 6
            cout << "# Welcome to Simple Substitution Cipher program," << endl;                                  // welcome message
            cin.ignore();
            while (true) {
                cout << "1)Cipher a message.\n2)Decipher a message.\n3)End.\n>> ";
                string c = "";
                getline(cin, c);
                if (size(c) != 1) { c = "5"; }
                if (c[0] != '1' && c[0] != '2' && c[0] != '3') { cout << "enter valid choice,\n"; continue; }
                if (c[0] == '3') { break; }
                if (c[0] == '1') {
                    cout << "Enter your message: ";
                    string message = "";
                    getline(cin, message);                                                                    // get message

                    string key = "";
                    while (key.size() != 5 || !isalpha1(key)) {                                                           // get key
                        cout << "Enter your key: ";
                        getline(cin, key);
                        if (key.size() != 5 || !isalpha1(key)) {
                            cout << "# enter valid key," << endl;
                        }
                    }

                    string cipher_alpha = cipher_alpha_create(key);
                    cout << "Encrypted message: " << encrypt(message, cipher_alpha) << endl;
                }
                else if (c[0] == '2') {
                    cout << "Enter your message: ";
                    string message = "";
                    getline(cin, message);                                                                    // get message

                    string key = "";
                    while (key.size() != 5 || !isalpha1(key)) {                                                           // get key
                        cout << "Enter your key: ";
                        getline(cin, key);
                        if (key.size() != 5 || !isalpha1(key)) {
                            cout << "# enter valid key," << endl;
                        }
                    }

                    string cipher_alpha = cipher_alpha_create(key);
                    cout << "Decrypted message: " << decrypt(message, cipher_alpha) << endl;
                }
            }
        }
        //----------------------------------------------------------------------------------------------------------
        else if (choice == "g" || choice == "G") {                                                             // program 7

            cout << "welcome to our program that encrypt and decrypt message using key,\n";  // welcome message
            cin.ignore(100, '\n');
            while (true) {
                cout << "1)open.\n2)exit.\n>> ";
                string c = "";
                getline(cin, c);
                if (size(c) != 1) { c = "5"; }
                if (c[0] == '1') {
                    string key;
                    while (true) {                                                                   // get valid key
                        cout << "Enter the key: ";
                        getline(cin, key);
                        string n_key;
                        int z = size(key);
                        for (int i = 0; i < z; i++) {
                            if (isdigit(key[i]) && key[i] > '0' && key[i] < '6' /* && !in  */) {
                                n_key += key[i];
                            }
                        }
                        if (n_key.length() == 5) {
                            key = n_key;
                            break;
                        }
                        else { cout << "Enter a valid key,\n"; }
                    }

                    string message = "";
                    cout << "Enter your message: ";
                    getline(cin, message);                                                           // get message

                    int n_n;
                    while (true) {                                                                   // get he want to encyript or decyript the message
                        string n = "";
                        cout << "1)Encription.\n2)Decription.\n>> ";
                        getline(cin, n);
                        if (n.length() == 1 && isdigit(n[0])) {
                            n_n = stoi(n);
                            break;
                        }
                        cout << "Enter valid choice,\n";
                    }

                    char alpha_array[5][5] = {
                                            {'A', 'B', 'C', 'D', 'E'},
                                            {'F', 'G', 'H', 'I', 'K'},
                                            {'L', 'M', 'N', 'O', 'P'},
                                            {'Q', 'R', 'S', 'T', 'U'},
                                            {'V', 'W', 'X', 'Y', 'Z'} };
                    if (n_n == 1) { cout << "Encrypted message: " << encrypt_polybiusSquare_Cipher(key, alpha_array, message) << endl; }
                    else { cout << "Decrypted message: " << decrypt_polybiusSquare_Cipher(key, alpha_array, message) << endl; }
                }
                else if (c[0] == '2') { break; }
                else { cout << "enter valid choice,\n"; }
            }
        }

        //----------------------------------------------------------------------------------------------------------
        else if (choice == "h" || choice == "H") {                                                             // program 8

            while (true) {
                cout << "Please enter your choice" << endl;
                cout << "a) cipher" << endl;
                cout << "b) decipher" << endl;
                cout << "c) exit" << endl;
                string choice;
                cin >> choice;
                if (choice == "a" || choice == "A") {
                    morse_cipher();

                }
                else if (choice == "b" || choice == "B") {
                    morse_decipher();
                }
                else if (choice == "c" || choice == "C") {
                    break;
                }
                else {
                    cout << "please enter valid choice" << endl;
                }
            }
        }
        //----------------------------------------------------------------------------------------------------------
        else if (choice == "i" || choice == "I") {                                                             // program 9
            while (true) {
                cout << "Please enter your choice" << endl;
                cout << "a) cipher" << endl;
                cout << "b) decipher" << endl;
                cout << "c) exit" << endl;
                string choice;
                cin >> choice;
                if (choice == "a" || choice == "A") {
                    cout << "Please enter text to encrypt" << endl;
                    string message;
                    getline(cin >> ws, message);
                    cout << "Please enter encrypt key" << endl;
                    string key;
                    cin >> key;
                    string encrypted_text = xor_encrypt(message, key);
                    cout << "Encrypted text: " << encrypted_text << endl;
                    cout << "Encrypted text (hex): ";
                    for (char c : encrypted_text) {
                        cout << hex << setw(2) << setfill('0') << int(c) << " ";
                    }
                    cout << endl;
                }
                else if (choice == "b" || choice == "B") {
                    cout << "enter text to decrypt" << endl;
                    string encrypted_text;
                    getline(cin >> ws, encrypted_text);
                    cout << "enter key" << endl;
                    string key;
                    cin >> key;
                    encrypted_text = remove_spaces(encrypted_text);
                    string decrypted_text = xor_decrypt(encrypted_text, key);
                    cout << "Decrypted text: " << decrypted_text << endl;
                }
                else if (choice == "c" || choice == "C") {
                    break;
                }
                else {
                    cout << "please enter valid choice" << endl;
                }
            }
        }
        //----------------------------------------------------------------------------------------------------------
        else if (choice == "j" || choice == "J") {                                                             // program 10
            while (true) {
                cout << "Please enter your choice" << endl;
                cout << "a) cipher" << endl;
                cout << "b) decipher" << endl;
                cout << "c) exit" << endl;
                string choice;
                cin >> choice;
                if (choice == "a" || choice == "A") {
                    cout << "Please enter text to encrypt" << endl;
                    string message;
                    getline(cin >> ws, message);
                    cout << "Please enter encrypt rail" << endl;
                    int rails;
                    cin >> rails;
                    string encrypted_text = rail_fence_encrypt(message, rails);
                    cout << "Encrypted text: " << encrypted_text << endl;

                }
                else if (choice == "b" || choice == "B") {
                    cout << "enter text to decrypt" << endl;
                    string encrypted_text;
                    getline(cin >> ws, encrypted_text);
                    cout << "enter key" << endl;
                    int rails;
                    cin >> rails;
                    string decrypted_text = rail_fence_decrypt(encrypted_text, rails);
                    cout << "Decrypted text: " << decrypted_text << endl;
                }
                else if (choice == "c" || choice == "C") {
                    break;
                }
                else {
                    cout << "please enter valid choice" << endl;
                }
            }
        }
        //----------------------------------------------------------------------------------------------------------
        else if (choice == "k" || choice == "K") {                                                                                                      // exit
            break;
        }
        //----------------------------------------------------------------------------------------------------------
        else {                                                                                                      // unvalid choice
            cout << "# enter valid choice,\n";
        }
    }

    // Finally the end (*_*)
    return 0;
}
