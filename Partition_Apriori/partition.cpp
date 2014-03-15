#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<conio.h>
float minsup;
int tc;
using namespace std;
//vert is the structure containing items and their transaction ids ,ids in vector h1 and items in s[] and item count in s1
struct vert
{
       int *s;
       int s1;
       int ct;
       vert(int n)
       {
       		  ct=0;
              s1=n;
              s=new int[n];//n signifies n-itemset
       }
       vector<int> h1;
};
//vv is a 2-D array containg all 1 ,2 , 3 or n items with their transation ids
vector <vector<vert*> >vv;
vector <vector<vert*> >vv1;
vector<vert*> temp;
//srch for 1st iteraion ,inserting items in vector and if trancation id related to that item than increase count nd insert transaction id
void srch(vector<int>&a,vector<vert*>& h2,int p)
{
     int j1;
     if(h2.size()==0)
     {
          vert *n2=new vert(a.size());
          for(int i=0;i<a.size();i++)
          n2->s[i]=a[i];
          (n2->h1).push_back(p);
          h2.push_back(n2);
     }
     else
     {
     for(int i=0;i<h2.size();i++)
     {
             j1=0;
             for(int j=0;j<a.size();j++)
             {
                     if(h2[i]->s[j]!=a[j])
                     {
                     j1=1;
                     j=a.size();
                     }
             }
             if(j1==0)
             {
			 (h2[i]->h1).push_back(p);i=h2.size();
             }
     }
     if(j1==1)
     {
              vert *n2=new vert(a.size());
              for(int i=0;i<a.size();i++)
              n2->s[i]=a[i];
              (n2->h1).push_back(p);
              h2.push_back(n2);
     }
     }
}
vector<vert*> b2;
//if k-1 elements are same than return 1
int mtch(int p1,int p2,int p3)
{
     int t1=0,t2=1;
     while(t1<((vv[p3-2][p1]->s1)-1))
     {         if(vv[p3-2][p1]->s[t1]!=vv[p3-2][p2]->s[t1])
               {
                    t2=0;
                    t1=vv[p3-2][p1]->s1;
               }
               else
               t1++;
     }
     return t2;
}

