#include<iostream>
#include<vector>
#include"DynamicArray.h"
#include"Random.h"

using namespace std;

bool isPrime(int n) {
	if (n <= 1)
		return false;
	for (int i = 2; i < n; ++i)
		if (n % i == 0)
			return false;
	return true;
}

int main() {
	DynamicArray<int> arr;
	DynamicArray<int> primes;
	Random rng;
	int n = rng.nextInt(5, 20);

	cout << n << " random numbers are:\n";
	for (int i = 0; i < n; ++i) {
		arr.push_back(rng.nextInt());
		cout << arr[i] << endl;
	}

	//find all prime numbers in arr
	for (int i = 0; i < n; ++i)
		if (isPrime(arr[i]))
			primes.push_back(arr[i]);

	//print primes vector
	if (primes.size() == 0)
		cout << "\nNo primes exist";
	else {
		cout << "\nprime numbers are:\n";
		for (int i = 0; i < primes.size(); ++i)
			cout << primes[i] << endl;
	}

	return 0;
}