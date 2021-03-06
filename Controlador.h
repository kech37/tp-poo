/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Controlador.h
 * Author: carlo
 *
 * Created on 30 de Dezembro de 2016, 15:24
 */

#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include "Colonia.h"
#include "Castelo.h"
#include <stdlib.h>
#include <time.h>


class Controlador {
private:
    vector<Colonia> vectorColonias;
    int moedasDefault;
    int linhasDefault, colunasDefault;
    string name;
    string nomes[26] = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
public:
    
    bool c_dim, c_moedas, c_oponentes, c_mkperfil, config;
    
    const static int QUALQUER = 0;
    const static int EDIFICIO = 1;
    const static int SER = 2;
    const static int ATACA = 1;
    const static int RECOLHE = 2;
    
    Controlador(string name);
    Controlador();
    
    void setName(string name);
    string getName() const;
    
    void setLinhasDefault(int linhas);
    int getLinhasDefault() const;
    void setColunasDefault(int colunas);
    int getColunasDefault() const;
    void setMoedasDefault(int moedas);
    
    int getRandomLinhas();
    int getRandomColunas();
    
    void apagarVectorColonias();
    bool addColonia();
    Colonia* getColonia(string nome);
    vector<Colonia>* getVectorColonia();

    bool addEdificio(Colonia* colonia, Edificios edificio);
    
    Unidade* getUnidade(Colonia* colonia, int id, int tipo);
    Ser* getSer(int linha, int coluna);
    bool removeSer(int id);
    Edificios* getEdifico(int linha, int coluna);
    bool removeEdificio(int id);
    
    bool removeColonia(int id);
    
    Unidade* verificaPosicao(int linha, int coluna);
    bool verificaMovimento(int linha, int coluna, int flag, int equipa = -1);
    
    void movimentoRandom(Ser* ser);
    
    void atribuirPerfil();
    
    bool next();
    
    string toLower(string str);
    string toUpper(string str);
    
    void listarTudo();

};

#endif /* CONTROLADOR_H */

