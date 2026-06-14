# INTEGRAÇÃO - INTEGRANTE 1 E INTEGRANTE 3

## 📋 Resumo

Este documento explica a integração do código de **Integrante 1** (CRUD de Despesas) e **Integrante 3** (Histórico com Pilha + Fila de Pendentes) no repositório do projeto.

---

## 🏗️ Estrutura de Arquivos

```
src/
├── config.h                    (Configurações globais - não alterar)
├── main.cpp                    (Interface Raylib - Integrante 4 completa)
├── models/
│   ├── despesa.h              ✅ INTEGRANTE 1 (header adaptado)
│   ├── despesa.cpp            ✅ INTEGRANTE 1 (implementação adaptada)
│   └── operacao.h             (Enum TipoOperacao - não alterar)
└── structures/
    ├── historico.h            ✅ INTEGRANTE 3 (Pilha LIFO)
    ├── historico.cpp          ✅ INTEGRANTE 3
    ├── fila.h                 ✅ INTEGRANTE 3 (Fila FIFO)
    └── fila.cpp               ✅ INTEGRANTE 3
```

---

## 👤 INTEGRANTE 1 - OPERAÇÕES CRUD

### Arquivos: `src/models/despesa.h` e `despesa.cpp`

**O que foi feito:**
- Adaptou `inte1.cpp` para `despesa.cpp` com estrutura de char[] em vez de strings
- Mantém todas as operações: inserir, editar, remover, listar, buscar, totalizar
- **Não foi alterado logicamente** — apenas adaptado aos types do repositório

**Variáveis Globais (compartilhadas):**
```cpp
extern Despesa lista[MAX_DESPESAS];      // Array global de despesas
extern int quantidade;                    // Quantos itens tem na lista
extern int proximoId;                     // Próximo ID a ser assignado
```

**Funções Disponíveis:**
```cpp
void inserir(const char* descricao, const char* categoria, float valor, const char* data);
void inserirOrdenado(const char* descricao, const char* categoria, float valor, const char* data);
void listar();
void editar(int id, const char* novaDescricao, const char* novaCategoria, 
            float novoValor, const char* novaData);
void remover(int id);
void buscarPorCategoria(const char* categoria);
float totalPorCategoria(const char* categoria);
void marcarComoPaga(int id);
int buscarIndice(int id);
```

**Como usar (exemplo):**
```cpp
#include "models/despesa.h"

// Inserir uma despesa
inserir("Mercado", "Alimentacao", 150.50f, "14/06/2026");

// Listar todas
listar();

// Buscar por ID
int idx = buscarIndice(1);
```

---

## 👤 INTEGRANTE 3 - HISTÓRICO (PILHA) E FILA

### Arquivos: `src/structures/historico.h/.cpp` e `fila.h/.cpp`

#### 1️⃣ HISTÓRICO (Pilha LIFO)

**O que é:**
- Rastreia cada operação realizada (cadastro, remoção, edição)
- Permite **DESFAZER** (undo) a última ação
- Usa uma pilha para LIFO (Last In, First Out)

**Funções Disponíveis:**
```cpp
void inserirComHistorico(const char* descricao, const char* categoria, 
                        float valor, const char* data);
void removerComHistorico(int id);
void editarComHistorico(int id, const char* novaDescricao, const char* novaCategoria,
                       float novoValor, const char* novaData);
void desfazerHistorico();
bool historicoVazio();
void mostrarHistorico();  // Debug
```

**Como usar:**
```cpp
#include "structures/historico.h"

// Em vez de inserir(), use inserirComHistorico()
inserirComHistorico("Aluguel", "Moradia", 1200.0f, "01/06/2026");

// Se não quiser registrar no histórico, chame direto:
inserir("Outro item", "Categoria", 100.0f, "14/06/2026");

// Desfazer último comando
desfazerHistorico();
```

---

#### 2️⃣ FILA (FIFO)

**O que é:**
- Gerencia **contas pendentes de pagamento**
- Usa fila circular: FIFO (First In, First Out)
- Integrada com a lista global de Integrante 1

**Funções Disponíveis:**
```cpp
void enqueueConta(const Despesa* d);           // Adicionar à fila
Despesa dequeueConta();                        // Remover da fila
bool filaVaziaContas();
void mostrarFilaContas();
void pagarProximaConta();                      // Pagar + marcar como paga
void agendarPagamentoPorId(int id);            // Procura na lista e enfileira
int quantidadePendentes();
```

