#include "Date.h"
#include <iostream> 
#include <iomanip> 
#include <ctime>
#include <string>
#include "myexception.h"
#include <QString>

using namespace std; 

Date::Date() //конструктор по умолчанию
{ 
	//инициализация переменных класса
	d = 0; 
	m = 0; 
	y = 0; 
	//вывод объекта класса
	cout << *this << " - родился.\n"; 
}

Date::Date(int d, int m, int y) : d(d), m(m), y(y) //конструктор с параметрами
{
	if (y > 0) //проверка правильно ли введён год
		if (1 <= m && m <= 12) //проверка правильности ввода месяца
		{
            if (!(1 <= d && d <= day_count[m - 1] + (int)((m == 2) && IsLeapYear()))) //проверка если ли такой день в месяце + проверка является ли год високосным для 29 февраля
                throw myexception("Ошибка. День введён неверно."); //выбросить исключение если неверный день
		}
		else
            throw myexception("Ошибка. Месяц должен быть в пределах[1..12]."); //выбросить исключение если неверный месяц
	else 
        throw myexception("Ошибка. Год должен быть больше 0."); //выбросить исключение если неверный год
	//вывод объекта класса
	cout << *this << " - родился.\n";
} 

Date::Date(const Date& rhs) //конструктор копирования
{ 
	//копирование данных
	d = rhs.d; 
	m = rhs.m; 
	y = rhs.y;
	//вывод объекта
	cout << *this << " - родился.\n"; 
} 

