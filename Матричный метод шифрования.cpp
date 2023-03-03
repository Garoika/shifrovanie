#include <iostream>
#include <vector>
#include <string>

using namespace std;

int charToNum(char c) {
	c = toupper(c);
	return c - 'A';
}

vector<vector<int>> matrixMultiply(const vector<vector<int>>& a, const vector<vector<int>>& b) {
	int m = a.size();
	int n = b[0].size();
	vector<vector<int>> c(m, vector<int>(n));

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			int sum = 0;
			for (int k = 0; k < b.size(); k++) {
				sum += a[i][k] * b[k][j];
			}
			c[i][j] = sum;
		}
	}

	return c;
}

void print_matrix(vector<vector<double>> matrix) {
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[0].size(); j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

vector<vector<double>> inverse(vector<vector<double>> matrix) {
	int n = matrix.size();
	vector<vector<double>> identity(n, vector<double>(n, 0.0));
	for (int i = 0; i < n; i++) {
		identity[i][i] = 1.0;
	}
	for (int i = 0; i < n; i++) {
		double div = matrix[i][i];
		for (int j = 0; j < n; j++) {
			matrix[i][j] /= div;
			identity[i][j] /= div;
		}
		for (int j = 0; j < n; j++) {
			if (i != j) {
				double factor = matrix[j][i];
				for (int k = 0; k < n; k++) {
					matrix[j][k] -= factor * matrix[i][k];
					identity[j][k] -= factor * identity[i][k];
				}
			}
		}
	}
	return identity;
}

vector<vector<double>> multiply(vector<vector<double>> a, vector<vector<double>> b) {
	int n = a.size(), m = b[0].size(), p = b.size();
	vector<vector<double>> c(n, vector<double>(m, 0.0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int k = 0; k < p; k++) {
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	return c;
}

string decrypt(vector<vector<double>> key, vector<vector<double>> message) {
	vector<vector<double>> inverse_key = inverse(key);
	print_matrix(inverse_key);
	vector<vector<double>> decrypted = multiply(message, inverse_key);
	string plaintext = "";
	print_matrix(decrypted);
	for (int i = 0; i < decrypted.size(); i++) {
		for (int j = 0; j < decrypted[0].size(); j++) {
			plaintext += 'A' + static_cast<int>(decrypted[i][j] + 0.5);
		}
	}
	return plaintext;
}

int main() {
	while (true) {
		int mode;
		cout << "Выберите режим работы: \n" << "1. Зашифровка\n2. Расшифровка" << endl;
		cin >> mode;

		if (mode == 1) {
			string word;
			cout << "Введите слово на английском языке (кратное 3 букв): ";
			cin >> word;

			vector<int> nums;
			for (char c : word) {
				nums.push_back(charToNum(c));
			}

			int cols = nums.size() / 3;
			vector<vector<int>> matrix(3, vector<int>(cols));
			int idx = 0;
			for (int j = 0; j < cols; j++) {
				for (int i = 0; i < 3; i++) {
					matrix[i][j] = nums[idx];
					idx++;
				}
			}

			cout << "Матрица:\n";
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < cols; j++) {
					cout << matrix[i][j] << " ";
				}
				cout << endl;
			}

			vector<vector<int>> key(3, vector<int>(3));
			cout << "Введите ключ (матрицу 3x3):\n";
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					cin >> key[i][j];
				}
			}
			cout << "Ключ:\n";
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					cout << key[i][j] << " ";
				}
				cout << endl;
			}
			vector<vector<int>> result = matrixMultiply(key, matrix);

			cout << "Результат:\n";
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < cols; j++) {
					cout << result[i][j] << " ";
				}
				cout << endl;
			}
		}
		else if (mode == 2) {
			int n;
			cout << "Введите размер ключевой матрицы (N x N): ";
			cin >> n;
			vector<vector<double>> key(n, vector<double>(n));
			cout << "Введите ключевую матрицу: " << endl;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					cin >> key[i][j];
				}
			}
			int m;
			cout << "Введите количество столбцов в матрице зашифрованного сообщения: ";
			cin >> m;
			vector<vector<double>> message(m, vector<double>(n));
			cout << "Введите матрицу зашифрованного сообщения (По столбцам, сверху вниз): " << endl;
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					cin >> message[i][j];
				}
			}
			string plaintext = decrypt(key, message);
			cout << "Расшифрованное сообщение: " << plaintext << endl;
		}
	}
}
