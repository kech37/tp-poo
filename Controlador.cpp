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

string Controlador::toLower(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

string Controlador::toUpper(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}