//===================================================
//Bibliotecas
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h> //Fun��o para manipular informa��es de datas e horas (relat�rio 1 [4][1])
#include<locale.h>
#define max 100 //Limite do vetor (valor arbitr�rio)

//===================================================
//Estrutura de datas
struct DATA
{
	int DIA, MES, ANO;
};

//===================================================
//Estrutura dos usu�rios
struct USUARIOS
{
	char CPF[15], NOME[50], RUA[30],NRO[5], CEP[11], MAIL[50], FONE[15], PROF[35];
	DATA NASC;
};

//===================================================
//Estrutura dos livros
struct LIVROS
{
	char ISBN[20], TITULO[50], GENERO[30], AUTORES[5][50];
	int NRO_PAG, CONT_AUTORES;
};

//===================================================
//Estrutura dos empr�stimos
struct EMPRESTIMOS
{
	char CPF[15], ISBN[20];
	DATA RETIRADA, DEVOLUCAO;
	float MULTA;
};

//===================================================
//Fun��o para apresentar o menu de op��es
void menu()
{
	printf("\n\n\t=== MENU DE OP��ES ===\n\n[1] Submenu de Usu�rios\n[2] Submenu de Livros");
	printf("\n[3] Submenu de Empr�stimos\n[4] Submenu de Relat�rios\n[5] Sair\n");
}

//===================================================
//[1]
//Fun��o para apresentar o submenu de usu�rios
void menu_usuario()
{
	system("cls");
	printf("\t=== SUBMENU DE OP��ES - USU�RIOS ===\n\n[1] Listar todos\n[2] Listar por CPF");
	printf("\n[3] Incluir\n[4] Alterar\n[5] Excluir\n");
}

//===================================================
//Fun��o para verificar a exist�ncia de um CPF
int buscar_cpf(char *cpf)
{
	USUARIOS *user;
	user=(USUARIOS *) calloc(1, sizeof(USUARIOS));
	FILE *arqUSUARIOS;
	if((arqUSUARIOS=fopen("registro_usuarios.txt", "rb"))==NULL)
		return -1;
	else
	{
		int i=0, verif=0;
		fread(user, sizeof(USUARIOS), 1, arqUSUARIOS);
		while(!feof(arqUSUARIOS) && verif==0)
		{
			if(strcmp(user->CPF, cpf)==0)
			{
				verif=1;
				return i;
			}
			i++;
			fread(user, sizeof(USUARIOS), 1, arqUSUARIOS);
		}		
		return -1;
	}
	free(user);
	fclose(arqUSUARIOS);
}

//===================================================
//[1][1]
//Fun��o para listar todos os usu�rios
void listar_usuarios()
{
	USUARIOS *user;
	FILE *arqUSUARIOS;
	if((arqUSUARIOS=fopen("registro_usuarios.txt", "rb"))==NULL)
	{
		printf("N�o h� usu�rios cadastrados.");
		exit(1);
	}
	else
	{
		//Comando de leitura de arquivo bin�rio (um por vez, at� chegar ao fim (EOF)
		//Necess�rio fread antes e no final do la�o para garantir que todas posi��es sejam lidas
		fread(user, sizeof(USUARIOS), 1, arqUSUARIOS);
		while(!feof(arqUSUARIOS))
		{
			printf("\nNome: %s", user->NOME);
			printf("\nCPF: %s", user->CPF);
			printf("\nRua: %s", user->RUA);
			printf("\tn� %s", user->NRO);
			printf("\nCEP: %s", user->CEP);
			printf("\nE-mail: %s", user->MAIL);	
			printf("\nTelefone: %s", user->FONE);
			printf("\nData de Nascimento: %d/%d/%d", user->NASC.DIA,user->NASC.MES, user->NASC.ANO);
			printf("\nProfiss�o: %s", user->PROF);
			printf("\n\n-------------------------------");
			fread(user, sizeof(USUARIOS), 1, arqUSUARIOS);
		}
	}
	fclose(arqUSUARIOS);
}

//===================================================
//[1][2]
//Fun��o para listar os dados de um usu�rio de acordo com seu CPF
void listar_cpf()
{
	USUARIOS *user;
	user=(USUARIOS *) calloc(1, sizeof(USUARIOS));
	int pos=-1;
	char cpf[15];
	fflush(stdin);
	printf("\nDeseja listar o cadastro de qual CPF [incluir pontua��o]: ");
	gets(cpf);
	pos=buscar_cpf(cpf);
	if(pos!=-1)
	{
		FILE *arqUSUARIOS;
		if((arqUSUARIOS=fopen("registro_usuarios.txt", "rb"))==NULL)
		{
			printf("N�o foi poss�vel abrir os cadastros dos usu�rios.");
			exit(1);
		}
		else
		{
			//Comando de leitura de arquivo bin�rio (um por vez, at� chegar ao fim (EOF)
			//Necess�rio fread antes e no final do la�o para garantir que todas posi��es sejam lidas
			//Neste caso a vari�vel i funciona como se fosse um contador
			int i=0, verif=0;
			fread(user, sizeof(USUARIOS), 1, arqUSUARIOS);
			while(!feof(arqUSUARIOS) && verif==0)
			{
				if(i!=pos)
				{
					i++;
					fread(user, sizeof(USUARIOS), 1, arqUSUARIOS);
				}
				else
				{
					printf("\nNome: %s", user->NOME);					
					printf("\nCPF: %s", user->CPF);
					printf("\nRua: %s", user->RUA);
					printf("\tn� %s", user->NRO);
					printf("\nCEP: %s", user->CEP);
					printf("\nE-mail: %s", user->MAIL);	
					printf("\nTelefone: %s", user->FONE);
					printf("\nData de Nascimento: %d/%d/%d", user->NASC.DIA,user->NASC.MES, user->NASC.ANO);
					printf("\nProfiss�o: %s", user->PROF);
					printf("\n\n-------------------------------");
					verif=1;
				}
			}
		}
		free(user);
		fclose(arqUSUARIOS);
	}
	else
		printf("\nCPF %s n�o encontrado!", cpf);
}

