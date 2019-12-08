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
	unsigned char* data_ptr;//ָ��ͼ�������ָ��
	float* buffer, * buffer_I, * buffer_G;
	int height, width;

	CBitmapFile();
	~CBitmapFile();
	//���ܣ���ӡ��Bmp�ļ�������
	void print();
	//���ܣ�����ָ��·���µ�����.bmp�ļ�
	vector<string> search_dir(string path);
	//���ܣ�24λ.bmpͼ���ȡ
	bool readBitmap_3(string name);
	//���ܣ�24λ.bmpͼ�񴢴�
	bool saveBitmap_3(string name);
	//���ܣ���24λ��.bmpͼ��ת��Ϊ8λ��.bmpͼ��
	bool transformBitmap();
	//���ܣ�24λͼ��ת����32bit����һ�����أ�����MFC������ʾ
	bool expand_3();
	//���ܣ�8λ.bmpͼ���ȡ
	bool readBitmap(string name);
	//���ܣ�8λ.bmpͼ�񴢴�
	bool saveBitmap(string name);
	//���ܣ�8λͼ��ת����32bit����һ�����أ�����MFC������ʾ
	bool expand();
	//���ܣ�����ͷ�ļ���������������
	void copy(CBitmapFile& out);
	/*
	���ܣ��ڵ�ǰ��ͼ���ú�ɫ�����ע��outͼ���д���threshold�ĵ����ڵ�λ����
	���룺8λBMPͼ
	�������ע���24λBMPͼ
	*/
	void mark(CBitmapFile& out, int threshold);
	//���ܣ���ֵͷ�ļ���Ϊ��ǰ������������ռ䲢��ֵΪ0
	void similar(CBitmapFile& out);
	/*
	����:8λBMPͼ��
	���ܣ�����wͼ��RΪbatch�Ŀ�ȣ�eΪһ��С��������ֹ���ֳ���0����ʽ��dstΪĿ��ͼ��
	�����
	*/
	void Lh_lhm(int R, float e, CBitmapFile& dst);
	//�ֲ��ݶ�ǿ�ȷ�
	/*
	�ֲ��ݶ�ǿ�ȷ�
	����:8λBMPͼ��
	���ܣ�
	�����
	*/
	void Lig(int R, float k, CBitmapFile& dst);
	void Lig(int R, float k, CBitmapFile& dst, CBitmapFile& dst_I, CBitmapFile& dst_G);
	//��8λBMPͼ�����Ϊͼ���ļ�
	int YwkWrite8BitImg2BmpFile(CBitmapFile& dst,  const char* filename);
};
#endif
#pragma once
