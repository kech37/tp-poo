/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Castelo.h
 * Author: carlo
 *
 * Created on 29 de Dezembro de 2016, 10:57
 */

#ifndef CASTELO_H
#define CASTELO_H

#include "Edificios.h"

class Castelo : public Edificios {
private:
public:
    Castelo(int linha, int coluna, int equipa);
    int getTipo() const override;
    virtual ~Castelo();
};

#endif /* CASTELO_H */

