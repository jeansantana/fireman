#ifndef BITLIB_H
#define BITLIB_H

#include <vector>

/* It returns true if bit on position i of 
 * number n is 1, false otherwise
 */
bool bitOn(int n, int i) {
	
	int value = (int) n & (1 << i);

	return value != 0 ? true : false;
}

/*
 * It returns the value with positions i setted to 1
 */
int setBitTo1(int n, int i) {
	return (int) n | (1 << i);
}

/*
 * It returns the value with positions i setted to 0
 */
int setBitTo0(int n, int i) {
	return (int) n ^ (1 << i);
}
/*
 * Exchange bit i, from 0 to 1, if n[i] = 0, from 1 to 0, otherwise
 */
int flipBit(int n, int i) {
	int newN;
	if (bitOn(n, i)) {
		newN = setBitTo0(n, i);
	} else {
		newN = setBitTo1(n, i);
	}
	return newN;
}

/*
 * It return bits on list, a sorted list (0 1 2 3 4 5 6 ... nDoors-1)
 */
std::vector<int> getBitsOn(int n, int nDoors) {
	std::vector<int> bitsOn;
	for (int i = 0; i < nDoors; ++i) {
		if (bitOn(n, i)) {
			bitsOn.push_back(i);
		}
	}

	return bitsOn;
}

#endif // BITLIB_H