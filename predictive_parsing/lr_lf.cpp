#include<iostream>
#include<vector>
#include<cstdlib>
#include<conio.h>
#include"p1.cpp"
using namespace std;

void sort(vector<prod*>&a)
{
     for(int i=0;i<a.size();i++)
     for(int j=0;j<a.size();j++)
     if(a[i]->l<a[j]->l)
     swap(a[i],a[j]);
}

void print(string s,vector<string> a)
{
     cout<<s<<endl;
     for(int i=0;i<a.size();i++)
     cout<<a[i]<<",";
     cout<<"\b\n";
}

void print(string s,vector<prod*> a)
{
     cout<<s<<endl;
     for(int i=0;i<a.size();i++)
     cout<<a[i]->l<<"->"<<a[i]->r<<endl;
     cout<<endl;
}

//to remove immediate left recursion;
void immlrec(vector<prod*>&a,int i1,vector<string>&b)
{
     vector<prod*>ok,ilr;
     string s=a[i1]->l;
     for(int i=i1;i<a.size();i++)
     {
       if(a[i]->l!=s)
       break;
       else if(a[i]->l==a[i]->r.substr(0,1))
       ilr.push_back(a[i]);
       else
       ok.push_back(a[i]);
     }
     if(ilr.size()>0)
     {
        for(int i=0;i<ok.size();i++)
           ok[i]->r+=ok[i]->l+"`";
        for(int i=0;i<ilr.size();i++)
        {
                ilr[i]->l+="`";
                ilr[i]->r=ilr[i]->r.substr(1,ilr[i]->r.size());
                ilr[i]->r+=ilr[i]->l;
        }
        a.insert(a.begin()+i1,new prod(ilr[0]->l,"#"));
        b.push_back(ilr[0]->l);
     }
}

//to remove left recursion;
void remove_leftrecursion(vector<prod*>&a,vector<string>&b)
{
     for(int i=0;i<b.size();i++)
     {
             for(int j=0;j<i;j++)
             {
                  int pos=find(a,b[i],0);       
                  while(pos!=-1)
                  {
                      string s=a[pos]->r.substr(0,1);
                      if(s==b[j])
                      {
                           int pos1=find(a,b[j],0);
                           vector<string>temp;
                           while(pos1!=-1)
                           {
                              temp.push_back(a[pos1]->r);
                              pos1=find(a,b[j],pos1+1);
                           }
                           prod* t=a[pos];
                           t->r=t->r.substr(1,t->r.size());
                           a.erase(a.begin()+pos);
                           for(int k=0;k<temp.size();k++)
                           a.insert(a.begin()+pos,new prod(t->l,temp[k]+t->r));
                      }
                      pos=find(a,b[i],pos+1);
                  }
             }
             immlrec(a,find(a,b[i],0),b);
     }
}

//to find the same prefix of two strings;
string prefix(string s1,string s2)
{
       int i1=min(s1.size(),s2.size());
       string s;
       for(int i=0;i<i1;i++)
       {
               if(s1[i]==s2[i])
               s+=s1[i];
               else
               break;
       }
       return s;
}

//to introduce left factoring;
void leftfactoring(vector<prod*>&a,vector<string>&b)
{
     for(int i=0;i<a.size();i++)
     {
             bool flag=true;
             string s2;
             for(int j=i+1;j<a.size();j++)
             {
                     if(a[i]->l!=a[j]->l)
                     {
                         i=j;
                         break;
                     }
                     else if(a[i]->l==a[j]->l && a[i]->r[0]==a[j]->r[0])
                     {
                         string s=prefix(a[i]->r,a[j]->r),s1;
                         s2=a[j]->r.substr(s.size(),a[j]->r.size());
                         if(flag)
                         {
                                 s1=a[i]->r.substr(s.size(),a[i]->r.size());
                                 a[i]->r=s+a[i]->l+"'";
                         }
                         a[j]->l+="'";
                         a[j]->r=s2;
                         if(flag)
                         {
                                 a.insert(a.end(),new prod(a[i]->l+"'",s1));
                                 b.push_back(a[i]->l+"'");
                         }
                         flag=0;
                     } 
             }
     }
}
