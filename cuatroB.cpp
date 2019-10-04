#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;
//////for ( auto & a : A ) cout << a << ", ";
struct Production{
	string izq;
	vector<string> der;
    vector<string> separe(string de){
        vector<string> a;
        int ss = de.size()-1,au=0,f;
        string t="";
        for (int i;i<ss;){
            if((de[i]) == '+' || (de[i]) == '-' || (de[i]) == '*' || (de[i]) == '/' || (de[i]) == '='){	
                t+=de[i];
                i++;
                a.push_back(t);
                t=""; continue;
            }else if((de[i]-'0')<10){
                while((de[i]-'0')<10){
                    t+=de[i];
                    i++;
                }
                a.push_back(t);
                t=""; continue;
            }else if((de[i] >= 'A')&&(de[i] <= 'Z')){
                while((de[i] >= 'A')&&(de[i] <= 'Z')){
                    t+=de[i];
                    i++;
                }
                a.push_back(t);
                t=""; continue;
            }else if((de[i] >= 'a')&&(de[i] <= 'z')){
                while((de[i] >= 'a')&&(de[i] <= 'z')){
                    t+=de[i];
                    i++;
                }
                a.push_back(t);
                t=""; continue;
            }
            i++;
        }
        return a;
    }
	Production(string iz, string der){
		izq = iz;
        cout<< this->izq<<" :: ";
        this->der = separe(der);
        for(int i =0;i<this->der.size();++i){
            cout<<"|"<<this->der[i];
        }
        cout<<"|"<<endl;
	}
};

struct Gramatica{
	vector<Production> productions;
	set<string> terminales;
	set<string> noterminales;
    string estadoInicial;
	
	Gramatica(string i):estadoInicial(i){}
	vector<vector<string>> getProduccion(string izq);
	void read(string texto);
};
vector<vector<string>> Gramatica::getProduccion(string izq){

}
void Gramatica::read(string txt){
	int index, auxf,auxi,x; index = auxi = auxf = 0;
	while(index<txt.size()){
		index = txt.find(":=",auxi);
		auxf = txt.find(";",auxi);
        if(index < 0 || auxf <0)break;
		Production p (txt.substr(auxi,index-auxi),txt.substr(index+2,(auxf-index)-1));
        productions.push_back(p);
        auxi = auxf+1;
	}
}
//****************************************************************************
#include <map>
class AnalizadorSintacticoLL1{
private:
    Gramatica gr;
    map<string, map<string, vector<string>>> tas;
    void adicionar(string noTerminal, string terminal, vector<string>);
    const string DOLAR = "$";
public:
    void llenarTas();
    bool reconocerSentencia(string sentencia);
};
void AnalizadorSintacticoLL1::adicionar(string noTerminal, string terminal, vector<string> v) {
    tas[noTerminal][terminal] = v;
}
void AnalizadorSintacticoLL1::llenarTas() {
    adicionar("E","num",{"T","Ep"});
		adicionar("E","id",{"T","Ep"});
		adicionar("Ep","+",{"+","T","Ep"});
		adicionar("Ep","-",{"-","T","Ep"});
		adicionar("Ep",")",{"lambda"});
		adicionar("Ep","$",{"lambda"});
		adicionar("T","(",{"F", "Tp"});
		adicionar("T","num",{"F", "Tp"});
		adicionar("T","id",{"F", "Tp"});
		adicionar("Tp","+",{"lambda"});
		adicionar("Tp","-",{"lambda"});
		adicionar("Tp","*",{"*", "F", "Tp"});
		adicionar("Tp","/",{"/", "F", "Tp"});
		adicionar("Tp",")",{"lambda"});
		adicionar("Tp","$",{"lambda"});
		adicionar("F","(",{"(E)"});
		adicionar("F","num",{"num"});
		adicionar("F","id",{"id"});
}
#include <queue>
#include <stack>

bool AnalizadorSintacticoLL1::reconocerSentencia(string cadena ) {
    queue<string> entrada;
    stack<string> pila;

    pila.push("$");
    pila.push( gr.estadoInicial );
    entrada.push("$");

    while( !entrada.empty() && !pila.empty() ) {
        if( entrada.front() == pila.top() ) {
            entrada.pop();
            pila.pop();
        }else{
            string tmp = pila.top();
            pila.pop();
            for(auto x : tas[tmp][entrada.front()])
                if( x != "lambda")
                    pila.push(x);
        }
    }
    return entrada.empty() && pila.empty();
}

//****************************************************************************

int main(){
	string lines="";
	string line;
	while(getline(cin,line)){
		if(line.empty())break;
		lines += (line+';');
		line.clear();
	}
	cout<< lines<<endl;
	Gramatica G("E");
	G.read(lines);
    AnalizadorSintacticoLL1 

    return 0;
}

/**
E  := T Ep
Ep := + T Ep 
Ep := - T Ep
Ep := lambda
T  := F Tp
Tp := * F Tp  |  /  F Tp  | lambda
F  := ( E ) | num | id
**/