/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Controlador.cpp
 * Author: carlo
 * 
 * Created on 30 de Dezembro de 2016, 15:24
 */

#include <numeric>
#include <algorithm>

#include "Controlador.h"
#include "Consola.h"
#include "Torre.h"

Controlador::Controlador() {
    this->moedasDefault = 0;
    this->colunasDefault = 0;
    this->linhasDefault = 0;
    srand(time(NULL));
}

void Controlador::setLinhasDefault(int linhas) {
    this->linhasDefault = linhas;
}

int Controlador::getLinhasDefault() const {
    return this->linhasDefault;
}

void Controlador::setColunasDefault(int colunas) {
    this->colunasDefault = colunas;
}

int Controlador::getColunasDefault() const {
    return this->colunasDefault;
}

void Controlador::setMoedasDefault(int moedas) {
    this->moedasDefault = moedas;
}

int Controlador::getRandomColunas() {
    return (rand() % colunasDefault);
}

int Controlador::getRandomLinhas() {
    return (rand() % linhasDefault);
}

bool Controlador::addColonia() {
    Colonia* c;
    int i = -1;
    int linha, coluna;
    do {
        i++;
        c = getColonia(this->nomes[i]);
    } while (c != NULL && i < 26);
    if (i < 26) {
        vectorColonias.push_back(Colonia(this->nomes[i], this->moedasDefault));
        c = &vectorColonias.back();
        do {
            linha = getRandomLinhas();
            coluna = getRandomColunas();
        } while (verificaPosicao(linha, coluna) != NULL);
        c->getVectorEdificios()->push_back(Castelo(linha, coluna, c->getID()));
        return true;
    } else {
        return false;
    }
}

Colonia* Controlador::getColonia(string nome) {
    for (int i = 0; i < vectorColonias.size(); i++) {
        if (vectorColonias[i].getNome() == nome) {
            return &vectorColonias[i];
        }
    }
    return NULL;
}

vector<Colonia>* Controlador::getVectorColonia() {
    return &vectorColonias;
}

void Controlador::apagarVectorColonias() {
    vectorColonias.clear();
}

Unidade* Controlador::verificaPosicao(int linha, int coluna) {
    if (linha < this->linhasDefault && coluna < this->colunasDefault) {
        for (int i = 0; i < vectorColonias.size(); i++) {
            for (int j = 0; j < vectorColonias[i].getVectorEdificios()->size(); j++) {
                if (vectorColonias[i].getVectorEdificios()->at(j).checkPosicao(linha, coluna)) {
                    return &vectorColonias[i].getVectorEdificios()->at(j);
                }
            }
            for (int j = 0; j < vectorColonias[i].getVectorSer()->size(); j++) {
                if (vectorColonias[i].getVectorSer()->at(j).checkPosicao(linha, coluna)) {
                    return &vectorColonias[i].getVectorSer()->at(j);
                }
            }
        }
    }
    return NULL;
}

Unidade* Controlador::getUnidade(Colonia* colonia, int id, int tipo) {
    switch (tipo) {
        case EDIFICIO:
            for (int i = 0; i < colonia->getVectorEdificios()->size(); i++) {
                if (colonia->getVectorEdificios()->at(i).getID() == id) {
                    return &colonia->getVectorEdificios()->at(i);
                }
            }
            break;
        case SER:
            for (int i = 0; i < colonia->getVectorSer()->size(); i++) {
                if (colonia->getVectorSer()->at(i).getID() == id) {
                    return &colonia->getVectorSer()->at(i);
                }
            }
            break;
    }
    return NULL;
}

bool Controlador::addEdificio(Colonia* colonia, Edificios edificio) {
    if (colonia->addEdificio(edificio)) {
        return true;
    } else {
        return false;
    }
}

Ser* Controlador::getSer(int linha, int coluna) {
    for (int i = 0; i < vectorColonias.size(); i++) {
        for (int j = 0; j < vectorColonias[i].getVectorSer()->size(); j++) {
            if (vectorColonias[i].getVectorSer()->at(j).checkPosicao(linha, coluna)) {
                return &vectorColonias[i].getVectorSer()->at(j);
            }
        }
    }
    return NULL;
}

Edificios* Controlador::getEdifico(int linha, int coluna) {
    for (int i = 0; i < vectorColonias.size(); i++) {
        for (int j = 0; j < vectorColonias[i].getVectorEdificios()->size(); j++) {
            if (vectorColonias[i].getVectorEdificios()->at(j).checkPosicao(linha, coluna)) {
                return &vectorColonias[i].getVectorEdificios()->at(j);
            }
        }
    }
    return NULL;
}

