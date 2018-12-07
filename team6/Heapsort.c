// C++ program for implementation of Heap Sort
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

// A utility function to swap two elements
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

// To heapify a subtree rooted with node i which is
// an index in arr[]. n is size of heap
void heapify(int arr[], int n, int i)
{
	int largest = i; // Initialize largest as root
	int l = 2*i + 1; // left = 2*i + 1
	int r = 2*i + 2; // right = 2*i + 2

	// If left child is larger than root
	if (l < n && arr[l] > arr[largest])
		largest = l;

	// If right child is larger than largest so far
	if (r < n && arr[r] > arr[largest])
		largest = r;

	// If largest is not root
	if (largest != i)
	{
		swap(&arr[i], &arr[largest]);

		// Recursively heapify the affected sub-tree
		heapify(arr, n, largest);
	}
}

// main function to do heap sort
void heapSort(int arr[], int n)
{
	// Build heap (rearrange array)
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	// One by one extract an element from heap
	for (int i=n-1; i>=0; i--)
	{
		// Move current root to end
		swap(&arr[0], &arr[i]);

		// call max heapify on the reduced heap
		heapify(arr, i, 0);
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

// Driver program
int main()
{
  printf("*****BEGINNING HEAPSORT TEST*****\n\n");

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
		heapSort(arr, n);
		clock_t end = clock();

    printf("Starting Ticks: %f\n", (double) start);
		printf("Ending Ticks: %f\n", (double) end);
		double totalTime = (double) (end - start) / CLOCKS_PER_SEC;
    // printf("SORTED Array #%d: ", i);
    // printIntArray(arr, N);
		printf("Array Sorted!\n");
		printf("Sort took: %f seconds\n\n", totalTime);
		times[i] = totalTime;
  }

	printf("Sort Timings: \n");
	printArray(times, TESTS);
  avg(times);
	return 0;
}
