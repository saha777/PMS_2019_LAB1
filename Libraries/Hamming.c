#include "Hamming.h"

char calc_Ham(char data)
{
	char dataBuf[4][7];
	char res=0;
	dataBuf[0][0]=0;
	dataBuf[0][1]=0;
	dataBuf[0][2]=data&(0x01);
	dataBuf[0][3]=0;
	dataBuf[0][4]=(data>>1)&(0x01);
	dataBuf[0][5]=(data>>2)&(0x01);
	dataBuf[0][6]=(data>>3)&(0x01);
	for(int i=0;i<7;i++)
	{
		for(int k=0;k<3;k++)
		{
			dataBuf[k+1][i]=((i+1)>>k)&(0x01);
		}
	}
	char val[3]={0,0,0};
	for(int k=0;k<3;k++)
	{
		for(int i=0;i<7;i++)
		{
			val[k]+=dataBuf[0][i]*dataBuf[k+1][i];
		}
	}
	res+=(val[0]%2);
	res+=((val[1]%2)<<1);
	res+=(dataBuf[0][2]<<2);
	res+=((val[2]%2)<<3);
  res+=(dataBuf[0][4]<<4);
	res+=(dataBuf[0][5]<<5);
	res+=(dataBuf[0][6]<<6);
	return res;
}

char check_Ham(char data)
{
	char dataBuf[4][7];
	dataBuf[0][0]=data&1;
	dataBuf[0][1]=(data>>1)&1;
	dataBuf[0][2]=(data>>2)&1;
	dataBuf[0][3]=(data>>3)&1;
	dataBuf[0][4]=(data>>4)&1;
	dataBuf[0][5]=(data>>5)&1;
	dataBuf[0][6]=(data>>6)&1;
	for(int i=0;i<7;i++)
	{
		for(int k=0;k<3;k++)
		{
			dataBuf[k+1][i]=((i+1)>>k)&1;
		}
	}
	char val[3]={0,0,0};
	for(int k=0;k<3;k++)
	{
		for(int i=0;i<7;i++)
		{
			val[k]+=(dataBuf[0][i]*dataBuf[k+1][i]);
		}
	}
	return val[0]+((val[1]%2)<<1)+((val[2]%2)<<2);
}

char fix_Ham(char data)
{
	char res=0;
	char val=check_Ham(data);
	if(val==0)
	{
		res+=((data>>2)&1);
	  res+=((data>>4)&1)<<1;
		res+=((data>>5)&1)<<2;
		res+=((data>>6)&1)<<3;
		return res;
	}
	char r=data & (1<<(val-1));
	if(r==0)data+=(1<<(val-1));
	else data-=(1<<(val-1));
	val=check_Ham(data);
	if(val==0)
	{
		res+=((data>>2)&1);
	  res+=((data>>4)&1)<<1;
		res+=((data>>5)&1)<<2;
		res+=((data>>6)&1)<<3;
		return res;
	}
	return 0;
}
