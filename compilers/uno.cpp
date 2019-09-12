#include <iostream>
#include <vector>

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

int main(int argc, char *argv[]) {
	char a[]="> perrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrro = 3 *pe2ce;";
	vector<Token> t = analizadorLexico(a);
	cout<<t.size()<<" sis"<<endl;
	for(int i=0;i<t.size();++i){
		cout<< t[i].idex <<" | "<< t[i].pal <<" | "<< t[i].type <<endl;
	}
	return 0;
}
