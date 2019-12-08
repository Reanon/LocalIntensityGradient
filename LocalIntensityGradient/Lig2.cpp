#include"Lig2.h"

void Lig2(BYTE* img, float* IG_buffer, int width, int height, int T, float k, BYTE* IG_map, BYTE* I_map, BYTE* G_map)
{
	int R = 8;//�����С
	int step = (R - T) / 2;//һ��patch�����ĵ��ߵľ���

	//����Gʹ�õı���
	float z1, z2, z3, z4, z6, z7, z8, z9;
	//G����ݶ�
	float g_x, g_y, angle;
	//�ĸ�G��
	float G1, G2, G3, G4, Gmin, Gmax, G;
	//ÿ��С��G������
	int G1_count, G2_count, G3_count, G4_count;
	//����Iʹ�õı���
	float sumf; //��Χ���������
	float sumf0; //�������������
	float f0;//�������ĵ������
	float f_;//������Χ������ƽ��ֵ
	float I;
	/*float* IG_buffer = new float[height * width];*/
	/*float* I_buffer = new float[height * width];
	float* G_buffer = new float[height * width];*/

	float IG_bar, IG_max;
	int IG_bar_count;
	BYTE* p1, * p2_1, * p2_2;
	BYTE* p2;//ָ�򻬿����Ͻ�
	BYTE* pBuf = img;    //����ͼ�ε�����
	BYTE* pDst = IG_map; //���ͼ�������
	BYTE* pDst_I = I_map;//Imapͼ�������
	BYTE* pDst_G = G_map;//Gmapͼ�������

	//ѭ������
	int i;//���������ĵ㣺i=(R -T)/2 + 1  ~ height - (R -T)/2 - 1
	int j;//�󻷺������ĵ㣺j=(R -T)/2 + 1 ~ width - (R -T)/2 - 1
	int r;//��������
	int l;//�������
	int x;
	int y;

	//calcualte average gray value of every patch 
	IG_bar = 0;
	IG_max = 0;
	IG_bar_count = 0;
	for (i = (R - T) / 2 + 1; i < height - (R - T) / 2 - 1; i++)//�������һ�������Χ���Ա㲻����
	{
		for (j = (R - T) / 2 + 1; j < width - (R - T) / 2 - 1; j++)
		{

			G1 = G2 = G3 = G4 = 0;
			G1_count = G2_count = G3_count = G4_count = 0;
			sumf0 = 0;
			int flag1 = 0, flag2 = 0;//���ڼ�¼�м��������μӷ�
			for (int o = i; o < i + T; o++)
			{
				for (int p = j; p < j + T; p++)
				{
					sumf0 += *(pBuf + o * width + p);
					flag1++;
				}
			}
			f0 = sumf0 / (T * T);//Ŀ���ƽ������

			sumf = 0;//������Χ������֮��
			//for a patch��������������ڵ�Gֵ
			for (r = i - step, p1 = pBuf + r * width; r < i + step; r++, p1 += width)//y
			{
				for (l = j - step, p2 = p1 + l; l < j + step; l++, p2++)//x
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

					g_x = (z7 + 2 * z8 + z9) - (z1 + 2 * z2 + z3);//�ײ���ȥ����
					g_y = (z3 + 2 * z6 + z9) - (z1 + 2 * z4 + z7);//���м�ȥ����

					//���������ĽǶ�
					angle = atan2(g_y, g_x);
					angle = angle > 0 ? angle : (2 * PI + angle);
					/*x = l - j;
					y = r - (i+T);*/
					if (angle < 0.5 * PI && r - (i + T) <= 0 && l - j < 0)
					{
						G1 += g_x * g_x + g_y * g_y;
						G1_count++;
					}
					else if (angle < PI && r - i < 0 && l - j >= 0)
					{
						G2 += g_x * g_x + g_y * g_y;
						G2_count++;
					}
					else if (angle < 1.5 * PI && r - i >= 0 && l - (j + T) > 0)
					{
						G3 += g_x * g_x + g_y * g_y;
						G3_count++;
					}
					else if (angle < 2 * PI && r - (i + T) > 0 && l - (j + T) <= 0)
					{
						G4 += g_x * g_x + g_y * g_y;
						G4_count++;
					}

					sumf += *p2;
					flag2++;

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

			int threshold = Gmin / Gmax;
			G = (threshold > k) ? (G1 + G2 + G3 + G4) : 0;

			pDst_G[i * width + j] = G;
			//ͼ��ƽ��ֵ
			f_ = (f0 - sumf) / (T * T - R * R);//��Χ������ƽ������ֵ

			if ((f0 - f_) > 0)
			{
				for (int o = i; o < i + T; o++)
				{
					for (int p = j; p < j + T; p++)
					{
						pDst_I[o * width + p] = f0 - f_;
					}
				}
			}
			else
			{
				for (int o = i; o < i + T; o++)
				{
					for (int p = j; p < j + T; p++)
					{
						pDst_I[o * width + p] = 0;
					}
				}

			}
			I = (f0 - f_) > 0 ? (f0 - f_) : 0;

			//���Imap��Gmap��IGmap;
			//pDst_I[i * width + j] = I;

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
	for (int i = (R - T) / 2  ; i < height - (R - T) / 2 ; i++)
	{
		for (int j = (R - T) / 2 ; j < width - (R - T) / 2 ; j++)
		{
			if (IG_buffer[i * width + j] <= IG_bar)
				pDst[i * width + j] = 0;
			else
				pDst[i * width + j] = IG_buffer[i * width + j] / IG_max * 255;
		}
	}

}