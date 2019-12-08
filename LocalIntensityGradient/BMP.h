#ifndef _BITMAPFILE_
#define _BITMAPFILE_
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<Windows.h>
#include <vector>
#include <io.h>
#include <time.h>
#include <fstream>
using namespace std;

typedef unsigned char uchar;
#define PI 3.1415926
class CBitmapFile
{
public:
	struct tagBITMAPFILEHEADER file_header;
	struct tagBITMAPINFOHEADER info_header;
	unsigned char* data_ptr;//指向图像数组的指针
	float* buffer, * buffer_I, * buffer_G;
	int height, width;

	CBitmapFile();
	~CBitmapFile();
	//功能：打印出Bmp文件的数据
	void print();
	//功能：搜索指定路径下的所有.bmp文件
	vector<string> search_dir(string path);
	//功能：24位.bmp图像读取
	bool readBitmap_3(string name);
	//功能：24位.bmp图像储存
	bool saveBitmap_3(string name);
	//功能：将24位的.bmp图像转化为8位的.bmp图像
	bool transformBitmap();
	//功能：24位图像转化成32bit描述一个像素，便于MFC程序显示
	bool expand_3();
	//功能：8位.bmp图像读取
	bool readBitmap(string name);
	//功能：8位.bmp图像储存
	bool saveBitmap(string name);
	//功能：8位图像转化成32bit描述一个像素，便于MFC程序显示
	bool expand();
	//功能：复制头文件，拷贝数据数组
	void copy(CBitmapFile& out);
	/*
	功能：在当前的图上用红色方框标注出out图像中大于threshold的点所在的位置上
	输入：8位BMP图
	输出：标注后的24位BMP图
	*/
	void mark(CBitmapFile& out, int threshold);
	//功能：赋值头文件，为当前数据数组申请空间并赋值为0
	void similar(CBitmapFile& out);
	/*
	输入:8位BMP图，
	功能：计算w图，R为batch的宽度，e为一个小的数，防止出现除以0的算式，dst为目标图像
	输出：
	*/
	void Lh_lhm(int R, float e, CBitmapFile& dst);
	//局部梯度强度法
	/*
	局部梯度强度法
	输入:8位BMP图，
	功能：
	输出：
	*/
	void Lig(int R, float k, CBitmapFile& dst);
	void Lig(int R, float k, CBitmapFile& dst, CBitmapFile& dst_I, CBitmapFile& dst_G);
	//将8位BMP图像输出为图像文件
	int YwkWrite8BitImg2BmpFile(CBitmapFile& dst,  const char* filename);
};
#endif
#pragma once
