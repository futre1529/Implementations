
#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<conio.h>
#include<vector>
using namespace std;

double minsup,t_count=0.0;
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

vector <vector<itemset*> >c;

//to sort the vector;
void sort(vector<itemset*> &a)
{
     for(int i=0;i<a.size();i++)
             for(int j=i+1;j<a.size();j++)
             if(a[i]->name>a[j]->name)
                swap(a[i],a[j]);
}
//to print element of a vector;
void print(vector<itemset*> &a,double c)
{
      cout<<"elements are:"<<endl;
      for(int i=0;i<a.size();i++)
      {
          if(a[i]->count/c!=0)
          cout<<a[i]->name<<" support:"<<a[i]->count/c<<"\n";
          else
          cout<<a[i]->name<<"\n";
      }

      cout<<endl;
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
//to generate of items for  candidate 1-itemset
void generate_c1()
{
    ifstream in("transaction.txt");
    vector<itemset*> temp;
    while(!in.eof())
    {
         string s;
         getline(in,s,':');
         if(s.size()==0)
         break;
		 getline(in,s,'\n');
         t_count+=1.0;
         int pos;

         while((pos=s.find(",")))
         {
              int te;
              if((te=index(s.substr(0,pos),temp))==-1)
              {
                   itemset* t=new itemset(s.substr(0,pos));
                   temp.push_back(t);
              }
              s.erase(0,pos+1);
              if(pos>s.size())
              break;
         }
    }
    sort(temp);
    c.push_back(temp);
    in.close();
}
//generate set of frequent itemset
void generate_l(double t_count,vector<itemset*> &a)
{
      for(int i=0;i<a.size();i++)
      {
            if(a[i]->count/t_count<minsup)
            a.erase(a.begin()+i--);
      }
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
//to reduce number of itemset from temporary candidate set
void prune(vector<itemset*> &a,int order)
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
                     if((pos=index(s.erase(pos,pos1+1-pos),c[order-2]))==-1)
                     {
                          a.erase(a.begin()+i);
                          --i;
                          break;
                     }
                     pos=pos1+1;
             }
     }
     c.push_back(a);
}
//to generate c;
void generate_c(int i,double t1)
{
     vector<itemset*> t=join(c[i-1]);
     cout<<"candidate set of order:"<<i<<" before pruning\n";
     print(t,t1);
     prune(t,i+1);
}
//to check the itemset presence in a  transaction
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

int main()
{
     cout<<"program for apriori algorithm"<<endl;
     cout<<"enter the minimum support value"<<endl;
     cin>>minsup;
     minsup-=0.000001;
     generate_c1();
     int j=1;
     while(true)
     {
         scan(j-1);
         cout<<"candidate itemset order:"<<j<<endl;
         print(c[j-1],t_count);
         generate_l(t_count,c[j-1]);
         if(c[j-1].size()==0)
         {
            c.erase(c.begin()+j-1);
            break;
         }
         cout<<"frequent temset order:"<<j<<endl;
         print(c[j-1],t_count);
         generate_c(j,t_count);
         if(c[j].size()==0)
         {
             c.erase(c.begin()+j);
             break;
         }
         j++;
     }


     cout<<"\nFrequent itemset are:"<<endl;
     for(int i=0;i<c.size();i++)
             print(c[i],t_count);
     getch();
     return 0;
}
