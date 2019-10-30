#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#define rep(i, a, n) for (int i = a; i < n; ++i)
#define dbg(x) cout << (#x) << " is " << x << '\n'
using namespace std;

string encrypt(string key, string tPlain) {
  string abc = "abcdefghijklmnopqrstuvwxyz";
  int keyLen = key.length();
  int tPlainLen = tPlain.length();
  string tCipher = "";
  // key
  // if (keyLen < tPlainLen)
  //   rep(i, 0, tPlainLen)
  //     key +=
  for (int i = 0; i < tPlainLen; ++i) {
    tCipher += abc[(tPlain[i] + 26 - key[i % keyLen]) % 26];
  }
}

int main() {
  string tPlain, tCipher = "", key, abc;
  int keyLen, tPlainLen;
  getline(cin, key);
  getline(cin, tPlain);
  cout << tCipher << endl;
}
