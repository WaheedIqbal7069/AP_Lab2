#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

#define MAX 50
#define MIN 1

int Rows = 4, Column = 4;    // declaration of Rows and columns   i.e:2^n, here 2^2=4
using namespace std;

vector<vector<int>> Regular_Multiplication(vector<vector<int>> A, vector<vector<int>> B)
{
	int Rows, Column, Dimension;
	
		Rows = A.size();
		Column = A[0].size();
	    Dimension = B[0].size();

	vector<vector<int>> ans;
	ans.resize(Rows, vector<int>(Dimension, 0));
	for (int i = 0; i < Rows; i++)
	for (int j = 0; j < Dimension; j++) 
	{
		int SUM_strass = 0;
		for (int k = 0; k < Column; k++)
			SUM_strass = SUM_strass + (A[i][k] * B[k][j]);
		ans[i][j] = SUM_strass;
	}
	return ans;
}

vector<vector<int>> SUM_strass(vector<vector<int>> A, vector<vector<int>> B) 
{
    int n = A.size();
	vector<vector<int>> Result;
	Result.resize(n, vector<int>(n, 0));
	int i, j;

	for (i = 0; i < n; i++) 
	{
		for (j = 0; j < n; j++) 
		{
			Result[i][j] = A[i][j] + B[i][j];
		}
	}
	return Result;
}

vector<vector<int>> SUB_strass(vector<vector<int>> A, vector<vector<int>> B) 
{
	int n = A.size();
	vector<vector<int>> Result;
	Result.resize(n, vector<int>(n, 0));
	int i, j;

	for (i = 0; i < n; i++) 
	{
		for (j = 0; j < n; j++) 
		{
			Result[i][j] = A[i][j] - B[i][j];
		}
	}
	return Result;
}

vector<vector<int>> Strassen(vector<vector<int>> A, vector<vector<int>> B) 
{
	int i, j;
	int n = A.size();

	vector<vector<int>> ans;
	ans.resize(n, vector<int>(n, 0));

	if (n == 1) 
	{
		ans[0][0] = A[0][0] * B[0][0];
		return ans;
	}
	else {
		vector<vector<int>> a11, a12, a21, a22;
		vector<vector<int>> b11, b12, b21, b22;
		vector<vector<int>> c11, c12, c21, c22;
		vector<vector<int>> p1, p2, p3, p4, p5, p6, p7;

		a11.resize(n / 2, vector<int>(n / 2, 0));
		a12.resize(n / 2, vector<int>(n / 2, 0));
		a21.resize(n / 2, vector<int>(n / 2, 0));
		a22.resize(n / 2, vector<int>(n / 2, 0));

		b11.resize(n / 2, vector<int>(n / 2, 0));
		b12.resize(n / 2, vector<int>(n / 2, 0));
		b21.resize(n / 2, vector<int>(n / 2, 0));
		b22.resize(n / 2, vector<int>(n / 2, 0));

		c11.resize(n / 2, vector<int>(n / 2, 0));
		c12.resize(n / 2, vector<int>(n / 2, 0));
		c21.resize(n / 2, vector<int>(n / 2, 0));
		c22.resize(n / 2, vector<int>(n / 2, 0));

		p1.resize(n / 2, vector<int>(n / 2, 0));
		p2.resize(n / 2, vector<int>(n / 2, 0));
		p3.resize(n / 2, vector<int>(n / 2, 0));
		p4.resize(n / 2, vector<int>(n / 2, 0));
		p5.resize(n / 2, vector<int>(n / 2, 0));
		p6.resize(n / 2, vector<int>(n / 2, 0));
		p7.resize(n / 2, vector<int>(n / 2, 0));

		vector<vector<int>> aResult;
		vector<vector<int>> bResult;
		aResult.resize(n / 2, vector<int>(n / 2, 0));
		bResult.resize(n / 2, vector<int>(n / 2, 0));


		

		//division of matrices in 4 SUB_strass-matrices:
		for (i = 0; i < n / 2; i++) 
		{
				for (j = 0; j < n / 2; j++) 
				{
				a11[i][j] = A[i][j];
				a12[i][j] = A[i][j + n / 2];
				a21[i][j] = A[i + n / 2][j];
				a22[i][j] = A[i + n / 2][j + n / 2];

				b11[i][j] = B[i][j];
				b12[i][j] = B[i][j + n / 2];
				b21[i][j] = B[i + n / 2][j];
				b22[i][j] = B[i + n / 2][j + n / 2];
				}
		}

		aResult = SUM_strass(a11, a22); 
		bResult = SUM_strass(b11, b22);
		p1 = Strassen(aResult, bResult); 

		aResult = SUM_strass(a21, a22); 
		p2 = Strassen(aResult, b11); 

		bResult = SUB_strass(b12, b22); 
		p3 = Strassen(a11, bResult); 

		bResult = SUB_strass(b21, b11); 
		p4 = Strassen(a22, bResult); 

		aResult = SUM_strass(a11, a12); 
		p5 = Strassen(aResult, b22); 	

		aResult = SUB_strass(a21, a11); 
		bResult = SUM_strass(b11, b12); 
		p6 = Strassen(aResult, bResult); 

		aResult = SUB_strass(a12, a22); 
		bResult = SUM_strass(b21, b22); 
		p7 = Strassen(aResult, bResult); 

		// calculating c21, c21, c11 e c22:

		c12 = SUM_strass(p3, p5); 
		c21 = SUM_strass(p2, p4); 

		aResult = SUM_strass(p1, p4); 
		bResult = SUM_strass(aResult, p7); 
		c11 = SUB_strass(bResult, p5); 

		aResult = SUM_strass(p1, p3); 
		bResult = SUM_strass(aResult, p6); 
		c22 = SUB_strass(bResult, p2); 

		
	    for (i = 0; i < n / 2; i++) 
		{
			for (j = 0; j < n / 2; j++) 
			{
				ans[i][j] = c11[i][j];
				ans[i][j + n / 2] = c12[i][j];
				ans[i + n / 2][j] = c21[i][j];
				ans[i + n / 2][j + n / 2] = c22[i][j];
			}
		}
	}
	return ans;
}

void print(vector<vector<int>> ans)
{
	int Rows = ans.size();
	int Column = ans[0].size();
	cout << "\n";
	for (int i = 0; i < Rows; i++)
	{
		cout << "[";
		for (int j = 0; j < Column; j++)
		{
			if (j == Column - 1)
				cout << ans[i][j];
			else
				cout << ans[i][j] << " ";
		}
		cout << "]\n";
	}
	cout << "\n";
}

int Random_NUM()  // generating random numbers
{
	srand(time(NULL));
	int Random_NUM = (rand() % ((MAX - MIN) + 1)) + MIN;
	return Random_NUM;
}

int main()
{
	vector<vector<int>> A;
	vector<vector<int>> B;

	A.resize(Rows, vector<int>(Column, 0));
	B.resize(Rows, vector<int>(Column, 0));

	for (int i = 0; i < Rows; i++) 
	{
		for (int j = 0; j < Column; j++) 
		{
			A[i][j] = Random_NUM();
			B[i][j] = Random_NUM();
		}
	}

	cout << "By Regular Matrix Multiplication:\n";
	print(Regular_Multiplication(A, B));

	cout << "By Strassen Method:\n";
	print(Strassen(A, B));
	system("Pause");
}
