#include <iostream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

void exercice1(){
    //-------------------------------------
    cout << ": ";
    string line;
    getline(cin,line);
    cout<< line << "<-" << endl;
    //-------------------------------------
    stack<bool> current;
    size_t line_len = line.length();
    for(size_t i = 0; i < line_len; ++i){
        if(line[i] == '('){
            current.push(0);
            continue;
        }else if (line[i] == '['){
            current.push(1);
            continue;
        }else if (line[i] == ' '){continue;}
        else{
            if(current.empty()){
                cout<<"NO"<<endl;
                return;
            }
            if(!(current.top()) && line[i]!= ')'){
                cout<<"NO"<<endl;
                return;
            }
            if(current.top() && line[i]!= ']'){
                cout<<"NO"<<endl;
                return;
            }
            current.pop();
        }
    }
    if(current.empty())
        cout << "SIU" <<endl;
    else
        cout<<"NO"<<endl;
}
vector<string> lista ={"decir","pedir","preferir","servir","vestir","seguir","repetir","dormir","morir","ir","sentir","venir","freir","reir","mentir","poder"};
vector<string> Lista ={"diciendo","pidiendo","prefiriendo","sirviendo","vistiendo","siguiendo","repitiendo","durmiendo","muriendo","yendo","sintiendo","viniendo","friendo","riendo","mintiendo","pudiendo"};

bool esvocal(char x){
    return (x == 'a' || x == 'i' || x == 'e' || x == 'o' || x == 'u');
}
string enLista(string v){
    size_t m = lista.size();
    for(size_t i = 0; i < m; ++i){
        if(v==lista[i]) return Lista[i];
    }
    return "x";
}
void exercice2(){
    //-------------------------------------------
    string verb, gerundio;
    cout << ":";
    cin >> verb;
    cin >> gerundio;
    //-------------------------------------------
    string aux = enLista(verb);
    string ter = "";
    if(aux != "x") verb = aux;
    else{
    ter = verb.substr(verb.length()-2);
    verb = verb.substr(0,verb.length()-2);
    cout<<"::"<<ter<<endl;
    cout<<":-:"<<verb<<endl;
    }
    if (ter == "ar"){
        verb += "ando";
    }else if(ter == "er" || ter == "ir"){
        if(esvocal(verb[verb.length()-1])) 
            verb += "yendo";
        else
            verb += "iendo";
    }

    if(verb == gerundio) cout << "SIU"<< endl;
    else cout << "NO" << endl;
}
void clea(string &x){
    size_t mm= x.size();
    for(size_t i = 0; i < mm; ++i){
        if(x[i]==' ' || x[i]==',')
            x=x.substr(0,i-1);
    }
    //cout<<"x:" <<x<<endl;
}
void exercice3(){
    //-------------------------------
    vector<string> templines;
    int n; cin>> n;
    string line;
    for(int i = 0; i < n; ++i){
        getline(cin,line);
        templines.push_back(line);
        line.clear();
    }
    double P,I,U;
    string uno,dos;
    //-------------------------------
    for(int i=0;i<n;++i){
        cout <<"Problem #"<< i+1<<endl;
        line = templines[i];
        uno = line.substr(line.find('=')-1);
        dos = line.substr(line.find_last_of('=')-1);
        clea(uno); clea(dos);
        P=I=U=0.0;
        char s = uno[uno.length()-1];
        switch (uno[0]){
        case 'P':
            if(s>=48 && s <= 57)P = stof(uno.substr(2,uno.length()-2));
            else  {
                P = stof(uno.substr(2,uno.length()-3));
                if(s=='m') P*=0.001;
                else if(s=='k') P*=1000;
                else if(s=='M') P*=1000000;
            }
            break;
        case 'U':
            if(s>=48 && s <= 57)U = stof(uno.substr(2,uno.length()-2));
            else  {
                U = stof(uno.substr(2,uno.length()-3));
                if(s=='m') U*=0.001;
                else if(s=='k') U*=1000;
                else if(s=='M') U*=1000000;
            }
            break;
        case 'I':
            if(s>=48 && s <= 57)I = stof(uno.substr(2,uno.length()-2));
            else  {
                I = stof(uno.substr(2,uno.length()-3));
                if(s=='m') I*=0.001;
                else if(s=='k') I*=1000;
                else if(s=='M') I*=1000000;
            }
            break;
        }
        s = dos[dos.length()-1];
        switch (dos[0]){
        case 'P':
            if(s>=48 && s <= 57)P = stof(uno.substr(2,uno.length()-2));
            else  {
                P = stof(dos.substr(2,dos.length()-3));
                if(s=='m') P*=0.001;
                else if(s=='k') P*=1000;
                else if(s=='M') P*=1000000;
            }
            break;
        case 'U':
            if(s>=48 && s <= 57)P = stof(uno.substr(2,uno.length()-2));
            else  {
                U = stof(dos.substr(2,dos.length()-3));
                if(s=='m') U*=0.001;
                else if(s=='k') U*=1000;
                else if(s=='M') U*=1000000;
            }
            break;
        case 'I':
            if(s>=48 && s <= 57)P = stof(uno.substr(2,uno.length()-2));
            else  {
                I = stof(dos.substr(2,dos.length()-3));
                if(s=='m') I*=0.001;
                else if(s=='k') I*=1000;
                else if(s=='M') I*=1000000;
            }
            break;
        }
        if (P==0.0){
            cout<<"P="<<U*I<<"W"<<endl;
        }
        else if (I==0.0){
            cout<<"I="<<P/U<<"A"<<endl;
        }else {
            cout<<"U="<<P/I<<"V"<<endl;
        }
    }
}

int main()
{
//    exercice1();
//    exercice2();
    exercice3();
    return 0;
}