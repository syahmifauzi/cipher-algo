#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#define rep(i, a, n) for (int i = a; i < n; ++i)
#define dbg(x) cout << (#x) << " is " << x << '\n'
using namespace std;

void printColsFromGeneratedRowInGF(int col[7]) {
  rep(i, 0, 7) cout << setw(6) << col[i];
  printf("\n");
}

int getInverseMUsingGaloisFields(int m, int n) {
  // Use two rows only for GFTable to save memory
  int GFTable[2][7] = {
    // Q,   A1,  A2,  A3,  B1,  B2,  B3
    {  0,   1,   0,   0,   0,   1,   0 },
    {  0,   0,   1,   0,   0,   0,   0 }
  };
  GFTable[0][3] = n;
  GFTable[0][6] = m;
  printf("Galois Fields Table\n====================\n     Q    A1    A2    A3    B1    B2    B3\n");
  printColsFromGeneratedRowInGF(GFTable[0]);
  while (GFTable[1][6] != 1) {
    // Calculation for second row and after
    GFTable[1][0] = GFTable[0][3] / GFTable[0][6];
    GFTable[1][1] = GFTable[0][4];
    GFTable[1][2] = GFTable[0][5];
    GFTable[1][3] = GFTable[0][6];
    GFTable[1][4] = GFTable[0][1] - GFTable[1][0] * GFTable[1][1];
    GFTable[1][5] = GFTable[0][2] - GFTable[1][0] * GFTable[1][2];
    GFTable[1][6] = GFTable[0][3] - GFTable[1][0] * GFTable[1][3];
    // Print the generated table for debugging purpose
    printColsFromGeneratedRowInGF(GFTable[1]);
    // Copy 2nd row to becomes 1st row and keep on searching until GFTable[1][6] == 1
    if (GFTable[1][6] != 1)
      rep(i, 0, 7)
        GFTable[0][i] = GFTable[1][i];
  }
  // Return the inverse of m
  if (GFTable[1][5] < 0) return n + GFTable[1][5];
  // TODO: What if GFTable[1][5] is zero? no inverse?
  return GFTable[1][5];
}

int main() {

  printf("========== Merkle-Hellman Knapsack Cryptosystem ==========\n\n");

  int keySize, tmp, N, M;
  string plainText = "", eachPlainText;
  vector<int> sik, cipherText;
  // vector<string> sumOnesStrList;

  printf("Enter the key size: ");
  scanf("%d", &keySize);

  printf("Enter SuperIncreasing Knapsack of size %d separated by space: ", keySize);
  rep(i, 0, keySize) {
    scanf("%d", &tmp);
    sik.push_back(tmp);
  }

  printf("Enter the corresponding N: ");
  scanf("%d", &N);

  printf("Enter the corresponding M: ");
  scanf("%d", &M);

  // Get the inverse M and then mod it with N
  M = getInverseMUsingGaloisFields(M, N) % N;
  printf("----> Inverse M: %d\n\n", M);

  printf("Enter Ciphertext separated by space (end with -1): ");
  while (scanf("%d", &tmp) == 1 && tmp != -1) cipherText.push_back(tmp);

  // Decryption begin
  // Convert each cipherText value using inverse M
  // Formula: CipherText * M_inverse mod N
  rep(i, 0, cipherText.size()) cipherText[i] = cipherText[i] * M % N;

  rep(i, 0, cipherText.size()) { // for each cipherText value
    printf("----> cipherText[%d]: %d = ", i + 1, cipherText[i]);
    eachPlainText = ""; // always initialize each string
    for (int j = keySize - 1; j >= 0; --j) { // decrypt it based on SIK
      if (cipherText[i] >= sik[j]) {
        eachPlainText += "1";
        cipherText[i] -= sik[j];
      } else {
        eachPlainText += "0";
      }
    }
    // Don't forget to reverse eachPlainText string
    reverse(eachPlainText.begin(), eachPlainText.end());
    printf("%s\n", eachPlainText.c_str());
    // Then add it to the final plainText string
    plainText += eachPlainText;
  }

  // Tadaaa!!
  printf("\n----> Plaintext Produced: %s\n", plainText.c_str());

  // Remove leading zeros
  plainText.erase(0, min(plainText.find('1'), plainText.size()-1));

  // Tadaa!!
  printf("----> Original Plaintext: %s\n\n", plainText.c_str());

  return 0;
}

// Convert ASCII to Binary: https://www.rapidtables.com/convert/number/ascii-to-binary.html
// Convert Binary to ASCII: https://www.rapidtables.com/convert/number/binary-to-ascii.html
// Example:
// Input:
//   keySize     = 8
//   sik         = 2 3 7 14 30 57 120 251
//   N           = 491
//   M           = 41
//   cipherText  = 604 503 1212 493 866 1512 1264 503 881 493 658 1212 287 1129 974 287 594 1347 1254 974 1512 1502 1254 758 -1
// Output:
//   plainText   = 001000010110010101101101011011110111001101100101011101110100000100100000011100110110100100100000011110010110100001110000011000010111001001100111011011110111010001110000011110010111001001000011
