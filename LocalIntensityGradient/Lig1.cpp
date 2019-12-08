#include "Lig1.h"
#include<math.h>

void Lig1(BYTE* img, float* IG_buffer, int width, int height, int R, float k, BYTE* IG_map, BYTE* I_map, BYTE* G_map)
{
	int step = (R - 1) / 2;//һ��patch�����ĵ��ߵľ���

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
	BYTE* pBuf, * p1, * p2_1, * p2_2;
	BYTE* p2;//ָ�򻬿����Ͻ�
	BYTE* pDst =  IG_map;//���ͼ�������
	BYTE* pDst_I = I_map;//Imapͼ�������
	BYTE* pDst_G = G_map;//Gmapͼ�������
	pBuf = img;
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
					angle = angle > 0 ? angle : (2 * PI + angle);//�Ա�õ�0-2*pi���ݶ�ֵ��

					x = l - j;
					y = r - i;
					if (angle < 0.5 * PI && y <= 0 && x < 0)
					{
						//G1 += g_x * g_x + g_y * g_y;
						G1 += abs(g_x) + abs(g_y);
						G1_count++;
					}
					else if (angle < PI && y < 0 && x >= 0)
					{
						//G2 += g_x * g_x + g_y * g_y;
						G2 += abs(g_x) + abs(g_y);
						G2_count++;
					}
					else if (angle < 1.5 * PI && y >= 0 && x > 0)
					{
						//G3 += g_x * g_x + g_y * g_y;
						G3 += abs(g_x) + abs(g_y);
						G3_count++;
					}
					else if (angle < 2 * PI && y > 0 && x <= 0)
					{
						//G4 += g_x * g_x + g_y * g_y;
						G4 += abs(g_x) + abs(g_y);
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

			G = (Gmin / Gmax > k) ? (G1 + G2 + G3 + G4)/4 : 0;

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
	if (IG_bar_count == 0)
	{
		IG_bar = IG_bar;
	}
	else
	{
		//IG_bar = IG_bar / IG_bar_count ;
		IG_bar = IG_max *0.8;
	}
	//IG_bar /= (IG_bar_count == 0 ? 1 : IG_bar_count);
	for (i = (R + 1) / 2; i < height - (R + 1) / 2; i++)
		for (j = (R + 1) / 2; j < width - (R + 1) / 2; j++)
		{
			if (IG_buffer[i * width + j] <= IG_bar)
				pDst[i * width + j] = 0;
			else
				pDst[i * width + j] = IG_buffer[i * width + j] / IG_max * 255;
		}


}


