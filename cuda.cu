#include <iostream>

typedef int data_type;

struct Matrix {
	int width;
	int height;
	data_type *elements;
	void setProp(int width_, int height_) {
		this->width = width_;
		this->height = height_;
	}
};

__device__ data_type getElement(Matrix *matrix, int row, int col)
{
	return matrix->elements[row * matrix->width + col];
}

__device__ void setElement(Matrix *matrix, int row, int col, int value)
{
	matrix->elements[row * matrix->width + col] = value;
}

__global__ void matMulKernel(Matrix *a, Matrix *b, Matrix *c)
{
	data_type value = 0;
	int row = threadIdx.y + blockIdx.y * blockDim.y;
	int col = threadIdx.x + blockIdx.x * blockDim.x;
	for (int i = 0; i < a->width; i++)
	{
		value += getElement(a, row, i) * getElement(b, i, col);
	}
	setElement(c, row, col, value);
}

inline void printMatrix(Matrix * matrix) {
	for (int i = 0; i < matrix->width * matrix->height; i++) {
		std::cout << (i % matrix->width == 0 ? "\n" : " ") << matrix->elements[i];
	}
}

int main()
{
	int width, height;
	std::cin >> width >> height;

	Matrix *matrix_a, *matrix_b, *matrix_result;

	cudaMallocManaged((void**)&matrix_a, sizeof(Matrix));
	cudaMallocManaged((void**)&matrix_b, sizeof(Matrix));
	cudaMallocManaged((void**)&matrix_result, sizeof(Matrix));
	size_t nBytes = width * height * sizeof(int);
	cudaMallocManaged((void**)&matrix_a->elements, nBytes);
	cudaMallocManaged((void**)&matrix_b->elements, nBytes);
	cudaMallocManaged((void**)&matrix_result->elements, nBytes);

	matrix_a->setProp(width, height);
	matrix_b->setProp(width, height);
	matrix_result->setProp(width, height);

	for (int i = 0; i < width * height; i++)
		std::cin >> matrix_a->elements[i];

	for (int i = 0; i < width * height; i++)
		std::cin >> matrix_b->elements[i];

	dim3 blockSize(32, 32);
	dim3 gridSize((width + blockSize.x - 1) / blockSize.x,
				  (height + blockSize.y - 1) / blockSize.y);
	matMulKernel<<<gridSize, blockSize>>>(matrix_a, matrix_b, matrix_result);

	cudaDeviceSynchronize();

	for (int i = 0; i < width * height; i++) {
		if (i > 0)
			std::cout << (i % width == 0 ? "\n" : " ");
		std::cout << matrix_result->elements[i];
	}
	std::cout << "\n";

	return 0;
}