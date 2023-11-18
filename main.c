#include "Analyseur_Lexical.h"
#include "Analyseur_Syntaxique_Semantique.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *readFileToString(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier '%s'\n", filename);
        return NULL;
    }
    fseek(file, 0, SEEK_END); 
    long fileSize = ftell(file); 
    fseek(file, 0, SEEK_SET); 
    char *fileContent = (char *)malloc(fileSize + 1);

    if (fileContent == NULL) {
        fclose(file);
        fprintf(stderr, "Allocation mémoire échouée\n");
        return NULL;
    }
    size_t bytesRead = fread(fileContent, 1, fileSize, file);
    fileContent[bytesRead] = '\0'; 
    fclose(file);
    return fileContent;
}


int main() {
    const char *filename = "program.txt"; 
    char *content = readFileToString(filename);
    if (content != NULL) {
        printf("Contenu du fichier à compiler:\n%s\n", content);
    } else {
        printf("Lecture échouée.\n");
    }
    //Analyse lexicale
    size_t numTokens;
    UnitLex *ul = analyseur(content, &numTokens);
    if (ul != NULL) {
        printf("Nombre d'unités lexicales: %zu\n", numTokens);
        printf("Unité lexicale:\n");
        for (size_t i = 0; i < numTokens; ++i) {
            printf("%s ", UnitLexTab[ul[i]]); 
            strcpy(unitelexicales[i],UnitLexTab[ul[i]]);
        }
        printf("\n");
        free(ul); 
    } else {
        printf("Analyse lexicale échouée.\n");
    }
    //Début de l'analyse syntaxique + sémantique
    P(); //appel à la fonction de départ

    
    free(content);
    return EXIT_SUCCESS;
}
