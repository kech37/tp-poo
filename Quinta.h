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


class Quinta:public Edificios{
private:
    int moedasProduzitas;
public:
    Quinta(int linha, int coluna, int equipa);
    int getMoedasProduzidas() const;
    void upgradeNivel() override;
    virtual ~Quinta();
};

#endif /* QUINTA_H */

