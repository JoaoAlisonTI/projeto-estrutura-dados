#include <stdio.h>
#include "Site.h"
#include <string.h>

Site *Site_create(char *nome, char palavras[][30], int qtdPalavras){
    Site *s = malloc(sizeof(Site));
    if(s == NULL){
        printf("Erro ao alocar memória para Site.\n");
        exit(1);
    }

    //copiar nome do site
    strncpy(s->nome, nome, 50);

    //copiar palavras chave do site
    s->qtdPalavras = qtdPalavras;
    for(int i = 0; i < qtdPalavras; i++){
        strncpy(s->palavras[i], palavras[i], 30);
    }

    //importancia
    s->importancia = 0;

    return s;
}

void Graph_insertSite(Graph *g, Site *site){
    if(g == NULL || site == NULL){
        printf("Erro: grafo ou site inválido.\n");;
        return;
    }

    Graph_insertVertex(g, (void*)site);
}

void Site_print(Site *s){
    printf("Site: %s\n", s->nome);
    printf("Importância: %d\n", s->importancia);
    printf("Palavras-chave (%d): ", s->qtdPalavras);

    for(int i = 0; i < s->palavras; i++){
        printf("%s ", s->palavras[i]);
    }

    printf("\n");
}

//função de comparação para localizar um site no grafo
int Site_cmp(void *a, void *b){
    Site *s1 = (Site*) a;
    Site *s2 = (Site*) b;

    return strcmp(s1->nome, s2->nome);
}

void Graph_insertLink(Graph *g, Site *origem, Site *destino){
    if(g == NULL || origem == NULL || destino == NULL){
        printf("Erro: parâmetros inválidos.\n");
        return;
    }

    Vertex *v1 = Graph_findByValue(g, origem, Site_cmp);
    Vertex *v2 = Graph_findByValue(g, origem, Site_cmp);

    if(v1 == NULL || v2 == NULL){
        printf("Erro: site de origem ou destino não encontrado no grafo.");
        return;
    }

    Graph_insertEdge(g, v1->label, v2->label, NULL);
}

void Graph_calcularImportancia(Graph *g){
    if(g == NULL) return;

    Vertex *vAtual = g->first;

    //para cada vertice do gráfico
    while(vAtual){

        int grauEntrada = 0;
        Vertex *vAux = g->first;

        //percorre todos os vertices procurando arestas que apontam para vAtual
        while(vAux){
            Edge *e = vAux->first;

            while(e){
                if(e->head == vAtual){
                    grauEntrada++;
                }
                e = e->next;
            }
            vAux = vAux->next;
        }

        //atualiza a importância do site
        Site *site = (Site*) vAtual->value;
        site->importancia = grauEntrada;

        vAtual = vAtual->next;

    }
}