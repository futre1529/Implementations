//clustering method
#include<iostream>
using namespace std;
int n,k;
struct point
{
	double x,y;
};
double finddis(point* a,point* b)
{
	double m=(a->x-b->x)*(a->x-b->x)+(a->y-b->y)*(a->y-b->y);
	return m;
}
struct cluster
{
	point *m;
	point** ob;
	int count;
	cluster(int n)
	{
		m=new point();
		ob=new point*[n];
		count=0;
	}
	void add(point* x)
	{
		ob[count++]=x;
	}
};
int print(cluster* c[]);
void fillcluster(cluster* c[],point* x[])
{
	for(int i=0;i<n;i++)
	{
		double l=1000;
		int index=0;
		for(int j=0;j<k;j++)
		{
			point *a,*b;
			a=c[j]->m;b=x[i];
			if(finddis(a,b)<l)
			{
				l=finddis(a,b);
			 	index=j;
			}
		}
		c[index]->add(x[i]);
	}
	print(c);
}
point* avg(point* ob[],int count)
{
	double x=0,y=0;
	for(int i=0;i<count;i++)
	{
		x+=ob[i]->x;
		y+=ob[i]->y;
	}
	point* z;
	z=new point();
	z->x=x/count;
	z->y=y/count;
	return z;
}
int print(cluster* c[])
{	
	static int x=1;
	cout<<"\n\nafter "<<x<<" iteration\n";
	for(int i=0;i<k;i++)
	{
		cout<<"\nIn "<<" cluster "<<i+1<<endl;
		cout<<"center point "<<" ("<<c[i]->m->x<<","<<c[i]->m->y<<")\n";
		for(int j=0;j<c[i]->count;j++)
		{
			cout<<" ("<<c[i]->ob[j]->x<<","<<c[i]->ob[j]->y<<") ,";
		}
		cout<<endl;
	}
	x++;
	cout<<endl<<endl;
	return 0;
}
void makecluster(cluster* c[],point* x[])
{
	cluster *d[k];
	for(int i=0;i<k;i++)
	d[i]=new cluster(n);
	for(int i=0;i<k;i++)
	{
		d[i]->m=avg(c[i]->ob,c[i]->count);
	}
	fillcluster(d,x);
	int flag=0;
	for(int i=0;i<k;i++)
	{
		if(!((d[i]->m->x==c[i]->m->x)&&(d[i]->m->y==c[i]->m->y)))
		flag=1;
	}
	
	if(flag==0)
	return;
	else
	{
		makecluster(d,x);
	}
}
int main()
{
	cout<<"enter no of data objects and clusters : \n";
	cin>>n>>k;
	point* x[n];
	cluster *c[k];
	for(int i=0;i<k;i++)
	c[i]=new cluster(n);
	for(int i=0;i<n;i++)
	{
		x[i]=new point();
		cin>>x[i]->x>>x[i]->y;
	}
	for(int i=0;i<k;i++)
	{
		c[i]->m=x[i];
	}
	fillcluster(c,x);
	makecluster(c,x);
}
/*
8  3
-1	 -1
0	 3
1	 2.5
2	 5
3	 4
5	 2
7	 5
9	 4
*/
