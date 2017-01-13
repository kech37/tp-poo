/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Controlador.cpp
 * Author: carlo
 * 
 * Created on 30 de Dezembro de 2016, 15:24
 */

#include <numeric>
#include <algorithm>

#include "Controlador.h"
#include "Consola.h"

Controlador::Controlador() {
    this->moedasDefault = 0;
    this->colunasDefault = 0;
    this->linhasDefault = 0;
    srand(time(NULL));
}

void Controlador::setLinhasDefault(int linhas) {
    this->linhasDefault = linhas;
}

int Controlador::getLinhasDefault() const {
    return this->linhasDefault;
}

void Controlador::setColunasDefault(int colunas) {
    this->colunasDefault = colunas;
}

int Controlador::getColunasDefault() const {
    return this->colunasDefault;
}

void Controlador::setMoedasDefault(int moedas) {
    this->moedasDefault = moedas;
}

int Controlador::getRandomColunas() {
    return (rand() % colunasDefault);
}

int Controlador::getRandomLinhas() {
    return (rand() % linhasDefault);
}
bool Controlador::addColonia() {
    Colonia* c;
    int i = -1;
    int linha, coluna;
    do{
        i++;
        c = getColonia(this->nomes[i]);
    }while(c != NULL && i < 26);
    if(i < 26){
        vectorColonias.push_back(Colonia(this->nomes[i], this->moedasDefault));
        c = &vectorColonias.back();
        do{
            linha = getRandomLinhas();
            coluna = getRandomColunas();
        }while(verificaPosicao(linha, coluna) != NULL);
        c->getVectorEdificios()->push_back(Castelo(linha, coluna, c->getID()));
        return true;
    }else{
        return false;
    }
}

Colonia* Controlador::getColonia(string nome) {
    for(int i = 0; i < vectorColonias.size(); i++){
        if(vectorColonias[i].getNome() == nome){
            return &vectorColonias[i];
        }
    }
    return NULL;
}

vector<Colonia>* Controlador::getVectorColonia() {
    return &vectorColonias;
}

void Controlador::apagarVectorColonias() {
    vectorColonias.clear();
}

Unidade* Controlador::verificaPosicao(int linha, int coluna) {
    if(linha < this->linhasDefault && coluna < this->colunasDefault){
        for(int i = 0; i < vectorColonias.size(); i++){
            for(int j = 0; j < vectorColonias[i].getVectorEdificios()->size(); j++){
                if(vectorColonias[i].getVectorEdificios()->at(j).checkPosicao(linha, coluna)){
                    return &vectorColonias[i].getVectorEdificios()->at(j);
                }
            }
            for(int j = 0; j < vectorColonias[i].getVectorSer()->size(); j++){
                if(vectorColonias[i].getVectorSer()->at(j).checkPosicao(linha, coluna)){
                    return &vectorColonias[i].getVectorSer()->at(j);
                }
            }
        }
    }
    return NULL;
}

Unidade* Controlador::getUnidade(Colonia* colonia, int id, int tipo) {
    switch(tipo){
        case EDIFICIO:
            for(int i = 0; i < colonia->getVectorEdificios()->size(); i++){
                if(colonia->getVectorEdificios()->at(i).getID() == id){
                    return &colonia->getVectorEdificios()->at(i);
                }
            }
        break;
        case SER:
            for(int i = 0; i < colonia->getVectorSer()->size(); i++){
                if(colonia->getVectorSer()->at(i).getID() == id){
                    return &colonia->getVectorSer()->at(i);
                }
            }    
        break;
    }
    return NULL;
}

bool Controlador::addEdificio(Colonia* colonia, Edificios edificio){
    if(colonia->addEdificio(edificio)){
        return true;
    }else{
        return false;
    }
}
Ser* Controlador::getSer(int linha, int coluna){
    for(int i = 0; i < vectorColonias.size(); i++){
        for(int j = 0; j < vectorColonias[i].getVectorSer()->size(); j++){
            if(vectorColonias[i].getVectorSer()->at(j).checkPosicao(linha, coluna)){
                return &vectorColonias[i].getVectorSer()->at(j);
            }
        }
    }
    return NULL;
}

