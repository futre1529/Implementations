#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
#include<conio.h>
#include<fstream>
using namespace std;

struct prod
{
       char l;
       string r;
       prod(char l1,string r1)
       {
                 l=l1;r=r1;
       }
};



void openfile(char * name,vector<prod*>&a)
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
         while(i1<s.size())
         {
              int pos=s.find("|",i1);
              if(pos>s.size())
              pos=s.size();
              a.push_back(new prod(s[0],s.substr(i1,pos-i1)));
              i1=pos+1;
         }
     }
}


bool is_cyk(vector<prod*>&a)
{
     bool flag=1;
     for(int i=0;i<a.size();i++)
     {
             int s=a[i]->r.size();
             if(s>2 || s==0 || (s==1 && isupper(a[i]->r[0])))
             {
                  cout<<"Production "<<a[i]->l<<"->"<<a[i]->r<<" not in cnf\n";
                  flag=0;
             }
             else if(s==2)
             {
                  for(int i1=0;i1<2;i1++)
                  if(!isupper(a[i]->r[i1]))
                  {
                     cout<<"Production "<<a[i]->l<<"->"<<a[i]->r<<" not in cnf\n";
                     flag=0;
                     break;
                  }
             }
     }
     return flag;
}
