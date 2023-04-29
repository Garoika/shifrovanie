#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <bitset>
#include <vector>
#include <string>

using namespace std;

int gcd(int a, int b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

int findCoPrime(int n) {
	for (int i = 2; i < n; i++) {
		if (gcd(i, n) == 1) {
			return i;
		}
	}
	return -1;
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

// Функция для нахождения обратного числа
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
	int h = NULL;
	const int hNull = 6;
	vector<int> wordPos;
	for (int i = 0; i < message.length(); i++) {
		message[i] = toupper(message[i]);
		wordPos.push_back(message[i] - 'A' + 1);

		if (i == 0)
			h = pow(wordPos[i] + hNull, 2);
		else
			h = pow(wordPos[i] + h, 2);

		h = h % n;
	}
	return h;
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
	int mode = 0;

	while (true) {
		cout << "1)Генерация подписи\n2)Проверка подписи\nВыберите режим: ";
		cin >> mode;
		switch (mode) {
			case 1: {
				int p, q, x, k, y, n, m, kInv, a, b, hNull;
				string message;
				cout << "Введите P: ";
				cin >> p;
				cout << "Введите Q: ";
				cin >> q;
				cout << "Введите X который будет < " << p << ": ";
				cin >> x;
				cout << "Введите сообщение: ";
				cin >> message;

				if (x >= p) { cout << "Ошибка: число x больше и равно p!"; return 0; }

				n = p * q;
				m = hashing(message, n);
				y = pow(q, x);
				y = y % p;
				k = findCoPrime(p - 1);
				kInv = modInverse(k, p - 1);
				a = pow(q, k);
				a = a % p;
				b = ((m - x * a) * kInv) % (p - 1);
				b = (b + (p - 1)) % (p - 1);
				cout << "a: " << a << endl <<
					"b: " << b << endl <<
					"y: " << y << endl <<
					"m: " << m << endl;

				break;
			}
			case 2: {
				int p, q, y, m, a, b, r, s;

				cout << "Введите P: ";
				cin >> p;
				cout << "Введите Q: ";
				cin >> q;
				cout << "Введите Хеш (m): ";
				cin >> m;
				cout << "Введите A: ";
				cin >> a;
				cout << "Введите B: ";
				cin >> b;
				cout << "Введите Y: ";
				cin >> y;

				r = powmod(y, a, p);
				s = powmod(a, b, p);

				int rFinal = (r * s) % p;
				int sFinal = powmod(q, m, p);
				cout << "rFinal: " << rFinal << endl;
				cout << "sFinal: " << sFinal << endl;
				if (rFinal == sFinal) cout << "Подпись верна" << endl;
				else cout << "Подпись не верна" << endl;
				break;
			}
		}
	}

	return 0;
}
