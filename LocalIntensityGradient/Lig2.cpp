#include"Lig2.h"

void Lig2(BYTE* img, float* IG_buffer, int width, int height, int T, float k, BYTE* IG_map, BYTE* I_map, BYTE* G_map)
{
	int R = 8;//滑块大小
	int step = (R - T) / 2;//一个patch从中心到边的距离

	//计算G使用的变量
	float z1, z2, z3, z4, z6, z7, z8, z9;
	//G块的梯度
	float g_x, g_y, angle;
	//四个G块
	float G1, G2, G3, G4, Gmin, Gmax, G;
	//每个小块G的数量
	int G1_count, G2_count, G3_count, G4_count;
	//计算I使用的变量
	float sumf; //周围区域的亮度
	float sumf0; //中心区域的亮度
	float f0;//滑块中心点的亮度
	float f_;//滑块周围的亮度平均值
	float I;
	/*float* IG_buffer = new float[height * width];*/
	/*float* I_buffer = new float[height * width];
	float* G_buffer = new float[height * width];*/

	float IG_bar, IG_max;
	int IG_bar_count;
	BYTE* p1, * p2_1, * p2_2;
	BYTE* p2;//指向滑块左上角
	BYTE* pBuf = img;    //输入图形的数据
	BYTE* pDst = IG_map; //输出图像的数据
	BYTE* pDst_I = I_map;//Imap图像的数据
	BYTE* pDst_G = G_map;//Gmap图像的数据

	//循环变量
	int i;//大环纵向，中心点：i=(R -T)/2 + 1  ~ height - (R -T)/2 - 1
	int j;//大环横向，中心点：j=(R -T)/2 + 1 ~ width - (R -T)/2 - 1
	int r;//滑块纵向
	int l;//滑块横向
	int x;
	int y;

	//calcualte average gray value of every patch 
	IG_bar = 0;
	IG_max = 0;
	IG_bar_count = 0;
	for (i = (R - T) / 2 + 1; i < height - (R - T) / 2 - 1; i++)//这里多留一个格给外围，以便不超界
	{
		for (j = (R - T) / 2 + 1; j < width - (R - T) / 2 - 1; j++)
		{

			G1 = G2 = G3 = G4 = 0;
			G1_count = G2_count = G3_count = G4_count = 0;
			sumf0 = 0;
			int flag1 = 0, flag2 = 0;//用于记录中间计算过几次加法
			for (int o = i; o < i + T; o++)
			{
				for (int p = j; p < j + T; p++)
				{
					sumf0 += *(pBuf + o * width + p);
					flag1++;
				}
			}
			f0 = sumf0 / (T * T);//目标的平均亮度

			sumf = 0;//中心周围的亮度之和
			//for a patch，计算这个滑块内的G值
			for (r = i - step, p1 = pBuf + r * width; r < i + step; r++, p1 += width)//y
			{
				for (l = j - step, p2 = p1 + l; l < j + step; l++, p2++)//x
				{
					p2_1 = p2 - width;//滑块中心点上方的点
					p2_2 = p2 + width;//滑块中心点下方的点
					//计算一个滑块
					z1 = *(p2_1 - 1);
					z2 = *(p2_1);
					z3 = *(p2_1 + 1);
					z4 = *(p2 - 1);
					z6 = *(p2 + 1);
					z7 = *(p2_2 - 1);
					z8 = *(p2_2);
					z9 = *(p2_2 + 1);

					g_x = (z7 + 2 * z8 + z9) - (z1 + 2 * z2 + z3);//底部减去顶部
					g_y = (z3 + 2 * z6 + z9) - (z1 + 2 * z4 + z7);//右列减去左列

					//计算这个点的角度
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
			//图像平均值
			f_ = (f0 - sumf) / (T * T - R * R);//周围背景的平均亮度值

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

			//求得Imap、Gmap和IGmap;
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
	//设定阈值
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