#include <locale>
#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <windows.h>

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main() {
    system("chcp 65001");
    std::locale::global(std::locale(""));
    std::string fileName;
    std::cout << "Введіть ім’я файлу:";
    setColor(13);
    std::cin >> fileName;
    setColor(7);

    std::ifstream file(fileName, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Помилка відкриття файлу. Перевірте правильність імені файлу." << std::endl;
        return 1;
    }
    else {
        std::cout << "Перевірка: ";
        setColor(13);
        std::cout << "OK" << std::endl;
        setColor(7);
    }

    int n;
    std::cout << "Введіть кількість байтів (3-30): ";
    setColor(13);
    std::cin >> n;
    setColor(7);
    if (n < 3 || n > 30) {
        n = (n > 36) ? 32 : 16;
        std::cout << "Кількість байтів коректовано до " << n << std::endl;
    }

    std::vector<unsigned char> bytes;
    bytes.reserve(n);

    unsigned char byte;
    while (bytes.size() < n && file >> byte) {
        bytes.push_back(byte);
    }

    setColor(9);
    std::cout << "Послідовність байт (початкова): ";
    setColor(7);
    for (unsigned char byte : bytes) {
        std::cout << static_cast<int>(byte) << " ";
    }
    std::cout << std::endl;

    setColor(9);
    std::cout << "Бінарна послідовність (початкова):" << std::endl;
    setColor(7);
    for (unsigned char byte : bytes) {
        std::cout << std::bitset<8>(byte) << " ";
    }
    std::cout << std::endl;

    setColor(9);
    std::cout << "Зсув вліво на 3 біти:" << std::endl;
    setColor(7);
    for (unsigned char& byte : bytes) {
        byte = byte << 3;
        std::cout << std::bitset<8>(byte) << " ";
    }
    std::cout << std::endl;

    std::vector<unsigned char> compressedBytes;
    int countZeroBytes = 0;
    for (unsigned char byte : bytes) {
        if (byte != 0) {
            compressedBytes.push_back(byte);
        }
        else {
            countZeroBytes++;
        }
    }

    setColor(9);
    std::cout << "Стиснення:" << std::endl;
    setColor(7);
    for (unsigned char byte : compressedBytes) {
        std::cout << std::bitset<8>(byte) << " ";
    }
    std::cout << std::endl;

    std::cout << "Кількість байт, які починаються з нуля: ";
    setColor(9);
    std::cout << countZeroBytes << std::endl;
    setColor(7);

    return 0;
}
