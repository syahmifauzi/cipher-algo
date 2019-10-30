// 1715845 MUHAMMAD SYAHMI FATHIMI BIN AHMAD FAUZI
#include <iostream>
#include <string>
using namespace std;

string substitutionCipher(string text) {
  char agreedMapping[] = "FEWHTIJPYODRUVLNGMZABSCKXQ"; // eg, 'A' becomes 'F'
  for (int i = 0; i < text.length(); ++i)
    if (text[i] >= 'A' && text[i] <= 'Z')
      text[i] = agreedMapping[text[i]-'A'];
  return text;
}

int main() {
  string plainTxt, cipherTxt;

  cout << "Plain Text:  ";
  getline(cin, plainTxt);

  cipherTxt = substitutionCipher(plainTxt);
  cout << "Cipher Text: " << cipherTxt << endl;

  return 0;
}
