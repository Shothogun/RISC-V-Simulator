# Plataforma de desenvolvimento

----------------

## Compilação

### Compilador

O __compilador__ empregado para a construção do programa de teste da biblioteca simuladora do RISC_V foi o __gcc 7.3.0__ (padrão do Linux Ubuntu 18.04).

Para sua compilação foi utilizada o seguinte padrão:

```
$ gcc <arquivos> -W -Wall -g -pedantic -o <nome_do_programa>
```

Mais informações da forma como os códigos foram compilados, por favor, consultar o arquivo Makefile.

### Compilar o programa de teste da biblioteca de simulação do RISCV
Para a compilação do programa de teste das funções do simulador do RISCV, basta estar no diretório `/Fetch_execute_cycle` e executar pelo terminal:

```
$ make test
```
Para executar o programa depois da compilação, entrar na pasta `/Fetch_execute_cycle/exec/`, e digitar no terminal:

```
$ ./test
```

### Compilar o programa que simula o RISCV

Para compilar o programa responsável por simular a arquitetura do RISCV executando um programa em assembly, no caso expresso em arquivos binários data.bin e text.bin(correspondente ao código assembly_tests.asm), execute no terminal: 

```
$ make assembly_code
```
Para executar o programa depois da compilação, entrar na pasta `/Fetch_execute_cycle/exec/` e digitar no terminal:

```
$ ./assembly_code
```

Para testar o simulador com diferentes códigos assembly, basta entrar no RARS, configurar ele, e gerar os arquivos binários. Entrar em `settings -> Memory configuration`, selecionar opcao Compact, Text at address 0. Monte o programa `(F3)`, abra a aba `File-> dump memory` e selecionar:

    .text (0x00000000 - 0xXXXXXXX)
    Dump Format: binary

    .data (0x00002000 - 0x00002FFC)
    Dump Format: binary

Desse modo o arquivo .text deve se chamar `text.bin`; e o .data, `data.bin`. Após gerar esses arquivos, basta mover os antigos da pasta `/Fetch_execute_cycle/exec/` para uma outra pasta, e substituí-las pelos novos gerados.

__Atenção Atenção!!!__

    Tanto o programa de teste quanto o programa que executa os códigos em assembly exigem a presença dos arquivos .text e .data. Se mal gerados ou ausentes, os programas NÃO FUNCIONARÃO.

## Plataforma SO

> O desenvolvimento desse código foi
> feita por meio do sistema
> operacional Linux, distribuição
> Ubuntu 18.04 LTS

## IDE de desenvolvimento

A IDE utilizada para a realização desse projeto foi o __Visual Studio Code__ para distribuições Debian, versão __1.33.1__