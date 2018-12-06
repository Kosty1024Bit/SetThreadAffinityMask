#include <iostream>
#include <sstream>
#include <ctime>
#include <windows.h>
using namespace std;

typedef unsigned int uint;

int main(int argc, const char *argv[]) {
	int HT = 3;
	if (argc <= 1) {
		if (argv[0]) argv[1] = "3";
	}

	stringstream convert(argv[1]);
	if (!(convert >> HT))
		HT = 3;

	srand(12);

	uint size = 1500;
	//uint size = 10;
	float **A = new float *[size];
	float **B = new float *[size];
	float **R = new float *[size];

	for (uint i = 0; i < size; i++) {
		A[i] = new float[size]; 
		B[i] = new float[size];
		R[i] = new float[size];
		for (uint j = 0; j < size; j++) {
			A[i][j] = 1.0f / float(rand() % RAND_MAX);
			B[i][j] = 1.0f / float(rand() % RAND_MAX);
			R[i][j] = 0.0f;
		}
	}

	if		(HT == 0) HT = 170; //bin 10101010, HT off
	else if (HT == 1) HT = 240; //bin 11001100, HT on
	else HT = 256; //all

#pragma omp parallel
	{
		DWORD_PTR threadAffinityMask = HT; 
		SetThreadAffinityMask(GetCurrentThread(), threadAffinityMask);
	}

	cout << "star" << endl;
	int start = clock();

#pragma omp parallel for
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			for (int k = 0; k < size; k++)
				R[i][j] += A[i][k] * B[k][j];
		}
	}
	int time = clock() - start;
	cout << "end, time = " << time << endl;
		
	cout << endl << "press any key to exit" << endl;
	//getchar();
	delete[] A;
	delete[] B;
	delete[] R;
	return 0;
}
