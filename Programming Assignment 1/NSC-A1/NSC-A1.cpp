#include<iostream>
#include<fstream>
using namespace std;

string cipher_text_1;
string cipher_text_2;
string cipher_text_3;
string cipher_text_4;
string cipher_text_5;
int hashvalue_length = 16;

string Hash(string str) {
    // hash function Hash() returns the hash string for a given string.
    string hash_string = "zzzzzzzzzzzzzzzz";
    int temp = hashvalue_length - str.size() % hashvalue_length;
    for (int i = 0; i < temp; i++) {
        str.append("z");
    }
    int hash_ascii_value[hashvalue_length] = {0};
    for (int i = 0; i < str.size(); i++) {
        hash_ascii_value[i % hashvalue_length] += str[i];
    }
    for (int i = 0; i < hashvalue_length; i++) {
        hash_ascii_value[i] %=26;
        hash_ascii_value[i] += 97;
        hash_string[i] = hash_ascii_value[i];
    }
    return hash_string;
}

string encrypt(string str, string key) {
    //decrypt a string using poly-alphabetic substitution with a known_key of length 4. Returns the encrypted string.
    int temp1,temp2;
    for (int i = 0; i < str.size(); i++) {
        temp1 = str[i];
        temp1 = temp1 - 97;
        temp2 = key[i % (key.size())];
        temp2 = temp2 - 97;
        temp1 = (temp1 + temp2) % 26;
        temp1 = temp1 + 97;
        str[i] = temp1;
    }
    return str;
}

string decrypt(string str, string key) {
    //decrypt a string using poly-alphabetic substitution with a known_key of length 4. Returns the decrypted string.
    int temp1,temp2;
    for (int i = 0; i < str.size(); i++) {
        temp1 = str[i];
        temp1 = temp1 - 97;
        temp2 = key[i % (key.size())];
        temp2 = temp2 - 97;
        if (temp1 < temp2) {
            temp1 = 26 + temp1 - temp2;
        }        
        else{
            temp1 = (temp1 - temp2) % 26;
        }
        temp1 = temp1 + 97;
        str[i] = temp1;
    }
    return str;
}

bool recognizable(string plaintext) {
    // checks the π property for the 5 plaintexts using the temp_key to check if the plaintext is recognizable or not. Retruns true or false accordingly.
    string original_text;
    string hash_string;
    original_text = plaintext.substr(0,plaintext.size() - hashvalue_length);
    hash_string = plaintext.substr(plaintext.size() - hashvalue_length);
    if (Hash(original_text)==hash_string) {
        return true;
    }
    return false;
}

