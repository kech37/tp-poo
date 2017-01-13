/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Edificios.cpp
 * Author: carlo
 * 
 * Created on 29 de Dezembro de 2016, 10:51
 */

#include "Edificios.h"

#include <iostream>

int Edificios::conta = 0;

Edificios::Edificios(string nome, int custo, int saude, int defesa, int linha, int coluna, int equipa):Unidade(linha, coluna, equipa) {
    this->nome = nome;
    this->custo = custo;
    this->saudeMAX = saude;
    this->saude = saudeMAX;
    this->defesa = defesa;
    this->id = conta;
    this->conta++;
    this->nivel = 0;
}

int Edificios::getSaude() const {
    return this->saude;
}

int Edificios::getDefesa() const {
    return this->defesa;
}

int Edificios::getSaudeMAX() const {
    return this->saudeMAX;
}

int Edificios::getCusto() const {
    return this->custo;
}

int Edificios::getNivel() const {
    return this->nivel;
}

void Edificios::setSaude(int saude) {
    this->saude = saude;
}

void Edificios::setDefesa(int defesa) {
    this->defesa = defesa;
}

void Edificios::setCusto(int custo) {
    this->custo = custo;
}

int Edificios::getID() const {
    return this->id;
}

string Edificios::getNome() const {
    return this->nome;
}

void Edificios::upgradeNivel() {

}

Edificios::~Edificios() {
    
}



