/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Gestor.cpp
 * Author: carlo
 * 
 * Created on 28 de Dezembro de 2016, 18:06
 */


#include "Gestor.h"
#include "Consola.h"
#include "Castelo.h"
#include "Torre.h"
#include "Quinta.h"

Gestor* Gestor::getInstance() {
    static Gestor* instance = 0;
    if (instance == 0) {
        instance = new Gestor();
    };
    return instance;
}

void Gestor::start() {
    controlador = new Controlador();
    focoLinhas = 0;
    focoColunas = 0;
    string comando;
    Consola::setBackgroundColor(Consola::CYAN);
    Consola::clrscr();
    imprimeLogo();
    do{
        if(!config){                    
            cout << "Prima qualquer tecla para continuar...";
            Consola::getch();
            desenharMapa();
        }
        getline(cin, comando);
    }while(intrepertaComandos(controlador->toLower(comando)));
    imprimeLog("Jogo terminado.\n      Obrigado por jogar!\n\n");
}


void Gestor::desenharMapa() {
    Consola::setBackgroundColor(Consola::CYAN);
    Consola::clrscr();
    imprimeLogo();
    Unidade* u;
    for(int linhas = this->focoLinhas; linhas < this->focoLinhas+20; linhas++){
        if(linhas % 2 == 0){
            Consola::setBackgroundColor(Consola::BRANCO);
        }else{
            Consola::setBackgroundColor(Consola::CINZENTO);
        }
        Consola::setTextColor(Consola::PRETO);
        if(linhas >0){
        if(linhas < 10){
            cout << " " << linhas;
        }else{
            cout << linhas;
        }
        }
        for(int colunas = this->focoColunas; colunas < this->focoColunas+40; colunas++){
            cout << " ";
            if(linhas % 2 == 0){
                if(colunas % 2 == 0){
                    Consola::setBackgroundColor(Consola::CINZENTO);
                }else{
                    Consola::setBackgroundColor(Consola::BRANCO);
                }
            }else{
                if(colunas % 2 == 0){
                    Consola::setBackgroundColor(Consola::BRANCO);
                }else{
                    Consola::setBackgroundColor(Consola::CINZENTO);
                }
            }
            Consola::setTextColor(Consola::PRETO);
            if(colunas >0){
            if(linhas == this->focoLinhas){
                if(colunas < 10){
                    cout<<colunas;
                }else{
                    cout <<colunas;
                }
            }}
            
            u = controlador->verificaPosicao(linhas, colunas);
            if(u != NULL){
                Consola::setBackgroundColor(u->getEquipa());
                Consola::setTextColor(Consola::BRANCO_CLARO);
                cout << u->getNome() << " ";
                //Consola::setTextColor(Consola::BRANCO_CLARO);
            }else{
                cout << "  ";
            }
        }
        cout << endl;
    }
    Consola::setBackgroundColor(Consola::CYAN);
    Consola::setTextColor(Consola::BRANCO_CLARO);
}

