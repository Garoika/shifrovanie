#include <iostream>
#include <cstring>
#include <cmath>
#include <string>
#include <bitset>
#include <vector>

using namespace std;

int gcd(int a, int b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

string XOR(string textBinary, string tBinary, int b) {
	if (textBinary.length() != tBinary.length()) {
		cout << "XOR: Строки не равны!";
		return "";
	}
	string resultBinary;
	for (int i = 0; i < textBinary.length(); i++) {
		if (tBinary[i] != textBinary[i]) {
			resultBinary += "1";
		}
		else resultBinary += "0";
	}
	return resultBinary;
}

int findCoPrime(int n) {
	for (int i = 2; i < n; i++) {
		if (gcd(i, n) == 1) {
			return i;
		}
	}
	return -1;
}

int modInverse(int a, int m) {
	int m0 = m, t, q;
	int x0 = 0, x1 = 1;

	if (m == 1) {
		return 0;
	}

	while (a > 1) {
		q = a / m;
		t = m;
		m = a % m, a = t;
		t = x0;
		x0 = x1 - q * x0;
		x1 = t;
	}

	if (x1 < 0) {
		x1 += m0;
	}
	return x1;
}

int hashing(string message, int n) {
	const string hNull = "00000000";
	string hOne;
	vector<string> t;
	vector<string> result;
	int resultHOne = 0;

	for (int i = 0; i < message.length(); i++) {
		bitset<8> messageBit(message[i]);
		int len = messageBit.to_string().length();

		string part1 = messageBit.to_string().substr(0, len / 2);
		string part2 = messageBit.to_string().substr(len / 2, len);

		t.push_back("1111" + part1);
		t.push_back("1111" + part2);

	}

	for (int i = 0; i < message.length() * 2; i++) {
		if (i == 0) {
			result.push_back(XOR(hNull, t[i], i));
			bitset<8> bts(result[i]);
			int powchik = pow(bts.to_ulong(), 2);
			bitset<8> g(powchik % n);
			hOne = g.to_string();
		}
		else {
			result.push_back(XOR(hOne, t[i], i));
			bitset<8> bts(result[i]);
			int test = pow(bts.to_ulong(), 2);
			test = test % n;
			bitset<8> two(test);
			hOne = two.to_string();
		}
		if (i == (message.length() * 2) - 1) {
			bitset<8> hOneResult(hOne);
			resultHOne = hOneResult.to_ulong();
		}
	}

	return resultHOne;
}

int powmod(int base, int exp, int mod) {
	int res = 1;
	while (exp > 0) {
		if (exp % 2 == 1) {
			res = (res * base) % mod;
		}
		base = (base * base) % mod;
		exp = exp / 2;
	}
	return res;
}

int main() {
	int mode;
	while (true) {
		int p, q, n, phi, e, d, hashMessage, s, h;
		cout << "1. Генерация подписи\n2. Проверка подписи\n3. Выход из программы\nВыберите действие: ";
		cin >> mode;
		switch (mode) {
			case 1: {
				system("cls");
				string message;
				cout << "Введите P:";
				cin >> p;
				cout << "Введите Q:";
				cin >> q;
				cout << "Введите сообщение:";
				cin >> message;

				n = p * q;
				phi = (p - 1) * (q - 1);
				e = findCoPrime(phi);
				d = modInverse(e, phi);
				hashMessage = hashing(message, n);
				s = powmod(hashMessage, d, n);
				system("cls");
				cout << "E: " << e << endl;
				cout << "ЭЦП: " << s << endl;
				cout << "N: " << n << endl;
				cout << "HashMessage: " << hashMessage << endl;
			break;
			}
			case 2: {
				int n, e, s, h, hashMessage;
				cout << "Введите N:";
				cin >> n;
				cout << "Введите E:";
				cin >> e;
				cout << "Введите ЭЦП:";
				cin >> s;
				cout << "Введите Хеш Сообщения:";
				cin >> hashMessage;

				h = powmod(s, e, n);
				system("cls");
				if (hashMessage == h) cout << "Подпись верна";
				else cout << "Подпись не верна";
			}
			case 3: {
				return 0;
			}
		}
	}
}
