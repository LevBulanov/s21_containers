#include "s21_stack.h"

#include <iostream>
#include <stack>

int main() {
  s21::stack<int> stack1;
  std::cout << "stack1.empty - " << stack1.empty() << std::endl;
  std::cout << "stack1.pop" << std::endl;
  stack1.pop();
  stack1.push(10);
  std::cout << "push 10" << std::endl;
  std::cout << "stack1.empty - " << stack1.empty() << std::endl;
  std::cout << "stack1.size - " << stack1.size() << std::endl;
  std::cout << "stack1.top - " << stack1.top() << std::endl;
  stack1.push(20);
  std::cout << "push 20" << std::endl;
  std::cout << "stack1:" << std::endl;
  stack1.print();
  std::cout << "stack1.top - " << stack1.top() << std::endl;
  std::cout << "stack1.size - " << stack1.size() << std::endl;
  std::cout << "stack1.empty - " << stack1.empty() << std::endl;
  s21::stack<int> stack2{5, 10, 15, 20};
  std::cout << "stack2 initialisation 5, 10, 15, 20" << std::endl;
  std::cout << "stack2.size - " << stack2.size() << std::endl;
  std::cout << "stack2:" << std::endl;
  stack2.print();
  std::cout << "stack2.pop" << std::endl;
  stack2.pop();
  std::cout << "stack2:" << std::endl;
  stack2.print();
  std::cout << "stack2.size - " << stack2.size() << std::endl;
  s21::stack<int> stack3 = stack2;
  std::cout << "stack3:" << std::endl;
  stack3.print();
  std::cout << "stack3.size - " << stack3.size() << std::endl;
  stack3.swap(stack1);
  std::cout << "swap stack1 & stack3" << std::endl;
  std::cout << "stack3:" << std::endl;
  stack3.print();
  std::cout << "stack3.size - " << stack3.size() << std::endl;
  std::cout << "stack1:" << std::endl;
  stack1.print();
  std::cout << "stack1.size - " << stack1.size() << std::endl;
  std::cout << "stack1.empty - " << stack1.empty() << std::endl;
  s21::stack<int> stack4 = std::move(stack1);
  std::cout << "stack1:" << std::endl;
  stack1.print();
  std::cout << "stack4:" << std::endl;
  stack4.print();
  stack4 = std::move(stack3);
  std::cout << "move stack4 <- stack3" << std::endl;
  std::cout << "stack4:" << std::endl;
  stack4.print();
}