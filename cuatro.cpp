#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

struct Production{
	string izq;
	vector<string> der;
	Production(string iz, istring der){
		;
	}
};

struct Gramatica{
	vector<Production> productions;
	set<string> terminales;
	set<string> noterminales;
	
	Gramatica(){}
	vector<vector<string>> getProduccion(string izq);
	void read(string texto);
};
vector<vector<string>> Gramatica::getProduccion(string izq){}
void Gramatica::read(string txt){
	size_t index, auxf,auxi; index = auxi = auxf = 0;
	while(index<txt.size()){
		index = txt.find(":=",auxi);
		auxf = txt.find(";",auxi);
		auxi = auxf+1;
		Production p (txt.substr(auxi,index-auxi),txt.substr(index+2,auxf-index+2));
		productions.push_back(p);
	}
}

int main(){
	string lines="";
	string line;
	while(getline(cin,line)){
		if(line.empty())break;
		lines += (";"+line);
		line.clear();
	}
	cout<< lines<<endl;
	Gramatica G();
	//G.read(lines);
}
