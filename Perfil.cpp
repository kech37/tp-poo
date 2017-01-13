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
}

Perfil& Perfil::operator=(Perfil p) {
    if(this != &p){
        this->custo = p.custo;
        this->forca = p.forca;
        this->nome = p.nome;
        this->vetorCaracteristicas = p.vetorCaracteristicas;
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
    cout << "Perfil: " <<  getNome() << ":" << endl;
    for(int i = 0; i < vetorCaracteristicas.size(); i++){
        cout << "-" << this->vetorCaracteristicas[i]->getNome() << endl;
    }
}

string Perfil::getNome() const {
    return this->nome;
}

Caracteristica* Perfil::getCarateristica(int index) {
    return vetorCaracteristicas[index];
}

int Perfil::getSizePerfil() const {
    return vetorCaracteristicas.size();
}

Perfil::~Perfil() {
    //delete(this);
}


