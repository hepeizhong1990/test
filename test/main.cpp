#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

// void DWORDReverseCopy(DWORD *pDest,const DWORD *pSrc,int iLength)
// {
// 	__asm
// 	{
// 		mov ecx,iLength
// 			mov esi,pSrc
// 			mov edi,pDest
// L1:
// 		lodsd
// 			bswap eax
// 			mov [edi+ecx*4-4],eax
// 			dec ecx
// 			jnz L1
// 	}
// }

//左右翻转，矩阵宽度为8的倍数
void TurnRighttoLift(unsigned char *src, unsigned char *dest, int wid, int high)
{
	unsigned long long *src_l = (unsigned long long *)src;
	unsigned long long *dest_l = (unsigned long long *)dest;
	unsigned long long x;
	int wid_l = wid/8;
	for (int i = 0; i < high; i ++)
	{
		for (int j = 0; j < wid_l; j ++)
		{
			x = *(src_l++);
			x = ((x<<8)&0xFF00FF00FF00FF00) | ((x>>8)&0x00FF00FF00FF00FF);
			x = ((x<<16)&0xFFFF0000FFFF0000) | ((x>>16)&0x0000FFFF0000FFFF);
			*(dest_l + wid_l*i + wid_l - 1 - j) = (x>>32) | (x<<32);
		}
	}

}

//对角线翻转（可见光的形式）,矩阵宽度为8的倍数
void TurnWrowtoHrow(unsigned char *src, unsigned char *dest, int wid, int high)
{

}

int main()
{
	clock_t start_t,end_t;
	FILE *fp;
	fp = fopen("D:\\HDR1.dat","rb+");

	unsigned char * src_buf = (unsigned char *)malloc(75767120);
	unsigned char * dest_buf = (unsigned char *)malloc(75767120);

	start_t = clock();
	unsigned char * dest_buf1 = (unsigned char *)malloc(75767120);
	end_t = clock();

	printf("malloc use time : %lld\n",end_t - start_t);


	start_t = clock();
	memset(dest_buf1,0,75767120);
	end_t = clock();

	printf("memset use time : %ld\n",end_t - start_t);

	start_t = clock();
	memcpy(dest_buf1,src_buf,75767120);
	end_t = clock();

	printf("memcpy use time : %ld\n",end_t - start_t);

	start_t = clock();
	fread(src_buf,1,75767120,fp);
	end_t = clock();

	printf("fread use time : %ld\n",end_t - start_t);

	start_t = clock();
	TurnRighttoLift(src_buf,dest_buf,6512,11635);
	end_t = clock();

	printf("turn use time : %ld\n",end_t - start_t);
	/*memcpy(dest_buf,src_buf,75767120);*/


	/*clock_t start_t,end_t; 
	register unsigned int x,y;
	register long long x1,y1;
	unsigned short x2;
	FILE *fp;
	fp = fopen("D:\\A.dat","rb+");

	unsigned char *buf = (unsigned char *)malloc(11635*6512);
	unsigned char *outbuf = (unsigned char *)malloc(11635*6512);
	fread(buf,1,11635*6512,fp);

	unsigned int *p = (unsigned int *)buf;
	unsigned int *p1 = (unsigned int *)malloc(11635*1628*4);
	long long *p3 = (long long *)buf;
	long long *p2 = (long long *)malloc(11635*6512);
	unsigned short *p4 = (unsigned short *)buf;
	unsigned short *p5 = (unsigned short *)malloc(11635*6512);
	int i,j;
	char *qqq = (char *)buf;
	char *qqq2 = (char *)outbuf;
	int num = 11635*6512;*/


// 	start_t = clock();
// 	memcpy(outbuf,buf,num);
	
// 	for (int i = 0; i < 11635*6512; i ++)
// 	{
// 		outbuf[i] = buf[i];
// 	}
// 	for (i = 0; i < 11635; i++)
// 	{
// 		for (j = 0; j < 6512; j ++)
// 		{
// 			outbuf[i*6512+j] = buf[i*6512+6512-j-1];
// 		}
// 	}
// 	for (int i = 0; i < 11635; i ++)
// 	{
// //// 		for (int j = 0; j < 1628; j ++)
// //// 		{
// //// 		x = p[i*1628+j];
// //// 		x = ((x<<8)&0xFF00FF00) | ((x>>8)&0x00FF00FF);
// //// 		p1[i*1628+j] = (x>>16) | (x<<16);
// //// 		}
// 		for (int j = 0; j < 814; j ++)
// 		{
// 			x1 = p3[i*814+j];
// 			x1 = ((x1<<8)&0xFF00FF00FF00FF00ll) | ((x1>>8)&0x00FF00FF00FF00FFll);
// 			x1 = ((x1<<16)&0xFFFF0000FFFF0000ll) | ((x1>>16)&0x0000FFFF0000FFFFll);
// 			p2[i*814+j] = (x1>>32) | (x1<<32);
// 		}
// //////// 		for (int j = 0; j < 3256; j ++)
// //////// 		{
// //////// 			x2 = p4[i*3256+j];
// //////// 			p5[i*3256+j] = (x2>>8) | (x2<<8);
// //////// 		}
// 	}

// 	end_t = clock();
// 	printf("%ld\n",end_t-start_t);

// 	long long t1 = 165820,t2;
// 	long long *q1 = &t1;
// 	long long *q2 = &t2;
// 	
// 	t1 = ((t1<<8)&0xFF00FF00FF00FF00) | ((t1>>8)&0x00FF00FF00FF00FF);
// 	t1 = ((t1<<16)&0xFFFF0000FFFF0000) | ((t1>>16)&0x0000FFFF0000FFFF);
// 	t2 = (t1>>32) | (t1<<32);

	return 0;
}