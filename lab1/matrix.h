#pragma once
#define order 6

#include<iostream>
#include<vector>
#include "date.h"
#include "graph.h"



template<typename T>
class MatrixElement {
public:
	int i;
	int j;
	T data;
	MatrixElement* next = nullptr;
	MatrixElement* prev = nullptr;
   

};

template<typename T>
class Matrix {
public:

	MatrixElement<T>* head = nullptr;
	MatrixElement<T>* end = nullptr;




	void add(T data, int i, int j) {
		MatrixElement<T>* new_element = new MatrixElement<T>;
		new_element->i = i;
		new_element->data = data;
		new_element->j = j;

		if (!head) {
			head = new_element;
			end = new_element;
		}
		else {
			new_element->next = head;
			head->prev = new_element;
			head = new_element;
		}

	}

	friend bool operator==(const Matrix<T> &horizontal_A, const Matrix<T> &horizontal_B) {
		MatrixElement<T>* element_A = horizontal_A.end;
		MatrixElement<T>* element_B = horizontal_B.end;
		bool flag = true;
		while (element_A && element_B) {
			if (element_A->j != element_B->j) {
				flag=false;
			}
			element_A = element_A->prev;
			element_B = element_B->prev;
		}

		if (element_A || element_B)
			flag = false;
		return flag;
	}



};


template<typename T>
MatrixElement<T>* search_by_index(Matrix<T> horizontal[order], int i, int j) {
	MatrixElement<T>* result = new MatrixElement<T>;
	if (i < order && j < order) {
		result = horizontal[i].end;
		for (int k = 0; k < order; k++) {
			if (!result || result->j > j) {
				result = new MatrixElement<T>;
				result->i = i;
				result->j = j;
				result->data = 0;

				return result;
			}
			else if (result && result->j == j) {
				return result;
			}
			result = result->prev;
		}
	}
	std::cout << "Wrong indexes!" << std::endl;
	return result;
}




template<typename T>
MatrixElement<T>* search_by_value(Matrix<T> horizontal[order], T data) {
	MatrixElement<T>* result = new MatrixElement<T>;
	if (data) {
		for (int i = 0; i < order; i++) {
			result = horizontal[i].end;
			for (int j = 0; j < order; j++) {
				if (result && result->data == data) {
					return result;
				}
				result = result->prev;
			}
		}
	}
	else {
		for (int i = 0; i < order; i++) {
			result = horizontal[i].end;
			for (int j = 0; j < order; j++) {
				if (!result) {
					MatrixElement<T>* result = new MatrixElement<T>;
					result->i = i;
					result->j = j;
					result->data = data;
					return result;
				}
				else if ((!result->next && result->j != 0) || (!result->next && !result->prev && result->j != 0)) {
					MatrixElement<T>* result = new MatrixElement<T>;
					result->i = i;
					result->j = j;
					result->data = data;
					return result;
				}
				else if (result->prev && result->j != result->prev->j - 1) {
					result->data = data;
					result->i = i;
					result->j = result->j + 1;
					return result;
				}
				result = result->prev;
			}
		}
	}

	std::cout << "There is no item with the specified value" << std::endl;
	result = new MatrixElement<T>;
	return result;
}


template<typename T>
void all_search_by_value(Matrix<T> horizontal[order], std::vector< MatrixElement<T>*>& search_vector, T data) {
	MatrixElement<T>* element = new MatrixElement<T>;
	if (data) {
		for (int i = 0; i < order; i++) {
			element = horizontal[i].end;
			while (element) {
				if (element && element->data == data) {
					search_vector.push_back(element);
				}
				element = element->prev;
			}
		}
	}
	else {
		for (int i = 0; i < order; i++) {
			element = horizontal[i].end;
			int j_last = 0;
			while (element) {
				if ((!element->next && element->prev && element->j != 0)) {
					for (int k = 0; k < element->j; k++) {
						MatrixElement<T>* e = new MatrixElement<T>;
						e->data = data;
						e->i = i;
						e->j = k;
						j_last = k;
						search_vector.push_back(e);
					}
				}
				else if (!element->next && !element->prev && element->j != 0) {
					for (int k = 0; k < element->j; k++) {
						MatrixElement<T>* e = new MatrixElement<T>;
						e->data = data;
						e->i = i;
						e->j = k;
						j_last = k;
						search_vector.push_back(e);
					}
					for (int k = element->j + 1; k < order; k++) {
						MatrixElement<T>* e = new MatrixElement<T>;
						e->data = data;
						e->i = i;
						e->j = k;
						j_last = k;
						search_vector.push_back(e);
					}

				}
				else if (!element->prev && !element->next && element->i == 0) {
					for (int k = 1; k < order; k++) {
						MatrixElement<T>* element = new MatrixElement<T>;
						element->data = data;
						element->i = i;
						element->j = k;
						j_last = k;
						search_vector.push_back(element);
					}
				}
				else if (element->prev && element->j != element->prev->j - 1) {

					int j_copy = element->j + 1;
					while (j_copy != element->prev->j)
					{
						MatrixElement<T>* e = new MatrixElement<T>;
						e->data = data;
						e->i = i;
						e->j = j_copy;
						j_last = j_copy;
						j_last = j_copy;
						search_vector.push_back(e);
						j_copy++;
					}

				}
				element = element->prev;
				j_last++;
			}
			for (int k = j_last; k < order; k++) {
				MatrixElement<T>* element = new MatrixElement<T>;
				element->data = data;
				element->i = i;
				element->j = k;
				search_vector.push_back(element);
			}

		}
	}
}


