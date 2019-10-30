// 1715845 MUHAMMAD SYAHMI FATHIMI BIN AHMAD FAUZI
#include <iostream>
#include <string>
using namespace std;

string ceasarCipher(string text, int shift) {
  char abc[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 0; i < text.length(); ++i)
    if (text[i] >= 'A' && text[i] <= 'Z')
      text[i] = abc[(text[i]-'A'+shift)%26];
  return text;
}

int main() {
  string plainTxt, cipherTxt;
  int matrixNo;

  cout << "Matric No.: ";
  cin >> matrixNo;
  cin.ignore();
  cout << "Plain Text:  ";
  getline(cin, plainTxt);

  cipherTxt = ceasarCipher(plainTxt, matrixNo % 10);
  cout << "Cipher Text: " << cipherTxt << endl;

  return 0;
}
