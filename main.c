#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "parsef.h"

int main(int argc, char *argv[])
{
    printf("Parseur C");
    for (int i = 1; i < argc; i++)
    {
        // On indique le nom de chaque fichier ajouter
        printf("\nFichier N°%d = %s", i, argv[i]);
    }
    /* ------------------------------------------------------------------------- */
    /*Vérification de l'ouverture des fichiers                                   */
    /* ------------------------------------------------------------------------- */
    for (int i = 1; i < argc; i++)
    {
        // On indique le nom du fichier sur lequel on travail
        printf("\nargv[%d] = %s", i, argv[i]);
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL)
        {
            printf("\nErreur: Impossible de lire le fichier %s", argv[i]);
            return 1;
        }

        dataStruct *head = NULL;
        dataStruct *current = NULL;

        // On se place à la fin pour définir la taille du fichier
        fseek(fp, 0, SEEK_END);
        int sz = ftell(fp);
        rewind(fp);
        // On initialise un buffer qui va contenir tout le fichier
        char *bufTmp=(char *)malloc(sz*sizeof(char));
        fread(bufTmp,sz,1,fp);
        // On ferme le fichier
        fflush(fp);
        fclose(fp);
        bufTmp[sz]='\0';
        // On contrôle le début et la fin
        if (formatOk (bufTmp)==1) {
            // On supprime le premier et dernier Caractère
            bufTmp[0]=' ';
            bufTmp[sz-1]=' ';
            char delim[] = ",";
            char *ptr = strtok(bufTmp, delim);
            //On entre dans une boucle while afin de vérifier le type de chaque elements
            while(ptr != NULL)
            {
                char *ptr2=trim(ptr);
                //On alloue la mémoire necessaire à chaque éléments
                dataStruct *element = (dataStruct *)malloc(sizeof(dataStruct));
                element->type=-1;
                element->next = NULL;
                //On effectue les tests pour chaque éléments jusqu'à trouver celui qui correspond
                if (isBoolean(ptr2)) {
                    element->type = 0;
                } else if (isInt(ptr2)) {
                    element->type = 1;
                } else if (isFloat(ptr2)) {
                    element->type = 2;
                } else if (isString(ptr2)) {
                    element->type = 3;
                } else if (isFalseBoolean(ptr2)) {
                    element->type = 4;
                } else {
                    element->type = 5;
                }
                if (element->type>=0) {
                    element->data = (char *)malloc(sizeof(char) * (strlen(ptr2) + 1));
                    strcpy(element->data, ptr2);
                }

                if (head == NULL)
                {
                    // Premier élément de la liste
                    head = element;
                    current = element;
                }
                else
                {
                    // Ajouter l'élément à la fin de la liste
                    current->next = element;
                    current = element;
                }

                ptr = strtok(NULL, delim);
            }
        }
        free(bufTmp);
        // Appel de la fonction pour l'affichage
        print_elements(head);
    }
    return 0;
}
/* ------------------------------------------------------------------------- */
/*Vérification des éléments pour en trouver le type                          */
/* ------------------------------------------------------------------------- */
//Test pour le type string
bool isString(char *ptr2) {
    if (ptr2[0]=='"' && ptr2[strlen(ptr2)-1]=='"') return 1;
    return 0;
}
//Test pour le type int
bool isInt(char *ptr2) {
    if (strspn(ptr2, "+-0123456789") == strlen(ptr2)) return 1;
    return 0;
}
//Test pour le type float
bool isFloat(char *ptr2) {
    if (strspn(ptr2, "+-0123456789.") == strlen(ptr2)) return 1;
    return 0;
}
//Test pour le type boolean
bool isBoolean(char *ptr2) {
    if (strcmp(ptr2,"false")==0 || strcmp(ptr2,"true")==0) return 1;
    return 0;
}
//Fonction pour enlever les majuscule d'un faux boolean
char * strtolower( char * dest, const char * src ) {
    char * result = dest;
    while( *dest++ = tolower( *src++ ) );
    return result;
}
//Test pour le type faux boolean
bool isFalseBoolean(char *ptr2) {
    char * result = malloc(sizeof(strlen(ptr2)));
    bool retour=0;
    strtolower(result,ptr2);
    if (strcmp(result,"false")==0 || strcmp(result,"true")==0) retour=1;
    free(result);
    return retour;
}
/* ------------------------------------------------------------------------- */
/*Vérification du bon format du fichier et suppression des espaces en trop   */
/* ------------------------------------------------------------------------- */
int formatOk(char *tmp) {
    if (tmp[0]=='[' && tmp[strlen(tmp)-1]==']') return 1;
    return 0;
}

char *ltrim(char *s)
{
    while(*s==' ') s++;
    return s;
}

char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while((*--back)==' ');
    *(back+1) = '\0';
    return s;
}

char *trim(char *string) {
    return rtrim(ltrim(string));
}
/* ------------------------------------------------------------------------- */
/*Affichage du type et du contenu de l'élément en utilisant                  */
/*les valeur attribuée après les tests                                       */
/* ------------------------------------------------------------------------- */
void print_elements(dataStruct *head)
{
    char *types[] = {"boolean", "integer", "float", "string", "Faux boolean", "Element non valide"};

    dataStruct *current = head;
    int i = 0;
    while (current != NULL)
    {
        printf("\n");
        printf("%d:\n", i);
        printf("type: %s\n", types[current->type]);
        printf("content: %s\n", current->data);
        current = current->next;
        i++;
    }

    // libérer la mémoire
    current = head;
    while (current != NULL)
    {
        dataStruct *next = current->next;
        free(current);
        current = next;
    }
}