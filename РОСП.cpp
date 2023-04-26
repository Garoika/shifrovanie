#include <iostream>
#include <bitset>
#include <string>
using namespace std;

string TextToBinary(string word) {
    string binary;
    for (int i = 0; i < word.length(); i++) {
        char c = word[i];
        bitset<8> bits(c);
        binary += bits.to_string();
    }
    return binary;
}

void generateGamma(int a, int b, int c, int d, int* returnArray) {
    int newA, newB, newC, newD, gamma;
    newA = (b + c + d) % 2;
    newB = a;
    newC = b;
    newD = (b + c + d) / 2;
    gamma = c;

    returnArray[0] = newA;
    returnArray[1] = newB;
    returnArray[2] = newC;
    returnArray[3] = newD;
    returnArray[4] = gamma;
}

string xor_strings(string one, string two) {
    string result;
    if (one.length() != two.length()) {
        cout << "Строки не равны!";
        return "";
    }
    for (int i = 0; i < one.length(); i++) {
        if (stoi(to_string(one[i])) == stoi(to_string(two[i]))) result += "0";
        else result += "1";
    }
    return result;
}

string binaryToString(string binary) {
    string result = "";
    int len = binary.length();

    for (int i = 0; i < len; i += 8) {
        string eightBits = binary.substr(i, 8);
        char character = (char)stoi(eightBits, nullptr, 2);
        result += character;
    }

    return result;
}

int main()
{
    int a, b, c, d, gamma, mode;
    while (true) {
        cout << "1. Зашифровка\n2. Расшифровка\n3. Выйти из программы\nВыберите режим: ";
        cin >> mode;
        switch (mode) {
            case 1: {
                string resultGamma = "";
                string text;
                cout << "Введите 4 числа (0 или 1): ";
                cin >> a >> b >> c >> d;

                if (a != 0 && a != 1
                    || b != 0 && b != 1
                    || c != 0 && c != 1
                    || d != 0 && d != 1) {
                    cout << "Неверный ввод!" << endl;
                    return -1;
                }

                cout << "Введите текст для шифрования: ";
                cin.ignore();
                getline(cin, text);
                text = TextToBinary(text);

                for (int i = 0; i < text.length(); i++) {
                    int newNumber[5] = { 0 };
                    generateGamma(a, b, c, d, newNumber);
                    a = newNumber[0];
                    b = newNumber[1];
                    c = newNumber[2];
                    d = newNumber[3];
                    gamma = newNumber[4];
                    resultGamma += to_string(gamma);
                    cout << "\t" << a << "\t\t" << b << "\t\t" << c << "\t\t" << d << "\t\t" << gamma << endl;
                }
                resultGamma = xor_strings(text, resultGamma);
                cout << "Зашифрованная строка: " << resultGamma << endl;
                break;
            }
            case 2: {
                string resultGamma = "";
                string text;
                cout << "Введите 4 числа (0 или 1): ";
                cin >> a >> b >> c >> d;

                if (a != 0 && a != 1
                    || b != 0 && b != 1
                    || c != 0 && c != 1
                    || d != 0 && d != 1) {
                    cout << "Неверный ввод!" << endl;
                    return -1;
                }

                cout << "Введите текст для расшифровки: ";
                cin.ignore();
                getline(cin, text);

                for (int i = 0; i < text.length(); i++) {
                    int newNumber[5] = { 0 };
                    generateGamma(a, b, c, d, newNumber);
                    a = newNumber[0];
                    b = newNumber[1];
                    c = newNumber[2];
                    d = newNumber[3];
                    gamma = newNumber[4];
                    resultGamma += to_string(gamma);
                    cout << "\t" << a << "\t\t" << b << "\t\t" << c << "\t\t" << d << "\t\t" << gamma << endl;
                }

                resultGamma = xor_strings(text, resultGamma);

                cout << "Расшифрованное слово: " << binaryToString(resultGamma) << endl;
                break;
            }
        }
    }

    return 0;
}
