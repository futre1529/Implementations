#include<iostream>
#include"fi_fo.cpp"
#include<vector>
using namespace std;

struct aaa
{
       char c;
       int i;
       aaa(char c1)
       {
       c=c1;i=-1;
       }
};

vector < vector<aaa*> >gt;

struct can
{
       prod* p;
       int dot;
       can(prod* p1,int d)
       {
           p=p1;dot=d;
       }
};


int find(vector<can*>&c,can* p1)
{
    for(int i=0;i<c.size();i++)
    if(c[i]->p==p1->p && c[i]->dot==p1->dot)
    return i;
    return -1;
}

int find(vector<aaa*>&c,aaa* p1)
{
    for(int i=0;i<c.size();i++)
    if(c[i]->c==p1->c && c[i]->i==p1->i)
    return i;
    return -1;
}

int find(vector<aaa*>&c,char p1)
{
    for(int i=0;i<c.size();i++)
    if(c[i]->c==p1)
    return i;
    return -1;
}

int find(vector<prod*>c,prod*key)
{
    for(int i=0;i<c.size();i++)
    if(c[i]==key)
    return i;
    return -1;

}

//to check if two sets are equal or not;
bool is_same(vector<can*>&a,vector<can*>&b)
{
     if(a.size()!=b.size())
     return false;
     else
     {
         for(int i=0;i<a.size();i++)
         if(find(b,a[i])==-1)
         return false;
     }
     return true;
}

int find(vector<vector<can*> >c,vector<can*>key)
{
    for(int i=0;i<c.size();i++)
    if(is_same(c[i],key))
    return i;
    return -1;

}

//to print all the sets;
void print(string s,vector<vector<can*> >c)
{
     cout<<s<<endl;
     for(int i=0;i<c.size();i++)
     {
             cout<<"\nSET("<<i<<"):\n";
             for(int j=0;j<c[i].size();j++)
             {
                     string s=c[i][j]->p->r;
                     s=s.substr(0,c[i][j]->dot)+"."+s.substr(c[i][j]->dot,s.size());
                     cout<<c[i][j]->p->l<<"->"<<s<<endl;
             }
             for(int j=0;j<gt[i].size();j++)
             cout<<"goto(I"<<i<<","<<gt[i][j]->c<<")=I"<<gt[i][j]->i<<endl;
     }
}    

//to find the cover of a set;
void cover(vector<can*>&c,vector<prod*>a)
{
     for(int i=0;i<c.size();i++)
     {
             int pos=c[i]->dot;
             if(isupper(c[i]->p->r[pos]))
             {
                    string s=c[i]->p->r.substr(pos,1);
                    int j1=find(a,s,0);
                    while(j1!=-1)
                    {
                         can* temp=new can(a[j1],0);
                         if(find(c,temp)==-1)
                         c.push_back(temp);
                         j1=find(a,s,j1+1);
                    }                     
             }
     }
}

//to find goto of a set on symbol s;
vector<can*> goto1(vector<can*>&c,vector<prod*>a,char s)
{
             vector<can*>temp;
             for(int i=0;i<c.size();i++)
             {
                     prod* t=c[i]->p;
                     int dot=c[i]->dot;
                     if(t->r[dot]==s)
                     temp.push_back(new can(t,dot+1));
             }
             cover(temp,a);
             return temp;
}

void create(vector<vector<can*> >&c,vector<prod*>a)
{
     vector<can*>temp;
     temp.push_back(new can(a[0],0));
     cover(temp,a);
     c.push_back(temp);
     for(int i=0;i<c.size();i++)
     {
             while(gt.size()<c.size())
             {
                 vector<aaa*>temp1;
                 gt.push_back(temp1);
             }
             for(int j=0;j<c[i].size();j++)
             {
                  prod* t=c[i][j]->p;
                  int dot=c[i][j]->dot;
                  if(t->r.size()>dot)
                  {
                      aaa* temp1=new aaa(t->r[dot]);
                      if(find(gt[i],temp1)==-1)
                      gt[i].push_back(temp1);
                  }
             }
             
             for(int j=0;j<gt[i].size();j++)
             {
                     vector<can*>temp1=goto1(c[i],a,gt[i][j]->c);
                     int pos;
                     if((pos=find(c,temp1))==-1)
                     {
                         gt[i][j]->i=c.size();
                         c.push_back(temp1);
                     }
                     else if(pos!=-1)
                     gt[i][j]->i=pos;
             }
             
     }
}
