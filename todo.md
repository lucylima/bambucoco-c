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

- [ ] **Definir constantes** no `.h` (ex: `MAX_LINHAS`, `MAX_COLUNAS`, `MAX_ITENS_MENU`).
- [ ] **Criar struct `ItemMenu`**: (ID, nome, preço, categoria).
- [ ] **Criar struct `Pedido`**: (ID do item, quantidade).
- [ ] **Criar struct `Mesa`**: (ID, status, capacidade, array de pedidos, contador de itens, total da conta).
- [ ] **Declarar a Matriz Global**: Instanciar a matriz `Mesa restaurante[LINHAS][COLUNAS]` no `main.c`.

### 💾 Fase 3: Persistência de Dados (Arquivos)

- [ ] **Criar arquivo `menu.txt`**: Popular manualmente com alguns itens (ex: `1;Moqueca;45.00`).
- [ ] **Implementar `carregar_menu()`**: Ler `menu.txt`, fazer o *parsing* da string (usando `strtok` ou `fscanf`) e preencher um vetor de structs `ItemMenu`.
- [ ] **Implementar `salvar_relatorio()`**: Função que recebe os dados de uma conta fechada e escreve (append) em `historico_vendas.txt` com data e hora.

### 🧠 Fase 4: Lógica de Negócio (Core)

- [ ] **Implementar `inicializar_restaurante()`**: Percorrer a matriz definindo todas as mesas como "Livres" e atribuindo IDs sequenciais.
- [ ] **Implementar `buscar_mesa()`**: Função auxiliar para encontrar as coordenadas (i, j) de uma mesa pelo seu ID numérico.
- [ ] **Implementar `adicionar_pedido()`**:
    - [ ] Verificar se a mesa está aberta.
    - [ ] Buscar item no menu pelo ID.
    - [ ] Adicionar ao vetor de pedidos da struct `Mesa`.
    - [ ] Atualizar o subtotal da mesa.
- [ ] **Implementar `fechar_conta()`**: Somar tudo, exibir o total, salvar no relatório e limpar a struct da mesa (resetar para "Livre").
- [ ] **Lógica Avançada (Matriz)**: Implementar função `verificar_vizinhos()` para checar se mesas ao lado estão livres (para futura funcionalidade de juntar mesas).

### 🖥️ Fase 5: Interface e Navegação

- [ ] **Criar `exibir_mapa()`**:
    - [ ] Loop aninhado que imprime a matriz no terminal.
    - [ ] Usar formatação visual (ex: `[ L ]` para livre, `[XXX]` para ocupada).
- [ ] **Menu Principal**: Loop `do-while` com `switch-case` para as opções (Novo Pedido, Ver Mapa, Fechar Conta, Sair).
- [ ] **Input Sanitization**: Garantir que se o usuário digitar uma letra onde deveria ser número, o programa não quebre.

### ✅ Fase 6: Polimento e Testes
- [ ] **Revisão de vazamento de memória**: Verificar se todos os arquivos abertos com `fopen` foram fechados com `fclose`.
- [ ] **Teste de carga**: Tentar encher todas as mesas e ver se o sistema aguenta.

---
