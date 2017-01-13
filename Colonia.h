#ifndef COLONIA_H
#define COLONIA_H

#include "Perfil.h"
#include "Ser.h"
#include "Edificios.h"

#include <iostream>

class Colonia {
private:
    string nome;
    int moedas, id;
    static int conta;
    vector<Perfil> vectorPerfil;
    vector<Ser> vectorSer;
    vector<Edificios> vectorEdificios;   
public:    
    Colonia(string nome, int moedas);
    
    /*
     * Retorna o ID da colonia
     */
    int getID() const;
    
    /*
     * -1 -> Ja tem 5 perfils
     *  0 -> Ja existe perfil com esse nome
     *  1 -> Perfil criado com sucesso
     */
    int addPerfil(string nome);
    int addPerfil(const Perfil &p);
    Perfil* getPerfil(string nome);
    bool removePerfil(string nome);
    
    /*
     * -1 -> Colonia nao tem dinheiro
     *  0 -> Nao existe castelo
     *  1 -> Criado com sucesso
     */
    int addSer(Perfil* perfil, int linha, int coluna);
    
    /*
     * -1 -> Colonia nao tem dinheiro
     *  0 -> Nao esta no raio de 10 do castelo
     *  1 -> Edificio criado com sucesso
     */
    int addEdificio(Edificios e);
    
    bool raioCastelo(Edificios &e);
    
    Edificios* getCastelo();
    Edificios* getEdificio(int id);
    
    vector<Perfil>* getVectorPerfil();
    vector<Ser>* getVectorSer();
    vector<Edificios>* getVectorEdificios();
    
    int getMoedas() const;
    void setMoedas(int num);
    string getNome() const;
    
    void listar();
    virtual ~Colonia();

};

#endif /* COLONIA_H */

