/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Torre.h
 * Author: carlo
 *
 * Created on 12 de Janeiro de 2017, 18:49
 */

#ifndef TORRE_H
#define TORRE_H

#include "Edificios.h"

class Torre : public Edificios {
private:
public:
    Torre(int linha, int coluna, int equipa);
    Torre(const Torre &t);
    int getAtaque() const;
    int getTipo() const override;
    virtual ~Torre();
};

#endif /* TORRE_H */

