#include <iostream>
#include <map>
#include <bitset>
#include <string>
using namespace std;

map<string, string> sBoxMap;
map<string, string> inverseSBoxMap;
string sub_key[11][4][4]={""};
string first_encryption;
string ninth_encryption;
string first_decryption;
string ninth_decryption;

string s_box[16][16]={
    {"63", "7C", "77", "7B", "F2", "6B", "6F", "C5", "30", "01", "67", "2B", "FE", "D7", "AB", "76"},
    {"CA", "82", "C9", "7D", "FA", "59", "47", "F0", "AD", "D4", "A2", "AF", "9C", "A4", "72", "C0"},
    {"B7", "FD", "93", "26", "36", "3F", "F7", "CC", "34", "A5", "E5", "F1", "71", "D8", "31", "15"},
    {"04", "C7", "23", "C3", "18", "96", "05", "9A", "07", "12", "80", "E2", "EB", "27", "B2", "75"},
    {"09", "83", "2C", "1A", "1B", "6E", "5A", "A0", "52", "3B", "D6", "B3", "29", "E3", "2F", "84"},
    {"53", "D1", "00", "ED", "20", "FC", "B1", "5B", "6A", "CB", "BE", "39", "4A", "4C", "58", "CF"},
    {"D0", "EF", "AA", "FB", "43", "4D", "33", "85", "45", "F9", "02", "7F", "50", "3C", "9F", "A8"},
    {"51", "A3", "40", "8F", "92", "9D", "38", "F5", "BC", "B6", "DA", "21", "10", "FF", "F3", "D2"},
    {"CD", "0C", "13", "EC", "5F", "97", "44", "17", "C4", "A7", "7E", "3D", "64", "5D", "19", "73"},
    {"60", "81", "4F", "DC", "22", "2A", "90", "88", "46", "EE", "B8", "14", "DE", "5E", "0B", "DB"},
    {"E0", "32", "3A", "0A", "49", "06", "24", "5C", "C2", "D3", "AC", "62", "91", "95", "E4", "79"},
    {"E7", "C8", "37", "6D", "8D", "D5", "4E", "A9", "6C", "56", "F4", "EA", "65", "7A", "AE", "08"},
    {"BA", "78", "25", "2E", "1C", "A6", "B4", "C6", "E8", "DD", "74", "1F", "4B", "BD", "8B", "8A"},
    {"70", "3E", "B5", "66", "48", "03", "F6", "0E", "61", "35", "57", "B9", "86", "C1", "1D", "9E"},
    {"E1", "F8", "98", "11", "69", "D9", "8E", "94", "9B", "1E", "87", "E9", "CE", "55", "28", "DF"},
    {"8C", "A1", "89", "0D", "BF", "E6", "42", "68", "41", "99", "2D", "0F", "B0", "54", "BB", "16"}
};

string inverseSBox[16][16] = {
    {"52", "09", "6A", "D5", "30", "36", "A5", "38", "BF", "40", "A3", "9E", "81", "F3", "D7", "FB"},
    {"7C", "E3", "39", "82", "9B", "2F", "FF", "87", "34", "8E", "43", "44", "C4", "DE", "E9", "CB"},
    {"54", "7B", "94", "32", "A6", "C2", "23", "3D", "EE", "4C", "95", "0B", "42", "FA", "C3", "4E"},
    {"08", "2E", "A1", "66", "28", "D9", "24", "B2", "76", "5B", "A2", "49", "6D", "8B", "D1", "25"},
    {"72", "F8", "F6", "64", "86", "68", "98", "16", "D4", "A4", "5C", "CC", "5D", "65", "B6", "92"},
    {"6C", "70", "48", "50", "FD", "ED", "B9", "DA", "5E", "15", "46", "57", "A7", "8D", "9D", "84"},
    {"90", "D8", "AB", "00", "8C", "BC", "D3", "0A", "F7", "E4", "58", "05", "B8", "B3", "45", "06"},
    {"D0", "2C", "1E", "8F", "CA", "3F", "0F", "02", "C1", "AF", "BD", "03", "01", "13", "8A", "6B"},
    {"3A", "91", "11", "41", "4F", "67", "DC", "EA", "97", "F2", "CF", "CE", "F0", "B4", "E6", "73"},
    {"96", "AC", "74", "22", "E7", "AD", "35", "85", "E2", "F9", "37", "E8", "1C", "75", "DF", "6E"},
    {"47", "F1", "1A", "71", "1D", "29", "C5", "89", "6F", "B7", "62", "0E", "AA", "18", "BE", "1B"},
    {"FC", "56", "3E", "4B", "C6", "D2", "79", "20", "9A", "DB", "C0", "FE", "78", "CD", "5A", "F4"},
    {"1F", "DD", "A8", "33", "88", "07", "C7", "31", "B1", "12", "10", "59", "27", "80", "EC", "5F"},
    {"60", "51", "7F", "A9", "19", "B5", "4A", "0D", "2D", "E5", "7A", "9F", "93", "C9", "9C", "EF"},
    {"A0", "E0", "3B", "4D", "AE", "2A", "F5", "B0", "C8", "EB", "BB", "3C", "83", "53", "99", "61"},
    {"17", "2B", "04", "7E", "BA", "77", "D6", "26", "E1", "69", "14", "63", "55", "21", "0C", "7D"}
    }; 

