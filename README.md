# Sistema-Financeiro-ED

Sistema de gerenciamento de finanças pessoais desenvolvido em C++ com interface gráfica em Raylib.  
Projeto acadêmico — Disciplina de Estrutura de Dados.

---
 
## ✅ Funcionalidades
 
- [x] Cadastro de despesas
- [x] Histórico financeiro
- [x] Ordenação de gastos (Bubble, Insertion e Selection Sort)
- [x] Busca de lançamentos (Busca Binária)
- [x] Desfazer operações (Pilha LIFO)
- [x] Fila de despesas pendentes (Fila FIFO)
- [x] Relatórios gráficos
---
 
## 🗂️ Estrutura do Projeto
 
```
financas-pessoais/
├── src/
│   ├── main.cpp
│   ├── config.h
│   ├── models/          # Integrante 1
│   ├── algorithms/      # Integrante 2
│   ├── structures/      # Integrante 3
│   └── ui/              # Integrante 4
├── libs/raylib/
├── assets/
├── build/
├── docs/
├── Makefile
└── README.md
```
 
---
 
## ⚙️ Como Compilar
 
### Pré-requisitos
 
- MinGW (g++) instalado e no PATH
- Windows 10 ou superior
### Compilar e executar
 
```bash
# Compilar
make
 
# Executar
./build/financas.exe
 
# Limpar build
make clean
```
 
> A Raylib já está incluída em `libs/raylib/` — não é necessário instalar nada além do MinGW.
 
---
 
## 📚 Algoritmos Implementados
 
| Algoritmo | Complexidade (melhor) | Complexidade (pior) | Uso no sistema |
|---|---|---|---|
| Bubble Sort | Ordenação simples |
| Insertion Sort | Listas quase ordenadas |
| Selection Sort | Ordenação por seleção |
| Busca Binária | Busca em lista ordenada |
 
 
## 🏫 Informações Acadêmicas
 
- **Disciplina:** Estrutura de Dados
- **Instituição:** UNIALFA 
- **Semestre:** 3°
- **Professor(a):** Rodrigo Naka
