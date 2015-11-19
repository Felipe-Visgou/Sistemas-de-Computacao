// Ler arquivo de entrada
/* j'a existe um vetor de processos vazio, com no maximo 100 ocorrencias, ao decorrer da funcao de ler, o vetor eh preenchido*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct processo
{
	int num;
	int tamanho;
	int exec[10];
	int io[10];
	int qtdexec;
	int qtdio;
	int naMemoria;
	int segAtual;
	int t_exec;
	int t_io;
};
typedef struct processo Processo;
struct segmento{
	int tam;
	Processo *proc;
};
struct memory{
	struct segmento s[5];
};
int lastInd = 0; // Indice que indica o segmento alocado para o ultimo processo
int tempoTotal = 0; // tempo total decorrido
typedef struct segmento Segmento;
typedef struct memory Memory;
typedef struct LIS_tagLista * LIS_tppLista;
typedef struct tagElemLista {

         void * pValor ;
               /* Ponteiro para o valor contido no elemento */
         struct tagElemLista * pAnt ;
               /* Ponteiro para o elemento predecessor */
         struct tagElemLista * pProx ;
               /* Ponteiro para o elemento sucessor */
	} tpElemLista ;
typedef struct LIS_tagLista {

         tpElemLista * pOrigemLista ;
               /* Ponteiro para a origem da lista */
         tpElemLista * pFimLista ;
               /* Ponteiro para o final da lista */
         tpElemLista * pElemCorr ;
               /* Ponteiro para o elemento corrente da lista */
         int numElem ;
               /* Número de elementos da lista */

   } LIS_tpLista ;
tpElemLista * CriarElemento( LIS_tppLista pLista , void * pValor  )
{

	tpElemLista * pElem ;

	pElem = ( tpElemLista * ) malloc( sizeof( tpElemLista )) ;
	if ( pElem == NULL )
	{
		return NULL ;
	} /* if */
	pElem->pValor = pValor ;
	pElem->pAnt   = NULL  ;
	pElem->pProx  = NULL  ;
	pLista->numElem ++ ;
	return pElem ;
}
LIS_tppLista LIS_CriarLista(void)
   {

      LIS_tpLista * pLista = NULL ;

      pLista = ( LIS_tpLista * ) malloc( sizeof( LIS_tpLista )) ;
      if ( pLista == NULL )
      {
         return NULL ;
      } /* if */
	  pLista->pOrigemLista = NULL ;
      pLista->pFimLista = NULL ;
      pLista->pElemCorr = NULL ;
      pLista->numElem   = 0 ;
      return pLista ;

   } /* Fim função: LIS  &Criar lista */
void LIS_ExcluirElemento( LIS_tppLista pLista )
{
	tpElemLista * pElem ;
	if ( pLista->pElemCorr == NULL )
	{
		return  ;
	} /* if */
	pElem = pLista->pElemCorr ;
	/* Desencadeia à esquerda */
	if ( pElem->pAnt != NULL )
	{
		pElem->pAnt->pProx   = pElem->pProx ;
		pLista->pElemCorr    = pElem->pAnt ;
	}
	else 
	{
		pLista->pElemCorr    = pElem->pProx ;
		pLista->pOrigemLista = pLista->pElemCorr ;
	} /* if */
	/* Desencadeia à direita */
	if ( pElem->pProx != NULL )
	{
		pElem->pProx->pAnt = pElem->pAnt ;
	} 
	else
	{
		pLista->pFimLista = pElem->pAnt ;
	} /* if */
	free(pElem) ;
	pLista->numElem--;
	return ;
} /* Fim função: LIS  &Excluir elemento */
void LIS_InserirElementoApos( LIS_tppLista pLista , void * pValor)
{
      tpElemLista * pElem ;
      /* Criar elemento a inerir após */

         pElem = CriarElemento( pLista , pValor ) ;

      /* Encadear o elemento após o elemento */

         if ( pLista->pElemCorr == NULL )
         {
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
            if ( pLista->pElemCorr->pProx != NULL )
            {
               pElem->pProx  = pLista->pElemCorr->pProx ;
               pLista->pElemCorr->pProx->pAnt = pElem ;
            } else
            {
               pLista->pFimLista = pElem ;
            } /* if */

            pElem->pAnt = pLista->pElemCorr ;
            pLista->pElemCorr->pProx = pElem ;

         } /* if */  
         pLista->pElemCorr = pElem ;  
         return;

   } /* Fim função: LIS  &Inserir elemento após */