**Como usar:**
```cpp
#include "structures/fila.h"

// Agendar pagamento para uma despesa existente
agendarPagamentoPorId(1);  // Despesa com ID=1

// Ver fila
mostrarFilaContas();

// Pagar próxima
pagarProximaConta();
```

---

## 🔗 Como Tudo Se Liga

```
[Integrante 4 - Interface Raylib]
         ↓
    main.cpp
    ├── chama funções de Integrante 1
    ├── chama funções de Integrante 3
    └── chama funções de Integrante 2
    
[Integrante 1 - CRUD]
    despesa.h / despesa.cpp
    ├── lista[], quantidade, proximoId (compartilhados)
    └── inserir(), editar(), remover(), etc.
         ↑
         Lido por Integrante 3
    
[Integrante 3 - Histórico + Fila]
    historico.h/cpp ──→ Usa lista[] de Integrante 1
    fila.h/cpp ──→ Usa lista[] de Integrante 1
    
[Integrante 2 - Algoritmos]
    algorithms/ (ainda será implementado)
    ├── Bubble Sort
    ├── Insertion Sort
    ├── Selection Sort
    └── Busca Binária
```

---

## ✅ O Que Já Está Pronto

- ✅ **Integrante 1:** CRUD completo (inserir, editar, remover, listar)
- ✅ **Integrante 3:** Histórico (desfazer) + Fila de pendentes
- ⏳ **Integrante 2:** Algoritmos (aguardando implementação)
- ⏳ **Integrante 4:** Interface Raylib (aguardando implementação)

---

## ⚠️ Importante para Integrante 4 (Líder)

### Ao implementar a interface:

1. **Inclua os headers:**
   ```cpp
   #include "models/despesa.h"
   #include "structures/historico.h"
   #include "structures/fila.h"
   ```

2. **Use os wrappers com histórico** quando quiser que o usuário possa desfazer:
   ```cpp
   // Desfazável:
   inserirComHistorico(desc, categ, valor, data);
   
   // Sem histórico:
   inserir(desc, categ, valor, data);
   ```

3. **Menu recomendado:**
   - Cadastrar despesa (Integrante 1)
   - Listar despesas (Integrante 1)
   - Buscar por categoria (Integrante 1)
   - Editar despesa (Integrante 3 - com histórico)
   - Desfazer (Integrante 3)
   - Agendar pagamento (Integrante 3 - Fila)
   - Ver pendentes (Integrante 3 - Fila)
   - Pagar conta (Integrante 3 - Fila)
   - Gráficos/Relatórios (Integrante 2 - Algoritmos)

---

## 📝 Notas Técnicas

### Tipos de Dados
- `MAX_DESC`: 128 caracteres para descrição
- `MAX_CATEG`: 32 caracteres para categoria
- `MAX_DATA`: 11 caracteres (DD/MM/AAAA)
- `MAX_DESPESAS`: 500 itens máximo
- `MAX_HISTORICO`: 100 operações máximo
- `MAX_PENDENTES`: 500 contas máximo

### Variáveis Compartilhadas
Todos os módulos acessam:
```cpp
extern Despesa lista[MAX_DESPESAS];
extern int quantidade;
extern int proximoId;
```

Isso significa que quando você insere uma despesa via `inserir()`, o `Integrante 3` consegue acessar via `lista[]`.

---

## 🚀 Próximos Passos

1. **Integrante 2:** Implementar `src/algorithms/` com os 4 algoritmos
2. **Integrante 4:** Implementar a interface gráfica em `src/ui/`
3. **Líder:** Integrar tudo no `main.cpp`

---

## 📞 Dúvidas Frequentes

**P: Por que usar `inserirComHistorico()` em vez de `inserir()`?**
R: Porque `inserirComHistorico()` registra a ação na pilha, permitindo desfazer. Se não precisar dessa funcionalidade, use `inserir()` direto.

**P: Posso usar `fila.h` sem `historico.h`?**
R: Sim! São independentes. A fila não depende do histórico.

**P: O que acontece se a lista ficar cheia?**
R: As funções checam e retornam erro. Aumente `MAX_DESPESAS` em `config.h`.

**P: Como integro os algoritmos de Integrante 2?**
R: Crie `src/algorithms/sorts.h` e `sorts.cpp` com as funções de ordenação e busca. Eles vão operar sobre `lista[]`.

---

**Atualizado em:** 14/06/2026  
**Por:** Integrante 3 (com Copilot)
