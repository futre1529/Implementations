#include<iostream>
#include"p2.cpp"
#include<vector>
#include<conio.h>
using namespace std;

vector<string>term,nterm,null;
vector<prod*>ptable;
vector<vector<string> >first,follow;



//to find the first of a non-terminal;
vector<string> first1(vector<prod*>&a,string s)
{
     vector<string>temp;
     int pos=find(a,s,0);
     while(pos!=-1)
     {
         if(a[pos]->r[0]=='#')
         {
            if(find(temp,"#")==-1)
            temp.push_back("#");
         }
         else if(!isupper(a[pos]->r[0]))
         {
              if(find(temp,a[pos]->r.substr(0,1))==-1)
              temp.push_back(a[pos]->r.substr(0,1));
         }
         else
         {
             bool null1=true;
             int j1=0;
             while(null1)
             {
                         if(!isupper(a[pos]->r[j1]) && find(temp,a[pos]->r.substr(j1,1))==-1)
                         {
                             temp.push_back(a[pos]->r.substr(j1,1));
                             break;
                         }
                         vector<string>temp1;
                         if(a[pos]->l!=a[pos]->r.substr(j1,1))
                         temp1=first1(a,a[pos]->r.substr(j1,1));
                         
                         for(int j=0;j<temp1.size();j++)
                         if(find(temp,temp1[j])==-1)
                         temp.push_back(temp1[j]);
                         int pos1=find(null,a[pos]->r.substr(0,1));
                         if(pos1==-1)
                         null1=false;
                         j1++;
             }
         }
         pos=find(a,s,pos+1);
     }
     return temp;
}

//to find substring of the
bool sub_null(string s,int pos)
{
     for(int i=pos;i<s.size();)
     {
             string s1=s.substr(i,1);
             if(s.find(s1+"'",pos)<s.size())
             s1+="'";
             if(s.find(s1+"`",pos)<s.size())
             s1+="`";
             if(find(null,s1)==-1)
             return false;
             i+=s1.size();
     }
     return true;
}

//to find follow of a non terminal;
vector<string> follow1(vector<prod*>&a,vector<string>n,string s)
{
               vector<string>temp;
               if(find(n,s)==0)
               temp.push_back("$");
               for(int i=0;i<a.size();i++)
               {
                       int pos=a[i]->r.find(s,0);
                       while(pos!=-1 && a[i]->r.find(s+"'",pos)==-1 && a[i]->r.find(s+"`",pos)==-1)
                       {
                           if(a[i]->r.size()>pos+s.size() && find(n,a[i]->r.substr(pos+s.size(),1))==-1)
                           temp.push_back(a[i]->r.substr(pos+s.size(),1));
                           else if(a[i]->r.size()>pos+s.size())
                           {
                                string s1=a[i]->r.substr(pos+s.size(),1);
                                if(a[i]->r.find(s1+"'",pos+s.size())<a[i]->r.size())
                                s1+="'";
                                else if(a[i]->r.find(s1+"`",pos+s.size())<a[i]->r.size())
                                s1+="`";
                                int pos1=find(n,s1);
                                for(int j=0;j<first[pos1].size();j++)
                                if(find(temp,first[pos1][j])==-1 && first[pos1][j]!="#")
                                temp.push_back(first[pos1][j]);
                                if(sub_null(a[i]->r,pos+s.size()+s1.size()))
                                {
                                    vector<string>temp1;
                                    if(a[i]->l!=s1)
                                    temp1=follow1(a,n,a[i]->l);
                                    for(int j=0;j<temp1.size();j++)
                                    if(find(temp,temp1[j])==-1)
                                    temp.push_back(temp1[j]);
                                }
                           }
                           else
                           {
                               vector<string>temp1;
                               if(a[i]->l!=s)
                               temp1=follow1(a,n,a[i]->l);
                               for(int j=0;j<temp1.size();j++)
                               if(find(temp,temp1[j])==-1)
                               temp.push_back(temp1[j]);
                           }
                           pos=a[i]->r.find(s,pos+1);
                       }
               }
               return temp;
}


bool is_null(vector<prod*>&a,vector<string>n,string s)
{
     int pos=find(a,s,0);
     while(pos!=-1)
     {
                   if(a[pos]->r[0]=='#')
                   return true;
                   else
                   {
                       int i;
                       for(i=0;i<a[pos]->r.size();i++)
                       {
                          int j=0;
                          if(i+1<a[pos]->r.size() && (a[pos]->r[i+1]=='`'||a[pos]->r[i+1]=='\''))
                          j=1;
                          if(find(n,a[pos]->r.substr(i,1+j))==-1)
                          break;
                          else if(a[pos]->l!=a[pos]->r.substr(i,1+j)  && !is_null(a,n,a[pos]->r.substr(i,1+j)))
                          break;
                          i+=j;
                       }
                       if(i==a[pos]->r.size())
                       return true;
                   }
                  pos=find(a,s,pos+1);
     }
     return false;
}
//to find first and follow of every non terminal;
void first_follow(vector<prod*>&a,vector<string>&n,vector<vector<string> >&fi,vector<vector<string> >&fo)
{
     a.insert(a.begin(),new prod(a[0]->l+"'",a[0]->l));
     n.insert(n.begin(),a[0]->l);
     for(int i=0;i<n.size();i++)
     {
             vector<string>temp;
             fi.push_back(temp);
             fo.push_back(temp);
     }
     
     for(int i=0;i<n.size();i++)
     {
             if(is_null(a,n,n[i]))
             null.push_back(n[i]);
     }
     
     for(int i=0;i<n.size();i++)
     fi[i]=first1(a,n[i]);
     for(int i=0;i<n.size();i++)
     fo[i]=follow1(a,n,n[i]);
     
     for(int i=0;i<fi.size();i++)
     {
        cout<<"first("<<n[i]<<"):{";
        for(int j=0;j<fi[i].size();j++)
        cout<<fi[i][j]<<",";
        cout<<"\b}\tfollow("<<n[i]<<"):{";
        for(int j=0;j<fo[i].size();j++)
        cout<<fo[i][j]<<",";
        cout<<"\b}\n";
     }
}
