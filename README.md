# Sistema-Financeiro-ED

Sistema de gerenciamento de finanças pessoais desenvolvido em C++ com interface gráfica em Raylib.  
Projeto acadêmico — Disciplina de Estrutura de Dados — UNIALFA — 3° Semestre — Prof. Rodrigo Naka.
Link github: https://github.com/JoaoFsSilva/Sistema-Financeiro-ED
---

## ✅ Funcionalidades

- [x] Cadastro de despesas
- [x] Histórico financeiro
- [x] Ordenação de gastos (Bubble, Insertion e Selection Sort)
- [x] Busca de lançamentos (Busca Binária)
- [x] Desfazer operações (Pilha LIFO)
- [x] Fila de despesas pendentes (Fila FIFO)
- [x] Relatórios gráficos por categoria

---

## 🗂️ Estrutura do Projeto

```
Sistema-Financeiro-ED/
├── src/
│   ├── main.cpp
│   ├── config.h
│   ├── models/          # Integrante 1 — struct Despesa + CRUD
│   ├── algorithms/      # Integrante 2 — ordenação e busca
│   ├── structures/      # Integrante 3 — pilha e fila
│   └── ui/              # Integrante 4 — interface Raylib
├── libs/
│   └── raylib/
│       ├── include/     # raylib.h (adicionar manualmente — veja abaixo)
│       └── lib/         # libraylib.a (adicionar manualmente — veja abaixo)
├── assets/
├── build/
├── Makefile
└── README.md
```

---

## ⚙️ Configuração do Ambiente

> **Atenção:** siga os passos abaixo antes de tentar compilar. A Raylib e o compilador **não estão incluídos no repositório** e precisam ser configurados em cada máquina.

### 1. Instalar o MSYS2

Baixe e instale o MSYS2 em [msys2.org](https://www.msys2.org). Instale na localização padrão `C:\msys64`.

### 2. Instalar o compilador e o make

Abra o terminal **MSYS2 MinGW 64-bit** (não o MSYS2 comum) e rode:

```bash
pacman -S mingw-w64-x86_64-gcc make
```

### 3. Adicionar ao PATH do Windows

Vá em **Painel de Controle → Sistema → Variáveis de Ambiente → Path** e adicione as duas entradas abaixo:

```
C:\msys64\mingw64\bin
C:\msys64\usr\bin
```

Feche e reabra o VS Code após salvar.

### 4. Adicionar os arquivos da Raylib

A Raylib não está no repositório (arquivo binário, não versionamos). Instale via pacman:

```bash
pacman -S mingw-w64-x86_64-raylib
```

Depois copie os dois arquivos para dentro do projeto (ajuste o caminho se necessário):

```bash
cp /c/msys64/mingw64/include/raylib.h   ./libs/raylib/include/
cp /c/msys64/mingw64/lib/libraylib.a    ./libs/raylib/lib/
```

---

## 🔨 Como Compilar e Executar

Abra o **Git Bash** ou use `Ctrl+Shift+B` no VS Code:

```bash
# Compilar
make

# Executar
./build/financas.exe

# Limpar build
make clean
```

---

## 📚 Algoritmos Implementados

| Algoritmo | Ordena por | Complexidade média |
|---|---|---|
| Bubble Sort | Valor | O(n²) |
| Selection Sort | ID | O(n²) |
| Insertion Sort | Categoria | O(n²) |
| Busca Binária | ID (lista deve estar ordenada) | O(log n) |

---

## 👥 Divisão da Equipe

| Integrante | Responsabilidade | Arquivos |
|---|---|---|
| Integrante 1 | Estruturas base e CRUD | `models/despesa.h/.cpp`, `models/operacao.h` |
| Integrante 2 | Algoritmos de ordenação e busca | `algorithms/ordenacao.h/.cpp` |
| Integrante 3 | Pilha e Fila | `structures/historico.h/.cpp`, `structures/fila.h/.cpp` |
| Integrante 4 | Interface e integração | `ui/sistema.h`, `ui/interface.h/.cpp`, `ui/relatorios.h/.cpp`, `main.cpp` |

---

## 🏫 Informações Acadêmicas

- **Disciplina:** Estrutura de Dados
- **Instituição:** UNIALFA
- **Semestre:** 3°
- **Professor(a):** Rodrigo Naka