void construct_s_box () {
    string key;
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            key = "";
            if (i<10) {
                key+=('0' + i);
            }
            else {
                key+=('A' + i - 10);
            }
            if (j<10) {
                key+=('0' + j);
            }
            else {
                key+=('A' + j - 10);
            }
            sBoxMap[key] = s_box[i][j];
        }
    }    
}

void construct_inverse_s_box () {
    string key;
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            key = "";

            if (i<10) {
                key+=('0' + i);
            }
            else {
                key+=('A' + i - 10);
            }
            if (j<10) {
                key+=('0' + j);
            }
            else {
                key+=('A' + j - 10);
            }
            inverseSBoxMap[key] = (inverseSBox[i][j]);
        }
    } 
}

void copy_data(string matrix1[4][4], string (&matrix2)[4][4]) {
    for (int i=0;i<4;i++) {
        for (int j=0;j<4;j++) {
            matrix2[i][j]=matrix1[i][j];
        }
    }
}

string hex_string_to_binary(string hex) {
    string binary_string="";
    for (char hex_digit : hex) {
        switch(hex_digit)
        {
            case '0':
                binary_string+="0000";
                break;
            case '1':
                binary_string+="0001";
                break;
            case '2':
                binary_string+="0010";
                break;
            case '3':
                binary_string+="0011";
                break;
            case '4':
                binary_string+="0100";
                break;
            case '5':
                binary_string+="0101";
                break;
            case '6':
                binary_string+="0110";
                break;
            case '7':
                binary_string+="0111";
                break;
            case '8':
                binary_string+="1000";
                break;
            case '9':
                binary_string+="1001";
                break;
            case 'A':
                binary_string+="1010";
                break;
            case 'B':
                binary_string+="1011";
                break;
            case 'C':
                binary_string+="1100";
                break;
            case 'D':
                binary_string+="1101";
                break;
            case 'E':
                binary_string+="1110";
                break;
            case 'F':
                binary_string+="1111";
                break;
        }        
    }
    return binary_string;
}

string binary_to_hex(string binary) {
    string result="";
    string temp1= binary.substr(0,4);
    string temp2= binary.substr(4,4);
    switch (stoi(temp1, nullptr, 2)) {
        case 0: result+="0";
        break;

        case 1: result+="1";
        break;

        case 2: result+="2";
        break;
        
        case 3: result+="3";
        break;
        
        case 4: result+="4";
        break;
        
        case 5: result+="5";
        break;
        
        case 6: result+="6";
        break;
        
        case 7: result+="7";
        break;
        
        case 8: result+="8";
        break;
        
        case 9: result+="9";
        break;
        
        case 10: result+="A";
        break;
        
        case 11: result+="B";
        break;
        
        case 12: result+="C";
        break;
        
        case 13: result+="D";
        break;
        
        case 14: result+="E";
        break;
        
        case 15: result+="F";
        break;
    }

    switch (stoi(temp2, nullptr, 2)) {
        case 0: result+="0";
        break;

        case 1: result+="1";
        break;

        case 2: result+="2";
        break;
        
        case 3: result+="3";
        break;
        
        case 4: result+="4";
        break;
        
        case 5: result+="5";
        break;
        
        case 6: result+="6";
        break;
        
        case 7: result+="7";
        break;
        
        case 8: result+="8";
        break;
        
        case 9: result+="9";
        break;
        
        case 10: result+="A";
        break;
        
        case 11: result+="B";
        break;
        
        case 12: result+="C";
        break;
        
        case 13: result+="D";
        break;
        
        case 14: result+="E";
        break;
        
        case 15: result+="F";
        break;
    }    

    return result;
}

