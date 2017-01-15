/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Unidade.h
 * Author: carlo
 *
 * Created on 30 de Dezembro de 2016, 0:16
 */

#ifndef UNIDADE_H
#define UNIDADE_H

#include <string>

using namespace std;

class Unidade {
private:
    int linha, coluna, equipa;
protected:
    int tipoUnidade;
public:
    const static int SER = 0;
    const static int EDIFICO = 1;
    /*
     * Construtor de unidade, que necessita de uma linha e de uma coluna
     */
    Unidade(int linha, int coluna, int equipa);
    
    int getEquipa() const;
    
    /*
     * Retorna Linha da Unidade
     */
    int getLinha() const;
    
    /*
     * Retorna Coluna da Unidade
     */
    int getColuna() const;
    
    /*
     * Muda Linha da Unidade
     */
    void setLinha(int linha);  
    
    /*
     * Muda coluna da Unidade
     */
    void setColuna(int coluna);
    
    /*
     * Muda linha e coluna da Unidade
     */
    void setLinhaColuna(int linha, int coluna);
    
    /*
     * Retorna se e a sua posicao ou nao, dependente dos argumentos.
     * Se os argumentos forem a posicao da unidade, retorna true
     */
    bool checkPosicao(int linha, int coluna);
    
    int getUnidade() const;
    
    /*
     * Funcao Virtual getNome. Deve ser implementada nas classes derivadas
     */
    virtual string getNome() const = 0;
    
    /*
     * Funcao Virtual GetID. Deve ser implementada nas classes derivadas
     */
    virtual int getID() const = 0;
    
    virtual ~Unidade();

};

#endif /* UNIDADE_H */