//===================================================
//[1][3]
//Fun��o para cadastrar um usu�rio
void incluir_usuario()
{
	USUARIOS *user;
	int pos=0;
	char cpf[15];
	fflush(stdin);
	while(pos!=-1)
	{
		printf("\nCPF [incluir pontua��o]: ");
		gets(cpf);
		pos=buscar_cpf(cpf);
		if(pos!=-1)
			printf("\n\t*** ATEN��O! ***\nCPF EXISTENTE. Tente novamente\n\t****************\n");
	}
	strcpy(user->CPF, cpf);
	printf("Nome: ");
	gets(user->NOME);
	printf("Rua: ");
	gets(user->RUA);
	printf("n� ");
	gets(user->NRO);
	printf("CEP: ");
	gets(user->CEP);
	fflush(stdin);
	printf("E-mail: ");
	gets(user->MAIL);
	printf("Telefone: ");
	gets(user->FONE);
	fflush(stdin);
	printf("DATA DE NASCIMENTO");
	printf("\nDia [dd]: ");
	scanf("%d", &user->NASC.DIA);
	printf("M�s [mm]: ");
	scanf("%d", &user->NASC.MES);
	printf("Ano [aaaa]: ");
	scanf("%d", &user->NASC.ANO);
	fflush(stdin);
	printf("Profiss�o: ");
	gets(user->PROF);
	
	//Manipula��o de arquivos dos usu�rios. Salvar os dados no arquivo registro_usuarios.txt
	FILE *arqUSUARIOS;
	if((arqUSUARIOS=fopen("registro_usuarios.txt", "ab"))==NULL)
	{
		printf("N�o foi poss�vel abrir o arquivo.");
		exit(1);
	}
	else
		fwrite(user, sizeof(USUARIOS), 1, arqUSUARIOS);
	fflush(stdin);
	fclose(arqUSUARIOS);	
}

//===================================================
//[1][4]
//Fun��o para alterar um usu�rio
void alterar_usuario()
{
	USUARIOS *user;
	user=(USUARIOS *) calloc(1, sizeof(USUARIOS));
	int pos;
	char cpf[15];
	fflush(stdin);
	printf("\nCPF [incluir pontua��o]: ");
	gets(cpf);
	pos=buscar_cpf(cpf);
	if(pos!=-1)
	{
		FILE *arqUSUARIOS;
		if((arqUSUARIOS=fopen("registro_usuarios.txt", "rb+"))==NULL)
		{
			printf("N�o foi poss�vel abrir os cadastros dos usu�rios.");
			exit(1);
		}
		else
		{
			//Comando de leitura e escrita de arquivo bin�rio (um por vez, at� chegar ao fim (EOF)
			//A vari�vel i representa a parada do la�o
			//M�todo fseek utilizando o tipo current (ponto corrente do arquivo), sem pular bytes uma vez que se deseja editar o ponteiro corrente
			int i=0, verif=0;
			while(!feof(arqUSUARIOS) && verif==0)
			{
				if(i!=pos)
				{
					i++;
					fread(user, sizeof(USUARIOS), 1, arqUSUARIOS);
				}
				else
				{
					strcpy(user->CPF, cpf);
					printf("Nome: ");
					gets(user->NOME);
					printf("Rua: ");
					gets(user->RUA);
					printf("n� ");
					gets(user->NRO);
					printf("CEP: ");
					gets(user->CEP);
					fflush(stdin);
					printf("E-mail: ");
					gets(user->MAIL);
					printf("Telefone: ");
					gets(user->FONE);
					fflush(stdin);
					printf("Data de Nascimento [dd/mm/aaaa]");
					printf("\nDia: ");
					scanf("%d", &user->NASC.DIA);
					printf("M�s: ");
					scanf("%d", &user->NASC.MES);
					printf("Ano: ");
					scanf("%d", &user->NASC.ANO);
					fflush(stdin);
					printf("Profiss�o: ");
					gets(user->PROF);
					fseek(arqUSUARIOS, 0, SEEK_CUR);
					fwrite(user, sizeof(USUARIOS), 1, arqUSUARIOS);
					verif=1;
					free(user);
					fclose(arqUSUARIOS);
					fflush(stdin);
					printf("\nUsu�rio alterado com sucesso.");
				}
			}
		}
	}
	else
		printf("\nCPF %s n�o encontrado!", cpf);
}

//===================================================
//[1][5]
//Fun��o para excluir um usu�rio
void excluir_usuario()
{
	USUARIOS *user;
	user=(USUARIOS *) calloc(1, sizeof(USUARIOS));
	int pos, i;
	char cpf[15];
	fflush(stdin);
	printf("\nCPF [incluir pontua��o]: ");
	gets(cpf);
	pos=buscar_cpf(cpf);
	if(pos!=-1)
	{
		FILE *arqUSUARIOS;
		if((arqUSUARIOS=fopen("registro_usuarios.txt", "rb+"))==NULL)
		{
			printf("N�o foi poss�vel abrir os cadastros dos usu�rios.");
			exit(1);
		}
		else
		{
			//Comando de leitura e escrita de arquivo bin�rio (um por vez, at� chegar ao fim (EOF)
			//A vari�vel i representa a parada do la�o
			//A vari�vel cont representa a quantidade de registros existentes ap�s a leitura do arquivo
			//M�todo fseek utilizando o tipo current (ponto corrente do arquivo), sem pular bytes uma vez que se deseja editar o ponteiro corrente
			int i=0, verif=0, cont;
			while(!feof(arqUSUARIOS) && verif==0)
			{
				if(i!=pos)
				{
					i++;
					fread(user, sizeof(USUARIOS), 1, arqUSUARIOS);
				}
				else
				{
					fseek(arqUSUARIOS, 0, SEEK_CUR);
					int flag=0;
					while(!feof(arqUSUARIOS) && flag==0)
					{
						user[i]=user[i+1];
						fwrite(user+i, sizeof(USUARIOS), 1, arqUSUARIOS);
						flag=1;
					}
					verif=1;
					free(user);
					fclose(arqUSUARIOS);
					fflush(stdin);
					printf("\nUsu�rio removido com sucesso!\n\n");
				}
			}
		}
	}
	else
		printf("\nCPF %s n�o encontrado!", cpf);
}		

//===================================================
//[2]
//Fun��o para apresentar o submenu de livros
void menu_livro()
{
	system("cls");
	printf("\t=== SUBMENU DE OP��ES - LIVROS ===\n\n[1] Listar todos\n[2] Listar por ISBN");
	printf("\n[3] Incluir\n[4] Alterar\n[5] Excluir\n");
}