string xor_operation(string s1, string s2, string s3, string s4) {
    int temp1[8], temp2[8], temp3[8], temp4[8];
    for (int i=0;i<8;i++) {
        temp1[i]=s1[i]-'0';
        temp2[i]=s2[i]-'0';
        temp3[i]=s3[i]-'0';
        temp4[i]=s4[i]-'0';
    }

    string result="";
    
    for (int i=0;i<8;i++) {
        result+=to_string(temp1[i]^temp2[i]^temp3[i]^temp4[i]);
    }
    result=binary_to_hex(result);
    return result;
}

string GF_multiplication(string string_1, string string_2) {
    string temp1=hex_string_to_binary(string_1);
    string temp2=hex_string_to_binary(string_2);
    int a[8],b[8];
    for (int i=0;i<8;i++){
        a[i]=temp1[i]-'0';
        b[i]=temp2[i]-'0';
    }
    int c[15]={0};
    int m[] = {1, 0, 0, 0, 1, 1, 0, 0, 1};
    for (int i=0;i<8;i++) {
        for (int j=0;j<8;j++) {
            if (a[7-i]&&b[7-j]) {
                c[14-i-j]+=1; 
            }
        }
    }
    for (int i=0;i<15;i++) {
        c[i]=c[i]%2;
    }
    
    if (c[6]) {
        c[6]=0;
        c[14]^=1;
        c[13]^=1;
        c[11]^=1;
        c[10]^=1;
    }  
    if (c[5]) {
        c[5]=0;
        c[13]^=1;
        c[12]^=1;
        c[10]^=1;
        c[9]^=1;
    }  
    if (c[4]) {
        c[4]=0;
        c[12]^=1;
        c[11]^=1;
        c[9]^=1;
        c[8]^=1;
    }
    if (c[3]) {
        c[3]=0;
        c[11]^=1;
        c[10]^=1;
        c[8]^=1;
        c[7]^=1;
    }
    if (c[2]) {
        c[2]=0;
        c[14]^=1;
        c[13]^=1;
        c[11]^=1;
        c[9]^=1;
        c[7]^=1;
    }
    if (c[1]) {
        c[1]=0;
        c[14]^=1;
        c[12]^=1;
        c[11]^=1;
        c[8]^=1;
    }
    if (c[0]) {
        c[0]=0;
        c[13]^=1;
        c[11]^=1;
        c[10]^=1;
        c[7]^=1;
    }

    string result="";
    for (int i=7;i<15;i++) {
        result+= to_string(c[i]);
    }
    return result;
}

void substitue_bytes (string (&matrix)[4][4]) {
    for (int i=0;i<4;i++) {
        for (int j=0;j<4;j++) {
            matrix[i][j]=sBoxMap[matrix[i][j]];
        }
    }
}

void inverse_sub_bytes(string (&matrix)[4][4]) {
    for (int i=0;i<4;i++) {
        for (int j=0;j<4;j++) {
            matrix[i][j]=inverseSBoxMap[matrix[i][j]];
        }
    }
}

void shift_rows (string (&matrix)[4][4]) {
    swap(matrix[1][0], matrix[1][1]);
    swap(matrix[1][1], matrix[1][2]);
    swap(matrix[1][2], matrix[1][3]);

    swap(matrix[2][0], matrix[2][2]);
    swap(matrix[2][1], matrix[2][3]);

    swap(matrix[3][2], matrix[3][3]);
    swap(matrix[3][1], matrix[3][2]);
    swap(matrix[3][0], matrix[3][1]);
}

void inverse_shift_rows (string (&matrix)[4][4]) {
    swap(matrix[1][2], matrix[1][3]);
    swap(matrix[1][1], matrix[1][2]);
    swap(matrix[1][0], matrix[1][1]);

    swap(matrix[2][0], matrix[2][2]);
    swap(matrix[2][1], matrix[2][3]);

    swap(matrix[3][0], matrix[3][1]);
    swap(matrix[3][1], matrix[3][2]);
    swap(matrix[3][2], matrix[3][3]);
}

