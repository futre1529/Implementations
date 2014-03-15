#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
#include<conio.h>
#include<fstream>
using namespace std;

struct prod
{
       string r,l;
       prod(string l1,string r1)
       {
                 l=l1;r=r1;
       }
};

int find(vector<string>a,string s)
{
    for(int i=0;i<a.size();i++)
    if(a[i]==s)
    return i;
    return -1;
}


int find(vector<prod*>a,string s,int j)
{
    for(int i=j;i<a.size();i++)
     if(a[i]->l==s)
     return i;
     return -1;
}


void update(prod*a,vector<string>&b,vector<string>&c)
{
    for(int i=0;i<a->r.size();i++)
    {
            char l=a->r[i];
            if((l<'A' || l>'Z') && find(c,a->r.substr(i,1))==-1)
            c.push_back(a->r.substr(i,1));
    }
}

void openfile(char* name,vector<prod*>&a,vector<string>&b,vector<string>&c)
{
     ifstream in;
     in.open(name,ios::in);
     if(!in.is_open())
     {
           cout<<"ERROR:Opening input file...\n";
           cout<<"Either file name or path specified is incorrect...\n";
           getch();
          exit(1);
     }
     
     int i=1;
     while(!in.eof())
     {
         string s;
         getline(in,s,'\n');
         if(s.size()==0)
         break;
         if(s.find("->")!=1)
         {
              cout<<"ERROR:Grammer production of line no:"<<i<<endl;
              getch();
              exit(1);
         }
         int i1=3;
         if(find(b,s.substr(0,1))==-1)
         b.push_back(s.substr(0,1));
             
         while(i1<s.size())
         {
              int pos=s.find("|",i1);
              if(pos>s.size())
              pos=s.size();
              a.push_back(new prod(s.substr(0,1),s.substr(i1,pos-i1)));
              update(a[a.size()-1],b,c);
              i1=pos+1;
         }
     } 
}