bool Gestor::intrepertaComandos(string comando) {
    int inputInt;
    vector<string> stringSeparada;
    stringSeparada = separaComando(comando, ' ');
    if(stringSeparada.size() != 0){
        if(stringSeparada[0] == "fim"){
            return false;
        }else if(stringSeparada[0] == "dim"){
            if(config){
                if(stringSeparada.size() == 3){
                    if(checkNumero(stringSeparada[1]) && checkNumero(stringSeparada[2])){
                        comando_dim(atoi(stringSeparada[1].c_str()), atoi(stringSeparada[2].c_str()));
                        imprimeLog("Dimensao configurada - Linhas: " + stringSeparada[1] + ", Colunas: " + stringSeparada[2] + ".\n");
                        c_dim = true;
                    }else{
                        imprimeErro("Os argumentos tem que ser inteiros positivo!\n");
                    }
                }else{
                    imprimeErro("Numero de argumentos errado!\n       dim -numero\n");
                }
            }else{
                imprimeErro("Configuracao terminada!\n");
            }
        }else if(stringSeparada[0] == "moedas"){
            if(config){
                if(stringSeparada.size() == 2){
                    if(checkNumero(stringSeparada[1])){
                        comando_moedas(atoi(stringSeparada[1].c_str()));
                        imprimeLog("Moedas configurada - Valor: " + stringSeparada[1] + ".\n");
                        c_moedas = true;
                    }else{
                        imprimeErro("O argumento tem que se inteiro positivo!\n");
                    }
                }else{
                    imprimeErro("Numero de argumentos errado!\n       moedas -numero.\n");
                }
            }else{
                imprimeErro("Configuracao terminada!\n");
            }
        }else if(stringSeparada[0] == "oponentes"){
            if(config){
                if(c_dim && c_moedas){
                    if(stringSeparada.size() == 2){
                        if(checkNumero(stringSeparada[1])){
                            if(comando_oponentes(atoi(stringSeparada[1].c_str()))){
                                imprimeLog("Oponentes configurada - Num. Oponentes: " + stringSeparada[1] + ".\n");
                                c_oponentes = true;
                            }else{
                                imprimeErro("Nao ha espaco para mais colonias!\n");
                            }
                        }else{
                            imprimeErro("O argumento tem que se inteiro positivo!\n");
                        }
                    }else{
                        imprimeErro("Numero de argumentos errado!\n       oponentes -numero.\n");
                    }
                }else{
                    imprimeErro("Defina primeiro -dim e -moedas|\n");
                }
            }else{
                imprimeErro("Configuracao terminada!\n");
            }
        }else if(stringSeparada[0] == "castelo"){
            if(stringSeparada.size() == 4){
                if(checkNumero(stringSeparada[2]) && checkNumero(stringSeparada[3])){
                    switch(comando_castelo(stringSeparada[1], atoi(stringSeparada[2].c_str()), atoi(stringSeparada[3].c_str()))){
                        case -1:
                            imprimeErro("Nao existe a colonia \'" + stringSeparada[1] + "\'!\n");
                        break;
                        case 0:
                            imprimeErro("Posicao ja ocupada!\n");
                        break;
                        case 1:
                            imprimeLog("Castelo movido com sucesso!\n");
                        break;
                    }
                }else{
                    imprimeErro("Argumentos -lin -col, tem que ser inteiros positivos!\n");
                }
            }else{
                imprimeErro("Numero de argumentos errado!\n       castelo -colonia -lin -col.\n");
            }
        }else if(stringSeparada[0] == "mkperfil"){
            if(config){
                if(c_oponentes){
                    if(stringSeparada.size() == 2){
                        switch(comando_mkperfil("A", stringSeparada[1])){
                            case -2:
                                imprimeErro("Colonia nao encontrada\n");
                            break;
                            case -1:
                                imprimeErro("Ja tem a capacidade maximo de perfil!\n");
                            break;
                            case 0:
                                imprimeErro("Ja existe um perfil com o mesmo nome\n");
                            break;
                            case 1:
                                imprimeLog("Perfil \'" + stringSeparada[1] + "\' criada com sucesso!\n");
                                c_mkperfil = true;
                            break;
                        }
                    }else{
                        imprimeErro("Numero de argumentos errado!\n       mkperfil -letra.\n");
                    }
                }else{
                    imprimeErro("Defina primeiro os oponentes!\n");
                }
            }else{
                imprimeErro("Configuracao terminada!\n");
            }
        }else if(stringSeparada[0] == "addperfil"){
            if(config){
                if(c_mkperfil){
                    if(stringSeparada.size() == 3){
                        if(checkNumero(stringSeparada[2])){
                            inputInt = atoi(stringSeparada[2].c_str());
                            if(inputInt > 0 && inputInt < 15){
                                switch(comando_addperfil("A", controlador->toLower(stringSeparada[1]), inputInt)){
                                    case -2:
                                        imprimeErro("Colonia nao encontrada\n");
                                    break;
                                    case -1:
                                        imprimeErro("Nao foi encontrado o perfil \'" + stringSeparada[1] + "\'!\n");
                                    break;
                                    case 0:
                                        imprimeErro("Nao consegue adicionar mais caracteristicas!\n");
                                    break;
                                    case 1:
                                        imprimeLog("Caracteristica \'" + stringSeparada[2] + "\' criada com sucesso!\n");
                                    break;
                                }
                            }else{
                                imprimeErro("So exite 1 a 14 caracteristicas!\n");
                            }
                        }else{
                            imprimeErro("O segundo argumento tem que se inteiro positivo!\n");
                        }
                    }else{
                        imprimeErro("Numero de argumentos errado!\n       addperfil -letra -caracteristica.\n");
                    } 
                }else{
                    imprimeErro("Crie pelo menos um perfil!\n");
                }
            }else{
                imprimeErro("Configuracao terminada!\n");
            }
        }else if(stringSeparada[0] == "subperfil"){
            if(config){
                if(stringSeparada.size() == 3){
                    if(checkNumero(stringSeparada[2])){
                        inputInt = atoi(stringSeparada[2].c_str());
                        if(inputInt > 0 && inputInt < 15){
                            switch(comando_subperfil("A", controlador->toLower(stringSeparada[1]), inputInt)){
                                case -2:
                                    imprimeErro("Colonia nao encontrada\n");
                                break;
                                case -1:
                                    imprimeErro("Nao foi encontrado o perfil \'" + stringSeparada[1] + "\'!\n");
                                break;
                                case 0:
                                    imprimeErro("Nao encontrado a caracteristica!\n");
                                break;
                                case 1:
                                    imprimeLog("Caracteristica \'" + stringSeparada[2] + "\' removida com sucesso!\n");
                                break;
                            }
                        }else{
                            imprimeErro("So exite 1 a 14 caracteristicas!\n");
                        }
                    }else{
                        imprimeErro("O segundo argumento tem que se inteiro positivo!\n");
                    }
                }else{
                    imprimeErro("Numero de argumentos errado!\n       subperfil -letra -caracteristica.\n");
                }  
            }else{
                imprimeErro("Configuracao terminada!\n");
            }
        }else if(stringSeparada[0] == "rmperfil"){
            if(config){
                if(stringSeparada.size() == 2){
                    if(comando_rmperfil("A", stringSeparada[1])){
                        imprimeLog("Perfil removido com sucesso!\n");
                    }else{
                        imprimeErro("perfil não encontrado!\n");
                    }
                }else{
                    imprimeErro("Numero de argumentos errado!\n       rmperfil -letra.\n");
                } 
            }else{
                imprimeErro("Configuracao terminada!\n");
            }
        }else if(stringSeparada[0] == "load"){
            if(stringSeparada.size() == 2){
                if(!comando_load(stringSeparada[1])){
                    imprimeErro("Ficheiro nao encontrado!\n");
                }
            }else{
                imprimeErro("Numero de argumentos errado!\n       load -ficheiro.\n");
            }
        }else if(stringSeparada[0] == "inicio"){
            if(isConfig()){
                comando_inicio();
                config = false;
            }
        }
        else if(stringSeparada[0] == "foco"){
            if(atoi(stringSeparada[1].c_str())-10 < 0){
                this->focoLinhas = 0;
            }else{
                if(atoi(stringSeparada[1].c_str())+10 >= controlador->getLinhasDefault()){
                    this->focoLinhas = controlador->getLinhasDefault() - 20;
                }else{
                    this->focoLinhas = atoi(stringSeparada[1].c_str()) - 10;
                }
            }
            if(atoi(stringSeparada[2].c_str())-20 < 0){
                this->focoColunas = 0;
            }else{
                if(atoi(stringSeparada[2].c_str())+20 >= controlador->getColunasDefault()){
                    this->focoColunas = controlador->getLinhasDefault() - 40;
                }else{
                    this->focoColunas = atoi(stringSeparada[2].c_str()) - 20;
                }
            }
        }else if(stringSeparada[0] == "list"){
            Colonia* c;
            if(stringSeparada.size() == 1){
                controlador->listarTudo();
            }else{
                c = controlador->getColonia(controlador->toUpper(stringSeparada[1]));
                if(c != NULL){
                    c->listar();
                }else{
                    imprimeErro("Nao foi encontrada essa colonia!\n");
                }
            }
        }else if(stringSeparada[0] == "listp"){
            if(stringSeparada.size()==2){
                for(int i = 0; i < controlador->getVectorColonia()->size(); i++){
                    for(int j = 0; j < controlador->getVectorColonia()->at(i).getVectorPerfil()->size(); j++){
                      if(controlador->getVectorColonia()->at(i).getVectorPerfil()->at(j).getNome() == stringSeparada[1]){
                          controlador->getVectorColonia()->at(i).getVectorPerfil()->at(j).listarTudo();
                          break;
                      }  
                    }
                }
            }else{
                imprimeErro("Numero de argumentos errado!           listp PERFIL\n");
            }
                
        }else if(stringSeparada[0] == "listallp"){
            if(stringSeparada.size()==1){
                for(int i = 0; i < controlador->getVectorColonia()->size(); i++){
                    for(int j = 0; j < controlador->getVectorColonia()->at(i).getVectorPerfil()->size(); j++){
                        controlador->getVectorColonia()->at(i).getVectorPerfil()->at(j).listarTudo();

                    }
                }
            }else{
                imprimeErro("Comando errado !!     listallp!");
            }
        }else if(stringSeparada[0] == "setmoedas"){
            if(stringSeparada.size() == 3){
                if(checkNumero(stringSeparada[2])){
                    Colonia* c;
                    c = controlador->getColonia(controlador->toUpper(stringSeparada[1]));
                    if(c != NULL){
                        c->setMoedas(atoi(stringSeparada[2].c_str()));
                        imprimeLog("Moedas alteradas com sucesso!\n");
                    }else{
                        imprimeErro("Nao foi encontrada essa colonia!\n");
                    }
                }else{
                    imprimeErro("O segundo argumento tem que se inteiro positivo!\n");
                }
            }else{
                imprimeErro("Numero de argumentos errado!\n       setmoedas -colonia -num.\n");
            }
        }else if(stringSeparada[0] == "build" || stringSeparada[0] == "mkbuild"){
            string colString;
            if(stringSeparada.size() >= 4){
                if(checkNumero(stringSeparada[2]) && checkNumero(stringSeparada[3])){
                    if(stringSeparada[0] == "mkbuild"){
                        colString = controlador->toUpper(stringSeparada[4]);
                    }else{
                        colString = "A";
                    }
                    switch(comando_build(colString, controlador->toLower(stringSeparada[1]) , atoi(stringSeparada[2].c_str()), atoi(stringSeparada[3].c_str()))){
                        case -3:
                            imprimeErro("Esse edificio nao existe!\n");
                        break;
                        case -2:
                            imprimeErro("Nao foi encontrado a colonia indicada!\n");
                        break;
                        case -1:
                            imprimeErro("A sua colonia nao tem dinheiro!\n");
                        break;
                        case 0:
                            imprimeErro("Nao se encontra no perimetro do castelo, ou posicao ja ocupada!\n");
                        break;
                        case 1:
                            imprimeLog("Edifico criado com sucesso!\n");
                        break;
                    }
                }else{
                    imprimeErro("Os ultimos 2 argumentos tem que ser inteiros positivos!\n");  
                }
            }else{
                imprimeErro("Numero de argumentos errado!\n       build -edif -lin -col.\n");
            }
        }else if(stringSeparada[0] == "repair"){
            if(stringSeparada.size() == 2){
                if(checkNumero(stringSeparada[1])){
                    switch(comando_repair("A", atoi(stringSeparada[1].c_str()))){
                        case -3:
                            imprimeErro("Edificio destroido!\n");
                        break;
                        case -2:
                            imprimeErro("Nao tem dinheiro sucifiente!\n");
                        break;
                        case -1:
                            imprimeErro("Nao foi encontrada a colonia!\n");
                        break;
                        case 0:
                            imprimeErro("Nao foi encontrado nenhum edicifio com esse id!\n");
                        break;
                        case 1:
                            imprimeLog("Reparacao realizada com sucesso!\n");
                        break;
                    }
                }else{
                    imprimeErro("O argumento tem que ser um valor inteiro positivo.\n");
                }
            }else{
                imprimeErro("Numero de argumentos errado!\n       repair -EID.\n");
            }            
        }else if(stringSeparada[0] == "upgrade"){
            if(stringSeparada.size() == 2){
                if(checkNumero(stringSeparada[1])){
                    switch(comando_upgrade("A", atoi(stringSeparada[1].c_str()))){
                        case -2:
                            imprimeErro("Nao tem dinheiro sucifiente!\n");
                        break;
                        case -1:
                            imprimeErro("Nao foi encontrada a colonia!\n");
                        break;
                        case 0:
                            imprimeErro("Nao foi encontrado nenhum edicifio com esse id!\n");
                        break;
                        case 1:
                            imprimeLog("Upgrade realizado com sucesso!\n");
                        break;
                    }
                }else{
                    imprimeErro("O argumento tem que ser um valor inteiro positivo.\n");
                }
            }else{
                imprimeErro("Numero de argumentos errado!\n       upgrade -EID.\n");
            } 
        }else if(stringSeparada[0] == "sell"){
            if(stringSeparada.size() == 2){
                if(checkNumero(stringSeparada[1])){
                    switch(comando_sell("A", atoi(stringSeparada[1].c_str()))){
                        case -1:
                            imprimeErro("Nao foi encontrada a colonia!\n");
                        break;
                        case 0:
                            imprimeErro("Nao foi encontrado nenhum edicifio com esse id!\n");
                        break;
                        case 1:
                            imprimeLog("Edificio vendido com sucesso!\n");
                        break;
                    }
                }else{
                    imprimeErro("O argumento tem que ser um valor inteiro positivo.\n");
                }
            }else{
                imprimeErro("Numero de argumentos errado!\n       sell -EID.\n");
            } 
        }else if(stringSeparada[0] == "ser"){
            if(stringSeparada.size() == 3){
                if(checkNumero(stringSeparada[1])){
                    switch(comando_ser("A", atoi(stringSeparada[1].c_str()), stringSeparada[2])){
                        case -2:
                            imprimeErro("Nao tem dinheiro suficiente!\n");
                        break;
                        case -1:
                            imprimeErro("Nao foi encontrada a colonia!\n");
                        break;
                        case 0:
                            imprimeErro("Nao foi encontrado nenhum perfil com esse nome!\n");
                        break;
                        case 1:
                            imprimeLog("Seres criados com sucesso!\n");
                        break;
                    }
                }else{
                    imprimeErro("O argumento -num tem que ser um valor inteiro positivo.\n");
                }
            }else{
                imprimeErro("Numero de argumentos errado!\n       ser -num -perf.\n");
            }  
        }else if(stringSeparada[0] == "next"){
            if(stringSeparada.size() == 1){
                controlador->next(1);
            }else if(stringSeparada.size() == 2){
                if(checkNumero(stringSeparada[1])){
                    controlador->next(atoi(stringSeparada[1].c_str()));
                }else{
                    imprimeErro("O argumento tem que ser um valor inteiro positivo!\n");
                }
            }else{
                imprimeErro("Numero de argumentos errados!\n       next -num.\n");
            }            
        }else if(stringSeparada[0] == "ataca"){
            
        }else if(stringSeparada[0] == "recolhe"){
            
        }else{ 
            imprimeErro("Digite um comando valido!\n");
        }
    }else{
        imprimeErro("Digite um comando!\n");
    }
    return true;
}