//===================================================
//Fun��o para verificar a exist�ncia de um ISBN
int buscar_isbn(char *isbn)
{
	LIVROS *book;
	book=(LIVROS *) calloc(1, sizeof(LIVROS));
	FILE *arqLIVROS;
	if((arqLIVROS=fopen("registro_livros.txt", "rb"))==NULL)
		return -1;
	else
	{
		int i=0, verif=0;
		fread(book, sizeof(LIVROS), 1, arqLIVROS);
		while(!feof(arqLIVROS) && verif==0)
		{
			if(strcmp(book->ISBN, isbn)==0)
			{
				verif=1;
				return i;
			}
			i++;
			fread(book, sizeof(LIVROS), 1, arqLIVROS);
		}		
		return -1;
	}
	fclose(arqLIVROS);
}

//===================================================
//[2][1]
//Fun��o para listar todos os livros
void listar_livros()
{
	LIVROS *book;
	book=(LIVROS *) calloc(1, sizeof(LIVROS));
	FILE *arqLIVROS;
	if((arqLIVROS=fopen("registro_livros.txt", "rb"))==NULL)
	{
		printf("N�o h� livros cadastrados.");
		exit(1);
	}
	else
	{
		//Comando de leitura de arquivo bin�rio (um por vez, at� chegar ao fim (EOF)
		//Necess�rio fread antes e no final do la�o para garantir que todas posi��es sejam lidas
		//A vari�vel i representa a parada de contagem dos autores
		fread(book, sizeof(LIVROS), 1, arqLIVROS);
		int i;
		while(!feof(arqLIVROS))
		{
			printf("\nT�tulo: %s", book->TITULO);
			printf("\nISBN: %s", book->ISBN);
			printf("\nG�nero: %s", book->GENERO);
			printf("\nAutor(es):");
			for(i=0; i<book->CONT_AUTORES; i++)
			{
				printf("\n\t%s", book->AUTORES[i]);
			}
			printf("\nN�mero de p�ginas: %d", book->NRO_PAG);
			printf("\n\n-------------------------------");
			fread(book, sizeof(LIVROS), 1, arqLIVROS);
		}
	}
	free(book);
	fclose(arqLIVROS);	
}

//===================================================
//[2][2]
//Fun��o para listar os dados de um livro de acordo com seu ISBN
void listar_isbn()
{
	LIVROS *book;
	book=(LIVROS *) calloc(1, sizeof(LIVROS));
	int pos=-1;
	char isbn[20];
	fflush(stdin);
	printf("\nDeseja listar o cadastro de qual ISBN [incluir pontua��o]: ");
	gets(isbn);
	pos=buscar_isbn(isbn);
	if(pos!=-1)
	{
		FILE *arqLIVROS;
		if((arqLIVROS=fopen("registro_livros.txt", "rb"))==NULL)
		{
			printf("N�o foi poss�vel abrir os cadastros dos livros.");
			exit(1);
		}
		else
		{
			//Comando de leitura de arquivo bin�rio (um por vez, at� chegar ao fim (EOF)
			//Necess�rio fread antes e no final do la�o para garantir que todas posi��es sejam lidas
			//Neste caso a vari�vel i funciona como se fosse um contador
			int i=0, verif=0, j;
			fread(book, sizeof(LIVROS), 1, arqLIVROS);
			while(!feof(arqLIVROS) && verif==0)
			{
				if(i!=pos)
				{
					i++;
					fread(book, sizeof(LIVROS), 1, arqLIVROS);
				}
				else
				{
					printf("\nT�tulo: %s", book->TITULO);
					printf("\nISBN: %s", book->ISBN);
					printf("\nG�nero: %s", book->GENERO);
					printf("\nAutor(es):");
					for(j=0; j<book->CONT_AUTORES; j++)
					{
						printf("\n\t%s", book->AUTORES[j]);
					}
					printf("\nN�mero de p�ginas: %d", book->NRO_PAG);
					printf("\n\n-------------------------------");
					verif=1;
				}
			}
		}
		free(book);
		fclose(arqLIVROS);
	}
	else
		printf("\nISBN %s n�o encontrado!", isbn);
}

//===================================================
//[2][3]
//Fun��o para cadastrar um livro
void incluir_livro()
{
	LIVROS *book;
	book=(LIVROS *) calloc(1, sizeof(LIVROS));
	int pos=0, *cont_autores=0;
	cont_autores=&book->CONT_AUTORES;
	char isbn[20], resp;
	fflush(stdin);
	while(pos!=-1)
	{
		printf("\nISBN [incluir pontua��o]: ");
		gets(isbn);
		pos=buscar_isbn(isbn);
		if(pos!=-1)
			printf("\n\t*** ATEN��O! ***\nISBN EXISTENTE. Tente novamente\n\t****************\n");
	}
	strcpy(book->ISBN, isbn);
	printf("T�tulo: ");
	gets(book->TITULO);
	printf("G�nero: ");
	gets(book->GENERO);
	printf("Autor(a) %d: ", *cont_autores+1);
	gets(book->AUTORES[*cont_autores]);
	(*cont_autores)++;
	printf("Voc� ainda pode adicionar %d autores. ", 5-*cont_autores);
	printf("Deseja adicionar outro(a) autor(a) [S/N]: ");
	scanf("%c", &resp);
	while(resp=='S' || resp=='s' && *cont_autores<5) //O inteiro 5 � devido ao tamanho do vetor bidimensional pr�-definido
	{
		fflush(stdin);
		printf("Autor(a) %d: ", *cont_autores+1);
		gets(book->AUTORES[*cont_autores]);
		(*cont_autores)++;
		if(*cont_autores<5)
		{
			fflush(stdin);
			printf("Voc� ainda pode adicionar %d autores. ", 5-*cont_autores);
			printf("Deseja adicionar outro(a) autor(a) [S/N]: ");
			scanf("%c", &resp);
		}
	}
	printf("N�mero de p�ginas: ");
	scanf("%d", &book->NRO_PAG);

	//Manipula��o de arquivos dos livros. Salvar os dados no arquivo registro_livros.txt
	FILE *arqLIVROS;
	if((arqLIVROS=fopen("registro_livros.txt", "ab"))==NULL)
	{
		printf("N�o foi poss�vel abrir o arquivo.");
		exit(1);
	}
	else
		fwrite(book, sizeof(LIVROS), 1, arqLIVROS);
	fflush(stdin);
	free(book);
	fclose(arqLIVROS);	
}

