#include<iostream>
#include<vector>
#include<cstdlib>
#include<conio.h>
#include<string>
#include"p1.cpp"
using namespace std;

vector<prod*> ptable;
vector<char> terminal;
vector<vector<vector<char> > >table;

string tostring(char a)
{
       char* s1=new char[2];
       s1[0]=a;
       s1[1]=0;
       return s1;
}

void print()
{
     cout<<"Table:\n";
     for(int i=0;i<table.size();i++)
     {
          for(int j=0;j<table[i].size()-i;j++)
          {
                 for(int k=0;k<table[j][i+j].size();k++)
                 {
                         cout<<table[j][i+j][k]<<",";
                 }
                 cout<<"\b\t";
         }
         cout<<"\n";
     }
}

vector<char> find(string s)
{
      vector<char>temp;
      for(int i=0;i<ptable.size();i++)
      if(ptable[i]->r.find(s)<ptable[i]->r.size())
      temp.push_back(ptable[i]->l);
      return temp;
}

int find(vector<char> a,char b)
{
    for(int i=0;i<a.size();i++)
    if(a[i]==b)
    return i;
    return -1;
}

vector<string> create(vector<char>a,vector<char>b)
{
     vector<string>temp;
     if(a[0]=='$' || b[0]=='$')
     return temp;
     for(int i=0;i<a.size();i++)
     for(int j=0;j<b.size();j++)
     {
             char a1=a[i],b1=b[j];
             string s=tostring(a1)+tostring(b1);
             temp.push_back(s);
     }
     return temp;
}

vector<char> match(int i,int j)
{
             vector<char>temp1;
             vector<string>name;
             for(int k=i;k<j;k++)
             {
                     name=create(table[i][k],table[k+1][j]);
                     for(int i1=0;i1<name.size();i1++)
                     {
                             vector<char>temp=find(name[i1]);
                             for(int i2=0;i2<temp.size();i2++)
                             if(find(temp1,temp[i2])==-1)
                                     temp1.push_back(temp[i2]);
                     }
             }
             if(temp1.size()==0)
             temp1.push_back('$');
             return temp1;
}

bool in_language(string s)
{
     for(int i=0;i<s.size();i++)
     {
         vector<  vector<char> >temp;
         for(int j=0;j<s.size();j++)
         {
                 vector<char> temp1;
                 temp.push_back(temp1);
         }
         table.push_back(temp);
     }
     
     for(int i=0;i<s.size();i++)
     {
             table[i][i]=find(s.substr(i,1));
             if(table[i][i].size()==0)
             table[i][i].push_back('$');
     }
            
    for(int j=1;j<s.size();j++)
     for(int i=0;i<s.size()-j;i++)
       table[i][i+j]=match(i,i+j);
       
       vector<char>temp=table[0][s.size()-1];
       for(int i=0;i<temp.size();i++)
       if(temp[i]==ptable[0]->l)
       return true;
       
       return false;
}

int main()
{
    cout<<"Program for CYK Algorithm...\n";
    cout<<"Enter the name of the input file...\n";
    char name[25];
    cin>>name;
    openfile(name,ptable);
    if(!is_cyk(ptable))
    {
         getch();
         exit(1);
    }
    cout<<"Given Productions are:\n";
    for(int i=0;i<ptable.size();i++)
    cout<<ptable[i]->l<<"->"<<ptable[i]->r<<endl;
    
    cout<<"Now enter the string...\n";
    string s;
    cin>>s;
    
    if(!in_language(s))
    cout<<s<<" is not in the given grammer...\n";
    else
    cout<<s<<" is in the grammer...\n";
    
    cout<<".......\n";print();
    getch();
    return 0;;
}