void Controlador::atribuirPerfil() {
    vector<int> v(4);
    iota(v.begin(), v.end(), 0);
    int tamA = getColonia("A")->getVectorPerfil()->size(), resp, car, nom;
    for (int i = 1; i < vectorColonias.size(); i++) {
        if (tamA > 3) {
            random_shuffle(v.begin(), v.end());
            for (int j = 0; j < 5; j++) {
                if (j < 3) {
                    vectorColonias[i].getVectorPerfil()->push_back(Perfil(vectorColonias[0].getVectorPerfil()->at(v[j])));
                } else {
                    do {
                        nom = rand() % 26;
                        resp = vectorColonias[i].addPerfil(toLower(nomes[nom]));
                    } while (resp != 1);
                    do {
                        car = rand() % 14 + 1;
                    } while (vectorColonias[i].getPerfil(toLower(nomes[nom]))->addCaracteristica(new Caracteristica(car)));
                }
            }
        } else {
            for (int j = 0; j < 5; j++) {
                if (j < tamA) {
                    vectorColonias[i].getVectorPerfil()->push_back(Perfil(vectorColonias[0].getVectorPerfil()->at(j)));
                } else {
                    do {
                        nom = rand() % 26;
                        resp = vectorColonias[i].addPerfil(toLower(nomes[nom]));
                    } while (resp != 1);
                    do {
                        car = rand() % 14 + 1;
                    } while (vectorColonias[i].getPerfil(toLower(nomes[nom]))->addCaracteristica(new Caracteristica(car)));
                }
            }
        }
    }
}

void Controlador::listarTudo() {
    for (int i = 0; i < vectorColonias.size(); i++) {
        vectorColonias[i].listar();
    }
}

bool Controlador::removeSer(int id) {
    for (int i = 0; i < vectorColonias.size(); i++) {
        for (int j = 0; j < vectorColonias[i].getVectorSer()->size(); j++) {
            if (vectorColonias[i].getVectorSer()->at(j).getID() == id) {
                vectorColonias[i].getVectorSer()->erase(vectorColonias[i].getVectorSer()->begin() + j);
                return true;
            }
        }
    }
    return false;
}

bool Controlador::removeEdificio(int id) {
    for (int i = 0; i < vectorColonias.size(); i++) {
        for (int j = 0; j < vectorColonias[i].getVectorEdificios()->size(); j++) {
            if (vectorColonias[i].getVectorEdificios()->at(j).getID() == id) {
                vectorColonias[i].getVectorEdificios()->erase(vectorColonias[i].getVectorEdificios()->begin() + j);
                return true;
            }
        }
    }
    return false;
}

