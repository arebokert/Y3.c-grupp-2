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
  if(a != nullptr)
    //delete[] a;
  a = nullptr;
}
/*
Matrix& Matrix::operator=(Matrix&& rhs) & noexcept {
  std::swap(a, rhs.a);
  std::swap(width, rhs.width);
  std::swap(height, rhs.height);
  return *this;
}
*/
int& Matrix::at(int x, int y) {
  if(x >= width)
    x = width - 1;
  if(y >= height)
    y = height -1;
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
    }
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
