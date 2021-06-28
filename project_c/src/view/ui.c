#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../../includes/model/table.h"
#include "../../includes/config.h"
#include "../../includes/view/ui.h"

/**
 \brief Prints a table line
 @param content Table content
 @param nPars Number of parameters
 @param max Content size
*/
void printTableLine(GPtrArray* content, int nPars, int max){
	if (max % 2) max += 3;
	else max += 2;
	int maxLenght = (max * nPars) + (nPars * 2) - 2;
	for(int i = 0; i < nPars; i++){
		int aux = max - (strlen((char*) g_ptr_array_index(content, i)));
		printf("| %s", g_ptr_array_index(content, i));
		for(int j = 0; j < aux; j++)
			printf(" ");
	}
	printf("|\n");
	printf(" ");
	for(int k = 0; k < maxLenght; k++)
		printf("-");
	printf("\n");
}

/**
 \brief Prints a table
 @param t table
*/
void printTable(TABLE t){
	GPtrArray* content = getGPtrArray(t);
	int nPars = getNCols(t);
	int size = getInsertedData(t);
	if(content){
		int max = 0;
		for(guint i = 0; i < content->len; i++){
			if((int) strlen((char*) g_ptr_array_index(content, i)) > max) max = (int) strlen((char*) g_ptr_array_index(content, i));
		}
		guint j, k;
		for(j = 0; j < content->len; ){
			system("clear");
			guint lim = j + (ITEMSPERPAGE * nPars);
			if(lim > content->len) lim = content->len;
			for(k = j; k < lim; ){
				GPtrArray* aux = g_ptr_array_new();
				for(int m = 0; m < nPars; m++){
					g_ptr_array_add(aux, strdup((char*) g_ptr_array_index(content, k++)));
				}
				printTableLine(aux, nPars, max);
				g_ptr_array_free(aux, TRUE);
			}
			printSize(size);
			if ((lim == content->len && (int) k > (ITEMSPERPAGE * nPars))){
				char code;
				printLastPage();
				if(scanf("%c", &code) == 1){
					if(code == 'q'){
						g_ptr_array_free(content, TRUE);
						return;
					}
					else if(code == 'p') j -= (ITEMSPERPAGE * nPars);
				}
			}
			else if(lim == content->len){
				printOnlyPage();
				char code;
				if(scanf("%c", &code) == 1)
					if(code == 'q'){
						g_ptr_array_free(content, TRUE);
						return;
					}
			}
			else{
				printOptions(k, ITEMSPERPAGE);
				char code;
				if(scanf("%c", &code) == 1){
				if(code == 'q'){
					g_ptr_array_free(content, TRUE);
					return;
				}
				else if(code == 'p' && j != 0) j -= (ITEMSPERPAGE * nPars);
				else if (code == 'n') j += (ITEMSPERPAGE * nPars);
				}
			}
		}
	}
}


void printIndexFloat(TABLE t){
	GPtrArray* cont = getGPtrArray(t);
	system("clear");
	printf("| %f |\n", *((float*) g_ptr_array_index(cont, 0)));
	printOnlyPage();
	char code;
	if(scanf("%c", &code) == 1)
		if(code == 'q'){
			g_ptr_array_free(cont, TRUE);
				return;
		}
}

void printIndexInt(TABLE t){
	GPtrArray* cont = getGPtrArray(t);
	system("clear");
	printf("| %d |\n", *((int*) g_ptr_array_index(cont, 0)));
	printOnlyPage();
	char code;
	if(scanf("%c", &code) == 1)
		if(code == 'q'){
			g_ptr_array_free(cont, TRUE);
				return;
		}
}

void show(TABLE t)
{
	if(t){
		int query = getNQuery(t);
		switch(query){
			case 2:
				printQ2Q4Q5(t);
				break;
			case 3:
				printQ3(t);
				break;
			case 4:
				printQ2Q4Q5(t);
				break;
			case 5:
				printQ2Q4Q5(t);
				break;
			case 6:
				printQ6(t);
				break;
			case 7:
				printQ7(t);
				break;
			case 8:
				printQ8(t);
				break;
			case 9:
				printQ9(t);
				break;
			case 10:
				printHelp(t);
				break;
			case 11:
				printIndexFloat(t);
				break;
			case 12:
				printIndexInt(t);
				break;
			default:
				printTable(t);
				break;
		}
	}
}


