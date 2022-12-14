#include<iostream>
using namespace std;
int main()
{
	int a1,a2,b1,b2;
	
	//1 输入 
	cin>>a1>>a2;
	int a[100][100];
	for(int i=0;i<a1;i++)
	{
		for(int j=0;j<a2;j++)
		{
			cin>>a[i][j];
		}
	}
	
	cin>>b1>>b2;
	int b[100][100];
	for(int i=0;i<b1;i++)
	{
		for(int j=0;j<b2;j++)
		{
			cin>>b[i][j];
		}
	}
	
	//2 判断
	if(a2==b1) 
	{
		int c[100][100];//a1==c1,b2==c2;
		for(int i=0;i<a1;i++)
		{						
			for(int j=0;j<b2;j++)
			{
				c[i][j]=0;
				for(int k=0;k<a2;k++)//a2==b1
				{
					c[i][j]=c[i][j]+a[i][k]*b[k][j];
				}
			}
		}
		
		//3 输出 
		cout<<a1<<" "<<b2<<endl;
		for(int i=0;i<a1;i++)
		{
			for(int j=0;j<b2;j++)
			{
				cout<<c[i][j];
				if(j!=b2-1)  cout<<" ";
			}
			if(i!=a1-1) cout<<endl;
			
		}	
	}
	
	
	
	else{
		cout<<"Error: "<<a2<<" != "<<b1;
	}
	return 0;
}
