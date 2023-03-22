#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

string XOR(string a, string b);
string combineAndConvert(string firstHalf, string secondHalf);

unordered_map<char, string> letters = {
    {'a', "00011"},
    {'b', "11001"},
    {'c', "01110"},
    {'d', "01001"},
    {'e', "00001"},
    {'f', "01101"},
    {'g', "11010"},
    {'h', "10100"},
    {'i', "00110"},
    {'j', "01011"},
    {'k', "01111"},
    {'l', "10010"},
    {'m', "11100"},
    {'n', "01100"},
    {'o', "11000"},
    {'p', "10110"},
    {'q', "10111"},
    {'r', "01010"},
    {'s', "00101"},
    {'t', "10000"},
    {'u', "00111"},
    {'v', "11110"},
    {'w', "10011"},
    {'x', "11101"},
    {'y', "10101"},
    {'z', "10001"}
};

int main() {
    string word;
    int n;

    cout << "Введите английское слово: ";
    cin >> word;
    cout << "Введите число раундов: ";
    cin >> n;

    if (n >= word.length() * 5) {
        cout << "Нельзя использовать такое большое число раундов для этого слова! (Не должно быть больше чем СЛОВО * 5)" << endl;
        return 0;
    }

    if (word.length() % 2 != 0 || word.length() == 0) {
        cout << "Нельзя шифровать слова с нечетным кол-вом букв!" << endl;
        return 0;
    }

    string letterInfo = "";
    for (char c : word) {
        letterInfo += letters[tolower(c)];
    }

    string firstHalf = letterInfo.substr(0, letterInfo.length() / 2);
    string secondHalf = letterInfo.substr(letterInfo.length() / 2);

    cout << "Было: " << firstHalf << " | " << secondHalf << endl;

    for (int i = 1; i <= n; i++) {
        string newNumbers = secondHalf + XOR(firstHalf, secondHalf);
        string left = newNumbers.substr(0, newNumbers.length() / 2);
        string right = newNumbers.substr(newNumbers.length() / 2);
        firstHalf = left;
        secondHalf = right;
    }

    cout << "Ответ: " << firstHalf << " | " << secondHalf << endl;
    cout << "Ответ: " << combineAndConvert(firstHalf, secondHalf) << endl;

    return 0;
}

string XOR(string a, string b) {
    string result = "";
    for (int i = 0; i < a.length(); i++) {
        result += a[i] == b[i] ? "0" : "1";
    }
    return result;
}

string combineAndConvert(string firstHalf, string secondHalf) {
    string letterInfo = firstHalf + secondHalf;
    string result = "";
    for (int i = 0; i < letterInfo.length(); i += 5) {
        string letterCode = letterInfo.substr(i, 5);
        for (auto const& pair : letters) {
            if (pair.second == letterCode) {
                result += pair.first;
                break;
            }
        }
    }
    return result;
}