bool Gestor::comando_load(string ficheiro) {
    ifstream dados(ficheiro);
    string linha;
    if(!dados.is_open()){
        return false;
    }
    while(!dados.eof()){
        getline(dados, linha);
        intrepertaComandos(linha);
    }
    dados.close();
    return true;
}

void Gestor::comando_inicio() {
    controlador->atribuirPerfil();
}

int Gestor::comando_build(string co, string edif, int linha, int coluna) {
    Colonia* c = controlador->getColonia(controlador->toUpper(co));
    int result;
    if(c != NULL){
        if(edif == "torre"){
            result = c->addEdificio(Torre(linha, coluna, c->getID()));
        }else if(edif == "quinta"){
            result = c->addEdificio(Quinta(linha, coluna, c->getID()));
        }else{
            return -3;
        }
        switch(result){
            case -1:
                return -1;
            break;
            case 0:
                return 0;
            break;
            case 1:
                return 1;
            break;
        }
    }else{
        return -2;
    }
}

int Gestor::comando_repair(string co, int id) {
    Colonia* c = controlador->getColonia(controlador->toUpper(co));
    int custoReparacao;
    if(c != NULL){
        Edificios* e = c->getEdificio(id);
        if(e != NULL){
            if(e->getSaude()>0){
                custoReparacao = (e->getCusto()*e->getSaude())/e->getSaudeMAX();
                if(c->getMoedas()-custoReparacao >= 0){
                    c->setMoedas(c->getMoedas()-custoReparacao);
                    e->setSaude(e->getSaudeMAX());
                    return 1;
                }else{
                    return -2;
                }
            }else{
                return -3;
            }
        }else{
            return 0;
        }
    }else{
        return -1;
    }
}

