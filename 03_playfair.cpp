#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#define rep(i, a, n) for (int i = a; i < n; ++i)
#define dbg(x) cout << (#x) << " is " << x << '\n'
using namespace std;

struct CharPosMatrix {
  char ch;
  int row;
  int col;
};

CharPosMatrix getPosFromMatrix(char matrix[5][5], char ch) {
  CharPosMatrix chPos;
  rep(i, 0, 5) rep(j, 0, 5) if (matrix[i][j] == ch) {
    chPos.ch = ch;
    chPos.row = i;
    chPos.col = j;
  }
  return chPos;
}

string getTwoCorrespondingChars(char c1, char c2, char matrix[5][5], int shift) {
  string correspondingChars = "";
  // get the positon of both chars in the 5x5 matrix
  CharPosMatrix posC1 = getPosFromMatrix(matrix, c1);
  CharPosMatrix posC2 = getPosFromMatrix(matrix, c2);
  // if same row
  if (posC1.row == posC2.row) {
    correspondingChars += matrix[posC1.row][(posC1.col + shift) % 5];
    correspondingChars += matrix[posC2.row][(posC2.col + shift) % 5];
  }
  // if same col
  else if (posC1.col == posC2.col) {
    correspondingChars += matrix[(posC1.row + shift) % 5][posC1.col];
    correspondingChars += matrix[(posC2.row + shift) % 5][posC2.col];
  }
  // if diff row and diff col
  else {
    correspondingChars += matrix[posC1.row][posC2.col];
    correspondingChars += matrix[posC2.row][posC1.col];
  }
  // return the 2 encrypted chars
  return correspondingChars;
}

string decrypt(string tCipher, char matrix[5][5]) { // shift = +4 <-- char LEFT/UP
  string tPlain = "";
  int cipherTextLen = tCipher.length();
  for (int i = 0, j = 1; j < cipherTextLen; i += 2, j += 2) {
    if (tCipher[i] == tCipher[j] && tCipher[i] == 'x') tPlain += "xx";
    else tPlain += getTwoCorrespondingChars(tCipher[i], tCipher[j], matrix, +4);
  }
  if (cipherTextLen % 2)
    tPlain += tCipher[cipherTextLen-1];
  return tPlain;
}

string encrypt(string tPlain, char matrix[5][5]) { // shift = +1 <-- char RIGHT/DOWN
  string tCipher = "";
  int plainTextLen = tPlain.length();
  int i = 0, j = 1;
  while (i < plainTextLen) {
    if (j == plainTextLen) {
      if (tPlain[i] == 'x') tCipher += 'x';
      else tCipher += getTwoCorrespondingChars(tPlain[i], 'x', matrix, +1);
      break;
    }
    if (tPlain[i] == tPlain[j]) {
      if (tPlain[i] == 'x') tCipher += "xx";
      else tCipher += getTwoCorrespondingChars(tPlain[i], 'x', matrix, +1);
      i += 1;
      j += 1;
    } else {
      tCipher += getTwoCorrespondingChars(tPlain[i], tPlain[j], matrix, +1);
      i += 2;
      j += 2;
    }
  }
  return tCipher;
}

void generateKeyMatrix(string key, char matrix[5][5]) {
  // i and j are one
  string abc = "abcdefghiklmnopqrstuvwxyz";
  // change all char j to be i
  rep(i, 0, key.length())
    if (key[i] == 'j')
      key[i] = 'i';
  // construct string puzzle of size 25
  string puzzle = "";
  rep(i, 0, key.length())
    if (key[i] >= 'a' && key[i] <= 'z')
      if (puzzle.find(key[i]) == string::npos)
        puzzle += key[i];
  // add the remaining chars to the string
  rep(i, 0, 25)
    if (puzzle.find(abc[i]) == string::npos)
      puzzle += abc[i];
  // convert string puzzle of size 25 to 5x5 char matrix
  int row = 0, col = 0;
  rep(i, 0, 25) {
    matrix[row][col++] = puzzle[i];
    if (i % 5 == 4) {
      row++;
      col = 0;
    }
  }
  // print 5x5 key matrix string (DEBUGGING)
  puts("5x5 Key Matrix:");
  rep(i, 0, 5) {
    printf("\t");
    rep(j, 0, 5)
      printf("%c ", matrix[i][j]);
    puts("");
  }
}

string formatString(string str) {
  string formattedStr = "";
  // convert to lower char string
  rep(i, 0, str.length())
    str[i] = tolower(str[i]);
  // remove non-alphabetical chars
  rep(i, 0, str.length())
    if (str[i] >= 'a' && str[i] <= 'z')
      formattedStr += str[i];
  // return the formatted string
  return formattedStr;
}

int main() {

  string key, tPlain, tCipher;
  char keyMatrix[5][5];
  int opt = 0;

  while (opt != 3) {
    puts("\n   Playfair Cipher");
    puts("=====================");
    puts("1. Encipher");
    puts("2. Decipher");
    puts("3. Exit");
    printf("ENTER option: ");
    scanf("%d", &opt);
    getchar();
    if (opt == 1) {
      puts("----- Encipher -----");
      printf("ENTER Key: ");
      getline(cin, key);
      printf("ENTER Plain Text:  ");
      getline(cin, tPlain);
      key = formatString(key);
      tPlain = formatString(tPlain);
      generateKeyMatrix(key, keyMatrix);
      tCipher = encrypt(tPlain, keyMatrix);
      printf("Formatted Key:  %s\n", key.c_str());
      printf("Formatted Plain Text:  %s\n", tPlain.c_str());
      printf("OUTPUT  Cipher  Text:  %s\n", tCipher.c_str());
    }
    if (opt == 2) {
      puts("----- Decipher -----");
      printf("ENTER Key: ");
      getline(cin, key);
      printf("ENTER Cipher Text:  ");
      getline(cin, tCipher);
      key = formatString(key);
      tCipher = formatString(tCipher);
      generateKeyMatrix(key, keyMatrix);
      tPlain = decrypt(tCipher, keyMatrix);
      printf("Formatted Key:  %s\n", key.c_str());
      printf("Formatted Cipher Text: %s\n", tCipher.c_str());
      printf("OUTPUT  Plain  Text:   %s\n", tPlain.c_str());
    }
  }

  return 0;
}
