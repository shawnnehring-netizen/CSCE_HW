#include <iostream>
#include <stdexcept>
#include <limits>

int largest(int a, int b, int c) {
  int d = a;
  if (b > d) {
    d = b;
  } if (c > d) {
    d = c;
  }
  return d;
}

bool sum_is_even(int a, int b) {
  if((a+b)%2 == 0){
    return true;}
  else{
    return false;
  }
}

int boxes_needed(int apples) {
  if (apples < 0){
    return 0;}
  if (apples %20 != 0){
    return 1+ apples/20;
  }
  else {
    return apples/20;}
}

bool smarter_section(int A_correct, int A_total, int B_correct, int B_total) {
  if (A_correct > A_total || B_correct > B_total){
    throw std::invalid_argument("invalid input");}
  if (!(A_correct >= 0 && A_total >= 0 && B_correct >= 0 && B_total >= 0)){
    throw std::invalid_argument("invalid input");
  }
  double multi = B_total / A_total;
  return (A_correct * multi) > B_correct;}


bool good_dinner(int pizzas, bool is_weekend) {
  if ((pizzas >= 10 && pizzas <= 20) && (!is_weekend)) {
    return true;
  }
  else if (is_weekend && pizzas >= 10) {
    return true;
  }
  return false;
}

int sum_between(int low, int high) {
  long int num_max = std::numeric_limits<int32_t>::max();
  long int num_min = std::numeric_limits<int32_t>::min();
  long int sum = (low + high);
  long double div_1 = low / 2.0;
  long double div_2 = high/2.0;
  //std::cout << div_1 << " " << div_2 << " "<< div_2-div_1;
  long int total = (div_2-div_1+.5) * sum;
  if (((div_2-div_1+.5) * sum) > num_max || ((div_2-div_1+.5) * sum) < num_min){
    throw std::overflow_error("overflow");
  }
  return total;
}

int product(int a, int b) {
  long long int num_max = std::numeric_limits<int64_t>::max();
  long long int num_min = std::numeric_limits<int64_t>::min();
  long long int mult = a * b;
  if ((a*b) < num_min || (a*b) > num_max){
    throw std::overflow_error("overflow");
  }
  return mult;
}