int Gestor::comando_upgrade(string co, int id) {
    Colonia* c = controlador->getColonia(controlador->toUpper(co));
    if(c != NULL){
        Edificios* e = c->getEdificio(id);
        if(e != NULL){
            if(c->getMoedas()-10 >= 0){
                e->upgradeNivel();
                c->setMoedas(c->getMoedas()-10);
                return 1;
            }else{
                return -2;
            }
        }else{
            return 0;
        }
    }else{
        return -1;
    }
}

int Gestor::comando_sell(string co, int id) {
    Colonia* c = controlador->getColonia(controlador->toUpper(co));
    if(c != NULL){
        Edificios* e = c->getEdificio(id);
        if(e != NULL){
            c->setMoedas((c->getMoedas()+(e->getCusto()/2)));
            c->removeEdificio(id);
            return 1;
        }else{
            return 0;
        }
    }else{
        return -1;
    }
}

int Gestor::comando_ser(string co, int num, string perf) {
    Colonia* c = controlador->getColonia(controlador->toUpper(co));
    int custoTotal;
    if(c != NULL){
        Perfil* p = c->getPerfil(controlador->toLower(perf));
        if(p != NULL){
            custoTotal = p->getCusto() * num;
            if(c->getMoedas()-custoTotal >= 0){
                for(int i = 0; i < num; i++){
                    c->addSer(p, c->getCastelo()->getLinha(), c->getCastelo()->getColuna());
                }
                return 1;
            }else{
                return -2;
            }
        }else{
            return 0;
        }
    }else{
        return -1;
    }
}