int LIS_ObterTamanho( LIS_tppLista pLista)
{
	return pLista->numElem;
}
void * LIS_ObterValor( LIS_tppLista pLista )
{
	if ( pLista->pElemCorr == NULL )
	{
		return NULL ;
	} /* if */

	return pLista->pElemCorr->pValor ;
}
int LIS_AvancarElementoCorrente( LIS_tppLista pLista , int numElem )
{
	int i ;
	tpElemLista * pElem ;
	/* Tratar avançar para frente */
	if ( numElem > 0 )
	{
		pElem = pLista->pElemCorr ;
		for( i = numElem ; i > 0 ; i-- )
		{
			if ( pElem == NULL )
			{
				break ;
			} /* if */
			pElem    = pElem->pProx ;
		} /* for */

		if ( pElem != NULL )
		{
			pLista->pElemCorr = pElem ;
			return 0;
		} /* if */
		pLista->pElemCorr = pLista->pFimLista ;
		return 0 ;
	} /* fim ativa: Tratar avançar para frente */
	/* Tratar avançar para trás */
	else if ( numElem < 0 )
	{
		pElem = pLista->pElemCorr ;
		for( i = numElem ; i < 0 ; i++ )
		{
			if ( pElem == NULL )
			{
				break ;
			} /* if */
			pElem    = pElem->pAnt ;
		} /* for */

		if ( pElem != NULL )
		{
			pLista->pElemCorr = pElem ;
			return 0;
		} /* if */

		pLista->pElemCorr = pLista->pOrigemLista ;
		return 0 ;
	} /* fim ativa: Tratar avançar para trás */
	return -1;
} /* Fim função: LIS  &Avançar elemento */
void IrInicioLista( LIS_tppLista pLista )
{
	pLista->pElemCorr = pLista->pOrigemLista ;
} /* Fim função: LIS  &Ir para o elemento inicial */
void IrFinalLista( LIS_tppLista pLista )
{

	pLista->pElemCorr = pLista->pFimLista ;
}
void DestruirLista(LIS_tppLista plista)
{
	int i, tam;
	void* aux;
	struct tagElemLista * elemAux;
	tam = LIS_ObterTamanho(plista);
	IrFinalLista(plista);
	elemAux = plista->pElemCorr;
	for(i = 0; i < tam; i++)
	{
		free(elemAux->pValor);
		free(elemAux);
		elemAux = plista->pElemCorr->pProx;
	}
	free(plista);
}
int lerEntrada(FILE** fp, Processo *vProc)
{
	int i, j, qtdprocessos, qtdinf, num_proc, t_exec, t_io, tam_proc;
	char* buff;
	char c;
	int passeiexec = 0, passeiio = 0;
	fscanf(*fp, "%d\n", &qtdprocessos);
	printf("qtdprocessos = %d\n", qtdprocessos);
	for(i = 0; i < qtdprocessos;  i++)
	{
		fscanf(*fp, "Processo#%d - %dMb\n", &num_proc, &tam_proc);
		printf("num_proc = %d --- tam_proc = %d \n", num_proc, tam_proc);
		vProc[i].num = num_proc;
		vProc[i].tamanho = tam_proc;
		passeiexec = 0;
		passeiio = 0;
		fscanf(*fp, "%d\n", &qtdinf);
		printf("qtdinf = %d \n", qtdinf);
		for(j = 0; j < qtdinf; j++)
		{
			fscanf(*fp, "%c", &c);
			if(c == 'e')
			{
				fscanf(*fp,"xec ");
				fscanf(*fp, "%d\n", &t_exec);
				printf("t_exec = %d \n", t_exec);
				vProc[i].exec[passeiexec] = t_exec;
				passeiexec++;
			}
			else // entao eu li um 'io'
			{
				fscanf(*fp, "o ");
				fscanf(*fp, "%d\n", &t_io);
				printf("t_io = %d \n", t_io);
				vProc[i].io[passeiio] = t_io;
				passeiio++;
			}
		}
		vProc[i].qtdio = passeiio;
		vProc[i].qtdexec = passeiexec;
	}
	return qtdprocessos;
}

