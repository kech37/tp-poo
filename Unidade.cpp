/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Unidade.cpp
 * Author: carlo
 * 
 * Created on 30 de Dezembro de 2016, 0:16
 */

#include "Unidade.h"

Unidade::Unidade(int linha, int coluna, int equipa) {
    this->linha = linha;
    this->coluna = coluna;
    this->equipa = equipa;
}

int Unidade::getEquipa() const {
    return this->equipa;
}

int Unidade::getColuna() const {
    return this->coluna;
}

int Unidade::getLinha() const {
    return this->linha;
}

void Unidade::setColuna(int coluna) {
    this->coluna = coluna;
}

void Unidade::setLinha(int linha) {
    this->linha = linha;
}

void Unidade::setLinhaColuna(int linha, int coluna) {
    this->linha = linha;
    this->coluna = coluna;
}

bool Unidade::checkPosicao(int linha, int coluna) {
    if(this->linha == linha && this->coluna == coluna){
        return true;
    }else{
        return false;
    }
}

int Unidade::getUnidade() const {
    return tipoUnidade;
}

Unidade::~Unidade() {

}




