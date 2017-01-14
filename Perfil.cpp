/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Perfil.cpp
 * Author: carlo
 * 
 * Created on 28 de Dezembro de 2016, 18:40
 */

#include <iostream>

#include "Perfil.h"

Perfil::Perfil(string nome) {
    this->nome = nome;
    this->forca = 10;
    this->custo = 0;
}

Perfil::Perfil(const Perfil &p){
    this->nome = p.nome;
    this->forca = p.forca;
    this->nome = p.nome;
    this->vetorCaracteristicas = p.vetorCaracteristicas;
    this->custo = p.custo;
}

Perfil& Perfil::operator=(Perfil p) {
    if(this != &p){
        this->custo = p.custo;
        this->forca = p.forca;
        this->nome = p.nome;
        this->vetorCaracteristicas = p.vetorCaracteristicas;
        this->custo = p.custo;
    }
    return *this;
}


bool Perfil::addCaracteristica(Caracteristica* c) {
    if((forca-c->getForca()) >= 0){
        this->vetorCaracteristicas.push_back(c);
        forca-=c->getForca();
        this->custo += c->getMonetario();
        return true;
    }else{
        return false;
    }
}

bool Perfil::removeCarateristica(int id) {
    for(int i = 0; i < vetorCaracteristicas.size(); i++){
        if(vetorCaracteristicas[i]->getId() == id){
            vetorCaracteristicas.erase(vetorCaracteristicas.begin()+i);
            return true;
        }
    }
    return false;
}

int Perfil::getCusto() const {
    return this->custo;
}

void Perfil::listarTudo() {
    int ataque = 0, defesa = 0, velocidade = 0, saude = 10;
    cout << "   [Perfil: " << getNome() << "] [Custo: " << this->getCusto() << "]" << endl;
    for (int i = 0; i < vetorCaracteristicas.size(); i++) {
        cout << "       > " << this->vetorCaracteristicas[i]->getNome() << "." << endl;
        switch(vetorCaracteristicas[i]->getId()){
            case 2:
                saude+=1;
            break;
            case 3:
                defesa+=1;
            break;
            case 4:
                defesa+=2;
            break;
            case 5:
                ataque+=1;
            break;
            case 6:
                ataque+=3;
            break;
            case 9:
                velocidade+=1;
            break;
            case 10:
                velocidade+=1;
            break;
            case 11:
                velocidade+=1;
            break;
            case 12:
                saude=2;                
            break;
        }
    }
    cout << "   [Saude: " << saude << "] [Velocidade: " << velocidade << "]" << endl;
    cout << "   [Ataque: " << ataque << "] [Defesa: " << defesa << "]" << endl << endl;
}

string Perfil::getNome() const {
    return this->nome;
}

bool Perfil::temBandeira() {
    for(int i = 0; i < vetorCaracteristicas.size(); i++){
        if(vetorCaracteristicas[i]->getId() == 1){
            return true;
        }
    }
    return false;
}

bool Perfil::temRemedio() {
    for(int i = 0; i < vetorCaracteristicas.size(); i++){
        if(vetorCaracteristicas[i]->getId() == 12){
            return true;
        }
    }
    return false;
}

Caracteristica* Perfil::getCarateristica(int index) {
    if(index < vetorCaracteristicas.size()){
        return vetorCaracteristicas[index];
    }else{
        return NULL;
    }
}

int Perfil::getSizePerfil() const {
    return vetorCaracteristicas.size();
}

Perfil::~Perfil() {
    //delete(this);
}


