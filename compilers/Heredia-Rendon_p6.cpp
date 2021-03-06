/**
* Hecho por 
*	Heredia Parillo, JuanPablo Andrew
*	Rendon Zuniga, Luis Francisco
**/
#include <iostream>
#include <vector>
#include <set>
#include <string.h>
#include <sstream>
#include <queue>
#include <stack>
#include <algorithm>

#define contex pair<string,string>

using namespace std;

void DeteleFromString(string &s, char d){
	string result;
	for(size_t i = 0; i < s.size(); ++i){
		if(s[i] == d)continue;
		result += s[i];
	}
	s = result;
}

template<class T>
void printMatrix(vector<vector<T> > &mat){
	for(size_t i = 0; i < mat.size(); ++i){
		for(size_t j = 0; j < mat[i].size(); ++j){
			cout << mat[i][j] << '\t';
		}
		cout<<endl;
	}
}

struct Token{
	char *pal;
	char type;
	int idex;
	
	Token(){}
	~Token(){}
};

class Produccion{
public:
	string nombre;
	vector<string> *der;
public:
	Produccion(){}
	Produccion(string &s): nombre(s){}
	Produccion(string &s, vector<string> &vec): nombre(s), der(new vector<string> (vec)){}
};

class SimpleProduc : public Produccion{
public:
	SimpleProduc(string &s, vector<string> &vec): Produccion(s,vec){}
};

class ContexProduc : public Produccion{
public:
	vector<contex>* contexto;
	vector<Produccion>* derP;
	ContexProduc(Produccion p):Produccion(p.nombre,*(p.der)){
		cout<<"aqa"<<endl;
		contexto = 0;
		derP = 0;
	}
	ContexProduc(string &name, vector<contex>& ctx): Produccion(name){
		contexto = new vector<contex>(ctx);
		derP = 0;
	}
	ContexProduc(string &name, vector<contex>& ctx, vector<string>& der):Produccion(name,der){
		contexto = new vector<contex>(ctx);
		derP = 0;
	}
	ContexProduc(string &name, vector<contex>& ctx, vector<Produccion>& derP):Produccion(name){
		contexto = new vector<contex>(ctx);
		this->derP = new vector<Produccion>(derP);
	}
};

struct Gramatica{
	string estadoInicial;
	vector<Produccion*> production;
	set<string> terminales;
	set<string> noterminales;
	
