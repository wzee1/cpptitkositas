// Keszitette: Farkas Zoltan es Balog Balint Milan
// DEIK PTI, PROG1 2024
 
#include <iostream>
#include <fstream>
#include <string>
 
std::string encryptText(const std::string &text)
{
  std::string encryptedText = text;
  for (char &c : encryptedText)
  {
    if (isalpha(c))
    {
      c = (c == 'z' || c == 'Z') ? c - 25 : c + 1;
    }
  }
  return encryptedText;
}
 
int main()
{
  std::string inputText;
  std::cout << "Titkositando szoveg: ";
  std::getline(std::cin, inputText);
 
  std::string encryptedText = encryptText(inputText);
 
  std::ofstream outFile("encryptedText.txt");
  if (outFile.is_open())
  {
    outFile << encryptedText;
    outFile.close();
    std::cout << "Szoveg titkositva es elmentve az encryptedText.txt fajlba." << std::endl;
  }
  else
  {
    std::cerr << "HIBA: Nem sikerult megnyitni a fajlt!" << std::endl;
    return 1;
  }
 
  return 0;
}