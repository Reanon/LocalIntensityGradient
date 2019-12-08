#define _CRT_SECURE_NO_WARNINGS
#include"BMP.h"
#include"Lig2.h"
#include"Lig1.h"
#include"BMP1.h"
#include<iostream>
using namespace std;
int main()
{
	CBitmapFile c_bitmap;
	float* buffer;//����
	buffer = new float[500 * 500];
	char  infile[100], outfile1[100], outfile2[100], outfile3[100];//��������ļ�Ŀ¼
	int height,width;
	BYTE* IG_map, * I_map, *G_map;

	for (int k = 0; k < 30; k++)
	{
		sprintf(infile, "D:\\Documents\\CppProject\\BmpImage_Data\\lihong_data_8\\%05d.bmp", k);
		c_bitmap.readBitmap(infile); //8λ.bmpͼ���ȡ
		//c_bitmap.transformBitmap();//���ܣ���24λ��.bmpͼ��ת��Ϊ8λ��.bmpͼ��
		height = c_bitmap.height;
		width = c_bitmap.width;
		//���¸�ͼ���ǰ�λ
		//c_bitmap0.similar(c_bitmap);
		//I��Gͼ
		IG_map = new BYTE[width * height * sizeof(BYTE)];
		I_map = new BYTE[width * height * sizeof(BYTE)];
		G_map = new BYTE[width * height * sizeof(BYTE)];

		clock_t startTime, endTime;
		startTime = clock();//��ʱ��ʼ
		Lig1(c_bitmap.data_ptr, buffer, width, height, 3, 0.8, IG_map, I_map, G_map);
		//Lig2(c_bitmap.data_ptr, buffer, width, height, 2, 0.4, IG_map, I_map, G_map);
		endTime = clock();//��ʱ����
		cout << "The run time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
		sprintf(outfile1, "D:\\Desktop\\Imap\\%05d.bmp", k);
		YwkWrite8BitImg2BmpFile(I_map,width,height,outfile1);
		sprintf(outfile2, "D:\\Desktop\\Gmap\\%05d.bmp", k);
		YwkWrite8BitImg2BmpFile(G_map, width, height, outfile2);
		sprintf(outfile3, "D:\\Desktop\\IGmap\\%05d.bmp", k);
		YwkWrite8BitImg2BmpFile(IG_map, width, height, outfile3);
		delete[] IG_map;
		delete[] I_map;
		delete[] G_map;
	}
	system("pause");
}