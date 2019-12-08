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
//		c_bitmap.readBitmap(infile); //8位.bmp图像读取
//		//c_bitmap.transformBitmap();//功能：将24位的.bmp图像转化为8位的.bmp图像
//		
//		//以下各图都是八位
//		//c_bitmap0.similar(c_bitmap);
//		//I和G图
//		c_bitmap_I.similar(c_bitmap);
//		c_bitmap_G.similar(c_bitmap);
//		
//		clock_t startTime, endTime;
//		startTime = clock();//计时开始
//		c_bitmap.Lig(7, 0.4, c_bitmap, c_bitmap_I, c_bitmap_G);
//		endTime = clock();//计时结束
//		std::cout << "The run time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << std::endl;
//
//		sprintf(outfile1, "D:\\Desktop\\Imap\\%05d.bmp", k);
//		c_bitmap_I.YwkWrite8BitImg2BmpFile(c_bitmap_I, outfile1);
//		sprintf(outfile2, "D:\\Desktop\\Gmap\\%05d.bmp", k);
//		c_bitmap_G.YwkWrite8BitImg2BmpFile(c_bitmap_G, outfile2);
//	}
//}