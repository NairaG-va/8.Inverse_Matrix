//Написать функцию, переводящую квадратную матрицу в обратную
#include <iostream>
#include <math.h>
#include <vector>

std::vector<std::vector<double>> function(int n, std::vector<std::vector<double>> matrix);
void mult_matrix(int n, std::vector<std::vector<double>>& matrix, std::vector<std::vector<double>>& inv_matrix);

int main(int argc, char* argv[])
{
	int n; //размерность матрицы
	
	try
		{
			n = std::stod(argv[1]);
   
		}
	catch(...)
		{
			std::cout << "Not able to parse arguments" << "\n";
			return 1;
		}
	
	std::vector<std::vector<double>> matrix;
	
	//заполняем исходную матрицу, т.е matrix
	for (int i = 0; i < n; i++)  
		{   
			std::vector<double> v;
			for (int j = 0; j < n; j++) 
			{
				v.push_back(rand()%20);
			}
			matrix.push_back(v);	
		}	
		
	//выводим исходную матрицу, т.е matrix
	std::cout << "Direct matrix:" << "\n";
	for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
				{
					std::cout << matrix[i][j] << "\t\t";
				}
			std::cout << "\n";	
		}
	std::cout << "\n";
	
	std::vector<std::vector<double>> inv_matrix = function(n, matrix);
	
	mult_matrix(n, matrix, inv_matrix);//осталось проверить, что произведение матрицы на обратную дает единичную
	
	return 0;
}

std::vector<std::vector<double>> function(int n, std::vector<std::vector<double>> matrix) //нахождение обратной матрицы
{
	std::vector<std::vector<double>> inv_matrix;
	
	for (int i = 0; i < n; i++)//делаем обратную матрицу изначально единичной
		{
			std::vector<double> v;
			for (int j = 0; j < n; j++)
				{
					v.push_back((i == j) ? 1 : 0); //т.е равно 1, если i == j, иначе равно 0
				}
			inv_matrix.push_back(v);

		}
		
		
	for (int k = 0; k < n; k++)//приводим матрицу к верхнетреугольной
		{
			for (int i = k + 1; i < n; i++)
				{
					double temp = matrix[i][k] / matrix[k][k];
					for (int j = 0; j < n; j++)
						{
							matrix[i][j] -= temp * matrix[k][j];
							inv_matrix[i][j] -= temp * inv_matrix[k][j];
						}
				}
		}
	
		
	for (int k = n - 1; k > 0; k--)//далее зануляем все, что выше главной диагонали
		{
			for (int i = k - 1; i >= 0; i--)
				{
					double temp = matrix[i][k] / matrix[k][k];
					for (int j = 0; j < n; j++)
						{
							matrix[i][j] -= temp * matrix[k][j];
							inv_matrix[i][j] -= temp * inv_matrix[k][j];
						}
				}
		}
		
		
	for (int i = 0; i < n; i++)//делим на элементы главной диагонали
		{
			for (int j = 0; j < n; j++)
				{
					inv_matrix[i][j] /= matrix[i][i];
				}
		}

//выводим обратную матрицу, т.е inv_matrix
	std::cout << "Inverse matrix:" << "\n";
	for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
				{
					std::cout << inv_matrix[i][j] << "\t\t";
				}
			std::cout << "\n";	
		}
		
	std::cout << "\n";	
		
return inv_matrix;
}

void mult_matrix(int n, std::vector<std::vector<double>>& matrix, std::vector<std::vector<double>>& inv_matrix)
{
	std::vector<std::vector<double>> multiplication;
	
	//заполняем нулями матрицу, отвечающую за произведение 
	for(int i = 0; i < n; i++) 
	{
		std::vector<double> v;
		for (int j = 0; j < n; j++) 
		{
			v.push_back(0.0);
		}
		multiplication.push_back(v);
	}
	
	
	
	for(int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			//multiplication[i][j] = 0;
			for (int k = 0; k < n; k++)
			{
				multiplication[i][j] += matrix[i][k] * inv_matrix[k][j];
			}
		}
	}
	
	
	//выводим произведение матриц, т.е multiplication
	std::cout << "Product of direct and inverse matrix:" << "\n";
	for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
				{
					std::cout << multiplication[i][j] << "\t\t";
				}
			std::cout << "\n";	
		}

}
