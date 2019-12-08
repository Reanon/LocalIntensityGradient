#include "BMP.h"
//#include "stdafx.h"
CBitmapFile::CBitmapFile()
{
	data_ptr = NULL;
	this->buffer = new float[256 * 200];
}
CBitmapFile::~CBitmapFile()
{
	if (!data_ptr)
		delete[] data_ptr;
	data_ptr = NULL;
	if (!NULL)
	{
		delete[] buffer;
	}
}
/********************************************************************************************************************/
//���ܣ���ֵͷ�ļ���������������
/********************************************************************************************************************/
void CBitmapFile::copy(CBitmapFile& out)
{
	this->info_header = out.info_header;
	this->file_header = out.file_header;
	int size = info_header.biWidth * info_header.biHeight * info_header.biBitCount / 8;
	this->data_ptr = new unsigned char[size];
	for (int i = 0; i < size; i++)
		this->data_ptr[i] = out.data_ptr[i];
}
/********************************************************************************************************************/
//���ܣ��ڵ�ǰ��ͼ�ϱ��out�Ĵ���threshold�ĵ����ڵ�λ��
/********************************************************************************************************************/
void CBitmapFile::mark(CBitmapFile& out, int threshold)
{
	_ASSERT(this->info_header.biBitCount == 24);
	_ASSERT(out.info_header.biBitCount == 8);

	int height = out.info_header.biHeight;
	int width = out.info_header.biWidth;
	int max_size = this->file_header.bfSize - 54;
	int mid = 10;
	int m, k;

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			if (out.data_ptr[i * width + j] > threshold)
			{
				m = 0;
				for (k = 0; k < 2 * mid; k++)
					if ((i + k - mid) > 0 && (j + (m * 2 - 1) * mid) > 0 && ((i + k - mid) * width * 3 + (j + m - mid) * 3 + 2) < max_size)
					{
						this->data_ptr[(i + k - mid) * width * 3 + (j + m - mid) * 3] = 0;
						this->data_ptr[(i + k - mid) * width * 3 + (j + m - mid) * 3 + 1] = 0;
						this->data_ptr[(i + k - mid) * width * 3 + (j + m - mid) * 3 + 2] = 255;
					}
				m = 2 * mid;
				for (k = 0; k < 2 * mid; k++)
					if ((i + k - mid) > 0 && (j + (m * 2 - 1) * mid) > 0 && ((i + k - mid) * width * 3 + (j + m - mid) * 3 + 2) < max_size)
					{
						this->data_ptr[(i + k - mid) * width * 3 + (j + m - mid) * 3] = 0;
						this->data_ptr[(i + k - mid) * width * 3 + (j + m - mid) * 3 + 1] = 0;
						this->data_ptr[(i + k - mid) * width * 3 + (j + m - mid) * 3 + 2] = 255;
					}
				k = 0;
				for (m = 0; m < 2 * mid; m++)
					if ((i + k - mid) > 0 && (j + (m * 2 - 1) * mid) > 0 && ((i + k - mid) * width * 3 + (j + m - mid) * 3 + 2) < max_size)
					{
						this->data_ptr[(i + k - mid) * width * 3 + (j + m - mid) * 3] = 0;
						this->data_ptr[(i + k - mid) * width * 3 + (j + m - mid) * 3 + 1] = 0;
						this->data_ptr[(i + k - mid) * width * 3 + (j + m - mid) * 3 + 2] = 255;
					}
				k = 2 * mid;
				for (m = 0; m < 2 * mid; m++)
					if ((i + k - mid) > 0 && (j + (m * 2 - 1) * mid) > 0 && ((i + k - mid) * width * 3 + (j + m - mid) * 3 + 2) < max_size)
					{
						this->data_ptr[(i + k - mid) * width * 3 + (j + m - mid) * 3] = 0;
						this->data_ptr[(i + k - mid) * width * 3 + (j + m - mid) * 3 + 1] = 0;
						this->data_ptr[(i + k - mid) * width * 3 + (j + m - mid) * 3 + 2] = 255;
					}
			}
		}
}
/********************************************************************************************************************/
//���ܣ���ֵͷ�ļ���Ϊ��ǰ������������ռ䲢��ֵΪ0
/********************************************************************************************************************/
void CBitmapFile::similar(CBitmapFile& out)
{
	this->info_header = out.info_header;
	this->file_header = out.file_header;
	int size = info_header.biWidth * info_header.biHeight * info_header.biBitCount / 8;
	this->data_ptr = new unsigned char[size];
	for (int i = 0; i < size; i++)
		this->data_ptr[i] = 0;
}
/********************************************************************************************************************/
//���ܣ�����ָ��·���µ�����.bmp�ļ�
/********************************************************************************************************************/
vector<string> CBitmapFile::search_dir(string path)
{
	long hFile = 0;
	struct _finddata_t fileInfo;
	string pathName, exdName;
	vector<string> v_name;
	// \\* ����Ҫ�������е�����,��ĳ�\\*.jpg��ʾ����jpg�����ļ�
	if ((hFile = _findfirst(pathName.assign(path).append("\\*.bmp").c_str(), &fileInfo)) == -1) {
		return v_name;
	}
	do
	{
		//�ж��ļ����������ļ��л����ļ�
		v_name.push_back(fileInfo.name);
	} while (_findnext(hFile, &fileInfo) == 0);
	_findclose(hFile);
	return v_name;
}
void CBitmapFile::print()
{
	int line_byte = (info_header.biWidth * info_header.biBitCount / 8 + 3) / 4 * 4;
	for (int i = 0; i < info_header.biHeight; i++)
	{
		for (int j = 0; j < line_byte; j++)
			cout << (int)data_ptr[i * info_header.biWidth + j] << " ";
		cout << endl;
	}
}
/********************************************************************************************************************/
//���ܣ�24λ.bmpͼ���ȡ
/********************************************************************************************************************/
bool CBitmapFile::readBitmap_3(string name)
{
	ifstream inFile(name, ios::in | ios::binary);   //�ļ�������  ���ļ��е�student��Ϣ��������Ļ��
	//���ļ��򿪴���ʱ�Ĳ���
	if (!inFile)
	{
		cout << "The inFile open error!" << endl;
		return 0;
	}
	else
	{
		inFile.read((char*)&file_header, sizeof(file_header));
		inFile.read((char*)&info_header, sizeof(info_header));
		if (info_header.biBitCount != 24)
			return false;
		int line_byte = (info_header.biWidth * info_header.biBitCount / 8 + 3) / 4 * 4;
		data_ptr = new unsigned char[info_header.biHeight * line_byte];
		inFile.read((char*)data_ptr, sizeof(char) * (info_header.biHeight * line_byte));
		inFile.close();       //�ر�������
	}

}
/********************************************************************************************************************/
//���ܣ�24λ.bmpͼ�񴢴�
/********************************************************************************************************************/
bool CBitmapFile::saveBitmap_3(string name)
{
	ofstream outFile(name, ios::out | ios::binary);   //�ļ�������  ���ļ��е�student��Ϣ��������Ļ��
	//���ļ��򿪴���ʱ�Ĳ���
	if (!outFile)
	{
		cout << "The outFile open error!" << endl;
		return false;
	}
	else
	{
		outFile.write((char*)&file_header, sizeof(file_header));
		outFile.write((char*)&info_header, sizeof(info_header));
		int line_byte = (info_header.biWidth * info_header.biBitCount / 8 + 3) / 4 * 4;
		outFile.write((char*)data_ptr, sizeof(char) * (info_header.biHeight * line_byte));
		outFile.close();       //�ر�������
		return true;
	}
}
/********************************************************************************************************************/
//���ܣ�8λ.bmpͼ���ȡ
/********************************************************************************************************************/
bool CBitmapFile::readBitmap(string name)
{
	ifstream inFile(name, ios::in | ios::binary);   //�ļ�������  ���ļ��е�student��Ϣ��������Ļ��
	//���ļ��򿪴���ʱ�Ĳ���
	if (!inFile)
	{
		cout << "The inFile open error!" << endl;
		return 0;
	}
	else
	{
		inFile.read((char*)&file_header, sizeof(file_header));
		inFile.read((char*)&info_header, sizeof(info_header));
		if (info_header.biBitCount != 8)
			return false;
		int line_byte = (info_header.biWidth * info_header.biBitCount / 8 + 3) / 4 * 4;
		height = info_header.biHeight;
		width = info_header.biWidth;
		data_ptr = new unsigned char[info_header.biHeight * line_byte];
		inFile.seekg(256 * 4, ios::cur);
		inFile.read((char*)data_ptr, sizeof(char) * (info_header.biHeight * line_byte));
		inFile.close();       //�ر�������
	}

}
/********************************************************************************************************************/
//���ܣ�8λ.bmpͼ�񴢴�
/********************************************************************************************************************/
bool CBitmapFile::saveBitmap(string name)
{
	ofstream outFile(name, ios::out | ios::binary);   //�ļ�������  ���ļ��е�student��Ϣ��������Ļ��
	//���ļ��򿪴���ʱ�Ĳ���
	if (!outFile)
	{
		cout << "The outFile open error!" << endl;
		return false;
	}
	else
	{
		outFile.write((char*)&file_header, sizeof(file_header));
		outFile.write((char*)&info_header, sizeof(info_header));

		char* rgbq = new char[256 * 4];
		for (int i = 0; i < 256; i++)
		{
			rgbq[i * 4] = rgbq[i * 4 + 1] = rgbq[i * 4 + 2] = i;
			rgbq[i * 4 + 3] = 0;
		}
		outFile.write((char*)rgbq, sizeof(char) * (256 * 4));
		int line_byte = (info_header.biWidth * info_header.biBitCount / 8 + 3) / 4 * 4;

		outFile.write((char*)data_ptr, sizeof(char) * (info_header.biHeight * line_byte));
		outFile.close();       //�ر�������
		delete[] rgbq;
		return true;
	}
}
/********************************************************************************************************************/
//���ܣ�24λͼ��ת����32bit����һ�����أ�����MFC������ʾ
/********************************************************************************************************************/
bool CBitmapFile::expand_3()
{
	unsigned char* temp_ptr = data_ptr;
	data_ptr = new unsigned char[info_header.biWidth * info_header.biHeight * 4];
	for (int j = 0; j < info_header.biHeight; j++)
		for (int i = 0; i < info_header.biWidth; i++)
		{
			data_ptr[((info_header.biHeight - j - 1) * info_header.biWidth + i) * 4] = temp_ptr[(j * info_header.biWidth + i) * 3];
			data_ptr[((info_header.biHeight - j - 1) * info_header.biWidth + i) * 4 + 1] = temp_ptr[(j * info_header.biWidth + i) * 3 + 1];
			data_ptr[((info_header.biHeight - j - 1) * info_header.biWidth + i) * 4 + 2] = temp_ptr[(j * info_header.biWidth + i) * 3 + 2];
			data_ptr[((info_header.biHeight - j - 1) * info_header.biWidth + i) * 4 + 3] = 0;
		}
	delete[] temp_ptr;
	return true;
}
/********************************************************************************************************************/
//���ܣ�8λͼ��ת����32bit����һ�����أ�����MFC������ʾ
/********************************************************************************************************************/
bool CBitmapFile::expand()
{
	unsigned char* temp_ptr = data_ptr;
	data_ptr = new unsigned char[info_header.biWidth * info_header.biHeight * 4];
	for (int j = 0; j < info_header.biHeight; j++)
		for (int i = 0; i < info_header.biWidth; i++)
		{
			data_ptr[((info_header.biHeight - j - 1) * info_header.biWidth + i) * 4] = temp_ptr[(j * info_header.biWidth + i)];
			data_ptr[((info_header.biHeight - j - 1) * info_header.biWidth + i) * 4 + 1] = temp_ptr[(j * info_header.biWidth + i)];
			data_ptr[((info_header.biHeight - j - 1) * info_header.biWidth + i) * 4 + 2] = temp_ptr[(j * info_header.biWidth + i)];
			data_ptr[((info_header.biHeight - j - 1) * info_header.biWidth + i) * 4 + 3] = 0;
		}
	delete[] temp_ptr;
	return true;
}
/********************************************************************************************************************/
//���ܣ���24λ��.bmpͼ��ת��Ϊ8λ��.bmpͼ��
/********************************************************************************************************************/
bool CBitmapFile::transformBitmap()
{
	unsigned char* temp_ptr = data_ptr;
	data_ptr = new unsigned char[info_header.biHeight * info_header.biWidth];

	int line_byte = (info_header.biWidth + 3) / 4 * 4;//8λͼ������ֽ���
	int line_byte_origin = (info_header.biWidth * info_header.biBitCount / 8 + 3) / 4 * 4;//ԭͼ������ֽ���

	for (int j = 0; j < info_header.biHeight; j++)
		for (int i = 0; i < line_byte; i++)
		{
			data_ptr[j * line_byte + i] = temp_ptr[j * line_byte_origin + i * 3] * 0.114 + temp_ptr[j * line_byte_origin + i * 3 + 1] * 0.587 + temp_ptr[j * line_byte_origin + i * 3 + 2] * 0.299;
		}
	info_header.biBitCount = 8;
	file_header.bfSize = 54 + info_header.biWidth * info_header.biBitCount;
	delete[] temp_ptr;
	return true;
}
/********************************************************************************************************************/
//���ܣ�����wͼ��RΪbatch�Ŀ�ȣ�eΪһ��С��������ֹ���ֳ���0����ʽ��dstΪĿ��ͼ��
/********************************************************************************************************************/
void CBitmapFile::Lh_lhm(int R, float e, CBitmapFile& dst)
{
	int height = this->info_header.biHeight;
	int width = this->info_header.biWidth;
	float* buffer = new float[(height - R + 1) * (width - R + 1)];//����һ��batch�еľ�ֵ
	BYTE* pBuf, * p1, * p2;
	BYTE* pDst = dst.data_ptr;
	pBuf = this->data_ptr;
	int i, j, u, v, num, n;
	float p, q, sum, sumq;
	num = -1;
	float sigma;
	float mT, mB1, mB2, mB3, mB4, mB5, mB6, mB7, mB8;
	float d1, d2, d3, d4, d5, d6, d7, d8;
	float C, W, minD;
	//calcualte average gray value of every patch 
	for (i = 0; i <= height - R; i++)
	{
		for (int j = 0; j <= width - R; j++)
		{
			sum = 0;
			num += 1;
			for (u = 0; u < R; u++)
			{
				for (v = 0; v < R; v++)
				{
					p = *(pBuf + (i + u) * width + j + v);
					sum += p;
				}
			}
			buffer[num] = sum / (R * R);
		}
	}

	for (i = (3 * R - 1) / 2; i < height - (3 * R - 1) / 2; i++)
	{
		for (j = (3 * R - 1) / 2; j < width - (3 * R - 1) / 2; j++)
		{
			u = i - (R - 1) / 2; v = j - (R - 1) / 2;
			mT = buffer[u * (width - R + 1) + v];
			sumq = 0;
			for (u = i - (R - 1) / 2, p1 = pBuf + u * width; u <= i + (R - 1) / 2; u++, p1 += width)
			{
				for (v = j - (R - 1) / 2, p2 = p1 + v; v <= j + (R - 1) / 2; v++, p2++)
				{
					p = *p2;
					q = (p - mT) * (p - mT);
					sumq += q;
				}
			}
			sigma = sqrt(sumq / (R * R));
			//calculate mBi;��ָ�����������
			u = i + (R - 1) / 2 + 1; v = j - (R - 1) / 2 - R;
			mB1 = buffer[u * (width - R + 1) + v];

			u = i + (R - 1) / 2 + 1; v = j - (R - 1) / 2;
			mB2 = buffer[u * (width - R + 1) + v];

			u = i + (R - 1) / 2 + 1; v = j + (R - 1) / 2 + 1;
			mB3 = buffer[u * (width - R + 1) + v];

			u = i - (R - 1) / 2; v = j + (R - 1) / 2 + 1;
			mB4 = buffer[u * (width - R + 1) + v];

			u = i - (R - 1) / 2 - R; v = j + (R - 1) / 2 + 1;
			mB5 = buffer[u * (width - R + 1) + v];

			u = i - (R - 1) / 2 - R; v = j - (R - 1) / 2;
			mB6 = buffer[u * (width - R + 1) + v];

			u = i - (R - 1) / 2 - R; v = j - (R - 1) / 2 - R;
			mB7 = buffer[u * (width - R + 1) + v];

			u = i - (R - 1) / 2; v = j - (R - 1) / 2 - R;
			mB8 = buffer[u * (width - R + 1) + v];

			//calculate d`i;
			d1 = mT - mB1;
			d2 = mT - mB2;
			d3 = mT - mB3;
			d4 = mT - mB4;
			d5 = mT - mB5;
			d6 = mT - mB6;
			d7 = mT - mB7;
			d8 = mT - mB8;
			float D1, D2, D3, D4;

			if ((d1 > 0) && (d5 > 0))D1 = d1 * d5;
			else D1 = 0;

			if ((d2 > 0) && (d6 > 0))D2 = d2 * d6;
			else D2 = 0;

			if ((d3 > 0) && (d7 > 0))D3 = d3 * d7;
			else D3 = 0;

			if ((d4 > 0) && (d8 > 0))D4 = d4 * d8;
			else D4 = 0;

			float D[4] = { D1,D2,D3,D4 };

			minD = D[0];
			for (int k = 0; k < 4; k++)
			{
				if (D[k] < minD)
					minD = D[k];
			}
			C = minD;
			W = C * (1 / (e + sigma));
			*(pDst + i * width + j) = W;
		}
	}

	delete[] buffer;
}

