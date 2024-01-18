/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2023                           **/
/**   Turma 94 - Prof. Flávio Luiz Coutinho                         **/
/**                                                                 **/
/**   Exercício-Programa                                            **/
/**                                                                 **/
/** <Gabriel Bernardini Schimidt>                <12873188>         **/
/** <Fernando Webes Soares Brandão>              <13672940>         **/
/** <Davi Martins>                               <10337787>         **/
/**                                                                 **/
/*********************************************************************/


## Sobre o proejto: 

    Trata-se de um indexador e buscador de palavras para arquivos de texto.

## Como compilar o projeto:

    1) Certifique-se que os seguintes arquivos estejam no mesmo diretório:
        - ep.c
        - arvore.h
        - funcoes.h
        - lista.h
 
    2) Confirmada a presença dos arquivos anteriores no mesmo diretório, execute em um terminal o seguinte comando para 
       gerar um arquivo executável:

         gcc -o <nome_para_o_ep.c> ep.c

         - Observações:

            2.1) Substitua "<nome_para_o_ep.c>" para o nome do executável que você desejar (retire os "<>").
                 - Exemplo: "gcc -o executavel ep.c"
            2.2) A execução do comando acima deve ser realziado dentro do diretório que contém os arquvios listados.

## Como executar o projeto:

	1)  Se que você seguiu corretamente os passos anteriores, agora você possui um arquivo executável.
	2)  No diretório onde executável está, coloque o arquivo de texto selecionado para se realizar a busca.
	3)  Com o executável e o arquivo de texto presentes no mesmo diretório, execute o comando:
	     "./<executável> <nome_do_arquivo> <tipo_de_organização>" , onde: 
		 <executável> = nome escolhido para o executável no passo anterior
		 <nome_do_arquivo> = nome do arquivo de texto escolhido (junto com sua extensão)
		 <tipo_de_organização> = escolha da organização utilizada pelo programa ("lista" ou "arvore", sem acento!)
		
		- Exemplo: ./exec texto.txt arvore

		- Observação: caso o terminal alertar que o comando "." não é reconhecido, faça: "<executável> <nome_do_arquivo> <tipo_de_organização>"
																[exec texto.txt arvore]
## No programa:

	Dentro do programa, após a leitura do arquivo, o usuário será recebido com um prompt ">". 
	Nesse momento, pode-se tanto digitar "busca <palavra_a_ser_buscada>" quanto "fim". 
	O primeiro busca no arquivo a palavra <palavra_a_ser_buscada>, enquanto o segundo encerra a operação.

	- Exemplo: busca Sorvete
	- Exemplo: fim


Por algum motivo não definido e explorado, o comando "fim", executado no terminal quando deseja-se finalizar o processo de busca necessitada de qualquer outra digitação para ser, de fato, concluído.


		