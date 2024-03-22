
#include "main.h"

using namespace s21;

int main(){


  test_2();
  // test_stod();
  return 0;
}

void test_2(){

  // std::string str = "-10.02+15.2-5e-64";
  // std::string str = "-1.23*100/sin(2.5)-(2^(ln(9)/10))";
  std::string str = "-x+(100)";
  std::string x_str = "12";
  SmartCalc t;

  t.SetVarX(x_str);
  t.IsValidString(str);
  std::cout << "IsValidString = " <<  (t.GetStatus() == kOk ? "Ok" : "Error")  << "\n";
  // std::cout << *it << "\n";
}

void test_1(){

  std::string str = "aasin";
  SmartCalc t;

  t.SetVarX(str);
  std::cout << "x " << t.IsFunc(str)<< "\n";
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
  std::string orbits ("36.5e+0.105-29e-0002");
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