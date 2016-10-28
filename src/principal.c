#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "analisador_lexico.h"
#include "analisador_sintatico.h"
#include "constantes.h"

int main() {

    token lexico[1024];
    //int i = 0;


    fnLexico(lexico);

    fnSintatico(lexico);
//    while (strcmp(lexico[i].tipo, "vazio") != 0 && i < 1024) {
//        printf("[%s, %s]\n", lexico[i].tipo, lexico[i].valor);
//        i++;
//    }

    return 0;
}
