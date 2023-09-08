#pragma once

#include <iostream>

using namespace std;

class Cdate {
public:
	Cdate() {};
	Cdate(int d, int m, int y) : day(d), month(m), year(y) {
		cout << "Created a Date successfully!\n";
	};
	~Cdate() {};
	bool check(const int&, const int&, const int&);
	void operator++();
	void operator--();
	bool operator<(const Cdate& other) const;
	bool operator>(const Cdate& other) const;
	bool operator==(const Cdate& other) const;
	bool operator!=(const Cdate& other) const;
	string calculateDayOfWeek(Cdate d);
	friend ostream& operator<<(ostream& out, const Cdate&);
	friend istream& operator>>(istream& in, Cdate&);
private:
	int day, month, year;
};


