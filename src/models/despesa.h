#ifndef DESPESA_H
#define DESPESA_H

#include "../config.h"

struct Despesa {
    int   id;
    char  descricao[MAX_DESC];
    char  categoria[MAX_CATEG];
    char  data[MAX_DATA];
    float valor;
    bool  paga;
};

#endif // DESPESA_H
