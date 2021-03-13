#include "stdafx.h"
#include <cstdlib>
#include <ctime>

using namespace std;

void encodingFace(unsigned int key);
void decodingFace(unsigned int key);

int main()
{
	unsigned int key = time(NULL);

	// encoding
	encodingFace(key);

	// decoding
	decodingFace(key);

	return 0;
}