Date Date::operator+(int day) const //перегрузка оператора сложения
{ 
		if (day < 0) //проверка является ли день отрицательным
			return *this - (-day); //если отрицательный, то проводим вычитание
		Date NewDate(*this); //создаётся копия объекта
		while (NewDate.AddYear(day)); 
		while (NewDate.AddMonth(day)); 
		while (NewDate.AddDay(day)); 
			return NewDate; 
} 


		Date Date::operator-(int day) const 
		{
			if (day < 0) 
				return *this + (-day); 
			Date NewDate(*this); 
			while (NewDate.SubYear(day));
			while (NewDate.SubMonth(day)); 
			while (NewDate.SubDay(day)); 
			return NewDate;
		}

		int Date::operator-(const Date & rhs) const 
		{
			if ((y < 0) or (rhs.y < 0))
				if (y < rhs.y)
					return this->GetFromBegin(y) - rhs.GetFromBegin(y);
				else
					return this->GetFromBegin(rhs.y) - rhs.GetFromBegin(rhs.y);
			return this->GetFromBegin() - rhs.GetFromBegin();
		} 
		Date& Date::operator+=(int rhs) 
		{
			Date NewDate = *this + rhs; return NewDate;
		} 
		Date& Date::operator-=(int rhs) 
		{
			Date NewDate = *this - rhs;
			return NewDate;
		}
		bool Date::operator!=(const Date & rhs) const 
		{
			return !(*this == rhs);
		} 
		bool Date::operator==(const Date & rhs) const 
		{
			return (this->d == rhs.d) &&
				(this->m == rhs.m) && (this->y == rhs.y);
		} 
		bool Date::operator<(const Date & rhs)
			const 
		{
			if (this->y == rhs.y) 
			{
				if (this->m == rhs.m) 
				{ 
					return this->d < rhs.d;
				}
				else
				{
					return this->m < rhs.m;
				}
			}
			else 
			{ 
				return this->y < rhs.y; 
			}
		} 
		bool Date::operator<=(const Date & rhs) const 
		{
			return (*this == rhs) || (*this < rhs);
		} 
		bool Date::operator>(const Date & rhs) const 
		{
			if (this->y == rhs.y) 
			{
				if (this -> m == rhs.m) 
				{
					return this->d > rhs.d;
				}
				else 
				{ 
					return this->m > rhs.m; 
				}
			}
			else
			{
				return this->y > rhs.y;
			}
		} 
		bool Date::operator>=(const Date & rhs) const 
		{
			return (*this == rhs) || (*this > rhs);
		} Date& Date::operator=(const Date & rhs) 
		{
			if (this == &rhs) 
				return (*this); 
			this->d = rhs.d; 
			this->m = rhs.m; 
			this->y = rhs.y; 
			return (*this);
		}
		Date::~Date() 
		{
			//cout << *this << " - убит.\n"; 
		} 
		int Date::GetFromBegin(int startY) const //получить сколько дней прошло с начала эры
			{ 
			int days = 0;;
			for (int i = startY; i < this->y; i++)
				if (i != 0)
					days += 365 + int(IsLeapYear(i));
			for (int i = 1; i < this->m; i++) days += day_count[i - 1] + int((i == 2) && IsLeapYear());
				days += d; 
			return days; } 
		
		Date Date::LocalTime() //возвращает объект класса содержащий текущую дату
		{
			//получение даты
			time_t rawtime; 
			tm* Time = new tm; 
			time(&rawtime);
			localtime_s(Time, &rawtime);
			//возврат объекта класса с текущей датой
			return Date(Time->tm_mday, Time->tm_mon + 1, Time->tm_year + 1900);
		} 

		bool Date::AddDay(int& day) //вычитает дни пока не будет равно day
		{
			cout << endl << "Add day " << d << " | " << m << " | " << y << endl;
			if (day > 0) 
			{
				day = day - 1; 
				int day_cnt_in_this_mounth = day_count[m - 1] + int((m == 2) && IsLeapYear()); 
				d = d + 1; 
				if (d > day_cnt_in_this_mounth) 
					d = 1, m = m + 1;
				if (m > 12)
				{
					m = 1;
					if (y != -1)
						y = y + 1;
					else
						y = 1;
				}
					return true;
			} 
			return false;
		} 

			bool Date::AddMonth(int& day) 
			{
				cout << endl << "Add day " << d << " | " << m << " | " << y << endl;
				while (d != 1 && AddDay(day)); int
					day_cnt_in_this_mounth = day_count[m - 1] + int((m == 2) && IsLeapYear()); 
				if (day >= day_cnt_in_this_mounth) 
				{
					day = day - day_cnt_in_this_mounth; 
					m = m + 1;
					if (m > 12)
					{
						m = 1;
						if (y != -1)
							y = y + 1;
						else
							y = 1;
						return true;
					}
				} 
				return false;
			} 
			
			bool Date::AddYear(int& day) 
			{
				cout << endl << "Add day " << d << " | " << m << " | " << y << endl;
				while (d != 1 && AddDay(day)); 
				while (m != 1 && AddMonth(day)); 
				int day_in_this_year = 365 + int(IsLeapYear()); 
				if (day >= day_in_this_year) 
				{
					day = day - day_in_this_year; 
					if (y != -1)
						y = y + 1;
					else
						y = 1;
					return true;
				} 
			return false;

			} bool Date::SubYear(int&
				day) {
				while (d != day_count[m - 1] + int((m == 2) && IsLeapYear()) &&
					SubDay(day)); while (m != 12 && SubMonth(day)); int day_in_this_year = 365 +
					int(IsLeapYear()); if (day >= day_in_this_year) {
					day = day - day_in_this_year; y = y
						- 1; return true;
				} return false;
			} bool Date::SubMonth(int& day) {
				while (d !=
					day_count[m - 1] + int((m == 2) && IsLeapYear()) && SubDay(day)); int
					day_cnt_in_this_mounth = day_count[m - 1] + int((m == 2) && IsLeapYear());
				if (day >= day_cnt_in_this_mounth) {
					day = day - day_cnt_in_this_mounth; m = m -
						1; if (m < 1) m = 12, y = y - 1; d = day_count[m - 1] + int((m == 2) &&
							IsLeapYear()); return true;
				} return false;
			} bool Date::SubDay(int& day) {
				if (day >
					0) {
					day = day - 1; d = d - 1; if (d < 1) {
						m = m - 1; if (m - 1 < 1) m = 12, y = y - 1; int
							day_cnt_in_month = day_count[m - 1] + int((m == 2) && IsLeapYear()); d =
							day_cnt_in_month;
					} return true;
				} return false;
			} bool Date::IsLeapYear(int year)
				const {
				if (year == -1) year = this->y; if (year % 400 == 0) return true; if (year % 100
					== 0) return false; if (year % 4 == 0) return true; return false;
			} 
				
			ostream& operator<<(ostream& outp__, const Date& date__) 
			{
				//форматирование вывода
				outp__ << setw(2) << setfill('0') << date__.d << "."; outp__ << setw(2) << setfill('0') << date__.m << "."; outp__ << setw(4) << setfill('0') << date__.y;
				//возврат вывода
				return outp__;
			}

			istream& operator>>(istream& input, Date& date__)
			{	
				string inp;
				input >> inp;
				date__.d = stoi(inp.substr(0, inp.find(".")));
				date__.m = stoi(inp.substr(inp.find(".") + 1, inp.rfind(".") - inp.find(".")));
				date__.y = stoi(inp.substr(inp.rfind(".") + 1));
				if (date__.y != 0) //проверка правильно ли введён год
					if (1 <= date__.m && date__.m <= 12) //проверка правильности ввода месяца
					{
						if (!(1 <= date__.d && date__.d <= date__.day_count[date__.m - 1] + (int)((date__.m == 2) && date__.IsLeapYear()))) //проверка если ли такой день в месяце + проверка является ли год високосным для 29 февраля 
                            throw myexception("Ошибка. День введён неверно."); //выбросить исключение если неверный день
					}
					else
                        throw myexception("Ошибка. Месяц должен быть в пределах[1..12]."); //выбросить исключение если неверный месяц
				else
                    throw myexception("Ошибка. Год должен быть больше 0."); //выбросить исключение если неверный год
				return input;
			}
