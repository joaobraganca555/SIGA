## Programação 22/23 2º Semestre

### Introdução

Estão responsáveis por desenvolver um programa protótipo para gestão de carteiras de investimento, denominado Sistema de
Informação para a Gestão de Ativos (SIGA). Este sistema suportará os analistas e gestores de carteiras no seu trabalho,
ao centralizar os dados dos ativos e carteiras dos clientes.

### Estrutura & Organização

- Existem Carteira, AtivoFinanceiro, ValorAtivo, AtivoCarteira
- Cada Carteira está associada a uma série de AtivoCarteira
- Cada AtivoCarteira está associada a um AtivoFinanceiro
- Cada AtivoFinanceiro está associado a um ValorAtivo

**Dados de AtivoFinanceiro**

- id
- tipo (acção, bond, crypto, …)
- nome

**Dados de ValorAtivo**

- id do AtivoFinanceiro
- data
- valor

**Dados de Carteira**

- id da Carteira
- descrição
- lista de AtivoCarteira

**Dados de AtivoCarteira**

- id de AtivoFinanceiro
- quantidade desse AtivoFinanceiro que está guardado em Carteira

O programa guarda uma base de dados em formato binário com as carteiras, as quantidades de cada ativo em cada carteira e
os valores atuais dos ativos financeiros. A lista de ativos financeiros disponível está num ficheiro de texto.

### Funcionalidades

- Importar dados de ficheiro de texto
    - Carteira nova
    - Atualização dos novos valores dos AtivoFinanceiro
- Compra/Venda de AtivoFinanceiro para determinada Carteira
    - Programa lista as carteiras existentes com id e nome
    - Programa mostra lista de ativos atuais em carteira e questiona se utilizador quer comprar ou vender mais unidades
      de algum desses ativos
        - Comprar/vender ativos atuais: utilizador seleciona o que quer, se quer vender ou comprar e quantidade
        - Comprar outros ativos: programa mostra lista de todos os ativos existentes, utilizador seleciona o que quer e
          quantidade a comprar.
- Relatórios
    - Descrever uma determinada Carteira
        - mostrar todos os AtivoCarteira
        - mostrar valor total da Carteira atual
- Estatísticas
    - 5 AtivoFinanceiros com maior valor
    - Média do valor de AtivoFinanceiro por tipo
    - Gráfico com evolução do preço de um determinado AtivoFinanceiro (⚠️ para grupos de 4 elementos)

### Formato dos ficheiros de texto para importar

**Ficheiro de texto para importar conjunto de Carteira**

```
CarteiraId 2
CarteiraDescrição
Id de AtivoFinanceiro 1
Quantidade de AtivoFinanceiro 1
Id de AtivoFinanceiro 2
Quantidade de AtivoFinanceiro 2
... (representativo de mais ativos financeiros)
Id de AtivoFinanceiro N
Quantidade de AtivoFinanceiro N
---
CarteiraId 2
CarteiraDescrição
Id de AtivoFinanceiro 1
Quantidade de AtivoFinanceiro 1
Id de AtivoFinanceiro 2
Quantidade de AtivoFinanceiro 2
...
Id de AtivoFinanceiro N
Quantidade de AtivoFinanceiro N
```

**Ficheiro de texto para importar novos valores de AtivoFinanceiro (duração dada em minutos), i.e. lista de ValorAtivo**

- Em cada linha o formato é `data[espaço]id de ativo[espaço]novo valor`
- Exemplo:

```
2023-05-17 1 13.13
2023-05-17 2 34.12
2023-05-17 3 42.12
```

- Ficheiro de texto com lista de AtivoFinanceiro disponível.

```
1,A,Tesla
2,C,Bitcoin
3,B,iShares iBoxx ETF
```

### Notas

- Se for conveniente, podes assumir que nunca existirão mais de 100 carteiras e que uma carteira nunca tem mais de 50
  AtivoCarteira.
- Pode ajudar manter a base de dados de ValorAtivo ordenada por data.
- Não usar qualquer biblioteca além das que foram introduzidas nas aulas sem aprovação do docente.

### Entrega do trabalho

O trabalho deve implementar uma aplicação para o problema enunciado. Os ficheiros de código (.c e .h) assim como
documentação auxiliar (.txt, .pdf) são submetidos pelo chefe do grupo no Moodle. Ficheiros a submeter:

- Todos os ficheiros .c e .h necessários para a compilação e execução do programa;
- Todos os ficheiros necessários para a execução do programa (e.g. ficheiros de configuração, devem ser do tipo .txt);
- Um manual de utilização MANUAL.pdf com uma descrição simples e curta de como utilizar o programa (é o documento que um
  utilizador iria ler para aprender a utilizar o programa);
- Um relatório REPORT.pdf simples e curto sobre como implementaram as diversas funcionalidades e as decisões que
  tomaram, e onde se clarifica a estrutura do código (e.g. o ficheiro comandos.c contém as funções que manipulam a lista
  de comandos, grava a lista em ficheiro; optámos por manter a base de dados dos voos ordenada porque…; a estratégia
  para exportar os relatórios para ficheiro foi….; etc.);

Caso necessário, irão ocorrer discussões para defesa dos trabalhos.

### Critérios de avaliação

A avaliação do trabalho será feita de acordo com os seguintes princípios:

- O programa deve estar estruturado em funções consideradas necessárias para a resolução do problema. O programa deve
  estar dividido em vários ficheiros quando for relevante.
- O programa pode e deve reutilizar código tanto quanto possível e for adequado.
- O programa deve executar todas as funcionalidades tal como pedido.
- Devem ser escolhidos nomes apropriados para os tipos de dados, operações, variáveis e constantes de modo a facilitar o
  entendimento do programa. A formatação do código é importante.
- O código deve ser comentado. Todas as funções devem ter um breve comentário sobre a sua função, imediatamente abaixo
  do cabeçalho
