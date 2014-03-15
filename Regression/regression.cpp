#include<iostream>
#include<cstdlib>
#include<math.h>
using namespace std;

int main()
{
	int c;
	int degree;
	int sum = 0;

	cout<<"Enter the number of the coordinates  x and y ..."<<endl;
	cin>>c;

	double x[c];
	double y[c];

	cout<<"Enter the coordinates now.."<<endl;
	for(int i=0; i<c; i++)
	{
		cout<<"x["<<i<<"] = "; cin>>x[i];
		cout<<"y["<<i<<"] = "; cin>>y[i];
	}

	cout<<"enter the degree of your Equation.."<<endl;
	cin>>degree;

	double matrix[degree+1][degree+2];

	//filling the matrix..
	for(int i=0; i<degree+1; i++)
	{
		for(int j=0; j<degree+1; j++)
		{
			sum = 0;
			for(int k=0; k<c; k++)
				sum += pow(x[k], i+j);
			matrix[i][j] = sum;
		}
	}

	for(int i=0; i<degree+1; i++)
	{
		sum = 0;
		for(int j=0; j<c; j++)
			sum += pow(x[j],i)*y[j];
		matrix[i][degree+1] = sum;
	}

	// initial matrix
	cout<<endl<<endl;
	for(int i=0; i<degree+1;i++)
	{
		for(int j=0; j<degree+2; j++)
			cout<< matrix[i][j]<<"  ";
			cout<<endl;
	}

	double p1;

	// GAUSE JORDAN method

	//for lower traingle
	for(int i=0; i<degree+1; i++)
	{
		p1 = matrix[i][i];
		for(int j=0; j<degree+2; j++)
			matrix[i][j] = matrix[i][j]/ p1;

		for(int j=i+1; j<degree+1; j++)
		{
			p1 = matrix[j][i];
			for(int k=0; k<degree+2; k++)
				matrix[j][k] = matrix[j][k] - (matrix[i][k]*p1);
		}
	}

	// after lower triangle elimination
	cout<<endl<<endl;
	for(int i=0; i<degree+1;i++)
	{
		for(int j=0; j<degree+2; j++)
			cout<< matrix[i][j]<<"  ";
			cout<<endl;
	}

	//for upper traingle
	for(int i=degree; i>=0; i--)
	{
		for(int j=0; j<i; j++)
		{
			p1 = matrix[j][i];
			for(int k=0; k<degree+2; k++)
				matrix[j][k] = matrix[j][k] - matrix[i][k]*p1;
		}
	}

	// display matrix
	cout<<"_______________________________________________________"<<endl;
	for(int i=0; i<degree+1;i++)
	{
		for(int j=0; j<degree+2; j++)
			cout<< matrix[i][j]<<"  ";
			cout<<endl;
	}
	return 0;
}

