#include <iostream>
#include <string>

#include "postfix.h"

#include "stack.h"

using namespace std;

int main()
{
  double res;
  string expression;
  TPostfix postfix("((1+2*3)/4+6)*8");
  setlocale(LC_ALL, "Russian");
  cout << "Введите арифметическое выражение: ";
  cin >> expression;
  cout << expression << endl;
  postfix.SetInfix(expression);
  cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
  postfix.ToPostfix();
  cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;
  res = postfix.Calculate();
  cout << res << endl;

  return 0;
}