void initShow()
{
	printf("\n Se desejar carregar os seus próprios ficheiros insira 1.\n");
	printf("\n Se desejar utilizar os ficheiros pré-definidos insira 2.\n\n");
}

void showFilePath()
{
	printf("\nInsira o path para os ficheiros que deseja carregar (espaçados e ordenados da forma: <ficheiro_users.csv ficheiro_businesses.csv ficheiro_reviews.csv):\n\n");
}

void showMessage(char* message)
{
	printf("%s\n", message);
}

void printPageNum(int cur, int max){
	printf("Página %d de %d\n", cur + 1, max + 1);
}

void printSize(int elems){
	printf("A tabela tem um total de %d linhas.\n", elems);
}

void printOptions(int aux, int min){
	printf("   Opções Disponíveis:");
	if(aux == min){  
			printf("\n     * q - Sair;");
			printf("\n     * n - Avançar para a próxima página.\n");
	}
	else{
		printf("\n     * q - Sair da query;");
		printf("\n     * n - Avançar para a próxima página;"); 
		printf("\n     * p - Voltar à página anterior\n");
	}
}

void printOnlyPage(){
		printf("   Opções Disponíveis:");
		printf("\n     * q - Sair;\n");
}

void printLastPage(){
	printf("   Opções Disponíveis:");
	printf("\n     * q - Sair;");
	printf("\n     * p - Avançar para a próxima página.\n");
}

void printHelpTop(){
	printf("|                    AVAILABLE COMMANDS                     |\n");
	for(int i = 0; i < BIGGESTCOMMANDHELP + 1; i++)
		printf("-");
	printf("\n");
}

void printHelpLine(char* comm){
	int aux = (BIGGESTCOMMANDHELP - strlen(comm));
	printf("| %s", comm);
	for(int i = 0; i < aux; i++)
		printf(" ");
	printf("|\n");
	printf(" ");
	for(int i = 0; i < BIGGESTCOMMANDHELP + 1; i++)
		printf("-");
	printf("\n");
}

void printHelp(TABLE t){
	GPtrArray* tableContent = getGPtrArray(t);
	int size = getInsertedData(t);
	int flag = 1;
	if(tableContent){
		int max = 0;
		int i, j, k;
		for(k = 0; (guint) k < tableContent->len; ){
			int lim = k + ITEMSPERPAGE;
			if((guint)lim > tableContent->len) lim = (int) tableContent->len;
			system("clear");
			printHelpTop(max);
			for(j = k; j < lim && flag; j++){
				char* name = strdup((char*) g_ptr_array_index(tableContent, j));
				if(name){
					printHelpLine(name);
					free(name);
				}
				else flag = 0;
			}
			printPageNum(0, 0);
			printSize(tableContent->len);
			if (!flag || ((guint) lim == tableContent->len && j > ITEMSPERPAGE)){
				char code;
				printLastPage();
				if(scanf("%c", &code) == 1){
					if(code == 'q'){
						g_ptr_array_free(tableContent, TRUE);
						system("clear");
						return;
					}
					else if(code == 'p') k -= ITEMSPERPAGE;
				}
			}
			else if((guint) lim == tableContent->len){
				printOnlyPage();
				char code;
				if(scanf("%c", &code) == 1)
					if(code == 'q'){
						g_ptr_array_free(tableContent, TRUE);
						system("clear");
						return;
					}
			}
			else{
				printOptions(j, ITEMSPERPAGE);
				char code;
				if(scanf("%c", &code) == 1){
				if(code == 'q'){
					g_ptr_array_free(tableContent, TRUE);
					system("clear");
					return;
				}
				else if(code == 'p' && j != ITEMSPERPAGE) k -= ITEMSPERPAGE;
				else if (code == 'n' && flag) k += ITEMSPERPAGE;
				}
			}
		}
	}
}	

