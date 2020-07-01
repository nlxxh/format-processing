#include<iostream>
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#include<stack> 
#define INITSIZE 1000
using namespace std;
 
//�ؼ��� 
string key[15]={"main","int","if","else","while","float","char","break","case","long","continue","double","for","return","void"}; 
//������ͽ�� 
string symbol[30]={"<",">","!=",">=","<=","==",",",";","(",")","{","}","+","-","*","/","=","+=","-=","_","//","#","%",":","||","&&","*=","/=","%=","^"};
//������ͽ�������� 
string symbolName[30]={"С�ں�","���ں�","�����ں�","���ڵ��ں�","С�ڵ��ں�","���ں�","����","�ֺ�","��С����","��С����","�������","�Ҵ�����",
"�Ӻ�","����","�˺�","����","��ֵ��","�ӷ���ֵ","������ֵ","�»���","ע��","����","�����","ð��","��","��","�˷���ֵ","������ֵ","���ำֵ","�˷�"};
string letter[1000];//����ļ�ȡ�����ַ� 
int length;//����������ַ�����Ŀ 
int num; 
int p;
int z=0;
int oo=0;
int errors=0;
struct key{
	string h;//��������
	int g;//�������� 
};//���ʶ����ĵ������� 
struct key ww;
struct key kind,idt;
struct key Words[1000];//���ʶ��������е��� 
//����һ�Σ�ȡһ������ 
struct key gettoken(){
	ww.h=Words[oo].h;
	ww.g=Words[oo].g;
	oo++;
	return ww;
}; 
//�ж��Ƿ�Ϊ������ͽ�� 
int isSymbol(string s){ 
 int i;
 for(i=0;i<30;i++){
  if(s==symbol[i])
   return i; 
 }
 return 0;
} 
//�ж��Ƿ�Ϊ�ؼ��� 
int isKeyWord(string s){
 int i;
 for(i=0;i<15;i++){
  if(s==key[i])
   return 1;
 }
 return 0;
}
//�ж��Ƿ�Ϊ���� 
bool isNum(string s){
 if(s>="0" && s<="9")
  return true;
 return false;
}
//�ж��Ƿ�Ϊ��ĸ 
bool isLetter(string s)
{
 if((s>="a" && s<="z")||(s>="A" && s<="Z"))
  return true;
 return false;
}
//���ص����ַ������� 
int typeword(string str){
 if((str>="a" && str<="z")||(str>="A" && str<="Z")) // ��ĸ 
  return 1; 
 if(str>="0" && str<="9") //���� 
  return 2;
 if(str==">"||str=="="||str=="<"||str=="!"||str==","||str==";"||str=="("||str==")"||str=="{"||str=="}"||str=="+"||str=="-"
 ||str=="*"||str=="/"||str=="#"||str=="&"||str=="^"||str=="%"||str==":"||str=="|"||str=="_") //�ж�������ͽ��(��һλ) 
  return 3; 
 if(str=="'") //�ж��ַ��ͳ���
  return 4;  
 if(str=="[") //�ж�����
  return 5;
 if(str=="\"") //�ж��ַ���
  return 6; 
}
//���عؼ��ֻ��ʶ�� 
string identifier(string s,int n){
 int j=n+1;
 int flag=1;//����ѭ�� 
 while(flag){
  if(isNum(letter[j])||isLetter(letter[j])||letter[j]=="_"){
   s=s+letter[j];
   if(isKeyWord(s)){
    j++;
    num=j;
    return s;//���عؼ��� 
   }
   j++;
  }
  else{
   flag=0;//����������ͽ��������ѭ�� 
  }
 } 
 num=j;
 return s;//���ر�ʶ�� 
}
//����������ͽ��  
string symbolStr(string s,int n){//s��������ͽ��(��һλ)  
 int j=n+1;
 string str=letter[j];//strȡ��һλ 
 if(str=="="||str=="&"||str=="|"||str=="/") {//�ж�str�Ƿ���������ͽ���ĵڶ�λ 
  s=s+letter[j];
  j++;
 }
 num=j;
 return s;//����������ͽ�� 
}
//�������� 
string Number(string s,int n){
 int j=n+1;
 int flag=1;
 p=1; 
 while(flag){
  if(isNum(letter[j]) || letter[j]=="x" || letter[j]=="X"){
   s=s+letter[j];
   j++;//���ͳ��� 
  }
  else if(letter[j]=="." || letter[j]=="f" || letter[j]=="F"){
   s=s+letter[j];
   j++;
   p=2;//�����ͳ��� 
  }
  else if(letter[j]=="L" || letter[j]=="l"){
   s=s+letter[j];
   j++;
   p=3;//�����ͳ��� 
  }  
  else{
   flag=0;
  }
 }
 num=j;
 return s;//�������� 
}
//�����ַ����� 
string charConst(string s,int n){
 int j=n+1;
 s=s+letter[j];	
 j++;
 s=s+letter[j];
 num=j+1;
 return s;//�����ַ�����
}
//��������
string array(string s,int n){
 int j=n+1;
 while(letter[j-1]!="]")
 {
 	s=s+letter[j];
 	j++;
 }
 num=j;
 return s;//�������� 
} 
//�����ַ�������
string charList(string s,int n){
 int j=n+1;
 while(letter[j]!="\"")
 {
 	s=s+letter[j];
 	j++;
 }
 s=s+letter[j];
 num=j+1;
 return s;//�����ַ�������
}  
//ȡ���ʲ�����ʷ��������  
void TakeWord(){ 
 int k;
 for(num=0;num<length;){
  string str1,str;
  str=letter[num];
  k=typeword(str);//kΪ�����ַ�������  
  switch(k){
   case 1:
    {
     str1=identifier(str,num);
     if(isKeyWord(str1))
      cout<<"�ؼ���"<<"  "<<str1<<endl;
     else
      cout<<"��ʶ��"<<"  "<<str1<<endl;
     break;
    }
   case 2:
    {
     str1=Number(str,num);
     if(p==1)  cout<<"���ͳ���"<<"  "<<str1<<endl;
     else if(p==2)  cout<<"�����ͳ���"<<"  "<<str1<<endl;
     else if(p==3)  cout<<"�����ͳ���"<<"  "<<str1<<endl;  
     break;
    }
   case 3:
    {
     str1=symbolStr(str,num);
     cout<<symbolName[isSymbol(str1)]<<"  "<<str1<<endl;
     break; 
    }
    case 4:
    {
     str1=charConst(str,num);
     cout<<"�ַ��ͳ���"<<"  "<<str1<<endl;
     break;
	}
	case 5:
	{
     str1=array(str,num);
     cout<<"����"<<"  "<<str1<<endl;
     break;
	}	
	case 6:
	{
     str1=charList(str,num);
     cout<<"�ַ�������"<<"  "<<str1<<endl;
     break;
	}
  }
 } 
}
//��������ʴ������Ա� 
void WordList(){
 int k;
 for(num=0;num<length;){
  string str1,str,str2,str3,str4,str5,str6;
  str=letter[num];
  int m=0;
  k=typeword(str);//kΪ�����ַ�������  
  switch(k){
   case 1:
    {
     str1=identifier(str,num);
	 if(isKeyWord(str1)) m=0;
	 else m=1;
     break;
    }
   case 2:
    {
     str2=Number(str,num);m=2;
     break;
    }
   case 3:
    {
     str3=symbolStr(str,num);m=3;
     break; 
    }
    case 4:
    {
     str4=charConst(str,num);m=4;
     break;
	}
	case 5:
	{
     str5=array(str,num);m=5;
     break;
	}	
	case 6:
	{
     str6=charList(str,num);m=6;
     break;
	}	
  }
  switch(m){
  	case 0:
  	{
  	 Words[z].h=str1;
  	 Words[z].g=0;
  	 break;	
	}
  	case 1:
  	{
  	 Words[z].h=str1;
  	 Words[z].g=1;
  	 break;
	}
	case 2:
  	{
  	 Words[z].h=str2;
  	 Words[z].g=2;
  	 break;
	}	
	case 3:
  	{
  	 Words[z].h=str3;
  	 Words[z].g=3;
  	 break;
	}	
	case 4:
  	{
  	 Words[z].h=str4;
  	 Words[z].g=4;
  	 break;
	}	
	case 5:
  	{
  	 Words[z].h=str5;
  	 Words[z].g=5;
  	 break;
	}
	case 6:
  	{
  	 Words[z].h=str6;
  	 Words[z].g=6;
  	 break;
	}			
  }	
  z++;
 } 
} 
typedef struct node{
	struct node *lchild;//����ָ�� 
	struct node *rsibling;//���ֵ�ָ�� 
	string name; 
}*tree,node;
//��������
tree program();//������� 
tree ExtDefList();//�����ⲿ�������� 
tree ExtDef();//�����ⲿ���� 
tree ExtVarDef();//�����ⲿ��������
tree FuncDef();//����������
tree Para();//�������β� 
tree ComSen();//���������
tree InVarDef();//����ֲ��������� 
tree SenList();//������������䲿��(�������) 
tree statement();//����һ�����
tree exp();//������ʽ 
int PrintTree(tree root);//��������﷨�� 
char precede(string a,string b);//��������ȼ��ж� 
int visit();
//������� 
tree program(){
	ww=gettoken();
	tree root;
	root=ExtDefList();//���򷵻ص��﷨�������ָ�룬�ɱ�����ʾ
	if (root!=NULL) return root;
	else {
		cout<<"Error!"<<endl;;//��������﷨���� 
		return NULL;
	}
}
//�����ⲿ�������� 
tree ExtDefList(){
	if(ww.h=="") return NULL;
	if(errors!=0) return NULL;
	tree root,root1,root2;
	root=new node();//����һ���ⲿ�������н��root 
	root->rsibling=NULL;
	root1=ExtDef();//����һ���ⲿ���壬�õ�һ����������Ϊroot�ĵ�һ������
	root->lchild=root1; 
	root2=ExtDefList();//�ݹ���ã��õ�����������Ϊroot�ĵڶ�������
	root1->rsibling=root2; 
	return root;
}
//�����ⲿ���� 
tree ExtDef(){
	if(ww.h!="int" && ww.h!="float" && ww.h!="char" && ww.h!="double" && ww.h!="void" && ww.h!="long"){
		cout<<"�ⲿ���岿�֣�"<<"Error1 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
		errors+=1;
		return NULL;
	}//ww�������͹ؼ���,��������NULL
	kind=ww;
	ww=gettoken();
	if(ww.g!=1){
		cout<<"�ⲿ���岿�֣�"<<"Error2 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
		errors+=1;
		return NULL;
	}//ww���Ǳ�ʶ��,��������NULL 
	idt=ww; 
	tree p;
	ww=gettoken();
	if (ww.h!="(") p=ExtVarDef();//�����ⲿ���������ӳ���   
	else p=FuncDef();//���ú��������ӳ���
	return p; 
}
//�����ⲿ�������� 
tree ExtVarDef(){//���ô��ӳ���ʱ���ⲿ�������ͺ͵�һ���������ĵ����Ѿ����룬�������ͱ�����kind�У�������������idt�У���ʱ��ww�Ƿ���","��";" 
	tree root,root0,root1,root2,p,q,h;
	if(ww.g==5) ww=gettoken();
	root=new node();//����һ���ⲿ����������root 
	root->name="�ⲿ�������壺\n";
	root->rsibling=NULL;
	root1=new node();//����һ���ⲿ�������ͽ��root1 
	root1->name="    ���ͣ�"+kind.h+"\n";
	root->lchild=root1;
	root1->lchild=NULL;
	root0=new node();//����һ���������������root0
	root0->name="    ��������\n";
	root1->rsibling=root0;
	root0->rsibling=NULL;
	root2=new node();//����һ���ⲿ�������н��root2 
	root2->name="      ID��";
	root2->rsibling=NULL;
	root0->lchild=root2;
	p=new node();//����һ���ⲿ���������p
	root2->lchild=p;
	p->name=idt.h+"\n";
	p->lchild=NULL; 
	while(1){//ÿ���ⲿ�������н��ĵ�һ�����Ӷ�Ӧһ�������� 
		if (ww.h!=";" && ww.h!=","){
			cout<<"�ⲿ�������岿�֣�"<<"Error3 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
			errors+=1;
			delete(root);delete(root1);delete(root2);delete(p);delete(root0);
			return NULL;
		}//ww����";"��","�������ͷ�rootΪ����ȫ����㣬���ؿ�ָ��
		if (ww.h==";"){
			ww=gettoken();//wwȡ��";"֮��ĵ�һ���ַ�
			return root;
		}//����";"���ⲿ���������������� 
		ww=gettoken();//��ʼʶ������ı�����
		if (ww.g!=1){
			cout<<"�ⲿ�������岿�֣�"<<"Error4 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
			errors+=1;
			delete(root);delete(root1);delete(root2);delete(p);
			return NULL;
		}//ww���Ǳ�ʶ���������ͷ�rootΪ����ȫ����㣬���ؿ�ָ��
		q=new node();//����һ���ⲿ�������н��q
		q->name="      ID��";
		p->rsibling=q; 
		q->rsibling=NULL;
		h=new node();//����һ���ⲿ���������h
		h->name=ww.h+"\n";
		q->lchild=h;
		h->lchild=NULL;
		p=h;
		ww=gettoken();
	}
}//����ʱwwȡ��";"֮��ĵ�һ���ַ���  
//���������� 
tree FuncDef(){//���ô��ӳ���ʱ����������ֵ���ͺͺ������ĵ����Ѿ����룬��������ֵ���ͱ�����kind�У�������������idt�У���ʱ��ww�Ƿ���"("
	tree root,root1,root0,root2,p,h;
	root=new node();//����һ������������root 
	root->name="�������壺\n";
	root->rsibling=NULL;
	root1=new node();//����һ����������ֵ���ͽ��root1 
	root1->name="    ���ͣ�"+kind.h+"\n";
	root->lchild=root1;
	root1->lchild=NULL;
	root0=new node();//����һ�����������root0
	root0->name="    ��������" +idt.h+"\n";
	root1->rsibling=root0;
	root2=new node();//����һ�������β��������root2
	root0->lchild=root2;
	root2->name="    �����βΣ�\n";
	p=Para();//���ú����β��ӳ���,���ú�wwȡ�� ")"֮��ĵ�һ���ַ�
	root2->lchild=p; 
	h=ComSen();//���ø�������ӳ���
	root0->rsibling=h; 
	return root;
}
//�������β� 
tree Para(){//���ô��ӳ���ʱ��ww�Ƿ���"(",δ�����β���Ϣ 
	tree root,root1,root2,q,h,p;
	ww=gettoken();//wwȡ���β����ͻ��޲�ȡ��")" 
	if(ww.h==")"){//�޲κ��� 
		ww=gettoken();//wwȡ��")"֮��ĵ�һ���ַ� 
		return NULL;
	}
	if(ww.h!="int" && ww.h!="float" && ww.h!="char" && ww.h!="double" && ww.h!="void" && ww.h!="lomg"){
		cout<<"�����ββ��֣�"<<"Error5 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
		errors+=1;
		return NULL;
	}//ww�������͹ؼ���,��������NULL	 
	if(ww.h=="void"){//�޲κ��� 
		ww=gettoken();
		if(ww.h!=")"){
			cout<<"�����ββ��֣�"<<"Error6 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
			errors+=1;
		    return NULL;
		}
		ww=gettoken();//wwȡ��")"֮��ĵ�һ���ַ� 
		return NULL;
	}
	root=new node();//����һ�������β������������root 
	root->name="      ���ͣ�";
	root->rsibling=NULL;
	root1=new node();//����һ�������β����ͽ��root1
	root->lchild=root1;
	root1->name=ww.h+" , ";
	root1->lchild=NULL;
	ww=gettoken();//wwȡ�������β��� 
	root2=new node();//����һ�������β������root2
	root2->name="��������"+ww.h+"\n";
	root1->rsibling=root2;
	root2->rsibling=NULL;
	ww=gettoken();//wwȡ��","��")"
	while(1){ 
		if (ww.h!=")" && ww.h!=","){
			cout<<"�����ββ��֣�"<<"Error7 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
			errors+=1;
			delete(root);delete(root1);delete(root2);
			return NULL;
		}//ww����")"��","�������ͷ�rootΪ����ȫ����㣬���ؿ�ָ��
		if (ww.h==")"){
			ww=gettoken();//wwȡ��")"֮��ĵ�һ���ַ�
			return root;
		}//����")"�������β��������� 
		ww=gettoken();//��ʼʶ������ı�����,wwȡ�������β����� 
		if (ww.h!="int" && ww.h!="float" && ww.h!="char" && ww.h!="double" && ww.h!="long"){
			cout<<"�����ββ��֣�"<<"Error8 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
			errors+=1;
			delete(root);delete(root1);delete(root2); 
			return NULL;
		}//ww�������͹ؼ��֣������ͷ�rootΪ����ȫ����㣬���ؿ�ָ�� 
		q=new node();//����һ�������β������������q
		q->name="      ���ͣ�";
		root2->lchild=q; 
		q->rsibling=NULL;
		h=new node();//����һ�������β����ͽ��h
		h->name=ww.h+" , ";
		q->lchild=h;
		h->lchild=NULL;
		p=new node();//����һ�������β������p
		ww=gettoken();
		if (ww.g!=1){
			cout<<"�����ββ��֣�"<<"Error9 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
			errors+=1;
			delete(root);delete(root1);delete(root2);delete(p);delete(q);delete(h);
			return NULL;
		}//ww���Ǳ�ʶ���������ͷ�rootΪ����ȫ����㣬���ؿ�ָ��
		p->name="��������"+ww.h+"\n";
		h->rsibling=p; 
		p->rsibling=NULL;
		root2=p;
		ww=gettoken();
	}
}//����ʱwwȡ�� ")"֮��ĵ�һ���ַ�
//��������� 
tree ComSen(){//���ô��ӳ���ʱ��wwȡ��";"��"{" 
	if(ww.h!=";" && ww.h!="{"){
		cout<<"������䲿�֣�"<<"Error10 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
		errors+=1;
		return NULL;
	}
	tree root,root1,root2,root3,root4,root5,p,q;
	root=new node();//����һ�����������root
	root->name="    ������䣺\n";
	root->rsibling=NULL;
	if(ww.h==";"){//���������������������Ϊ�� 
		ww=gettoken();//wwȡ����������������";"֮��ĵ�һ���ַ� 
	
		root->lchild=NULL;
		return root; 
	}
	ww=gettoken();//wwȡ��"{"֮��ĵ�һ���ַ�
	root1=new node();//����һ�������������������root1
	root1->name="      �������ı������壺\n"; 
	root3=new node();//����һ����䲿���������root3 
	root->lchild=root1; 
	root2=new node();//����һ�������������������root2
	root2->name="        LOCAL VAR_NAME��\n";
	root1->lchild=root2;
	root2->rsibling=NULL;
	root1->rsibling=root3;
	root3->name="      ����������䲿�֣�\n";
	root3->rsibling=NULL;
	while(ww.h!="}"){
	if(ww.h=="int" || ww.h=="float" || ww.h=="char" || ww.h=="double" || ww.h=="long"){
		p=InVarDef();//���ô���ֲ����������ӳ��� 
		root2->lchild=p;
		root4=new node();
		p->rsibling=root4;
		root2=root4;//�ݹ�����	
	}//wwȡ��";"֮��ĵ�һ���ַ� 
	else{
	q=SenList();//���ô�����������ӳ��򣬽���ʱwwȡ��"}" 
	root3->lchild=q;
	root5=new node();
	q->rsibling=root5;
	root3=root5;//�ݹ�����	
    }
} 
	if(ww.h!="}"){
		cout<<"������䲿�֣�"<<"Error11 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
		errors+=1;
		delete(root);delete(root1);delete(root3); 
		return NULL;
	}
	ww=gettoken();//wwȡ��"}"֮��ĵ�һ���ַ� 
	return root;
}//����ʱwwȡ��"}"֮��ĵ�һ���ַ�  
//����ֲ��������� 
tree InVarDef(){//wwȡ����������еı��������ַ� 
	tree root,root0,root1,root2,p,q,h,root3;
	if (ww.h!="int" && ww.h!="float" && ww.h!="char" && ww.h!="double" && ww.h!="long") return NULL;
	root=new node();//����һ�������������������root
	root1=new node();//����һ���ֲ��������ͽ��root1 
	root1->name="          ���ͣ�"+ww.h+"\n";
	root->lchild=root1;
	root1->lchild=NULL;
	root0=new node();//����һ���������������root0
	root0->name="          VAR_NAME��\n";
	root1->rsibling=root0;
	root0->rsibling=NULL;
	root2=new node();//����һ���ֲ��������н��root2 
	root2->name="            ID��";
	root2->rsibling=NULL;
	root0->lchild=root2;
	p=new node();//����һ���ֲ����������p
	root2->lchild=p;
	ww=gettoken();//wwȡ���ֲ������� 
	p->name=ww.h+"\n";
	p->lchild=NULL; 
	ww=gettoken();//wwȡ��";"��"," 
	if(ww.g==5) ww=gettoken();
	while(1){//ÿ���ֲ��������н��ĵ�һ�����Ӷ�Ӧһ�������� 
		if (ww.h!=";" && ww.h!=","){
			cout<<"�ֲ��������岿�֣�"<<"Error12 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
			errors+=1;
			delete(root);delete(root1);delete(root2);delete(p);delete(root0);
			return NULL;
		}//ww����";"��","�������ͷ�rootΪ����ȫ����㣬���ؿ�ָ��
		if (ww.h==";"){
			ww=gettoken();//wwȡ��";"֮��ĵ�һ���ַ�
			break;
		}//����";"��һ���ֲ�����������������������ѭ�� 
		ww=gettoken();//��ʼʶ������ı�����
		if (ww.g!=1){
			cout<<"�ֲ��������岿�֣�"<<"Error13 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
			errors+=1;
		    delete(root);delete(root1);delete(root2);delete(p);
			return NULL;
		}//ww���Ǳ�ʶ���������ͷ�rootΪ����ȫ����㣬���ؿ�ָ��
		q=new node();//����һ���ֲ��������н��q
		q->name="            ID��";
		p->rsibling=q; 
		q->rsibling=NULL;
		h=new node();//����һ���ֲ����������h
		h->name=ww.h+"\n";
		q->lchild=h;
		h->lchild=NULL;
		p=h;
		ww=gettoken();
	}
	return root;	
}//����ʱwwȡ���ֲ��������������";"֮��ĵ�һ���ַ� 
//������������䲿��(�������) 
tree SenList(){
	tree root,root1,root2;
	root1=statement();//���ô���һ�������ӳ��� 
	if (root1==NULL) {
		if(errors>0) {
			cout<<"����������䲿�֣�"<<"Error14 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
			errors+=1;
			delete(root);
			return NULL;
		}
		else return NULL;
	} 
	else{
		root=new node();//����һ�����������䲿�ֽ��root
	    root->rsibling=NULL;
	    root->lchild=root1;
	    root2=SenList();
	    root1->rsibling=root2;
	    return root;
	}
} 
//����һ����� 
tree statement(){//��ʱwwȡ�����ĵ�һ���ַ� 
	if (ww.h=="if") {
		ww=gettoken();//wwȡ��if����ĵ�һ���ַ�"("
		if(ww.h!="(") {
			cout<<"��䲿�֣�"<<"Error15 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
			errors+=1;
			return NULL;
		} 
		ww=gettoken();//wwȡ��"("����ĵ�һ���ַ�
		tree p,q,h,root,a,b,c;
		p=exp();//���ô�����ʽ���ӳ��򣬽���ʱwwȡ��")"֮��ĵ�һ���ַ���if�Ӿ�ĵ�һ���ַ�,pΪif�����������ʽ�������ָ��
		q=statement();//���ô���һ�������ӳ��򣬵õ�if�Ӿ��������ָ�룬ȷ������ʱwwȡ��";"��"}"֮��ĵ�һ���ַ���if��������ĵ�һ���ַ�
		if(ww.h=="else") {
			ww=gettoken();
			h=statement();//���ô���һ�������ӳ��򣬵õ�else�Ӿ��������ָ�룬ȷ������ʱwwȡ��";"��"}"֮��ĵ�һ���ַ���if��������ĵ�һ���ַ�
			root=new node();//����һ��if-else�����
			root->name="        �������(IF_THEN_ELSE)��\n";
			a=new node();//����һ�����������
			a->name="          ������\n"; 
			root->lchild=a;
			a->lchild=p;
			b=new node();//����һ��if�Ӿ���
			b->name="          IF�Ӿ䣺\n"; 
			a->rsibling=b; 
			b->lchild=q;
			c=new node();//����һ��else�Ӿ���
			c->name="          ELSE�Ӿ䣺\n"; 
			c->lchild=h;
			b->rsibling=c;
			c->rsibling=NULL;
			root->rsibling=NULL;;
			return root;
		} 
		else{
			root=new node();//����һ��if�����
			root->name="        �������(IF_THEN)��\n";
			a=new node();//����һ�����������
			a->name="          ������\n"; 
			b=new node();//����һ��if�Ӿ���
			b->name="          IF�Ӿ䣺\n";
			root->rsibling=NULL;
			root->lchild=a;
			a->rsibling=b;
			b->rsibling=NULL;
			a->lchild=p;
			b->lchild=q;
			return root;
		} 	 
	}//����ʱwwȡ��";"��"}"֮��ĵ�һ���ַ���if��������ĵ�һ���ַ� 
	if (ww.h=="{") {
		tree root0;
		root0=ComSen();
		return root0;
	}//����ʱwwȡ��"}"֮��ĵ�һ���ַ�  
	if(ww.h=="while") {
		ww=gettoken();//wwȡ��while����ĵ�һ���ַ�"("
		if(ww.h!="(") {
			cout<<"��䲿�֣�"<<"Error16 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
			errors+=1;
			return NULL;
		} 
		ww=gettoken();//wwȡ��"("����ĵ�һ���ַ�
		tree root1,root2,root3,m,n;
		root1=exp();//���ô�����ʽ���ӳ��򣬽���ʱwwȡ��")"֮��ĵ�һ���ַ���while�Ӿ�ĵ�һ���ַ� ,root1Ϊwhile�����������ʽ�������ָ�� 
		root2=statement();//���ô���һ�������ӳ��򣬵õ�while�Ӿ��������ָ�룬ȷ������ʱwwȡ��";"��"}"֮��ĵ�һ���ַ���while��������ĵ�һ���ַ�
		root3=new node();//����һ��while�����
		root3->name="        WHILE��䣺\n";
		root3->rsibling=NULL;
		m=new node();//����һ�����������
		m->name="          ������\n"; 
		root3->lchild=m;
		n=new node();//����һ��while�Ӿ���
		n->name="          WHILE�Ӿ䣺\n"; 
		m->rsibling=n; 
		n->lchild=root2;
		n->rsibling=NULL;
		m->lchild=root1;
		return root3;
	}//����ʱwwȡ��";"��"}"֮��ĵ�һ���ַ���while��������ĵ�һ���ַ� 
	if(ww.h=="return") {
		tree root4,root5;
		root4=new node();//����һ��return�����
		root4->name="        ������䣺\n";
		ww=gettoken();//wwȡ��return֮��ĵ�һ���ַ� 
		root5=exp();//���ô�����ʽ���ӳ��򣬽���ʱwwȡ��";"֮��ĵ�һ���ַ� 
		root4->lchild=root5;
		root4->rsibling=NULL;
		return root4;
	}//����ʱwwȡ��";"֮��ĵ�һ���ַ���return��������ĵ�һ���ַ�   
	if(ww.h=="break"){
		tree root6;
		root6=new node();//����һ��break�����
		root6->name="        BREAK��䣺\n";
		root6->rsibling=NULL;
		root6->lchild=NULL;
		ww=gettoken();//wwȡ��";"
		if(ww.h!=";") {
			cout<<"��䲿�֣�"<<"Error17 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
			errors+=1;
			return NULL;
		}  
		ww=gettoken();//wwȡ��";"֮��ĵ�һ���ַ�
		return root6; 
	}//����ʱwwȡ��";"֮��ĵ�һ���ַ�,break��������ĵ�һ���ַ� 
	if(ww.h=="continue"){
		tree root7;
		root7=new node();//����һ��continue�����
		root7->name="        CONTINUE��䣺\n";
		root7->rsibling=NULL;
		root7->lchild=NULL;
		ww=gettoken();//wwȡ��";"
		if(ww.h!=";") {
			cout<<"��䲿�֣�"<<"Error18 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
			errors+=1;
			return NULL;
		}  
		ww=gettoken();//wwȡ��";"֮��ĵ�һ���ַ�
		return root7; 
	}//����ʱwwȡ��";"֮��ĵ�һ���ַ�,continue��������ĵ�һ���ַ�  
	if(ww.h=="for"){
		ww=gettoken();//wwȡ��for֮��ĵ�һ���ַ�"("
		if(ww.h!="(") {
			cout<<"��䲿�֣�"<<"Error19 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
			errors+=1;
			return NULL;
		}  
		tree root8,root9,root10,root11,root12,x,y,z,i;
		root8=new node();//����һ��for�����
		root8->name="        FOR��䣺\n";
		root8->rsibling=NULL;
		ww=gettoken();//wwȡ��"("֮��ĵ�һ���ַ�
		root9=exp();//���ô�����ʽ���ӳ��򣬽���ʱwwȡ��";"֮��ĵ�һ���ַ�
		root10=exp();//���ô�����ʽ���ӳ��򣬽���ʱwwȡ��";"֮��ĵ�һ���ַ�
		root11=exp();//���ô�����ʽ���ӳ��򣬽���ʱwwȡ��")"֮��ĵ�һ���ַ�
		root12=statement();//���ô���һ�������ӳ��򣬵õ�for�Ӿ��������ָ�룬ȷ������ʱwwȡ��";"��"}"֮��ĵ�һ���ַ���for��������ĵ�һ���ַ�
		x=new node();//����һ������ֵ�����
		x->name="          ����ֵ��\n"; 
		root8->lchild=x;
		x->lchild=root9;
		y=new node();//����һ�����������
		y->name="          ������\n";  
		x->rsibling=y;
		y->lchild=root10;
		z=new node();//����һ����ֵ�����
		z->name="          ��ֵ��\n";
		y->rsibling=z;
		z->lchild=root11;  
		i=new node();//����һ��for�Ӿ���
		i->name="          FOR�Ӿ䣺\n"; 
		z->rsibling=i;
		i->rsibling=NULL;
		i->lchild=root12;
		return root8;
	}//����ʱwwȡ��";"��"}"֮��ĵ�һ���ַ���for��������ĵ�һ���ַ�
	if(ww.g==1) {
		tree root13;
		root13=exp();
		return root13;
	}//����ʱwwȡ��";"֮��ĵ�һ���ַ�
	if(ww.g==2 || ww.g==4 || ww.g==6 || ww.g==5) {
		tree root14;
		root14=exp();
		return root14;
	}//����ʱwwȡ��";"֮��ĵ�һ���ַ�
	if(ww.h=="}"){
		return NULL;
	}
	if(ww.h=="(") {
		tree root15;
		root15=exp();
		return root15;
	}//����ʱwwȡ��")"֮��ĵ�һ���ַ�
	cout<<"��䲿�֣�"<<"Error20 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
	errors+=1;
	return NULL;//��������������㣬���� 
}
//��������ȼ��ж� 
char precede(string a,string b){
    int i,j;
    char pre[][17]={//�����֮������ȼ�������һ�ű��         
        {'>','>','<','<','<','>','0','>','>','>','>','>','>','>','<','>','>'},
        {'>','>','<','<','<','>','0','>','>','>','>','>','>','>','<','>','>'},
        {'>','>','>','>','<','>','0','>','>','>','>','>','>','>','>','>','>'},
        {'>','>','>','>','<','>','0','>','>','>','>','>','>','>','>','>','>'},
        {'<','<','<','<','<','=','0','>','>','>','>','>','>','>','<','>','>'},
        {'>','>','>','>','>','0','0','>','>','>','>','>','>','>','>','>','>'},
        {'<','<','<','<','<','0','<','<','<','<','<','>','<','<','<','<','<'},
        {'<','<','<','<','<','>','0','>','>','>','>','>','>','>','<','>','>'},
        {'<','<','<','<','<','>','0','>','>','>','>','>','>','>','<','>','>'},
        {'<','<','<','<','<','>','0','<','<','>','>','>','>','>','<','<','<'},
        {'<','<','<','<','<','>','0','<','<','>','>','>','>','>','<','<','<'},
        {'<','<','<','<','<','0','<','<','<','<','<','=','<','<','<','<','<'},
        {'<','<','<','<','<','>','0','<','<','<','<','>','>','>','<','<','<'},
        {'<','<','<','<','<','>','0','<','<','<','<','>','<','>','<','<','<'},
        {'>','>','>','>','<','>','0','>','>','>','>','>','>','>','>','>','>'},
        {'<','<','<','<','<','>','0','>','>','>','>','>','>','>','<','>','>'},
		{'<','<','<','<','<','>','0','>','>','>','>','>','>','>','<','>','>'},
		};
    if (a=="+") i=0;
    else if (a=="-") i=1;
	else if (a=="*") i=2;
	else if (a=="/") i=3;
	else if (a=="(") i=4;
	else if (a==")") i=5;
	else if (a=="=") i=6;
	else if (a==">") i=7;
	else if (a=="<") i=8;
	else if (a=="==") i=9;
	else if (a=="!=") i=10;
	else if (a=="#") i=11;
	else if (a=="&&") i=12;
	else if (a=="||") i=13;
	else if (a=="%") i=14;
	else if (a==">=") i=15;
	else if (a=="<=") i=16; 
	else{
		cout<<"���ʽ���֣�"<<"Error21 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
	    errors+=1;
	}
	if (b=="+") j=0;
    else if (b=="-") j=1;
	else if (b=="*") j=2;
	else if (b=="/") j=3;
	else if (b=="(") j=4;
	else if (b==")") j=5;
	else if (b=="=") j=6;
	else if (b==">") j=7;
	else if (b=="<") j=8;
	else if (b=="==") j=9;
	else if (b=="!=") j=10;
	else if (b=="#") j=11;
	else if (b=="&&") j=12;
	else if (b=="||") j=13;
	else if (b=="%") j=14;
	else if (b==">=") j=15;
	else if (b=="<=") j=16;
	else{
		cout<<"���ʽ���֣�"<<"Error22 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
	    errors+=1;
	}
    if(0<=i<=16 && 0<=j<=16) return pre[i][j];
}
//�ж��Ƿ�������� 
int CalSym(string b){
	if(b=="+" || b=="-" || b=="*" || b=="/" || b=="(" || b==")" || b=="=" || b==">" || b=="<" || b=="==" || b=="!=" ||\
    b=="#" || b=="&&" || b=="||" || b=="%" || b==">=" || b=="<=") return 1;
    else return 0;
}
//������ʽ 
tree exp(){//���ø��㷨ʱ���Ѿ������˵�һ���ַ���ww��
	stack<string>op;//���������ջ op
	stack<tree>opn;//���������ջopn
	op.push("#");//����ֹ��"#"��ջ
	string t;
	tree t1,t2;
	while ((ww.h!="#" || op.top()!="#") && !errors ){
		if(ww.g==1 || ww.g==2 || ww.g==4 || ww.g==6 || ww.g==5){
			tree root0;
			root0=new node();
			root0->name="              ID��"+ww.h+"\n";
			opn.push(root0);
			ww=gettoken();}
		else if(CalSym(ww.h)) {
			switch(precede(op.top(),ww.h))
			{
				case '<':op.push(ww.h);ww=gettoken();break;
				case '=':if(op.size()) 	{t=op.top();op.pop();}
				         else errors++;ww=gettoken();break;
				case '>':if(opn.size()) {t2=opn.top();opn.pop();} 
			             else errors++;   
			             if(opn.size()) {t1=opn.top();opn.pop();} 
			             else errors++;   
                         if(op.size()) {t=op.top();op.pop();} 
			             else errors++;   
                         tree root1,root2,root3,root4;
                         root1=new node();//����һ�������� 
                         root1->rsibling=NULL;
                         root2=new node();
                         root2->name="            �������"+t+"\n";//����һ���������� 
                         root1->lchild=root2;
                         root2->rsibling=NULL;
                         root3=t1;//����һ�����������
                         root2->lchild=root3;
                         root4=t2;//����һ�����������
                         root3->rsibling=root4;
                         opn.push(root1);
						 break;
				default:if(ww.h==")") ww.h="#";
				        else {
				        	errors++;
				        	cout<<"���ʽ���֣�"<<"Error23 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
				        	return NULL;
						}								                        
			}			
		}
		else if(ww.h==";") ww.h="#";
		else {
				errors++;
		    	cout<<"���ʽ���֣�"<<"Error24 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
				return NULL;
			}			 		
		}
		if(opn.size()==1 && op.top()=="#" && !errors)	{ww=gettoken();return opn.top();
		}
		else return NULL;	
	} 
