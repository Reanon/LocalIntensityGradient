#ifndef _LIG1_
#define _LIG1_
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<Windows.h>
#include <vector>
#include <io.h>
#include <time.h>
#include <fstream>
typedef unsigned char uchar;
#define PI 3.1415926

void Lig1(BYTE* img,       //input image
	float* IG_buffer,
	int width,
	int height,
	int R,           //length of every patch
	float k,          // Gmin��Gmax֮�ȵ���ֵ
	BYTE* IG_map,
	BYTE* I_map,
	BYTE* G_map
);      //output image
//�ɵ���Ŀ���С

#endif
#pragma once
