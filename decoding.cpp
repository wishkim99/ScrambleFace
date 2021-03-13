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
	char tempData[74 * 78];			// �󱼺κи� �ӽ÷� ������ �迭 (�󱼿����� ��ǥ�� 84,90 ���� 157,167 ������ ������)
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

	// ��ũ����� �󱼿����� tempData �迭�� ����
	int k = 0;
	for (i = 90; i <= 167; i++) {
		for (j = 84; j <= 157; j++) {
			tempData[k++] = sourceData[(i * MAX_X) + j];
		}
	}

	// key ���� ���� ������ random ���� �������� srand ����
	srand(key);

	// ��ũ������ ����� radndom ���� �ӽ�����
	int randArray[74 * 78];
	for (i = 0; i < 74 * 78; i++)
	{
		randArray[i] = (rand() % (74 * 78));
	}

	// ��ũ����� �����͸� �������� �����Ͽ� ������ ����
	for (i = (74 * 78) - 1; i >= 0; i--)
	{
		char temp = tempData[randArray[i]];
		tempData[randArray[i]] = tempData[i];
		tempData[i] = temp;
	}

	// ������ �󱼺κ� �����͸� ������������ �󱼺κп� ����
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

	// ����� ���� �ݱ�
	in.close();
	out.close();
}