void Mix_Column(string matrix[4][4], string (&matrix2)[4][4]) {
    for (int i=0;i<4;i++) {
        matrix2[0][i]=xor_operation(GF_multiplication("02",matrix[0][i]), GF_multiplication("03",matrix[1][i]), hex_string_to_binary(matrix[2][i]), hex_string_to_binary(matrix[3][i]));
        matrix2[1][i]=xor_operation(hex_string_to_binary(matrix[0][i]), GF_multiplication("02", matrix[1][i]), GF_multiplication("03", matrix[2][i]), hex_string_to_binary(matrix[3][i]));
        matrix2[2][i]=xor_operation(hex_string_to_binary(matrix[0][i]), hex_string_to_binary(matrix[1][i]), GF_multiplication("02", matrix[2][i]), GF_multiplication("03", matrix[3][i]));
        matrix2[3][i]=xor_operation(GF_multiplication("03", matrix[0][i]), hex_string_to_binary(matrix[1][i]), hex_string_to_binary(matrix[2][i]), GF_multiplication("02", matrix[3][i]));
    }
    
}

void Inverse_Mix_Column(string matrix[4][4], string (&matrix2)[4][4]) {
    for (int i=0;i<4;i++) {
        matrix2[0][i]=xor_operation(GF_multiplication("0E",matrix[0][i]), GF_multiplication("0B",matrix[1][i]), GF_multiplication("0D",matrix[2][i]), GF_multiplication("09",matrix[3][i]));
        matrix2[1][i]=xor_operation(GF_multiplication("09",matrix[0][i]), GF_multiplication("0E",matrix[1][i]), GF_multiplication("0B",matrix[2][i]), GF_multiplication("0D",matrix[3][i]));
        matrix2[2][i]=xor_operation(GF_multiplication("0D",matrix[0][i]), GF_multiplication("09",matrix[1][i]), GF_multiplication("0E",matrix[2][i]), GF_multiplication("0B",matrix[3][i]));
        matrix2[3][i]=xor_operation(GF_multiplication("0B",matrix[0][i]), GF_multiplication("0D",matrix[1][i]), GF_multiplication("09",matrix[2][i]), GF_multiplication("0E",matrix[3][i]));
    }
}

void add_round_key(string (&state)[4][4], string subkey[4][4]) {
    for (int i=0;i<4;i++) {
        for (int j=0;j<4;j++) {
            state[i][j]=xor_operation(hex_string_to_binary(state[i][j]),hex_string_to_binary(subkey[i][j]),"00000000","00000000");
        }
    }
}

void g_function(string (&word)[4], int round) {

    swap(word[0], word[1]);
    swap(word[1], word[2]);
    swap(word[2], word[3]);

    for (int i=0;i<4;i++) {
        word[i]=sBoxMap[word[i]];
    }
    string RC="";
    switch(round) {
        case 1: RC="00000001";
        break;

        case 2: RC="00000010";
        break;

        case 3: RC="00000100";
        break;

        case 4: RC="00001000";
        break;

        case 5: RC="00010000";
        break;

        case 6: RC="00100000";
        break;

        case 7: RC="01000000";
        break;

        case 8: RC="10000000";
        break;

        case 9: RC="00011011";
        break;

        case 10: RC="00110110";
        break;
    }
    word[0]=xor_operation(hex_string_to_binary(word[0]), RC, "00000000", "00000000"); 
}

void generate_sub_key(string (&key)[4][4], int round) {
    string word_3[4];
    for (int i=0;i<4;i++) {
        word_3[i]=key[3][i];
    }
    g_function(word_3, round);
    for (int i=0;i<4;i++) {
        key[0][i]=xor_operation(hex_string_to_binary(key[0][i]), hex_string_to_binary(word_3[i]), "00000000", "00000000");
    }

    for (int i=1;i<4;i++) {
        for (int j=0;j<4;j++) {
            key[i][j]=xor_operation(hex_string_to_binary(key[i-1][j]), hex_string_to_binary(key[i][j]), "00000000", "00000000");
        }
    }

}

string matrix_to_string(string matrix[4][4]) {
    string result="";
    for (int i=0;i<4;i++) {
        for (int j=0;j<4;j++) {
            result+=matrix[j][i];
        }
    }
    return result;
}

