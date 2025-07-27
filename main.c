// Template C to x86 call
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <time.h>

extern float asmhello(float vectorX1, float vectorY1, float vectorX2, float vectorY2);

float cKernel(float vectorX1, float vectorY1, float vectorX2, float vectorY2) {

	return sqrt( pow((vectorX2-vectorX1), 2.0) + pow((vectorY2 - vectorY1), 2.0) ); //returns distance of points in Vector 1 and 2
}

int main() {
	srand(time(0));
	ULONGLONG startC = 0, endC = 0, startASM = 0, endASM = 0;
	ULONGLONG timeElapsedC = 0, timeElapsedASM = 0;
	
	ULONGLONG avgC = 0, avgASM = 0, maxC = 0, minC = 0, maxASM = 0, minASM = 0;

	int n = 0, choice = 0;
	float buffer = 0;

	printf("This Program outputs the distances of points between Vector 1 and Vector 2.\n\n");
	
	do {
		printf("Use random vector points or Input numbers yourself?\n[1] -		Input Numbers\n[2] -		Random Numbers (also checks program speed): ");
		scanf_s("%d", &choice);
	} while (choice < 1 || choice > 2);

	
	printf("Enter size of for vectors 1 and 2: ");
	scanf_s("%d", &n);
	if (n <= 0) {
		printf("Invalid Size...\n\n");
		return 1;
	}

	float* vectorX1 = (float *)malloc(n * sizeof(float));
	float* vectorY1 = (float *)malloc(n * sizeof(float));

	float* vectorX2 = (float *)malloc(n * sizeof(float));
	float* vectorY2 = (float *)malloc(n * sizeof(float));

	float zBuffer = 0;
	if (choice == 1) {
		printf("Enter Vector 1 and 2 points: ");
		for (int i = 0; i < n; i++) {
			printf("\n[%d] X1: ", i + 1);
			scanf_s("%f", &buffer);
			vectorX1[i] = buffer;


			printf("\n[%d] Y1: ", i + 1);
			scanf_s("%f", &buffer);
			vectorY1[i] = buffer;

			printf("\n[%d] X2: ", i + 1);
			scanf_s("%f", &buffer);
			vectorX2[i] = buffer;


			printf("\n[%d] Y2: ", i + 1);
			scanf_s("%f", &buffer);
			vectorY2[i] = buffer;
		}
	}
	else if (choice == 2) {
		
		for (int i = 0; i < n; i++) {
			
			
			vectorX1[i] = (float)rand() / RAND_MAX * 100.0f;
			
			vectorY1[i] = (float)rand() / RAND_MAX * 100.0f;

			vectorX2[i] = (float)rand() / RAND_MAX * 100.0f;

			vectorY2[i] = (float)rand() / RAND_MAX * 100.0f;
		}
	}


	
	for (int i = 0; i < 30; i++) {
		printf("\nZ from C kernel: \n");
		
		startC = GetTickCount64();

		for (int i = 0; i < n; i++) {
			zBuffer = cKernel(vectorX1[i], vectorY1[i], vectorX2[i], vectorY2[i]);
			printf("%.2f, ", zBuffer);
		}

		endC = GetTickCount64();

		timeElapsedC = endC - startC;

		avgC += timeElapsedC / 30;

		if (i == 0) {
			maxC == timeElapsedC;
			minC == timeElapsedC;
		}
		else {
			if (maxC < minC) {
				buffer = minC;
				minC = maxC;
				maxC = buffer;
			}
			else
				maxC = timeElapsedC;
		}
	}

	

	
	printf("\n\nZ from ASM kernel: \n");

	for (int i = 0; i < 30; i++) {
		startASM = GetTickCount64();

		for (int i = 0; i < n; i++) {
			zBuffer = asmhello(vectorX1[i], vectorY1[i], vectorX2[i], vectorY2[i]);
			printf("%.2f, ", zBuffer);
		}

		endASM = GetTickCount64();

		timeElapsedASM = endASM - startASM;
	
		avgASM += timeElapsedASM / 30;

		if (i == 0) {
			maxASM == timeElapsedASM;
			minASM == timeElapsedASM;
		}
		else {
			if (maxASM < minASM) {
				buffer = minASM;
				minASM = maxASM;
				maxASM = buffer;
			}
			else
				maxASM = timeElapsedASM;
		}

	}





	printf("\n\nAvg time from C kernel in ms: %llu\n", avgC);
	printf("\nMax time from C kernel in ms: %llu\n", maxC);
	printf("\nMin time from C kernel in ms: %llu\n", minC);
	
	printf("\n\nAvg time from ASM kernel in ms: %llu\n", avgASM);
	printf("\nMax time from ASM kernel in ms: %llu\n", maxASM);
	printf("\nMin time from ASM kernel in ms: %llu\n", minASM);

	free(vectorX1);
	free(vectorX2);
	free(vectorY1);
	free(vectorY2);

	vectorX1 = NULL;
	vectorX2 = NULL;
	vectorY1 = NULL;
	vectorY2 = NULL;


	return 0;
}
 