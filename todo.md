# BambuCoco

### Fase 1: Configuração e Estrutura Básica
Esta fase prepara o terreno para o código.

- [x] **Criar diretório do projeto** e inicializar git (`git init`).
- [x] **Criar estrutura de arquivos**:
    - [x] `main.c` (ponto de entrada).
    - [x] `bambucoco.h` (definições de structs e protótipos de funções).
    - [x] `bambucoco.c` (implementação da lógica).
    - [x] `./data/` (pasta para guardar os arquivos .txt ou .csv).
- [x] **Configurar Makefile**: Criar um `Makefile` simples para compilar o projeto rapidamente no terminal.

### 🧱 Fase 2: Definição de Dados (Structs e Matriz)

- [x] **Definir constantes** no `.h` (ex: `MAX_LINHAS`, `MAX_COLUNAS`, `MAX_ITENS_MENU`).
- [x] **Criar struct `ItemMenu`**: (ID, nome, preço, categoria).
- [x] **Criar struct `Pedido`**: (ID do item, quantidade).
- [x] **Criar struct `Mesa`**: (ID, status, array de pedidos, contador de itens, total da conta).
- [x] **Declarar a Matriz Global**: Instanciar a matriz `Mesa restaurante[LINHAS][COLUNAS]` no `main.c`.

### 💾 Fase 3: Persistência de Dados (Arquivos)

- [x] **Criar arquivo `menu.csv`**: Popular manualmente com alguns itens (ex: `1;Moqueca;45.00`).
- [x] **Implementar `ler_cardapio()`**: Ler `cardapio.csv`, fazer o *parsing* da string (usando `strtok` ou `fscanf`) e preencher um vetor de structs `ItemMenu`.
- [ ] **Implementar `salvar_relatorio()`**: Função que recebe os dados de uma conta fechada e escreve (append) em `historico_vendas.txt` com data e hora.

### 🧠 Fase 4: Lógica de Negócio (Core)

- [x] **Implementar `inicializar_restaurante()`**: Percorrer a matriz definindo todas as mesas como "Livres" e atribuindo IDs sequenciais.
- [ ] **Implementar `buscar_mesa()`**: Função auxiliar para encontrar as coordenadas (i, j) de uma mesa pelo seu ID numérico.
- [ ] **Implementar `adicionar_pedido()`**:
    - [ ] Verificar se a mesa está aberta.
    - [ ] Buscar item no menu pelo ID.
    - [ ] Adicionar ao vetor de pedidos da struct `Mesa`.
    - [ ] Atualizar o subtotal da mesa.
- [ ] **Implementar `fechar_conta()`**: Somar tudo, exibir o total, salvar no relatório e limpar a struct da mesa (resetar para "Livre").
- [ ] **Implementar `reservar_mesa()`**: Reservar a mesa, checar se está livre e perguntar qual o tamanho da mesa.

### 🖥️ Fase 5: Interface e Navegação

- [x] **Criar `exibir_mapa()`**:
    - [x] Loop aninhado que imprime a matriz no terminal.
    - [x] Usar formatação visual (ex: `[ L ]` para livre, `[XXX]` para ocupada).
- [x] **Menu Principal**: Loop `do-while` com `switch-case` para as opções (Novo Pedido, Ver Mapa, Fechar Conta, Sair).
- [x] **Input Sanitization**: Garantir que se o usuário digitar uma letra onde deveria ser número, o programa não quebre.

### ✅ Fase 6: Polimento e Testes
- [ ] **Revisão de vazamento de memória**: Verificar se todos os arquivos abertos com `fopen` foram fechados com `fclose`.
- [ ] **Teste de carga**: Tentar encher todas as mesas e ver se o sistema aguenta.

---
