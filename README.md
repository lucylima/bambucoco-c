# BambuCoco - Sistema de Gestão de Restaurante (C/CLI)

![Language](https://img.shields.io/badge/Language-C11-blue?style=for-the-badge&logo=c)
![Platform](https://img.shields.io/badge/Platform-Linux-orange?style=for-the-badge&logo=linux)
![Build](https://img.shields.io/badge/Build-Makefile-green?style=for-the-badge&logo=gnu-bash)
![License](https://img.shields.io/badge/License-MIT-lightgrey?style=for-the-badge)

> **⚠️ DISCLAIMER / AVISO LEGAL**
> 
> Este software é um **projeto acadêmico** desenvolvido para fins de estudo de Estrutura de Dados e Linguagem C na Universidade do Estado da Bahia (UNEB).
> 
> **O projeto NÃO possui qualquer vínculo, afiliação, autorização ou relação comercial com a rede de restaurantes "Coco Bambu" ou suas marcas registradas.** O nome "BambuCoco" é meramente fictício e utilizado em contexto educacional.

---

## Sobre o Projeto

**BambuCoco** é um sistema de gerenciamento de mesas e pedidos para restaurantes que opera via Interface de Linha de Comando (CLI). 

Diferente de sistemas comerciais padrão, este projeto foca na **performance de baixo nível** e no controle manual de recursos do sistema. Ele simula o ciclo de vida de um estabelecimento real (reservas, pedidos, fechamento de conta) persistindo dados complexos em arquivos binários.

## Funcionalidades

* [x] **Gestão de Mesas:** Visualização de mapa de mesas, reservas e liberação.
* [x] **Sistema de Comandas:** Adição dinâmica de itens a partir de um cardápio CSV.
* [x] **Junção de Mesas:** Algoritmo para fundir comandas e transferir responsabilidade de pagamentos.
* [x] **Persistência:** Salvamento automático do estado do restaurante em arquivo binário (`.bin`).
* [x] **Interface TUI:** Menu interativo via terminal com formatação alinhada.

## Estrutura de Arquivos

```bash
bambucoco-c/
├── data/
│   └── restaurante/
│       ├── cardapio.csv    # Banco de dados de produtos (Input)
│       └── mesas.bin       # Estado persistido do sistema (Output Binário)
├── lib/
│   ├── bambucoco.c         # Core Logic (Backend)
│   ├── interface.c         # Camada de Apresentação (Frontend CLI)
│   └── ...
├── main.c                  # Entry Point
├── Makefile                # Automação de Build
└── install.sh              # Script de Setup de Ambiente
```

## Instalação e Execução

### Pré-requisitos

- GCC Compiler

- Make

- Ambiente Linux/WSL

### Passo a Passo

1. Clone o repositório:

```bash
git clone https://github.com/lucylima/bambucoco-c.git
cd bambucoco-c
``` 

2. Setup do Ambiente: Execute o script para criar as pastas de dados necessárias:

```bash
chmod +x install.sh
./install.sh
```


3. Compilação e Execução:

  - **Modo Produção (Otimizado):**

    ```bash
    make release
    ./bambucoco
    ```

  - **Modo Desenvolvimento (Debug + ASan):**

    ```bash
    make all
    ./main
    ```

4. Limpeza: Para remover binários e objetos compilados:
Bash

```bash
make clean
```
___
## Lucy Lima
- Estudante de Sistemas de Informação - UNEB
- Foco: Backend, Hardware & Linux.
