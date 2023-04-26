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
		char character = (char)stoi(eightBits, nullptr, 2);
		result += character;
	}

	return result;
}

string xor_strings(string one, string two) {
	string result;
	if (one.length() != two.length()) {
		cout << "?????? ?? ?????!";
		return "";
	}
	for (int i = 0; i < one.length(); i++) {
		if (stoi(to_string(one[i])) == stoi(to_string(two[i]))) result += "0";
		else result += "1";
	}
	return result;
}

int XOR(char one, char two) {
	if (one == two) return '0';
	else return '1';
}

char XOR_Addition(char one, char two) {
	if (one == '0' && two == '0') return '0';
	else return '1';
}

char XOR_Multiplication(char one, char two) {
	if (one == '1' && two == '1') return '1';
	else return '0';
}

string TextToBinary(string word) {
	string binary;
	for (int i = 0; i < word.length(); i++) {
		char c = word[i];
		bitset<8> bits(c);
		binary += bits.to_string();
	}
	return binary;
}

string generateGammaKey(string textBinary) {
	string SecretGamma = "1101010100011010110011001100111010100101110000101101100110000010";

	string part1 = SecretGamma.substr(0, 19);
	string part2 = SecretGamma.substr(19, 23);
	string part3 = SecretGamma.substr(42, 22);

	string FinalGamma;

	for (int i = 0; i < textBinary.length(); i++) {
		FinalGamma += XOR(XOR(part1[0], part2[0]), part3[0]);

		char f = XOR_Addition(XOR_Addition(XOR_Multiplication(part1[8], part2[10]), XOR_Multiplication(part1[8], part3[10])), XOR_Multiplication(part2[10], part3[10]));
		string part1String(1, part1[8]);
		if (part1String[0] == f) {
			char XORpart1 = XOR(XOR(part1[18], part1[17]), part1[16]);
			XORpart1 = XOR(XORpart1, part1[13]);
			part1.erase(0, 1);
			part1 += XORpart1;
		}

		string part2String(1, part2[10]);
		if (part2String[0] == f) {
			char XORpart2 = XOR(part2[21], part2[20]);
			part2.erase(0, 1);
			part2 += XORpart2;
		}

		string part3String(1, part3[10]);
		if (part3String[0] == f) {
			char XORpart3 = XOR(XOR(part3[22], part3[21]), part3[20]);
			XORpart3 = XOR(XORpart3, part3[7]);
			part3.erase(0, 1);
			part3 += XORpart3;
		}
	}

	return FinalGamma;
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
		case 2:
		{
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
