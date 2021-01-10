#include<iostream>
#include<conio.h>
#include <stdlib.h> 
#include<time.h>
using namespace std;
int data[4][4];
int data_old[4][4];
int Times=0;
int Maxscore=0;
void copyData()
{
	int i,j;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			data_old[i][j]=data[i][j];

}
int compareData()
{
	int i,j;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			if(data_old[i][j] != data[i][j])return 0; 
	return 1; 
}
int getEmptyNum()
{
	int i,j,n=0;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			if(data[i][j]==0)
				n++;
	return n;
}
void putNewNum()
{
	int i,j,c=0;
	c=1+rand()%getEmptyNum();
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			if(data[i][j]==0)
			{
				c--;
				if(c==0)
					data[i][j]=2;
			}	
}
void printLine(int L)
{
	int i=0;

	for(i=0;i<4;i++)
	{
		cout<<"│";
		if(data[L][i]==0)cout<<"\t";
		else cout<<data[L][i]<<"\t";
	}
	cout<<"│"<<endl;
}
void printMap()
{
	cout<<"┌-------┬-------┬-------┬-------┐"<<endl;
	printLine(0);
	cout<<"├-------┼-------┼-------┼-------┤"<<endl;
	printLine(1);
	cout<<"├-------┼-------┼-------┼-------┤"<<endl;
	printLine(2);
	cout<<"├-------┼-------┼-------┼-------┤"<<endl;
	printLine(3);
	cout<<"└-------┴-------┴-------┴-------┘"<<endl;
	cout<<"分數："<<Maxscore<<endl;
	cout<<"操作次數："<<Times<<endl;
	cout<<"剩餘空間："<<getEmptyNum()<<endl;
}
int moveUP()
{
	int i,j;
	int m=0,n=0;
	int point[8]={0};
	int count=0;
	int total=0;
	for(i=0;i<4;i++)
	{
		
		j=0;n=0;		 
		while(n<3 && j<3)
		{
			if(data[j][i]==0)   
			{
				for(m=j;m<3;m++)
					data[m][i]=data[m+1][i];	
				data[3][i]=0;	
				n++;			
				
			}else j++; 
		}

		
		for(j=0;j<3;j++)
			if(data[j][i]==data[j+1][i] && data[j][i]!=0)
			{											 
				data[j][i]=data[j][i]*2;
				point[count]=data[j][i];
				count++;
				data[j+1][i]=0;			
			}
		
		j=0;n=0;
		while(n<3 && j<3)
		{
			if(data[j][i]==0)
			{
				for(m=j;m<3;m++)
					data[m][i]=data[m+1][i];	
				data[3][i]=0;
				n++;	
			}else j++;
		}
	}
	for(int i=0;i<8;i++)
	{
		total+=point[i];
	}
	return total;
}

int moveDOWN()
{
	int i,j;
	int m=0,n=0;
	int point[8]={0};
	int count=0;
	int total=0;
	for(i=0;i<4;i++)
	{
		
		j=3;n=0;
		while(n<3 && j>0)
		{
			if(data[j][i]==0)
			{
				for(m=j;m>0;m--)data[m][i]=data[m-1][i];	
				data[0][i]=0;
				n++;	
			}else j--;
		}

		for(j=3;j>0;j--)
			if(data[j][i]==data[j-1][i] && data[j][i]!=0)
			{
				data[j][i]=data[j][i]*2;
					point[count]=data[j][i];
					count++;
				data[j-1][i]=0;			
			}
		
		j=3;n=0;
		while(n<3 && j>0)
		{
			if(data[j][i]==0)
			{
				for(m=j;m>0;m--)data[m][i]=data[m-1][i];	
				data[0][i]=0;
				n++;	
			}else j--;
		}
	}
	for(int i=0;i<8;i++)
	{
		total+=point[i];
	}
	return total;
}

int moveLEFT()
{
	int i,j;
	int m=0,n=0;
	int point[8]={0};
	int count=0;
	int total=0;
	for(i=0;i<4;i++)
	{
		
		j=0;n=0;
		while(n<3 && j<3)
		{
			if(data[i][j]==0)
			{
				for(m=j;m<3;m++)data[i][m]=data[i][m+1];	
				data[i][3]=0;
				n++;	
			}else j++;
		}
		
		for(j=0;j<3;j++)
			if(data[i][j]==data[i][j+1] && data[i][j]!=0)
			{
				data[i][j]=data[i][j]*2;
					point[count]=data[i][j];
					count++;
				data[i][j+1]=0;		
			}
		
		j=0;n=0;
		while(n<3 && j<3)
		{
			if(data[i][j]==0)
			{
				for(m=j;m<3;m++)data[i][m]=data[i][m+1];	
				data[i][3]=0;
				n++;	
			}else j++;
		}
	}
	for(int i=0;i<8;i++)
	{
		total+=point[i];
	}
	return total;
}

int moveRIGHT()
{
	int i,j;
	int m=0,n=0;
	int point[8]={0};
	int count=0;
	int total=0;
	for(i=0;i<4;i++)
	{
		
		j=3;n=0;
		while(n<3 && j>0)
		{
			if(data[i][j]==0)
			{
				for(m=j;m>0;m--)data[i][m]=data[i][m-1];	
				data[i][0]=0;
				n++;	
			}else j--;
		}
		
		for(j=3;j>0;j--)
			if(data[i][j]==data[i][j-1] && data[i][j]!=0)
			{
				data[i][j]=data[i][j]*2;
					point[count]=data[i][j];
					count++;
				data[i][j-1]=0;			
			}
		
		j=3;n=0;
		while(n<3 && j>0)
		{
			if(data[i][j]==0)
			{
				for(m=j;m>0;m--)data[i][m]=data[i][m-1];	
				data[i][0]=0;
				n++;	
			}else j--;
		}
	}
	for(int i=0;i<8;i++)
	{
		total+=point[i];
	}
	return total;
}
int isGameover()
{
	int i,j;
    for(i=0;i<4;++i)
	{
        for(j=0;j<4;++j)
		{
            if(data[i][j]==0)
                return 0;
            if(i>0)
			{
                if(data[i-1][j]==data[i][j])
                    return 0;
            }
            if(j>0)
                if(data[i][j-1]==data[i][j])
                    return 0;
        }
    }
    return 1;
}
int main()
{
	int ch;
	srand(time(NULL));
    putNewNum();
	putNewNum();
	copyData(); 
	printMap(); 
	while( (ch=getch())!='Q')
    { 	
		  switch(ch)
		  {
		  case 224:
			 switch(ch=getch())
			 {
				case 72:Maxscore+=moveUP(); break;
				case 80:Maxscore+=moveDOWN(); break;
				case 75:Maxscore+=moveLEFT(); break;
				case 77:Maxscore+=moveRIGHT(); break;
				default:
				   break;
			 }
			 if(compareData()==0)
			 {
				putNewNum();  
				copyData();   
				Times++;	  
				
			 }
			 system("cls");  
			 printMap();	 	
			 if(isGameover())cout<<"遊戲結束,按Q退出"<<endl;
			 
			 break;
		  default:break;
		  }	
	 }
} 

