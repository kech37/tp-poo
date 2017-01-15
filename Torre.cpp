/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Torre.cpp
 * Author: carlo
 * 
 * Created on 12 de Janeiro de 2017, 18:49
 */

#include "Torre.h"

Torre::Torre(int linha, int coluna, int equipa) : Edificios("T", 30, 20, 10, linha, coluna, equipa) {
    this->ataque = 3;
    this->tipo = this->TORRE;
}

Torre::Torre(const Torre& t) : Torre(t.getLinha(), t.getColuna(), t.getEquipa()) {
}

int Torre::getAtaque() const {
    return ataque;
}


int Torre::getTipo() const {
    return this->tipo;
}

Torre::~Torre() {

}

