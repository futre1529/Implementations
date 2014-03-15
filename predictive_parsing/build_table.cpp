#include<iostream>
#include"fi_fo.cpp"
#include<conio.h>
using namespace std;


void print_table(string s,int** t)
{
     cout<<s<<endl<<"\t";
     for(int i=0;i<term.size();i++)
     cout<<term[i]<<"\t";
     cout<<endl;
     for(int i=0;i<nterm.size();i++)
     {
             cout<<nterm[i]<<"\t";
             for(int j=0;j<term.size();j++)
             {
                     if(t[i][j]==-1)
                     cout<<"-\t";
                     else        
                     cout<<t[i][j]<<"\t";
             }
             cout<<endl;
     }
}

void create_table(int** &t,vector<prod*>a)
{
     t=new int*[nterm.size()];
     for(int i=0;i<nterm.size();i++)
     {
             t[i]=new int[term.size()];
             for(int j=0;j<term.size();j++)
             t[i][j]=-1;
     }
     
     for(int i=0;i<a.size();i++)
     {
             int pos=find(nterm,a[i]->l);
             if(a[i]->r[0]=='#' || sub_null(a[i]->r,0))
             {
                 for(int j=0;j<follow[pos].size();j++)
                 {
                         int pos1=find(term,follow[pos][j]);
                         t[pos][pos1]=i;
                 }
             }
             else if(find(term,a[i]->r.substr(0,1))!=-1)
             {
                 int pos1=find(term,a[i]->r.substr(0,1));
                 t[pos][pos1]=i;
             }
             else
             {
                 string s1=a[i]->r.substr(0,1);
                 if(a[i]->r.find(s1+"'",0)<a[i]->r.size())
                 s1+="'";
                 if(a[i]->r.find(s1+"`",0)<a[i]->r.size())
                 s1+="`";
                 int pos2=find(nterm,s1);
                 for(int j=0;j<first[pos2].size();j++)
                 {
                         int pos1=find(term,first[pos2][j]);
                         t[pos][pos1]=i;
                 }
             }
     }
}
