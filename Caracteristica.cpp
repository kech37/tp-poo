/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Caracteristica.cpp
 * Author: carlo
 * 
 * Created on 28 de Dezembro de 2016, 17:53
 */

#include "Caracteristica.h"

Caracteristica::Caracteristica(int id) {
    switch(id){
        case 1:
            this->id = 1;
            this->nome = "Bandeira";
            this->monetario = 1;
            this->forca = 0;
        break;
        case 2:
            this->id = 2;
            this->nome = "Superior";
            this->monetario = 1;
            this->forca = 1;
        break;
        case 3:
            this->id = 3;
            this->nome = "Pele Dura";
            this->monetario = 2;
            this->forca = 2;
        break;
        case 4:
            this->id = 4;
            this->nome = "Armadura";
            this->monetario = 2;
            this->forca = 3;
        break;
        case 5:
            this->id = 5;
            this->nome = "Faca";
            this->monetario = 1;
            this->forca = 1;
        break;
        case 6:
            this->id = 6;
            this->nome = "Espada";
            this->monetario = 2;
            this->forca = 2;
        break;
        case 7:
            this->id = 7;
            this->nome = "Agressao";
            this->monetario = 1;
            this->forca = 1;
        break;
        case 8:
            this->id = 8;
            this->nome = "Ecologico";
            this->monetario = 1;
            this->forca = 1;
        break;
        case 9:
            this->id = 1;
            this->nome = "HeatSeeker";
            this->monetario = 1;
            this->forca = 1;
        break;
        case 10:
            this->id = 10;
            this->nome = "BuildSeeker";
            this->monetario = 1;
            this->forca = 1;
        break;
        case 11:
            this->id = 11;
            this->nome = "Walker";
            this->monetario = 1;
            this->forca = 1;
        break;
        case 12:
            this->id = 12;
            this->nome = "Remedio";
            this->monetario = 2;
            this->forca = 1;
        break;
        case 13:
            this->id = 13;
            this->nome = "SecondChance";
            this->monetario = 3;
            this->forca = 0;
        break;
        case 14:
            this->id = 14;
            this->nome = "Aluno";
            this->monetario = 5;
            this->forca = 3;
        break;
    }
}

int Caracteristica::getId() const {
    return this->id;
}

string Caracteristica::getNome() const {
    return this->nome;
}

int Caracteristica::getForca() const {
    return this->forca;
}

int Caracteristica::getMonetario() const {
    return this->monetario;
}

Caracteristica::~Caracteristica() {
}