void imprimeVetor(Processo *vProc, int qtdprocessos)
{
	int i, j = 0, lim = 0, qtdio, qtdexec;
	printf("%d\n", qtdprocessos);
	for(i = 0; i < qtdprocessos; i++)
	{
		printf("Processo#%d - %dMb\n", vProc[i].num, vProc[i].tamanho);
		qtdexec = vProc[i].qtdexec; qtdio = vProc[i].qtdio;
		lim = 0;
		j = 0;
		while(lim < qtdexec + qtdio)
		{
			printf("exec %d\n", vProc[i].exec[j]);
			lim++; if(lim >= qtdexec + qtdio) continue;
			printf("io %d\n", vProc[i].io[j]);
			lim++;
			j++;
		}
	}
}
void InicializaMemoria (Memory *mem)
{
		// 8Mb
		mem->s[0].proc = NULL;
		mem->s[0].tam = 8;
		// 4Mb
		mem->s[1].proc = NULL;
		mem->s[1].tam = 4;
		// 2Mb
		mem->s[2].proc = NULL;
		mem->s[2].tam = 2;
		// 1Mb
		mem->s[3].proc = NULL;
		mem->s[3].tam = 1;
		// 1Mb
		mem->s[4].proc = NULL;
		mem->s[4].tam = 1;
}
void InsereProcessosMem(Memory *mem, Processo *proc, int seg)
{
	switch(seg)
	{
	case 8:
		proc->naMemoria = 1;
		proc->segAtual = 8;
		mem->s[0].proc = proc;
		break;
	case 4:
		proc->naMemoria = 1;
		proc->segAtual = 4;
		mem->s[1].proc = proc;
		break;
	case 2:
		proc->naMemoria = 1;
		proc->segAtual = 2;
		mem->s[2].proc = proc;
		break;
	case 1:
		proc->naMemoria = 1;
		if(mem->s[3].proc == NULL)
		{
			proc->segAtual = 10;
			mem->s[3].proc = proc;
		}
		else if(mem->s[4].proc ==  NULL)
		{
			proc->segAtual = 11;
			mem->s[4].proc = proc;
		}
		break;
	case 11:
		proc->naMemoria = 1;
		proc->segAtual = 11;
		mem->s[4].proc = proc;
		break;
	default:
		break;
	}
}
Processo * RetiraProcessoMem(Memory *mem, int seg)
{
	Processo *aux;
	switch(seg)
	{
	case 8:
		aux = mem->s[0].proc;
		mem->s[0].proc = NULL;
		break;
	case 4:
		aux = mem->s[1].proc;
		mem->s[1].proc = NULL;
		break;
	case 2:
		aux = mem->s[2].proc;
		mem->s[2].proc = NULL;
		break;
	case 10:
		aux = mem->s[3].proc;
		mem->s[3].proc = NULL;
		break;
	case 11:
		aux = mem->s[4].proc;
		mem->s[4].proc = NULL;;
		break;
	default:
		break;
	}
	return aux;
}
void imprimeProcesso(Processo *proc)
{
	int i, j = 0, lim = 0, qtdio, qtdexec;
	if(proc == NULL)
	{
		printf(" VAZIO \n");
	}
	else
	{
		printf("Processo#%d - %dMb\n", proc->num, proc->tamanho);
		qtdexec = proc->qtdexec; qtdio = proc->qtdio;
		lim = 0;
		j = 0;
		while(lim < qtdexec + qtdio)
		{
			printf("exec %d\n", proc->exec[j]);
			lim++; if(lim >= qtdexec + qtdio) continue;
			printf("io %d\n", proc->io[j]);
			lim++;
			j++;
		}
	}
}
void imprimeMemoria(Memory * mem)
{
	Processo *paux;
	system("cls");
	printf("Tempo total decorrido : %d \n", tempoTotal);
	printf("* * * * Memory * * * * * \n");
	printf("----------8Mb---------\n");
	paux = mem->s[0].proc;
	imprimeProcesso(paux);
	printf("----------4Mb---------\n");
	paux =  mem->s[1].proc;
	imprimeProcesso(paux);
	printf("----------2Mb---------\n");
	paux =  mem->s[2].proc;
	imprimeProcesso(paux);
	printf("----------1Mb---------\n");
	paux =  mem->s[3].proc;
	imprimeProcesso(paux);
	printf("----------1Mb---------\n");
	paux =  mem->s[4].proc;
	imprimeProcesso(paux);
	printf("* * * * * * * * * * * * *\n");
}
void clock (int t)
{
	int a, j;
	long int i;
	for(j = 0; j < t; j++)
	{
		// 122588545
		//
		for(i = 0; i < 	12258845; i++)
		{
			a = 3;
		}
	//printf("time! \n");
	}
return;
}
int firstFit(Memory *mem, LIS_tppLista lisProntos)
{	
	Processo *aux;
	int cnt = 0, fail = 0,i;
	IrInicioLista(lisProntos);
	aux = (Processo*)LIS_ObterValor(lisProntos);
	cnt = LIS_ObterTamanho(lisProntos);
	fail = 1;
	while(cnt > 0)
	{
		for(i = 0; i < 5; i++)
		{
			if((aux->tamanho <= mem->s[i].tam) && (mem->s[i].proc == NULL) && (aux->naMemoria == 0)) // se o tamanho do process é menor q o segmento da memoria
			{
				InsereProcessosMem(mem, aux, mem->s[i].tam);
				fail = 0;
				break;
			}
		}
		LIS_AvancarElementoCorrente(lisProntos, 1);
		aux = (Processo*)LIS_ObterValor(lisProntos);
		cnt--;
	}
	return fail;
}
int BestFit(Memory *mem, LIS_tppLista lisProntos){
	Processo *aux;
	int cnt = 0, fail = 0, i;
	IrInicioLista(lisProntos);
	aux = (Processo*)LIS_ObterValor(lisProntos);
	cnt = LIS_ObterTamanho(lisProntos);
	fail = 1;
	while (cnt > 0)
	{
		int diferenca = 90;
		int BestInd = -1;
		for (i = 0; i < 5; i++)
		{
			if ((aux->tamanho <= mem->s[i].tam) && (mem->s[i].proc == NULL) && (aux->naMemoria == 0)) // se o tamanho do process é menor q o segmento da memoria
			{
				if (mem->s[i].tam - aux->tamanho <= diferenca){
					BestInd = i;
					diferenca = mem->s[i].tam - aux->tamanho;
				}
			}
		}
		if (BestInd != -1){
			InsereProcessosMem(mem, aux, mem->s[BestInd].tam);
			fail = 0;
		}
		LIS_AvancarElementoCorrente(lisProntos, 1);
		aux = (Processo*)LIS_ObterValor(lisProntos);
		cnt--;
	}
	return fail;
}
int WorstFit (Memory *mem, LIS_tppLista lisProntos){
	Processo *aux;
	int cnt = 0, fail = 0, i;
	IrInicioLista(lisProntos);
	aux = (Processo*)LIS_ObterValor(lisProntos);
	cnt = LIS_ObterTamanho(lisProntos);
	fail = 1;
	while (cnt > 0)
	{
		int diferenca = 0;
		int BestInd = -1;
		for (i = 0; i < 5; i++)
		{
			if ((aux->tamanho <= mem->s[i].tam) && (mem->s[i].proc == NULL) && (aux->naMemoria == 0)) // se o tamanho do process é menor q o segmento da memoria
			{
				if (mem->s[i].tam - aux->tamanho >= diferenca){
					BestInd = i;
					diferenca = mem->s[i].tam - aux->tamanho;
				}
			}
		}
		if (BestInd != -1){
			InsereProcessosMem(mem, aux, mem->s[BestInd].tam);
			fail = 0;
		}
		LIS_AvancarElementoCorrente(lisProntos, 1);
		aux = (Processo*)LIS_ObterValor(lisProntos);
		cnt--;
	}
	return fail;
}
int NextFit(Memory *mem, LIS_tppLista lisProntos)
{	
	Processo *aux;
	int cnt = 0, fail = 0,i;
	IrInicioLista(lisProntos);
	aux = (Processo*)LIS_ObterValor(lisProntos);
	cnt = LIS_ObterTamanho(lisProntos);
	fail = 1;
	while(cnt > 0)
	{
		for(i = lastInd; i < 5; i++)
		{
			if((aux->tamanho <= mem->s[i].tam) && (mem->s[i].proc == NULL) && (aux->naMemoria == 0)) // se o tamanho do process é menor q o segmento da memoria
			{
				InsereProcessosMem(mem, aux, mem->s[i].tam);
				lastInd = i;
				fail = 0;
				break;
			}
		}
		for(i = 0; i < lastInd; i++)
		{
			if((aux->tamanho <= mem->s[i].tam) && (mem->s[i].proc == NULL) && (aux->naMemoria == 0)) // se o tamanho do process é menor q o segmento da memoria
			{
				InsereProcessosMem(mem, aux, mem->s[i].tam);
				lastInd = i;
				fail = 0;
				break;
			}
		}
		LIS_AvancarElementoCorrente(lisProntos, 1);
		aux = (Processo*)LIS_ObterValor(lisProntos);
		cnt--;
	}
	return fail;
}
void getNext(LIS_tppLista lisProc)
{
	Processo *aux;
	IrInicioLista(lisProc);
	aux = (Processo*)LIS_ObterValor(lisProc);
	while(aux->naMemoria == 0)
	{
		LIS_AvancarElementoCorrente(lisProc, 1);
		aux = (Processo*)LIS_ObterValor(lisProc);
	}
}
void ImprimirLista(LIS_tppLista lisProntos)
{
	int tam, i;
	Processo *aux;
	IrInicioLista(lisProntos);
	tam = LIS_ObterTamanho(lisProntos);
	for(i = 0; i < tam; i++)
	{
		aux = (Processo*)LIS_ObterValor(lisProntos);
		imprimeProcesso(aux);
		LIS_AvancarElementoCorrente(lisProntos, 1);
	}
}
void ImprimirEstado(FILE **fp, LIS_tppLista lisIO, Processo *exec, Memory *mem, int t)
{
	int contador, i;
	Processo *aux;
	int numProc, tamIO = LIS_ObterTamanho(lisIO);
	fprintf(*fp,"Tempo Total Decorrido : %d \n", t);
	fprintf(*fp, "* * * * * * * * Memory * * * * * * * * \n");
	aux = mem->s[0].proc;
	if(aux == NULL)
	{
		fprintf(*fp, "|-----8Mb-----------------------------|\n");
		fprintf(*fp, "|                                     |\n");
		fprintf(*fp, "|                                     |\n");
		fprintf(*fp, "|                                     |\n");
		fprintf(*fp, "|              VAZIO                  |\n");
		fprintf(*fp, "|                                     |\n");
		fprintf(*fp, "|                                     |\n");
		fprintf(*fp, "|                                     |\n");
	}
	else
	{
		numProc = aux->num;
		fprintf(*fp, "|-----8Mb-----------------------------|\n");
		fprintf(*fp, "|                                     |\n");
		fprintf(*fp, "|                                     |\n");
		fprintf(*fp, "|                                     |\n");
		fprintf(*fp, "|        Processo %d                   |\n", numProc);
		fprintf(*fp, "|                                     |\n");
		fprintf(*fp, "|                                     |\n");
		fprintf(*fp, "|                                     |\n");
	}
	aux = mem->s[1].proc;
	if(aux == NULL)
	{
		fprintf(*fp, "------4Mb------------------------------\n");
		fprintf(*fp, "|                                     |\n");
		fprintf(*fp, "|                                     |\n");
		fprintf(*fp, "|                VAZIO                |\n");
		fprintf(*fp, "|                                     |\n");
		fprintf(*fp, "|                                     |\n");
	}
	else
	{
		numProc = aux->num;
		fprintf(*fp, "------4Mb------------------------------\n");
		fprintf(*fp, "|                                     |\n");
		fprintf(*fp, "|                                     |\n");
		fprintf(*fp, "|        Processo %d                   |\n", numProc);
		fprintf(*fp, "|                                     |\n");
		fprintf(*fp, "|                                     |\n");
	}
	aux = mem->s[2].proc;
	if(aux == NULL)
	{
		fprintf(*fp, "------2Mb------------------------------\n");
		fprintf(*fp, "|                                     |\n");
		fprintf(*fp, "|              VAZIO                  |\n");
		fprintf(*fp, "|                                     |\n");
	}
	else
	{
		numProc = aux->num;
		fprintf(*fp, "------2Mb------------------------------\n");
		fprintf(*fp, "|                                     |\n");
		fprintf(*fp, "|        Processo %d                   |\n", numProc);
		fprintf(*fp, "|                                     |\n");
	}
	aux = mem->s[3].proc;
	if(aux == NULL)
	{
		fprintf(*fp, "------1Mb------------------------------\n");
		fprintf(*fp, "|              VAZIO                  |\n");
	}
	else
	{
		numProc = aux->num;
		fprintf(*fp, "------1Mb------------------------------\n");
		fprintf(*fp, "|        Processo %d                   |\n", numProc);
	}
	aux = mem->s[4].proc;
	if(aux == NULL)
	{
		fprintf(*fp,"------1Mb------------------------------\n");
		fprintf(*fp, "|              VAZIO                  |\n");
	}
	else
	{
		numProc = aux->num;
		fprintf(*fp,"------1Mb------------------------------\n");
		fprintf(*fp,"|        Processo %d                   |\n", numProc);
	}
	fprintf(*fp, "* * * * * * * * * * * * * * * * * * * * \n");
	fprintf(*fp,"\n");
	fprintf(*fp," * * * * CPU * * * * \n");
	fprintf(*fp,"|                     |\n");
	fprintf(*fp,"|   Processo %d        |\n", exec->num);
	fprintf(*fp,"|                     |\n");
	fprintf(*fp," * * * * * * * * * * \n");
	fprintf(*fp,"\n");
	fprintf(*fp," * * * * I/O * * * * * \n");
	fprintf(*fp,"|                     |\n");
	for(i = 0; i < tamIO; i++)
	{
		aux = (Processo*)LIS_ObterValor(lisIO);
		numProc = aux->num;
		fprintf(*fp,"|   Processo %d       |\n", numProc);
	}
	fprintf(*fp,"|                     |\n");
	fprintf(*fp," * * * * * * * * * * \n");
}

