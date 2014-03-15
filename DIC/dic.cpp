#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<conio.h>
using namespace std;
int minsup,par;
struct item
{
	int tc;
	int ic;
	int ori;
	int *a;
	item(int n)
	{
		ori=n;
		a=new int[n];
		tc=0;
		ic=0;
	}
};

vector<item*> v;
vector<item*> v1;
vector<item*> v2;
vector<item*> v3;

void print(vector<item*> &m)
{
	for(int i=0;i<m.size();i++)
	{
		for(int j=0;j<m[i]->ori;j++)
		cout<<m[i]->a[j]<<"   ";
		cout<<"\n";
	}
    cout<<"\n";
}

//considered all 1-itemsets in v  with 0 count
void dash(vector<item*> vv,vector<int> f1)
{
    int x;
	for(int i=0;i<vv.size();i++)
	{
        x=0;
        for(int k=0;k<f1.size();k++)
        {
            if(vv[i]->a[x]==f1[k])
            x++;
        }
        if(x==vv[i]->ori)
        vv[i]->ic++;
    }
}

void srch(vector<int> f1)
{
	dash(v,f1);
	dash(v1,f1);
}

int check1(vector<item*> b1,item *h)
{
	int y=0,y1;
	for(int i=0;i<b1.size();i++)
	{
		if(b1[i]->ori==h->ori)
		{
		    y1=0;
			for(int j=0;j<h->ori;j++)
			{
				if(b1[i]->a[j]!=h->a[j])
				{
					y1=1;
					j=h->ori;
				}
			}
		}
		if(y1==0)
		y=1;
	}
	if(y==1)
	return 0;
	else
	return 1;
}

//whether item is already in dc or ds
int check(item *h)
{
	int y=0,y1;
	for(int i=0;i<v.size();i++)
	{
		if(v[i]->ori==h->ori)
		{
		    y1=0;
			for(int j=0;j<h->ori;j++)
			{
				if(v[i]->a[j]!=h->a[j])
				{
					y1=1;
					j=h->ori;
				}
			}
		}
		if(y1==0)
		y=1;
	}
	if(y==1)
	return 0;
	else
	{
		for(int i=0;i<v1.size();i++)
        {
            if(v1[i]->ori==h->ori)
            {   y1=0;
                for(int j=0;j<h->ori;j++)
                {
                    if(v1[i]->a[j]!=h->a[j])
                    {
                        y1=1;
                        j=h->ori;
                    }
                }
            }
            if(y1==0)
            y=1;
        }
        if(y==1)
        return 0;
        else
        return 1;
    }

}
void sort1(item* &m2)
{
	for(int i=0;i<(m2->ori)-1;i++)
	{
		for(int j=i+1;j<m2->ori;j++)
		{
			if(m2->a[i]>m2->a[j])
			swap(m2->a[i],m2->a[j]);
		}
	}
}
int mtch(item *a1,item *b1)
{
	int x1=0;item *c;//2 itemsets a and b are having k-1 equal or not
	for(int i=0;i<(a1->ori)-1;i++)
	{
		if(a1->a[i]!=b1->a[i])
		x1=1;
	}
	//if equal than join
	if(x1==0)
	{
		int x2,x3=0,x4;
		item *c;
		c=new item(a1->ori+1);int i;
		for(i=0;i<a1->ori;i++)
		c->a[i]=a1->a[i];
		c->a[i]=b1->a[b1->ori-1];
		sort1(c);

		if(check(c))
		{
            int w[(c->ori)-1];
            for(int i=0;i<c->ori;i++)
            {
                x2=0;
                for(int j=0;j<c->ori;j++)
                {
                    if(i!=j)
                    {
                        w[x2++]=c->a[j];
                    }
                }
                for(int p=0;p<v1.size();p++)
                {
                    x4=0;
                    if(v1[p]->ori==x2)
                    {
                        for(int q=0;q<x2;q++)
                        {
                            if(v1[p]->a[q]!=w[q])
                                x4=1;
                        }
                    }
                    if(x4==0)
                    {
                        x3++;p=v1.size();
                    }
                }
            }
            if(x3==c->ori)
                v.push_back(c);

        }
	}
}

void sort(vector<item*> &m1)
{
	for(int i=0;i<m1.size()-1;i++)
	{
		for(int j=i+1;j<m1.size();j++)
		{
			if(m1[i]->ori==1&&m1[j]->ori==1)
			{
				if(m1[i]->a[0]>m1[j]->a[0])
				{
					swap(m1[i],m1[j]);
				}
			}
		}
	}
}


void dic()
{
	for(int i=0;i<v.size();i++)
        v[i]->tc++;
	for(int i=0;i<v1.size();i++)
        v1[i]->tc++;
	for(int i=0;i<v.size();i++)
	{
		if(v[i]->ic>=minsup)
		{
			v1.push_back(v[i]);
			v.erase(v.begin()+i);
			i--;
		}
	}

	if(v1.size())
	{
        for(int i=0;i<v1.size()-1;i++)
        {
            for(int j=i+1;j<v1.size();j++)
            {
                if(v1[i]->ori==v1[j]->ori)
                {
                    (mtch(v1[i],v1[j]));
                }
            }
        }
	}

	if(v1.size()!=0&&v3.size()!=0)
	{
        for(int i1=0;i1<v1.size();i1++)
        {
            for(int j1=0;j1<v3.size();j1++)
            {
                if(v1[i1]->ori==2&&v3[j1]->ori==2)
                {
                    (mtch(v1[i1],v3[j1]));
                }
            }
        }
    }

	for(int i=0;i<v1.size();i++)
	{
		if(v1[i]->tc==par)
		{
			v3.push_back(v1[i]);
			v1.erase(v1.begin()+i);
			i--;
		}
	}

	for(int i=0;i<v.size();i++)
	{
		if(v[i]->tc==par)
		{
			v2.push_back(v[i]);
			v.erase(v.begin()+i);
			i--;
		}
	}
}

int main()
{
    cout<<"enter minsup:\n";
    cin>>minsup;
    char ch;
    int p,q;
    cin>>par;
    for(int i=0;i<5;i++)
    {
        item *kk;
        kk=new item(1);
        kk->a[0]=i+1;
        v.push_back(kk);
    }
    vector<int> f1;

    while(v.size()!=0||v1.size()!=0)
    {
        ifstream fin("DIC.txt");q=0;
        while(!fin.eof())
        {
            ch=fin.get();
            p=ch;
            if(ch!='\n'&&(p>=48&&p<=57))
            {
                f1.push_back((p-48));
            }
            else if(ch=='\n')
            {
                q++;
                srch(f1);
                f1.clear();
                if(q%par==0)
                {
                    dic();
                    print(v);
                }
            }
        }
        fin.close();
    }

    for(int i=0;i<v1.size();i++)
        v3.push_back(v1[i]);
    getch();
    return 0;
}
