
#ifndef PERFIL_H
#define PERFIL_H

#include "Caracteristica.h"
#include <vector>

class Perfil {
private:
    string nome;
    int forca, custo;
    vector<Caracteristica*> vetorCaracteristicas;
public:
    Perfil(string nome);
    Perfil(const Perfil &p);
    
    Perfil& operator=(Perfil p);
    
    bool addCaracteristica(Caracteristica *c);
    Caracteristica* getCarateristica(int index);
    
    bool removeCarateristica(int id);
    
    string getNome() const;
    int getCusto() const;
    int getSizePerfil() const;
    
    bool temBandeira();
    
    void listarTudo();
    virtual ~Perfil();
};

#endif /* PERFIL_H */

