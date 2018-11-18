#include<bits/stdc++.h>
#define SIZE 26
using namespace std;


map<char,string> hcode;
struct hNode
{
    char d;
    int f;
    hNode *left,*right;
};
hNode* makenode(char d,int f)
{
  hNode* t=new hNode;
  t->d=d;
  t->f=f;
  t->left=NULL;t->right=NULL;
  return t;
}
vector <hNode*> hv;
void makecode(hNode* root,string str)
{
    if (root==NULL)
    return;

  if(root->d!='$')
  {
    hcode.insert(pair<char,string>(root->d,str));
    cout<<root->d<<":"<<str<<endl;
  }

    makecode(root->left,str+"0");
    makecode(root->right,str+"1");
}
class mycomp
{
  public:
    int operator()(hNode* a,hNode* b)
    {
      return (a->f > b->f);
    }
};
void hoffmantree(priority_queue<hNode*,vector<hNode*>,mycomp > &pqueue)
{
  hNode *left,*right,*top;
  cout<<"\nunique characters = "<<pqueue.size()<<endl;
  priority_queue<hNode*,vector<hNode*>,mycomp > debug;

    while(pqueue.size()!=1)
  {
    left=pqueue.top();pqueue.pop();
    right=pqueue.top();pqueue.pop();
    top=makenode('$',left->f+right->f);
    top->left=left;top->right=right;
    pqueue.push(top);
    debug=pqueue;

  }
  makecode(pqueue.top(),"");

}
void count(char *s,int size)
{
  set <char> st;
  pair< set<char>::iterator,bool> ptr;

  for(int j=0;j<size;j++)
  {
    ptr=st.insert(s[j]);
    if(ptr.second)
    {
      int frequency=0;
      for(int i=0;i<size;i++)
        if(s[j]==s[i])
          {
            frequency++;
          }
          hNode* tmp=makenode(s[j],frequency);
          hv.push_back(tmp);
          //cout<<s[j]<<" "<<frequency<<"\t";

      }

    else continue;

  }
}

int main()
{
  int sum=0;
    hNode* a[SIZE];

  char vs[2048]={0};int num_characters = 0;
  int i = 0;
  ifstream myfile ("file.txt");

       if (myfile.is_open())
          {
            cout<<"File opened\n";
            while ( !myfile.eof())
            {
                  myfile >> vs[i];
                  i++;
                  num_characters ++;
            }}cout<<"File read\nNumbers of character="<<num_characters<<endl;

 count(vs,sizeof(vs)/sizeof(vs[0]));
  priority_queue<hNode*,vector<hNode*>,mycomp > pq,ppq;

  for(int i=0;i<hv.size();i++)
    pq.push(hv[i]);



  hoffmantree(pq);
  cout<<"Final string\n\n";
for(int i=0;i<num_characters;i++)
  {
      for (auto itr = hcode.begin(); itr != hcode.end(); ++itr)
      {
          if(vs[i]==itr->first)
          {
            cout<<itr->second;
            sum=sum+(itr->second).length();
          }
    }
}
cout<<"\n";
cout<<"\nTotal Number of bits = "<<sum<<"\n";
cout<<"Number of bits before compressing = "<<num_characters*8<<"\n";
float saving=num_characters*8-sum;
cout<<" Bits saved = "<<saving<<" = "<<(saving/(num_characters*8))*100<<"%\n";

}