void CBitmapFile::Lig(int R, float k, CBitmapFile& dst)
{
	int height = this->info_header.biHeight;
	int width = this->info_header.biWidth;
	int step = (R - 1) / 2;//һ��patch�����ĵ��ߵľ��� 
	float* IG_buffer = this->buffer;
	//float* IG_buffer = new float[height * width];

	//����Gʹ�õı���
	float z1, z2, z3, z4, z6, z7, z8, z9;
	float g_x, g_y, angle;
	float G1, G2, G3, G4, Gmin, Gmax, G;
	int G1_count, G2_count, G3_count, G4_count;
	//����Iʹ�õı���
	float sumf, f0, f_;
	float I;

	float IG_bar, IG_max;
	int IG_bar_count;
	BYTE* pBuf, * p1, * p2, * p2_1, * p2_2;
	BYTE* pDst = dst.data_ptr;
	pBuf = this->data_ptr;
	int i, j, u, v, x, y;
	//calcualte average gray value of every patch 
	IG_bar = IG_max = 0;
	IG_bar_count = 0;
	for (i = (R + 1) / 2; i < height - (R + 1) / 2; i++)
	{
		for (j = (R + 1) / 2; j < width - (R + 1) / 2; j++)
		{

			G1 = G2 = G3 = G4 = 0;
			G1_count = G2_count = G3_count = G4_count = 0;
			f0 = *(pBuf + i * width + j);
			sumf = 0;
			//for a patch
			for (u = i - step, p1 = pBuf + u * width; u <= i + step; u++, p1 += width)//y
			{
				for (v = j - step, p2 = p1 + v; v <= j + step; v++, p2++)//x
				{
					p2_1 = p2 - width;
					p2_2 = p2 + width;

					z1 = *(p2_1 - 1);
					z2 = *(p2_1);
					z3 = *(p2_1 + 1);
					z4 = *(p2 - 1);
					z6 = *(p2 + 1);
					z7 = *(p2_2 - 1);
					z8 = *(p2_2);
					z9 = *(p2_2 + 1);

					g_y = (z7 + 2 * z8 + z9) - (z1 + 2 * z2 + z3);
					g_x = (z3 + 2 * z6 + z9) - (z1 + 2 * z4 + z7);

					angle = atan2(g_y, g_x);
					angle = angle > 0 ? angle : (2 * PI + angle);
					x = v - j;
					y = u - i;
					if (angle < 0.5 * PI && y <= 0 && x < 0)
					{
						G1 += g_x * g_x + g_y * g_y;
						G1_count++;
					}
					else if (angle < PI && y < 0 && x >= 0)
					{
						G2 += g_x * g_x + g_y * g_y;
						G2_count++;
					}
					else if (angle < 1.5 * PI && y >= 0 && x > 0)
					{
						G3 += g_x * g_x + g_y * g_y;
						G3_count++;
					}
					else if (angle < 2 * PI && y > 0 && x <= 0)
					{
						G4 += g_x * g_x + g_y * g_y;
						G4_count++;
					}

					sumf += *p2;
				}
			}
			G1 /= G1_count != 0 ? (G1_count) : 1;
			G2 /= G2_count != 0 ? (G2_count) : 1;
			G3 /= G3_count != 0 ? (G3_count) : 1;
			G4 /= G4_count != 0 ? (G4_count) : 1;
			Gmax = Gmin = G1;
			if (G2 > Gmax)
				Gmax = G2;
			if (G3 > Gmax)
				Gmax = G3;
			if (G4 > Gmax)
				Gmax = G4;

			if (G2 < Gmin)
				Gmin = G2;
			if (G3 < Gmin)
				Gmin = G3;
			if (G4 < Gmin)
				Gmin = G4;

			G = (Gmin / Gmax > k) ? (G1 + G2 + G3 + G4) : 0;

			f_ = (f0 - sumf) / (1 - R * R);
			I = (f0 - f_) > 0 ? (f0 - f_) : 0;

			IG_buffer[i * width + j] = I * G;
			if (IG_buffer[i * width + j] > IG_max)
				IG_max = IG_buffer[i * width + j];
			if (IG_buffer[i * width + j] != 0)
			{
				IG_bar += IG_buffer[i * width + j];
				IG_bar_count++;
			}
		}
	}

	IG_bar /= IG_bar_count == 0 ? 1 : IG_bar_count;

	for (i = (R + 1) / 2; i < height - (R + 1) / 2; i++)
		for (j = (R + 1) / 2; j < width - (R + 1) / 2; j++)
		{
			if (IG_buffer[i * width + j] <= IG_bar)
				pDst[i * width + j] = 0;
			else
				pDst[i * width + j] = IG_buffer[i * width + j] / IG_max * 255;
		}
}

