/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ser.cpp
 * Author: carlo
 * 
 * Created on 28 de Dezembro de 2016, 18:29
 */

#include "Ser.h"

#include <iostream>

int Ser::conta = 500;

Ser::Ser(Perfil* p, int linha, int coluna, int equipa):Unidade(linha, coluna, equipa) {
    int i = 0;
    Caracteristica* c;
    
    this->perfil = p;
    this->saudeMAX = 10;
    this->defesa = 0;
    this->ataque = 0;
    this->numEspada = -1;
    this->id = conta;
    this->conta++;
    this->secondChance = false;
    this->remedio = false;
    this->bandeira = false;
    
    c = this->perfil->getCarateristica(i);
    while(c != NULL){
        switch(c->getId()){
            case 1:
                this->bandeira = true;
            break;
            case 2:
                this->saudeMAX+=1;
            break;
            case 3:
                this->defesa+=1;
            break;
            case 4:
                this->defesa+=2;
            break;
            case 5:
                this->ataque+=1;
            break;
            case 6:
                this->numEspada = 2;
                this->ataque+=2;
            break;
            case 12:
                this->remedio = true;
                break;
            case 13:
                this->secondChance = true;
                break;
        }
        i++;
        c = this->perfil->getCarateristica(i);
    }
    this->saude = this->saudeMAX;
    tipoUnidade = Unidade::SER;
}

int Ser::getAtaque() {
    if(this->numEspada > 0){
        this->numEspada--;
        return this->ataque+1;
    }else{
        return this->ataque;
    }
}

int Ser::getNumEspada() const {
    return this->numEspada;
}

int Ser::getDefesa() const {
    return this->defesa;
}

int Ser::getSaude() const {
    return this->saude;
}

int Ser::getSaudeMAX() const{
    return this->saudeMAX;
}

int Ser::getVelocidade() const {
    return this->velocidade;
}

void Ser::setAtaque(int ataque) {
    this->ataque = ataque;
}

void Ser::setNumEspada(int num) {
    this->numEspada = num;
}

void Ser::setDefesa(int defesa) {
    this->defesa = defesa;
}

void Ser::setSaude(int saude) {
    this->saude = saude;
}

void Ser::setVelocidade(int velocidade) {
    this->velocidade = velocidade;
}

Perfil* Ser::getPerfil() const {
    return this->perfil;
}

int Ser::getID() const {
    return this->id;
}

string Ser::getNome() const {
    return this->perfil->getNome();
}

bool Ser::getRemedio() const {
    return this->remedio;
}

bool Ser::getSecondChance() const {
    return this->secondChance;
}

bool Ser::getBandeira() const {
    return this->bandeira;
}

void Ser::setRemedio(bool b) {
    this->remedio = b;
}

void Ser::setSecondChance(bool b) {
    this->secondChance = b;
}

Ser::~Ser() {

}

