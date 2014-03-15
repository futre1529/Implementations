#include<iostream>
#include"build_table.cpp"
#include<conio.h>
#include"stack.cpp"
using namespace std;

int**table;
stack <string> stk;

void parse(string&s)
{
     s+="$";
     stk.push("$");
     stk.push(nterm[0]);
     int i=0;
     cout<<"............................\n";
     cout<<"Stack\t\tInput\t\tAction\n";
     while(stk.size()>0)
     {
          stk.print();
          cout<<"\t"<<s.substr(i,s.size())<<"\t\t";
          string st=stk.pop(),in=s.substr(i,1);
          int check;
          //st holds element at top of the stack and in holds current input symbol;
          if(in==st  && in=="$")
          {
              cout<<"Accept...\n";
              return;
          }
          else if(in==st)
          {
              cout<<"Pop & Consume input\n";
              i++;
              continue;
          }
          else if(find(nterm,st)==-1 && in!=st)
          {
               cout<<"ERROR:Parsing string:"<<s<<endl;
               getch();
               exit(1);
          }
          else
          {
              check=table[find(nterm,st)][find(term,in)];
              if(check==-1)
              {
                cout<<"ERROR:Parsing string:"<<s<<endl;
                getch();
                exit(1);
              }
              else
              {
                  prod* t=ptable[check];
                  int ii=t->r.size()-1;
                  cout<<"Push production:"<<t->l<<"->"<<t->r<<endl;
                  while(ii>=0)
                  {
                      string s1=t->r.substr(ii,1);
                      int i1=1;
                      if(s1=="'" || s1=="`")
                      {
                            i1=2;
                            s1=t->r.substr(ii-1,2);
                      }
                      if(s1!="#")
                      stk.push(s1);
                      ii-=i1;
                  }
              }
          }
     }
}

int main()
{
    cout<<"Program For Predictive parsing..\n";
    cout<<"Enter the name of the input file...\n";
    char name[25];
    cin>>name;
    openfile(name,ptable,nterm,term);
    print("Grammer Productions:",ptable);
    remove_leftrecursion(ptable,nterm);
    print("Grammer Productions Without Left Recurssion:",ptable);
    leftfactoring(ptable,nterm);
    sort(ptable);
    print("Left Factored Grammer Productions Without Left Recurssion:",ptable);
    print("......\nGrammer Terminals:",term);
    print("......\nGrammer Non-Terminals:",nterm);
    first_follow(ptable,nterm,first,follow);
    term.push_back("$");
    create_table(table,ptable);
    print_table("\n.........\nAction Table:",table);
    
    cout<<".....\nNow Enter the terimnal string...\n";
    string key;
    cin>>key;
    parse(key);
    getch();
    return 0;
}
