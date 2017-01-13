/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ser.h
 * Author: carlo
 *
 * Created on 28 de Dezembro de 2016, 18:29
 */

#ifndef SER_H
#define SER_H

#include "Perfil.h"
#include "Unidade.h"

class Ser:public Unidade{
private:
    static int conta;
    int id, saude, velocidade, ataque, defesa, saudeMAX, numEspada;
    bool secondChance, remedio, bandeira;
    Perfil* perfil;
public:
    Ser(Perfil* p, int linha, int coluna, int equipa);
    
    int getSaude() const;
    int getSaudeMAX() const;
    void setSaude(int saude);
    
    int getVelocidade() const;
    void setVelocidade(int velocidade);
    
    int getAtaque();
    void setAtaque(int ataque);
    
    int getNumEspada() const;
    void setNumEspada(int num);
    
    int getDefesa() const;
    void setDefesa(int defesa);
    
    Perfil* getPerfil() const;
    
    bool getRemedio() const;
    bool getSecondChance() const;
    bool getBandeira() const;
    
    void setRemedio(bool b);
    void setSecondChance(bool b);
    
    virtual int getID() const override;
    
    virtual string getNome() const override;

    virtual ~Ser() override;

};

#endif /* SER_H */