template<typename T>
void push_sum(MatrixElement<T>* element, Matrix<T>(&result)[order], int i) {
	while (element != nullptr) {
		result[i].add(element->data, element->i, element->j);
		element = element->prev;
	}
}

template<typename T>
void matrix_sum(Matrix<T> A_horizontal[order], Matrix<T> B_horizontal[order], Matrix<T>(&result)[order]) {
	for (int i = 0; i < order; i++) {
		MatrixElement<T>* rows_a = A_horizontal[i].end;
		MatrixElement<T>* rows_b = B_horizontal[i].end;
		if (rows_a == nullptr && rows_b != nullptr) {
			push_sum(rows_b, result, i);
		}
		else {
			if (rows_a != nullptr && rows_b == nullptr) {
				push_sum(rows_a, result, i);
			}
			else {
				bool check_A = true;
				bool check_B = true;
				while (rows_a != nullptr && rows_b != nullptr) {
					if ((rows_a->j == rows_b->j) && (rows_a->data + rows_b->data != 0)) {
						result[i].add(rows_a->data + rows_b->data, rows_a->i, rows_b->j);
						rows_a = rows_a->prev;
						rows_b = rows_b->prev;
					}
					if (rows_a && rows_b && rows_a->j < rows_b->j) {
						result[i].add(rows_a->data, rows_a->i, rows_a->j);
						rows_a = rows_a->prev;
					}
					if (rows_a && rows_b && rows_a->j > rows_b->j) {
						result[i].add(rows_b->data, rows_b->i, rows_b->j);
						rows_b = rows_b->prev;
					}

					if (rows_a == nullptr) check_A = false;
					if (rows_b == nullptr) check_B = false;
				}

				if (!check_A)
					push_sum(rows_b, result, i);
				if (!check_B)
					push_sum(rows_a, result, i);
			}
		}
	}
}

template<typename T>
void get_vertical(Matrix<T> horizontal[order], Matrix<T>(&vertical)[order]) {
	for (int i = 0; i < order; i++) {
		MatrixElement<T>* element = horizontal[i].end;
		while (element) {
			vertical[element->j].add(element->data, element->i, element->j);
			element = element->prev;
		}
	}
}



template<typename T>
void multiplication(Matrix<T> A_horizontal[order], Matrix<T> B_horizontal[order], Matrix<T>(&result)[order]) {
	Matrix<T> B_vertical[order];
	get_vertical(B_horizontal, B_vertical);
	for (int i = 0; i < order; i++) {
		MatrixElement<T>* A_element = A_horizontal[i].end;
		for (int j = 0; j < order; j++) {
			MatrixElement<T>* A_element = A_horizontal[i].end;
			int counter = 0;
			int i_A, j_A;
			if (A_element) {
				i_A = A_element->i;
				j_A = A_element->j + j;
			}
			while (A_element) {
				MatrixElement<T>* B_element = B_vertical[j].end;
				while (B_element) {
					if (B_element->i == A_element->j) {
						counter += B_element->data * A_element->data;
						break;
					}
					B_element = B_element->prev;
				}
				A_element = A_element->prev;
			}

			if (counter) {
				result[i].add(counter, i_A, j_A);
			}
		}
	}

}


template<typename T>
void transponce(Matrix<T> horizontal[order], Matrix<T>(&result)[order]) {
	Matrix<T> vertical[order];
	get_vertical(horizontal, vertical);

	for (int i = 0; i < order; i++) {
		MatrixElement<T>* element = vertical[i].end;
		while (element) {
			result[i].add(element->data, element->j, element->i);
			element = element->prev;
		}
	}
}


