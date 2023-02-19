#include <iostream>

using namespace std;

int* generateGamma(int a, int b, int c);
int main()
{
    setlocale(LC_ALL, "Russian");
    int a, b, c, gamma;
    cout << "Введите 3 числа: ";
    cin >> a >> b >> c;
    cout << "Первое число\t" << "Второе число\t" << "Третье число\t" << "Гамма" << endl;
    cout << "\t" << a << "\t\t" << b << "\t\t" << c << endl;
    for (int i = 0; i < 8; i++) {
        int* newNumber = generateGamma(a, b, c);
        a = newNumber[0];
        b = newNumber[1];
        c = newNumber[2];
        gamma = newNumber[3];
        cout << "\t" << a << "\t\t" << b << "\t\t" << c << "\t" << gamma << endl;
    }
}

int *generateGamma(int a, int b, int c)
{
    int newA, newB, newC, gamma;
    gamma = c;

    newB = a;
    newC = b;

    if (a == c) newA = 0;
    if (a != c) newA = 1;

    int newArray[4] = { newA, newB, newC, gamma };
    return newArray;
}
