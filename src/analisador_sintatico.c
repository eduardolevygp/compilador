#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "analisador_lexico.h"
#include "constantes.h"

typedef struct Transicao {
    int maq_dest;
    int est_dest;
} transicao;

typedef struct Pilha {
        transicao *pilha;
        int pos;
} ape;

void semantico_tbd();

void inicializaTransicoes(transicao (*trans)[25], int numEstados);
void preencheTransSint(transicao *trans, int maq, int est);
void preencheEstadoFinal(transicao (*maq)[25], int estFinal);

void preencheMaine(transicao (*maq)[25]);
void preencheProgr(transicao (*maq)[25]);
void preencheDecl (transicao (*maq)[25]);
void preencheDeclFn (transicao (*maq)[25]);
void preencheTipo (transicao (*maq)[25]);
void preencheComando (transicao (*maq)[25]);
void preencheAtrib (transicao (*maq)[25]);
void preencheExpr (transicao (*maq)[25]);
void preencheSubExp (transicao (*maq)[25]);
void preencheOr (transicao (*maq)[25]);
void preencheComp (transicao (*maq)[25]);
void preencheTermo (transicao (*maq)[25]);
void preencheFator (transicao (*maq)[25]);
void preencheOperador (transicao (*maq)[25]);
void preencheCondicao (transicao (*maq)[25]);
void preencheIter (transicao (*maq)[25]);
void preencheChamada (transicao (*maq)[25]);

int classificaToken(token tok);