bool Controlador::next() {
    for (int i = 0; i < vectorColonias.size(); i++) {
        for (int j = 0; j < vectorColonias[i].getVectorSer()->size(); j++) {
            Ser* ser = &vectorColonias[i].getVectorSer()->at(j);
            if (vectorColonias[i].getFlagAvancar()) {
                int index_car = 0;
                Caracteristica* car = ser->getPerfil()->getCarateristica(index_car);
                while (car != NULL) {
                    switch (car->getId()) {
                        case 7: //Agressão
                            if (ser->getBandeira()) {
                                Ser * serAtacar[8];
                                serAtacar[0] = this->getSer(ser->getLinha() - 1, ser->getColuna() - 1);
                                serAtacar[1] = this->getSer(ser->getLinha(), ser->getColuna() - 1);
                                serAtacar[2] = this->getSer(ser->getLinha() + 1, ser->getColuna() - 1);
                                serAtacar[3] = this->getSer(ser->getLinha() + 1, ser->getColuna());
                                serAtacar[4] = this->getSer(ser->getLinha() + 1, ser->getColuna() + 1);
                                serAtacar[5] = this->getSer(ser->getLinha(), ser->getColuna() + 1);
                                serAtacar[6] = this->getSer(ser->getLinha() - 1, ser->getColuna() + 1);
                                serAtacar[7] = this->getSer(ser->getLinha() - 1, ser->getColuna());
                                for (int k = 0; k < 8; k++) {
                                    if (serAtacar[k] != NULL) {
                                        if (serAtacar[k]->getBandeira() == true && serAtacar[k]->getEquipa() != ser->getEquipa() || serAtacar[k]->getBandeira() == false) {
                                            cout << "SER: vou atacar um ser -> " << serAtacar[k]->getID() << endl;
                                            if (ser->getAtaque() > serAtacar[k]->getDefesa()) {
                                                serAtacar[k]->setSaude(serAtacar[k]->getSaude()-(ser->getAtaque() - serAtacar[k]->getDefesa()));
                                            } else {
                                                serAtacar[k]->setSaude(serAtacar[k]->getSaude() - 1);
                                            }
                                            if (serAtacar[k]->getSaude() <= 0) {
                                                if (serAtacar[k]->getSecondChance() == true) {
                                                    serAtacar[k]->setSecondChance(false);
                                                    serAtacar[k]->setSaude(serAtacar[k]->getSaudeMAX());
                                                    serAtacar[k]->setLinhaColuna(vectorColonias[i].getCastelo()->getLinha(), vectorColonias[i].getCastelo()->getColuna());
                                                } else {
                                                    this->removeSer(serAtacar[k]->getID());
                                                }
                                            }
                                            k = 8;
                                        }
                                    }
                                }
                            }
                            break;
                        case 8: //Ecologico
                            if (ser->getBandeira()) {
                                Edificios * ediAtacar[8];
                                ediAtacar[0] = this->getEdifico(ser->getLinha() - 1, ser->getColuna() - 1);
                                ediAtacar[1] = this->getEdifico(ser->getLinha(), ser->getColuna() - 1);
                                ediAtacar[2] = this->getEdifico(ser->getLinha() + 1, ser->getColuna() - 1);
                                ediAtacar[3] = this->getEdifico(ser->getLinha() + 1, ser->getColuna());
                                ediAtacar[4] = this->getEdifico(ser->getLinha() + 1, ser->getColuna() + 1);
                                ediAtacar[5] = this->getEdifico(ser->getLinha(), ser->getColuna() + 1);
                                ediAtacar[6] = this->getEdifico(ser->getLinha() - 1, ser->getColuna() + 1);
                                ediAtacar[7] = this->getEdifico(ser->getLinha() - 1, ser->getColuna());
                                for (int k = 0; k < 8; k++) {
                                    if (ediAtacar[k] != NULL && ediAtacar[k]->getEquipa() != ser->getEquipa()) {
                                        cout << "SER: vou atacar um edificio -> " << ediAtacar[k]->getID() << endl;
                                        if (ser->getAtaque() > ediAtacar[k]->getDefesa()) {
                                            ediAtacar[k]->setSaude(ediAtacar[k]->getSaude()-(ser->getAtaque() - ediAtacar[k]->getDefesa()));
                                        } else {
                                            ediAtacar[k]->setSaude(ediAtacar[k]->getSaude() - 1);
                                        }
                                        if (ediAtacar[k]->getSaude() <= 0) {
                                            /*if (ediAtacar[k]->getNome() == "C") {
                                                this->removeColonia(ediAtacar[k]->getEquipa());
                                            } else {
                                                this->removeEdificio(ediAtacar[k]->getID());
                                            }*/
                                            this->removeEdificio(ediAtacar[k]->getID());
                                        }
                                        k = 8;
                                    }
                                }
                            }
                            break;
                        case 9: //HeatSeeker
                            Ser* perto;
                            int s_l_p, s_c_p;
                            Ser* temp;
                            int s_l_t, s_c_t;
                            perto = NULL;
                            for (int l = ser->getLinha() - 10; l < ser->getLinha() + 10; l++) {
                                for (int c = ser->getColuna() - 20; c < ser->getColuna() + 20; c++) {
                                    temp = getSer(l, c);
                                    if (temp != NULL) {
                                        cout << "Heat: Encontrei um ser: " << temp->getID() << " -Eq: " << temp->getEquipa() << endl;
                                        if (temp->getEquipa() != ser->getEquipa()) {
                                            if (perto == NULL) {
                                                perto = temp;
                                                if (perto->getLinha() > ser->getLinha()) {
                                                    s_l_p = perto->getLinha() - ser->getLinha();
                                                } else {
                                                    s_l_p = ser->getLinha() - perto->getLinha();
                                                }
                                                if (perto->getColuna() > ser->getColuna()) {
                                                    s_c_p = perto->getColuna() - ser->getColuna();
                                                } else {
                                                    s_c_p = ser->getColuna() - perto->getColuna();
                                                }
                                            } else {
                                                if (temp->getLinha() > ser->getLinha()) {
                                                    s_l_t = temp->getLinha() - ser->getLinha();
                                                } else {
                                                    s_l_t = ser->getLinha() - temp->getLinha();
                                                }
                                                if (temp->getColuna() > ser->getColuna()) {
                                                    s_c_t = temp->getColuna() - ser->getColuna();
                                                } else {
                                                    s_c_t = ser->getColuna() - temp->getColuna();
                                                }
                                                if (s_c_t < s_c_p && s_l_t < s_l_p) {
                                                    s_c_p = s_c_t;
                                                    s_l_p = s_l_t;
                                                    perto = temp;
                                                }
                                            }
                                            
                                        cout << "Ser mais perto: " << perto->getID() << " -Eq: " << perto->getEquipa() << endl;
                                        }
                                    }
                                }
                            }
                            if (perto != NULL) {
                                cout << "SER HEAT: Detetei um ser -> " << perto->getID() << endl;
                                if (ser->getLinha() < perto->getLinha() && ser->getColuna() < perto->getColuna()) {
                                    if (verificaMovimento(ser->getLinha() + 1, ser->getColuna() + 1, ATACA)) {
                                        ser->setLinhaColuna(ser->getLinha() + 1, ser->getColuna() + 1);
                                    } else {
                                        movimentoRandom(ser);
                                    }
                                } else if (ser->getLinha() < perto->getLinha() && ser->getColuna() > perto->getColuna()) {
                                    if (verificaMovimento(ser->getLinha() + 1, ser->getColuna() - 1, ATACA)) {
                                        ser->setLinhaColuna(ser->getLinha() + 1, ser->getColuna() - 1);
                                    } else {
                                        movimentoRandom(ser);
                                    }
                                } else if (ser->getLinha() > perto->getLinha() && ser->getColuna() > perto->getColuna()) {
                                    if (verificaMovimento(ser->getLinha() - 1, ser->getColuna() - 1, ATACA)) {
                                        ser->setLinhaColuna(ser->getLinha() - 1, ser->getColuna() - 1);
                                    } else {
                                        movimentoRandom(ser);
                                    }
                                } else if (ser->getLinha() > perto->getLinha() && ser->getColuna() < perto->getColuna()) {
                                    if (verificaMovimento(ser->getLinha() - 1, ser->getColuna() + 1, ATACA)) {
                                        ser->setLinhaColuna(ser->getLinha() - 1, ser->getColuna() + 1);
                                    } else {
                                        movimentoRandom(ser);
                                    }
                                } else if (ser->getLinha() == perto->getLinha() && ser->getColuna() < perto->getColuna()) {
                                    if (verificaMovimento(ser->getLinha(), ser->getColuna() + 1, ATACA)) {
                                        ser->setLinhaColuna(ser->getLinha(), ser->getColuna() + 1);
                                    } else {
                                        movimentoRandom(ser);
                                    }
                                } else if (ser->getLinha() == perto->getLinha() && ser->getColuna() > perto->getColuna()) {
                                    if (verificaMovimento(ser->getLinha(), ser->getColuna() - 1, ATACA)) {
                                        ser->setLinhaColuna(ser->getLinha(), ser->getColuna() - 1);
                                    } else {
                                        movimentoRandom(ser);
                                    }
                                } else if (ser->getLinha() < perto->getLinha() && ser->getColuna() == perto->getColuna()) {
                                    if (verificaMovimento(ser->getLinha() + 1, ser->getColuna(), ATACA)) {
                                        ser->setLinhaColuna(ser->getLinha() + 1, ser->getColuna());
                                    } else {
                                        movimentoRandom(ser);
                                    }
                                } else if (ser->getLinha() > perto->getLinha() && ser->getColuna() == perto->getColuna()) {
                                    if (verificaMovimento(ser->getLinha() - 1, ser->getColuna(), ATACA)) {
                                        ser->setLinhaColuna(ser->getLinha() - 1, ser->getColuna());
                                    } else {
                                        movimentoRandom(ser);
                                    }
                                }
                            }
                            break;
                        case 10: //BuildSeeker
                            Edificios* ep;
                            int l_p, c_p;
                            Edificios* tp;
                            int l_t, c_t;
                            ep = NULL;
                            for (int l = ser->getLinha() - 10; l < ser->getLinha() + 10; l++) {
                                for (int c = ser->getColuna() - 20; c < ser->getColuna() + 20; c++) {
                                    tp = getEdifico(l, c);
                                    if (tp != NULL) {
                                        if (tp->getEquipa() != ser->getEquipa()) {
                                            if (ep == NULL) {
                                                ep = tp;
                                                if (ep->getLinha() > ser->getLinha()) {
                                                    l_p = ep->getLinha() - ser->getLinha();
                                                } else {
                                                    l_p = ser->getLinha() - ep->getLinha();
                                                }
                                                if (ep->getColuna() > ser->getColuna()) {
                                                    c_p = ep->getColuna() - ser->getColuna();
                                                } else {
                                                    c_p = ser->getColuna() - ep->getColuna();
                                                }
                                            } else {
                                                if (tp->getLinha() > ser->getLinha()) {
                                                    l_t = tp->getLinha() - ser->getLinha();
                                                } else {
                                                    l_t = ser->getLinha() - tp->getLinha();
                                                }
                                                if (tp->getColuna() > ser->getColuna()) {
                                                    c_t = tp->getColuna() - ser->getColuna();
                                                } else {
                                                    c_t = ser->getColuna() - tp->getColuna();
                                                }
                                                if (c_t < c_p && l_t < l_p) {
                                                    c_p = c_t;
                                                    l_p = l_t;
                                                    ep = tp;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            if (ep != NULL) {
                                cout << "SER: Detetei um edificio -> " << ep->getID() << endl;
                                if (ser->getLinha() < ep->getLinha() && ser->getColuna() < ep->getColuna()) {
                                    if (verificaMovimento(ser->getLinha() + 1, ser->getColuna() + 1, ATACA)) {
                                        ser->setLinhaColuna(ser->getLinha() + 1, ser->getColuna() + 1);
                                    }
                                } else if (ser->getLinha() < ep->getLinha() && ser->getColuna() > ep->getColuna()) {
                                    if (verificaMovimento(ser->getLinha() + 1, ser->getColuna() - 1, ATACA)) {
                                        ser->setLinhaColuna(ser->getLinha() + 1, ser->getColuna() - 1);
                                    }
                                } else if (ser->getLinha() > ep->getLinha() && ser->getColuna() > ep->getColuna()) {
                                    if (verificaMovimento(ser->getLinha() - 1, ser->getColuna() - 1, ATACA)) {
                                        ser->setLinhaColuna(ser->getLinha() - 1, ser->getColuna() - 1);
                                    }
                                } else if (ser->getLinha() > ep->getLinha() && ser->getColuna() < ep->getColuna()) {
                                    if (verificaMovimento(ser->getLinha() - 1, ser->getColuna() + 1, ATACA)) {
                                        ser->setLinhaColuna(ser->getLinha() - 1, ser->getColuna() + 1);
                                    }
                                } else if (ser->getLinha() == ep->getLinha() && ser->getColuna() < ep->getColuna()) {
                                    if (verificaMovimento(ser->getLinha(), ser->getColuna() + 1, ATACA)) {
                                        ser->setLinhaColuna(ser->getLinha(), ser->getColuna() + 1);
                                    }
                                } else if (ser->getLinha() == ep->getLinha() && ser->getColuna() > ep->getColuna()) {
                                    if (verificaMovimento(ser->getLinha(), ser->getColuna() - 1, ATACA)) {
                                        ser->setLinhaColuna(ser->getLinha(), ser->getColuna() - 1);
                                    }
                                } else if (ser->getLinha() < ep->getLinha() && ser->getColuna() == ep->getColuna()) {
                                    if (verificaMovimento(ser->getLinha() + 1, ser->getColuna(), ATACA)) {
                                        ser->setLinhaColuna(ser->getLinha() + 1, ser->getColuna());
                                    }
                                } else if (ser->getLinha() > ep->getLinha() && ser->getColuna() == ep->getColuna()) {
                                    if (verificaMovimento(ser->getLinha() - 1, ser->getColuna(), ATACA)) {
                                        ser->setLinhaColuna(ser->getLinha() - 1, ser->getColuna());
                                    }
                                }
                            }
                            break;
                        case 11: //Walker
                            movimentoRandom(ser);
                            break;
                        case 12: //Remedio
                            if (ser->getSaude() > 0 && ser->getSaude() <= 3 && ser->getRemedio() == true) {
                                ser->setSaude(ser->getSaude() + 2);
                                ser->setRemedio(false);
                            }
                            break;
                        case 14: //Aluno

                            break;
                    }
                    index_car++;
                    car = ser->getPerfil()->getCarateristica(index_car);
                }
            } else {
                if (ser->getLinha() == vectorColonias[i].getCastelo()->getLinha() && ser->getColuna() == vectorColonias[i].getCastelo()->getColuna()) {
                    if (ser->getSaude() > 0 && ser->getSaude() < ser->getSaudeMAX()) {
                        ser->setSaude(ser->getSaude() + 1);
                    }
                    if (ser->getPerfil()->temRemedio()) {
                        ser->setRemedio(true);
                    }
                    if (ser->getNumEspada() != -1) {
                        ser->setNumEspada(2);
                    }
                } else {
                    if (ser->getLinha() < vectorColonias[i].getCastelo()->getLinha() && ser->getColuna() < vectorColonias[i].getCastelo()->getColuna()) {
                        if (verificaMovimento(ser->getLinha() + 1, ser->getColuna() + 1, RECOLHE, ser->getEquipa())) {
                            ser->setLinhaColuna(ser->getLinha() + 1, ser->getColuna() + 1);
                        } else {
                            movimentoRandom(ser);
                        }
                    } else if (ser->getLinha() < vectorColonias[i].getCastelo()->getLinha() && ser->getColuna() > vectorColonias[i].getCastelo()->getColuna()) {
                        if (verificaMovimento(ser->getLinha() + 1, ser->getColuna() - 1, RECOLHE, ser->getEquipa())) {
                            ser->setLinhaColuna(ser->getLinha() + 1, ser->getColuna() - 1);
                        } else {
                            movimentoRandom(ser);
                        }
                    } else if (ser->getLinha() > vectorColonias[i].getCastelo()->getLinha() && ser->getColuna() > vectorColonias[i].getCastelo()->getColuna()) {
                        if (verificaMovimento(ser->getLinha() - 1, ser->getColuna() - 1, RECOLHE, ser->getEquipa())) {
                            ser->setLinhaColuna(ser->getLinha() - 1, ser->getColuna() - 1);
                        } else {
                            movimentoRandom(ser);
                        }
                    } else if (ser->getLinha() > vectorColonias[i].getCastelo()->getLinha() && ser->getColuna() < vectorColonias[i].getCastelo()->getColuna()) {
                        if (verificaMovimento(ser->getLinha() - 1, ser->getColuna() + 1, RECOLHE, ser->getEquipa())) {
                            ser->setLinhaColuna(ser->getLinha() - 1, ser->getColuna() + 1);
                        } else {
                            movimentoRandom(ser);
                        }
                    } else if (ser->getLinha() == vectorColonias[i].getCastelo()->getLinha() && ser->getColuna() < vectorColonias[i].getCastelo()->getColuna()) {
                        if (verificaMovimento(ser->getLinha(), ser->getColuna() + 1, RECOLHE, ser->getEquipa())) {
                            ser->setLinhaColuna(ser->getLinha(), ser->getColuna() + 1);
                        } else {
                            movimentoRandom(ser);
                        }
                    } else if (ser->getLinha() == vectorColonias[i].getCastelo()->getLinha() && ser->getColuna() > vectorColonias[i].getCastelo()->getColuna()) {
                        if (verificaMovimento(ser->getLinha(), ser->getColuna() - 1, RECOLHE, ser->getEquipa())) {
                            ser->setLinhaColuna(ser->getLinha(), ser->getColuna() - 1);
                        } else {
                            movimentoRandom(ser);
                        }
                    } else if (ser->getLinha() < vectorColonias[i].getCastelo()->getLinha() && ser->getColuna() == vectorColonias[i].getCastelo()->getColuna()) {
                        if (verificaMovimento(ser->getLinha() + 1, ser->getColuna(), RECOLHE, ser->getEquipa())) {
                            ser->setLinhaColuna(ser->getLinha() + 1, ser->getColuna());
                        } else {
                            movimentoRandom(ser);
                        }
                    } else if (ser->getLinha() > vectorColonias[i].getCastelo()->getLinha() && ser->getColuna() == vectorColonias[i].getCastelo()->getColuna()) {
                        if (verificaMovimento(ser->getLinha() - 1, ser->getColuna(), RECOLHE, ser->getEquipa())) {
                            ser->setLinhaColuna(ser->getLinha() - 1, ser->getColuna());
                        } else {
                            movimentoRandom(ser);
                        }
                    }
                }
            }
        }
        for (int j = 0; j < vectorColonias[i].getVectorEdificios()->size(); j++) {
            switch (vectorColonias[i].getVectorEdificios()->at(j).getTipo()) {
                case Edificios::QUINTA:
                    vectorColonias[i].setMoedas(vectorColonias[i].getMoedas()+(vectorColonias[i].getQuinta(vectorColonias[i].getVectorEdificios()->at(j).getID())->getMoedasProduzidas()));
                    break;
                case Edificios::TORRE:
                    Torre* torre = vectorColonias[i].getTorre(vectorColonias[i].getVectorEdificios()->at(j).getID());
                    Unidade * uniAtacar[24];
                    uniAtacar[0] = this->verificaPosicao(torre->getLinha() - 1, torre->getColuna() - 1);
                    uniAtacar[1] = this->verificaPosicao(torre->getLinha(), torre->getColuna() - 1);
                    uniAtacar[2] = this->verificaPosicao(torre->getLinha() + 1, torre->getColuna() - 1);
                    uniAtacar[3] = this->verificaPosicao(torre->getLinha() + 1, torre->getColuna());
                    uniAtacar[4] = this->verificaPosicao(torre->getLinha() + 1, torre->getColuna() + 1);
                    uniAtacar[5] = this->verificaPosicao(torre->getLinha(), torre->getColuna() + 1);
                    uniAtacar[6] = this->verificaPosicao(torre->getLinha() - 1, torre->getColuna() + 1);
                    uniAtacar[7] = this->verificaPosicao(torre->getLinha() - 1, torre->getColuna());
                    uniAtacar[8] = this->verificaPosicao(torre->getLinha() - 2, torre->getColuna() - 1);
                    uniAtacar[9] = this->verificaPosicao(torre->getLinha() - 2, torre->getColuna() - 2);
                    uniAtacar[10] = this->verificaPosicao(torre->getLinha() - 1, torre->getColuna() - 2);
                    uniAtacar[11] = this->verificaPosicao(torre->getLinha(), torre->getColuna() - 2);
                    uniAtacar[12] = this->verificaPosicao(torre->getLinha() + 1, torre->getColuna() - 2);
                    uniAtacar[13] = this->verificaPosicao(torre->getLinha() + 2, torre->getColuna() - 2);
                    uniAtacar[14] = this->verificaPosicao(torre->getLinha() + 2, torre->getColuna() - 1);
                    uniAtacar[15] = this->verificaPosicao(torre->getLinha() + 2, torre->getColuna());
                    uniAtacar[16] = this->verificaPosicao(torre->getLinha() + 2, torre->getColuna() + 1);
                    uniAtacar[17] = this->verificaPosicao(torre->getLinha() + 2, torre->getColuna() + 2);
                    uniAtacar[18] = this->verificaPosicao(torre->getLinha() + 1, torre->getColuna() + 2);
                    uniAtacar[19] = this->verificaPosicao(torre->getLinha(), torre->getColuna() + 2);
                    uniAtacar[20] = this->verificaPosicao(torre->getLinha() - 1, torre->getColuna() + 2);
                    uniAtacar[21] = this->verificaPosicao(torre->getLinha() - 2, torre->getColuna() + 2);
                    uniAtacar[22] = this->verificaPosicao(torre->getLinha() - 2, torre->getColuna() + 1);
                    uniAtacar[23] = this->verificaPosicao(torre->getLinha() - 2, torre->getColuna());
                    for (int k = 0; k < 24; k++) {
                        if (uniAtacar[k] != NULL) {
                            switch (uniAtacar[k]->getUnidade()) {
                                case Unidade::SER:
                                    Ser* serA;
                                    serA = getSer(uniAtacar[k]->getLinha(), uniAtacar[k]->getColuna());
                                    if (serA->getBandeira() == true && serA->getEquipa() != torre->getEquipa() || serA->getBandeira() == false) {
                                        cout << "TORRE: Detetei um ser -> " << serA->getID() << endl;
                                        if (torre->getAtaque() > serA->getDefesa()) {
                                            serA->setSaude(serA->getSaude()-(torre->getAtaque() - serA->getDefesa()));
                                        } else {
                                            serA->setSaude(serA->getSaude() - 1);
                                        }
                                        if (serA->getSaude() <= 0) {
                                            if (serA->getSecondChance() == true) {
                                                serA->setSecondChance(false);
                                                serA->setSaude(serA->getSaudeMAX());
                                                serA->setLinhaColuna(vectorColonias[i].getCastelo()->getLinha(), vectorColonias[i].getCastelo()->getColuna());
                                            } else {
                                                this->removeSer(serA->getID());
                                            }
                                        }
                                        k = 24;
                                    }
                                    break;
                                case Unidade::EDIFICO:
                                    Edificios* ediA;
                                    ediA = getEdifico(uniAtacar[k]->getLinha(), uniAtacar[k]->getColuna());
                                    if (ediA != NULL && ediA->getEquipa() != torre->getEquipa()) {
                                        cout << "TORRE: Detetei um edicio -> " << ediA->getID() << endl;
                                        if (torre->getAtaque() > ediA->getDefesa()) {
                                            ediA->setSaude(ediA->getSaude()-(torre->getAtaque() - ediA->getDefesa()));
                                        } else {
                                            ediA->setSaude(ediA->getSaude() - 1);
                                        }
                                        if (ediA->getSaude() <= 0) {
                                            /*if (ediA->getNome() == "C") {
                                                this->removeColonia(ediA->getEquipa());
                                            } else {
                                                this->removeEdificio(ediA->getID());
                                            }*/
                                            this->removeEdificio(ediA->getID());
                                        }
                                        k = 24;
                                    }
                                    break;
                            }
                        }
                    }
                    break;
            }
        }
    }
    vector<int> indexApagar;
    for(int i = 0; i < vectorColonias.size(); i++){
        if(vectorColonias[i].getVectorEdificios()->size() == 0 && vectorColonias[i].getVectorSer()->size() == 0){
            indexApagar.push_back(i);
        }
    }
    for(int i = 0; i < indexApagar.size(); i++){
        vectorColonias.erase(vectorColonias.begin()+indexApagar[i]);
    }
    if (vectorColonias.size() == 1) {
        Consola::setBackgroundColor(Consola::CYAN);
        Consola::clrscr();
        Consola::setTextColor(Consola::VERMELHO_CLARO);
        cout << "        <";
        Consola::setTextColor(Consola::BRANCO_CLARO);
        cout << "----- ";
        Consola::setTextColor(Consola::VERMELHO_CLARO);
        cout << "C";
        Consola::setTextColor(Consola::BRANCO_CLARO);
        cout << "ASTLE";
        Consola::setTextColor(Consola::VERMELHO_CLARO);
        cout << "W";
        Consola::setTextColor(Consola::BRANCO_CLARO);
        cout << "AR!";
        Consola::setTextColor(Consola::BRANCO_CLARO);
        cout << " -----";
        Consola::setTextColor(Consola::VERMELHO_CLARO);
        cout << ">" << endl;
        Consola::setTextColor(Consola::BRANCO_CLARO);
        cout << "Jogo terminado! A colonia " << vectorColonias[0].getNome() << " ganhou!\n" << endl;
        cout << "Prima qualquer tecla para continuar...";
        Consola::getch();
        return false;
    }
    return true;
}

bool Controlador::verificaMovimento(int linha, int coluna, int flag, int equipa) {
    if (linha >= 0 && linha < linhasDefault && coluna >= 0 && coluna < colunasDefault) {
        Unidade* u = verificaPosicao(linha, coluna);
        if (u == NULL) {
            return true;
        } else {
            if (flag == ATACA) {
                return false;
            } else if (flag == RECOLHE) {
                if (equipa != -1) {
                    if (u->getEquipa() == equipa) {
                        if (u->getNome() == "C") {
                            return true;
                        } else {
                            return false;
                        }
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            }
        }
    } else {
        return false;
    }
}

bool Controlador::removeColonia(int id) {
    for (int i = 0; i < vectorColonias.size(); i++) {
        if (vectorColonias[i].getID() == id) {
            vectorColonias.erase(vectorColonias.begin() + i);
            return true;
        }
    }
    return false;
}

void Controlador::movimentoRandom(Ser* ser) {
    switch (rand() % 8) {
        case 0:
            if (verificaMovimento(ser->getLinha() - 1, ser->getColuna() - 1, ATACA)) {
                ser->setLinhaColuna(ser->getLinha() - 1, ser->getColuna() - 1);
            }
            break;
        case 1:
            if (verificaMovimento(ser->getLinha(), ser->getColuna() - 1, ATACA)) {
                ser->setLinhaColuna(ser->getLinha(), ser->getColuna() - 1);
            }
            break;
        case 2:
            if (verificaMovimento(ser->getLinha() + 1, ser->getColuna() - 1, ATACA)) {
                ser->setLinhaColuna(ser->getLinha() + 1, ser->getColuna() - 1);
            }
            break;
        case 3:
            if (verificaMovimento(ser->getLinha() + 1, ser->getColuna(), ATACA)) {
                ser->setLinhaColuna(ser->getLinha() + 1, ser->getColuna());
            }
            break;
        case 4:
            if (verificaMovimento(ser->getLinha() + 1, ser->getColuna() + 1, ATACA)) {
                ser->setLinhaColuna(ser->getLinha() + 1, ser->getColuna() + 1);
            }
            break;
        case 5:
            if (verificaMovimento(ser->getLinha(), ser->getColuna() + 1, ATACA)) {
                ser->setLinhaColuna(ser->getLinha(), ser->getColuna() + 1);
            }
            break;
        case 6:
            if (verificaMovimento(ser->getLinha() - 1, ser->getColuna() + 1, ATACA)) {
                ser->setLinhaColuna(ser->getLinha() - 1, ser->getColuna() + 1);
            }
            break;
        case 7:
            if (verificaMovimento(ser->getLinha() - 1, ser->getColuna(), ATACA)) {
                ser->setLinhaColuna(ser->getLinha() - 1, ser->getColuna());
            }
            break;
    }
}

string Controlador::toLower(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

string Controlador::toUpper(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}