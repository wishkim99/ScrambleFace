#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

void decodingFace(unsigned int key)
{
#define MAX_X 256
#define MAX_Y 256

	char sourceData[MAX_X * MAX_Y];
	char tempData[74 * 78];			// 얼굴부분만 임시로 저장할 배열 (얼굴영역의 좌표는 84,90 에서 157,167 까지로 간주함)
	char ch;

	int i, j;

	ifstream in("girl_scrambled.gray", ios::in | ios::binary);
	ofstream out("girl_descrambled.gray", ios::out | ios::binary);

	for (i = 0; i < MAX_Y; i++) {
		for (j = 0; j < MAX_X; j++) {
			in.get(ch);
			sourceData[(i * MAX_X) + j] = ch;
		}
	}

	// 스크럼블된 얼굴영역만 tempData 배열에 넣음
	int k = 0;
	for (i = 90; i <= 167; i++) {
		for (j = 84; j <= 157; j++) {
			tempData[k++] = sourceData[(i * MAX_X) + j];
		}
	}

	// key 값에 따라 동일한 random 값이 나오도록 srand 실행
	srand(key);

	// 스크럼블할 당시의 radndom 값을 임시저장
	int randArray[74 * 78];
	for (i = 0; i < 74 * 78; i++)
	{
		randArray[i] = (rand() % (74 * 78));
	}

	// 스크럼블된 데이터를 역순으로 실행하여 데이터 원복
	for (i = (74 * 78) - 1; i >= 0; i--)
	{
		char temp = tempData[randArray[i]];
		tempData[randArray[i]] = tempData[i];
		tempData[i] = temp;
	}

	// 원복된 얼굴부분 데이터를 원본데이터의 얼굴부분에 넣음
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