	void read(string texto){
		if(texto.find("=?")){
			readContx(texto);
			return;
		}
		string temp1 = texto.substr(0, texto.find( ":=" ));
		DeteleFromString(temp1,' ');
		string temp2 = texto.substr(texto.find(":=") + 2, texto.length() - 1);
		stringstream ss(temp2);
		string token;
		while(getline(ss, token, '|')){
			vector<string> der;
			stringstream ss2(token);
			string token2;
			while(ss2 >> token2){
				der.push_back(token2);
			}
			SimpleProduc * temp = new SimpleProduc(temp1,der);
			production.push_back(temp);
		}			
	}
	void readContx(string texto){
		short separe = texto.find(":=");
		string nameIZQ = texto.substr(0,texto.find("["));
		DeteleFromString(nameIZQ,' ');
		vector<contex> tempContx = readVarContx(texto.substr(texto.find("[")+1,separe-texto.find("[")-1));
		string dere = texto.substr(separe+2);
		if(dere.find("?_") != string::npos){
			vector<Produccion> to_der = readMoreProduc(dere);
			ContexProduc * ctp = new ContexProduc(nameIZQ,tempContx,to_der);
			production.push_back(ctp);
		}else{
			vector<string> to_der = readTerminals(dere);
			ContexProduc * ctp = new ContexProduc(nameIZQ,tempContx,to_der);
			production.push_back(ctp);
		}
	}
	vector<contex> readVarContx(string subtex){
		DeteleFromString(subtex,']');
		stringstream Saux(subtex);
		string temp;
		vector<contex> tempContx;
		while(getline(Saux, temp, ',')){
			contex a = make_pair(temp.substr(0,temp.find("=")),temp.substr(temp.find("=")+1));
			tempContx.push_back(a);
		}
		return tempContx;
	}
	vector<Produccion> readMoreProduc(string &subtex){
		stringstream Saux(subtex);
		string temp;
		vector<Produccion> otherProd;
		while(Saux>>temp){
			string nameIZQ = temp.substr(0,temp.find("["));
			vector<contex> tempContx = readVarContx(temp.substr(temp.find("[")+1));
			otherProd.push_back(ContexProduc(nameIZQ,tempContx));
			//			production.push_back(& otherProd[otherProd.size()-1]);
		}
		return otherProd;
	}
	vector<string> readTerminals(string &subtex){
		stringstream Saux(subtex);
		string temp;
		vector<string> terminals;
		while(Saux>>temp){
			terminals.push_back(temp);
		}
		return terminals;
	}
	vector<vector<string> > getProduction(string izq){
		vector<vector<string> > result;
		for(size_t i = 0; i < production.size(); ++i){
			if(production[i]->nombre == izq){
				if(production[i]->der){
					result.push_back(*(production[i]->der));
				}
				else{
					vector<string> temp;
					ContexProduc *a = (ContexProduc *)(production[i]);
					for(int j=0;j < a->derP->size();j++){
						string te = a->derP->at(j).nombre;
						temp.push_back(te);
					}	
					result.push_back(temp);
				}
			}
		}
		return result;
	}
	void printGrammar(){
		for(size_t i = 0; i < production.size(); ++i){
			cout << production[i]->nombre;
			ContexProduc *a = (ContexProduc *)(production[i]);
			if(!a->contexto){
				cout << " :: ";
				for(int j =0;j < production[i]->der->size();j++){
					cout << production[i]->der->at(j) << "\t";
				}
			}
			else{
				ContexProduc *a = (ContexProduc *)(production[i]);
				cout<< "<";
				for(int j=0;j < a->contexto->size();j++){
					cout<<a->contexto->at(j).first <<"  ";
				}
				cout << "> :: ";
				if(!a->derP){
					for(int j =0;j < production[i]->der->size();j++){
						cout << production[i]->der->at(j) << "\t";
					}
				}else{
					for(int j=0;j < a->derP->size();j++){
						cout<<a->derP->at(j).nombre<< "<";
						/*ContexProduc *b = (ContexProduc *)&(a->derP->at(j));
						for(int k=0;k<b->contexto->size();k++){
							cout<< b->contexto->at(k).first<<" ";
						}*/
						cout<<">\t";
					}	
				}
			}
			cout<<endl;
		}
	}
	bool isTerminal(string token){///comprobar si es terminal

	}
	Gramatica(){}
    ~Gramatica(){}

    Produccion* get_Production(int pos){
        return production[pos];
    }
    void insertProduction(Produccion* xtr, int pos){
        production.insert(production.begin() + pos, xtr);
    }
};
class Estado_Compilador{
public:
	int estadoChart;
	Produccion *producRef;
    int PosAsterisco;
    int PosPalabra;
    Estado_Compilador *root;
	vector<string> *tokens;
    Estado_Compilador(Produccion* PR, int PA, int PP, Estado_Compilador* R):producRef(PR),PosAsterisco(PA), PosPalabra(PP), root(R){}
	Estado_Compilador(){}
    ~Estado_Compilador(){}
};
//queue <Estado_Compilador*> chart;
vector<Estado_Compilador *> chart;

class Accion {
public:
	Gramatica *gramarSource;
    virtual bool sePuedeAplicar(Estado_Compilador *estado) = 0;
    virtual void aplica(Estado_Compilador *estado) =0 ;//, queue<Estado_Compilador*> &chart) = 0;
};
class Dummy : public Accion{
public:
    bool sePuedeAplicar(Estado_Compilador *stte){return true;}
    void aplica(Estado_Compilador *stte){//, queue<Estado_Compilador*> &chrt){
		Produccion* fist = gramarSource->get_Production(0);
		vector<string> v;
		v.push_back(fist->nombre);
        string nn = "S";
		Produccion* temp = new SimpleProduc(nn,v);
		stte->PosAsterisco = 0;
		stte->PosPalabra = 0;
		stte->root = 0;
		stte->producRef = temp;
        gramarSource->production.insert(gramarSource->production.begin(),temp);
    }
    Dummy(Estado_Compilador*state){
        if (sePuedeAplicar(state)){
            aplica(state);
        }
    }
    ~Dummy(){}
};
class Expandir : public Accion {
	bool sePuedeAplicar(Estado_Compilador *stte){
//        if (stte->producRef->isTerminal) return false;
        int i;
        for(i = 0; i < chart.size(); ++i){
            if(chart[i]->producRef->nombre == stte->producRef->nombre) return false;
        }
        return true;
	}
    void aplica(Estado_Compilador *stte){//, queue<Estado_Compilador*> &chrt){
        size_t sizz = gramarSource->production.size();
        string nn = stte->producRef->der->at(stte->PosAsterisco);
        for(size_t i = 0; i< sizz; ++i){
            if(gramarSource->production[i]->nombre == nn){
                Estado_Compilador * EC = new Estado_Compilador(gramarSource->production[i], 0, 0, stte);
                /*EC->producRef = gramarSource->production[i];
                EC->PosAsterisco = 0;
                EC->PosPalabra = 0;
                EC->root = stte;*/
                chart.push_back(EC);
            }
        }
	}
    Expandir(Estado_Compilador*state){
        if (sePuedeAplicar(state)){
            aplica(state);
        }
    }
    ~Expandir(){}
};