string bruteforce() {
    // iterate from "aaaa" to "zzzz" and calls the checkfunc funciton() for every temp_key. Returns a string, either the found_key or "ERROR".
    string temp_key = "aaaa";
    for (int a = 0; a < 26; a++) {
        for (int b = 0; b < 26; b++) {
            for (int c = 0; c < 26; c++) {
                for (int d = 0; d < 26; d++) {
                    temp_key[0] = 97 + a;
                    temp_key[1] = 97 + b;
                    temp_key[2] = 97 + c;
                    temp_key[3] = 97 + d;

                    if (recognizable(decrypt(cipher_text_1, temp_key))){
                        if (recognizable(decrypt(cipher_text_2, temp_key))) {
                            if (recognizable(decrypt(cipher_text_3, temp_key))) {
                                if (recognizable(decrypt(cipher_text_4, temp_key))) {
                                    if (recognizable(decrypt(cipher_text_5, temp_key))) {
                                        return temp_key;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return "ERROR";
}

bool check_string(string original_text) {
    for (int i = 0; i < original_text.size(); i++) {
        if (!islower(original_text[i])) {
            return false;
        }
    }
    return true;
}

int main()
{
    //Main Function   

    ifstream infile;
    infile.open("key.txt");
    if (!infile.is_open()) {
        return 0;
    }
    string known_key;
    infile>>known_key;
    if (check_string(known_key) == false) {
        cout<<"Key is not appropriate";
        return 0;
    }
    infile.close();
    cout<<"Known key: "<<known_key<<endl<<endl; 

    infile.open("Original_texts.txt");
    if (!infile.is_open()) {
        return 0;
    }
    string original_text_1, original_text_2, original_text_3, original_text_4, original_text_5;
    getline(infile, original_text_1);
    getline(infile, original_text_2);
    getline(infile, original_text_3);
    getline(infile, original_text_4);
    getline(infile, original_text_5);

    if ((check_string(original_text_1) && check_string(original_text_2) && check_string(original_text_3) && check_string(original_text_4) && check_string(original_text_5))==false) {
        cout<<"Original String is not appropriate";
        return 0;
    }
    infile.close();

    string plain_text_1;
    string decrypted_text_1;
    plain_text_1 = original_text_1 + Hash(original_text_1);
    
    cipher_text_1 = encrypt(plain_text_1, known_key);

    decrypted_text_1 = decrypt(cipher_text_1, known_key);

    cout<<"First OrinialText   : "<<original_text_1<<endl;
    cout<<"First PlainText     : "<<plain_text_1<<endl;
    cout<<"First CipherText    : "<<cipher_text_1<<endl;
    cout<<"First decryptedText : "<<decrypted_text_1<<endl<<endl;    

    string plain_text_2;
    string decrypted_text_2;
    plain_text_2 = original_text_2 + Hash(original_text_2);

    cipher_text_2 = encrypt(plain_text_2, known_key);

    decrypted_text_2 = decrypt(cipher_text_2, known_key);

    cout<<"Second OrinialText   : "<<original_text_2<<endl;
    cout<<"Second PlainText     : "<<plain_text_2<<endl;
    cout<<"Second CipherText    : "<<cipher_text_2<<endl;
    cout<<"Second decryptedText : "<<decrypted_text_2<<endl<<endl;        

    string plain_text_3;
    string decrypted_text_3;
    plain_text_3 = original_text_3 + Hash(original_text_3);
    
    cipher_text_3 = encrypt(plain_text_3, known_key);

    decrypted_text_3 = decrypt(cipher_text_3, known_key);

    cout<<"Third OrinialText   : "<<original_text_3<<endl;
    cout<<"Third PlainText     : "<<plain_text_3<<endl;
    cout<<"Third CipherText    : "<<cipher_text_3<<endl;
    cout<<"Third decryptedText : "<<decrypted_text_3<<endl<<endl;          

    string plain_text_4;
    string decrypted_text_4;
    plain_text_4 = original_text_4 + Hash(original_text_4);

    cipher_text_4 = encrypt(plain_text_4, known_key);
 
    decrypted_text_4 = decrypt(cipher_text_4, known_key);

    cout<<"Fourth OrinialText   : "<<original_text_4<<endl;
    cout<<"Fourth PlainText     : "<<plain_text_4<<endl;
    cout<<"Fourth CipherText    : "<<cipher_text_4<<endl;
    cout<<"Fourth decryptedText : "<<decrypted_text_4<<endl<<endl;        

    string plain_text_5;
    string decrypted_text_5;
    plain_text_5 = original_text_5 + Hash(original_text_5);

    cipher_text_5 = encrypt(plain_text_5, known_key);

    decrypted_text_5 = decrypt(cipher_text_5, known_key);

    cout<<"Fifth OrinialText   : "<<original_text_5<<endl;
    cout<<"Fifth PlainText     : "<<plain_text_5<<endl;
    cout<<"Fifth CipherText    : "<<cipher_text_5<<endl;
    cout<<"Fifth decryptedText : "<<decrypted_text_5<<endl<<endl;        

    cout<<"LAUNCHING BRUTE FORCE ATTACK..."<<endl<<endl;

    string found_key;
    found_key=bruteforce();
    if (found_key=="ERROR") {
        cout<<"Error: Couldn't find Key";
    }
    else {
        cout<<"Found Key: "<<found_key;
    }
    return 0;
}