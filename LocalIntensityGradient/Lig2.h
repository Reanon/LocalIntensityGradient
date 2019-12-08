#ifndef _LIG2_
#define _LIG2_
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<Windows.h>
#include <vector>
#include <io.h>
#include <time.h>
#include <fstream>
typedef unsigned char uchar;
#define PI 3.1415926
void Lig2(BYTE* img,       //input
	float* IG_buffer,
	int width,
	int height,
	int T,           //目标大小
	float k,          // Gmin与Gmax之比的阈值
	BYTE* IG_map,
	BYTE* I_map,
	BYTE* G_map
);      //output image

#endif
#pragma once