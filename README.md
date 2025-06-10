# Teoria da Computação

Esse projeto tem como objetivo criar um programa que receba uma Gramática Linear Unitária à Direita (GLUD) e, a partir dela, gere um Automato Finito Não Determinístico (AFND), para então gerar um Automato Finito Determinístico (AFD). No fim, será possível testar uma cadeia de entrada no AFD resultante, que deve reconhecer a mesma linguagem gerada pela GLUD.

Além das conversões, o programa é capaz de aplicar as operações de Reverso e Complemento na AFD, gerando assim novas AFDs que reconheçam respectivamente as entradas invertidas e tudo que não é aceito na AFD original.

## Build

```
mkdir build
cmake -S . -B build/
cmake --build build/
```

## Execução

Se apenas executar o binário gerado, o programa irá realizar todo o processo para a gramática que já está na função main.

Caso queira executar todos os testes com as gramáticas no arquivo `test_inputs.h`, basta executar o programa passando o parâmetro `-t`.

Caso queira apenas fazer as conversões de uma gramática que esteja em um arquivo de texto, basta executar o programa passando o parâmetro `-f` e em seguida o caminho para um arquivo. Por exemplo:

```
tcomp -f <caminho_para_arquivo>
```

Caso deseje gerar as saídas de acordo com o que foi solicitado no trabalho, basta incluir além do caminho para o arquivo, um parâmetro `-w` e em seguida uma cadeia de entrada. Por exemplo:

```
tcomp -f <caminho_para_arquivo> -w <cadeia>
```

### Formato do arquivo

Uma GLUD é um conjunto $G = \{V, T, P, S\}$, onde $V$ é um conjunto de variáveis, $T$ é um conjunto de símbolos terminais, $P$ é um conjunto de produções no formato $\alpha \rightarrow \beta$, onde $\alpha \in V$ e $\beta \in \{\epsilon, t, v, tv\}$, para $t \in T$ e $v \in V$.

> Nesse projeto, o símbolo $\epsilon$ é representado por um `@`.

A primeira linha do arquivo de entrada deverá ser um inteiro **A** representando a quantidade de variáveis. Na segunda linha devem ser colocadas as **A** variáveis, separadas por espaço. A terceira linha será um inteiro **B** representando a quantidade de simbolos terminais. A quarta linha consistirá nos **B** simbolos terminais, separados por espaço. A quinta linha será um inteiro **C** representando o número de produções da gramática. Cada uma das **C** proximas linhas deverá ter uma produção no formato  `A -> B`. Por fim, a última linha do arquivo será a variável inicial da gramática.

Um exemplo de arquivo de entrada seria:

```
2
S A
2
a b
3
S -> aA
A -> bS
S -> @
S
```