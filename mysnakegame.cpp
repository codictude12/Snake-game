#include<iostream>
#include<stdlib.h>
#include<pthread.h>
#include<signal.h>

using namespace std;

char a[12][12];
int dir=1,prevdir=1,ate=0;
bool ex=true;

typedef struct node node;
struct food
{
        int row;
        int col;
};
struct node
{
        char data;
        int row;
        int col;
        struct node *prev;
        struct node *next;
};

void *direction(void *args)
{
char choice;
        while(ex)
        {
                cin>>choice;
                switch(choice)
                {
                        case 'g':
                                if(dir==1||dir==3)
                                {
                                        prevdir=dir;
                                        dir = 2;
                                }
                        break;
                        case 'h':
                                if(dir==2||dir==4)
                                {
                                        prevdir=dir;
                                        dir = 1;
                                }
                        break;
                        case 'f':
                                if(dir==2||dir==4)
                                {
                                        prevdir=dir;
                                        dir = 3;
                                }
                        break;
                        case 't':
                                if(dir==1||dir==3)
                                {
                                        prevdir=dir;
                                        dir = 4;
                                }
                }
        for(int p=0;p<10000000;p++){}
        }
pthread_exit(0);
}
class ll
{
public:
        node *head,*tail;
        food f;
public:
        ll()
        {
                node *newnode1=createnode('_',0,0);
                head=newnode1;
                tail=newnode1;
                newnode1=createnode('_',0,1);
                head->next=newnode1;
                newnode1->prev=head;
                head=head->next;
                newnode1=createnode('_',0,2);
                head->next=newnode1;
                newnode1->prev=head;
                head=head->next;
                int rn=getrand();
                f.row=rn/12;
                f.col=rn%12;
        }
        int getrand()
        {
                return (rand()%144);
        }
        node * createnode(char x,int row,int col)
        {
                node *newnode=new node;
                newnode->data=x;
                newnode->row=row;
                newnode->col=col;
                newnode->next=NULL;
                newnode->prev=NULL;
        return newnode;
        }
        void init()
        {
                for(int i=0;i<12;i++)
                        for(int j=0;j<12;j++)
                                a[i][j]=' ';
        }
        void play()
        {
                for(;ex;)
                {       print();
                        delay();
                }
        }
        void delay()
        {
                sleep(1);
                incr();
        }
        void incr()
        {
        int r=head->row,c=head->col;
        node *temp=tail;
        node *newnode;
                if(dir==1)
                {
                        if(prevdir==1 || prevdir==2)
                        {
                                newnode=createnode('_',r,c+1);
                                if(newnode->col==12){newnode->col=0;}
                        }
                        else if(prevdir==4)
                        {
                                newnode=createnode('_',r-1,c+1);
                                if(newnode->col==12){newnode->col=0;}
                                if(newnode->row==-1){newnode->row=11;}
                        }
                prevdir=1;
                }
                else if(dir==3)
                {
                        if(prevdir==3 || prevdir==2)
                        {
                                newnode=createnode('_',r,c-1);
                                if(newnode->col==-1){newnode->col=11;}
                        }
                        else if(prevdir==4)
                        {
                                newnode=createnode('_',r-1,c-1);
                                if(newnode->row==-1){newnode->row=11;}
                                if(newnode->col==-1){newnode->col=11;}
                        }
                prevdir=3;
                }
                else if(dir==2)
                {
                        if(prevdir==2)
                        {
                                newnode=createnode('|',r+1,c);
                                if(newnode->row==12){newnode->row=0;}
                        }
                        else if(prevdir==1)
                        {
                                newnode=createnode('|',r+1,c+1);
                                if(newnode->row==12){newnode->row=0;}
                                if(newnode->col==12){newnode->col=0;}
                        }
                        else if(prevdir==3)
                        {
                                newnode=createnode('|',r+1,c-1);
                                if(newnode->row==12){newnode->row=0;}
                                if(newnode->col==-1){newnode->col=11;}
                        }
                prevdir=2;
                }
                else if(dir==4)
                {
                        if(prevdir==4)
                        {
                                newnode=createnode('|',r-1,c);
                                if(newnode->row==-1){newnode->row=11;}
                        }
                        else if(prevdir==1)
                        {
                                newnode=createnode('|',r,c+1);
                                if(newnode->row==-1){newnode->row=11;}
                                if(newnode->col==12){newnode->col=0;}
                        }
                        else if(prevdir==3)
                        {
                                newnode=createnode('|',r,c-1);
                                if(newnode->row==-1){newnode->row=11;}
                                if(newnode->col==-1){newnode->col=11;}
                        }
                prevdir=4;
                }
                head->next=newnode;
                newnode->prev=head;
                head=newnode;
                if(ate==0)
                {
                        tail=tail->next;
                        tail->prev=NULL;
                delete temp;
                }
                ate=0;
        print();
        }
        void print()
        {
                char x;
                int r,c;
                system("clear");
                init();
        node *temp=head;
                while(temp!=NULL)
                {
                        x=temp->data;
                        r=temp->row;
                        c=temp->col;
                        a[r][c]=x;
                temp=temp->prev;
                }
                a[f.row][f.col]='@';
                for(int i=0;i<14;i++)
                {
                        for(int j=0;j<14;j++)
                        {
                                if(i==0 || i==13)
                                        cout<<'_';
                                else if(j==0 || j==13)
                                        cout<<'|';
                                else
                                        cout<<a[i-1][j-1];
                        }
                cout<<endl;
                }

        if(check())
                ex=false;
        }
        bool check()
        {
                node *temp=head->prev;
                while(temp!=NULL)
                {
                        if(head->row==temp->row && head->col==temp->col)
                        {
                                cout<<" ******** GAME OVER ******* "<<endl;
                                return true;
                        }
                temp=temp->prev;
                }
                if(head->row==f.row && head->col==f.col)
                {
                        int rn=getrand();
                        f.row=rn/12;
                        f.col=rn%12;
                ate=1;
                }
        return false;
        }
        ~ll()
        {
                node *temp;
                while(head!=NULL)
                {
                        temp=head;
                        head=head->prev;
                delete temp;
                }
        }
};
int main()
{
ll l;
pthread_t pi;
pthread_create(&pi,NULL,direction,NULL);
l.play();
return 0;
}
