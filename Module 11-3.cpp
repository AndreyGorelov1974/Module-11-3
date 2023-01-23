/*Задание 3. Валидация IP-адреса
Что нужно сделать
Проверьте, задаёт ли введённая пользователем строка корректный IP-адрес четвёртой версии (IPv4).
IP-адрес должен представлять из себя четыре числа, разделённые точками без пробелов, причём каждое число должно быть в диапазоне от 0 до 255 включительно.
Числа не должны содержать ведущих нулей. Других символов в строке, кроме вышеописанных, быть не должно.

Пользователь вводит строку, задающую IP-адрес через стандартный ввод.
В результате программа должна вывести слово Valid, если адрес корректен, и слово Invalid, если это не так.

Примеры

Корректные: 
127.0.0.1 
255.255.255.255 
1.2.3.4 
55.77.213.101

Некорректные: 
255.256.257.258 (есть числа больше 255) 
0.55.33.22. (лишняя точка в конце) 
10.00.000.0 (лишние нули) 
23.055.255.033 (опять лишние нули) 
65.123..9 (две точки подряд) 
a.b.c.d (посторонние символы вместо чисел и точек)

Рекомендации
Активно используйте оператор индексации строки str[i], но помните, что индексы начинаются с нуля, а не с единицы.
Создайте отдельную функцию для получения отдельных чисел из IP-адреса и валидируйте эти отдельные числа.
Для валидации отдельных цифр у чисел следует использовать оператор сравнения с константами символов. Символы от ‘0’ до ‘9’ расположены последовательно и поэтому уместны операторы <= и >=.
Вам потребуется функция, принимающая на вход строку со всем IP-адресом и порядковый номер октета.
Октет — это часть IP-адреса между точками. Он содержится в восьми битах, отсюда и название (окта — восемь).
2^8 = 256. Отсюда уже предел значения октета — 255. То есть вызов get_address_part(“192.168.1.1”, 1) вернёт 168.
Данная функция проходит по всей строке и ищет разделители — точки, одновременно с этим накапливает символы в строку, которую вернёт в результате.
При нахождении разделителя нужно вернуть полученную строку.
Проверку её корректности нужно делать в другой функции (проверить длину == 3 и то, что число в строке находится в диапазоне [0,255] ).*/

#include <iostream>
#include <string>

// функция вырезания части адреса до @, если @ нет возвращаем пустую строку
std::string cut_name_post_box(std::string str) {
	std::string result = "";
	for (int i = 0; i < str.length(); i++) {
		if (str[i] != '@') {
			result += str[i];
		}
		else {
			return result;
		}
	}
	return result = "";
}

// функция вырезания части адреса после @, если @ нет возвращаем пустую строку
std::string cut_domain_name(std::string str) {
	std::string result = "";
	bool find = false;
	for (int i = 0; i < str.length(); i++) {
		if (find) {
			result += str[i];
		}
		if (str[i] == '@') {
			find = true;
		}
	}
	return result;
}

// функция проверки корректности, на вход подаём проверяемую строку, и строку-словарь разрешённых символов
bool check_address(std::string checkStr, std::string passedStr) {
	int checkStrLength = checkStr.length();
	int passedStrLength = passedStr.length();

	if (checkStr[0] == '.' || checkStr[checkStrLength - 1] == '.') {
		return false;
	}

	for (int i = 0; i < checkStrLength; i++) {
		if (checkStr[i] == '.' && checkStr[i + 1] == '.' && i < (checkStrLength - 1)) {
			return false;
		}

		bool noFind = true;
		for (int j = 0; j < passedStrLength && noFind; j++) {
			if (checkStr[i] == passedStr[j]) {
				noFind = false;
			}
		}
		if (noFind) {
			return false;
		}
	}
	return true;
}

//функция проверки адреса почты
bool check_email(std::string checkAddress) {
	std::string namePostBox = cut_name_post_box(checkAddress);
	std::string domainName = cut_domain_name(checkAddress);

	if (namePostBox.length() < 1 || namePostBox.length() > 64 || domainName.length() < 1 || domainName.length() > 63) {
		return false;
	}
	//строки разрешённых символов
	std::string passedSymbolNamePostBox = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890-.!#$%&'*+-/=?^_`{|}~";
	std::string passedSymbolDomainName = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890-.";

	return check_address(namePostBox, passedSymbolNamePostBox) && check_address(domainName, passedSymbolDomainName) ? true : false;
}



int main() {
	std::string emailAddress;
	std::cout << "Enter email address: ";
	std::cin >> emailAddress;

	while (emailAddress.length() > 128) {
		std::cout << "The email address is too long, enter again: ";
		std::cin >> emailAddress;
	}

	std::cout << std::endl << (check_email(emailAddress) ? "Yes" : "No");
}