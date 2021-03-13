#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

void encodingFace(unsigned int key)
{
#define MAX_X 256
#define MAX_Y 256

	char sourceData[MAX_X * MAX_Y];
	char tempData[74 * 78];			// 얼굴부분만 임시로 저장할 배열 (얼굴영역의 좌표는 84,90 에서 157,167 까지로 간주함)
	
	char ch;

	int i, j;

	ifstream in("GIRL.gray", ios::in | ios::binary);
	ofstream out("girl_scrambled.gray", ios::out | ios::binary);

	for (i = 0; i < MAX_Y; i++) {
		for (j = 0; j < MAX_X; j++) {
			in.get(ch);
			sourceData[(i * MAX_X) + j] = ch;
		}
	}
	

	// 스크럼블할 얼굴영역만 tempData 배열에 넣음
	int k = 0;
	for (i = 90; i <= 167; i++) {
		for (j = 84; j <= 157; j++) {
			tempData[k++] = sourceData[(i * MAX_X) + j];
		}
	}

	// key 값에 따라 동일한 random 값이 나오도록 srand 실행
	srand(key);

	// 랜덤하게 얼굴부분의 데이터를 스크럼블 함.
	for (i = 0; i < 74 * 78; i++) {
		int random = (rand() % (74 * 78));

		char temp = tempData[random];
		tempData[random] = tempData[i];
		tempData[i] = temp;
	}

	// 랜덤하게 스크럼블된 부분을 원본데이터의 얼굴부분에 넣음
	k = 0;
	for (i = 90; i <= 167; i++) {
		for (j = 84; j <= 157; j++) {
			sourceData[(i * MAX_X) + j] = tempData[k++];
		}
	}

	for (i = 0; i < MAX_Y; i++) {
		for (j = 0; j < MAX_X; j++) {
			out.put(sourceData[(i * MAX_X) + j]);
		}
	}

	// 사용한 파일 닫기
	in.close();
	out.close();
}