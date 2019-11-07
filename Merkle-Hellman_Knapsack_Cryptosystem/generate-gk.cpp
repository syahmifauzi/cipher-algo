#include <iostream>
#include <string>
#include <vector>
#define rep(i, a, n) for (int i = a; i < n; ++i)
#define dbg(x) cout << (#x) << " is " << x << '\n'
using namespace std;

bool validateSIK(vector<int> &sik) {
  int sum;
  rep(i, 1, sik.size()) {
    sum = 0;
    rep(j, 0, i) sum += sik[j];
    if (sum >= sik[i]) return false;
  }
  return true;
}

bool validateN(vector<int> &sik, int n) {
  int sum = 0;
  rep(i, 0, sik.size()) sum += sik[i];
  return n > sum;
}

int getGCD(int n, int m) {
  if (m == 0) return n;
  return getGCD(m, n % m);
}

bool validateM(int n, int m) {
  return 1 == getGCD(n, m);
}

int main() {
  printf("========== Merkle-Hellman Knapsack Cryptosystem ==========\n\n");

  // sik is superincreasing knapsack aka the private key
  // gk is general knapsack aka the public key
  int keySize, tmp, N, M;
  vector<int> sik, gk;
  bool isValid;

  printf("Enter the key size: ");
  scanf("%d", &keySize);

  do {
    printf("Enter SuperIncreasing Knapsack of size %d separated by space: ", keySize);
    rep(i, 0, keySize) {
      scanf("%d", &tmp);
      sik.push_back(tmp);
    }
    isValid = validateSIK(sik);
    printf(isValid ? "--> Valid SIK!\n\n" : "--> Invalid SIK!\n");
  } while (!isValid);

  do {
    printf("Enter a number N such that N is larger than sum of SIK: ");
    scanf("%d", &N);
    isValid = validateN(sik, N);
    printf(isValid ? "--> Valid N!\n\n" : "--> Invalid N!\n");
  } while (!isValid);

  do {
    printf("Enter a number M such that the GCD(N, M) = 1: ");
    scanf("%d", &M);
    isValid = validateM(N, M);
    printf(isValid ? "--> Valid M!\n\n" : "--> Invalid M!\n");
  } while (!isValid);

  rep(i, 0, keySize) gk.push_back(M * sik[i] % N);
  printf("----> General Knapsack Produced: ");
  rep(i, 0, keySize) printf("%d ", gk[i]);
  printf("\n");

  return 0;
}

// Example:
// Input:
//   keySize = 8
//   sik     = 2 3 7 14 30 57 120 251
//   N       = 491
//   M       = 41
// Output:
//   gk      = 82 123 287 83 248 373 10 471
