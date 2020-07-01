#include<iostream>
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#include<stack> 
#define INITSIZE 1000
using namespace std;
 
//关键字 
string key[15]={"main","int","if","else","while","float","char","break","case","long","continue","double","for","return","void"}; 
//运算符和界符 
string symbol[30]={"<",">","!=",">=","<=","==",",",";","(",")","{","}","+","-","*","/","=","+=","-=","_","//","#","%",":","||","&&","*=","/=","%=","^"};
//运算符和界符的名称 
string symbolName[30]={"小于号","大于号","不等于号","大于等于号","小于等于号","等于号","逗号","分号","左小括号","右小括号","左大括号","右大括号",
"加号","减号","乘号","除号","赋值号","加法赋值","减法赋值","下划线","注释","井号","求余号","冒号","或","且","乘法赋值","除法赋值","求余赋值","乘方"};
string letter[1000];//存放文件取出的字符 
int length;//保存程序中字符的数目 
int num; 
int p;
int z=0;
int oo=0;
int errors=0;
struct key{
	string h;//单词内容
	int g;//单词种类 
};//存放识别出的单个单词 
struct key ww;
struct key kind,idt;
struct key Words[1000];//存放识别出的所有单词 
//调用一次，取一个单词 
struct key gettoken(){
	ww.h=Words[oo].h;
	ww.g=Words[oo].g;
	oo++;
	return ww;
}; 
//判断是否为运算符和界符 
int isSymbol(string s){ 
 int i;
 for(i=0;i<30;i++){
  if(s==symbol[i])
   return i; 
 }
 return 0;
} 
//判断是否为关键字 
int isKeyWord(string s){
 int i;
 for(i=0;i<15;i++){
  if(s==key[i])
   return 1;
 }
 return 0;
}
//判断是否为数字 
bool isNum(string s){
 if(s>="0" && s<="9")
  return true;
 return false;
}
//判断是否为字母 
bool isLetter(string s)
{
 if((s>="a" && s<="z")||(s>="A" && s<="Z"))
  return true;
 return false;
}
//返回单个字符的类型 
int typeword(string str){
 if((str>="a" && str<="z")||(str>="A" && str<="Z")) // 字母 
  return 1; 
 if(str>="0" && str<="9") //数字 
  return 2;
 if(str==">"||str=="="||str=="<"||str=="!"||str==","||str==";"||str=="("||str==")"||str=="{"||str=="}"||str=="+"||str=="-"
 ||str=="*"||str=="/"||str=="#"||str=="&"||str=="^"||str=="%"||str==":"||str=="|"||str=="_") //判断运算符和界符(第一位) 
  return 3; 
 if(str=="'") //判断字符型常量
  return 4;  
 if(str=="[") //判断数组
  return 5;
 if(str=="\"") //判断字符串
  return 6; 
}
//返回关键字或标识符 
string identifier(string s,int n){
 int j=n+1;
 int flag=1;//进入循环 
 while(flag){
  if(isNum(letter[j])||isLetter(letter[j])||letter[j]=="_"){
   s=s+letter[j];
   if(isKeyWord(s)){
    j++;
    num=j;
    return s;//返回关键字 
   }
   j++;
  }
  else{
   flag=0;//遇到运算符和界符，跳出循环 
  }
 } 
 num=j;
 return s;//返回标识符 
}
//返回运算符和界符  
string symbolStr(string s,int n){//s是运算符和界符(第一位)  
 int j=n+1;
 string str=letter[j];//str取下一位 
 if(str=="="||str=="&"||str=="|"||str=="/") {//判断str是否是运算符和界符的第二位 
  s=s+letter[j];
  j++;
 }
 num=j;
 return s;//返回运算符和界符 
}
//返回数字 
string Number(string s,int n){
 int j=n+1;
 int flag=1;
 p=1; 
 while(flag){
  if(isNum(letter[j]) || letter[j]=="x" || letter[j]=="X"){
   s=s+letter[j];
   j++;//整型常量 
  }
  else if(letter[j]=="." || letter[j]=="f" || letter[j]=="F"){
   s=s+letter[j];
   j++;
   p=2;//浮点型常量 
  }
  else if(letter[j]=="L" || letter[j]=="l"){
   s=s+letter[j];
   j++;
   p=3;//长整型常量 
  }  
  else{
   flag=0;
  }
 }
 num=j;
 return s;//返回数字 
}
//返回字符常量 
string charConst(string s,int n){
 int j=n+1;
 s=s+letter[j];	
 j++;
 s=s+letter[j];
 num=j+1;
 return s;//返回字符常量
}
//返回数组
string array(string s,int n){
 int j=n+1;
 while(letter[j-1]!="]")
 {
 	s=s+letter[j];
 	j++;
 }
 num=j;
 return s;//返回数组 
} 
//返回字符串常量
string charList(string s,int n){
 int j=n+1;
 while(letter[j]!="\"")
 {
 	s=s+letter[j];
 	j++;
 }
 s=s+letter[j];
 num=j+1;
 return s;//返回字符串常量
}  
//取单词并输出词法分析结果  
void TakeWord(){ 
 int k;
 for(num=0;num<length;){
  string str1,str;
  str=letter[num];
  k=typeword(str);//k为单个字符的类型  
  switch(k){
   case 1:
    {
     str1=identifier(str,num);
     if(isKeyWord(str1))
      cout<<"关键字"<<"  "<<str1<<endl;
     else
      cout<<"标识符"<<"  "<<str1<<endl;
     break;
    }
   case 2:
    {
     str1=Number(str,num);
     if(p==1)  cout<<"整型常量"<<"  "<<str1<<endl;
     else if(p==2)  cout<<"浮点型常量"<<"  "<<str1<<endl;
     else if(p==3)  cout<<"长整型常量"<<"  "<<str1<<endl;  
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
     cout<<"字符型常量"<<"  "<<str1<<endl;
     break;
	}
	case 5:
	{
     str1=array(str,num);
     cout<<"数组"<<"  "<<str1<<endl;
     break;
	}	
	case 6:
	{
     str1=charList(str,num);
     cout<<"字符串常量"<<"  "<<str1<<endl;
     break;
	}
  }
 } 
}
//逐个将单词存入线性表 
void WordList(){
 int k;
 for(num=0;num<length;){
  string str1,str,str2,str3,str4,str5,str6;
  str=letter[num];
  int m=0;
  k=typeword(str);//k为单个字符的类型  
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
	struct node *lchild;//左孩子指针 
	struct node *rsibling;//右兄弟指针 
	string name; 
}*tree,node;
//函数声明
tree program();//处理程序 
tree ExtDefList();//处理外部定义序列 
tree ExtDef();//处理外部定义 
tree ExtVarDef();//处理外部变量定义
tree FuncDef();//处理函数定义
tree Para();//处理函数形参 
tree ComSen();//处理复合语句
tree InVarDef();//处理局部变量定义 
tree SenList();//处理复合语句的语句部分(语句序列) 
tree statement();//处理一条语句
tree exp();//处理表达式 
int PrintTree(tree root);//输出抽象语法树 
char precede(string a,string b);//运算符优先级判断 
int visit();
//处理程序 
tree program(){
	ww=gettoken();
	tree root;
	root=ExtDefList();//程序返回的语法树根结点指针，可遍历显示
	if (root!=NULL) return root;
	else {
		cout<<"Error!"<<endl;;//程序出现语法错误 
		return NULL;
	}
}
//处理外部定义序列 
tree ExtDefList(){
	if(ww.h=="") return NULL;
	if(errors!=0) return NULL;
	tree root,root1,root2;
	root=new node();//生成一个外部定义序列结点root 
	root->rsibling=NULL;
	root1=ExtDef();//处理一个外部定义，得到一棵子树，作为root的第一棵子树
	root->lchild=root1; 
	root2=ExtDefList();//递归调用，得到的子树，作为root的第二棵子树
	root1->rsibling=root2; 
	return root;
}
//处理外部定义 
tree ExtDef(){
	if(ww.h!="int" && ww.h!="float" && ww.h!="char" && ww.h!="double" && ww.h!="void" && ww.h!="long"){
		cout<<"外部定义部分："<<"Error1 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
		errors+=1;
		return NULL;
	}//ww不是类型关键字,报错并返回NULL
	kind=ww;
	ww=gettoken();
	if(ww.g!=1){
		cout<<"外部定义部分："<<"Error2 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
		errors+=1;
		return NULL;
	}//ww不是标识符,报错并返回NULL 
	idt=ww; 
	tree p;
	ww=gettoken();
	if (ww.h!="(") p=ExtVarDef();//调用外部变量定义子程序   
	else p=FuncDef();//调用函数定义子程序
	return p; 
}
//处理外部变量定义 
tree ExtVarDef(){//调用此子程序时，外部变量类型和第一个变量名的单词已经读入，变量类型保存在kind中，变量名保存在idt中，此时的ww是符号","或";" 
	tree root,root0,root1,root2,p,q,h;
	if(ww.g==5) ww=gettoken();
	root=new node();//生成一个外部变量定义结点root 
	root->name="外部变量定义：\n";
	root->rsibling=NULL;
	root1=new node();//生成一个外部变量类型结点root1 
	root1->name="    类型："+kind.h+"\n";
	root->lchild=root1;
	root1->lchild=NULL;
	root0=new node();//生成一个变量名声明结点root0
	root0->name="    变量名：\n";
	root1->rsibling=root0;
	root0->rsibling=NULL;
	root2=new node();//生成一个外部变量序列结点root2 
	root2->name="      ID：";
	root2->rsibling=NULL;
	root0->lchild=root2;
	p=new node();//生成一个外部变量名结点p
	root2->lchild=p;
	p->name=idt.h+"\n";
	p->lchild=NULL; 
	while(1){//每个外部变量序列结点的第一个孩子对应一个变量名 
		if (ww.h!=";" && ww.h!=","){
			cout<<"外部变量定义部分："<<"Error3 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
			errors+=1;
			delete(root);delete(root1);delete(root2);delete(p);delete(root0);
			return NULL;
		}//ww不是";"和","，报错，释放root为根的全部结点，返回空指针
		if (ww.h==";"){
			ww=gettoken();//ww取到";"之后的第一个字符
			return root;
		}//遇到";"，外部变量定义子树结束 
		ww=gettoken();//开始识别后续的变量名
		if (ww.g!=1){
			cout<<"外部变量定义部分："<<"Error4 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
			errors+=1;
			delete(root);delete(root1);delete(root2);delete(p);
			return NULL;
		}//ww不是标识符，报错，释放root为根的全部结点，返回空指针
		q=new node();//生成一个外部变量序列结点q
		q->name="      ID：";
		p->rsibling=q; 
		q->rsibling=NULL;
		h=new node();//生成一个外部变量名结点h
		h->name=ww.h+"\n";
		q->lchild=h;
		h->lchild=NULL;
		p=h;
		ww=gettoken();
	}
}//结束时ww取到";"之后的第一个字符串  
//处理函数定义 
tree FuncDef(){//调用此子程序时，函数返回值类型和函数名的单词已经读入，函数返回值类型保存在kind中，函数名保存在idt中，此时的ww是符号"("
	tree root,root1,root0,root2,p,h;
	root=new node();//生成一个函数定义结点root 
	root->name="函数定义：\n";
	root->rsibling=NULL;
	root1=new node();//生成一个函数返回值类型结点root1 
	root1->name="    类型："+kind.h+"\n";
	root->lchild=root1;
	root1->lchild=NULL;
	root0=new node();//生成一个函数名结点root0
	root0->name="    函数名：" +idt.h+"\n";
	root1->rsibling=root0;
	root2=new node();//生成一个函数形参声明结点root2
	root0->lchild=root2;
	root2->name="    函数形参：\n";
	p=Para();//调用函数形参子程序,调用后ww取到 ")"之后的第一个字符
	root2->lchild=p; 
	h=ComSen();//调用复合语句子程序
	root0->rsibling=h; 
	return root;
}
//处理函数形参 
tree Para(){//调用此子程序时，ww是符号"(",未传入形参信息 
	tree root,root1,root2,q,h,p;
	ww=gettoken();//ww取到形参类型或无参取到")" 
	if(ww.h==")"){//无参函数 
		ww=gettoken();//ww取到")"之后的第一个字符 
		return NULL;
	}
	if(ww.h!="int" && ww.h!="float" && ww.h!="char" && ww.h!="double" && ww.h!="void" && ww.h!="lomg"){
		cout<<"函数形参部分："<<"Error5 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
		errors+=1;
		return NULL;
	}//ww不是类型关键字,报错并返回NULL	 
	if(ww.h=="void"){//无参函数 
		ww=gettoken();
		if(ww.h!=")"){
			cout<<"函数形参部分："<<"Error6 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
			errors+=1;
		    return NULL;
		}
		ww=gettoken();//ww取到")"之后的第一个字符 
		return NULL;
	}
	root=new node();//生成一个函数形参类型声明结点root 
	root->name="      类型：";
	root->rsibling=NULL;
	root1=new node();//生成一个函数形参类型结点root1
	root->lchild=root1;
	root1->name=ww.h+" , ";
	root1->lchild=NULL;
	ww=gettoken();//ww取到函数形参名 
	root2=new node();//生成一个函数形参名结点root2
	root2->name="参数名："+ww.h+"\n";
	root1->rsibling=root2;
	root2->rsibling=NULL;
	ww=gettoken();//ww取到","或")"
	while(1){ 
		if (ww.h!=")" && ww.h!=","){
			cout<<"函数形参部分："<<"Error7 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
			errors+=1;
			delete(root);delete(root1);delete(root2);
			return NULL;
		}//ww不是")"和","，报错，释放root为根的全部结点，返回空指针
		if (ww.h==")"){
			ww=gettoken();//ww取到")"之后的第一个字符
			return root;
		}//遇到")"，函数形参子树结束 
		ww=gettoken();//开始识别后续的变量名,ww取到函数形参类型 
		if (ww.h!="int" && ww.h!="float" && ww.h!="char" && ww.h!="double" && ww.h!="long"){
			cout<<"函数形参部分："<<"Error8 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
			errors+=1;
			delete(root);delete(root1);delete(root2); 
			return NULL;
		}//ww不是类型关键字，报错，释放root为根的全部结点，返回空指针 
		q=new node();//生成一个函数形参类型声明结点q
		q->name="      类型：";
		root2->lchild=q; 
		q->rsibling=NULL;
		h=new node();//生成一个函数形参类型结点h
		h->name=ww.h+" , ";
		q->lchild=h;
		h->lchild=NULL;
		p=new node();//生成一个函数形参名结点p
		ww=gettoken();
		if (ww.g!=1){
			cout<<"函数形参部分："<<"Error9 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
			errors+=1;
			delete(root);delete(root1);delete(root2);delete(p);delete(q);delete(h);
			return NULL;
		}//ww不是标识符，报错，释放root为根的全部结点，返回空指针
		p->name="参数名："+ww.h+"\n";
		h->rsibling=p; 
		p->rsibling=NULL;
		root2=p;
		ww=gettoken();
	}
}//结束时ww取到 ")"之后的第一个字符
//处理复合语句 
tree ComSen(){//调用此子程序时，ww取到";"或"{" 
	if(ww.h!=";" && ww.h!="{"){
		cout<<"复合语句部分："<<"Error10 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
		errors+=1;
		return NULL;
	}
	tree root,root1,root2,root3,root4,root5,p,q;
	root=new node();//生成一个复合语句结点root
	root->name="    复合语句：\n";
	root->rsibling=NULL;
	if(ww.h==";"){//函数声明，复合语句子树为空 
		ww=gettoken();//ww取到函数声明结束，";"之后的第一个字符 
	
		root->lchild=NULL;
		return root; 
	}
	ww=gettoken();//ww取到"{"之后的第一个字符
	root1=new node();//生成一个复合语句变量声明结点root1
	root1->name="      复合语句的变量定义：\n"; 
	root3=new node();//生成一个语句部分声明结点root3 
	root->lchild=root1; 
	root2=new node();//生成一个复合语句变量声明结点root2
	root2->name="        LOCAL VAR_NAME：\n";
	root1->lchild=root2;
	root2->rsibling=NULL;
	root1->rsibling=root3;
	root3->name="      复合语句的语句部分：\n";
	root3->rsibling=NULL;
	while(ww.h!="}"){
	if(ww.h=="int" || ww.h=="float" || ww.h=="char" || ww.h=="double" || ww.h=="long"){
		p=InVarDef();//调用处理局部变量定义子程序 
		root2->lchild=p;
		root4=new node();
		p->rsibling=root4;
		root2=root4;//递归作用	
	}//ww取到";"之后的第一个字符 
	else{
	q=SenList();//调用处理语句序列子程序，结束时ww取到"}" 
	root3->lchild=q;
	root5=new node();
	q->rsibling=root5;
	root3=root5;//递归作用	
    }
} 
	if(ww.h!="}"){
		cout<<"复合语句部分："<<"Error11 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
		errors+=1;
		delete(root);delete(root1);delete(root3); 
		return NULL;
	}
	ww=gettoken();//ww取到"}"之后的第一个字符 
	return root;
}//结束时ww取到"}"之后的第一个字符  
//处理局部变量定义 
tree InVarDef(){//ww取到复合语句中的变量类型字符 
	tree root,root0,root1,root2,p,q,h,root3;
	if (ww.h!="int" && ww.h!="float" && ww.h!="char" && ww.h!="double" && ww.h!="long") return NULL;
	root=new node();//生成一个复合语句变量声明结点root
	root1=new node();//生成一个局部变量类型结点root1 
	root1->name="          类型："+ww.h+"\n";
	root->lchild=root1;
	root1->lchild=NULL;
	root0=new node();//生成一个变量名声明结点root0
	root0->name="          VAR_NAME：\n";
	root1->rsibling=root0;
	root0->rsibling=NULL;
	root2=new node();//生成一个局部变量序列结点root2 
	root2->name="            ID：";
	root2->rsibling=NULL;
	root0->lchild=root2;
	p=new node();//生成一个局部变量名结点p
	root2->lchild=p;
	ww=gettoken();//ww取到局部变量名 
	p->name=ww.h+"\n";
	p->lchild=NULL; 
	ww=gettoken();//ww取到";"或"," 
	if(ww.g==5) ww=gettoken();
	while(1){//每个局部变量序列结点的第一个孩子对应一个变量名 
		if (ww.h!=";" && ww.h!=","){
			cout<<"局部变量定义部分："<<"Error12 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
			errors+=1;
			delete(root);delete(root1);delete(root2);delete(p);delete(root0);
			return NULL;
		}//ww不是";"和","，报错，释放root为根的全部结点，返回空指针
		if (ww.h==";"){
			ww=gettoken();//ww取到";"之后的第一个字符
			break;
		}//遇到";"，一个局部变量定义子树结束，跳出循环 
		ww=gettoken();//开始识别后续的变量名
		if (ww.g!=1){
			cout<<"局部变量定义部分："<<"Error13 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
			errors+=1;
		    delete(root);delete(root1);delete(root2);delete(p);
			return NULL;
		}//ww不是标识符，报错，释放root为根的全部结点，返回空指针
		q=new node();//生成一个局部变量序列结点q
		q->name="            ID：";
		p->rsibling=q; 
		q->rsibling=NULL;
		h=new node();//生成一个局部变量名结点h
		h->name=ww.h+"\n";
		q->lchild=h;
		h->lchild=NULL;
		p=h;
		ww=gettoken();
	}
	return root;	
}//结束时ww取到局部变量定义结束，";"之后的第一个字符 
//处理复合语句的语句部分(语句序列) 
tree SenList(){
	tree root,root1,root2;
	root1=statement();//调用处理一条语句的子程序 
	if (root1==NULL) {
		if(errors>0) {
			cout<<"复合语句的语句部分："<<"Error14 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
			errors+=1;
			delete(root);
			return NULL;
		}
		else return NULL;
	} 
	else{
		root=new node();//生成一个复合语句语句部分结点root
	    root->rsibling=NULL;
	    root->lchild=root1;
	    root2=SenList();
	    root1->rsibling=root2;
	    return root;
	}
} 
//处理一条语句 
tree statement(){//此时ww取到语句的第一个字符 
	if (ww.h=="if") {
		ww=gettoken();//ww取到if后面的第一个字符"("
		if(ww.h!="(") {
			cout<<"语句部分："<<"Error15 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
			errors+=1;
			return NULL;
		} 
		ww=gettoken();//ww取到"("后面的第一个字符
		tree p,q,h,root,a,b,c;
		p=exp();//调用处理表达式的子程序，结束时ww取到")"之后的第一个字符，if子句的第一个字符,p为if语句的条件表达式子树结点指针
		q=statement();//调用处理一条语句的子程序，得到if子句的子树根指针，确保结束时ww取到";"或"}"之后的第一个字符，if语句结束后的第一个字符
		if(ww.h=="else") {
			ww=gettoken();
			h=statement();//调用处理一条语句的子程序，得到else子句的子树根指针，确保结束时ww取到";"或"}"之后的第一个字符，if语句结束后的第一个字符
			root=new node();//生成一个if-else语句结点
			root->name="        条件语句(IF_THEN_ELSE)：\n";
			a=new node();//生成一个条件语句结点
			a->name="          条件：\n"; 
			root->lchild=a;
			a->lchild=p;
			b=new node();//生成一个if子句结点
			b->name="          IF子句：\n"; 
			a->rsibling=b; 
			b->lchild=q;
			c=new node();//生成一个else子句结点
			c->name="          ELSE子句：\n"; 
			c->lchild=h;
			b->rsibling=c;
			c->rsibling=NULL;
			root->rsibling=NULL;;
			return root;
		} 
		else{
			root=new node();//生成一个if语句结点
			root->name="        条件语句(IF_THEN)：\n";
			a=new node();//生成一个条件语句结点
			a->name="          条件：\n"; 
			b=new node();//生成一个if子句结点
			b->name="          IF子句：\n";
			root->rsibling=NULL;
			root->lchild=a;
			a->rsibling=b;
			b->rsibling=NULL;
			a->lchild=p;
			b->lchild=q;
			return root;
		} 	 
	}//结束时ww取到";"或"}"之后的第一个字符，if语句结束后的第一个字符 
	if (ww.h=="{") {
		tree root0;
		root0=ComSen();
		return root0;
	}//结束时ww取到"}"之后的第一个字符  
	if(ww.h=="while") {
		ww=gettoken();//ww取到while后面的第一个字符"("
		if(ww.h!="(") {
			cout<<"语句部分："<<"Error16 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
			errors+=1;
			return NULL;
		} 
		ww=gettoken();//ww取到"("后面的第一个字符
		tree root1,root2,root3,m,n;
		root1=exp();//调用处理表达式的子程序，结束时ww取到")"之后的第一个字符，while子句的第一个字符 ,root1为while语句的条件表达式子树结点指针 
		root2=statement();//调用处理一条语句的子程序，得到while子句的子树根指针，确保结束时ww取到";"或"}"之后的第一个字符，while语句结束后的第一个字符
		root3=new node();//生成一个while语句结点
		root3->name="        WHILE语句：\n";
		root3->rsibling=NULL;
		m=new node();//生成一个条件语句结点
		m->name="          条件：\n"; 
		root3->lchild=m;
		n=new node();//生成一个while子句结点
		n->name="          WHILE子句：\n"; 
		m->rsibling=n; 
		n->lchild=root2;
		n->rsibling=NULL;
		m->lchild=root1;
		return root3;
	}//结束时ww取到";"或"}"之后的第一个字符，while语句结束后的第一个字符 
	if(ww.h=="return") {
		tree root4,root5;
		root4=new node();//生成一个return语句结点
		root4->name="        返回语句：\n";
		ww=gettoken();//ww取到return之后的第一个字符 
		root5=exp();//调用处理表达式的子程序，结束时ww取到";"之后的第一个字符 
		root4->lchild=root5;
		root4->rsibling=NULL;
		return root4;
	}//结束时ww取到";"之后的第一个字符，return语句结束后的第一个字符   
	if(ww.h=="break"){
		tree root6;
		root6=new node();//生成一个break语句结点
		root6->name="        BREAK语句：\n";
		root6->rsibling=NULL;
		root6->lchild=NULL;
		ww=gettoken();//ww取到";"
		if(ww.h!=";") {
			cout<<"语句部分："<<"Error17 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
			errors+=1;
			return NULL;
		}  
		ww=gettoken();//ww取到";"之后的第一个字符
		return root6; 
	}//结束时ww取到";"之后的第一个字符,break语句结束后的第一个字符 
	if(ww.h=="continue"){
		tree root7;
		root7=new node();//生成一个continue语句结点
		root7->name="        CONTINUE语句：\n";
		root7->rsibling=NULL;
		root7->lchild=NULL;
		ww=gettoken();//ww取到";"
		if(ww.h!=";") {
			cout<<"语句部分："<<"Error18 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
			errors+=1;
			return NULL;
		}  
		ww=gettoken();//ww取到";"之后的第一个字符
		return root7; 
	}//结束时ww取到";"之后的第一个字符,continue语句结束后的第一个字符  
	if(ww.h=="for"){
		ww=gettoken();//ww取到for之后的第一个字符"("
		if(ww.h!="(") {
			cout<<"语句部分："<<"Error19 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
			errors+=1;
			return NULL;
		}  
		tree root8,root9,root10,root11,root12,x,y,z,i;
		root8=new node();//生成一个for语句结点
		root8->name="        FOR语句：\n";
		root8->rsibling=NULL;
		ww=gettoken();//ww取到"("之后的第一个字符
		root9=exp();//调用处理表达式的子程序，结束时ww取到";"之后的第一个字符
		root10=exp();//调用处理表达式的子程序，结束时ww取到";"之后的第一个字符
		root11=exp();//调用处理表达式的子程序，结束时ww取到")"之后的第一个字符
		root12=statement();//调用处理一条语句的子程序，得到for子句的子树根指针，确保结束时ww取到";"或"}"之后的第一个字符，for语句结束后的第一个字符
		x=new node();//生成一个赋初值语句结点
		x->name="          赋初值：\n"; 
		root8->lchild=x;
		x->lchild=root9;
		y=new node();//生成一个条件语句结点
		y->name="          条件：\n";  
		x->rsibling=y;
		y->lchild=root10;
		z=new node();//生成一个增值语句结点
		z->name="          增值：\n";
		y->rsibling=z;
		z->lchild=root11;  
		i=new node();//生成一个for子句结点
		i->name="          FOR子句：\n"; 
		z->rsibling=i;
		i->rsibling=NULL;
		i->lchild=root12;
		return root8;
	}//结束时ww取到";"或"}"之后的第一个字符，for语句结束后的第一个字符
	if(ww.g==1) {
		tree root13;
		root13=exp();
		return root13;
	}//结束时ww取到";"之后的第一个字符
	if(ww.g==2 || ww.g==4 || ww.g==6 || ww.g==5) {
		tree root14;
		root14=exp();
		return root14;
	}//结束时ww取到";"之后的第一个字符
	if(ww.h=="}"){
		return NULL;
	}
	if(ww.h=="(") {
		tree root15;
		root15=exp();
		return root15;
	}//结束时ww取到")"之后的第一个字符
	cout<<"语句部分："<<"Error20 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
	errors+=1;
	return NULL;//以上情况都不满足，报错 
}
//运算符优先级判断 
char precede(string a,string b){
    int i,j;
    char pre[][17]={//运算符之间的优先级制作成一张表格         
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
		cout<<"表达式部分："<<"Error21 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
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
		cout<<"表达式部分："<<"Error22 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
	    errors+=1;
	}
    if(0<=i<=16 && 0<=j<=16) return pre[i][j];
}
//判断是否是运算符 
int CalSym(string b){
	if(b=="+" || b=="-" || b=="*" || b=="/" || b=="(" || b==")" || b=="=" || b==">" || b=="<" || b=="==" || b=="!=" ||\
    b=="#" || b=="&&" || b=="||" || b=="%" || b==">=" || b=="<=") return 1;
    else return 0;
}
//处理表达式 
tree exp(){//调用该算法时，已经读入了第一个字符在ww中
	stack<string>op;//定义运算符栈 op
	stack<tree>opn;//定义操作数栈opn
	op.push("#");//将起止符"#"入栈
	string t;
	tree t1,t2;
	while ((ww.h!="#" || op.top()!="#") && !errors ){
		if(ww.g==1 || ww.g==2 || ww.g==4 || ww.g==6 || ww.g==5){
			tree root0;
			root0=new node();
			root0->name="              ID："+ww.h+"\n";
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
                         root1=new node();//生成一个运算结点 
                         root1->rsibling=NULL;
                         root2=new node();
                         root2->name="            运算符："+t+"\n";//生成一个运算符结点 
                         root1->lchild=root2;
                         root2->rsibling=NULL;
                         root3=t1;//生成一个操作数结点
                         root2->lchild=root3;
                         root4=t2;//生成一个操作数结点
                         root3->rsibling=root4;
                         opn.push(root1);
						 break;
				default:if(ww.h==")") ww.h="#";
				        else {
				        	errors++;
				        	cout<<"表达式部分："<<"Error23 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
				        	return NULL;
						}								                        
			}			
		}
		else if(ww.h==";") ww.h="#";
		else {
				errors++;
		    	cout<<"表达式部分："<<"Error24 in "<<"\""<<ww.h<<"\" "<<"!"<<endl;
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
//输出抽象语法树 
int PrintTree(tree root){
	if(root) {if(visit(*root))//调用visit函数 
	if(PrintTree(root->lchild))//递归前序遍历左孩子子树 
	if(PrintTree(root->rsibling)) return 1;//递归前序遍历右兄弟子树 
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
	    } //去掉程序中的空格  
	}
	cout<<"单词类别"<<"  "<<"单词值"<<endl; 
	TakeWord();
	WordList();
	tree root;
	int i;
	root=program();
   if (PrintTree(root)==1) cout<<"遍历成功！"<<endl;
    else cout<<"遍历失败！"<<endl; 
	cout<<"\n";
    fclose(stdin);//关闭文件 
    fclose(stdout);//关闭文件 
    return 0;
}
