#ifndef ANALYSEUR_SYNTAXIQUE_SEMANTIQUE
#define ANALYSEUR_SYNTAXIQUE_SEMANTIQUE
#include <ctype.h>
#include "Analyseur_Lexical.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *unitelexicales[2000][100];
int num_ul =0;
int ul_courant=0;

void avancer(){
    ul_courant++;
}
void accepter(const char *ul_attendu){
    if(strcmp(unitelexicales[ul_courant],ul_attendu)==0){
        avancer();
    }else{
        printf("Erreur de syntaxe: '%s' est attendu, mais on a trouvé '%s' \n", ul_attendu,unitelexicales[ul_courant]);
    }
}
void signaler_erreur(const char *message) {
    printf("Erreur: %s\n", message);
    exit(EXIT_FAILURE);
}
//Initialisation des règles de la grammaire
void P();
void DCL();
void DCL_prime();
void Liste_id();
void Liste_id_prime();
void Type();
void Inst_composee();
void Inst();
void Exp();
void Exp_prime();
void Exp_simple();
void Exp_simple_prime();
void Terme();
void Terme_prime();
void Facteur();

void P(){
    accepter("MOT_CLE_PROGRAM");
    accepter("IDENTIFICATEUR");
    accepter("POINT_VIRGULE");
    DCL();
    Inst_composee();
    accepter("POINT");
}
void DCL(){
    if (strcmp(unitelexicales[ul_courant],"var")==0){
        avancer();
        Liste_id();
        accepter("DEUX_POINTS");
        Type();
        DCL_prime();
    }
}
void DCL_prime() {
    if (strcmp(unitelexicales[ul_courant], ";") == 0) {
        avancer();
        DCL();
    }
}
void Liste_id(){
    accepter("IDENTIFICATEUR");
    Liste_id_prime();
}
void Liste_id_prime(){
    if(strcmp(unitelexicales[ul_courant],",")==0){
        avancer();
        accepter("IDENTIFICATEUR");
        Liste_id_prime();
    }
}
void Type(){
    if(strcmp(unitelexicales[ul_courant],'MOT_CLE_INTEGER')==0 || strcmp(unitelexicales[ul_courant],"CHAR")==0){
        avancer();
    }else{
        printf("Erreur de syntaxe: Type invalide 's'\n",unitelexicales[ul_courant]);
    }
}
void Inst_composee(){
    accepter("MOT_CLE_BEGIN");
    Inst();
    accepter("MOT_CLE_END");
}
void Inst() {
    if (strcmp(unitelexicales[ul_courant], "IDENTIFICATEUR") == 0) {
        avancer();
        accepter("EGAL");
        Exp_simple();
    } else if (strcmp(unitelexicales[ul_courant], "MOT_CLE_IF") == 0) {
        avancer();
        Exp();
        accepter("then");
        Inst();
        accepter("else");
        Inst();
    } else if (strcmp(unitelexicales[ul_courant], "MOT_CLE_WHILE") == 0) {
        avancer();
        Exp();
        accepter("do");
        Inst();
    } else if (strcmp(unitelexicales[ul_courant], "MOT_CLE_READ") == 0 || strcmp(unitelexicales[ul_courant], "MOT_CLE_READLN") == 0 ||
               strcmp(unitelexicales[ul_courant], "MOT_CLE_WRITE") == 0 || strcmp(unitelexicales[ul_courant], "MOT_CLE_WRITELN") == 0) {
        avancer();
        accepter("PARENTHESE_OUVRANTE");
        accepter("IDENTIFICATEUR");
        accepter("PARENTHESE_FERMENTE");
    } else {
        printf("Erreur de syntaxe: Instruction invalide '%s'\n", unitelexicales[ul_courant]);
    }
}
void Exp(){
    Exp_simple();
    Exp_prime();
}
void Exp_prime() {
    if (strcmp(unitelexicales[ul_courant], "EGAL") == 0 || strcmp(unitelexicales[ul_courant], "DIFF") == 0 ||
        strcmp(unitelexicales[ul_courant], "INF") == 0 || strcmp(unitelexicales[ul_courant], "SUP") == 0 ||
        strcmp(unitelexicales[ul_courant], "INF_EGAL") == 0 || strcmp(unitelexicales[ul_courant], "SUP_EGAL") == 0) {
        avancer();
        Exp_simple();
    }
}
void Exp_simple(){
    Terme();
    Exp_simple_prime();
}
void Exp_simple_prime() {
    if (strcmp(unitelexicales[ul_courant], "PLUS") == 0 || strcmp(unitelexicales[ul_courant], "MOIN") == 0) {
        avancer();
        Terme();
        Exp_simple_prime();
    }
}
void Terme(){
    Facteur();
    Terme_prime();
}
void Terme_prime() {
    if (strcmp(unitelexicales[ul_courant], "MULT") == 0 || strcmp(unitelexicales[ul_courant], "DIV") == 0) {
        avancer();
        Facteur();
        Terme_prime();
    }
}
void Facteur() {
    if (strcmp(unitelexicales[ul_courant], "IDENTIFICATEUR") == 0 || strcmp(unitelexicales[ul_courant], "NOMBRE") == 0) {
        avancer();
    } else if (strcmp(unitelexicales[ul_courant], "PARENTHESE_OUVRANTE") == 0) {
        avancer();
        Exp_simple();
        accepter("PARENTHESE_FERMENTE");
    } else {
        printf("Erreur de syntaxe: Facteur invalide '%s'\n", unitelexicales[ul_courant]);
    }
}

#endif ANALYSEUR_SYNTAXIQUE_SEMANTIQUE