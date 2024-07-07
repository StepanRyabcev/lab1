#pragma once
#include <iostream> 
	
using namespace std;

class Date {
	public: 
	Date(); //конструктор по умолчанию
	Date(int d, int m, int y); //констуктор с параметрамм
	Date(const Date& rhs); //конструктор копирования
	static Date LocalTime(); //возвращает объект класса содержащий текущую дату
	friend ostream& operator<<(ostream& outp__, const Date& date__); //перегрузка оператора вывода
	Date operator+(int rhs) const; //перегрузка оператора сложения
	Date operator-(int rhs) const;
	int operator-(const Date& rhs) const;
	Date& operator+=(int rhs);
	Date& operator-=(int rhs);
	bool operator!=(const Date& rhs) const;
	bool operator==(const Date& rhs) const;
	bool operator<(const Date& rhs) const;
	bool operator<=(const Date& rhs) const;
	bool operator>(const Date& rhs) const;
	bool operator>=(const Date& rhs) const;
	Date& operator=(const Date& rhs);
	friend istream& operator>>(istream& input, Date& date__);
    ~Date();
    const unsigned char day_count[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int d, m, y;
    bool IsLeapYear(int year = -1) const;
private: 
	int GetFromBegin(int startY = 1) const;
	bool AddDay(int& day); //добавляет дни пока не будет равно day
	bool AddMonth(int& day);
	bool AddYear(int& day);
	bool SubYear(int& day);
	bool SubMonth(int& day);
	bool SubDay(int& day);
	};

