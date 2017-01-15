/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Castelo.cpp
 * Author: carlo
 * 
 * Created on 29 de Dezembro de 2016, 10:57
 */

#include "Castelo.h"

Castelo::Castelo(int linha, int coluna, int equipa) : Edificios("C", 0, 50, 10, linha, coluna, equipa) {
    this->tipo = this->CASTELO;
}

int Castelo::getTipo() const {
    return this->tipo;
}

Castelo::~Castelo() {
}