void printQ3(TABLE t){
	GPtrArray* aux = getGPtrArray(t);
	int max = 0, flag;
	char code;
	char* name = strdup((char*) g_ptr_array_index(aux, 0));
	char* city = strdup((char*) g_ptr_array_index(aux, 1));
	char* state = strdup((char*) g_ptr_array_index(aux, 2));
	float* stars = malloc(sizeof(float));
	*stars = *((float*) g_ptr_array_index(aux, 3));
	int* revs = malloc(sizeof(int));
	*revs = *((int*) g_ptr_array_index(aux, 4));

	system("clear");
	printf("Business Name: %s\n", name);
	printf("Business City: %s\n", city);
	printf("Business State: %s\n", state);
	printf("Business Stars: %f\n", *stars);
	printf("Business Reviews: %d\n", *revs);
	free(name);
	free(city);
	free(state);
	free(stars);
	free(revs);
	printOnlyPage();
	if(scanf("%c", &code) == 1)
		if (code == 'q'){
			g_ptr_array_free(aux, TRUE);
			system("clear");
			return;
		}
}

void printQ2Q4Q5Line(char* id, char* name, int max){
	if(max % 2) max += 3;
	else max += 2;
	int auxName = ((max + 8) - strlen(name)) - 1;
	int aux = max + 34;
	printf("| %s", id);
	printf(" ");
	printf("| %s", name);
	for(int i = 0; i < auxName; i++)
		printf(" ");
	printf("|\n");
	for(int k = 0; k < aux; k++)
		printf("-");
	printf("\n");
}

void printQ2Q4Q5Top(int max){
	if(max % 2) max += 3;
	else max += 2;
	int aux = max + 34;
	printf("|         BUS_ID         |");
	for(int k = 0; k < max / 2; k++)
		printf(" ");
	printf("BUS_NAME");
	for(int j = 0; j < (max / 2); j++)
		printf(" ");
	printf("|\n");
	for(int k = 0; k < aux; k++)
		printf("-");
	printf("\n");
}

void printQ2Q4Q5(TABLE t){
	GPtrArray* q = getGPtrArray(t);
	int maxLenght = 0, flag = 1;
	int size = getInsertedData(t);
	int j, k;
	char** ids = malloc(sizeof(char*) * size + 1);
	char** names = malloc(sizeof(char*) * size + 1);
	for(int m = 0, n = 0; (guint)m < q->len; m++, n++){
		ids[n] = strdup((char*) g_ptr_array_index(q, m++));
		names[n] = strdup((char*) g_ptr_array_index(q, m)); 
		if((int)strlen(names[n]) > maxLenght) maxLenght = (int)strlen(names[n]);
		if((int)strlen(ids[n]) > maxLenght) maxLenght = (int)strlen(ids[n]);
	}
	for(k = 0; k < size; ){
		int lim = k + ITEMSPERPAGE;
		if(lim > size) lim = size;
		system("clear");
		printQ2Q4Q5Top(maxLenght);
		for(j = k; j < lim && flag; j++){
				char* name = strdup(names[j]);
				char* id = strdup(ids[j]);
				if(id && name){
					printQ2Q4Q5Line(id, name, maxLenght);
					free(name);
					free(id);
				}
				else flag = 0;
		}
		printPageNum((k / ITEMSPERPAGE), size / ITEMSPERPAGE);
		printSize(size);
		if (!flag || (lim == size && j > ITEMSPERPAGE)){
				printLastPage();
				char code;
				if(scanf("%c", &code) == 1){
					if(code == 'q'){
							for(int s = 0; s < size; s++){
								free(names[s]);
								free(ids[s]);
							}
							g_ptr_array_free(q, TRUE);
							free(names);
							free(ids);
							return;
					}
					else if(code == 'p') k -= ITEMSPERPAGE;
				}
		}
		else if(lim == size){
			printOnlyPage();
			char code;
			if(scanf("%c", &code) == 1)
				if(code == 'q'){
					for(int s = 0; s < size; s++){
						free(names[s]);
						free(ids[s]);
					}
					g_ptr_array_free(q, TRUE);
					free(names);
					free(ids);
					system("clear");
					return;
				}
		}
		else{
			printOptions(j, ITEMSPERPAGE);
			char code;
			if(scanf("%c", &code) == 1){
				if(code == 'q'){
					for(int s = 0; s < size; s++){
						free(names[s]);
						free(ids[s]);
					}
					g_ptr_array_free(q, TRUE);
					free(names);
					free(ids);
					system("clear");
					return;
				}
				else if(code == 'p' && j != ITEMSPERPAGE) k -= ITEMSPERPAGE;
				else if (code == 'n' && flag) k += ITEMSPERPAGE;
			}
		}
	}
	for(int s = 0; s < size; s++){
		free(names[s]);
		free(ids[s]);
	}
	g_ptr_array_free(q, TRUE);
	free(names);
	free(ids);
}

