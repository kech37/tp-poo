/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Quinta.h
 * Author: carlo
 *
 * Created on 12 de Janeiro de 2017, 19:57
 */

#ifndef QUINTA_H
#define QUINTA_H

#include "Edificios.h"

class Quinta : public Edificios {
private:
public:
    Quinta(int linha, int coluna, int equipa);
    Quinta(const Quinta &q);
    int getMoedasProduzidas();
    int getTipo() const override;
    virtual ~Quinta();
};

#endif /* QUINTA_H */

