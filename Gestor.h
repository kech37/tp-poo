/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Gestor.h
 * Author: carlo
 *
 * Created on 28 de Dezembro de 2016, 18:06
 */

#ifndef GESTOR_H
#define GESTOR_H

#include <sstream>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <fstream>

#include "Colonia.h"
#include "Controlador.h"


class Gestor {
private:
    Controlador* controlador;
    bool c_dim = false, c_moedas = false, c_oponentes = false, c_mkperfil = false, config = true;
    int focoLinhas, focoColunas;
public:
    static Gestor * getInstance();

    void start();

    void desenharMapa();

    bool intrepertaComandos(string comando);
    vector<string> separaComando(string comando, char separador);

    bool comando_dim(int linhas, int colunas);
    void comando_moedas(int num);
    
    /*
     *  true  -> Oponentes Criados com sucesso
     *  false -> nao ha espaco
     */
    bool comando_oponentes(int num);
    
    /*
     * -1 -> Nao encontro a colonia
     *  0 -> Ponto nao esta vazio
     *  1 -> Castelo movido com sucesso
     */
    int comando_castelo(string nome, int linha, int coluna);
    
    /*
     * -2 -> Nao foi encontrada a colonia
     * -1 -> Ja tem 5 perfils
     *  0 -> Ja existe perfil com esse nome
     *  1 -> Perfil criado com sucesso
     */
    int comando_mkperfil(string co, string letra);
    
    /*
     * -2 -> Nao foi encontrada a colonoa.
     * -1 -> Não foi encontrado o perfil
     *  0 -> Nao consegue adicionar mais caracteristicas
     *  1 -> Caracteristica adiciona com sucesso
     */
    int comando_addperfil(string co, string ca, int id);
    
    /*
     * -2 -> Nao foi encontrada a colonoa.
     * -1 -> Não foi encontrado o perfil
     *  0 -> Nao foi encontrada a caracteristica
     *  1 -> Caracteristica removida com sucesso
     */
    int comando_subperfil(string co, string ca, int id);
    
    /*
     * -1 -> Não foi encontrado o Colonia
     *  0 -> Nao foi encontrada o perfil
     *  1 -> Perfil removido com sucesso
     */
    int comando_rmperfil(string co, string ca);
    
    bool comando_load(string ficheiro);
    void comando_inicio();
    
    bool comando_ataca_recolhe(string co, bool b);
    
    /*
     * -3 -> Edificio nao existente
     * -2 -> Não foi encontrada a colonia
     * -1 -> Colonia nao tem dinheiro
     *  0 -> Não está no perimetro do castelo ou posicao já ocupada
     *  1 -> Edificio criado com sucesso
     */
    int comando_build(string co, string edif, int linha, int coluna);
    
    /*
     * -3 -> Edificio destroido
     * -1 -> Não foi encontrado o Colonia
     *  0 -> Nao foi encontrada o edificio
     *  1 -> repair foi feito com sucesso
     */
    int comando_repair(string co, int id);
    
    /*
     * -2 -> Nao ha dinheiro
     * -1 -> Não foi encontrado o Colonia
     *  0 -> Nao foi encontrada o edificio
     *  1 -> repair foi feito com sucesso
     */
    int comando_upgrade(string co, int id);
    
    /*
     * -1 -> Não foi encontrado o Colonia
     *  0 -> Nao foi encontrada o edificio
     *  1 -> repair foi feito com sucesso
     */
    int comando_sell(string co, int id);
    
    /*
     * -2 -> Nao ha dinheiro
     * -1 -> Não foi encontrado o Colonia
     *  0 -> Nao foi encontrada o Perfil
     *  1 -> Comando foi feito com sucesso
     */
    int comando_ser(string co, int num, string perf);
    
    void comando_foco(int linhas, int colunas);
    
    bool comando_listp(string perfil);
    
    bool isConfig();

    bool checkNumero(const string s);

    void imprimeErro(string msg);
    void imprimeLog(string msg);
    void imprimePedidoInfo(string msg);
    void imprimeLogo();
    
    virtual ~Gestor();

};

#endif /* GESTOR_H */

