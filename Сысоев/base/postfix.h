#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"
#include <vector>

using namespace std;

class TPostfix{
	string infix;
	string postfix;

	size_t getPriority(char c) {
		switch (c) {
		case '*':
		case '/':
			return 2;
		case '+':
		case '-':
			return 1;
		default:
			return 0;
		}
	}
	struct sInstructions {
		double *instruction;
		size_t *priority;
	};

	string convertString(string source) {
		string temp = "";
		size_t len = source.length();
		for (size_t i = 0; i < len; i++) {
			switch (source[i]) {
			case ' ':
				continue;
			case '-':
				temp += '+';
			default:
				temp += source[i];
			}
		}
		return temp;
	}
	size_t iCounter;
	struct instruction {
		size_t pri; // 0 - число; >0 - приоритет операции
		double val; // X - число; 1 = +, 2 = *, 3 = /
	};
	double decodeVal(string v) {
		size_t len = v.length();
		size_t next = 1;
		double div = 0.1;
		double value = 0;
		double temp;
		for (auto c : v) {
			temp = 0;
			switch (c) {
			case '-': value *= -1; break;
			case '.': div *= 0.1; break;
			case '1': temp = 1;	break;
			case '2': temp = 2;	break;
			case '3': temp = 3;	break;
			case '4': temp = 4;	break;
			case '5': temp = 5;	break;
			case '6': temp = 6;	break;
			case '7': temp = 7;	break;
			case '8': temp = 8;	break;
			case '9': temp = 9;	break;
			case '0': temp = 0;	break;
			default: continue;
			}
			value += temp * (next *= 10)*div;
			if (div*next < 1) {
				div *= 0.1;
			}
		}
		return value;
	}
	instruction* stack;
	
	void splitOperations(string source) {
		iCounter = 0;

		size_t Priority = 0;
		size_t len = source.length();
		stack = new instruction[len];
		size_t i = 0;
		string val("");
		while (i < len) {
			char c = source[i++];
			switch (c) {
			case '(':
				if (val != "") {
					stack[iCounter++] = { 0, decodeVal(val) };
				}
				Priority += 2;
				val = "";
				continue;
			case ')':
				if (val != "") {
					stack[iCounter++] = { 0, decodeVal(val) };
				}
				Priority -= 2;
				val = "";
				continue;
			case '+':
				if (val != "") {
					stack[iCounter++] = { 0, decodeVal(val) };
				}
				stack[iCounter++] = { 1 + Priority, 1 };
				val = "";
				continue;
			case '*':
				if (val != "") {
					stack[iCounter++] = { 0, decodeVal(val) };
				}
				stack[iCounter++] = { 2 + Priority, 2 };
				val = "";
				continue;
			case '/':
				if (val != "") {
					stack[iCounter++] = { 0, decodeVal(val) };
				}
				stack[iCounter++] = { 2 + Priority, 3 };
				val = "";
				continue;
			default:
				val += c;
			}
		}
		stack[iCounter++] = { 0, decodeVal(val) };
	}
	double calc() {
		size_t lMaxPri;
		size_t lMaxPriInd;
		
		while (true) {
			lMaxPri = 0;

			for (size_t i = 0; i < iCounter; i++) {
				if (stack[i].pri > lMaxPri) {
					lMaxPri = stack[i].pri;
					lMaxPriInd = i;
				}
			}
			if (lMaxPri != 0) {
				switch ((int)stack[lMaxPriInd].val) {
				case 1:
					stack[lMaxPriInd - 1].val += stack[lMaxPriInd + 1].val;
					break;
				case 2:
					stack[lMaxPriInd - 1].val *= stack[lMaxPriInd + 1].val;
					break;
				case 3:
					stack[lMaxPriInd - 1].val /= stack[lMaxPriInd + 1].val;
					break;
				}
				stack[lMaxPriInd].pri = 0;
				stack[lMaxPriInd].val = 0;
				stack[lMaxPriInd + 1].val = 0;
				
				iCounter -= 2;

				instruction* tStack;
				tStack = new instruction[iCounter];

				for (size_t i = 0, j = 0; i < iCounter + 2; i++) {
					if (stack[i].pri > 0 || stack[i].val > 0) {
						tStack[j++] = stack[i];
					}
				}
				
				delete[] stack;
				stack = new instruction[iCounter];
				for (size_t i = 0; i < iCounter; i++) {
					stack[i] = tStack[i];
				}
				delete[] tStack;
			}
			else {
				return stack[0].val;
				//все операции 
			}
		}
	}
	
public:
	TPostfix(string base){
		infix = convertString(base);
		splitOperations(infix);
 		double t = calc();
	}
	string GetInfix() { return infix; }
	string GetPostfix() { return postfix; }
	string ToPostfix();
	double Calculate(); // Ввод переменных, вычисление по постфиксной форме
};

#endif
//(1+2)/(3+4*6.7)-5.3*4.4
//1 2+ 3 4 6.7*+/ 5.3 4.4* -