void printQ6Top(int max){
	if(max % 2) max += 3;
	else max += 2;
	int aux = (2 * max) + 55;
	printf("|         BUS_ID         |");
	for(int k = 0; k < max / 2; k++)
		printf(" ");
	printf("BUS_NAME");
	for(int j = 0; j < (max / 2); j++)
		printf(" ");
	printf("|");
	for(int j = 0; j < (max / 2); j++)
		printf(" ");
	printf("BUS_CITY");
	for(int j = 0; j < (max / 2); j++)
		printf(" ");
	printf("| ");
	printf("BUS_STARS |");
	printf("\n");
	for(int k = 0; k < aux; k++)
		printf("-");
	printf("\n");
}

void printQ6Line(char* id, char* name, char* city, float av, int max){
	if(max % 2) max += 3;
	else max += 2;
	int auxName = ((max + 8) - strlen(name)) - 1;
	int auxCity = ((max + 8) - strlen(city)) - 1;
	int aux = (2 * max) + 55;
	printf("| %s", id);
	printf(" ");
	printf("| %s", name);
	for(int i = 0; i < auxName; i++)
		printf(" ");
	printf("| %s", city);
	for(int i = 0; i < auxCity; i++)
		printf(" ");
	printf("| %f  |", av);
	printf("\n");
	for(int k = 0; k < aux; k++)
		printf("-");
	printf("\n");
}

void printQ6(TABLE t){
	GPtrArray* aux = getGPtrArray(t);
	int size = getInsertedData(t);
	int nPars = getNCols(t);
	if(aux){
		int max = 0, i, j, k;
		int flag = 1;
		for(int m = 0; (guint)m < aux->len; m++){
			char* id = strdup(g_ptr_array_index(aux, m++));
			char* name = strdup(g_ptr_array_index(aux, m++));
			char* city = strdup(g_ptr_array_index(aux, m++));
			if((int) strlen(id) > max) max = (int)strlen(id);
			if((int) strlen(name) > max) max = (int)strlen(name);
			if((int) strlen(city) > max) max = (int)strlen(city);
			free(id);
			free(name);
			free(city);
		}
		for(i = 0; (guint)i < aux->len; ){
			int lim = i + (ITEMSPERPAGE * nPars);
			if ((guint)lim > aux->len) lim = (int)aux->len;
			system("clear");
			printQ6Top(max);
			for(j = i; j < lim && flag; j++){
				char* id = strdup(g_ptr_array_index(aux, j++));
				char* name = strdup(g_ptr_array_index(aux, j++));
				char* city = strdup(g_ptr_array_index(aux, j++));
				float* av = malloc(sizeof(float));
				*av = *((float*) g_ptr_array_index(aux, j));
				if(id && name && city && av){
					printQ6Line(id, name, city, *av, max);
					free(id);
					free(name);
					free(city);
					free(av);
				}
				else flag = 0;
			}
			printPageNum(((i / nPars) / ITEMSPERPAGE), size / ITEMSPERPAGE);
			printSize(size);
			if(!flag || ((guint)lim == aux->len && j > ITEMSPERPAGE * nPars)){
				char code;
				printLastPage();
				if(scanf("%c", &code) == 1){
					if(code == 'q'){
						g_ptr_array_free(aux, TRUE);
						system("clear");
						return;
					}
					else if(code == 'p') i -= (ITEMSPERPAGE * nPars);
				}
			}
			else if((guint)lim == aux->len){
				printOnlyPage();
				char code;
				if(scanf("%c", &code) == 1)
					if(code == 'q'){
						g_ptr_array_free(aux, TRUE);
						system("clear");
						return;
					}
			}
			else{
				printOptions(j, ITEMSPERPAGE * nPars);
				char code;
				if(scanf("%c", &code) == 1){
					if(code == 'q'){
						g_ptr_array_free(aux, TRUE);
						system("clear");
						return;
					}
					else if(code == 'p' && j != ITEMSPERPAGE * nPars) i -= (ITEMSPERPAGE * nPars);
					else if (code == 'n' && flag) i += (ITEMSPERPAGE * nPars);
				}
			}
		}
	}
}