void fnSintatico(token lexico[]) {
    //inicialização
    transicao   maq_maine[5][25],
                maq_progr[2][25],
                maq_decl[4][25],
                maq_declFn[9][25],
                maq_tipo[2][25],
                maq_comando[5][25],
                maq_atrib[4][25],
                maq_expr[2][25],
                maq_subExpr[2][25],
                maq_or[2][25],
                maq_comp[2][25],
                maq_termo[2][25],
                maq_fator[4][25],
                maq_oper[6][25],
                maq_cond[10][25],
                maq_iter[7][25],
                maq_chamada[5][25];

    inicializaTransicoes(maq_maine, 5);
    inicializaTransicoes(maq_progr, 2);
    inicializaTransicoes(maq_decl, 4);
    inicializaTransicoes(maq_declFn, 9);
    inicializaTransicoes(maq_tipo, 2);
    inicializaTransicoes(maq_comando, 5);
    inicializaTransicoes(maq_atrib, 4);
    inicializaTransicoes(maq_expr, 2);
    inicializaTransicoes(maq_subExpr, 2);
    inicializaTransicoes(maq_or, 2);
    inicializaTransicoes(maq_comp, 2);
    inicializaTransicoes(maq_termo, 2);
    inicializaTransicoes(maq_fator, 4);
    inicializaTransicoes(maq_oper, 6);
    inicializaTransicoes(maq_cond, 10);
    inicializaTransicoes(maq_iter, 7);
    inicializaTransicoes(maq_chamada, 5);

    preencheMaine(maq_maine);
    preencheProgr(maq_progr);
    preencheDecl(maq_decl);
    preencheDeclFn(maq_declFn);
    preencheTipo(maq_tipo);
    preencheComando(maq_comando);
    preencheAtrib(maq_atrib);
    preencheExpr(maq_expr);
    preencheSubExp(maq_subExpr);
    preencheOr(maq_or);
    preencheComp(maq_comp);
    preencheTermo(maq_termo);
    preencheFator(maq_fator);
    preencheOperador(maq_oper);
    preencheCondicao(maq_cond);
    preencheIter(maq_iter);
    preencheChamada(maq_chamada);

    //execução
    int maq_atual = MAQ_MAINE;
    int est_atual = 0;



    ape pilha;

    pilha.pilha = malloc(256*sizeof(transicao));
    pilha.pos = -1;

    int posToken = 0;
    token proxToken = lexico[posToken];
    int proxTokenClasse;

    transicao transicaoAtual;

    while (strcmp(proxToken.tipo, "vazio") != 0) {
        proxTokenClasse = classificaToken(proxToken);

        switch (maq_atual) {
            case MAQ_MAINE:
                transicaoAtual = maq_maine[est_atual][proxTokenClasse];
                break;
            case MAQ_PROG:
                transicaoAtual = maq_progr[est_atual][proxTokenClasse];
                break;
            case MAQ_DECL:
                transicaoAtual = maq_decl[est_atual][proxTokenClasse];
                break;
           case MAQ_DECLFN:
                transicaoAtual = maq_declFn[est_atual][proxTokenClasse];
                break;
            case MAQ_TIPO:
                transicaoAtual = maq_tipo[est_atual][proxTokenClasse];
                break;
            case MAQ_COMAN:
                transicaoAtual = maq_comando[est_atual][proxTokenClasse];
                break;
            case MAQ_ATRIB:
                transicaoAtual = maq_atrib[est_atual][proxTokenClasse];
                break;
            case MAQ_EXPR:
                transicaoAtual = maq_expr[est_atual][proxTokenClasse];
                break;
            case MAQ_SUBEXPR:
                transicaoAtual = maq_subExpr[est_atual][proxTokenClasse];
                break;
            case MAQ_OR:
                transicaoAtual = maq_or[est_atual][proxTokenClasse];
                break;
            case MAQ_COMP:
                transicaoAtual = maq_comp[est_atual][proxTokenClasse];
                break;
            case MAQ_TERMO:
                transicaoAtual = maq_termo[est_atual][proxTokenClasse];
                break;
            case MAQ_FATOR:
                transicaoAtual = maq_fator[est_atual][proxTokenClasse];
                break;
            case MAQ_OPERADOR:
                transicaoAtual = maq_oper[est_atual][proxTokenClasse];
                break;
            case MAQ_COND:
                transicaoAtual = maq_cond[est_atual][proxTokenClasse];
                break;
            case MAQ_ITER:
                transicaoAtual = maq_iter[est_atual][proxTokenClasse];
                break;
            case MAQ_CHAMADA:
                transicaoAtual = maq_chamada[est_atual][proxTokenClasse];
                break;
        }

        if (transicaoAtual.est_dest == EST_FINAL) {
            //sai da máquina
            if (pilha.pos == -1) {
                printf ("\n\n\nSUCESSO - TEXTO FONTE VALIDO\n\n\n");
                break;
            }
            est_atual = pilha.pilha[pilha.pos].est_dest;
            maq_atual = pilha.pilha[pilha.pos].maq_dest;
            pilha.pos--;
        } else if (transicaoAtual.maq_dest == maq_atual) {
            //fica na mesma máquina
            est_atual = transicaoAtual.est_dest;
            posToken++;
        } else if (transicaoAtual.est_dest == -1) {
            //erro - linguagem inválida
            printf("\n\n\nERRO - TEXTO FONTE INVALIDO\n\n\n");
            break;
        } else {
            //muda de máquina
            pilha.pos++;
            pilha.pilha[pilha.pos].maq_dest = maq_atual;
            pilha.pilha[pilha.pos].est_dest = transicaoAtual.est_dest;
            maq_atual = transicaoAtual.maq_dest;
            est_atual = 0;
        }

        proxToken = lexico[posToken];

        semantico_tbd();
    }
    if (est_atual == 4 && maq_atual == MAQ_MAINE) {
        printf ("\n\n\nSUCESSO - TEXTO FONTE VALIDO\n\n\n");
    }


}

void semantico_tbd () {
    printf("TODO\n");
}

void inicializaTransicoes(transicao (*trans)[25], int numEstados) {
    int i, j;
    for (i = 0; i < numEstados; i++) {
        for (j=0; j < 25; j++) {
            trans[i][j].maq_dest = -1;
            trans[i][j].est_dest = -1;
        }
    }
}

void preencheEstadoFinal(transicao (*maq)[25], int estFinal) {
    int i;
    for (i = 0; i < 25; i++) {
        maq[estFinal][i].maq_dest = EST_FINAL;
        maq[estFinal][i].est_dest = EST_FINAL;
    }
}

void preencheTransSint(transicao *trans, int maq, int est) {
    trans->maq_dest = maq;
    trans->est_dest = est;
}

