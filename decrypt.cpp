// Keszitette: Farkas Zoltan es Balog Balint Milan
// DEIK PTI, PROG1 2024

#include <iostream>
#include <fstream>
#include <string>

// Ez a fuggveny a titkositott szoveget a megadott kulcs alapjan
// visszaallitja az eredeti formajaba:
std::string decryptText(const std::string &encryptedText, const std::string &key)
{
  std::string decryptedText = encryptedText;
  for (size_t i = 0; i < encryptedText.length(); ++i)
  {
    decryptedText[i] ^= key[i % key.length()];
  }
  return decryptedText;
}

int main()
{
  // Beolvassuk a titkositott szoveget:
  std::ifstream inFile("encryptedText.txt");
  if (!inFile.is_open())
  {
    std::cerr << "HIBA: Nem sikerult a fajl megnyitasa, kerlek probald ujra!" << std::endl;
    return 1;
  }

  // Beolvassuk a titkositott szoveget
  std::string encryptedText;
  std::getline(inFile, encryptedText);

  // Fajl bezarasa
  inFile.close();

  // Beolvassuk a titkositas feloldasahoz szukseges kulcsot:
  std::ifstream keyFile("key.txt", std::ios::binary);
  if (!keyFile.is_open())
  {
    std::cerr << "HIBA: Nem sikerult a kulcs lekerdezese, kerlek probald ujra!" << std::endl;
    return 1;
  }

  // Eltaroljuk a helyes kulcsot:
  std::string key;
  std::getline(keyFile, key);

  // Bezarjuk a file-t
  keyFile.close();

  // Bekerjuk a usertol a kulcsot
  std::string enteredKey;
  std::cout << "Add meg a kulcsot: ";
  std::getline(std::cin, enteredKey);

  // Megnezzuk, hogy helyes-e a user altal megadott kulcs:
  if (enteredKey == key)
  {
    // Ha igen, akkor visszaallitjuk a szoveget
    std::string decryptedText = decryptText(encryptedText, key);

    std::cout << "Eredeti szoveg: " << decryptedText << std::endl;

    // Az eredeti szoveget kiirjuk a decryptedText.txt fajlba:
    std::ofstream outFile("decryptedText.txt");
    if (outFile.is_open())
    {
      outFile << decryptedText;
      outFile.close();
      std::cout << "Az eredeti szoveg megtalalhato a decryptedText.txt fajlban is!" << std::endl;
    }
    else
    {
      std::cerr << "HIBA: Az eredeti szoveget nem tudtuk a decryptedText.txt fajlba kiiratni." << std::endl;
      return 1;
    }
  }
  else
  {
    std::cerr << "HIBA: A megadott kulcs nem helyes, probald ujra kesobb!" << std::endl;
    return 1;
  }

  return 0;
}
