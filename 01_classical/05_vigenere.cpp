#include <iostream>
#include <string>
using namespace std;

string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

string getVigenereCipher(string plain, string key){
    string res ="";
    for(int i=0,j=-1 ; i<plain.length() ; ++i){
        if(j==key.length()-1) j=-1;
        if(plain[i]==' '){
            res+=' ';
            continue;
        }            
        else ++j;
        // cout<<j<<endl;
        res += letters[((plain[i]-'A') + (key[j]- 'A')) % 26];

    }
    return res;
}

string convertToUpper(string str){
    for(int i=0 ; i<str.length(); ++i){
        if(str[i]==' '){
            continue;
        }
        str[i]= toupper(str[i]);
    }
    return str;
}

int main(){
    string plain,key;
    cout << "Plain Text: ";
    getline(cin,plain);
    cout << "Key: ";
    cin >> key;

    cout << "Cipher Text: "<< getVigenereCipher(convertToUpper(plain),convertToUpper(key))<<endl;
    // cout << letters.length();
    return 0;
}