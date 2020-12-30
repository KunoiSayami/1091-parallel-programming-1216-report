#include <cstdio>
#include <omp.h>
#include <chrono>
#include <iostream>

using namespace std::chrono;

typedef float data_type;

struct Matrix {
	int width;
	int height;
	data_type *elements;
	void setProp(int width_, int height_) {
		this->width = width_;
		this->height = height_;
	}
};

data_type getElement(Matrix *matrix, int row, int col)
{
	return matrix->elements[row * matrix->width + col];
}

void setElement(Matrix *matrix, int row, int col, int value)
{
	matrix->elements[row * matrix->width + col] = value;
}

void matMulKernel(int row, int col, Matrix *a, Matrix *b, Matrix *c)
{
	data_type value = 0;
	for (int i = 0; i <= a->width; i++) {
		value += getElement(a, row, i) * getElement(b, i, col);
	}
	setElement(c, row, col, value);
}

inline void printMatrix(Matrix * matrix) {
	for (int i = 0; i < matrix->width * matrix->height; i++) {
		std::cout << (i % matrix->width == 0 ? "\n" : " ") << (int)matrix->elements[i];
	}
}

int main() {
	int width, height;
	std::cin >> width >> height;

	Matrix *matrix_a, *matrix_b, *matrix_result;

	matrix_a = new Matrix;
	matrix_b = new Matrix;
	matrix_result = new Matrix;
	size_t sz = width * height;
	matrix_a->elements = new data_type[sz];
	matrix_b->elements = new data_type[sz];
	matrix_result->elements = new data_type[sz];

	matrix_a->setProp(width, height);
	matrix_b->setProp(width, height);
	matrix_result->setProp(width, height);

	for (int i = 0; i < width * height; i++)
		std::cin >> matrix_a->elements[i];

	for (int i = 0; i < width * height; i++)
		std::cin >> matrix_b->elements[i];


	high_resolution_clock::time_point start_time = high_resolution_clock::now();
#pragma omp parallel for default(none) shared(width, height, matrix_a, matrix_b, matrix_result)
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
			matMulKernel(j, i, matrix_a, matrix_b, matrix_result);

	printMatrix(matrix_result);

	std::cerr << "Time spend: " << duration_cast<duration<double>>(high_resolution_clock::now() - start_time).count() << "\n";

	delete [] matrix_a->elements;
	delete [] matrix_b->elements;
	delete [] matrix_result->elements;
	delete matrix_a;
	delete matrix_b;
	delete matrix_result;
}