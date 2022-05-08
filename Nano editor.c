#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Nod{

    char data;
    struct Nod *prev;
    struct Nod *next;
}node_t;

typedef struct nod_stiva {

    char data;
    struct nod_stiva *next;
}nod_stiva;

void init(node_t* lst){

    lst = (node_t*) malloc(sizeof(node_t));
    lst->next = lst->prev = NULL;
}

nod_stiva* initStack() {

    nod_stiva* s;
    return s=NULL;
}

void adaugare(node_t* nou, node_t* pos){

    nou->prev=pos;
    nou->next=pos->next;
    if(pos->next!=NULL)
        pos->next->prev=nou;
    pos->next=nou;
}

nod_stiva* push(nod_stiva* s,char el){

    nod_stiva* t;
    t = (nod_stiva*) malloc(sizeof(nod_stiva));
    if (t == NULL) {
        printf("memorie insuficienta\n");
        return NULL;
        }
    t->data = el;
    t->next = s;
    return t;
}

nod_stiva* pop(nod_stiva*s){

    char el;
    nod_stiva* t;
    if (s == NULL) {
        printf("stiva vida\n");
        return NULL;
    }
    el = s->data;
    printf ("Elementul din stiva este %d\n", el);
    t = s;
    s = s->next;
    free(t);
    return s;
}

void top(nod_stiva *s) {

    char e;
    nod_stiva* aux;
    aux = s;
    e = aux->data;
    printf("Elementul din varful stivei este %d\n", e);
}

void scoatere(node_t* pos){

    pos->prev->next=pos->next;
    if(pos->next!=NULL)
        pos->next->prev=pos->prev;
}

node_t* n_element ( const node_t * head , int n ){

    int nr=1;
    while (head->next != NULL ){
        if (nr==n)
            return head;
        head=head->next;
        nr++;
    }
    return head;
}

node_t* cautare(node_t* lst, char x){

    node_t* p = lst->next;
    while(p->data!=x && p!=NULL){
        p=p->next;
        }
    if(p==NULL)
        return NULL;
    return p;

}

void push_back ( node_t ** head , node_t * new_node ){

    node_t* lst = (node_t*) malloc(sizeof(node_t));
    lst->next = lst->prev = NULL;

    node_t* gata=*head;
    new_node->next=NULL;
    if (*head==NULL) {
        new_node->prev=NULL;
        *head=new_node;
        return;
        }
    while (gata->next!=NULL)
        gata=gata->next;
    gata->next=new_node;
    new_node->prev=gata;
    return;
}


void backspace(node_t* pos ){
    scoatere(pos);
}


node_t* parcurgere_lista(node_t* list, int n){

    int i;
    node_t* p=list;
    for(i=0;i<n;i++)
        p=p->next;
    return p;

}
node_t* glline(node_t* list, int nr_linie){   

int i,k=1;                   
    node_t* p=list;
    do{
            if(p->data == '\n'){

                k++;
            }

            p=p->next;
            }while(p->next!=NULL && k<nr_linie);

            return p;
}

node_t* gcchar(node_t* list, int nr_linie, int nr_caracter){

    list=glline(list,nr_linie);
    int k=1;
    node_t* p=list;
    while(p->next!=NULL && k<nr_caracter){
            k++;
            p=p->next;

    }

return p;
}

int nr_linii(node_t* list, node_t* element_curent){
int nr_linie=1;
while(list->next != NULL && list!=element_curent){
        if(list->data=='\n')
        nr_linie++;

    list=list->next;
}
return nr_linie;


}

void dlline(node_t* list, int nr_linie){   

list= glline(list,nr_linie);
if(nr_linie!=1)
    backspace(list->prev);

while(list->data!='\n'){
        backspace(list);
        list=list->next;


}
if(nr_linie==1)
    backspace(list);


}


void ddelete(node_t* list, int nr_caractere){
    list=list->next;
    int k=0;
    while(k<nr_caractere){
        backspace(list);
        k++;
        list=list->next;
    }




}

