// Keszitette: Farkas Zoltan es Balog Balint Milan
// DEIK PTI, PROG1 2024

#include <iostream>
#include <fstream>
#include <string>

std::string decryptText(const std::string &encryptedText)
{
  std::string decryptedText = encryptedText;
  for (char &c : decryptedText)
  {
    if (isalpha(c))
    {
      c = (c == 'a' || c == 'A') ? c + 25 : c - 1;
    }
  }
  return decryptedText;
}

int main()
{
  std::ifstream inFile("encryptedText.txt");
  if (!inFile.is_open())
  {
    std::cerr << "HIBA: Nem sikerult megnyitni a fajlt!" << std::endl;
    return 1;
  }

  std::string encryptedText;
  std::getline(inFile, encryptedText);

  inFile.close();

  std::string decryptedText = decryptText(encryptedText);

  std::cout << "Eredeti szoveg: " << decryptedText << std::endl;

  std::ofstream outFile("decryptedText.txt");
  if (outFile.is_open())
  {
    outFile << decryptedText;
    outFile.close();
    std::cout << "Eredeti szoveg elmentve a decryptedText.txt fajlba!" << std::endl;
  }
  else
  {
    std::cerr << "HIBA: Nem sikerult megnyitni a fajlt!" << std::endl;
    return 1;
  }

  return 0;
}
