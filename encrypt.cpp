// Keszitette: Farkas Zoltan es Balog Balint Milan
// DEIK PTI, PROG1 2024

#include <iostream>
#include <fstream>
#include <string>
#include <random>

// Fuggveny, ami general egy random kulcsot, amit a titkositott
// allomany feloldasahoz tudunk majd felhasznalni.
std::string generateRandomKey(int length)
{
  // Valtozok init
  std::string key;
  std::random_device rd;
  std::mt19937 gen(rd());

  // ASCII kiirathato karakterek, hogy a usernek ne kelljen
  // "erdekes" karaktereket hasznalnia kulcskent
  std::uniform_int_distribution<> dis(33, 126);

  // Kulcs generalasa:
  for (int i = 0; i < length; ++i)
  {
    key += static_cast<char>(dis(gen));
  }

  return key;
}

// Fuggveny ami egy egyszeru XOR-os titkositast vegez
// Beker egy titkositando stringet, majd a kulcsot hozza
std::string encryptText(const std::string &text, const std::string &key)
{
  std::string encryptedText = text;
  for (size_t i = 0; i < text.length(); ++i)
  {
    encryptedText[i] ^= key[i % key.length()];
  }
  return encryptedText;
}

int main()
{
  // Bekerjuk a felhasznalotol a titkositando szoveget:
  std::string inputText;
  std::cout << "Titkositando szoveg: ";
  std::getline(std::cin, inputText);

  // Legeneraljuk a random kulcsot
  std::string key = generateRandomKey(inputText.length());

  // Kiiratjuk a kulcsot a key.txt file-ba
  // (
  //   ezt production-ben erdemes lehet majd kicserelni valami
  //   valami adatbazisra, ahol "biztonsagosabb" helyen van a kulcs
  // )
  std::ofstream keyFile("key.txt", std::ios::binary);
  // Megnezzuk, hogy sikerult a fajlt megnyitni
  if (keyFile.is_open())
  {
    // Kiiratjuk, majd bezarjuk a file-t
    keyFile.write(key.c_str(), key.size());
    keyFile.close();
    std::cout << "Kulcs elmentve a kovetkezo file-ba: key.txt" << std::endl;
  }
  else
  {
    std::cerr << "HIBA: Nem sikerult a fajlba valo iras, kerlek probald ujra!" << std::endl;
    return 1;
  }

  // Titkositott szoveg:
  std::string encryptedText = encryptText(inputText, key);

  // A titkositott szoveg az "encryptedText.txt" allomanyba iratjuk:
  std::ofstream outFile("encryptedText.txt");
  // Megnezzuk, hogy sikerult a fajlt megnyitni
  if (outFile.is_open())
  {
    // Kiiratjuk, majd bezarjuk a file-t
    outFile << encryptedText;
    outFile.close();
    std::cout << "A titkositando szoveg titkositva es elmentve a kovetkezo file-ba: encryptedText.txt" << std::endl;
  }
  else
  {
    std::cerr << "HIBA: Nem sikerult a fajlba valo iras, kerlek probald ujra!" << std::endl;
    return 1;
  }

  return 0;
}
