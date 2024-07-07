#pragma once
#include <iostream> 
	
using namespace std;

class Date {
	public: 
	Date(); //����������� �� ���������
	Date(int d, int m, int y); //���������� � �����������
	Date(const Date& rhs); //����������� �����������
	static Date LocalTime(); //���������� ������ ������ ���������� ������� ����
	friend ostream& operator<<(ostream& outp__, const Date& date__); //���������� ��������� ������
	Date operator+(int rhs) const; //���������� ��������� ��������
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
	bool AddDay(int& day); //��������� ��� ���� �� ����� ����� day
	bool AddMonth(int& day);
	bool AddYear(int& day);
	bool SubYear(int& day);
	bool SubMonth(int& day);
	bool SubDay(int& day);
	};

