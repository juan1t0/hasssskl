#include <iostream>
#include <vector>

using namespace std;

struct Token{
	char pal[20];//operator
	char type;//
	int idex;
	
	Token(){}
	~Token(){}
};
Token reconocerop(char**l,int &i){
	Token t;
	t.idex = i;
	t.type = 'O';
	while((**l) != ' '){
		*(t.pal) = **l;
		(*l)++;
		(t.pal)++;
	}
	return t;
}
Token reconocernum(char**l,int &i){
	Token t;
	t.idex = i;
	t.type = 'E';
	while(**l != ' '){
		*(t.pal) = **l;
		(*l)++;
		(t.pal)++;
	}
	return t;
}
Token reconocervar(char**l,int &i){
	Token t;
	t.idex = i;
	t.type = 'V';
	while(**l != ' '){
		*(t.pal) = **l;
		(*l)++;
		(t.pal)++;
	}
	return t;
}


vector<Token> analizadorLexico(char * line){
	vector<Token> ttokens;
	int i=0;
	while(*line != '\n'){
		Token t;
		cout<<"-"<<*line<<endl;
		switch( *line ) {
		case '+':
		case '-':
		case '*':
		case '/':
		case '=':
			t = reconocerop(&line,i);
			ttokens.push_back(t);
		}
		if((*line-'0')<10){
			t = reconocernum(&line,i);
			ttokens.push_back(t);
		}else if((*line - 'A')<26){
			t = reconocervar(&line,i);
			ttokens.push_back(t);
		}else if((*line - 'a')<26){
			t = reconocervar(&line,i);
			ttokens.push_back(t);
		}
		line++;
		i++;
	}
	return ttokens;
}

int main(int argc, char *argv[]) {
	char a[]=">1 + 2 = 3";
	vector<Token> t = analizadorLexico(a);
	for(int i=0;i<t.size();++i){
		cout<< t[i].pal <<" | "<<endl;
	}
	return 0;
}


