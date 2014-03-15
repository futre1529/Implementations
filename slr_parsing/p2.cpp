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
