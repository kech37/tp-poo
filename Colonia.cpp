/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Colonia.cpp
 * Author: carlo
 * 
 * Created on 28 de Dezembro de 2016, 19:35
 */

#include "Colonia.h"
#include "Castelo.h"

int Colonia::conta = 0;

Colonia::Colonia(string nome, int moedas) {    
    this->nome = nome;
    this->moedas = moedas;
    this->id = conta;
    this->conta++;
    
}

int Colonia::getID() const {
    return this->id;
}

int Colonia::addPerfil(string nome) {
    if(vectorPerfil.size() < 5){
        if(getPerfil(nome) == NULL){
            vectorPerfil.push_back(Perfil(nome));
            return 1;
        }else{
            return 0;
        }
    }else{
        return -1;
    }
}
int Colonia::addPerfil(const Perfil &p){
    if(vectorPerfil.size() < 5){
        if(getPerfil(p.getNome()) == NULL){
            vectorPerfil.push_back(p);
            return 1;
        }else{
            return 0;
        }
    }else{
        return -1;
    }
}
Perfil* Colonia::getPerfil(string nome) {
    for(int i = 0; i < vectorPerfil.size(); i++){
        if(vectorPerfil[i].getNome() == nome){
            return &vectorPerfil[i];
        }
    }
    return NULL;
}

bool Colonia::removePerfil(string nome) {
    for(int i = 0; i < vectorPerfil.size(); i++){
        if(vectorPerfil[i].getNome() == nome){
            vectorPerfil.erase(vectorPerfil.begin()+i);
            return true;
        }
    }
    return false;
}

int Colonia::addSer(Perfil* perfil, int linha, int coluna) {
    if(vectorEdificios[0].getSaude() != 0){
        if(this->moedas-perfil->getCusto() >= 0){
            vectorSer.push_back(Ser(perfil, linha, coluna, this->id));
            this->moedas -= perfil->getCusto();
            return 1;
        }else{
            return -1;
        }
    }else{
        return 0;
    }
}

int Colonia::addEdificio(Edificios e) {
    if(vectorEdificios.empty()){
        vectorEdificios.push_back(e);
        return 1;
    }else{
        if(raioCastelo(e)){
            if((this->moedas-e.getCusto()) >= 0){
                vectorEdificios.push_back(e);
                this->moedas-=e.getCusto();
                return 1;
            }else{
                return -1;
            }
        }else{
            return 0;
        }
    }
}

bool Colonia::removeEdificio(int id) {
    if(vectorEdificios.size()>0){
        for(int i = 0; i < vectorEdificios.size(); i++){
            if(vectorEdificios[i].getID() == id){
                vectorEdificios.erase(vectorEdificios.begin()+i);
                return true;
            }
        }
        return false;
    }else{
        return false;
    }
}

bool Colonia::raioCastelo(Edificios& e) {
    if(!vectorEdificios.empty()){
        if((vectorEdificios.front().getLinha()-10) <= e.getLinha() && e.getLinha() <= (vectorEdificios.front().getLinha()+10)){
            if((vectorEdificios.front().getColuna()-10) <= e.getColuna() && e.getColuna() <= (vectorEdificios.front().getColuna()+10)){
                for(int i = 0; i < vectorEdificios.size(); i++){
                    if(vectorEdificios[i].getLinha() == e.getLinha() && vectorEdificios[i].getColuna() == e.getColuna()){
                        return false;
                    }
                }
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }else{
        return false;
    }
}

Edificios* Colonia::getCastelo() {
    if(vectorEdificios.size()>0){
        if(vectorEdificios.front().getNome() == "C"){
            return &vectorEdificios.front();
        }else{
            return NULL;
        }
    }else{
        return NULL;
    }
}

Edificios* Colonia::getEdificio(int id) {
    if(vectorEdificios.size()>0){
        for(int i = 0; i < vectorEdificios.size(); i++){
            if(vectorEdificios[i].getID() == id){
                return &vectorEdificios[i];
            }
        }
        return NULL;
    }else{
        return NULL;
    }
}

vector<Edificios>* Colonia::getVectorEdificios() {
    return &vectorEdificios;
}

vector<Perfil>* Colonia::getVectorPerfil() {
    return &vectorPerfil;
}

vector<Ser>* Colonia::getVectorSer() {
    return &vectorSer;
}

int Colonia::getMoedas() const {
    return this->moedas;
}

void Colonia::setMoedas(int num) {
    this->moedas = num;
}

string Colonia::getNome() const {
    return this->nome;
}

void Colonia::listar() {
        cout << "   Colonia: " << this->nome << " - Moedas: " << this->moedas << endl;

        cout << "       Seres: " << endl;
        if(vectorSer.size() > 0){
            for(int i = 0; i < vectorSer.size(); i++){
                cout << "           "<< vectorSer[i].getNome() << endl;
                cout << "           " << vectorSer[i].getID() << ") " << vectorSer[i].getPerfil()->getNome();
                cout << "           ["<< vectorSer[i].getLinha() << ":" << vectorSer[i].getColuna() << "]" << endl;
                cout << "           "<< "Saude: "<< vectorSer[i].getSaude() << endl;
                cout << "           "<< "Defesa: "<< vectorSer[i].getDefesa() << endl;
                cout << "           "<< "Ataque: "<< vectorSer[i].getAtaque() << endl;      
            }   
        }else{
            cout << "           <Sem Seres>" << endl;
        }
        
        
        cout << "       Edificios: " << endl;
        if(vectorEdificios.size() > 0){
            for(int i = 0; i < vectorEdificios.size(); i++){
                cout << "           " << vectorEdificios[i].getID() << ") " << vectorEdificios[i].getNome() << " ["<< vectorEdificios[i].getLinha() << ", " << vectorEdificios[i].getColuna() << "]" << endl;
                cout << "           " << "Defesa: " << vectorEdificios[i].getDefesa() << endl;
                cout << "           " << "Saude: " <<vectorEdificios[i].getSaude() << endl;
            }
        }else{
            cout << "           <Sem Edificios>" << endl;
        }
}

Colonia::~Colonia() {
    //delete(this);
}