void Gestor::comando_dim(int linhas, int colunas) {
    controlador->setLinhasDefault(linhas);
    controlador->setColunasDefault(colunas);
}

void Gestor::comando_moedas(int num) {
    controlador->setMoedasDefault(num);
}

bool Gestor::comando_oponentes(int num) {
    controlador->apagarVectorColonias();
    controlador->addColonia();
    for(int i = 0; i < num; i++){
        if(!controlador->addColonia()){
            return false;
        }
    }
    return true;
}

int Gestor::comando_castelo(string nome, int linha, int coluna) {
    Colonia* c = controlador->getColonia(controlador->toUpper(nome));
    if(c != NULL){
        if(controlador->verificaPosicao(linha, coluna) == NULL){
            c->getCastelo()->setLinhaColuna(linha, coluna);
            return 1;
        }else{
            return 0;
        }
    }else{
        return -1;
    }
}


int Gestor::comando_mkperfil(string co, string ca) {
    Colonia* c = controlador->getColonia(controlador->toUpper(co));
    if(c != NULL){
        switch(c->addPerfil(controlador->toLower(ca))){
            case -1:
                return -1;
            break;
            case 0:
                return 0;
            break;
            case 1:
                return 1;
            break;
        }
    }else{
        return -2;
    }
}

int Gestor::comando_addperfil(string co, string ca, int id) {
    Colonia* c = controlador->getColonia(controlador->toUpper(co));
    if(c != NULL){
        if(c->getPerfil(controlador->toLower(ca)) != NULL){
            if(c->getPerfil(controlador->toLower(ca))->addCaracteristica(new Caracteristica(id))){
                return 1;
            }else{
                return 0;
            }
        }else{
            return -1;
        }
    }else{
        return -2;
    }
}

