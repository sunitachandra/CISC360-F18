
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>
#include <unistd.h>
#define trials 10
#define randRange 1000
#define loops 200000000
#define randMax 32767
#define numThreads 4
double variance(int* array);
int min(int* array);
int max(int* array);

double variance(int* array) {
	double var = 0.0;
	double avg = (double)loops/randRange;
	for(int i = 0; i<randRange; i++) {
		var += (double)((avg-array[i])*(avg-array[i]));
	}
	return var/randRange;
}

int leastCommonNumber(int* array) {
	int m = loops+1;
	int ind = -5;
	for(int i = 0; i<randRange; i++) {
		if(array[i] < m) {
			m = array[i];
			ind = i;
		}
	}
	return ind;
}

int mostCommonNumber(int* array) {
	int m = -1;
	int ind = -5;
	for(int i = 0; i<randRange; i++) {
		if(array[i] > m) {
			m = array[i];
			ind = i;
		}
	}
	return ind;
}

int min(int* array) {
	int m = loops+1;
	for(int i = 0; i<randRange; i++) {
		if(array[i] < m) {
			m = array[i];
		}
	}
	return m;
}

int max(int* array) {
	int m = -1;
	for(int i = 0; i<randRange; i++) {
		if(array[i] > m) {
			m = array[i];
		}
	}
	return m;
}

double weightOfFirstHalf(int* array) {
	int half = randRange/2;
	int firstSum = 0;
	int secondSum = 0;
	for(int i = 0; i<half; i++) {
		firstSum += array[i];
	}
	for(int i = half; i<randRange; i++) {
		secondSum += array[i];
	}
	return (double)firstSum/secondSum;
}

int main(int argc, const char* argv[]){
	srand(time(0));
	double avgVariance = 0.0;
	double avgTime = 0.0;
	double avgMin = 0.0;
	double avgMax = 0.0;
	double minVariance = 5000000000;
	double minTime = 5000000000;
	double minMin = 5000000000;
	double minMax = 5000000000;
	double maxVariance = 0.0;
	double maxTime = 0.0;
	double maxMin = 0.0;
	double maxMax = 0.0;
	double totalTimeElapsed = 0.0;
	printf("Welcome to the spectacular PRNG test! \nPresented by Phil, Marisa, Jeremy, and Paul\n");
	printf("Performing %d trials of %d loops at modulo %d\n", trials, loops, randRange);
	printf("Dramatic pause...\n");
	sleep(2);
	printf("BEGIN!!! \n\n");


	for(int t = 0; t<trials; t++){
		printf("Trial %d\n", t);
		double timeElasped = 0.0;
		int counts[randRange] = {0};
		clock_t begin = clock();
		#pragma omp parallel num_threads(numThreads)
		for(int i = 0; i<loops; i++) {
			counts[((rand() * (randMax-1)) + rand())%randRange] += 1;
		}
		clock_t end = clock();
		timeElasped += (double)(end-begin) / CLOCKS_PER_SEC;
		printf("\tTime elapsed: %.2fs\n", timeElasped);
		double var = variance(counts);
		printf("\tVariance: %.2f\n", var);
		int mini = min(counts);
		int maxi = max(counts);
		printf("\tMin: %d \n\tMax: %d\n", mini, maxi);
		printf("\tLeast Common: %d \n\tMost Common: %d \n", leastCommonNumber(counts), mostCommonNumber(counts));
		printf("\tRatio of first half to second half: %.5f \n", weightOfFirstHalf(counts));
		avgVariance += var/trials;
		if(var < minVariance) {
			minVariance = var;
		}
		if(var > maxVariance) {
			maxVariance = var;
		}		
		avgTime += timeElasped/trials;
		if(timeElasped < minTime) {
			minTime = timeElasped;
		}
		if(timeElasped > maxTime) {
			maxTime = timeElasped;
		}
		avgMax += maxi/trials;
		if(maxi < minMax) {
			minMax = maxi;
		}
		if(maxi > maxMax) {
			maxMax = maxi;
		}
		avgMin += mini/trials;
		if(mini < minMin) {
			minMin = mini;
		}
		if(mini > maxMin) {
			maxMin = mini;
		}		
		totalTimeElapsed += timeElasped;
	}
	printf("\n**************Trials Complete***************\n");
	printf("Performed %d trials of %d loops at modulo %d\n", trials, loops, randRange);
	printf("Average Variance: %.2f\n", avgVariance);
	printf("\tMin Variance: %.2f\n", minVariance);
	printf("\tMax Variance: %.2f\n", maxVariance);
	printf("Average Time: %.2f\n", avgTime);
	printf("\tMin Time: %.2f\n", minTime);
	printf("\tMax Time: %.2f\n", maxTime);
	printf("Average Max: %.2f\n", avgMax);
	printf("\tMin Max: %.2f\n", minMax);
	printf("\tMax Max: %.2f\n", maxMax);
	printf("Average Min: %.2f\n", avgMin);
	printf("\tMin Min: %.2f\n", minMin);
	printf("\tMax Min: %.2f\n", maxMin);




}