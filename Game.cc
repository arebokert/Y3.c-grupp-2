#include <iostream>
#include "Matrix.h"
using namespace std;

int main() {
  Matrix mat{5,8};
  cout << mat.at(0,1) << endl;

  for(int i = 0; i < mat.sizeX(); i++) {
    for(int j = 0; j < mat.sizeY(); j++)
      mat.at(i,j) = i*j;
  }

  for(int i = 0; i < mat.sizeX(); i++) {
    for(int j = 0; j < mat.sizeY(); j++)
      cout << " "  << mat.at(i,j) << " ";
    cout << endl;
  }

  cout << mat.at(2,3) << endl;

  Matrix mat2 = mat.getArea(1,1,4,4);
  mat = std::move(Matrix{400,200});
  for(int i = 0; i < mat2.sizeX(); i++) {
    for(int j = 0; j < mat2.sizeY(); j++)
      cout << " "  << mat2.at(i,j) << " ";
    cout << endl;
  }
  
  return 0;
}
