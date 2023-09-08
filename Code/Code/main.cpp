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


bool Cdate::check(const int& a, const int& b, const int& c) {
    switch (b) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        if (a <= 0 || a > 31)
            return false;
        break;
    case 4: case 6: case 9: case 11:
        if (a <= 0 || a > 30)
            return false;
        break;
    case 2:
        if (c % 400 == 0 || (c % 4 == 0 && c % 100 == 0)) {
            if (a <= 0 || a > 29)
                return false;
        }
        else {
            if (a <= 0 || a > 28)
                return false;
        }
        break;
    default:
        return false;
    }
    return true;
}

istream& operator>>(istream& in, Cdate& d) {
    bool k;
    do {
        k = false;
        cout << "Day = "; in >> d.day;
        cout << "Month = "; in >> d.month;
        cout << "Year = "; in >> d.year;
        k = d.check(d.day, d.month, d.year);
        if (k == false) cout << "Please try again!\n";
    } while (!k);
    return in;
}

ostream& operator<<(ostream& out, const Cdate& d) {
    out << d.day << "/" << d.month << "/" << d.year;
    return out;
}

void Cdate::operator++() {
    day++;
    switch (month) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        if (day > 31) {
            day = 1;
            month++;
            if (month > 12) {
                year++;
                month = 1;
            }
        }
        break;
    case 4: case 6: case 9: case 11:
        if (day > 30) {
            day = 1;
            month++;
        }
        break;
    case 2:
        if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) {
            if (day > 29) {
                day = 1;
                month++;
            }
        }
        else {
            if (day > 28) {
                day = 1;
                month++;
            }
        }
    }
}

void Cdate::operator--(){
    day--;
    if (day == 0) {
        month--;
        switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10:
            day = 31;
            break;
        case 12:
            day = 31;
            month = 12;
            year--;
            break;
        case 4: case 6: case 9: case 11:
            day = 30;
            break;
        case 2:
            if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
                day = 29;
            else
                day = 28;
            break;
        }
    }
}

//Return true if date1 < date2
bool Cdate::operator<(const Cdate& other) const {
    if (year < other.year) return true;
    if (year > other.year) return false;
    if (month < other.month) return true;
    if (month > other.month) return false;
    return day < other.day;
}

//Return true if date1 > date2
bool Cdate::operator>(const Cdate& other) const {
    return other < *this;
}

bool Cdate::operator==(const Cdate& other) const {
    return day == other.day && month == other.month && year == other.year;
}
bool Cdate::operator!=(const Cdate& other) const {
    return !(*this == other);
}

string Cdate::calculateDayOfWeek(Cdate d) {
    if (d.month < 3) {
        d.month += 12;
        d.year--;
    }
    int h = (d.day + (13 * (d.month + 1)) / 5 + d.year + d.year / 4 - d.year / 100 + d.year / 400) % 7;
    string daysOfWeek[] = { "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};

    return daysOfWeek[h];
}

int main() {
    cout << "Name: Dinh Duc\t\t Class: 22T_DT2\n";
    cout << "MSSV: 102220098\n\n";
	Cdate date1, date2;
    //Date 1:
    cout << "Enter the date 1:\n";
	cin >> date1;
    cout << "The date of date 1 is " << date1.calculateDayOfWeek(date1) << " " << date1 << endl;
    ++date1;
    cout << "The next date of date 1 is " << date1 << endl;
    --date1;
    --date1;
    cout << "The previous date of date 1 is: " << date1 << endl;

    //Date 2:
    cout << "Enter the date 2:\n";
    cin >> date2;
    cout << "The date of date 2 is: " << date2.calculateDayOfWeek(date2) << " " << date2 << endl;
    ++date2;
    cout << "The next date of date 2 is: " << date2 << endl;
    --date2;
    --date2;
    cout << "The previous date of date 2 is: " << date2 << endl;

    //Compare two date
    if (date1 < date2) {
        cout << "date1 < date2" << endl;
    }
    else if (date1 > date2) {
        cout << "date1 > date2" << endl;
    }
    else {
        cout << "date1 == date2" << endl;
    }

    if (date1 == date2) {
        cout << "date1 == date2" << endl;
    }
    else {
        cout << "date1 != date2" << endl;
    }

	return 0;
}