//#define _CRT_SECURE_NO_WARNINGS
//#include"BMP.h"
//int main() 
//{
//	CBitmapFile c_bitmap,c_bitmap0, c_bitmap_I, c_bitmap_G;
//	//BYTE* srcImg, * dstImg;
//
//	float* buffer;
//	buffer = new float[500 * 500];
//	char  infile[100],outfile1[100], outfile2[100];
//
//	for (int k = 0; k < 10; k++)
//	{
//		sprintf(infile, "D:\\Documents\\CppProject\\BmpImage_Data\\lihong_data_8\\%05d.bmp", k);
//		c_bitmap.readBitmap(infile); //8λ.bmpͼ���ȡ
//		//c_bitmap.transformBitmap();//���ܣ���24λ��.bmpͼ��ת��Ϊ8λ��.bmpͼ��
//		
//		//���¸�ͼ���ǰ�λ
//		//c_bitmap0.similar(c_bitmap);
//		//I��Gͼ
//		c_bitmap_I.similar(c_bitmap);
//		c_bitmap_G.similar(c_bitmap);
//		
//		clock_t startTime, endTime;
//		startTime = clock();//��ʱ��ʼ
//		c_bitmap.Lig(7, 0.4, c_bitmap, c_bitmap_I, c_bitmap_G);
//		endTime = clock();//��ʱ����
//		std::cout << "The run time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << std::endl;
//
//		sprintf(outfile1, "D:\\Desktop\\Imap\\%05d.bmp", k);
//		c_bitmap_I.YwkWrite8BitImg2BmpFile(c_bitmap_I, outfile1);
//		sprintf(outfile2, "D:\\Desktop\\Gmap\\%05d.bmp", k);
//		c_bitmap_G.YwkWrite8BitImg2BmpFile(c_bitmap_G, outfile2);
//	}
//}