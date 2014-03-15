#include<iostream>
using namespace std;

template <class T>

class stack
{
      struct snode
      {
        T key;
        snode* next;
        snode(T val)
        {
               key=val;
               next=NULL;
        }       
      }*head;
      public:
             void push(T key)
             {
                  snode* temp=new snode(key);
                  temp->next=head;
                  head=temp;
             }
             
             int size()
             {
                 snode* temp=head;
                 int i=0;
                 while(temp!=NULL)
                 {
                      temp=temp->next;
                      i++;
                 }
                 return i;
             }
             
             T pop()
             {
                    if(head==0)
                    cout<<"Stack is empty\n";
                    else
                    {
                        T temp=head->key;
                        head=head->next;
                        return temp;
                    }
                    return NULL;
             }
             stack()
             {
                    head=NULL;
             }
};