Edificios* Controlador::getEdifico(int linha, int coluna){
    for(int i = 0; i < vectorColonias.size(); i++){
        for(int j = 0; j < vectorColonias[i].getVectorEdificios()->size(); j++){
            if(vectorColonias[i].getVectorEdificios()->at(j).checkPosicao(linha, coluna)){
                return &vectorColonias[i].getVectorEdificios()->at(j);
            }
        }
    }
    return NULL;
}

void Controlador::atribuirPerfil() {
    vector<int> v(4);
    iota(v.begin(), v.end(), 0);
    int tamA = getColonia("A")->getVectorPerfil()->size(), resp, car, nom;
    for(int i = 1; i < vectorColonias.size(); i++){
        if(tamA > 3){
            random_shuffle(v.begin(), v.end());
            for(int j = 0; j < 5; j++){
                if(j < 3){
                    vectorColonias[i].getVectorPerfil()->push_back(Perfil(vectorColonias[0].getVectorPerfil()->at(v[j])));
                }else{
                    do{
                        nom = rand() % 26;
                        resp = vectorColonias[i].addPerfil(toLower(nomes[nom]));
                    }while(resp != 1);
                    do{
                        car = rand() % 14 + 1; 
                    }while(vectorColonias[i].getPerfil(toLower(nomes[nom]))->addCaracteristica(new Caracteristica(car)));
                }
            }
        }else{
            for(int j = 0; j < 5; j++){
                if(j < tamA){
                    vectorColonias[i].getVectorPerfil()->push_back(Perfil(vectorColonias[0].getVectorPerfil()->at(j)));
                }else{
                    do{
                        nom = rand() % 26;
                        resp = vectorColonias[i].addPerfil(toLower(nomes[nom]));
                    }while(resp != 1);
                    do{
                        car = rand() % 14 + 1; 
                    }while(vectorColonias[i].getPerfil(toLower(nomes[nom]))->addCaracteristica(new Caracteristica(car)));
                }
            }
        }
    }
}

void Controlador::listarTudo() {
    for(int i = 0; i < vectorColonias.size(); i++){
        vectorColonias[i].listar();
    }
}

