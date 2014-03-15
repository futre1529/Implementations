#include<iostream>
#include"can_set.cpp"
#include<conio.h>
#include<utility>
using namespace std;

vector<vector<can*> >cset;

pair<bool,int>**table;
can* acc;
void print_table(string s,pair<bool,int>** t)
{
     cout<<s<<endl<<"\t";
     int num=term.size()+nterm.size();
     for(int i=0;i<term.size();i++)
     cout<<term[i]<<"     ";
     for(int i=0;i<nterm.size();i++)
     cout<<nterm[i]<<"     ";
     cout<<endl;
     for(int i=0;i<cset.size();i++)
     {
             cout<<i<<"\t";
             for(int j=0;j<num;j++)
             {
                     if(t[i][j].first==0)
                     cout<<"S";
                     else if(t[i][j].first==1)
                     cout<<"R";
                     
                     if(t[i][j].second==-1)
                     cout<<"\b---";
                     else if(t[i][j].second==-2)
                     cout<<"\bacc";
                     else if(t[i][j].second/10==0)
                     cout<<" "<<t[i][j].second;
                     else
                     cout<<t[i][j].second;
                     cout<<"   ";
             }
             cout<<endl;
     }
}

void create_table(pair<bool,int>** &t,vector<vector<can*> >a)
{
     t=new pair<bool,int> * [a.size()];
     int num=term.size()+nterm.size();
     for(int i=0;i<a.size();i++)
     {
             t[i]=new pair<bool,int>[num];
             for(int j=0;j<num;j++)
             {
                     t[i][j].first=0;
                     t[i][j].second=-1;
             }
     }
     
     for(int i=0;i<a.size();i++)
     {
         int pos;
         for(int j=0;j<a[i].size();j++)
         {
                 prod* t1=a[i][j]->p;
                 if(t1==acc->p && a[i][j]->dot==acc->dot)
                 t[i][find(term,"$")].second=-2;
                 else if((pos=find(term,t1->r.substr(a[i][j]->dot,1)))!=-1)
                 {
                      char s=t1->r[a[i][j]->dot];
                      int pos1=find(gt[i],s);
                      t[i][pos].second=gt[i][pos1]->i;
                 }
                 else if(a[i][j]->dot==t1->r.size())
                 {
                      pos=find(nterm,t1->l);
                     for(int k=0;k<follow[pos].size();k++)
                     {
                        string s=follow[pos][k];
                        int pos1=find(term,s);
                        t[i][pos1].first=1;
                        t[i][pos1].second=find(ptable,t1);
                     }
                 }
         }
         cout<<"A";
         for(int j=0;j<nterm.size();j++)
           if((pos=find(gt[i],nterm[j][0]))!=-1)
           t[i][term.size()+j].second=gt[i][pos]->i;
         cout<<"B";
     }
}

int main()
{
    cout<<"Program For Predictive parsing..\n";
    cout<<"Enter the name of the input file...\n";
    char name[25];
    cin>>name;
    openfile(name,ptable,nterm,term);
    first_follow(ptable,nterm,first,follow);
    term.push_back("$");
    
    print("......\nGrammer Productions:",ptable);
    print("......\nGrammer Terminals:",term);
    print("......\nGrammer Non-Terminals:",nterm);
    
    create(cset,ptable);
    acc=new can(ptable[0],ptable[0]->r.size());
    nterm.erase(nterm.begin());
    create_table(table,cset);
    print("..........\n",cset);
    print_table("\n.........\nAction Table:",table);
    getch();
    return 0;
}