void preencheMaine(transicao (*maq)[25]) {
    preencheEstadoFinal(maq, 4);

    preencheTransSint(&maq[0][MAINE], MAQ_MAINE, 1);
    preencheTransSint(&maq[1][ABRE_CHAVE], MAQ_MAINE, 2);
    preencheTransSint(&maq[2][TIPO], MAQ_PROG, 3);
    preencheTransSint(&maq[2][ID], MAQ_PROG, 3);
    preencheTransSint(&maq[2][RETURNE], MAQ_PROG, 3);
    preencheTransSint(&maq[2][IFE], MAQ_PROG, 3);
    preencheTransSint(&maq[2][WHILEE], MAQ_PROG, 3);
    preencheTransSint(&maq[3][FECHA_CHAVE], MAQ_MAINE, 4);
}

void preencheProgr(transicao (*maq)[25]) {
    preencheEstadoFinal(maq, 1);

    preencheTransSint(&maq[0][TIPO], MAQ_DECL, 0);
    preencheTransSint(&maq[0][ID], MAQ_COMAN, 1);
    preencheTransSint(&maq[0][WHILEE], MAQ_COMAN, 1);
    preencheTransSint(&maq[0][IFE], MAQ_COMAN, 1);
    preencheTransSint(&maq[0][RETURNE], MAQ_COMAN, 1);

    preencheTransSint(&maq[1][ID], MAQ_COMAN, 1);
    preencheTransSint(&maq[1][WHILEE], MAQ_COMAN, 1);
    preencheTransSint(&maq[1][IFE], MAQ_COMAN, 1);
    preencheTransSint(&maq[1][RETURNE], MAQ_COMAN, 1);
}

void preencheDecl(transicao (*maq)[25]) {
   preencheEstadoFinal(maq, 3);

   preencheTransSint(&maq[0][TIPO], MAQ_TIPO, 1);
   preencheTransSint(&maq[1][ID], MAQ_DECL, 2);
   preencheTransSint(&maq[2][ABRE_PAREN], MAQ_DECLFN, 3);
   preencheTransSint(&maq[2][PONTO_VIRG], MAQ_DECL, 3);

}
void preencheDeclFn (transicao (*maq)[25]) {
    preencheEstadoFinal(maq, 8);

    preencheTransSint(&maq[0][ABRE_PAREN], MAQ_DECLFN, 1);
    preencheTransSint(&maq[1][TIPO], MAQ_DECLFN, 2);
    preencheTransSint(&maq[1][FECHA_PAREN], MAQ_DECLFN, 3);

    preencheTransSint(&maq[2][ID], MAQ_DECLFN, 4);
    preencheTransSint(&maq[3][ABRE_CHAVE], MAQ_DECLFN, 5);
    preencheTransSint(&maq[4][VIRG], MAQ_DECLFN, 6);
    preencheTransSint(&maq[4][FECHA_PAREN], MAQ_DECLFN, 3);

    preencheTransSint(&maq[5][TIPO], MAQ_PROG, 7);
    preencheTransSint(&maq[5][ID], MAQ_PROG, 7);
    preencheTransSint(&maq[5][WHILEE], MAQ_PROG, 7);
    preencheTransSint(&maq[5][IFE], MAQ_PROG, 7);
    preencheTransSint(&maq[5][RETURNE], MAQ_PROG, 7);

    preencheTransSint(&maq[6][TIPO], MAQ_DECLFN, 2);
    preencheTransSint(&maq[7][FECHA_CHAVE], MAQ_DECLFN, 8);
}

void preencheTipo (transicao (*maq)[25]) {
    preencheEstadoFinal(maq, 1);

    preencheTransSint(&maq[0][TIPO], MAQ_TIPO, 1);
}