int Gestor::comando_subperfil(string co, string ca, int id) {
    Colonia* c = controlador->getColonia(controlador->toUpper(co));
    if(c != NULL){
        if(c->getPerfil(controlador->toLower(ca)) != NULL){
            if(c->getPerfil(controlador->toLower(ca))->removeCarateristica(id)){
                return 1;
            }else{
                return 0;
            }
        }else{
            return -1;
        }
    }else{
        return -2;
    }
}

int Gestor::comando_rmperfil(string co, string ca) {
    Colonia* c = controlador->getColonia(controlador->toUpper(co));
    if(c != NULL){
        if(c->removePerfil(controlador->toLower(ca))){
            return 1;
        }else{
            return 0;
        }
    }else{
        return -1;
    }
}

vector<string> Gestor::separaComando(string comando, char separador) {
    vector<string> stringSeparada;
    stringstream ss;
    ss.str(comando);
    string token;
    while(getline(ss, token, separador)){
        if(!token.empty()){
            stringSeparada.push_back(token);
        }
    }
    return stringSeparada;
}

void Gestor::imprimeLogo() {
    Consola::setTextColor(Consola::VERMELHO_CLARO);
    cout << "        <";
    Consola::setTextColor(Consola::BRANCO_CLARO);
    cout << "----- "; 
    Consola::setTextColor(Consola::VERMELHO_CLARO);
    cout << "C";
    Consola::setTextColor(Consola::BRANCO_CLARO);
    cout << "ASTLE";   
    Consola::setTextColor(Consola::VERMELHO_CLARO);
    cout << "W";
    Consola::setTextColor(Consola::BRANCO_CLARO);
    cout << "AR!";    
    Consola::setTextColor(Consola::BRANCO_CLARO);
    cout << " -----"; 
    Consola::setTextColor(Consola::VERMELHO_CLARO);
    cout << ">" << endl;
    Consola::setTextColor(Consola::BRANCO_CLARO);
}

void Gestor::imprimeErro(string msg) {
    Consola::setTextColor(Consola::VERMELHO_CLARO);
    cout << "[ERRO] ";
    Consola::setTextColor(Consola::BRANCO_CLARO);
    cout << msg;
}

void Gestor::imprimeLog(string msg) {
    Consola::setTextColor(Consola::VERDE_CLARO);
    cout << "[LOG] ";
    Consola::setTextColor(Consola::BRANCO_CLARO);
    cout << msg;
}

void Gestor::imprimePedidoInfo(string msg) {
    Consola::setTextColor(Consola::AMARELO_CLARO);
    cout << "   -> ";
    Consola::setTextColor(Consola::BRANCO_CLARO);
    cout << msg;
}

bool Gestor::checkNumero(const string s) {
    return (s.find_first_not_of( "0123456789" ) == string::npos);
}

bool Gestor::isConfig() {
    if(c_dim && c_mkperfil && c_moedas && c_oponentes){
        return true;
    }else{
        return false;
    }
}

Gestor::~Gestor() {
    delete(controlador);
}