//===================================================
//[2][4]
//Fun��o para alterar um livro
void alterar_livro()
{
	LIVROS *book;
	book=(LIVROS *) calloc(1, sizeof(LIVROS));
	int pos=0, *cont_autores=0;
	cont_autores=&book->CONT_AUTORES;
	char isbn[20], resp;
	fflush(stdin);
	printf("\nISBN [incluir pontua��o]: ");
	gets(isbn);
	pos=buscar_isbn(isbn);
	if(pos!=-1)
	{
		FILE *arqLIVROS;
		if((arqLIVROS=fopen("registro_livros.txt", "rb+"))==NULL)
		{
			printf("N�o foi poss�vel abrir os cadastros dos livros.");
			exit(1);
		}
		else
		{
			//Comando de leitura e escrita de arquivo bin�rio (um por vez, at� chegar ao fim (EOF)
			//A vari�vel i representa a parada do la�o
			//M�todo fseek utilizando o tipo current (ponto corrente do arquivo), sem pular bytes uma vez que se deseja editar o ponteiro corrente
			int i=0, verif=0;
			while(!feof(arqLIVROS) && verif==0)
			{
				if(i!=pos)
				{
					i++;
					fread(book, sizeof(LIVROS), 1, arqLIVROS);
				}
				else
				{
					*cont_autores=0;
					printf("T�tulo: ");
					gets(book->TITULO);
					printf("G�nero: ");
					gets(book->GENERO);
					printf("Autor(a) %d: ", *cont_autores+1);
					gets(book->AUTORES[*cont_autores]);
					(*cont_autores)++;
					printf("Voc� ainda pode adicionar %d autores. ", 5-*cont_autores);
					printf("Deseja adicionar outro(a) autor(a) [S/N]: ");
					scanf("%c", &resp);
					while(resp=='S' || resp=='s' && *cont_autores<5) //O inteiro 5 � devido ao tamanho do vetor bidimensional pr�-definido
					{
						fflush(stdin);
						printf("Autor(a) %d: ", *cont_autores+1);
						gets(book->AUTORES[*cont_autores]);
						(*cont_autores)++;
						if(*cont_autores<5)
						{
							fflush(stdin);
							printf("Voc� ainda pode adicionar %d autores. ", 5-*cont_autores);
							printf("Deseja adicionar outro(a) autor(a) [S/N]: ");
							scanf("%c", &resp);
						}
					}
					printf("N�mero de p�ginas: ");
					scanf("%d", &book->NRO_PAG);
					fseek(arqLIVROS, 0, SEEK_CUR);
					fwrite(book, sizeof(LIVROS), 1, arqLIVROS);
					verif=1;
					free(book);
					fclose(arqLIVROS);
					fflush(stdin);
					printf("\nLivro alterado com sucesso.");
				}
			}
		}
	}
	else
		printf("\nISBN %s n�o encontrado!", isbn);
}

//===================================================
//[2][5]
//Fun��o para excluir um livro
void excluir_livro()
{
	LIVROS *book;
	book=(LIVROS *) calloc(1, sizeof(LIVROS));
	int pos=0, *cont_autores=0;
	cont_autores=&book->CONT_AUTORES;
	char isbn[20], resp;
	fflush(stdin);
	printf("\nISBN [incluir pontua��o]: ");
	gets(isbn);
	pos=buscar_isbn(isbn);
	if(pos!=-1)
	{
		FILE *arqLIVROS;
		if((arqLIVROS=fopen("registro_livros.txt", "rb+"))==NULL)
		{
			printf("N�o foi poss�vel abrir os cadastros dos livros.");
			exit(1);
		}
		else
		{
			//Comando de leitura e escrita de arquivo bin�rio (um por vez, at� chegar ao fim (EOF)
			//A vari�vel i representa a parada do la�o
			//M�todo fseek utilizando o tipo current (ponto corrente do arquivo), sem pular bytes uma vez que se deseja editar o ponteiro corrente
			int i=0, verif=0;
			while(!feof(arqLIVROS) && verif==0)
			{
				if(i!=pos)
				{
					i++;
					fread(book, sizeof(LIVROS), 1, arqLIVROS);
				}
				else
				{
					fseek(arqLIVROS, 0, SEEK_CUR);
					int flag=0;
					while(!feof(arqLIVROS) && flag==0)
					{
						book[i]=book[i+1];
						fwrite(book+i, sizeof(LIVROS), 1, arqLIVROS);
						flag=1;
					}
					verif=1;
					free(book);
					fclose(arqLIVROS);
					fflush(stdin);
					printf("\nLivro removido com sucesso!\n\n");
				}
			}
		}
	}
	else
		printf("\nISBN %s n�o encontrado!", isbn);
}

//===================================================
//[3]
//Fun��o para apresentar o submenu de empr�stimos
void menu_emprestimo()
{
	system("cls");
	printf("\t=== SUBMENU DE OP��ES - EMPR�STIMOS ===\n\n[1] Listar todos\n[2] Listar por CPF, ISBN e Data");
	printf("\n[3] Incluir\n[4] Alterar\n[5] Excluir\n");
}

//===================================================
//Fun��o para verificar a exist�ncia da data de retirada de um empr�stimo
int buscar_emprestimo(char *cpf, char *isbn, int *d, int *m, int *a)
{
	EMPRESTIMOS *loan;
	loan=(EMPRESTIMOS *) calloc(1, sizeof(EMPRESTIMOS));
	FILE *arqEMPRESTIMOS;
	if((arqEMPRESTIMOS=fopen("registro_emprestimos.txt", "rb"))==NULL)
	{
		printf("N�o h� empr�stimos cadastrados.");
		exit(1);
	}
	else
	{
		int i, verif=0;
		fread(loan, sizeof(EMPRESTIMOS), 1, arqEMPRESTIMOS);
		while(!feof(arqEMPRESTIMOS) && verif==0)
		{
			if((loan->CPF, cpf)==0 && (loan->ISBN, isbn)==0 && loan->RETIRADA.DIA==*d && loan->RETIRADA.MES==*m && loan->RETIRADA.ANO==*a)
			{
				verif=1;
				return i;
			}
			i++;
			fread(loan, sizeof(EMPRESTIMOS), 1, arqEMPRESTIMOS);			
		}
		return -1;
	}
	fclose(arqEMPRESTIMOS);
}

