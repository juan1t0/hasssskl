#include <iostream>
#include <vector>
#include <set>
#include <string.h>
#include <sstream>
#include <queue>
#include <stack>
#include <map>

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
void printMatrix(vector<vector<T>> &mat){
	for(size_t i = 0; i < mat.size(); ++i){
		for(size_t j = 0; j < mat[i].size(); ++j){
			cout << mat[i][j] << '\t';
		}
		cout<<endl;
	}
}

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
	string estadoInicial = "E";
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
		//cout << "|" << nameIZQ << "|" << endl;
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
//		DeteleFromString(subtex,'[');
		DeteleFromString(subtex,']');
		stringstream Saux(subtex);
		string temp;
		vector<contex> tempContx;
		while(getline(Saux, temp, ',')){
			contex a = make_pair(temp.substr(0,temp.find("=")),temp.substr(temp.find("=")+1));
			tempContx.push_back(a);
	//		cout << "<" << a.first << "," << a.second << "> " ;
		}
	//	cout << endl;
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
	//		cout << ">>" << nameIZQ << ": " << tempContx.size() << " <<";
		}
	//	cout << endl;
		return otherProd;
	}
	vector<string> readTerminals(string &subtex){
		stringstream Saux(subtex);
		string temp;
		vector<string> terminals;
		while(Saux>>temp){
			terminals.push_back(temp);
		//	cout << "||" << temp << " ; " ;
		}
	//	cout << "||" << endl;
		return terminals;
	}
	vector<vector<string>> getProduction(string izq){
		vector<vector<string>> result;
		for(size_t i = 0; i < production.size(); ++i){
			if(production[i]->nombre == izq){
				if(production[i]->der == 0){
					//cout<<"algo"<<endl;
					vector<string> temp;
					//cout<<"algito"<<endl;
					ContexProduc *a = (ContexProduc *)(production[i]);
					//cout<<a->nombre<<endl;
					for(int j=0;j < a->derP->size();j++){
						string te = a->derP->at(j).nombre;
						temp.push_back(te);
					}	
					result.push_back(temp);				
				}
				else{
					result.push_back(*(production[i]->der));
				}
			}
		}
		return result;
	}
	Gramatica(){}
};

class AnalizadorSintacticoLL1{
	Gramatica gr;
	map<string, map<string, vector<string> > > tas;
	void adicionar(string noTerminal, string terminal, vector<string> prods){
		tas[noTerminal][terminal] = prods;
	}
	const string dolar = "$";
public:
	void llenarTas(){
		adicionar("E", "(", {"T", "Ep"});
		adicionar("E", "num", {"T", "Ep"});
		adicionar("E", "id", {"T", "Ep"});
		adicionar("Ep", "+", {"+", "T", "Ep"});
		adicionar("Ep", "-", {"-", "T", "Ep"});
		adicionar("Ep", ")", {"lambda"});
		adicionar("Ep", "$", {"lambda"});
		adicionar("T", "(", {"F", "Tp"});
		adicionar("T", "num", {"F", "Tp"});
		adicionar("T", "id", {"F", "Tp"});
		adicionar("Tp", "+", {"lambda"});
		adicionar("Tp", "-", {"lambda"});
		adicionar("Tp", "*", {"*", "F", "Tp"});
		adicionar("Tp", "/", {"/", "F", "Tp"});
		adicionar("Tp", ")", {"lambda"});
		adicionar("Tp", "$", {"lambda"});
		adicionar("F", "(", {"(","E",")"});
		adicionar("F", "num", {"num"});
		adicionar("F", "id", {"id"});
	}
	bool reconocerSentencia(string sentencia){
		queue<string> entrada;
		string token;
		stringstream ss(sentencia);
		while(ss>>token){
			entrada.push(token);
		}
		stack<string> pila;
		pila.push(dolar);
		pila.push(gr.estadoInicial);
		entrada.push(dolar);
		
		while( !entrada.empty() && !pila.empty()){
			if(entrada.front() == pila.top()){
				entrada.pop();
				pila.pop();
			}
			else{
				string temp = pila.top();
				pila.pop();
				vector<string> tempVec = tas[temp][entrada.front()];
				for(size_t i = 0; i < tempVec.size(); ++i){
					if(tempVec[i] != "lambda"){
						pila.push(tempVec[tempVec.size() -1 -i]);
					}
				}
			}
		}
		return (entrada.empty() && pila.empty());
	}
};

int main(int argc, char *argv[]) {
	Gramatica grammar;
/*	grammar.read("E := T Ep");
	grammar.read("Ep := + T Ep | - T Ep | lambda");
	grammar.read("T := F Tp");
	grammar.read("Tp := * F Tp");
	grammar.read("F := (E) | num | id");*/

	grammar.read("Sus[gen=?_] := Det[gen=?_] Suj[gen=?_]");
	grammar.read("Det[gen=?f] := 'la'");
/*	grammar.read("Det[gen=?m] := 'el'");
	grammar.read("Suj[gen=?m] := 'nino'");
	grammar.read("Suj[gen=?f] := 'nina'");
*/
	vector<vector<string>> producciones = grammar.getProduction("Sus");
	printMatrix(producciones);

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