void printQ7Top(){
	printf("|         USR_ID         |");
	printf("\n ");
	for(int i = 0; i < 24; i++)
		printf("-");
	printf("\n");
}

void printQ7Line(char* id){
	printf("| %s |\n ", id);
	for(int i = 0; i < 24; i++)
		printf("-");
	printf("\n");
}

void printQ7(TABLE t){
	GPtrArray* aux = getGPtrArray(t);
	int size = getInsertedData(t);
	if(aux){
		int i, j, k;
		int flag = 1;
		for(i = 0; (guint)i < aux->len; ){
			int lim = i + ITEMSPERPAGE;
			if((guint)lim > aux->len) lim = (int)aux->len;
			system("clear");
			printQ7Top();
			for(j = i; j < lim && flag; j++){
				char* id = strdup(g_ptr_array_index(aux, j));
				if(id){
					printQ7Line(id);
					free(id);
				}
				else flag = 0;
			}
			printPageNum((i / ITEMSPERPAGE), size / ITEMSPERPAGE);
			printSize(size);
			if(!flag || ((guint)lim == aux->len && j > ITEMSPERPAGE)){
				char code;
				printLastPage();
				if(scanf("%c", &code) == 1){
					if(code == 'q'){
						g_ptr_array_free(aux, TRUE);
						system("clear");
						return;
					}
					else if(code == 'p') i -= ITEMSPERPAGE ;
				}
			}
			else if((guint)lim == aux->len){
				printOnlyPage();
				char code;
				if(scanf("%c", &code) == 1)
					if(code == 'q'){
						g_ptr_array_free(aux, TRUE);
						system("clear");
						return;
					}
			}
			else{
				printOptions(j, ITEMSPERPAGE);
				char code;
				if(scanf("%c", &code) == 1){
					if(code == 'q'){
						g_ptr_array_free(aux, TRUE);
						system("clear");
						return;
					}
					else if(code == 'p' && j != ITEMSPERPAGE) i -= ITEMSPERPAGE;
					else if (code == 'n' && flag) i += ITEMSPERPAGE;
				}
			}
		}
	}
}

void printQ8Line(char* id, char* name, float av, int max){
	if(max % 2) max += 3;
	else max += 2;
	int auxName = ((max + 8) - strlen(name)) - 1;
	int aux = max + 46;
	printf("| %s", id);
	printf(" ");
	printf("| %s", name);
	for(int i = 0; i < auxName; i++)
		printf(" ");
	printf("| %f  |", av);
	printf("\n");
	for(int k = 0; k < aux; k++)
		printf("-");
	printf("\n");
}

void printQ8Top(int max){
	if(max % 2) max += 3;
	else max += 2;
	int aux = max + 46;
	printf("|         BUS_ID         |");
	for(int k = 0; k < max / 2; k++)
		printf(" ");
	printf("BUS_NAME");
	for(int j = 0; j < (max / 2); j++)
		printf(" ");
	printf("| ");
	printf("BUS_STARS |");
	printf("\n");
	for(int k = 0; k < aux; k++)
		printf("-");
	printf("\n");
}