//===================================================
//[3][1]
//Fun��o para listar todos os empr�stimos
void listar_emprestimos()
{
	EMPRESTIMOS *loan;
	loan=(EMPRESTIMOS *) calloc(1, sizeof(EMPRESTIMOS));
	FILE *arqEMPRESTIMOS;
	if((arqEMPRESTIMOS=fopen("registro_emprestimos.txt", "rb"))==NULL)
	{
		printf("N�o h� empr�stimos cadastrados.");
		exit(1);
	}
	else
	{
		//Comando de leitura de arquivo bin�rio (um por vez, at� chegar ao fim (EOF)
		//Necess�rio fread antes e no final do la�o para garantir que todas posi��es sejam lidas
		fread(loan, sizeof(EMPRESTIMOS), 1, arqEMPRESTIMOS);
		while(!feof(arqEMPRESTIMOS))
		{
			printf("\nCPF: %s", loan->CPF);
			printf("\nISBN: %s", loan->ISBN);
			printf("\nData de Retirada: %d/%d/%d", loan->RETIRADA.DIA, loan->RETIRADA.MES, loan->RETIRADA.ANO);
			printf("\nData de Devolu��o: %d/%d/%d", loan->DEVOLUCAO.DIA, loan->DEVOLUCAO.MES, loan->DEVOLUCAO.ANO);
			printf("\nMulta: R$%.2f/dia", loan->MULTA);
			printf("\n\n-------------------------------");
			fread(loan, sizeof(EMPRESTIMOS), 1, arqEMPRESTIMOS);
		}
	}
	free(loan);
	fclose(arqEMPRESTIMOS);				
}

//===================================================
//[3][2]
//Fun��o para listar os dados de um empr�stimo de acordo com o CPF, ISBN e Data de Retirada
void listar_emprestimo_chave()
{
	USUARIOS *user;
	//user=(USUARIOS *) calloc(1, sizeof(USUARIOS));
	LIVROS *book;
	//book=(LIVROS *) calloc(1, sizeof(LIVROS));
	EMPRESTIMOS *loan;
	//loan=(EMPRESTIMOS *) calloc(1, sizeof(LIVROS));
	//int *cont_user, int *cont_book, int *cont_loan
	int pos_cpf, pos_isbn, pos_emprestimo, dia, mes, ano;
	char cpf[15], isbn[20], retirada[11];
	fflush(stdin);
	printf("\nDeseja listar o empr�stimo de qual CPF [incluir pontua��o]: ");
	gets(cpf);
	pos_cpf=buscar_cpf(cpf);
	if(pos_cpf!=-1)
	{
		printf("Informe o ISBN do empr�stimo deseja consultar [incluir pontua��o]: ");
		gets(isbn);
		pos_isbn=buscar_isbn(isbn);
		if(pos_isbn!=-1)
		{
			printf("\nDATA DE RETIRADA");
			printf("\nDia [dd]: ");
			scanf("%d", &dia);
			printf("M�s [mm]: ");
			scanf("%d", &mes);
			printf("Ano [aaaa]: ");
			scanf("%d", &ano);
			pos_emprestimo=buscar_emprestimo(cpf, isbn, &dia, &mes, &ano);
			if(pos_emprestimo!=-1)
			{
				printf("\nNome: %s", user[pos_cpf].NOME);
				printf("\nCPF: %s", loan[pos_emprestimo].CPF);
				printf("\nT�tulo: %s", book[pos_isbn].TITULO);
				printf("\nISBN: %s", loan[pos_emprestimo].ISBN);
				printf("\nData de Retirada: %d/%d/%d", loan[pos_emprestimo].RETIRADA.DIA, loan[pos_emprestimo].RETIRADA.MES, loan[pos_emprestimo].RETIRADA.ANO);
				printf("\nData de Devolu��o: %d/%d/%d", loan[pos_emprestimo].DEVOLUCAO.DIA, loan[pos_emprestimo].DEVOLUCAO.MES, loan[pos_emprestimo].DEVOLUCAO.ANO);
				printf("\nMulta: R$%.2f/dia", loan[pos_emprestimo].MULTA);
				printf("\n\n-------------------------------");	
			}
			else
				printf("\nN�o h� empr�stimos com o CPF e o ISBN na data solicitada.");
		}
		else
			printf("\nISBN %s n�o encontrado!", isbn);
	}
	else
		printf("\nCPF %s n�o encontrado!", cpf);
}

//===================================================
//[3][3]
//Fun��o para cadastrar um empr�stimo
void incluir_emprestimo(USUARIOS *user, LIVROS *book, EMPRESTIMOS *loan, int *cont_user, int *cont_book, int *cont_loan)
{
	int pos_cpf, pos_isbn, pos_emprestimo, dia, mes, ano;
	char cpf[15], isbn[20], retirada[11];
	fflush(stdin);
	printf("\nCPF [incluir pontua��o]: ");
	gets(cpf);
	//pos_cpf=buscar_cpf(user, cpf, cont_user);
	if(pos_cpf!=-1)
	{
		printf("Informe o ISBN do empr�stimo deseja consultar [incluir pontua��o]: ");
		gets(isbn);
		//pos_isbn=buscar_isbn(book, isbn, cont_book);
		if(pos_isbn!=-1)
		{
			printf("\nDATA DE RETIRADA");
			printf("\nDia [dd]: ");
			scanf("%d", &dia);
			printf("M�s [mm]: ");
			scanf("%d", &mes);
			printf("Ano [aaaa]: ");
			scanf("%d", &ano);
			//pos_emprestimo=buscar_emprestimo(loan, cpf, isbn, &dia, &mes, &ano, cont_loan);
			if(pos_emprestimo==-1)
			{
				strcpy(loan[*cont_loan].CPF, cpf);
				strcpy(loan[*cont_loan].ISBN, isbn);
				loan[*cont_loan].RETIRADA.DIA=dia;
				loan[*cont_loan].RETIRADA.MES=mes;
				loan[*cont_loan].RETIRADA.ANO=ano;
				printf("\nDATA DE DEVOLU��O");
				printf("\nDia [dd]: ");
				scanf("%d", &loan[*cont_loan].DEVOLUCAO.DIA);
				printf("M�s [mm]: ");
				scanf("%d", &loan[*cont_loan].DEVOLUCAO.MES);
				printf("Ano [aaaa]: ");
				scanf("%d", &loan[*cont_loan].DEVOLUCAO.ANO);
				printf("Valor da Multa: R$");
				scanf("%f", &loan[*cont_loan].MULTA);
				fflush(stdin);
				printf("\nEmpr�stimo cadastrado com sucesso.");
				(*cont_loan)++;
			}
			else
				printf("\n\t*** ATEN��O! ***\nJ� existem empr�stimos com o CPF e o ISBN na data solicitada. Tente novamente\n\t****************\n");
		}
		else
			printf("\n\t*** ATEN��O! ***\nISBN N�O ENCONTRADO. Tente novamente\n\t****************\n");
	}
	else
		printf("\n\t*** ATEN��O! ***\nCPF N�O ENCONTRADO. Tente novamente\n\t****************\n");
}