template<typename T>
std::vector<T> multiplication_by_vector(const Matrix<T> horizontal[order], const std::vector<T>& vect) {
	std::vector<T> result;

	for (int i = 0; i < order; i++) {
		T intermidiate = 0;
		MatrixElement<T>* element = horizontal[i].end;
		for (int j = 0; j < order; j++) {
			if (element && element->j == j) {
				intermidiate += element->data * vect[j];
				element = element->prev;
			}

		}
		result.push_back(intermidiate);
	}

	return result;
}


template<typename T>
void print_matrix(Matrix<T>(&horizontal)[order]) {

	for (int i = 0; i < order; i++) {
		MatrixElement<T>* element = horizontal[i].end;
		if (element == nullptr) {
			for (int k = 0; k < order; k++) {
				std::cout << "0 ";
			}
		}
		int chek_column = -1;
		while (element != nullptr) {

			if (chek_column == -1 && element->j != 0) {
				for (int j = 0; j < element->j; j++) {
					std::cout << "0 ";
				}
			}
			else {
				for (int j = chek_column + 1; j < element->j; j++) {
					std::cout << "0 ";
				}
			}

			std::cout << element->data << ' ';
			chek_column = element->j;
			if (element->prev == nullptr) {
				for (int i = chek_column + 1; i < order; i++) {
					std::cout << "0 ";
				}
			}
			element = element->prev;
		}
		std::cout << std::endl;
	}

}

void fill_file(const char str[20]) {
	FILE* file;
	if (fopen_s(&file, str, "wb")) {
		perror("Error");
	}
	else {
		for (int i = 0; i < order; i++) {
			for (int j = 0; j < order; j++) {
				int element = rand() % 2;
				fwrite(&element, sizeof(element), 1, file);

			}
		}

	}
	fclose(file);
}


template<typename T>
void create_matrix(Matrix<T>(&horizontal)[order], const char name_file[20]) {
	FILE* file;
	if (fopen_s(&file, name_file, "r+b"))
		perror("Error!");
	else {
		for (int i = 0; i < order; i++) {
			for (int j = 0; j < order; j++) {
				int element;
				fread(&element, sizeof(int), 1, file);
				if (element) {
					horizontal[i].add(element, i, j);
				}
			}
		}
	}
	fclose(file);
}


template<typename T>
void main_search_by_index(Matrix<T> horizontal[order]) {
	int i, j;
	std::cout << "Enter indexes" << std::endl;
	std::cout << "i= " << std::endl;
	std::cin >> i;
	std::cout << "j= " << std::endl;
	std::cin >> j;
	MatrixElement<T>* element = search_by_index(horizontal, i, j);
	std::cout << element->data << std::endl;
}


template<typename T>
void main_search_by_value(Matrix<T> horizontal[order]) {
	std::cout << "Enter search value" << std::endl;
	double data;
	std::cin >> data;
	MatrixElement<T>* element = search_by_value(horizontal, data);
	std::cout << "Rows: " << element->i << std::endl;
	std::cout << "Column: " << element->j << std::endl;
}


template<typename T>
void main_all_search_by_value(Matrix<T> horizontal[order]) {
	std::cout << "Enter search value" << std::endl;
	double data;
	std::cin >> data;
	std::vector<MatrixElement<T>*> result;
	all_search_by_value(horizontal, result, data);
	for (MatrixElement<T>* element : result) {
		std::cout << "Rows: " << element->i << std::endl;
		std::cout << "Column: " << element->j << std::endl;
	}
	if (result.empty())
		std::cout << "There are no such elements in the matrix" << std::endl;

}

template<typename T>
void main_sum_matrix(Matrix<T> A_horizontal[order], Matrix<T> B_horizontal[order]) {
	Matrix<T> result[order];
	matrix_sum(A_horizontal, B_horizontal, result);
	std::cout << "Sum matrix A+B= " << std::endl;
	print_matrix(result);

}


template<typename T>

void main_multiplication(Matrix<T> A_horizontal[order], Matrix<T> B_horizontal[order]) {
	Matrix<T> result[order];
	multiplication(A_horizontal, B_horizontal, result);
	std::cout << "Multiplication A*B= " << std::endl;
	print_matrix(result);
}

template<typename T>
void  main_transponse(Matrix<T> A_horizontal[order]) {
	Matrix<T> result[order];
	transponce(A_horizontal, result);
	std::cout << "Transponce = " << std::endl;
	print_matrix(result);
}

template<typename T>
void main_multiplication_by_vector(Matrix<T> horizontal[order]) {
	std::vector<T> vect;
	std::cout << "Enter element of vector" << std::endl;
	for (int i = 0; i < order; i++) {
		int value;
		std::cin >> value;
		vect.push_back(value);
	}

	std::vector<T>result;
	result = multiplication_by_vector(horizontal, vect);

	for (const T temp : result) {
		std::cout << temp << std::endl;
	}

}