void undo_function(node_t* undo,node_t** list){
(*list)=undo->prev;
(*list)->next=NULL;
}

void redo_function(node_t* undo ,node_t* redo, node_t** list){

(*list)->next=undo;
(*list)=redo;
(*list)->next=NULL;
(*list)->data='\n';

}



void citire(node_t* list, FILE* pFILE)
{
	char c;

	char x[5]="xx";
    char cmd[20];
    FILE* fout;
    int k=0;
    node_t* nod;
    node_t* undo;
    node_t* redo;
    node_t* list_copy=list;
    if (pFILE == NULL)
        printf("Nu s-a putut deschide fisierul");

    do {
		c=fgetc(pFILE);
        if (c != ':') {


        nod=(node_t*)malloc(sizeof(node_t));
        nod->data=c;
        adaugare(nod,list);
        list=nod;
        if(k==0)
            undo=list;
        k++;


        }
        if (c == ':' )
        {
            redo=list;
            k=0;
            c=fgetc(pFILE);
            c=fgetc(pFILE);
            c=fgetc(pFILE);
            fgets(cmd,20,pFILE);
            while (strcmp(cmd, "::i\n") != 0 )
            {
            if(strcmp(cmd,"b\n") == 0){
                backspace(list);
                list=list->prev;
                }
            if(strcmp(cmd,"s\n") == 0)
                {
                  fout=fopen("editor1.out" , "w");
                  node_t* p = list_copy;
                    while (p->next) {
                        fprintf(fout, "%c", p->next->data);
                        p = p->next;
                        }
                }
            if(strcmp(cmd,"q\n") == 0)
                {
                   //quit();
                }
            if(strncmp(cmd,"gl",2) == 0)
                {   char *token=strtok(cmd," ");
                    char *token2=strtok(NULL," \n");

                    list=glline(list_copy->next,atoi(token2))->prev;

                }
            if(strncmp(cmd,"gc", 2) == 0)                                         
                {   char *token=strtok(cmd, " ");
                    char *token2=strtok(NULL, " ");
                    char *token3=strtok(NULL," \n");
                    if(token3!=NULL)
                    list=gcchar(list_copy,atoi(token3),atoi(token2));
                    else
                        list=gcchar(list_copy,nr_linii(list_copy,list->next),atoi(token2));
                    }else

                    if(strncmp(cmd,"dl", 2) == 0){
                    char *token=strtok(cmd," ");
                    char *token2=strtok(NULL," \n");
                    if(token2!=NULL)
                    dlline(list_copy,atoi(token2));
                    else
                        dlline(list_copy, nr_linii(list_copy,list->next));

                    }else
            if(strncmp(cmd,"d",1) == 0)
                {   char *token=strtok(cmd," ");
                    char *token2=strtok(NULL," \n");
                    if(token2!=NULL)
                    ddelete(list,atoi(token2));
                    else
                        ddelete(list,1);
                }else
                if(strcmp(cmd,"u\n") == 0)
                {

                    list=undo->prev;
                    list->next=NULL;
                }else
                if(strcmp(cmd,"r\n") == 0)
                {
                    list->next=undo;
                    list=redo;
                    list->next=NULL;
                    list->data='\n';

                }


            if(feof(pFILE))
                break;
            fgets(cmd,20,pFILE);
            }
        }
        if(feof(pFILE))
            break;

        }while(1);
}

void afisare(node_t* lst){

    node_t* p=lst->next;
    while(p!=NULL){
        printf("%c",p->data);
        p=p->next;
        }
}


void printL (node_t* lst) {

    if (lst != NULL){
        printf ("%c", lst->data);
        printL (lst->next);
        }
}




int main(){
    FILE *pFILE;
    pFILE = fopen("editor.in", "r");
    node_t* lst;
    lst=(node_t*) malloc(sizeof(node_t));
    lst->next=NULL;
    lst->prev=NULL;

    citire(lst,pFILE);
    lst=lst->next;
    printL(lst);



}