//===================================================
//[3][4]
//Fun��o para alterar um empr�stimo
void alterar_emprestimo(USUARIOS *user, LIVROS *book, EMPRESTIMOS *loan, int *cont_user, int *cont_book, int *cont_loan)
{
	int pos_cpf, pos_isbn, pos_emprestimo, dia, mes, ano;
	char cpf[15], isbn[20], retirada[11];
	fflush(stdin);
	printf("\nDeseja listar o empr�stimo de qual CPF [incluir pontua��o]: ");
	gets(cpf);
	//pos_cpf=buscar_cpf(user, cpf, cont_user);
	if(pos_cpf!=-1)
	{
		printf("Informe o ISBN do empr�stimo deseja consultar [incluir pontua��o]: ");
		gets(isbn);
		//pos_isbn=buscar_isbn(book, isbn, cont_book);
		if(pos_isbn!=-1)
		{
			printf("\nDATA DE RETIRADA");
			printf("\nDia [dd]: ");
			scanf("%d", &dia);
			printf("M�s [mm]: ");
			scanf("%d", &mes);
			printf("Ano [aaaa]: ");
			scanf("%d", &ano);
			//pos_emprestimo=buscar_emprestimo(loan, cpf, isbn, &dia, &mes, &ano, cont_loan);
			if(pos_emprestimo!=-1)
			{
				printf("\nDATA DE DEVOLU��O");
				printf("\nDia [dd]: ");
				scanf("%d", &loan[pos_emprestimo].DEVOLUCAO.DIA);
				printf("M�s [mm]: ");
				scanf("%d", &loan[pos_emprestimo].DEVOLUCAO.MES);
				printf("Ano [aaaa]: ");
				scanf("%d", &loan[pos_emprestimo].DEVOLUCAO.ANO);
				printf("Valor da Multa: R$");
				scanf("%f", &loan[pos_emprestimo].MULTA);
				fflush(stdin);
				printf("\nEmpr�stimo alterado com sucesso.");			
			}
			else
				printf("\nN�o h� empr�stimos com o CPF e o ISBN na data solicitada.");
		}
		else
			printf("\nISBN %s n�o encontrado!", isbn);
	}
	else
		printf("\nCPF %s n�o encontrado!", cpf);
}

//===================================================
//[3][5]
//Fun��o para excluir um empr�stimo
void excluir_emprestimo(USUARIOS *user, LIVROS *book, EMPRESTIMOS *loan, int *cont_user, int *cont_book, int *cont_loan)
{
	int pos_cpf, pos_isbn, pos_emprestimo, dia, mes, ano, i;
	char cpf[15], isbn[20], retirada[11];
	fflush(stdin);
	printf("\nDeseja listar o empr�stimo de qual CPF [incluir pontua��o]: ");
	gets(cpf);
	//pos_cpf=buscar_cpf(user, cpf, cont_user);
	if(pos_cpf!=-1)
	{
		printf("Informe o ISBN do empr�stimo deseja consultar [incluir pontua��o]: ");
		gets(isbn);
		//pos_isbn=buscar_isbn(book, isbn, cont_book);
		if(pos_isbn!=-1)
		{
			printf("\nDATA DE RETIRADA");
			printf("\nDia [dd]: ");
			scanf("%d", &dia);
			printf("M�s [mm]: ");
			scanf("%d", &mes);
			printf("Ano [aaaa]: ");
			scanf("%d", &ano);
			//pos_emprestimo=buscar_emprestimo(loan, cpf, isbn, &dia, &mes, &ano, cont_loan);
			if(pos_emprestimo!=-1)
			{
				for(i=pos_emprestimo; i<*cont_loan-1; i++)
					loan[i]=loan[i+1];
				printf("\nUsu�rio removido com sucesso!\n\n");
					(*cont_loan)--;						
			}
			else
				printf("\nN�o h� empr�stimos com o CPF e o ISBN na data solicitada.");
		}
		else
			printf("\nISBN %s n�o encontrado!", isbn);
	}
	else
		printf("\nCPF %s n�o encontrado!", cpf);
}

//===================================================
//[4]
//Fun��o para apresentar o submenu de relat�rios
void menu_relatorio()
{
	system("cls");
	printf("\t=== SUBMENU DE OP��ES - RELAT�RIOS ===\n\n[1] Listar usu�rios por idade");
	printf("\n[2] Listar livros por n�mero de autores");
	printf("\n[3] Listar empr�stimos por per�odo de devolu��o\n");
}

//===================================================
//[4][1]
//Fun��o para listar o relat�rio dos usu�rios de acordo com sua idade
void listar_idade()
{
	USUARIOS *user;
	user=(USUARIOS *) calloc(1, sizeof(USUARIOS));
	int idade, total_idade, anos;
	int dia_atual, mes_atual, ano_atual;
	printf("\nDeseja listar os usu�rios a partir de que idade? ");
	scanf("%d", &idade);
	time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);
    dia_atual=tm.tm_mday;
	mes_atual=tm.tm_mon+1;
	ano_atual=tm.tm_year+1900;
	FILE *arqIDADE;
	arqIDADE=fopen("relatorio_idade.txt", "w"); //N�o � necess�rio verificar a exist�ncia, uma vez que o m�todo � write
	FILE *arqUSUARIOS;
	if((arqUSUARIOS=fopen("registro_usuarios.txt", "rb"))==NULL)
	{
			printf("N�o foi poss�vel abrir os cadastros dos usu�rios.");
			exit(1);
	}
	else
	{
		system("cls");
		printf("\n\t=== LISTAR USU�RIOS - MAIORES QUE %d ANOS ===\n", idade);
		int verif=0;
		fread(user, sizeof(USUARIOS), 1, arqUSUARIOS);
		while(!feof(arqUSUARIOS))
		{
			total_idade=365*ano_atual+30*mes_atual+dia_atual-365*user->NASC.ANO-30*user->NASC.MES-user->NASC.DIA;
			anos=total_idade/365;
			if(anos>=idade)
			{
				printf("\nNome: %s", user->NOME);
				printf("\nCPF: %s", user->CPF);
				printf("\nRua: %s", user->RUA);
				printf("\tn� %s", user->NRO);
				printf("\nCEP: %s", user->CEP);
				printf("\nE-mail: %s", user->MAIL);	
				printf("\nTelefone: %s", user->FONE);
				printf("\nData de Nascimento: %d/%d/%d", user->NASC.DIA,user->NASC.MES, user->NASC.ANO);
				printf("\tIdade: %d anos", anos);
				printf("\nProfiss�o: %s", user->PROF);
				printf("\n\n-------------------------------");
				fwrite(user, sizeof(USUARIOS), 1, arqIDADE);
				verif=1;
			}
			fread(user, sizeof(USUARIOS), 1, arqUSUARIOS);
		}
		free(user);
		fclose(arqIDADE);
		fclose(arqUSUARIOS);
		if(verif==0)
			printf("\nOs usu�rios cadastrados s�o menores que %d anos.", idade);
	}
}

