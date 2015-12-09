#include <iostream>
#include "Matrix.h"
using namespace std;

int main() {

  //Default-constructor
  cout << "Creating m1 using default-constructor" << endl;
  Matrix m1;
  cout << m1.at(0,0) << endl;
  cout << "Successful" << endl;

  //Normal-constructor
  cout << "Creating m2 using normal-constructor" << endl;
  Matrix m2{50,50};
  m2.fillWith(5);
  cout << m2.at(25,25) << endl;
  cout << (m2.at(25,25) == 5 ? "Successful" : "Expected value: 5") << endl;

  //Copy-constructor
  cout << "Creating m3 using copy-constructor on m2" << endl;
  Matrix m3{m2};
  cout << m3.at(25,25) << endl;
  cout << (m3.at(25,25) == 5 ? "Successful" : "Expected value: 5") << endl;

  //Move-constructor
  cout << "Creating m4 using move-constructor on m2" << endl;
  Matrix m4{std::move(m2)};
  cout << m4.at(25,25) << endl;
  cout << (m4.at(25,25) == 5 ? "Successful" : "Expected value: 5") << endl;
  
  //Copy_assignment-operator
  cout << "Creating m5 using copy-assignment on m4" << endl;
  Matrix m5 = m4;
  cout << m5.at(25,25) << endl;
  cout << (m5.at(25,25) == 5 ? "Successful" : "Expected value: 5") << endl;
  
  //Move_assignment-operator
  cout << "m5 using move-assignment on m4" << endl;
  m4.fillWith(10);
  m5 = std::move(m4);
  cout << m5.at(25,25) << " : " << m5.sizeX() << " : " << m5.sizeY() << endl;
  cout << (m5.at(25,25) == 10 ? "Successful" : "Expected value: 10") << endl; 

  //getArea
  cout << "Creating m6 using getArea on m5" << endl;
  Matrix m6{std::move(m5.getArea(0,0,30,30))};
  cout << m6.at(25,25) << " : " << m6.sizeX() << " : " << m6.sizeY() << endl;
  cout << (m6.at(25,25) == 10 ? "Successful" : "Expected value: 10") << endl; 
  


  return 0;
}
