#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Token{
	char *pal;
	char type;
	int idex;
	
	Token(){}
	~Token(){}
};
void reconocerop(char**l,int *i,Token* T){
	T->idex = *i;
	T->type = 'O';
	char *x = new char;
	*x = **l;
	T->pal = x;
	(*l)++;
	(*i)++;
}
void reconocernum(char**l,int *i, Token *T){
	T->idex = *i;
	T->type = 'E';
	char *x = new char[10];
	int temp =0;
	while(**l != ' ' && **l != ';'){
		x[temp] = **l;
		(*l)++;
		(*i)++;
		temp++;
	}
	T->pal = x;
}
void reconocervar(char**l,int *i, Token *T){
	T->idex = *i;
	T->type = 'V';
	int temp=0;
	char *aux = *l;
	while(*aux != ' ' && *aux != ';'){
		temp++;
		aux++;
	}
	char *x = new char[temp];
	temp =0;
	while(**l != ' ' && **l != ';'){
		x[temp] = **l;
		(*l)++;
		temp++;
		(*i)++;
	}
	T->pal = x;
}
vector<Token> analizadorLexico(char * line){
	vector<Token> ttokens;
	int i=0,xxxx;
	while(*line != ';'){
		if(*line == ' ' || *line == '>') {
			line++;
			i++;
			continue;
		}
		Token t;
		//	cout<<"-"<<*line<<"_"<<endl;
		if((*line) == '+' || (*line) == '-' || (*line) == '*' || (*line) == '/' || (*line) == '='){			reconocerop(&line,&i,&t);
		ttokens.push_back(t);
		}else if((*line-'0')<10){
			reconocernum(&line,&i,&t);
			ttokens.push_back(t);
		}else if((*line >= 'A')&&(*line <= 'Z')){
			reconocervar(&line,&i,&t);
			ttokens.push_back(t);
		}else if((*line >= 'a')&&(*line <= 'z')){
			reconocervar(&line,&i,&t);
			ttokens.push_back(t);
		}
	}
	return ttokens;
}
pair<int,int> getExp1(vector<Token> &V,int i, int f){
    int it=i;
    while(V[it].type != 'O' && it<=f) it++;
    if(it==f) return make_pair(-1,-1);
    pair<int,int> exprl = getExp(V,i,it-1);
    pair<int,int> exprr = getExp(V,it+1,f);
    if (exprl.first != -1 && exprr.first != -1){
        return make_pair(i,f);
    }
    return make_pair(-1,-1);
}
pair<int,int> getExp2(vector<Token> &V,int i, int f){
    if(*(V[i].pal) == '(' && *(V[f].pal) == ')'){
        pair<int,int> expr = getExp(V,i+1,f-1);
        if(expr.first != -1)
    		return make_pair(i,f);
    }
    return make_pair(-1,-1);
}
pair<int,int> getExp3(vector<Token> &V,int i, int f){
    if(i == f && (V[i].type == 'E' || V[i].type == 'V')){
        return make_pair(i,i);
    }
    return make_pair(-1,-1);
}
pair<int,int> getExp(vector<Token> &V,int i, int f){
	pair<int,int> expr1 = getExp1(V,i,f);
	if( expr1.first != -1 )
		return expr1;
	pair<int,int> expr2 = getExp2(V,i,f);
	if( expr2.first != -1 )
		return expr2;
	pair<int,int> expr3 = getExp3(V,i,f);
    if( expr3.first != -1 )
		return expr3;
	return expr1;
}
pair<int,int> getIgu(vector<Token> &V,int i,int f){
	if(V[i].type == 'V' && *(V[i+1].pal) == '='){
        pair<int,int> expr = getExp(V,i+2,f);
        if(expr.first != -1)
    		return make_pair(i,expr.second);
	}
    return make_pair(-1,-1);
}
pair<int,int> getCom(vector<Token> &V){
    int mf = V.size()-1;
	pair<int,int> expr = getExp(V,0,mf);
	if( expr.first != -1 )
		return expr;
    pair<int,int> igul = getIgu(V,0,mf);
	if( igul.first != -1 )
		return igul;
	return igul;
}
int main(int argc, char *argv[]) {
	char a[]="> perrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrro = 3 *pe2ce;";
	vector<Token> t = analizadorLexico(a);
	cout<<t.size()<<" sis"<<endl;
/*	for(int i=0;i<t.size();++i){
		cout<< t[i].idex <<" | "<< t[i].pal <<" | "<< t[i].type <<endl;
	}*/
    pair<int,int> r = getCom(t);
    if(r.first == -1){
        cout<<"Nop"<<endl;
    }else {
        cout<<"SIU"<<endl;
    }

	return 0;
}