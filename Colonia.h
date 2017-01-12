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
    
    const static int LIST = 0;
    const static int LISTP = 1;
    
    Colonia(string nome, int moedas);
    
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
     *  2 -> Nao ha castelo
     */
    int addEdificio(Edificios e);
    
    bool raioCastelo(Edificios &e);
    
    Edificios* getCastelo();
    
    vector<Perfil>* getVectorPerfil();
    vector<Ser>* getVectorSer();
    vector<Edificios>* getVectorEdificios();
    
    int getMoedas() const;
    string getNome() const;
    
    void listar(int modo); // teste
    virtual ~Colonia();

};

#endif /* COLONIA_H */