void string_to_matrix(string text, string (&matrix)[4][4]) {
    int k=0;
    for (int i=0;i<4;i++) {
        for (int j=0;j<4;j++) {
            matrix[j][i]=text.substr(k*2,2); 
            k++;
        }
    }
}

string AES_Encryption(string plaintext) {
    string ciphertext[4][4]={""};
    string temp[4][4]={""};
    string_to_matrix(plaintext, ciphertext);

    add_round_key(ciphertext, sub_key[0]);

    substitue_bytes(ciphertext);
    shift_rows(ciphertext);
    copy_data(ciphertext, temp);
    Mix_Column(temp, ciphertext);
    add_round_key(ciphertext, sub_key[1]);

    first_encryption=matrix_to_string(ciphertext);

    for (int i=2;i<10;i++) {
        substitue_bytes(ciphertext);
        shift_rows(ciphertext);
        copy_data(ciphertext, temp);
        Mix_Column(temp, ciphertext);
        add_round_key(ciphertext, sub_key[i]);
    }

    ninth_encryption=matrix_to_string(ciphertext);

    substitue_bytes(ciphertext);
    shift_rows(ciphertext);
    add_round_key(ciphertext, sub_key[10]);    

    return matrix_to_string(ciphertext);
}

string AES_Decryption(string ciphertext) {
    string plaintext[4][4]={""};
    string temp[4][4]={""};
    string_to_matrix(ciphertext, plaintext);
    string_to_matrix(ciphertext, temp);
    
    add_round_key(plaintext, sub_key[10]);
    inverse_shift_rows(plaintext);
    inverse_sub_bytes(plaintext);

    first_decryption=matrix_to_string(plaintext);

    for (int i=9; i>1;i--) {
        add_round_key(plaintext, sub_key[i]);
        copy_data(plaintext, temp);
        Inverse_Mix_Column(temp, plaintext);
        inverse_shift_rows(plaintext);
        inverse_sub_bytes(plaintext);
    }

    ninth_decryption=matrix_to_string(plaintext);

    add_round_key(plaintext, sub_key[1]);
    copy_data(plaintext, temp);
    Inverse_Mix_Column(temp, plaintext);
    inverse_shift_rows(plaintext);
    inverse_sub_bytes(plaintext);

    add_round_key(plaintext, sub_key[0]);

    return matrix_to_string(plaintext);
}

string generate_plaintext(string original_text) {
    string result="";
    for (char c : original_text) {
        result+=binary_to_hex(bitset<8>(int(c)).to_string());
    }
    return result;
}

string generate_originaltext(string plaintext) {
    string result="";
    for (int i=0;i<16;i++) {
        result+=static_cast<char>(stoi(hex_string_to_binary(plaintext.substr(i*2,2)), nullptr, 2));
    }
    return result;
}

