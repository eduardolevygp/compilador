#include <stdio.h>
#include <string.h>

#define ASCII_LF 10
#define ASCII_SP 32

int _tabelaTransicoes[11][128];

void preencheTransicao();
int eDigito(int ch);
int eAlpha(int ch);
int eSimbolo(int ch);
int ProximoEstado (int estadoAnterior, char ch);
void EscreveToken (int estado, char* caracteresLidos);
int verificarReservado (char* identificador);

FILE *lexico;

int main () {
    lexico = fopen("lexico.txt", "w");
    preencheTransicao(_tabelaTransicoes);
    char caracteresLidos[255];
    char proximoCaractere = 'x';
    int estadoAtual = 0;
    FILE *fonte;
    fonte = fopen("entrada.txt", "r");
    int posicao = 0;

    int consome = 1;

    do{
        int proximoEstado;

        if (consome) {
            proximoCaractere = (char) fgetc(fonte);
        }
        proximoEstado = ProximoEstado(estadoAtual, proximoCaractere);

        if (proximoEstado == -1){
            consome = 0;
            if (strlen(caracteresLidos) > 0) {
                EscreveToken(estadoAtual, caracteresLidos);
            }
            proximoEstado = 0;
            posicao = -1;
        } else if (proximoEstado == 0) {
            posicao = -1;
            consome = 1;
        } else {
            consome = 1;
        }

        if (posicao > -1) {
            caracteresLidos[posicao] = proximoCaractere;
        }
        estadoAtual = proximoEstado;
        posicao++;
        caracteresLidos[posicao] = '\0';
    } while (proximoCaractere != EOF);

    fclose(fonte);
    fclose(lexico);

    return 0;
}

void EscreveToken (int estado, char* caracteresLidos){


  char tipo[255];
  switch (estado) {
    case 1:
    	if (verificarReservado(caracteresLidos)) {
            strcpy(tipo, "palavra_reservada");
        } else {
            strcpy(tipo, "identificador");
        }
    	break;
    case 2:
    	strcpy(tipo, "inteiro");
    	break;
    case 4:
    	strcpy(tipo, "float");
    	break;
    case 5:
    	strcpy(tipo, "simbolo");
    	break;
    case 6:
    case 7:
    case 8:
    	strcpy(tipo, "operador");
    	break;
    case 10:
    	strcpy(tipo, "string");
    	break;
  }
  fprintf(lexico, "[%s, %s]\n", tipo,  caracteresLidos);
}

int verificarReservado (char* identificador) {
    int reservado = strcmp(identificador, "maine") == 0 ||
                    strcmp(identificador, "ife") == 0 ||
                    strcmp(identificador, "whilee") == 0 ||
                    strcmp(identificador, "inte") == 0 ||
                    strcmp(identificador, "floate") == 0 ||
                    strcmp(identificador, "elsee") == 0 ||
                    strcmp(identificador, "returne") == 0 ||
                    strcmp(identificador, "stringe") == 0;
    return reservado;
}

void preencheTransicao () {
  int coluna;
  int linha;
  //preenchendo tudo com -1
  for (linha = 0; linha < 11; linha++) {
    for (coluna = 0; coluna < 128; coluna++) {
    	_tabelaTransicoes[linha][coluna] = -1;
    }
  }

  //estado 0
  for (coluna = 0; coluna < 128; coluna++) {
    if (eAlpha(coluna)) {
        _tabelaTransicoes[0][coluna] = 1;
    } else if (eDigito(coluna)) {
        _tabelaTransicoes[0][coluna] = 2;
    } else if (eSimbolo(coluna)) {
        _tabelaTransicoes[0][coluna] = 5;
    } else if (coluna == (int) '>' || coluna == (int) '<' || coluna == (int) '!' || coluna == (int) '=') {
        _tabelaTransicoes[0][coluna] = 6;
    } else if (coluna == (int) '*' || coluna == (int) '+' || coluna == (int) '/' || coluna == (int) '-') {
        _tabelaTransicoes[0][coluna] = 8;
    } else if (coluna == (int) '"') {
        _tabelaTransicoes[0][coluna] = 9;
    } else {
        _tabelaTransicoes[0][coluna] = 0;
    }
  }

  //estado 1
  for (coluna = 0; coluna < 128; coluna++) {
    if (eAlpha(coluna) || eDigito(coluna)) {
        _tabelaTransicoes[1][coluna] = 1;
    }
  }

  //estado 2
  for (coluna = 0; coluna < 128; coluna++) {
    if (eDigito(coluna)) {
        _tabelaTransicoes[2][coluna] = 2;
    } else if (coluna == (int) '.') {
        _tabelaTransicoes[2][coluna] = 3;
    }
  }

  //estado 3
  for (coluna = 0; coluna < 128; coluna++) {
    if (eDigito(coluna)) {
        _tabelaTransicoes[3][coluna] = 4;
    }
  }

  //estado 4
  for (coluna = 0; coluna < 128; coluna++) {
    if (eDigito(coluna)) {
    	_tabelaTransicoes[4][coluna] = 4;
    }
  }

  //estado 5
  //tudo -1

  //estado 6
  _tabelaTransicoes[6][(int) '='] = 7;

  //estado 7
  //tudo -1

  //estado 8
 //tudo -1

  //estado 9
  for (coluna = 0; coluna < 128; coluna++) {
    _tabelaTransicoes[9][coluna] = 9;
  }
  _tabelaTransicoes[9][(int) '"'] = 10;

  //estado 10
  //tudo -1
}

int eDigito (int ch) {
  return ch >= (int) '0' && ch <= (int) '9';
}

int eAlpha (int ch) {
  return (ch >= (int) 'a' && ch <= (int) 'z') || (ch >= (int) 'A' && ch <= (int) 'Z');
}

int eSimbolo (int ch) {
    return ch == (int) ';' || ch == (int) '[' || ch == (int) ']'
                || ch == (int) '(' || ch == (int) ')' || ch == (int) '{' || ch == (int) '}' || ch == (int) ',';
}

int ProximoEstado (int estadoAnterior, char caractere){
    if (caractere == EOF) {
        return -1;
    }
    return _tabelaTransicoes[estadoAnterior][(int) caractere];
}