void join1(int order)
{
     int x1;
     for(int i=0;i<vv[order-2].size()-1;i++)
     {
             for(int j=i+1;j<vv[order-2].size();j++)
             {
                     vert *xx;
                     if(mtch(i,j,order))
                    {
                                       xx=new vert(vv[order-2][i]->s1+1);
                                       for(x1=0;x1<vv[order-2][i]->s1-1;x1++)
                                       {
                                               xx->s[x1]=vv[order-2][i]->s[x1];
                                       }
                                       xx->s[x1++]=vv[order-2][i]->s[vv[order-2][i]->s1-1];
                                       xx->s[x1]=vv[order-2][j]->s[vv[order-2][j]->s1-1];
                    int p=0,q=0;
                    while(p <((vv[order-2][i]->h1).size())&&q <((vv[order-2][j]->h1).size()))
                    {
                          if(vv[order-2][i]->h1[p]<vv[order-2][j]->h1[q])
                          p++;
                          else if(vv[order-2][i]->h1[p]>vv[order-2][j]->h1[q])
                          q++;
                          else
                          {
                               if(vv[order-2][i]->h1[p]==vv[order-2][j]->h1[q])
                               {
                                   (xx->h1).push_back(vv[order-2][i]->h1[p]);
                                   p++;q++;
                               }
                          }
                    }
                    temp.push_back(xx);
             }
             }
     }
}
void last(vector<int> f1,int x2)
{
	int cc;
	for(int p=0;p <x2;p++)
           {
                   for(int i=0;i<vv1[p].size();i++)
                   {cc=0;
                   	for(int j=0;j<f1.size();j++)
                   	{
                   		if(vv1[p][i]->s[cc]==f1[j])
                   		cc++;
                   	}
                   	if(cc==vv1[p][i]->s1)
                   	vv1[p][i]->ct++;
                	}
                   }


}
int main()
{
	int x2=0;
          cout<<"enter minsup:\n";
          cin>>minsup;
          ifstream fin("partition.txt");
          int m=0;
          char ch;
          int p,q=0;
          int *p1;
           vector<vert*> h2;
          p1=new int[1];
          p1[0]=1;vector<int>f1;
          while(!fin.eof())
          {
                    ch=fin.get();
                    p=ch;
                    if(ch!='\n'&&(p>=48&&p<=57))
                    {
                                                p1[0]=p-48;
                                              f1.push_back(p1[0]);
                                               srch(f1,h2,q);
                                                f1.clear();
                    }
                    else if(ch=='\n')
                    {
                    	q++;
                    	if(q%3==0)
                    	{
                    	    /*swapping loop to arrange the items in order*/
                    		for(int i=0;i<h2.size()-1;i++)
          					{
                 				 for(int j=i+1;j<h2.size();j++)
                  					{
                          			if(h2[i]->s[0]>h2[j]->s[0])
                          			swap(h2[i],h2[j]);
                  					}
          					}
          					/*loop for removing infrequent items*/
           					for(int i=0;i<h2.size();i++)
           					{
                   				if(float((h2[i]->h1).size())<(minsup*3))
                   				{
                                          h2.erase(h2.begin()+i);
                                          i--;
                   				}
           					}

          				vv.push_back(h2);
          				int ori=2;
         				h2.clear();
         				while(vv[ori-2].size())
          				{
          					join1(ori);cout<<"\n";
           					for(int i=0;i<temp.size();i++)
           					{
                   				if(float((temp[i]->h1).size())<(minsup))
                   				{
                                          temp.erase(temp.begin()+i);
                                          i--;
                   				}
           					}
          					vv.push_back(temp);cout<<"after  "<<(ori-2)<<"\n";
                   for(int i=0;i<vv[ori-2].size();i++)
                   {
                    for(int j=0;j<vv[ori-2][i]->s1;j++)
                    cout<<vv[ori-2][i]->s[j]<<"  ";
                    //cout<<vv[ori-2][i]->ct<<"   ";
                    cout<<"\n";
                   }
                   cout<<"\n\n";

           					ori++;
           					temp.clear();
           				}
						if(x2==0)
						{
							for(int i=0;i<ori-2;i++)
							vv1.push_back(vv[i]);
							x2=ori-2;
			 				vv.clear();
						}
						else
						{
							if((ori-2)>x2)
							{
								for(int i=x2;i<ori-2;i++)
								vv1.push_back(vv[i]);
								x2=ori-2;
							}
							for(int i=0;i<ori-2;i++)
							{
							int x3;
								for(int j=0;j<vv[i].size();j++)
								{
									for(int k1=0;k1<vv1[i].size();k1++)
									{
										x3=0;
										for(int k=0;k<vv[i][j]->s1;k++)
										{
											if(vv[i][j]->s[k]!=vv1[i][k1]->s[k])
											{
												x3=1;
											}
										}
										if(x3==0)
										k1=vv1[i].size();
									}
									if(x3==1)
									vv1[i].push_back(vv[i][j]);
								}
							}
						vv.clear();
						}
					}
                    }
          }
          fin.close();
           for(int p=0;p <x2;p++)
           {
                   cout<<"\n\n";
           }
           ifstream fin1("partition.txt");
           while(!fin1.eof())
          {
                    ch=fin1.get();
                    p=ch;
                    if(ch!='\n'&&(p>=48&&p<=57))
                    {
                                                p1[0]=p-48;
                                              f1.push_back(p1[0]);
                    }
                    else if(ch=='\n')
                    {

                    							last(f1,x2);
                        						f1.clear();
                	}
          }
          fin1.close();
  getch();
  return 0;
}
