#include <iostream>
#include <string>

#include "postfix.h"

#include "stack.h"

using namespace std;

int main()
{

  //string expression;
  TPostfix postfix("(((1+23)*1-22)+5)*2-7");
  double check = postfix.Calculate();
  //double res;
  //temp = "1 23+ -22+ 2 5+ -7*+"
  //(1+23)
  //x*1 -22
  //x + 5
  //x*2 - 7
  //setlocale(LC_ALL, "Russian");
  //cout << "Введите арифметическое выражение: ";
  //cin >> expression;
  //cout << expression << endl;
  //cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
  //postfix.ToPostfix();
  //cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;
  //res = postfix.Calculate();
  //cout << res << endl;

  //TStack<int> test(10);

  //for (int i = 0; i < 10; i++)
	  //test.push(i);

  //for (int i = 0; i < 10; i++)
	 // cout << test.pop();

  return 0;
}