//===================================================
//[4][2]
//Fun��o para listar o relat�rio dos livros de acordo com o n�mero de autores
void listar_autores()
{
	LIVROS *book;
	book=(LIVROS *) calloc(1, sizeof(LIVROS));
	int autores;
	printf("\nDeseja listar os livros que possuem quantos (ou mais) autores? ");
	scanf("%d", &autores);
	FILE *arqAUTORES;
	arqAUTORES=fopen("relatorio_autores.txt", "w"); //N�o � necess�rio verificar a exist�ncia, uma vez que o m�todo � write
	FILE *arqLIVROS;
	if((arqLIVROS=fopen("registro_livros.txt", "rb"))==NULL)
	{
			printf("N�o foi poss�vel abrir os cadastros dos livros.");
			exit(1);
	}
	else
	{
		system("cls");
		printf("\n\t=== LISTAR LIVROS - MAIS QUE %d AUTORES ===\n", autores);
		int i, *cont_autores=0, verif=0; //, 
		fread(book, sizeof(LIVROS), 1, arqLIVROS);
		while(!feof(arqLIVROS))
		{
			if(book->CONT_AUTORES>=autores)
			{
				printf("\nT�tulo: %s", book->TITULO);
				printf("\nISBN: %s", book->ISBN);
				printf("\nG�nero: %s", book->GENERO);
				printf("\nAutor(es):");
				cont_autores=&book->CONT_AUTORES;
				for(i=0; i<*cont_autores; i++)
					printf("\n\t%s", book->AUTORES[i]);
				printf("\nN�mero de p�ginas: %d", book->NRO_PAG);
				fwrite(book, sizeof(LIVROS), 1, arqAUTORES);
				printf("\n\n-------------------------------");			
				verif=1;
			}
			fread(book, sizeof(LIVROS), 1, arqLIVROS);
		}
		free(book);
		fclose(arqAUTORES);
		fclose(arqLIVROS);
		if(verif==0)
			printf("\nOs livros cadastrados possuem menos que %d autores.", autores);
	}
}

//===================================================
//Para realizar opera��es entre as datas ser� utilizado o c�lculo dos dias julianos
//Os dias julianos � um m�todo para contar os dias sequencialmente.
//S�o muito �teis porque facilitam a opera��o entre dias.
//Tais opera��es s�o mais dif�ceis no calend�rio padr�o (gregoriano), pois s�o
//agrupados em meses, podem conter um n�mero vari�vel de dias, al�m das complica��es dos anos bissextos.        
//DJ = D - 32075 + 1461*( A + 4800 + ( M - 14 ) / 12 ) / 4 + 367*( M - 2 - ( M - 14 ) / 12 * 12 ) / 12 - 3*( ( A + 4900 + ( M - 14 ) / 12 ) / 100 ) / 4
//DJ: dia juliano; A: ano; M: m�s; D: dia
//Exemplo: 01/01/1970 tem DJ = 2440588
//OBS: esta f�rmula � v�lida apenas entre os anos 1801 e 2099
int dia_juliano(int *D, int *M, int *A)
{
	int DJ;
	DJ=*D-32075+1461*(*A+4800+(*M-14)/12)/4+367*(*M-2-(*M-14)/12*12)/12-3*((*A+4900+(*M-14)/12)/100)/4;
    return DJ;
}

//===================================================
//[4][3]
//Fun��o para listar o relat�rio dos empr�stimos entre datas X e Y de devolu��o
void listar_data(USUARIOS *user, LIVROS *book, EMPRESTIMOS *loan, int *cont_user, int *cont_book, int *cont_loan)
{
	DATA dev_inicial, dev_final;
	int verif=0, i, pos_cpf, pos_isbn;
	int DJ_atual, DJ_inicial, DJ_final;
	printf("\nInforme o per�odo que deseja listar os empr�stimos\n\nData de devolu��o inicial");
	printf("\nDia [dd]: ");
	scanf("%d", &dev_inicial.DIA);
	printf("M�s [mm]: ");
	scanf("%d", &dev_inicial.MES);
	printf("Ano [aaaa]: ");
	scanf("%d", &dev_inicial.ANO);
	printf("\nData de devolu��o final");
	printf("\nDia [dd]: ");
	scanf("%d", &dev_final.DIA);
	printf("M�s [mm]: ");
	scanf("%d", &dev_final.MES);
	printf("Ano [aaaa]: ");
	scanf("%d", &dev_final.ANO);
	DJ_inicial=dia_juliano(&dev_inicial.DIA, &dev_inicial.MES, &dev_inicial.ANO);
	DJ_final=dia_juliano(&dev_final.DIA, &dev_final.MES, &dev_final.ANO);
	for(i=0; i<*cont_loan; i++)
	{
		DJ_atual=dia_juliano(&loan[i].DEVOLUCAO.DIA, &loan[i].DEVOLUCAO.MES, &loan[i].DEVOLUCAO.ANO);
		if(DJ_inicial<=DJ_atual && DJ_atual<=DJ_final)
		{
			//pos_cpf=buscar_cpf(user, loan[i].CPF, cont_user);
			//pos_isbn=buscar_isbn(book, loan[i].ISBN, cont_book);
			printf("\nNome: %s", user[pos_cpf].NOME);
			printf("\nCPF: %s", loan[i].CPF);
			printf("\nT�tulo: %s", book[pos_isbn].TITULO);
			printf("\nISBN: %s", loan[i].ISBN);
			printf("\nData de Retirada: %d/%d/%d", loan[i].RETIRADA.DIA, loan[i].RETIRADA.MES, loan[i].RETIRADA.ANO);
			printf("\nData de Devolu��o: %d/%d/%d", loan[i].DEVOLUCAO.DIA, loan[i].DEVOLUCAO.MES, loan[i].DEVOLUCAO.ANO);
			printf("\nMulta: R$%.2f/dia", loan[i].MULTA);
			printf("\n\n-------------------------------");
			verif=1;			
		}
	}
	if(verif==0)
		printf("\nN�o h� empr�stimos cadastrados  entre os dias %d/%d/%d e %d/%d/%d", dev_inicial.DIA, dev_inicial.MES, dev_inicial.ANO, dev_final.DIA, dev_final.MES, dev_final.ANO);
}