int main (void)
{
	int qtdprocessos, met;
	FILE* out = fopen("saida.txt","w");
	int i, j, fail = 0, cnt = 0, tamProntos, tamIO, tamIO2, seg = 0, inxExec, inxIO;
	Processo *aux, *procExec, *procIO, *procRetirado;
	LIS_tppLista listaIO = LIS_CriarLista();
	LIS_tppLista listaProntos = LIS_CriarLista();
	Memory *	mem = (Memory*)malloc(sizeof(Memory));
	FILE* fp = fopen("entrada.txt", "r");
	Processo *vp = (Processo*)malloc(100*sizeof(Processo));
	qtdprocessos = lerEntrada(&fp, vp);
	imprimeVetor(vp, qtdprocessos);
	InicializaMemoria(mem);
	procExec = NULL;
	// Insere os elementos lidos numa lista de prontos
	for(i = 0; i < qtdprocessos; i++)
	{
		LIS_InserirElementoApos(listaProntos, &vp[i]);
		LIS_AvancarElementoCorrente(listaProntos, 1);
		vp[i].segAtual = -1;
		vp[i].naMemoria = 0;
		vp[i].t_exec = 0;
		vp[i].t_io = 0;
	}
	printf("1: First Fit \n");
	printf("2: Best Fit \n");
	printf("3: Worst Fit \n");
	printf("4: Next Fit \n");
	scanf("%d", &met);
EXEC:
	IrInicioLista(listaProntos); // vai pro inicio da lista de prontos
	aux = (Processo*)LIS_ObterValor(listaProntos);
	switch(met)
	{
	case 1:
		firstFit(mem, listaProntos);
		break;
	case 2:
		BestFit(mem, listaProntos);
		break;
	case 3:
		WorstFit(mem, listaProntos);
		break;
	case 4:
		NextFit(mem, listaProntos);
		break;
	default:
		break;
	}
	imprimeMemoria(mem);
	printf("\n Lista de Prontos \n");
	ImprimirLista(listaProntos);
	printf("\n Lista de IO \n");
	ImprimirLista(listaIO);
	/* * * * * * * * * * * * * * * * * * * * * * */
	// executar o processo
	IrInicioLista(listaProntos);
	tamProntos = LIS_ObterTamanho(listaProntos);
	tamIO = LIS_ObterTamanho(listaIO);
	aux =  (Processo*)LIS_ObterValor(listaProntos); // obtem o priemeiro elemento da lista de prontos
	while(tamProntos > 0)
	{
		if(!aux->naMemoria)	// se o processo não esta em memoria
		{
			LIS_AvancarElementoCorrente(listaProntos, 1);
			aux = (Processo*)LIS_ObterValor(listaProntos);
			continue;
		}
		procExec = aux;
		for(i = 0; i < 10; i++) // os 10 clocks de cpu
		{
			ImprimirEstado(&out, listaIO, procExec, mem, tempoTotal);
			clock(1); tempoTotal++;
			inxExec = procExec->t_exec;
			procExec->exec[inxExec]--;
			tamIO = LIS_ObterTamanho(listaIO);
			IrInicioLista(listaIO);
			for(j = 0; j < tamIO; j++) // diminui 1 de IO para todos q estao na lista de I/O
			{
				procIO = (Processo*)LIS_ObterValor(listaIO);
				inxIO = procIO->t_io;
				procIO->io[inxIO]--;
				if(procIO->io[inxIO] == 0) // seu tempo de io acabou
				{
					LIS_ExcluirElemento(listaIO); // retira da lista de io e insere-o na lista de prontos
					IrFinalLista(listaProntos);
					LIS_InserirElementoApos(listaProntos, procIO);
					procIO->t_io++;
				}
				LIS_AvancarElementoCorrente(listaIO, 1);
			}
			tamIO2 = LIS_ObterTamanho(listaIO);
			if(tamIO != tamIO2)
			{
				switch(met)
				{
				case 1:
					firstFit(mem, listaProntos);
					break;
				case 2:
					BestFit(mem, listaProntos);
					break;
				case 3:
					WorstFit(mem, listaProntos);
					break;
				case 4:
					NextFit(mem, listaProntos);
					break;
				default:
					break;
				}
			}
			getNext(listaProntos);
			if(procExec->exec[inxExec] == 0 || i == 9) // se o seu tempo de exec terminou entao retira da memoria
			{
				/* * * * * */	//imprimeMemoria(mem);
				LIS_ExcluirElemento(listaProntos);
				if(procExec->exec[inxExec] == 0) procExec->t_exec++; // se acabou um exec inteiro
				if(procExec->exec[inxExec] == 0 && procExec->t_io < procExec->qtdio) // se o processo terminou um exec e ainda tem io para fazer
				{
					IrFinalLista(listaIO);
					LIS_InserirElementoApos(listaIO, procExec);
				}
				// retira da memoria
				// se o processo ainda tem exec para fazer
				if(procExec->exec[inxExec] > 0)
				{
					IrFinalLista(listaProntos);
					LIS_InserirElementoApos(listaProntos, procExec);
				}
				seg = procExec->segAtual;
				procRetirado = RetiraProcessoMem(mem, seg);
				procRetirado->naMemoria = 0;
				switch(met)
				{
				case 1:
					firstFit(mem, listaProntos);
					break;
				case 2:
					BestFit(mem, listaProntos);
					break;
				case 3:
					WorstFit(mem, listaProntos);
					break;
				case 4:
					NextFit(mem, listaProntos);
					break;
				default:
					break;
				}
				break;
			}
			imprimeMemoria(mem);
			printf("\n Lista de Prontos \n");
			ImprimirLista(listaProntos);
			printf("\n Lista de IO \n");
			ImprimirLista(listaIO);
		} /* final dos 10 clocks*/
		imprimeMemoria(mem);
		printf("\n Lista de Prontos \n");
		ImprimirLista(listaProntos);
		printf("\n Lista de IO \n");
		ImprimirLista(listaIO);
		tamProntos = LIS_ObterTamanho(listaProntos);
		IrInicioLista(listaProntos);
		aux =  (Processo*)LIS_ObterValor(listaProntos);
	}
	tamIO = LIS_ObterTamanho(listaIO);
	while(tamIO > 0) // entao tem IO sobrando e ngm para executar
	{
		IrInicioLista(listaIO);
		clock(1);tempoTotal++;
		for(j = 0; j < tamIO; j++) // diminui 1 de IO para todos q estao na lista de I/O
		{
			procIO = (Processo*)LIS_ObterValor(listaIO);
			inxIO = procIO->t_io;
			procIO->io[inxIO]--;
			if(procIO->io[inxIO] == 0) // seu tempo de io acabou
			{
				LIS_ExcluirElemento(listaIO); // retira da lista de io e insere-o na lista de prontos
				IrFinalLista(listaProntos);
				LIS_InserirElementoApos(listaProntos, procIO);
				procIO->t_io++;
			}
			LIS_AvancarElementoCorrente(listaIO, 1);
		}
		tamIO = LIS_ObterTamanho(listaIO);
		tamProntos = LIS_ObterTamanho(listaProntos);
		imprimeMemoria(mem);
		printf("\n Lista de Prontos \n");
		ImprimirLista(listaProntos);
		printf("\n Lista de IO \n");
		ImprimirLista(listaIO);
		if(tamProntos > 0) // se alguem voltou par a lista de prontos...
			goto EXEC;
	}
	fclose(out);
	free(mem);
	free(vp);
	free(listaProntos);
	free(listaIO);
	return 0;
}