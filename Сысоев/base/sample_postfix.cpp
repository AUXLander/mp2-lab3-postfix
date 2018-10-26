#include <iostream>
#include <string>

#include "postfix.h"

#include "stack.h"

using namespace std;

int main()
{

  //string expression;
  TPostfix postfix("(1 + 2) *3/9*(100/1000)");
  //double res;

  //setlocale(LC_ALL, "Russian");
  //cout << "Введите арифметическое выражение: ";
  //cin >> expression;
  //cout << expression << endl;
  //cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
  //postfix.ToPostfix();
  //cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;
  //res = postfix.Calculate();
  //cout << res << endl;

  TStack<int> test(10);

  for (int i = 0; i < 10; i++)
	  test.push(i);

  for (int i = 0; i < 10; i++)
	  cout << test.pop();

  return 0;
}