//===================================================
//Fun��o principal
main()
{
	setlocale(LC_ALL, "Portuguese");
	USUARIOS usuario[max];
	LIVROS livro[max];
	EMPRESTIMOS emprestimo[max];
	int op;
	int cont_usuario=0, cont_livro=0, cont_emprestimo=0;

	printf("\t_____ BIBLIOTECA _____");
	do
	{
		menu();
		printf("\nOp��o desejada: ");
		scanf("%d", &op);
		
		switch(op) //Switch - MENU DE OP��ES
		{
			case 1: //SUBMENU DE USU�RIOS
				system("cls");
				menu_usuario();
				printf("\nOp��o desejada: ");
				scanf("%d", &op);
				
				switch(op) //Switch - SUBMENU DE USU�RIOS
				{
					case 1:
						printf("\n\t=== LISTAR TODOS USU�RIOS ===\n");
						listar_usuarios();
						break;
						
					case 2:
						printf("\n\t=== LISTAR USU�RIO - CPF ===\n");
						listar_cpf();
						break;
						
					case 3:
						printf("\n\t=== INCLUIR USU�RIO ===\n");
						incluir_usuario();
						printf("\nUsu�rio cadastrado com sucesso.");
						break;
						
					case 4:
						printf("\n\t=== ALTERAR USU�RIO ===\n");
						alterar_usuario();
						break;
						
					case 5:
						printf("\n\t=== EXCLUIR USU�RIO ===\n");
						excluir_usuario();
						op=0; //Necess�rio resetar para o programa n�o ser encerrado.
						break;
						
					default: //OP��ES INV�LIDAS (<1 OU >5) - SUBMENU DE USU�RIOS
						printf("\n\n\t*** ATEN��O! ***\nOp��o INV�LIDA. Tente novamente\n\t****************");
				}
				break;
				
			case 2: //SUBMENU DE LIVROS
				system("cls");
				menu_livro();
				printf("\nOp��o desejada: ");
				scanf("%d", &op);
			
				switch(op) //Switch - SUBMENU DE LIVROS
				{
					case 1:
						printf("\n\t=== LISTAR TODOS LIVROS ===\n");
						listar_livros();
						break;
						
					case 2:
						printf("\n\t=== LISTAR LIVRO - ISBN ===\n");
						listar_isbn();
						break;
						
					case 3:
						printf("\n\t=== INCLUIR LIVRO ===\n");
						incluir_livro();
						printf("\nLivro cadastrado com sucesso.");
						break;
						
					case 4:
						printf("\n\t=== ALTERAR LIVRO ===\n");
						alterar_livro();
						break;
						
					case 5:
						printf("\n\t=== EXCLUIR LIVRO ===\n");
						excluir_livro();
						op=0; //Necess�rio resetar para o programa n�o ser encerrado.
						break;
						
					default: //OP��ES INV�LIDAS (<1 OU >5) - SUBMENU DE USU�RIOS
						printf("\n\n\t*** ATEN��O! ***\nOp��o INV�LIDA. Tente novamente\n\t****************");
				}
				break;
				
			case 3: //SUBMENU DE EMPR�STIMOS
				system("cls");
				menu_emprestimo();
				printf("\nOp��o desejada: ");
				scanf("%d", &op);
				
				switch(op) //Switch - SUBMENU DE EMPR�STIMOS
				{
					case 1:
						printf("\n\t=== LISTAR TODOS EMPR�STIMOS ===\n");
						listar_emprestimos();
						break;
						
					case 2:
						printf("\n\t=== LISTAR EMPR�STIMO - CPF, ISBN, DATA DE RETIRADA ===\n");
						listar_emprestimo_chave();
						break;
						
					case 3:
						if(cont_emprestimo<max)
						{
							printf("\n\t=== INCLUIR EMPR�STIMO ===\n");
							incluir_emprestimo(usuario, livro, emprestimo, &cont_usuario, &cont_livro, &cont_emprestimo);
						}
						else
							printf("\n\tN�o � poss�vel realizar novos cadastros!\nEntre em contato com o t�cnico respons�vel!\n");
						break;
						
					case 4:
						printf("\n\t=== ALTERAR EMPR�STIMO ===\n");
						alterar_emprestimo(usuario, livro, emprestimo, &cont_usuario, &cont_livro, &cont_emprestimo);
						break;
						
					case 5:
						printf("\n\t=== EXCLUIR EMPR�STIMO ===\n");
						excluir_emprestimo(usuario, livro, emprestimo, &cont_usuario, &cont_livro, &cont_emprestimo);
						op=0; //Necess�rio resetar para o programa n�o ser encerrado.
						break;
					
					default: //OP��ES INV�LIDAS (<1 OU >5) - SUBMENU DE EMPR�STIMOS
						printf("\n\n\t*** ATEN��O! ***\nOp��o INV�LIDA. Tente novamente\n\t****************");
				}
				break;
				
			case 4: //SUBMENU DE RELAT�RIOS
				system("cls");
				menu_relatorio();
				printf("\nOp��o desejada: ");
				scanf("%d", &op);
				
				switch(op) //Switch - SUBMENU DE RELAT�RIOS
				{
					case 1:
						listar_idade();
						break;
						
					case 2:
						listar_autores();
						break;
						
					case 3:
						listar_data(usuario, livro, emprestimo, &cont_usuario, &cont_livro, &cont_emprestimo);
						break;
						
					default: //OP��ES INV�LIDAS (<1 OU >5) - SUBMENU DE RELAT�RIOS
						printf("\n\n\t*** ATEN��O! ***\nOp��o INV�LIDA. Tente novamente\n\t****************");
						op=0; //Necess�rio resetar para o programa n�o ser encerrado caso o usu�rio pressionar 5.
				}
				break;
				
			case 5:
				printf("\nPrograma ENCERRADO. At� logo!\n");
				break;
				
			default: //OP��ES INV�LIDAS (<1 OU >5) - MENU DE OP��ES
				printf("\n\n\t*** ATEN��O! ***\nOp��o INV�LIDA. Tente novamente\n\t****************");
		}
	}
	
	while(op!=5);
}