void preencheComando (transicao (*maq)[25]) {
    preencheEstadoFinal(maq, 2);

    preencheTransSint(&maq[0][ID], MAQ_COMAN, 1);
    preencheTransSint(&maq[0][RETURNE], MAQ_COMAN, 3);
    preencheTransSint(&maq[0][IFE], MAQ_COND, 2);
    preencheTransSint(&maq[0][WHILEE], MAQ_ITER, 2);

    preencheTransSint(&maq[1][ABRE_PAREN], MAQ_CHAMADA, 2);
    preencheTransSint(&maq[1][IGUAL], MAQ_ATRIB, 2);

    preencheTransSint(&maq[3][STRING], MAQ_EXPR, 4);
    preencheTransSint(&maq[3][ID], MAQ_EXPR, 4);
    preencheTransSint(&maq[3][INT], MAQ_EXPR, 4);
    preencheTransSint(&maq[3][FLOAT], MAQ_EXPR, 4);
    preencheTransSint(&maq[3][ABRE_PAREN], MAQ_EXPR, 4);
    preencheTransSint(&maq[3][EXCLA], MAQ_EXPR, 4);
    preencheTransSint(&maq[3][MENOS], MAQ_EXPR, 4);

    preencheTransSint(&maq[4][PONTO_VIRG], MAQ_COMAN, 2);
}

void preencheAtrib (transicao (*maq)[25]) {
    preencheEstadoFinal(maq, 3);

    preencheTransSint(&maq[0][IGUAL], MAQ_ATRIB, 1);

    preencheTransSint(&maq[1][STRING], MAQ_EXPR, 2);
    preencheTransSint(&maq[1][ID], MAQ_EXPR, 2);
    preencheTransSint(&maq[1][INT], MAQ_EXPR, 2);
    preencheTransSint(&maq[1][FLOAT], MAQ_EXPR, 2);
    preencheTransSint(&maq[1][ABRE_PAREN], MAQ_EXPR, 2);
    preencheTransSint(&maq[1][EXCLA], MAQ_EXPR, 2);
    preencheTransSint(&maq[1][MENOS], MAQ_EXPR, 2);

    preencheTransSint(&maq[2][PONTO_VIRG], MAQ_ATRIB, 3);
}

void preencheExpr (transicao (*maq)[25]) {
    preencheEstadoFinal(maq, 1);

    preencheTransSint(&maq[0][STRING], MAQ_EXPR ,1);

    preencheTransSint(&maq[0][ID], MAQ_SUBEXPR, 1);
    preencheTransSint(&maq[0][INT], MAQ_SUBEXPR, 1);
    preencheTransSint(&maq[0][FLOAT], MAQ_SUBEXPR, 1);
    preencheTransSint(&maq[0][ABRE_PAREN], MAQ_SUBEXPR, 1);
    preencheTransSint(&maq[0][EXCLA], MAQ_SUBEXPR, 1);
    preencheTransSint(&maq[0][MENOS], MAQ_SUBEXPR, 1);
}

void preencheSubExp (transicao (*maq)[25]) {
    preencheEstadoFinal(maq, 1);

    preencheTransSint(&maq[0][ID], MAQ_OR, 1);
    preencheTransSint(&maq[0][INT], MAQ_OR, 1);
    preencheTransSint(&maq[0][FLOAT], MAQ_OR, 1);
    preencheTransSint(&maq[0][ABRE_PAREN], MAQ_OR, 1);
    preencheTransSint(&maq[0][EXCLA], MAQ_OR, 1);
    preencheTransSint(&maq[0][MENOS], MAQ_OR, 1);

    preencheTransSint(&maq[1][OR], MAQ_SUBEXPR, 0);
}

void preencheOr (transicao (*maq)[25]) {
    preencheEstadoFinal(maq, 1);

    preencheTransSint(&maq[0][ID], MAQ_COMP, 1);
    preencheTransSint(&maq[0][INT], MAQ_COMP, 1);
    preencheTransSint(&maq[0][FLOAT], MAQ_COMP, 1);
    preencheTransSint(&maq[0][ABRE_PAREN], MAQ_COMP, 1);
    preencheTransSint(&maq[0][EXCLA], MAQ_COMP, 1);
    preencheTransSint(&maq[0][MENOS], MAQ_COMP, 1);

    preencheTransSint(&maq[1][AND], MAQ_OR, 0);
}

