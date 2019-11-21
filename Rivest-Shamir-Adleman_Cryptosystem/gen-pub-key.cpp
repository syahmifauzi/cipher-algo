#include <iostream>
#include <iomanip>
#include <string>
#define rep(i, a, n) for (int i = a; i < n; ++i)
#define dbg(x) cout << (#x) << " is " << x << '\n'
using namespace std;

void printColsFromGeneratedRowInGF(int col[7]) {
  rep(i, 0, 7) cout << setw(6) << col[i];
  printf("\n");
}

int getInverseUsingGaloisFields(int m, int n) {
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

int getGCD(int n, int m) {
  if (m == 0) return n;
  return getGCD(m, n % m);
}

bool isPrime(int n) {
  if (n <= 1) return false;
  if (n <= 3) return true;
  if (n % 2 == 0 || n % 3 == 0) return false;
  for (int i = 5; i * i <= n; i += 2)
    if (n % i == 0)
      return false;
  return true;
}

int main() {
  printf("========== Rivest-Shamir-Adleman (RSA) Cryptosystem ==========\n\n");

  int p, q, n, phi, e, d; // p & q are really large prime numbers
  bool isValid;

  do {
    do {
      printf("Enter p: ");
      scanf("%d", &p);
      isValid = isPrime(p);
      printf(isValid ? "--> Valid p!\n\n" : "--> Invalid p!\n");
    } while (!isValid);

    do {
      printf("Enter q: ");
      scanf("%d", &q);
      isValid = isPrime(q);
      printf(isValid ? "--> Valid q!\n\n" : "--> Invalid q!\n");
    } while (!isValid);

    n = p * q;
    phi = (p-1) * (q-1);

    isValid = n > 127;
    printf("----> n = %d\n----> phi(%d) = %d\n\n", n, n, phi);
    if (!isValid) printf("----> Invalid n! n must be grater than 127 (largest ASCII value)\n\n");
  } while (!isValid);

  do {
    printf("Enter e: ");
    scanf("%d", &e);
    isValid = e > 1 && e < phi && getGCD(e, phi) == 1;
    printf(isValid ? "--> Valid e!\n\n" : "--> Invalid e!\n");
  } while (!isValid);

  d = getInverseUsingGaloisFields(e, phi);
  printf("----> d = %d\n\n", d);

  printf("----> Public Key = {%d, %d}\n", e, n);
  printf("----> Private Key = {%d, %d}\n\n", d, n);

  printf("==============================================================\n");

  return 0;
}
