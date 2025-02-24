// ReverseArray.cpp : This program will take an input array, reverse its order, and output the new array.
//

#include <iostream>

using namespace std;


//The following function takes the input integers and size as parameters to reverse their order by use of the temporary variable
int* reversedArray(int arr[], int size);

//The following function will use the size variable to iterate through the array and print the integers in accordance with the reversedArray function's output
void print(int const arr[], int size);

int main()
{
	int size;
	cout << "How many integers are in your array?";
	cin >> size;

	int* arr = new int[size];

	cout << "Enter " << size << " integers:" << endl;
	for (int i = 0; i < size; i++) {
		cin >> arr[i];
	}


	int* revArr = reversedArray(arr, size);
	print(revArr, size);

	delete[] arr;

	return 0;


}

int* reversedArray(int arr[], int size) {
	for (int i = 0; i < size / 2; i++) {
		int temporary = arr[i];
		arr[i] = arr[size - 1 - i];
		arr[size - 1 - i] = temporary;
	}
	return arr;
}
void print(int const arr[], int size) {
	cout << "The reversed array integers are: " << endl;
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}

	cout << endl;
}