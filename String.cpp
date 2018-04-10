#include <cstddef> // size_t
#include <cstring> // strlen, strcpy
#define _CRT_SECURE_NO_WARNINGS
#include <utility>
#include <iostream>

using namespace std;

struct String {

	String(const char *str = "") {
		this->size = strlen(str);
		strcpy_s(this->str = new char[size + 1], size + 1, str);
	}
		
	String(size_t n, char c) {
		this->size = n;
		char* temp = new char[size + 1];
		for (size_t i = 0; i != size; i++) {
			temp[i] = c;
		}
		temp[size] = '\0';
		this->str = temp;
	}
		
	~String() { delete[]str; }

	void append(String &other) {
		int new_size = other.size + this->size + 1;
		char* new_str = new char[new_size];
		strcpy_s(new_str, new_size, this->str);
		strcpy_s(new_str + size, new_size, other.str);
		new_str[new_size - 1] = '\0';
		delete[]str;
		this->str = new_str;
		this->size = new_size - 1;
	}

	String(const String &other) :size(other.size), str(new char[size]) {
		strcpy_s(str, size + 1, other.str);
	};

	String &operator=(const String& other) {
		if (this != &other) {
			delete[]str;
			str = new char[other.size];
			size = other.size;
			strcpy_s(str, size + 1, other.str);
		}
		return *this;
	};

	/*
	//перемещающий конструктор
	String(String && s) :size(s.size), str(s.str) {
		s.str = nullptr;
		s.size = 0;
	}

	//перемещающий оператор присваивания
	String & operator=(String && s) {
		delete[]str;
		str = s.str;
		size = s.size;
		s.str = nullptr;
		s.size = 0;
		return *this;
	}
	*/

	void swap(String & s) {
		std::swap(str, s.str);
		std::swap(size, s.size);
	}
	//перемещающий конструктор
	String(String && s) {
		std::cout << "Move Constructor" << std::endl;
		swap(s);
	}
	//перемещающий оператор присваивания
	String & operator=(String && s) {
		swap(s);
		std::cout << "Move Operator = " << std::endl;
		return *this;
	}

	size_t size = 0;
	char *str = nullptr;
};

int main() {
	
	String s1 = String("Hellow");
	String s2("world");
	//String s3 = s1 + ", " + s2 + " !";
	String s3("Helow, world!");
	String s4 = s3;
	s1 = std::move(s4);
	s2 = String(s1);
	
	return 0;
}
