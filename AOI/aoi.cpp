#include<iostream>
#include<cstring>
#include<fstream>
#include<set>
#include<iterator>
#include<vector>
#include<conio.h>

using namespace std;

#define n_attributes 7
#define upperlimit 6
#define lowerlimit 3

class name
{
	public:
	string attr [n_attributes];
	friend bool operator<(name const& a,name const& b)
    {
        return (a.attr!=b.attr) > 0;
    }
	name()
	{
		for(int i=0;i<n_attributes;i++)
		{
			attr[i]=" ";
		}
	}
};

string str1[4]={"history","commerce","civics","economics"};
string str2[4]={"CS","civil","electronics","mechanical"};
string str3[4]={"biology","chemistry","physics","geology"};

int check[n_attributes]={0,1,1,1,1,0,1};
int main()
{
	int count=0,total;
	string s;
	ifstream fin;
	fin.open("AOIfile.txt");

	//Count the number of entries in the dataset
	while(fin)
	{
		fin>>s;
		char ch=fin.peek();
		if(ch=='\n')
			count++;
	}
	fin.close();

	set<string> acheck[n_attributes];

	ifstream ifile;
	ifile.open("AOIfile.txt");
	total=count+1;
	string str[total][n_attributes];
	count=0;int i=0;
	while(ifile)
	{
		ifile>>s;
		acheck[i].insert(s);//distinct values only inserted into acheck
		str[count][i++]=s;
		if(ifile.peek()=='\n')
		{
			count++;
			i=0;
		}
	}
	//Loop to check which attributes to take and not to take based on number of distinct values
	for(i=0;i<n_attributes;i++)
	{
		if(acheck[i].size()>=upperlimit)
		{
			if(check[i]==0)
				check[i]=-1;
			else
				check[i]=2;
		}
		else if(acheck[i].size()<=lowerlimit)
		{
			if(check[i]==0)
				check[i]=-1;
		}
		else
		{
			if(check[i]==0)
				check[i]=1;
			else
				check[i]=2;
		}
	}
	int l;
	int j;

	//Mapping of attribute values and insertion into the database
	for(i=0;i<count;i++)
	{
		for(j=0;j<n_attributes;j++)
		{
			if(check[j]==-1 || check[j]==1)
				continue;
			else
			{
				string temp;
				int cnt;
				int val;
				switch(j)
				{
					case 0:
						break;
					case 1:
						break;
					case 2:
						 temp=str[i][j];
						 for(l=0;l<4;l++)
						 {
						 	if(temp==str1[l])
						 	{
						 		str[i][j]="Arts";
						 		break;
						 	}
						 	else if(temp==str2[l])
						 	{
						 		str[i][j]="Engineering";
						 		break;
						 	}
						 	else if(temp==str3[l])
						 	{
						 		str[i][j]="Science";
						 		break;
						 	}
						 }
						 break;
					case 3:
						cnt=0;
						temp=str[i][j];
						for(l=0;l<temp.length();l++)
						{
								if(temp[l]==',')cnt++;
								if(cnt==2)break;
						}
						temp=temp.substr(l+1);
						str[i][j]=temp;
						break;
					case 4:
						cnt=0;
						temp=str[i][j];
						for(l=0;l<temp.length();l++)
						{
								if(temp[l]=='-')cnt++;
								if(cnt==2)break;
						}
						temp=temp.substr(l+1);
						val=0;
						for(l=0;l<temp.length();l++)
							val=(val*10)+(temp[l]-'0');
						if(2013-val>30)str[i][j]="above 30";
						else if(2013-val>=25)str[i][j]="between 25-30";
						else str[i][j]="below 25";
						break;
					case 5:
						break;
					case 6:
						temp=str[i][j];
						if(temp[0]=='7')
							str[i][j]="Good";
						else if(temp[0]=='8')
							str[i][j]="Very-Good";
						else if(temp[0]=='9')
							str[i][j]="Excellent";
						else
							str[i][j]="Unsatisfactory";
						break;
				}
			}
		}
	}

	vector<name> fcheck;
	for(i=0;i<count;i++)
	{
		name temp;
		for(j=0;j<n_attributes;j++)
		{
			if(check[j]==-1)continue;
			temp.attr[j]=str[i][j];
			if((j==2 || j==4) && str[i][j].length()<10)
                cout<<"\t";
		}
		fcheck.push_back(temp);
		cout<<endl;
	}

	int len=fcheck.size();
	for(i=0;i<len-1;i++)
	{
		name temp1=fcheck[i];
		for(j=i+1;j<len;)
		{
			int flag=0;
			name temp2=fcheck[j];
			for(int m=0;m<n_attributes;m++)
			{
				if(temp1.attr[m]!=temp2.attr[m])
				{
					flag=1;
					break;
				}
			}
			if(flag==0)
			{
				for(int k=j;k<len-1;k++)
					fcheck[k]=fcheck[k+1];
				len-=1;
			}
			else j++;
		}
	}
	cout<<"\n\nPrinting after removal with new number of entries = "<<len<<endl<<endl;
	for(i=0;i<len;i++)
	{
		name temp=fcheck[i];
		for(j=0;j<n_attributes;j++)
		{
			if(check[j]==-1)continue;
			cout<<temp.attr[j]<<"\t";
			if((j==2 || j==4) && temp.attr[j].length()<8)
				cout<<"\t";
		}
		cout<<endl;
	}
	system("pause");
}
