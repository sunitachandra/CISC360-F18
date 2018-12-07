/* C program for Merge Sort */
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

//Global Variables for testing
const int TESTS = 10; //Number of tests to run
const int N = 50000; //Length of Array(s) to sort

//Function to build Array of size elements
void buildArray(int *arr, int size)
{
	srand(0);
	for(int i = 0; i < size; i++)
	{
		arr[i] = rand() % 10;
	}
}

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp arrays */
	int L[n1], R[n2];

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1+ j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray
	j = 0; // Initial index of second subarray
	k = l; // Initial index of merged subarray
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there
	are any */
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
	are any */
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}

/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
	if (l < r)
	{
		// Same as (l+r)/2, but avoids overflow for
		// large l and h
		int m = l+(r-l)/2;

		// Sort first and second halves
		mergeSort(arr, l, m);
		mergeSort(arr, m+1, r);

		merge(arr, l, m, r);
	}
}

/* Function to average the timings data */
void avg(double times[])
{
  double sum = 0;
  for(int i = 0; i < TESTS; i++)
  {
    sum += times[i];
  }
  printf("Average Time: %f\n", sum / TESTS);
}

/* Function to print the arrays */
void printArray(double arr[], int size)
{
	int i;
	for (i=0; i < size; i++)
		printf("%f ", arr[i]);
	printf("\n");
}

// void printIntArray(int arr[], int size)
// {
// 	int i;
// 	for (i=0; i < size; i++)
// 		printf("%d ", arr[i]);
// 	printf("\n");
// }

/* Driver program to test above functions */
int main()
{
	printf("*****BEGINNING MERGESORT TEST*****\n\n");

	double times[TESTS];
	printf("Testing Array Complete!\nSorting...\n");

	for(int i = 0; i < TESTS; i++)
	{
		int arr[N];
		buildArray(arr, N);
		// printf("Array #%d: ", i);
    // printIntArray(arr, N);
		printf("Array #%d Complete!\nSorting...\n", i);

		int n = sizeof(arr)/sizeof(arr[0]);
		clock_t start = clock();
		printf("Starting Ticks: %f\n", (double) start);

		mergeSort(arr, 0, n - 1);
		clock_t end = clock();
		printf("Ending Ticks: %f\n", (double) end);

		double totalTime = (double) (end - start) / CLOCKS_PER_SEC;
		// printf("SORTED Array #%d: ", i);
    // printIntArray(arr, N);
		printf("Array Sorted!\n");
		printf("Sort took: %f seconds\n\n", totalTime);
		times[i] = totalTime;
  }

	printf("Sort Timings: ");
	printArray(times, TESTS);
	avg(times);
	return 0;
}
