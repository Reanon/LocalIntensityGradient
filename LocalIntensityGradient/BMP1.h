#ifndef _BMP1_H_
#define _BMP1_H_
void YwkThreshold(BYTE* img, int width, int height, BYTE Thre);
BYTE* YwkRead8BitBmpFile2Img(const char* filename, int* width, int* height);
int YwkWrite8BitImg2BmpFile(BYTE* img, int width, int height, const char* filename);
#endif // !_BMP_H_#pragma once
