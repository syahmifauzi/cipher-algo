#include <iostream>
#include <string>
#include <vector>
#define rep(i, a, n) for (int i = a; i < n; ++i)
#define dbg(x) cout << (#x) << " is " << x << '\n'
using namespace std;

int main() {

  printf("========== Merkle-Hellman Knapsack Cryptosystem ==========\n\n");

  int keySize, tmp, sumOnes;
  string plainText, cipherText = "", sumOnesStr;
  vector<int> gk, sumOnesList;
  vector<string> sumOnesStrList;

  printf("Enter the key size: ");
  scanf("%d", &keySize);

  printf("Enter General Knapsack of size %d separated by space: ", keySize);
  rep(i, 0, keySize) {
    scanf("%d", &tmp);
    gk.push_back(tmp);
  }

  printf("Enter binary string of Plaintext without space: ");
  cin >> plainText;

  // Pad the string with zeros
  if (plainText.length() % keySize != 0)
    plainText += string(plainText.length() % keySize, '0');

  // Encryption begin
  rep(i, 0, plainText.length() / keySize) {
    sumOnes = 0; // IMPORTANT
    sumOnesStr = "";
    rep(j, 0, keySize) if (plainText[i*keySize+j] == '1') {
      sumOnes += gk[j]; // IMPORTANT
      sumOnesStr += to_string(gk[j]);
      sumOnesStr += " + ";
    }
    sumOnesStr = sumOnesStr.substr(0, sumOnesStr.length()-3); // remove last " + "
    sumOnesList.push_back(sumOnes); // IMPORTANT
    sumOnesStrList.push_back(sumOnesStr);
  }

  printf("\n--> Encrypted values using General Knapsack\n");
  rep(i, 0, plainText.length() / keySize) {
    printf("----> %d = %s\n", sumOnesList[i], sumOnesStrList[i].c_str());
    cipherText += to_string(sumOnesList[i]);
    cipherText += " ";
  }
  printf("\n----> Ciphertext Produced: %s\n\n", cipherText.c_str());

  return 0;
}

// Convert ASCII to Binary: https://www.rapidtables.com/convert/number/ascii-to-binary.html
// Convert Binary to ASCII: https://www.rapidtables.com/convert/number/binary-to-ascii.html
// Example:
// Input:
//   keySize    = 8
//   gk         = 82 123 287 83 248 373 10 471
//   plainText  = 010000110111001001111001011100000111010001101111011001110111001001100001011100000110100001111001001000000110100101110011001000000100000101110111011001010111001101101111011011010110010100100001
// Output:
//   cipherText = 604 503 1212 493 866 1512 1264 503 881 493 658 1212 287 1129 974 287 594 1347 1254 974 1512 1502 1254 758
