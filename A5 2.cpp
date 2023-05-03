#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <bitset>

using namespace std;

string binaryToString(string binary) {
	string result = "";
	int len = binary.length();
	for (int i = 0; i < len; i += 8) {
		string eightBits = binary.substr(i, 8);
		char character = (char)bitset<8>(eightBits).to_ulong();
		result += character;
	}
	return result;
}

string xor_strings(string one, string two) {
	string result;
	if (one.length() != two.length()) {
		cout << "Строки не равны!";
		return "";
	}
	for (int i = 0; i < one.length(); i++) {
		if (one[i] == two[i]) result += "0";
		else result += "1";
	}
	return result;
}

char XOR(char one, char two) {
	return (one == two) ? '0' : '1';
}

char XOR_Addition(char one, char two) {
	if (one == '0' && two == '0') return '0';
	else return '1';
}

char XOR_Multiplication(char one, char two) {
	char result = (one == '1' && two == '1') ? '1' : '0';
	return result;
}

string TextToBinary(string word) {
	string binary;
	for (int i = 0; i < word.length(); i++) {
		char c = word[i];
		binary += bitset<8>(c).to_string();
	}
	return binary;
}

string generateGammaKey(string textBinary) {
	string secretGamma = "1101010100011010110011001100111010100101110000101101100110000010";
	string gammaPart1 = secretGamma.substr(0, 19);
	string gammaPart2 = secretGamma.substr(19, 22);
	string gammaPart3 = secretGamma.substr(41, 23);
	string finalGamma;
	for (int i = 0; i < textBinary.length(); i++) {
		finalGamma += XOR(XOR(gammaPart1[0], gammaPart2[0]), gammaPart3[0]);
		char f = XOR_Addition(XOR_Addition(XOR_Multiplication(gammaPart1[8], gammaPart2[10]), XOR_Multiplication(gammaPart1[8], gammaPart3[10])), XOR_Multiplication(gammaPart2[10], gammaPart3[10]));
		string part1String(1, gammaPart1[8]);
		if (part1String[0] == f) {
			char XORpart1 = XOR(XOR(gammaPart1[18], gammaPart1[17]), gammaPart1[16]);
			XORpart1 = XOR(XORpart1, gammaPart1[13]);
			gammaPart1.erase(0, 1);
			gammaPart1 += XORpart1;
		}
		string part2String(1, gammaPart2[10]);
		if (part2String[0] == f) {
			char XORpart2 = XOR(gammaPart2[21], gammaPart2[20]);
			gammaPart2.erase(0, 1);
			gammaPart2 += XORpart2;
		}
		string part3String(1, gammaPart3[10]);
		if (part3String[0] == f) {
			char XORpart3 = XOR(XOR(gammaPart3[22], gammaPart3[21]), gammaPart3[20]);
			XORpart3 = XOR(XORpart3, gammaPart3[7]);
			gammaPart3.erase(0, 1);
			gammaPart3 += XORpart3;
		}
	}
	return finalGamma;
}

int main() {
	system("chcp 65001 > nul");
	int mode = 0;
	while (true) {
		cout << "1. Шифрование\n2. Расшифрование\n3. Выйти из программы\nВыберите режим: ";
		cin >> mode;
		switch (mode) {
			case 1: {
				string text;
				cout << "Введите текст: ";
				cin >> text;
				string textBinary = TextToBinary(text);
				string gammaKey = generateGammaKey(textBinary);
				string test = xor_strings(gammaKey, textBinary);
				cout << "Зашифрованная строка: " << test << endl;
				break;
			}
			case 2: {
				string binaryText;
				cout << "Введите зашифрованный текст: ";
				cin >> binaryText;
				string gammaKey = generateGammaKey(binaryText);
				string tests = xor_strings(gammaKey, binaryText);
				cout << "Расшифрованное сообщение: " << binaryToString(tests) << endl;
				break;
			}
			case 3: {
				return 0;
			}
		}
	}

	return 0;
}
