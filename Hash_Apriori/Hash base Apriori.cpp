#include<iostream>
#include<fstream>
#include<string>
#include<time.h>
#include<cstdlib>
#include<conio.h>
#include<vector>
using namespace std;

double minsup;
//to hold minimum value of support

struct itemset
{
    string name;
    int count;
    itemset(string a)
    {
        name=a;count=0;
    }
};
void sort(vector<itemset*> &a)
{
     for(int i=0;i<a.size();i++)
             for(int j=i+1;j<a.size();j++)
             if(a[i]->name>a[j]->name)
                 swap(a[i],a[j]);
}
//to define the structure of hash table;
struct slice
{
       int count;
       slice()
       {
              count=0;
       }
};
//creating hash table of size 25;
slice table[10];
vector <vector<itemset*> >c;
vector <vector<itemset*> >l;
//vector to hold candidate 1-itemset

//to print element of a vector;
void print(vector<itemset*> &a,double c)
{
      cout<<"elements are:"<<endl;
      for(int i=0;i<a.size();i++)
      cout<<a[i]->name<<" support:"<<a[i]->count/c<<"\n";
      cout<<endl;
}

//to count yhee transactions of database;
double tcount()
{
    ifstream in("transaction.txt");
    int c=0;
    while(!in.eof())
    {
         string s;
         getline(in,s,'\n');
         c++;
    }
    in.close();
    return (double)c;
}

//to check the index of an item in the vector array
int index(string s,vector<itemset*> &a)
{
    for(int i=0;i<a.size();i++)
    {
            if(a[i]->name==s)
                return i;
    }
    return -1;
}

//to join two strings
string match(string s1,string s2)
{
     int pos1,pos2;
     bool flag=true;
     string result;
     while((pos1=s1.find(','))<s1.size() &&(pos2=s2.find(','))<s2.size())
     {
         if(s1.substr(0,pos1)!=s2.substr(0,pos2))
         {
             flag=false;
             break;
         }
         result+=s1.substr(0,pos1+1);
         s1.erase(0,pos1+1);
         s2.erase(0,pos2+1);
     }
     if(flag)
     return result+s1+","+s2;
     return "";
}

//defines the hash function for the string passed;
int  hash_function(string s)
{
     int j=0;
     for(int i=0;i<s.size();i++)
     j+=s[i];
     return j%10;
}
//to hash itemset of order 2 passed in vector a;
void hash(vector<string> a)
{
     for(int i=0;i<a.size();i++)
     {
             for(int j=i+1;j<a.size();j++)
             {
                     string s=match(a[i],a[j]);
                     int k=hash_function(s);
                     table[k].count++;
             }
     }
}
//to generate of items for  candidate 1-itemset
void generate_c1()
{
    ifstream in("transaction.txt");
    vector<itemset*> temp;
    while(!in.eof())
    {
         string s;
         vector<string> item;
         getline(in,s,':');
         getline(in,s,'\n');
         int pos;
         while((pos=s.find(",")))
         {
              int te;
              if((te=index(s.substr(0,pos),temp))==-1)
              {
                   itemset* t=new itemset(s.substr(0,pos));
                   t->count++;
                   temp.push_back(t);
              }
              else
              temp[te]->count++;
              item.push_back(s.substr(0,pos));
              s.erase(0,pos+1);
              if(pos>s.size())
              break;
         }
         hash(item);
    }
    c.push_back(temp);
    in.close();
}

//generate set of frequent itemset
void generate_l(double t_count,vector<itemset*> &a)
{
      double sup;
      vector<itemset*> temp;
      for(int i=0;i<a.size();i++)
      {
            if((sup=a[i]->count/t_count)>=minsup)
            temp.push_back(a[i]);
      }
      l.push_back(temp);
}

//to perform join algoritm;
vector<itemset*> join(vector<itemset*> &a)
{
     vector<itemset*> temp;
     for(int i=0;i<a.size();i++)
     {
             for(int j=i+1;j<a.size();j++)
             {
                     string s;
                     if((s=match(a[i]->name,a[j]->name))!="")
                     {
                         itemset* t=new itemset(s);
                         temp.push_back(t);
                     }
             }
     }
     return temp;
}

//to check the itemset preesence in a  transaction
bool is_present(string main,string sub)
{
     int pos=0;
     while(pos<sub.size())
     {
            int pos1=sub.find(',',pos);
            if(pos1>sub.size())
            pos1=pos;
            int pos2=main.find(sub.substr(pos,pos1+1-pos));
            if(pos2>main.size())
            return false;
            pos=pos1+1;
     }
     return true;
}

//to calculate the counts of element
void scan(int j)
{
     ifstream in("transaction.txt");
     while(!in.eof())
     {
         string s;
         getline(in,s,':');
         getline(in,s,'\n');
         for(int i=0;i<c[j].size();i++)
         {
                 if(is_present(s,c[j][i]->name))
                 c[j][i]->count++;
         }
     }
     in.close();
}

//to reduce number of itemset from temporary candidate set
void prunge(vector<itemset*> &a,int order)
{
     for(int i=0;i<a.size();i++)
     {
             int pos=0;
             for(int j=0;j<order;j++)
             {
                     string s=a[i]->name;
                     int pos1=s.find(',',pos);
                     if(pos1>s.size())
                     {
                         pos1=s.size();
                         pos--;
                     }
                     if((pos=index(s.erase(pos,pos1+1-pos),l[order-2]))==-1)
                     {
                          a.erase(a.begin()+i--);
                          break;
                     }
                     pos=pos1+1;
             }
     }
     c.push_back(a);
}

//to generate candidate set of order 2 by hash table;
void generate_c2(vector<itemset*> &a,double t)
{
     /*cout<<"\nHash Table generated is:"<<endl;
     cout<<"INDEX\tCOUNT"<<endl;
     for(int i=0;i<10;i++)
     cout<<i<<"\t"<<table[i].count<<endl;
     */
     for(int i=0;i<a.size();i++)
     {
             int ref=hash_function(a[i]->name);
             if(table[ref].count/t<minsup)
             a.erase(a.begin()+i--);
     }
     c.push_back(a);
}

//to generate c
void generate_c(int i,double t1)
{
     vector<itemset*> t=join(l[i-1]);
     if(i!=1)
     prunge(t,i+1);
     else
     generate_c2(t,t1);
}

int main()
{
     cout<<"program for Hash Based Apriori algorithm"<<endl;
     double  t_count=tcount(); //t_count stores the number of transactioons in database
     generate_c1();
     sort(c[0]);
     cout<<"enter the minimum support value"<<endl;
     cin>>minsup;
     clock_t time=clock();
     minsup-=0.000001;
     int j=1;
     while(true)
     {
         cout<<"\ncandidate itemset order:"<<j<<endl;
         print(c[j-1],t_count);
         generate_l(t_count,c[j-1]);
         if(l[j-1].size()==0)
         {
             l.erase(l.begin()+j-1);
             break;
         }
         cout<<"frequent temset order:"<<j<<endl;
         print(l[j-1],t_count);
         generate_c(j,t_count);
         if(c[j].size()==0)
         {
             c.erase(c.begin()+j);
             break;
         }
         scan(j);
         j++;
     }


     cout<<"\nFrequent itemset are:"<<endl;
     for(int i=0;i<l.size();i++)
     {
           print(l[i],t_count);
     }
     time=clock()-time;
     cout<<"time taken:"<<time<<" milisecs\n";
     getch();
     return 0;
}
