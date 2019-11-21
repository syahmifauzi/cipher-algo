#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#define rep(i, a, n) for (int i = a; i < n; ++i)
#define dbg(x) cout << (#x) << " is " << x << '\n'
using namespace std;

int getPowWithMod(int n, int pow, int mod) {
  int nn = n;
  // printf("%c = %d --> ", n, n);
  while (--pow) n =  (n * nn) % mod;
  // printf("%c = %d\n", n, n);
  return n;
}

int main() {
  printf("========== Rivest-Shamir-Adleman (RSA) Cryptosystem ==========\n\n");

  int d, n, tmp; // public key
  string plaintext = "";
  vector<int> ciphertext;

  printf("Enter d: ");
  scanf("%d", &d);

  printf("Enter n: ");
  scanf("%d", &n);

  printf("Enter ciphertext separated by space (end with -1): \n> ");
  while (scanf("%d", &tmp) == 1 && tmp != -1) ciphertext.push_back(tmp);

  // decryption
  rep(i, 0, ciphertext.size())
    plaintext += char(getPowWithMod(ciphertext[i], d, n));

  // print plaintext
  printf("----> Plaintext is: %s\n\n", plaintext.c_str());

  printf("==============================================================\n");

  return 0;
}