int main(){
    construct_s_box();
    construct_inverse_s_box();
    string key[4][4]={"54","68","61","74","73","20","6D","79","20","4B","75","6E","67","20", "46", "75"};

    for (int i=0;i<4;i++) {
        for (int j=0;j<4;j++) {
            sub_key[0][i][j]=key[i][j];
        }
    }

    for (int i=1;i<11;i++) {
        generate_sub_key(key, i);
        for (int j=0;j<4;j++) {
            for (int k=0;k<4;k++) {
                sub_key[i][j][k]=key[j][k];
            }
        }
    }
    cout<<"Key(128 bit) in hexadecimal: ";
    for (int i=0;i<4;i++) {
        for (int j=0;j<4;j++) {
            cout<<sub_key[0][i][j];
        }
    }
    cout<<endl<<endl;

    cout<<"First Pair:\n";
    
    string original_text_1="Whatsapp*Youtube";
    string plaintext_1=generate_plaintext(original_text_1); 
    string ciphertext=AES_Encryption(plaintext_1);
    string decrypted_text=AES_Decryption(ciphertext);

    cout<<plaintext_1<<", "<<ciphertext<<endl<<endl;

    cout<<"Origninal text(in characters): "<<original_text_1<<endl;
    cout<<"Plaintext(in hexadeimals): "<<plaintext_1<<endl;
    cout<<"Ciphertext(in hexadecimals): "<<ciphertext<<endl;
    cout<<"Cihertext(in characters): "<<generate_originaltext(ciphertext)<<endl;
    cout<<"Decypted Text(in characters): "<<generate_originaltext(decrypted_text)<<endl;
    cout<<"Decrypted Text(in hexadecimals): "<<decrypted_text<<endl;
    cout<<"First Encryption(in hexadecimals): "<<first_encryption<<endl;
    cout<<"Ninth Decryption(in hexadecimals): "<<ninth_decryption<<endl;
    cout<<"Ninth Encryption(in hexadecimals): "<<ninth_encryption<<endl;
    cout<<"First Decryption(in hexadecimals): "<<first_decryption<<endl;

    cout<<"\nSecond Pair:\n";

    string original_text_2="mymarksinNSC100x"; 
    string plaintext_2=generate_plaintext(original_text_2);
    ciphertext=AES_Encryption(plaintext_2);
    decrypted_text=AES_Decryption(ciphertext);

    cout<<plaintext_2<<", "<<ciphertext<<endl<<endl;

    cout<<"Origninal text(in characters): "<<original_text_2<<endl;
    cout<<"Plaintext(in hexadecimals): "<<plaintext_2<<endl;
    cout<<"Ciphertext(in hexadecimals): "<<ciphertext<<endl;
    cout<<"Cihertext(in characters): "<<generate_originaltext(ciphertext)<<endl;
    cout<<"Decrypted Text(in hexadecimals): "<<decrypted_text<<endl;
    cout<<"Decypted Text(in characters): "<<generate_originaltext(decrypted_text)<<endl;
    cout<<"First Encryption(in hexadecimals): "<<first_encryption<<endl;
    cout<<"Ninth Decryption(in hexadecimals): "<<ninth_decryption<<endl;
    cout<<"Ninth Encryption(in hexadecimals): "<<ninth_encryption<<endl;
    cout<<"First Decryption(in hexadecimals): "<<first_decryption<<endl; 

    cout<<"\nThrid Pair:\n";

    string original_text_3="ekkhokado@divine"; 
    string plaintext_3=generate_plaintext(original_text_3);
    ciphertext=AES_Encryption(plaintext_3);
    decrypted_text=AES_Decryption(ciphertext);

    cout<<plaintext_3<<", "<<ciphertext<<endl<<endl;

    cout<<"Origninal text(in characters): "<<original_text_3<<endl;
    cout<<"Plaintext(in hexadecimals): "<<plaintext_3<<endl;
    cout<<"Ciphertext(in hexadecimals): "<<ciphertext<<endl;
    cout<<"Cihertext(in characters): "<<generate_originaltext(ciphertext)<<endl;
    cout<<"Decrypted Text(in hexadecimals): "<<decrypted_text<<endl;
    cout<<"Decypted Text(in characters): "<<generate_originaltext(decrypted_text)<<endl;
    cout<<"First Encryption(in hexadecimals): "<<first_encryption<<endl;
    cout<<"Ninth Decryption(in hexadecimals): "<<ninth_decryption<<endl;
    cout<<"Ninth Encryption(in hexadecimals): "<<ninth_encryption<<endl;
    cout<<"First Decryption(in hexadecimals): "<<first_decryption<<endl;

    cout<<"\nFourth Pair:\n";

    string original_text_4="1BharathAndVansh"; 
    string plaintext_4=generate_plaintext(original_text_4);
    ciphertext=AES_Encryption(plaintext_4);
    decrypted_text=AES_Decryption(ciphertext);

    cout<<plaintext_4<<", "<<ciphertext<<endl<<endl;

    cout<<"Origninal text(in characters): "<<original_text_4<<endl;
    cout<<"Plaintext(in hexadecimals): "<<plaintext_4<<endl;
    cout<<"Ciphertext(in hexadecimals): "<<ciphertext<<endl;
    cout<<"Cihertext(in characters): "<<generate_originaltext(ciphertext)<<endl;
    cout<<"Decrypted Text(in hexadecimals): "<<decrypted_text<<endl;
    cout<<"Decypted Text(in characters): "<<generate_originaltext(decrypted_text)<<endl;
    cout<<"First Encryption(in hexadecimals): "<<first_encryption<<endl;
    cout<<"Ninth Decryption(in hexadecimals): "<<ninth_decryption<<endl;
    cout<<"Ninth Encryption(in hexadecimals): "<<ninth_encryption<<endl;
    cout<<"First Decryption(in hexadecimals): "<<first_decryption<<endl;

    return 0;
}