class Aceptar : public Accion {
	bool sePuedeAplicar(Estado_Compilador *stte){
		///si el astericso esta a la izquierda de un terminal
		vector<string> tokens = *(stte->tokens);
		if(gramarSource->isTerminal(tokens[stte->PosAsterisco])){//faltaria implementar isTerminal
			///verificamos con ayuda de unificar si es el mismo elemento indicado con pos palabra del estado compilador
		}
	}
	void aplica(Estado_Compilador *stte){
		Estado_Compilador *NE = new Estado_Compilador(stte->producRef,stte->PosAsterisco+1,stte->PosPalabra,stte->root);
		NE->estadoChart = stte->estadoChart+1;
		chart.push_back(NE);
		///estado char incrementa
		///mueve el asterisco		
	}
	Aceptar(Estado_Compilador*state){
		if (sePuedeAplicar(state)){
			aplica(state);
		}
	}
	~Aceptar(){}
};

class Unificar : public Accion {
	bool sePuedeAplicar(Estado_Compilador *stte){
		///si el no terminal es igual a un elemento de la oracion
		///si es libre de contexto, no verifica mas
	}
	void aplica(Estado_Compilador *stte){
		///Verificamos si la cadena de la oracion es igual a la cadena del nodo no terminal
		///Si son iguales, verificamos si no hay problema con cambiar de contexto en el Estado compilador
		///Si el valor de la variable no fue establecido, verificamos que no haya conflicto
	}
	Unificar(Estado_Compilador*state){
		if (sePuedeAplicar(state)){
			aplica(state);
		}
	}
	~Unificar(){}
};

int main(int argc, char *argv[]) {
	Gramatica grammar;
	grammar.read("E := T Ep");
	grammar.read("Ep := + T Ep | - T Ep | lambda");
	grammar.read("T := F Tp");
	grammar.read("Tp := * F Tp");
	grammar.read("F := (E) | num | id");
	/*
	grammar.read("Sus[gen=?_,num=?_] := Det[gen=?_] Suj[gen=?_,num=?_]");
	grammar.read("Det[gen=?f] := 'la'");
	grammar.read("Det[gen=?m] := 'el'");
	grammar.read("Suj[gen=?m] := 'nino'");
	grammar.read("Suj[gen=?f] := 'nina'");
	vector<vector<string> > producciones = grammar.getProduction("Sus");
	printMatrix(producciones);
	producciones = grammar.getProduction("Det");
	printMatrix(producciones);
	producciones = grammar.getProduction("Suj");
	printMatrix(producciones);
	grammar.printGrammar();
	*/

	return 0;
}

/**
* Sus[gen=? ] := Det[gen=? ] Suj[gen=? ]
* Det[gen=f] := 'la'
* Det[gen=m] := 'el'
* Suj[gen=m] := 'nino'
* Suj[gen=f] := 'nina'
*/

/*	AnalizadorSintacticoLL1 analizador;
analizador.llenarTas();
cout<<analizador.reconocerSentencia("num + num + num + num")<<endl;
cout<<analizador.reconocerSentencia("( num + num ) + ( num + num )")<<endl;	
cout<<analizador.reconocerSentencia("num * ( num * num )")<<endl;	
cout<<analizador.reconocerSentencia("( num *) num")<<endl;	*/
