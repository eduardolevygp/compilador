#include <stdio.h>
#include <string.h>

#define ASCII_LF 10
#define ASCII_SP 32

int _tabelaTransicoes[12][128];

void preencheTransicao();
int eDigito(int ch);
int eAlpha(int ch);
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
    	strcpy(tipo, "pontuacao");
    	break;
    case 2:
    	strcpy(tipo, "operador");
    	break;
    case 3:
    	strcpy(tipo, "operador_composto");
    	break;
    case 4:
        if (verificarReservado(caracteresLidos)) {
            strcpy(tipo, "palavra_reservada");
        } else {
            strcpy(tipo, "identificador");
        }
    	break;
    case 5:
    	strcpy(tipo, "inteiro");
    	break;
    case 7:
    	strcpy(tipo, "ponto_flutuante");
    	break;
    case 8:
    	strcpy(tipo, "operador");
    	break;
  }
  fprintf(lexico, "[%s, %s]\n", tipo,  caracteresLidos);
}

int verificarReservado (char* identificador) {
    int reservado = strcmp(identificador, "return") == 0 ||
                    strcmp(identificador, "if") == 0 ||
                    strcmp(identificador, "while") == 0 ||
                    strcmp(identificador, "for") == 0 ||
                    strcmp(identificador, "int") == 0 ||
                    strcmp(identificador, "float") == 0 ||
                    strcmp(identificador, "else") == 0 ||
                    strcmp(identificador, "char") == 0;
    return reservado;
}

void preencheTransicao () {
  int coluna;
  int linha;
  //preenchendo tudo com -1
  for (linha = 0; linha < 12; linha++) {
    for (coluna = 0; coluna < 128; coluna++) {
    	_tabelaTransicoes[linha][coluna] = -1;
    }
  }

  //estado 0
  for (coluna = 0; coluna < 128; coluna++) {
    _tabelaTransicoes[0][coluna] = 0;
  }

    _tabelaTransicoes[0][(int) ';'] = 1;
    _tabelaTransicoes[0][(int) '['] = 1;
    _tabelaTransicoes[0][(int) ']'] = 1;
    _tabelaTransicoes[0][(int) '('] = 1;
    _tabelaTransicoes[0][(int) ')'] = 1;
    _tabelaTransicoes[0][(int) '{'] = 1;
    _tabelaTransicoes[0][(int) '}'] = 1;
    _tabelaTransicoes[0][(int) ','] = 1;

  for (coluna = (int) 'a'; coluna <= (int) 'z'; coluna++) {
  	_tabelaTransicoes[0][coluna] = 4;
  }
  for (coluna = (int) 'A'; coluna <= (int) 'Z'; coluna++) {
  	_tabelaTransicoes[0][coluna] = 4;
  }

  for (coluna = (int) '0'; coluna <= (int) '9'; coluna++) {
  	_tabelaTransicoes[0][coluna] = 5;
  }

  _tabelaTransicoes[0][(int) '+'] = 2;
  _tabelaTransicoes[0][(int) '-'] = 2;
  _tabelaTransicoes[0][(int) '*'] = 2;
  _tabelaTransicoes[0][(int) '='] = 2;
  _tabelaTransicoes[0][(int) '!'] = 2;
  _tabelaTransicoes[0][(int) '<'] = 2;
  _tabelaTransicoes[0][(int) '>'] = 2;

  _tabelaTransicoes[0][(int) '/'] = 8;


  //estado 1
  //tudo -1

  //estado 2
  _tabelaTransicoes[2][(int) '='] = 3;

  //estado 3
  //tudo -1

  //estado 4
  for (coluna = 0; coluna < 128; coluna++) {
    if (eDigito(coluna) || eAlpha(coluna)) {
      //se for digito ou alpha
    	_tabelaTransicoes[4][coluna] = 4;
    }
  }

  //estado 5
  for (coluna = 0; coluna < 128; coluna++) {
    if (eDigito(coluna)) {
    	_tabelaTransicoes[5][coluna] = 5;
    } else if (coluna == (int) '.') {
      _tabelaTransicoes[5][coluna] = 6;
    }
  }

  //estado 6
  for (coluna = (int) '0'; coluna <= (int) '9'; coluna++) {
    _tabelaTransicoes[6][coluna] = 7;
  }

  //estado 7
  for (coluna = (int) '0'; coluna <= (int) '9'; coluna++) {
    _tabelaTransicoes[7][coluna] = 7;
  }

  //estado 8
  _tabelaTransicoes[8][(int) '/'] = 9;
  _tabelaTransicoes[8][(int) '='] = 3;
  _tabelaTransicoes[8][(int) '*'] = 10;

  //estado 9
  for (coluna = 0; coluna < 128; coluna++) {
    _tabelaTransicoes[9][coluna] = 9;
  }
  _tabelaTransicoes[9][ASCII_LF] = 0;

  //estado 10
  for (coluna = 0; coluna < 128; coluna++) {
    _tabelaTransicoes[10][coluna] = 10;
  }
  _tabelaTransicoes[10][(int) '*'] = 11;

  //estado 11
  for (coluna = 0; coluna < 128; coluna++) {
    _tabelaTransicoes[11][coluna] = 10;
  }
  _tabelaTransicoes[11][(int) '/'] = 0;
}

int eDigito (int ch) {
  return ch >= (int) '0' && ch <= (int) '9';
}

int eAlpha (int ch) {
  return (ch >= (int) 'a' && ch <= (int) 'z') || (ch >= (int) 'A' && ch <= (int) 'Z');
}

int ProximoEstado (int estadoAnterior, char caractere){
    if (caractere == EOF) {
        return -1;
    }
    return _tabelaTransicoes[estadoAnterior][(int) caractere];
}