void preencheComp (transicao (*maq)[25]) {
    preencheEstadoFinal(maq, 1);

    preencheTransSint(&maq[0][ID], MAQ_TERMO, 1);
    preencheTransSint(&maq[0][INT], MAQ_TERMO, 1);
    preencheTransSint(&maq[0][FLOAT], MAQ_TERMO, 1);
    preencheTransSint(&maq[0][ABRE_PAREN], MAQ_TERMO, 1);
    preencheTransSint(&maq[0][EXCLA], MAQ_TERMO, 1);
    preencheTransSint(&maq[0][MENOS], MAQ_TERMO, 1);

    preencheTransSint(&maq[1][MAIS], MAQ_COMP, 0);
    preencheTransSint(&maq[1][MENOS], MAQ_COMP, 0);
}

void preencheTermo(transicao (*maq)[25]) {
    preencheEstadoFinal(maq, 1);

    preencheTransSint(&maq[0][ID], MAQ_FATOR, 1);
    preencheTransSint(&maq[0][INT], MAQ_FATOR, 1);
    preencheTransSint(&maq[0][FLOAT], MAQ_FATOR, 1);
    preencheTransSint(&maq[0][ABRE_PAREN], MAQ_FATOR, 1);
    preencheTransSint(&maq[0][EXCLA], MAQ_FATOR, 1);
    preencheTransSint(&maq[0][MENOS], MAQ_FATOR, 1);

    preencheTransSint(&maq[1][VEZES], MAQ_TERMO, 0);
    preencheTransSint(&maq[1][BARRA], MAQ_TERMO, 0);
}

void preencheFator (transicao (*maq)[25]) {
    preencheEstadoFinal(maq, 1);
    preencheEstadoFinal(maq, 3);

    preencheTransSint(&maq[0][ID], MAQ_OPERADOR, 1);
    preencheTransSint(&maq[0][INT], MAQ_OPERADOR, 1);
    preencheTransSint(&maq[0][FLOAT], MAQ_OPERADOR, 1);
    preencheTransSint(&maq[0][ABRE_PAREN], MAQ_OPERADOR, 1);
    preencheTransSint(&maq[0][EXCLA], MAQ_OPERADOR, 1);
    preencheTransSint(&maq[0][MENOS], MAQ_OPERADOR, 1);

    preencheTransSint(&maq[1][COMPARA], MAQ_FATOR, 2);

    preencheTransSint(&maq[2][ID], MAQ_OPERADOR, 3);
    preencheTransSint(&maq[2][INT], MAQ_OPERADOR, 3);
    preencheTransSint(&maq[2][FLOAT], MAQ_OPERADOR, 3);
    preencheTransSint(&maq[2][ABRE_PAREN], MAQ_OPERADOR, 3);
    preencheTransSint(&maq[2][EXCLA], MAQ_OPERADOR, 3);
    preencheTransSint(&maq[2][MENOS], MAQ_OPERADOR, 3);

}

void preencheOperador (transicao (*maq)[25]) {
    preencheEstadoFinal(maq, 2);
    preencheEstadoFinal(maq, 3);

    preencheTransSint(&maq[0][ID], MAQ_OPERADOR, 2);
    preencheTransSint(&maq[0][INT], MAQ_OPERADOR, 3);
    preencheTransSint(&maq[0][FLOAT], MAQ_OPERADOR, 3);
    preencheTransSint(&maq[0][ABRE_PAREN], MAQ_OPERADOR, 4);
    preencheTransSint(&maq[0][EXCLA], MAQ_OPERADOR, 1);
    preencheTransSint(&maq[0][MENOS], MAQ_OPERADOR, 1);

    preencheTransSint(&maq[1][ABRE_PAREN], MAQ_OPERADOR, 4);
    preencheTransSint(&maq[1][FLOAT], MAQ_OPERADOR, 3);
    preencheTransSint(&maq[1][INT], MAQ_OPERADOR, 3);
    preencheTransSint(&maq[1][ID], MAQ_OPERADOR, 2);

    preencheTransSint(&maq[4][ID], MAQ_SUBEXPR, 5);
    preencheTransSint(&maq[4][INT], MAQ_SUBEXPR, 5);
    preencheTransSint(&maq[4][FLOAT], MAQ_SUBEXPR, 5);
    preencheTransSint(&maq[4][ABRE_PAREN], MAQ_SUBEXPR, 5);
    preencheTransSint(&maq[4][EXCLA], MAQ_SUBEXPR, 5);
    preencheTransSint(&maq[4][MENOS], MAQ_SUBEXPR, 5);

    preencheTransSint(&maq[5][FECHA_PAREN], MAQ_OPERADOR, 3);
}

