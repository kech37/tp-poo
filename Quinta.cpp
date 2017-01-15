/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Quinta.cpp
 * Author: carlo
 * 
 * Created on 12 de Janeiro de 2017, 19:57
 */

#include "Quinta.h"

#include <iostream>

Quinta::Quinta(int linha, int coluna, int equipa) : Edificios("Q", 20, 20, 10, linha, coluna, equipa) {
    moedasProduzitas = 2;
    tipo = QUINTA;
}

Quinta::Quinta(const Quinta& q) : Quinta(q.getLinha(), q.getColuna(), q.getEquipa()) {
}

int Quinta::getMoedasProduzidas(){
    return moedasProduzitas;
}

int Quinta::getTipo() const {
    return tipo;
}

Quinta::~Quinta() {

}
