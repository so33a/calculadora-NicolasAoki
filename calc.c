#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#define MAX 1000

typedef struct node * link;
struct node {
  int item;
  link next;
};

struct pilha {
  link topo;
};

link novoNo (int item, link next) {
  link n = malloc(sizeof (struct node));
  if(n == NULL) {
    printf ("Erro ao alocar no\n");
    exit(-1);
  }
  n->item = item;
  n->next = next;
  return n;
}
Pilha novaPilha() {
    Pilha p = malloc(sizeof (struct pilha));
    if(p == NULL)
        printf("erro na alocação"); exit(-1);
    p->topo = NULL;
    return p;
}
void push(Pilha p, int item){
    link t = novoNo(item, NULL);
    if(p->topo == NULL){
        p->topo = t;
        return;
    }
    t->next = p->topo;
    p->topo = t;
}
int pop(Pilha p){
    int aux;
    link t;
    if(p->topo == NULL)
        printf("pilha vazia"); exit(-1);
    aux = p->topo->item;
    t = p->topo;
    p->topo = t->next;
    free(t);
    return aux;
}
int estaVazia(Pilha p) {
  return (p->topo == NULL);
}
int pegaTopo(Pilha p) {
  if (p->topo == NULL) {
    printf("Pilha vazia");
    exit(-1);
  }
  return p->topo->item;
}
void destroiPilha(Pilha p){
    while(!estaVazia(p)){
        pop(p);
    }
    free(p);
}
void imprimePilha(Pilha p){
    link t = p->topo;
    while(t->next != NULL){
        printf("%d", t->next);
        t = t->next;
    }
}
int bemEncaixado(char *s){

    Pilha p = novaPilha();
    int i, resultado = 1;
    for(i=0; s[i] != '\0'; i++){
        if(texto[i] == '(') {
            push(p,1);
        }else if(s[i] == ')'){
          if(p->topo == NULL)  
            resultado = 0;
          else 
            pop(p);
        }
    }
    if (p->topo > 0)
        resultado = 0;
    destroiPilha(p);
    return resultado;
}

/* Transforma a notação infixa para a notação posfixa */
int infixoParaPosfixo (char * entrada, char * saida, int n)
{
    Pilha p = novaPilha();
    int i,k ;
    int j = 0;
    char c;
    push(p, '(');
    for (i = 0; entrada[i] != '\0' &&  i < n; i++)
        {
            if((j-1 > 0) && (saida[j-1] != ' '))
                saida[j++]  = ' ';
            if(entrada[i] == '(') {
                push(p, entrada[i]);
            } else if(entrada[i] == ')'){
                while (1) {
                    c = pop(p);
                    if(c == '(') break;
                    saida[j++] = c;
                    saida[j++] = ' ';
                }
            } else if((entrada[i] == '+') || (entrada[i] == '-')){
                while (1) {
                    c = topo(p);
                    if(c == '(') break;
                    pop(p);
                    saida[j++] = c;
                    saida[j++] = ' ';
                }
                push(p, entrada[i]);
            } else if((entrada[i] == '*') || (entrada[i] == '/')) {
                while (1) {
                    c = topo(p);
                    if(c == '(' || c == '+' || c == '-'  ) break;
                    pop(p);
                    saida[j++] = c;
                    saida[j++] = ' ';
                }
                push(p, entrada[i]);
            } else if (entrada[i] >= '0' && entrada[i] <= '9') {
                while (entrada[i] >= '0' && entrada[i] <= '9') {
                    saida[j++] = entrada[i];
                    i++;
                }
                saida[j++] = ' ';
                i--;
            }

        }
    while (1) {
        c = pop(p);
        if(c == '(') break;
        saida[j++] = c;
        saida[j++] = ' ';
    }
    saida[j] = '\0';
    destroiPilha(p);
    return 0;
}




int calcula ( char * s ) {
    int i = 0;
    int d = 0,k;
    int numero = 0;
    Pilha p = novaPilha();
    int resultado ;
    int a,b;
    while  (s[i] != '\0') {
        if(s[i] >= '0' && s[i] <= '9' ) {
            sscanf(&s[i], "%d", & numero);
            while(s[i] >= '0' && s[i] <= '9')
                i++;
            i--;
            push(p, numero);
        } else if (s[i] == '+') {
            b = pop(p);
            a = pop(p);
            push (p, a + b);
        } else if (s[i] == '-') {
            b = pop(p);
            a = pop(p);
            push (p, a - b);
        } else if (s[i] == '*') {
            b = pop(p);
            a = pop(p);
            push (p, a * b);
        } else if (s[i] == '/') {
            b = pop(p);
            a = pop(p);
            push (p, a/b);
        }
        i++;
    }

    resultado = topo(p);
    destroiPilha(p);
    return resultado;
}



/* Exemplo de utilização */
int main () {
    char infixo[255] ;
    char posfixo[255];
    printf("Sou uma calculadora de inteiros implementado com pilha!\n");
    printf("Digite quit para sair !\n");
    printf ("> ");
    while(fgets(infixo, 255, stdin) != NULL) {
        if(strcmp(infixo, "quit\n") == 0)  {
            printf ("morri !\n");
            return 0;
        }
        if(bemEncaixado(infixo)) {
            infixoParaPosfixo(infixo, posfixo, 255);
            printf("%d\n", calcula(posfixo));
        } else
            printf ("Erro nos parenteses\n");
        printf ("> ");
    }
    return 0;
}
