#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
public:
	Matrix(int, int);
	Matrix(Matrix&&) = default;
	~Matrix();
	Matrix& operator=(Matrix&&) & noexcept;
	int& at(const int, const int);
	int sizeX() const;
	int sizeY() const;
	Matrix getArea(int,int,int,int) noexcept;
	void transpose();
private:
	int* a;
	int width{0};
	int height{0};
};

#endif
