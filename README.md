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

Caso queira executar todos os testes com as gramáticas no arquivo `test_inputs.h`, baste executar o programa passando o parâmetro `-t`.