void Controlador::next(int num) {
    for(int round = 0; round < num; round++){
        for(int i = 0; i < vectorColonias.size(); i++){
            for(int j = 0; j < vectorColonias[i].getVectorSer()->size(); j++){
                int index_car = 0;
                Ser* ser = &vectorColonias[i].getVectorSer()->at(j);
                Caracteristica* car = ser->getPerfil()->getCarateristica(index_car);
                int escolhido;
                while(car != NULL){
                    switch(car->getId()){
                        case 7: //Agressão
                            Ser* serAtacar[8];
                            serAtacar[0] = this->getSer(ser->getLinha()-1, ser->getColuna()-1);
                            serAtacar[1] = this->getSer(ser->getLinha(), ser->getColuna()-1);
                            serAtacar[2] = this->getSer(ser->getLinha()+1, ser->getColuna()-1);
                            serAtacar[3] = this->getSer(ser->getLinha()+1, ser->getColuna());
                            serAtacar[4] = this->getSer(ser->getLinha()+1, ser->getColuna()+1);
                            serAtacar[5] = this->getSer(ser->getLinha(), ser->getColuna()+1);
                            serAtacar[6] = this->getSer(ser->getLinha()-1, ser->getColuna()+1);
                            serAtacar[7] = this->getSer(ser->getLinha()-1, ser->getColuna());
                            for(int k = 0; k < 8; k++){
                                if(serAtacar[k] != NULL && serAtacar[k]->getEquipa() != ser->getEquipa()){
                                    if(ser->getAtaque() > serAtacar[escolhido]->getDefesa()){
                                        serAtacar[escolhido]->setSaude(serAtacar[escolhido]->getSaude()-(ser->getAtaque()-serAtacar[escolhido]->getDefesa()));
                                    }else{
                                        serAtacar[escolhido]->setSaude(serAtacar[escolhido]->getSaude()-1);
                                    }
                                    k = 8;
                                }
                            }
                            break;
                        case 8: //Ecologico
                            Edificios* ediAtacar[8];
                            ediAtacar[0] = this->getEdifico(ser->getLinha()-1, ser->getColuna()-1);
                            ediAtacar[1] = this->getEdifico(ser->getLinha(), ser->getColuna()-1);
                            ediAtacar[2] = this->getEdifico(ser->getLinha()+1, ser->getColuna()-1);
                            ediAtacar[3] = this->getEdifico(ser->getLinha()+1, ser->getColuna());
                            ediAtacar[4] = this->getEdifico(ser->getLinha()+1, ser->getColuna()+1);
                            ediAtacar[5] = this->getEdifico(ser->getLinha(), ser->getColuna()+1);
                            ediAtacar[6] = this->getEdifico(ser->getLinha()-1, ser->getColuna()+1);
                            ediAtacar[7] = this->getEdifico(ser->getLinha()-1, ser->getColuna());
                            for(int k = 0; k < 8; k++){
                                if(ediAtacar[k] != NULL && ediAtacar[k]->getEquipa() != ser->getEquipa()){
                                    if(ser->getAtaque() > ediAtacar[escolhido]->getDefesa()){
                                        ediAtacar[escolhido]->setSaude(ediAtacar[escolhido]->getSaude()-(ser->getAtaque() - ediAtacar[escolhido]->getDefesa()));
                                    }else{
                                        ediAtacar[escolhido]->setSaude(ediAtacar[escolhido]->getSaude()-1);
                                    }
                                    k = 8;
                                }
                            }
                            break;
                        case 9:
                            
                            break;
                        case 10:
                            
                            break;
                        case 11:
                            switch(rand() % 8){
                                case 0:
                                    if(verificaPosicao(ser->getLinha()-1, ser->getColuna()-1) == NULL){
                                        ser->setLinha(ser->getLinha()-1);
                                        ser->setColuna(ser->getColuna()-1);
                                    }
                                    break;
                                case 1:
                                    if(verificaPosicao(ser->getLinha(), ser->getColuna()-1) == NULL){
                                        ser->setColuna(ser->getColuna()-1);
                                    }
                                    break;
                                case 2:
                                    if(verificaPosicao(ser->getLinha()+1, ser->getColuna()-1) == NULL){
                                        ser->setLinha(ser->getLinha()+1);
                                        ser->setColuna(ser->getColuna()-1);
                                    }
                                    break;
                                case 3:
                                    if(verificaPosicao(ser->getLinha()+1, ser->getColuna()) == NULL){
                                        ser->setLinha(ser->getLinha()+1);
                                    }
                                    break;
                                case 4:
                                    if(verificaPosicao(ser->getLinha()+1, ser->getColuna()+1) == NULL){
                                        ser->setLinha(ser->getLinha()+1);
                                        ser->setColuna(ser->getColuna()+1);
                                    }
                                    break;
                                case 5:
                                    if(verificaPosicao(ser->getLinha(), ser->getColuna()+1) == NULL){
                                        ser->setColuna(ser->getColuna()+1);
                                    }
                                    break;
                                case 6:
                                    if(verificaPosicao(ser->getLinha()-1, ser->getColuna()+1) == NULL){
                                        ser->setLinha(ser->getLinha()-1);
                                        ser->setColuna(ser->getColuna()+1);
                                    }
                                    break;
                                case 7:
                                    if(verificaPosicao(ser->getLinha()-1, ser->getColuna()) == NULL){
                                        ser->setLinha(ser->getLinha()-1);
                                    }
                                    break;
                            }
                            break;
                        case 12:
                            
                            break;
                        case 13:
                            
                            break;
                        case 14:
                            
                            break;
                    }
                    index_car++;
                    car = ser->getPerfil()->getCarateristica(index_car);
                }
            }
        }
    }
}

string Controlador::toLower(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

string Controlador::toUpper(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}