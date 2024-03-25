
#include "main.h"

using namespace s21;

int main(){


  // test_1();
  test_2();
  // test_stod();
  return 0;
}

void test_2(){

  // std::string str = "1*2/sin(3)-(4^(ln(5)/6))";
  // std::string str = "2/sin(1)-(4^(5/6))";
  std::string str = "2/sin(x-4/6";
  // std::string str = "sin(x)--atan(10.2)+200";
  // std::string str = "sqrt(x)*(x+tan(sin(2*x-x)+cos(8-x)))";
  // std::string str = "1-2";
  std::string x_str = "10";
  double x = 10;
  SmartCalc t;

  t.SetVarX(x_str);
  // t.IsValidString(str);
  // t.ShuntingYard();
  // t.Calculation();
  double res = t.ProcessAndCalculate(str);
  double expect = (2 / sin(x) - 4.0 / 6.0);

  std::cout << str << " IsValidString = " <<  (t.GetStatus() == kOk ? "Ok" : "Error")  << "\n";
  std::cout << "res " << res <<  " expect " << expect << "\n";

  // str = "1 2 * 3 sin / 4 5 log 6 / ^ - \n";
  // std::cout << str;
}

void test_1(){

  std::string str = "aasin";
  SmartCalc t;

  t.SetVarX(str);
  double res = t.ProcessAndCalculate(str);
  std::cout << "x " << (t.GetStatus() == kOk ? "Ok" : "Error") << "\n";
  std::cout << "res " << res << "\n";
  // std::cout << *it << "\n";
}

void test_0 (){
  std::string str = "Hello World, Privet Mir";
  // const std::string::iterator cit = str.find('W');
  auto it = str.cbegin();
  it++;
  // auto b = it.base();

  auto x = it - str.end();
  std::cout << "x " << x << "\n";
  std::cout << *it << "\n";
  std::cout << str.size() << "\n";
  std::cout << str.capacity() << "\n";

}

void test_stod (){
  std::string orbits ("1.0e-(0.1)-sin(x)-29e-0002");
  // std::string orbits ("36.5e+0.105-29e-0002");
  std::string::size_type sz;     // alias of size_t

  double earth = std::stod (orbits,&sz);
  double moon = std::stod (orbits.substr(sz));
  std::cout << "The moon completes " << earth << " / " << moon << " = " << (earth/moon) << " orbits per Earth year.\n";
}

void test_stod_2 (){
  std::string orbits ("365.24 29.5334 314,1");
  size_t sep;     // alias of size_t
  size_t sep1 = 0;     // alias of size_t


  double a365 = std::stod (orbits,&sep);
  std::cout << sep <<  " <sep \n";
  std::string x = orbits.substr(sep);
  sep1 += sep;
  double b29 = std::stod (x, &sep);
  sep1 += sep;
  x = orbits.substr(sep1);
  double c314 = std::stod (x, &sep);
  sep1 += sep;
  x = orbits.substr(sep1);

  std::cout << a365 << " <a " << b29 << " <b " << c314 << " <c \n";
}