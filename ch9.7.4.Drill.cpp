#include "std_lib_facilities.h"

const vector<string> months{
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December"
};

enum class Month {
	jan, feb, mar, apr, may, jun, july, aug, sept, oct, nov, dec
};

Month operator++(Month& m)
{
	m = (m == Month::dec) ? Month::jan : Month(int(m) + 1);
	return m;
}

ostream& operator<<(ostream& os, Month m)
{
	return os << months[int(m)];
}

class Date {
private:
	int y;
	Month m;
	int d;

	bool is_valid()
	{
		if (y < 0 || d < 0 || d > 31)
			return false;
		else
			return true;
	}

public:
	Date(int y, Month m, int d);
	void add_day(int n);
	int year() const { return y; }
	Month month() const { return m; }
	int day() const { return d; }
};

Date::Date(int yy, Month mm, int dd)
	:y{ yy }, m{ mm }, d{ dd }
{
	if (d < 1 || 31 < d) error("impossible day");
}

void Date::add_day(int n)
{
	d += n;
	if (d > 31) d %= 31;
}

ostream& operator<<(ostream& os, const Date& d)
{
	return os << '(' << d.year()
		<< ',' << d.month()
		<< ',' << d.day() << ')';
}


int main()
try {
	Date today(1978, Month::jun, 25);
	Date tomorrow = today;
	tomorrow.add_day(1);
	cout << today << endl;
	cout << tomorrow << endl;
	//Date bad_day (2004, Month(13), -5);
	//cout << bad_day << endl;
	return 0;
}
catch (exception& e)
{
	cerr << e.what() << endl;
	return 1;
}