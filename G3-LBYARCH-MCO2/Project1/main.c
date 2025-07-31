//Group 3
// Names: Corpuz, Hannah and Chang, Alwyn
// Section S13A
// Template C to x86 call
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <time.h>

extern float asmKernel(float X1, float Y1, float X2, float Y2);

float cKernel(float X1, float Y1, float X2, float Y2) {

	return (float) sqrt( ((X2-X1)*(X2 - X1)) + ((Y2 - Y1)*(Y2 - Y1)) ); //returns distance of points in Vector 1 and 2
}

int main() {
	srand(time(NULL));
	ULONGLONG startC = 0, endC = 0, startASM = 0, endASM = 0;
	ULONGLONG timeElapsedC = 0, timeElapsedASM = 0;
	
	ULONGLONG avgC = 0, avgASM = 0, maxC = 0, minC = 0, maxASM = 0, minASM = 0;

	int n = 0, choice = 0, choice2 = 0, test = 0;
	float buffer = 0;

	printf("This Program outputs the distances of points between Vector 1 and Vector 2.\n\n");
	
	do {
		printf("Use random vector points or Input numbers yourself?\n[1] -		Input Numbers\n[2] -		Random Numbers: ");
		scanf_s("%d", &choice);
	} while (choice < 1 || choice > 2);

	
	

	printf("Enter size of for vectors 1 and 2: ");
	scanf_s("%d", &n);
	if (n <= 0) {
		printf("Invalid Size...\n\n");
		return 1;
	}
	
	float* X1 = (float *)malloc(n * sizeof(float));
	float* Y1 = (float *)malloc(n * sizeof(float));
	
	float* X2 = (float *)malloc(n * sizeof(float));
	float* Y2 = (float *)malloc(n * sizeof(float));

	float* cZ = (float*)malloc(n * sizeof(float));
	float* asmZ = (float*)malloc(n * sizeof(float));

	float zBuffer = 0;

	if (choice == 1) {
		printf("Enter Vector 1 and 2 points: \n\n");
		for (int i = 0; i < n; i++) {
			printf("[%d]: Vector 1 -	", i + 1);

			printf("X: ");
			scanf_s("%f", &buffer);
			X1[i] = buffer;


			printf("		Y: ");
			scanf_s("%f", &buffer);
			Y1[i] = buffer;

			printf("[%d]: Vector 2 - ", i + 1);
			printf("X: ");
			scanf_s("%f", &buffer);
			X2[i] = buffer;


			printf("		Y: ");
			scanf_s("%f", &buffer);
			Y2[i] = buffer;
		}
	}
	else if (choice == 2) {
		
		for (int i = 0; i < n; i++) {
			
			
			X1[i] = (float)rand() / RAND_MAX * 100.0f;
			
			Y1[i] = (float)rand() / RAND_MAX * 100.0f;

			X2[i] = (float)rand() / RAND_MAX * 100.0f;

			Y2[i] = (float)rand() / RAND_MAX * 100.0f;
		}
	}


	
	for (int i = 0; i < 30; i++) {
		
		
		startC = GetTickCount64();

		for (int i = 0; i < n; i++) {
			zBuffer = cKernel(X1[i], Y1[i], X2[i], Y2[i]);
			cZ[i] = zBuffer;
		}

		endC = GetTickCount64();

		timeElapsedC = endC - startC;

		avgC += timeElapsedC;
		
	}

	for (int i = 0; i < 30; i++) {
		startASM = GetTickCount64();

		for (int i = 0; i < n; i++) {
			zBuffer = asmKernel(X1[i], Y1[i], X2[i], Y2[i]);
			asmZ[i] = zBuffer;
		}

		endASM = GetTickCount64();

		timeElapsedASM = endASM - startASM;
	
		avgASM += timeElapsedASM;
		
		
	}

	if (n >= 10) {
		printf("\nFirst 10 elements of Z from C kernel: \n");
		for (int i = 0; i < 10; i++)
			printf("%.9f, ", cZ[i]);

		printf("\n\nFirst 10 Elements of Z from ASM kernel: \n");
		for (int i = 0; i < 10; i++)
			printf("%.9f, ", asmZ[i]);
	}
	else
	{
		printf("\nElements of Z from C kernel: \n");
		for (int i = 0; i < n; i++)
			printf("%.9f, ", cZ[i]);

		printf("\n\nElements of Z from ASM kernel: \n");
		for (int i = 0; i < n; i++)
			printf("%.9f, ", asmZ[i]);
	}



	printf("\n\nAvg time from C kernel after 30 tries in ms: %llu\n", avgC/30);
	
	printf("\n\nAvg time from ASM kernel after 30 tries in ms: %llu\n", avgASM/30);


	free(X1);
	free(X2);
	free(Y1);
	free(Y2);

	X1 = NULL;
	X2 = NULL;
	Y1 = NULL;
	Y2 = NULL;


	return 0;
}
 