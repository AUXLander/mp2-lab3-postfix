#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"

using namespace std;

class TPostfix {
	string infix;
	string postfix;
	TStack<string> _T;

	string convertString(string source) {

		for (size_t i = 0; i < source.length(); i++) {
			switch (source[i]) {
			case ' ':
				source.erase(i, 1);
				continue;
			case '-':
				source.replace(i++, 1, "+-");
			}
		}
		return source;
	}
	double decodeVal(string value) {

		double div = 1;
		double result = 0;
		bool negative = false;

		const int sta = (int)('0');
		const int end = (int)('9');
		const int exc_1 = (int)('.');
		const int exc_2 = (int)('-');

		for (auto c : value) {

			int ch = (int)c;
			switch (ch) {
			case exc_1:
				div = 0.1;
				continue;
			case exc_2:
				negative = !negative;
				break;
			default:
				if (ch >= sta && ch <= end) {
					if (div > 0.5) {
						result *= 10;
					}
					result += (ch - sta)*div;
				}
			}
			if (div < 1) {
				div *= 0.1;
			}
		}
		if (negative) {
			result *= -1;
		}
		return result;
	}
	string getVal(string& source, size_t start) {

		string val;
		const int sta = (int)('0');
		const int end = (int)('9');
		const int exc_1 = (int)('.');
		const int exc_2 = (int)('-');
		const int exc_3 = (int)('x');

		for (; start < source.length();) {
			int c = (int)source[start];
			switch (c) {
			default:
				if (c < sta || end < c) { return val; }
			case exc_1:
			case exc_2:
			case exc_3:
				val += source[start];
				source.erase(start, 1);
			}
		}
		return val;
	}
	void ToPostfixIteration(string source) {
		TStack<string> _N(100);
		TStack<char> _O(100);

		char locType = '\0';
		string result;

		size_t locPos;
		size_t locMin = 0;

		bool flag = true;
		while (flag) {
			flag = false;
			for (int i = 0; i < source.length(); i++) {
				if (source[i] == '(') {
					flag = true;
					for (size_t offset = 0, j = i + 1; j < source.length(); j++) {
						if (source[j] == '(') {
							offset++;
							continue;
						}
						if (source[j] == ')') {
							string h = source.substr(offset + i + 1, j - i - offset - 1);
							ToPostfixIteration(h);
							source.replace(offset + i, j - i - offset + 1, "x");
							break;
						}
					}
					i = -1;
				}
			}
		}
		string base = source;
		while (locMin < 10) {
			locMin = 10;
			for (size_t i = 0; i < base.length(); i++) {
				switch (base[i]) {
				case '+':
					if (1 < locMin) {
						locMin = 1;
						locPos = i;
					}
					break;
				case '*':
				case '/':
					if (2 < locMin) {
						locMin = 2;
						locPos = i;
					}
					break;
				}
			}
			if (locMin < 10) {
				_O.push(base[locPos]);
				base.erase(locPos, 1);
			}
		}

		while (source.length() > 0) {
			for (int i = 0; i < source.length(); i++) {
				char ch = source[i];

				switch (ch) {
				case '*':
				case '/':
				case '+':
					locType = ch;
					locPos = i;
					continue;
				default:
					_N.push(getVal(source, i));
					if (!_O.IsEmpty()) {
						char lastO = _O.pop();
						if (locType == lastO) {
							if (!_N.IsEmpty()) {
								result += _N.pop() + ' ';
							}
							if (!_N.IsEmpty()) {
								result += _N.pop();
							}
							result += lastO;
							source.erase(locPos, 1);
						}
						else {
							_O.push(lastO);
						}
					}
					else {
						result += _N.pop();
						break;
					}
					i = -1;
					continue;
				}
			}
		}
		_T.push(result);
	}

public:
	TPostfix(string base) : _T(100), infix(convertString(base)) {
		postfix = ToPostfix(infix);
	}
	string GetInfix() { return infix; }
	string GetPostfix() { return postfix; }
	string ToPostfix(string source) {

		ToPostfixIteration(source);
		string temp = _T.pop();
		while (!(_T.IsEmpty())) {
			for (int i = temp.length(); i >= 0; --i) {
				if (temp[i] == 'x') {
					temp.erase(i, 1);
					string h = _T.pop();
					temp.insert(i, h);
					i = temp.length() - 1;
				}
			}
		}
		return temp;
	}
	double Calculate(string source = "\0") { // Ввод переменных, вычисление по постфиксной форме
		
		TStack<double> _D(100);
		if (source == "\0") {
			source = postfix;
		}
		for (int i = 0; i < source.length(); i++) {
			switch (source[i]) {
			default: {
				_D.push(decodeVal(getVal(source, i)));
				i = -1;
				continue;
			}
			case ' ': {
				break;
			}
			case '+': {
				_D.push(_D.pop() + _D.pop());
				break; 
			}
			case '*': {
				_D.push(_D.pop() * _D.pop());
				break;
			}
			case '/': {
				_D.push(_D.pop() / _D.pop());
				break;
			}
			}
			source.erase(0, 1);
			i = -1;
		}
		return _D.pop();
	}
};
#endif