void preencheCondicao (transicao (*maq)[25]) {
    preencheEstadoFinal(maq, 6);
    preencheEstadoFinal(maq, 9);

    preencheTransSint(&maq[0][IFE], MAQ_COND, 1);
    preencheTransSint(&maq[1][ABRE_PAREN], MAQ_COND, 2);

    preencheTransSint(&maq[2][ID], MAQ_SUBEXPR, 3);
    preencheTransSint(&maq[2][INT], MAQ_SUBEXPR, 3);
    preencheTransSint(&maq[2][FLOAT], MAQ_SUBEXPR, 3);
    preencheTransSint(&maq[2][ABRE_PAREN], MAQ_SUBEXPR, 3);
    preencheTransSint(&maq[2][EXCLA], MAQ_SUBEXPR, 3);
    preencheTransSint(&maq[2][MENOS], MAQ_SUBEXPR, 3);

    preencheTransSint(&maq[3][FECHA_PAREN], MAQ_COND, 4);

    preencheTransSint(&maq[4][ABRE_CHAVE], MAQ_COND, 5);

    preencheTransSint(&maq[5][FECHA_CHAVE], MAQ_COND, 6);

    preencheTransSint(&maq[5][ID], MAQ_COMAN, 5);
    preencheTransSint(&maq[5][RETURNE], MAQ_COMAN, 5);
    preencheTransSint(&maq[5][IFE], MAQ_COMAN, 5);
    preencheTransSint(&maq[5][WHILEE], MAQ_COMAN, 5);

    preencheTransSint(&maq[6][ELSEE], MAQ_COND, 7);

    preencheTransSint(&maq[7][ABRE_CHAVE], MAQ_COND, 8);

    preencheTransSint(&maq[8][FECHA_CHAVE], MAQ_COND, 9);

    preencheTransSint(&maq[8][ID], MAQ_COMAN, 8);
    preencheTransSint(&maq[8][RETURNE], MAQ_COMAN, 8);
    preencheTransSint(&maq[8][IFE], MAQ_COMAN, 8);
    preencheTransSint(&maq[8][WHILEE], MAQ_COMAN, 8);
}

void preencheIter (transicao (*maq)[25]) {
    preencheEstadoFinal(maq, 6);

    preencheTransSint(&maq[0][WHILEE], MAQ_ITER, 1);
    preencheTransSint(&maq[1][ABRE_PAREN], MAQ_ITER, 2);

    preencheTransSint(&maq[2][ID], MAQ_SUBEXPR, 3);
    preencheTransSint(&maq[2][INT], MAQ_SUBEXPR, 3);
    preencheTransSint(&maq[2][FLOAT], MAQ_SUBEXPR, 3);
    preencheTransSint(&maq[2][ABRE_PAREN], MAQ_SUBEXPR, 3);
    preencheTransSint(&maq[2][EXCLA], MAQ_SUBEXPR, 3);
    preencheTransSint(&maq[2][MENOS], MAQ_SUBEXPR, 3);

    preencheTransSint(&maq[3][FECHA_PAREN], MAQ_ITER, 4);
    preencheTransSint(&maq[4][ABRE_CHAVE], MAQ_ITER, 5);

    preencheTransSint(&maq[5][FECHA_CHAVE], MAQ_ITER, 6);
    preencheTransSint(&maq[5][ID], MAQ_COMAN, 5);
    preencheTransSint(&maq[5][RETURNE], MAQ_COMAN, 5);
    preencheTransSint(&maq[5][IFE], MAQ_COMAN, 5);
    preencheTransSint(&maq[5][WHILEE], MAQ_COMAN, 5);


}

