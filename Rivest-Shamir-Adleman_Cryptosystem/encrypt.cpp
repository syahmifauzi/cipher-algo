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

  int e, n; // public key
  string plaintext;
  vector<int> ciphertext;

  printf("Enter e: ");
  scanf("%d", &e);

  printf("Enter n: ");
  scanf("%d", &n);

  printf("Enter plaintext message in one line: \n> ");
  cin.ignore();
  getline(cin, plaintext);

  // encryption
  rep(i, 0, plaintext.length())
    ciphertext.push_back(getPowWithMod(plaintext[i], e, n));

  // print ciphertext
  printf("----> Ciphertext is: ");
  rep(i, 0, ciphertext.size()) printf("%d ", ciphertext[i]);
  printf("\n\n");

  printf("==============================================================\n");

  return 0;
}
