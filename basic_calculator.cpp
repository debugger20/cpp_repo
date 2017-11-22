// https://github.com/debugger20/cpp_repo.git

/*
You are building an educational website and want to create a simple calculator for students to use. For now, the calculator will only allow addition and subtraction of positive integers.

Given an expression string using the "+" and "-" operators like "5+16-2", write a function to parse the string and evaluate the result.

Sample input/output:
"6+9-12" => 3
"1+2-3+4-5+6-7" => -2

We also want to allow parentheses in our input. Given an expression string using the "+", "-", "(", and ")" operators like "5+(16-2)", write a function to parse the string and evaluate the result.

Sample input:
    expression1 = "5+16-((9-6)-(4-2))"
    expression2 = "22+(2-4)"
 
Sample output:
    evaluate(expression1) => 20
    evaluate(expression2) => 20
*/

#include <iostream>
#include <stack>
using namespace std;

int extractNumber2(string& str, int f, int l) {
  int num = 0;
  int digit = 1;
  
  // cout << "f: " << f << " l:" << l << endl;
  
  for (int i = l; i >= f; i--) {
    num += (str[i] - '0') * digit;
    digit *= 10;
  }
  
  return num;
}

int extractNumber(string& str, int pos, int& lastPos) {
  
  int i = pos;
  for (; i < str.size() && str[i] != '+' && str[i] != '-'; i++);
  
  // cout << str << endl;
  
  lastPos = i;
  i--;
  return extractNumber2(str, pos, i);
}

int calculator(string& str) {
  
  int num = 0;
  int i = 0;
  int lastPos;
  int total = 0;
  
  while (i < str.size()) 
  {
    if (str[i] == '+') {
      num = extractNumber(str, i+1, lastPos);
      cout << "num: " << num << endl;
      i = lastPos; 
      total += num;
    }
    else if (str[i] == '-') {
      num = extractNumber(str, i+1, lastPos);
      cout << "num: " << num << endl;
      i = lastPos; 
      total -= num;      
    }
    else {
      total = extractNumber(str, i, lastPos);
      cout << "total: " << total << endl;
      i = lastPos;
    }  
  }
  
  return total;
}


// 5+16-((9-6)-(4-2))

// 5 // + // '1' // '6' // - // ( // '9' // - // '6' //  

void insertNumIntoStack(stack<char>& st, int num) {
  stack<char> tempSt;
  
  int rem;
  
  while(num > 0) {
    rem = num % 10;
    num = num / 10;
    tempSt.push(rem + '0');
  }
  
  while(!tempSt.empty()) {
    st.push(tempSt.top());
    tempSt.pop();
  }
}

void calculateInStack(stack<char>& st) {
  
  // ( 1 + 2 - 3 )
  int num = 0;
  int total = 0;
  int digit = 1;
  
  while ( st.top() != '(' ) {
    
    if (st.top() == '+') {
      total = total + num;
      digit = 1;
      num = 0;
    }
    else if (st.top() == '-') {
      total = total - num;
      digit = 1;
      num = 0;
    }
    else {
      num += (st.top() - '0') * digit;
      digit *= 10;
    }
    st.pop();
  }
  
  // pop the '('
  total += num;
  st.pop();
  
  cout << total << endl;
  
  if (total < 0) {
    if (st.empty()) {
      st.push('-');
    }
    else if (st.top() == '+') {
      st.pop();
      st.push('-');
    }
    else if (st.top() == '-') {
      st.pop();
      st.push('+');
    }
    total *= -1;
  }
  
  insertNumIntoStack(st, total);
}

int calculator2(string& str) {
  
  stack<char> elements;
  elements.push('(');
  
  int i = 0;
  while (i < str.size()) {
    
    if (str[i] == ')') {
        calculateInStack(elements);        
    }
    else {
      elements.push(str[i]);
    }
    
    i++;
  }
  
  calculateInStack(elements);
  
  
  int num = 0;
  int digit = 1;
  bool neg = false;
  
  while(!elements.empty()) {
    if (elements.top() == '-') {
      neg = true;
      break;
    }
    
    num += (elements.top() - '0') * digit;
    digit *= 10;
    elements.pop();
  }
  
  return neg ? -1 * num : num;
}


// To execute C++, please define "int main()"
int main() {
  // string expression = "6+9-12";
  string expression = "11";
  string expression1 = "5+16-((9-6)-(4-2))";
  string expression2 = "4+(5+4+3-4)+8-(10-8)";
  
  // cout << calculator(expression) << endl;
  
  cout << calculator2(expression2) << endl;
  
  
  return 0;
}