void printQ8(TABLE t){
	GPtrArray* aux = getGPtrArray(t);
	int size = getInsertedData(t);
	int nPars = getNCols(t);
	if(aux){
		int max = 0, i, j, k;
		int flag = 1;
		for(int m = 0; (guint)m < aux->len; m++){
			char* id = strdup(g_ptr_array_index(aux, m++));
			char* name = strdup(g_ptr_array_index(aux, m++));
			if((int)strlen(id) > max) max = (int)strlen(id);
			if((int)strlen(name) > max) max = (int)strlen(name);
			free(id);
			free(name);
		}
		for(i = 0; (guint)i < aux->len; ){
			int lim = i + (ITEMSPERPAGE * nPars);
			if ((guint)lim > aux->len) lim = (int)aux->len;
			system("clear");
			printQ8Top(max);
			for(j = i; j < lim && flag; j++){
				char* id = strdup(g_ptr_array_index(aux, j++));
				char* name = strdup(g_ptr_array_index(aux, j++));
				float* av = malloc(sizeof(float));
				*av = *((float*) g_ptr_array_index(aux, j));
				if(id && name && av){
					printQ8Line(id, name,*av, max);
					free(id);
					free(name);
					free(av);
				}
				else flag = 0;
			}
			printPageNum(((i / nPars) / ITEMSPERPAGE), size / ITEMSPERPAGE);
			printSize(size);
			if(!flag || ((guint)lim == aux->len && j > ITEMSPERPAGE * nPars)){
				printLastPage();
				char code;
				if(scanf("%c", &code) == 1){
					if(code == 'q'){
						g_ptr_array_free(aux, TRUE);
						system("clear");
						return;
					}
					else if(code == 'p') i -= (ITEMSPERPAGE * nPars);
				}
			}
			else if((guint)lim == aux->len){
				printOnlyPage();
				char code;
				if(scanf("%c", &code) == 1)
					if(code == 'q'){
						g_ptr_array_free(aux, TRUE);
						system("clear");
						return;
					}
			}
			else{
				printOptions(j, ITEMSPERPAGE * nPars);
				char code;
				if(scanf("%c", &code) == 1){
					if(code == 'q'){
						g_ptr_array_free(aux, TRUE);
						system("clear");
						return;
					}
					else if(code == 'p' && j != ITEMSPERPAGE * nPars) i -= (ITEMSPERPAGE * nPars);
					else if (code == 'n' && flag) i += (ITEMSPERPAGE * nPars);
				}
			}
		}
	}
}

void printQ9Top(){
	printf("|         REV_ID         |");
	printf("\n ");
	for(int i = 0; i < 24; i++)
		printf("-");
	printf("\n");
}

void printQ9Line(char* id){
	printf("| %s |\n ", id);
	for(int i = 0; i < 24; i++)
		printf("-");
	printf("\n");
}

void printQ9(TABLE t){
	GPtrArray* aux = getGPtrArray(t);
	int size = getInsertedData(t);
	if(aux){
		int i, j, k;
		int flag = 1;
		for(i = 0; (guint)i < aux->len; ){
			int lim = i + ITEMSPERPAGE;
			if((guint)lim > aux->len) lim = (int)aux->len;
			system("clear");
			printQ9Top();
			for(j = i; j < lim; j++){
				char* id = strdup(g_ptr_array_index(aux, j));
				if(id){
					printQ9Line(id);
					free(id);
				}
				else flag = 0;
			}
			printPageNum((i / ITEMSPERPAGE), size / ITEMSPERPAGE);
			printSize(size);
			if(!flag || ((guint)lim == aux->len && j > ITEMSPERPAGE)){
				char code;
				printLastPage();
				if(scanf("%c", &code) == 1){
					if(code == 'q') return;
					else if(code == 'p') i -= ITEMSPERPAGE;
				}
			}
			else if((guint)lim == aux->len){
				printOnlyPage();
				char code;
				if(scanf("%c", &code) == 1)
					if(code == 'q'){
						g_ptr_array_free(aux, TRUE);
						system("clear");
						return;
					}
			}
			else{
				printOptions(j, ITEMSPERPAGE);
				char code;
				if(scanf("%c", &code) == 1){
					if(code == 'q'){
						g_ptr_array_free(aux, TRUE);
						system("clear");
						return;
					}
					else if(code == 'p' && j > ITEMSPERPAGE) i -= ITEMSPERPAGE;
					else if (code == 'n' && flag) i += ITEMSPERPAGE;
				}
			}
		}
	}
}

 
