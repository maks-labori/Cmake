// Copyright 2026 Maksim Tarasenko

#define EASY_EXAMPLE
#ifdef EASY_EXAMPLE

#include <iostream>
#include <iomanip>
#include "../Algorithms/easy_example.h"
#include "../multistack_lib/multistack.h"

int main() {
  /*int a, b;
  float result;

  a = 1; b = 4;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }

  a = 1; b = 0;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }*/
  Multistack<int> stack(3, 21);
  std::cout << stack.isEmpty();
  stack.push(1, 40);
  std::cout << stack.top(1);


  return 0;
}

#endif  // EASY_EXAMPLE
