/******************************
            块状链表实现editor
    For NOI2003 :     Editor
    Author:        DarkRaven
 *****************************/
#include<iostream>
#include<cmath>
#define MAX 2900
struct block{//Type of block
    int nos;//Number of elements in this block
    char em[MAX];//elements 
    block *be,*su;//previous&successor
}*first;
struct cursor{//Type of cursor
    int n;//The postion of cursor(in one block)
    block *ll;//The block the cursor in
}cur;
int tot,n;//tot:the total number of elements,n:the number of operations
inline void clean(block *op){//Clean a new block
    op->nos=0;
    memset(op->em,0,sizeof op->em);
    op->be=NULL;
    op->su=NULL;
}
inline void Spilt(block *a,int newsize){//Break a block into two blocks,one's size equal to 'newsize',and another's equal to 'a->nos-newsize'
    if(!newsize)return;
    int tmp=a->nos;
    a->nos=newsize;
    block *tps=a->su;
    a->su=new(block);
    clean(a->su);
    a->su->be=a;
    if(tps){
        a->su->su=tps;
        a->su->su->be=a->su;
    }
    a->su->nos=tmp-newsize;
    block *tt=a->su;
    for(int i=newsize+1;i<=tmp;i++)tt->em[i-newsize]=a->em[i];
}
inline void Merge(block *a){//Merge a & a->su
    if(a->su==NULL)return ;
 int tmp=a->nos;
    for(int i=1;i<=a->su->nos;i++)a->em[a->nos+i]=a->su->em[i];
    a->nos+=a->su->nos;
    block *oo=a->su;
 if(cur.ll==oo){
  cur.ll=cur.ll->be;
  cur.n+=tmp;
 }
    a->su=a->su->su;
    delete(oo);
    if(a->su)a->su->be=a;
}
inline void Balance(){//Make these blocks' size balance
    block *k=first;
    int kk=(int)sqrt(tot);
    for(;k!=NULL;){
        for(;k->nos < kk/2 || k->nos > 2*kk;){
            if(k->nos<kk/2){//the block is too small?
                if(k->su)Merge(k);
                else break;
            }
            else if(k->nos>kk*2){//the block is too big?
    Spilt(k,(k->nos)>>1);
    if((cur.ll==k)&&(cur.n>k->nos)){
                    cur.ll=k->su;
                    cur.n-=k->nos;
                }
    k=k->su;
    }
        }
  k=k->su;
    }
}
inline void Insert(block *lk,int x,int k){//Insert text behind the cursor
     block *oo=new(block);
    clean(oo);
    block *gg=oo;
    int rr=k;
    tot+=rr;
    int bt=(int)sqrt(tot);
    for(int i=0;i<rr;i++){
     char gg;
  scanf("%c",&gg);
  for(;(gg>126)||(gg<32);scanf("%c",&gg));
  oo->em[++oo->nos]=gg;
  if((oo->nos>=bt)&&(i<rr-1)){
   oo->su=new(block);
   clean(oo->su);
   oo->su->be=oo;
   oo=oo->su;
  }
 }
 if(x){
  Spilt(lk,x);
 }
 else {
  if(!cur.ll->be){
   block *jj;
   jj=first;
   first=new(block);
   clean(first);
   first->su=jj;
   jj->be=first;
  }
  cur.ll=cur.ll->be;
  cur.n=cur.ll->nos;
  lk=lk->be;
 }
 block *tmp=lk->su;
 lk->su=gg;
 oo->su=tmp;
 if(oo->su)oo->su->be=oo;
 lk->su->be=lk;
 cur.ll=lk->su;
 cur.n=0;
 Balance();
}
inline void Remove(block *lk,int x,int num){ //Delete 'num' elements behind the cursor
 if(x){
  Spilt(lk,x);
  lk=lk->su;
 }
 else {
  if(!cur.ll->be){
   block *jj;
   jj=first;
   first=new(block);
   clean(first);
   first->su=jj;
   jj->be=first;
  }
  cur.ll=cur.ll->be;
  cur.n=cur.ll->nos;
 }
 tot-=num;
 int ttt=num;
 block *tmp;
 block *ii;
 for(tmp=lk;tmp&&((num-tmp->nos)>=0);tmp=ii){
  ii=tmp->su;
  num-=tmp->nos;
  delete(tmp);
 }
 if(num&&tmp){
  Spilt(tmp,num);
  cur.ll->su=tmp->su;
  cur.ll->su->be=cur.ll;
  if(cur.ll->be)cur.ll->be->su=cur.ll;
 }
 else {
  cur.ll->su=tmp;
  if(cur.ll->be)cur.ll->be->su=cur.ll;
  if(cur.ll->su)cur.ll->su->be=cur.ll;
 }
 Balance();
}  
inline void Print(block *lk,int x,int num){//print 'num' elements behind the cursor
 block *cp=lk;
 for(;num-(cp->nos-x)>0;cp=cp->su){
  for(int i=x+1;i<=cp->nos;i++)printf("%c",cp->em[i]);
  num-=(cp->nos-x);
  x=0;
 }
 for(int i=1;i<=num;i++)printf("%c",cp->em[i+x]);
 printf("\n");
}
inline void prev(){//cursor move forward
 cur.n--;
 if(cur.n<0){
  cur.ll=cur.ll->be;
  cur.n=cur.ll->nos-1;
 }
}
inline void next(){//cursor move backward
 cur.n++;
 if((cur.n>=cur.ll->nos)&&(cur.ll->su)){
  cur.ll=cur.ll->su;
  cur.n-=cur.ll->be->nos;
 }
}
inline void move(int k){//move the cursor to the postion 'k'
 cur.ll=first;
 for(;(cur.ll)&&(k-cur.ll->nos>0);cur.ll=cur.ll->su)
 k-=cur.ll->nos;
 cur.n=k;
}
int main(){
 freopen("editor.in","r",stdin);
 freopen("editor.out","w",stdout);
 first=new(block);
 clean(first);
 char str[100];
 cur.ll=first;
 cur.n=0;
 scanf("%d\n", &n);
 int k;
 for (int i=0;i<n;i++) {
  scanf("%s", str);
  switch (str[0]) {//deal with operations
      case 'M' : scanf("%d", &k); move(k); break;
            case 'I' : scanf("%d", &k); Insert(cur.ll,cur.n,k); break;
            case 'D' : scanf("%d", &k); Remove(cur.ll,cur.n,k); break;
            case 'G' : scanf("%d", &k); Print(cur.ll,cur.n,k);; break;
            case 'P' : prev(); break;
            case 'N' : next(); break;
        }
    }
 
    fclose(stdin);
    fclose(stdout);
}

