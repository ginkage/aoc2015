#include "../lib.hpp"

long result = 0;

void skip(istream &cin) {
    while (cin && isspace(cin.peek()))
        cin.get();
}

bool parse_value(istream &cin);

bool parse_string(istream &cin) {
    skip(cin);
    cin.get(); // "
    stringstream ss;
    while (cin.peek() != '\"')
        ss << (char)cin.get();
    cin.get();
    return ss.str() == "red";
}

void parse_object(istream &cin) {
    long tmp = result;
    skip(cin);
    cin.get(); // {
    skip(cin);
    bool red = false;
    while (cin.peek() != '}') {
        parse_string(cin);
        skip(cin);
        cin.get(); // :
        if (parse_value(cin))
            red = true;
        skip(cin);
        if (cin.peek() == ',')
            cin.get();
    }
    cin.get(); // }
    if (red)
        result = tmp;
}

void parse_number(istream &cin) {
    skip(cin);
    stringstream ss;
    while (cin.peek() == '-' || isdigit(cin.peek()))
        ss << (char)cin.get();
    result += stol(ss.str());
}

void parse_bool(istream &cin) {
    skip(cin);
    while (isalpha(cin.peek()))
        cin.get();
}

void parse_array(istream &cin) {
    skip(cin);
    cin.get(); // [
    skip(cin);
    while (cin.peek() != ']') {
        parse_value(cin);
        skip(cin);
        if (cin.peek() == ',')
            cin.get();
    }
    cin.get(); // ]
}

bool parse_value(istream &cin) {
    skip(cin);
    char c = cin.peek();
    if (c == '{')
        parse_object(cin);
    else if (c == '[')
        parse_array(cin);
    else if (c == '\"')
        return parse_string(cin);
    else if (c == '-' || isdigit(c))
        parse_number(cin);
    else
        parse_bool(cin);
    return false;
}

int main()
{
    ifstream cin("input.txt");
	parse_value(cin);
	cout << result << endl;
	return 0;
}