void preencheChamada (transicao (*maq)[25]) {
    preencheEstadoFinal(maq, 3);

    preencheTransSint(&maq[0][ABRE_PAREN], MAQ_CHAMADA, 1);

    preencheTransSint(&maq[1][FECHA_PAREN], MAQ_CHAMADA, 3);

    preencheTransSint(&maq[1][STRING], MAQ_EXPR, 2);
    preencheTransSint(&maq[1][ID], MAQ_EXPR, 2);
    preencheTransSint(&maq[1][INT], MAQ_EXPR, 2);
    preencheTransSint(&maq[1][FLOAT], MAQ_EXPR, 2);
    preencheTransSint(&maq[1][ABRE_PAREN], MAQ_EXPR, 2);
    preencheTransSint(&maq[1][EXCLA], MAQ_EXPR, 2);
    preencheTransSint(&maq[1][MENOS], MAQ_EXPR, 2);

    preencheTransSint(&maq[2][FECHA_PAREN], MAQ_CHAMADA, 3);
    preencheTransSint(&maq[2][VIRG], MAQ_CHAMADA, 4);

    preencheTransSint(&maq[4][STRING], MAQ_EXPR, 2);
    preencheTransSint(&maq[4][ID], MAQ_EXPR, 2);
    preencheTransSint(&maq[4][INT], MAQ_EXPR, 2);
    preencheTransSint(&maq[4][FLOAT], MAQ_EXPR, 2);
    preencheTransSint(&maq[4][ABRE_PAREN], MAQ_EXPR, 2);
    preencheTransSint(&maq[4][EXCLA], MAQ_EXPR, 2);
    preencheTransSint(&maq[4][MENOS], MAQ_EXPR, 2);
}

int classificaToken(token tok) {
    if (strcmp(tok.tipo, "palavra_reservada") == 0) {
        if (strcmp(tok.valor, "maine") == 0) return MAINE;
        if (strcmp(tok.valor, "ife") == 0) return IFE;
        if (strcmp(tok.valor, "whilee") == 0) return WHILEE;
        if (strcmp(tok.valor, "inte") == 0) return TIPO;
        if (strcmp(tok.valor, "floate") == 0) return TIPO;
        if (strcmp(tok.valor, "stringe") == 0) return TIPO;
        if (strcmp(tok.valor, "elsee") == 0) return ELSEE;
        if (strcmp(tok.valor, "returne") == 0) return RETURNE;
    }
    if (strcmp(tok.tipo, "identificador") == 0) return ID;
    if (strcmp(tok.tipo, "inteiro") == 0) return INT;
    if (strcmp(tok.tipo, "float") == 0) return FLOAT;
    if (strcmp(tok.tipo, "simbolo") == 0) {
        if (strcmp(tok.valor, "(") == 0) return ABRE_PAREN;
        if (strcmp(tok.valor, ")") == 0) return FECHA_PAREN;
        if (strcmp(tok.valor, "{") == 0) return ABRE_CHAVE;
        if (strcmp(tok.valor, "}") == 0) return FECHA_CHAVE;
        if (strcmp(tok.valor, ";") == 0) return PONTO_VIRG;
        if (strcmp(tok.valor, ",") == 0) return VIRG;
    }
    if (strcmp(tok.tipo, "operador") == 0) {
        if (strcmp(tok.valor, "+") == 0) return MAIS;
        if (strcmp(tok.valor, "-") == 0) return MENOS;
        if (strcmp(tok.valor, "*") == 0) return VEZES;
        if (strcmp(tok.valor, "/") == 0) return BARRA;
        if (strcmp(tok.valor, "=") == 0) return IGUAL;
        if (strcmp(tok.valor, "||") == 0) return OR;
        if (strcmp(tok.valor, "&&") == 0) return AND;
        if (strcmp(tok.valor, "!") == 0) return EXCLA;
        if (strcmp(tok.valor, "!=") == 0) return COMPARA;
        if (strcmp(tok.valor, "==") == 0) return COMPARA;
        if (strcmp(tok.valor, ">") == 0) return COMPARA;
        if (strcmp(tok.valor, ">=") == 0) return COMPARA;
        if (strcmp(tok.valor, "<") == 0) return COMPARA;
        if (strcmp(tok.valor, "<=") == 0) return COMPARA;
    }
    if (strcmp(tok.tipo, "string") == 0) return STRING;

    return -1;
}
