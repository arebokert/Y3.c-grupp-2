#include <iostream>
#include "Matrix.h"
using namespace std;

Matrix::Matrix(int x, int y) {
  
  try {
    a = new int[x*y];
  }
  catch(bad_alloc& ba) {
    cerr << ba.what() << endl;
  }

  width = x;
  height = y;
}

Matrix::~Matrix() {
  cout << "Trying to delete a" << endl;
  cout << a[1] << endl;
  if(a != nullptr)
    //delete[] a;
  a = nullptr;
  cout << "a deleted" << endl;
}
/*
Matrix& Matrix::operator=(Matrix&& rhs) & noexcept {
  std::swap(a, rhs.a);
  std::swap(width, rhs.width);
  std::swap(height, rhs.height);
  return *this;
}
*/
int& Matrix::at(const int x, const int y) {
  return a[x+width*y];
}

int Matrix::sizeX() const {
  return width;
}

int Matrix::sizeY() const {
  return height;
}

Matrix Matrix::getArea(int fromX, int fromY, int toX, int toY) noexcept {
 

  Matrix temp{toX-fromX+1, toY-fromY+1};
  
  for(int i = 0; i < temp.sizeX(); i++) {
    for(int j = 0; j < temp.sizeY(); j++) {
      
      temp.at(i,j) = a[(i+fromX) + width*(j+fromY)];
      cout << temp.at(i,j) << " ";
    }
    cout << endl;
  }

  return temp;
}

void Matrix::transpose() {
  /*
  int* b;
  try {
    b = new int[x*y];
  }
  catch(bad_alloc& ba) {
    cerr << ba.what() << endl;
  }
  */
  
}
