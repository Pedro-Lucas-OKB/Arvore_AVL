# Árvore AVL

Implementação de uma árvore AVL, feita em linguagem **C**, na disciplina de Estruturas de Dados Avançadas, 
pelo curso de Ciência da Computação da Universidade Federal do Ceará (Campus Russas).

### Definição

Uma árvore AVL é uma estrutura do tipo Árvore Binária de Busca(BST), a qual possui **balanceamento** entre seus nós.

#### Propriedade
Dado um nó **_v_** qualquer, e seja **_bal_** a diferença entre a altura das sub-árvores de **_v_** (direita - esquerda), então: -1 <= **_bal_** <= 1.

Por ser balanceada, a árvore AVL possui altura _O(log n)_.