/********************************************************************************************************************/
//���ܣ�����wͼ��RΪbatch�Ŀ�ȣ�dstΪĿ��ͼ��ʹ��sobel����
//z1    z2	z3
//z4    z5  z6
//z7	z8  z9
/********************************************************************************************************************/
void CBitmapFile::Lig(int R, float k, CBitmapFile& dst, CBitmapFile& dst_I, CBitmapFile& dst_G)
{
	int height = this->info_header.biHeight;
	int width = this->info_header.biWidth;
	int step = (R - 1) / 2;//һ��patch�����ĵ��ߵľ��� 
	float* IG_buffer = this->buffer;
	float* I_buffer = this->buffer_I;//���ڻ���Imapd��ָ��
	float* G_buffer = this->buffer_G;//���ڻ���Gmapd��ָ��
	//float* IG_buffer = new float[height * width];

	//����Gʹ�õı���
	float z1, z2, z3, z4, z6, z7, z8, z9;
	//G����ݶ�
	float g_x, g_y, angle;
	//�ĸ�G��
	float G1, G2, G3, G4, Gmin, Gmax, G;
	//ÿ��С��G������
	int G1_count, G2_count, G3_count, G4_count;
	//����Iʹ�õı���
	float sumf;//
	float f0;//�������ĵ������
	float f_;//������Χ������ƽ��ֵ
	float I;

	float IG_bar, IG_max;
	int IG_bar_count;
	BYTE* pBuf;//����ͼ�������
	BYTE* p1, * p2_1, * p2_2;
	BYTE* p2;//ָ�򻬿����Ͻ�
	BYTE* pDst = dst.data_ptr;//���ͼ�������
	BYTE* pDst_I = dst_I.data_ptr;//Imapͼ�������
	BYTE* pDst_G = dst_G.data_ptr;//Gmapͼ�������

	pBuf = this->data_ptr;//����ͼ�������
	//ѭ������
	int i;//���������ĵ㣺i=(R + 1) / 2 ~ height - (R + 1) / 2
	int j;//�󻷺������ĵ㣺j=(R + 1) / 2 ~ width - (R + 1) / 2
	int r;//��������
	int l;//�������
	int x;
	int y;
	//calcualte average gray value of every patch 
	IG_bar = 0;
	IG_max = 0;
	IG_bar_count = 0;
	for (i = (R + 1) / 2; i < height - (R + 1) / 2; i++)//�������һ�������Χ���Ա㲻����
	{
		for (j = (R + 1) / 2; j < width - (R + 1) / 2; j++)
		{

			G1 = G2 = G3 = G4 = 0;
			G1_count = G2_count = G3_count = G4_count = 0;
			f0 = *(pBuf + i * width + j);//ͼ�����ĵ�λ��
			sumf = 0;
			//for a patch��������������ڵ�Gֵ
			for (r = i - step, p1 = pBuf + r * width; r <= i + step; r++, p1 += width)//y
			{
				for (l = j - step, p2 = p1 + l; l <= j + step; l++, p2++)//x
				{
					p2_1 = p2 - width;//�������ĵ��Ϸ��ĵ�
					p2_2 = p2 + width;//�������ĵ��·��ĵ�
					//����һ������
					z1 = *(p2_1 - 1);
					z2 = *(p2_1);
					z3 = *(p2_1 + 1);
					z4 = *(p2 - 1);
					z6 = *(p2 + 1);
					z7 = *(p2_2 - 1);
					z8 = *(p2_2);
					z9 = *(p2_2 + 1);

					g_x = (z7 + 2 * z8 + z9) - (z1 + 2 * z2 + z3);
					g_y = (z3 + 2 * z6 + z9) - (z1 + 2 * z4 + z7);

					//���������ĽǶ�
					angle = atan2(g_y, g_x);
					angle = angle > 0 ? angle : (2 * PI + angle);
					x = l - j;
					y = r - i;
					if (angle < 0.5 * PI && y <= 0 && x < 0)
					{
						G1 += g_x * g_x + g_y * g_y;
						G1_count++;
					}
					else if (angle < PI && y < 0 && x >= 0)
					{
						G2 += g_x * g_x + g_y * g_y;
						G2_count++;
					}
					else if (angle < 1.5 * PI && y >= 0 && x > 0)
					{
						G3 += g_x * g_x + g_y * g_y;
						G3_count++;
					}
					else if (angle < 2 * PI && y > 0 && x <= 0)
					{
						G4 += g_x * g_x + g_y * g_y;
						G4_count++;
					}

					sumf += *p2;
				}
			}
			G1 /= (G1_count != 0 ? (G1_count) : 1);
			G2 /= (G2_count != 0 ? (G2_count) : 1);
			G3 /= (G3_count != 0 ? (G3_count) : 1);
			G4 /= (G4_count != 0 ? (G4_count) : 1);
			Gmax = Gmin = G1;
			if (G2 > Gmax)
				Gmax = G2;
			if (G3 > Gmax)
				Gmax = G3;
			if (G4 > Gmax)
				Gmax = G4;

			if (G2 < Gmin)
				Gmin = G2;
			if (G3 < Gmin)
				Gmin = G3;
			if (G4 < Gmin)
				Gmin = G4;

			G = (Gmin / Gmax > k) ? (G1 + G2 + G3 + G4) : 0;
			
			//ͼ��ƽ��ֵ
			f_ = (f0 - sumf) / (1 - R * R);
			I = (f0 - f_) > 0 ? (f0 - f_) : 0;
			//���Imap��Gmap��IGmap;
			pDst_I[i * width + j] = I;
			pDst_G[i * width + j] = G;
			IG_buffer[i * width + j] = I * G;

			if (IG_buffer[i * width + j] > IG_max)
				IG_max = IG_buffer[i * width + j];
			if (IG_buffer[i * width + j] != 0)
			{
				IG_bar += IG_buffer[i * width + j];
				IG_bar_count++;
			}
		}
	}
	//�趨��ֵ
	IG_bar /= (IG_bar_count == 0 ? 1 : IG_bar_count);
	for (i = (R + 1) / 2; i < height - (R + 1) / 2; i++)
		for (j = (R + 1) / 2; j < width - (R + 1) / 2; j++)
		{
			if (IG_buffer[i * width + j] <= IG_bar)
				pDst[i * width + j] = 0;
			else
				pDst[i * width + j] = IG_buffer[i * width + j] / IG_max * 255;
		}
}

