#include <iostream>
#include <cstdlib>
#include <math.h>
#include <ctime>

using namespace std;


int modInverse(int a, int m);
int obrChisl(int a, int z, int m);


int generate_random_number(int min_num, int max_num) {
	srand(time(NULL));

	int random_number = rand() % (max_num - min_num + 1) + min_num; // генерируем число в заданном интервале

	return random_number;
}

int main()
{
	//setlocale(LC_ALL, "Russian");
	int p, q, g, x, y, k, gOBR, r, h, s, rsh, gsh, t;
	cout << "Введите p:";
	cin >> p;
	cout << "Введите q:";
	cin >> q;
	cout << "Введите h:";
	cin >> gsh;

	if ((p - 1) % q == 0) {

		if (gsh < 1 || gsh > p - 1) {
			cout << "Ошибка! Число g не входит в промежуток от 1 до " << p - 1;
			return 0;
		}

		g = pow(gsh, ((p - 1) / q));
		g = g % q;
		cout << "Введите t (40 <= t < q):";
		cin >> t;

		if (t < 40 || t > q) {
			cout << "Ошибка! Число t не входит в промежуток от 40 до " << q;
			return 0;
		}

		h = generate_random_number(1, pow(2, t) - 1);
		cout << "Введите X (1 < x < q - 2):";
		cin >> x;
		gOBR = modInverse(g, p);
		y = obrChisl(gOBR, x, p);

		k = generate_random_number(1, (q - 1));

		r = obrChisl(g, k, p);

		s = (k + x * h) % q;
		rsh = obrChisl(g, s, p);
		rsh = rsh * obrChisl(y, h, p);
		rsh = obrChisl(rsh, 1, p);

		cout << "Генерация подписи r: " << r << endl;
		cout << "Проверка подписи r`: " << rsh << endl;
	}


	system("pause");
	return 0;
}

int gcdExtended(int a, int b, int& x, int& y) {
	if (a == 0) {
		x = 0;
		y = 1;
		return b;
	}

	int x1, y1;
	int gcd = gcdExtended(b % a, a, x1, y1);

	x = y1 - (b / a) * x1;
	y = x1;

	return gcd;
}

int modInverse(int a, int m) {
	int x, y;
	int gcd = gcdExtended(a, m, x, y);

	if (gcd != 1) {
		return -1;
	}
	else {
		return (x % m + m) % m;
	}
}

int obrChisl(int a, int z, int m) {
	int a1 = a;
	int z1 = z;
	int x = 1;

	while (z1 != 0) {
		while (z1 % 2 == 0) {
			z1 = z1 / 2;
			a1 = (a1 * a1) % m;
		}
		z1 = z1 - 1;
		x = (x * a1) % m;
	}
	return x;
}
