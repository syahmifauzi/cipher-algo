// 1715845 MUHAMMAD SYAHMI FATHIMI BIN AHMAD FAUZI
#include <iostream>
#include <string>
using namespace std;
char abc[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

string ceasarCipher(string text, int shift) {
  for (int i = 0; i < text.length(); ++i)
    if (text[i] >= 'A' && text[i] <= 'Z')
      text[i] = abc[(text[i]-'A'+shift)%26];
  return text;
}

int main() {
  string plainTxt, cipherTxt;
  int matrixNo;
  while (true){
    cout << "Shift Number: ";
    cin >> matrixNo;
    cin.ignore();
    cout << "Plain Text:  ";
    getline(cin, plainTxt);
    for(int i=0 ; i<plainTxt.length(); ++i){
        if(plainTxt[i]==abc[26]){
            continue;
        }
        plainTxt[i]= toupper(plainTxt[i]);
    }
    cipherTxt = ceasarCipher(plainTxt, matrixNo);
    cout << "Cipher Text: " << cipherTxt << endl;
    cout << endl;
  }
  
 
  return 0;
}
