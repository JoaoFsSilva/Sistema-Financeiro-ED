#ifndef OPERACAO_H
#define OPERACAO_H

#include "despesa.h"

enum TipoOperacao {
    OP_CADASTRO = 0,
    OP_REMOCAO  = 1,
    OP_EDICAO   = 2
};

struct Operacao {
    TipoOperacao tipo;
    Despesa      despesaAnterior;
};

#endif // OPERACAO_H