int CBitmapFile::YwkWrite8BitImg2BmpFile(CBitmapFile& dst, const char* filename)
{

	FILE* BinFile;
	BITMAPFILEHEADER FileHeader;
	BITMAPINFOHEADER BmpHeader;
	BYTE p[4];
	BYTE* img = dst.data_ptr;
	int height = this->info_header.biHeight;
	int width = this->info_header.biWidth;
	int i, Suc = 1;

	// Open File
	if ((BinFile = fopen(filename, "w+b")) == NULL) { return -1; }
	// Fill the FileHeader
	FileHeader.bfType = ((WORD)('M' << 8) | 'B');
	FileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BmpHeader) + 256 * 4L;
	FileHeader.bfSize = FileHeader.bfOffBits + width * height;
	FileHeader.bfReserved1 = 0;
	FileHeader.bfReserved2 = 0;
	if (fwrite((void*)&FileHeader, 1, sizeof(BITMAPFILEHEADER), BinFile) != sizeof(BITMAPFILEHEADER)) Suc = -1;
	// Fill the ImgHeader
	BmpHeader.biSize = 40;
	BmpHeader.biWidth = width;
	BmpHeader.biHeight = height;
	BmpHeader.biPlanes = 1;
	BmpHeader.biBitCount = 8;
	BmpHeader.biCompression = 0;
	BmpHeader.biSizeImage = 0;
	BmpHeader.biXPelsPerMeter = 0;
	BmpHeader.biYPelsPerMeter = 0;
	BmpHeader.biClrUsed = 0;
	BmpHeader.biClrImportant = 0;
	if (fwrite((void*)&BmpHeader, 1, sizeof(BmpHeader), BinFile) != sizeof(BmpHeader)) Suc = -1;
	// write Pallete
	for (i = 0, p[3] = 0; i < 256; i++)
	{
		p[0] = p[1] = p[2] = i; // blue,green,red;

		if (fwrite((void*)p, 1, 4, BinFile) != 4) { Suc = -1; break; }
	}
	// write image data
	if (fwrite((void*)img, 1, width * height, BinFile) != width * height) Suc = -1;
	// return;
	fclose(BinFile);
	return Suc;
	return 0;
}
