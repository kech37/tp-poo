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


class Torre:public Edificios{
private:
    int ataque;
public:
    Torre(int linha, int coluna, int equipa);
    
    int getAtaque() const;
    
    void upgradeNivel() override;
    virtual ~Torre();
};

#endif /* TORRE_H */