int visit(node a)	{
	cout<<a.name;
	return 1;
}
//��������﷨�� 
int PrintTree(tree root){
	if(root) {if(visit(*root))//����visit���� 
	if(PrintTree(root->lchild))//�ݹ�ǰ������������� 
	if(PrintTree(root->rsibling)) return 1;//�ݹ�ǰ��������ֵ����� 
	return 0;
	}else return 1;
} 
int main()
{
	char w;
	int j;
	int line=0;
	FILE *fp;
	fp=fopen("s.txt","r+");
	while(!feof(fp)){
		w=fgetc(fp);
	}
	fclose(fp);
    freopen("s.txt","r",stdin);
    freopen("result.txt","w",stdout); 
	length=0;
	while(cin>>w){
		if(w!=' '){
			letter[length]=w;
			length++;
	    } //ȥ�������еĿո�  
	}
	cout<<"�������"<<"  "<<"����ֵ"<<endl; 
	TakeWord();
	WordList();
	tree root;
	int i;
	root=program();
   if (PrintTree(root)==1) cout<<"�����ɹ���"<<endl;
    else cout<<"����ʧ�ܣ�"<<endl; 
	cout<<"\n";
    fclose(stdin);//�ر��ļ� 
    fclose(stdout);//�ر��ļ� 
    return 0;
}
