#include <iostream>
#include <stdexcept>
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
    throw std::invalid_argument("invalid input");
  }
  return A_correct/A_total > B_correct/B_total;}


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
  int sum = (low + high) * ((high + 1 -low)/2);
  return sum;
}

int product(int a, int b) {
  //if (mult < -9223372036854775808 || mult > 9223372036854775807){
  //  throw std::overflow_error("too big or short");
  //}
  return a*b;
}