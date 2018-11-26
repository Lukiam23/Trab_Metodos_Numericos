#include <iostream>
#include <clocale>
#include <stdexcept>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include "NumericalMethods/pivoting-LU.h"
#include "Terminal Bootstrap/terminal.h"

using namespace std;

void fillMatrixRow(float **M, string entries[], int m, int i) {
    for (int j = 0; j < m; j++) {
        M[i][j] = (float)strtof((entries[j]).c_str(), 0);
    }
}   

int main(void) {
    Terminal::clear();
    Terminal::setBoxWidth(90);
    std::setlocale(LC_ALL, "en_US.utf8");

    cout << Terminal::insertHeader("ROCKET EXPLOSION DETECTION") << endl;
    cout << Terminal::insertSectionStart() << endl;
    cout << Terminal::insertBlankSpace() << endl;
    cout << Terminal::insertParagraph("Esse sistema calcula o deslocamento 'd' da extremidade de um foguete espacial através da equação f(d) = ad – dln(d), onde 'd' é o deslocamento medido em 'cm' e 'a' é um parâmetro de ajuste. Com isso, é inferido se o foguete irá explodir ou não.") << endl;
    cout << Terminal::insertBlankSpace() << endl;
    cout << Terminal::insertBottomLine() << endl;

    cout << Terminal::insertTitle("INSIRA OS DADOS DA MATRIZ A") << endl;

    int n;
    Terminal::insertInput("Insira a dimensão da matriz: ", n, "Valor incorreto.");;

    float **A;
    A = new float *[n];
    for (int i = 0; i < n; i++) {
        A[i] = new float[n];
    }

    cout << Terminal::insertSubtitle("Preencha cada linha da matriz, usando ';' para separar os valores") << endl;

    cin.ignore();

    for (int i = 0; i < n; i++) {
        int alright = 1;
        string label = "Linha " + to_string(i + 1) + ": ";
        string entries;
        string entriesList[n];

        while (alright) {
            try {
                Terminal::insertInput(label, entries);
                entries.erase(std::remove(entries.begin(), entries.end(), ' '), entries.end());
                strutil::split(entries, ';', entriesList, n);
                alright = 0;
            } catch (const std::domain_error& e) {
                cout << Terminal::insertParagraph("A quantidade de valores fornecida não corresponde ao informado inicialmente", "") << endl;
                alright = 1;
            }
        }

        fillMatrixRow(A, entriesList, n, i);
    }

    cout << Terminal::insertHR() << endl;

    cout << Terminal::insertTitle("INSIRA OS DADOS DO VETOR F") << endl;

    float **B;
    B = new float *[n];
    for (int i = 0; i < n; i++) {
        B[i] = new float[1];
    }

    for (int i = 0; i < n; i++) {
        int alright = 1;
        string label = "Linha " + to_string(i + 1) + ": ";
        float entry;
        Terminal::insertInput(label, entry, "Valor incorreto.");
        B[i][0] = entry;
    }

    cout << Terminal::insertSubtitle("Matriz A") << endl;
    cout << Terminal::insertCenteredMatrix(A, n, n) << endl;

    cout << Terminal::insertSubtitle("Vetor f") << endl;
    cout << Terminal::insertCenteredMatrix(B, n, 1) << endl;

    Terminal::insertInput("Pressione <Enter> para continuar...");
    Terminal::clear();

    cout << Terminal::insertTitle("CÁLCULO COM O MÉTODO LU COM PIVOTAMENTO PARCIAL") << endl;

    int p[n];
    float x[n];
    float b[n];

    for (int i = 0; i < n; i++) {
        b[i] = B[i][0];
    }

    float **A_m;
    A_m = new float *[n];
    for (int i = 0; i < n; i++) {
        A_m[i] = new float[n];
        for (int j = 0; j < n; j++) {
            A_m[i][j] = A[i][j];
        }
    }

    PivotingLU calc(A, p, b, n);
    calc.calculate(x);

    cout << Terminal::insertCenteredMatrix(A, n, n) << endl;

    cout << Terminal::insertSubtitle("Vetor 'd'") << endl;
    
    float **d;
    d = new float *[n];
    for (int i = 0; i < n; i++) {
        d[i] = new float[1];
        d[i][0] = x[i];
    }

    cout << Terminal::insertCenteredMatrix(d, n, 1) << endl;

    cout << Terminal::insertSubtitle("Vetor 'p' de permutações") << endl;

    float **P;
    P = new float *[n];
    for (int i = 0; i < n; i++) {
        P[i] = new float[1];
        P[i][0] = p[i];
    }

    cout << Terminal::insertCenteredMatrix(P, n, 1) << endl;
    
    bool willExplode = false;
    for (int i = 0; i < n; i++) {
        if (abs(d[i][0]) > 2) {
            willExplode = true;
        }
    }

    string conclusion = willExplode ? "" : "NÃO ";
    cout << Terminal::insertSubtitle("CONCLUSÃO: O FOGUETE " + conclusion + "IRÁ EXPLODIR") << endl;

    Terminal::insertInput("Pressione <Enter> para continuar...");
    Terminal::clear();

    cout << Terminal::insertTitle("CÁLCULO COM O MÉTODO LU MODIFICADO") << endl;

    int p_m[n];
    float x_m[n];
    float b_m[n];

    for (int i = 0; i < n; i++) {
        b_m[i] = B[i][0];
    }

    PivotingLU calc_m(A_m, p_m, b_m, n);
    calc_m.calculate(x_m);

    cout << Terminal::insertCenteredMatrix(A_m, n, n) << endl;

    cout << Terminal::insertSubtitle("Vetor 'd'") << endl;
    
    float **d_m;
    d_m = new float *[n];
    for (int i = 0; i < n; i++) {
        d_m[i] = new float[1];
        d_m[i][0] = x_m[i];
    }

    cout << Terminal::insertCenteredMatrix(d_m, n, 1) << endl;

    cout << Terminal::insertSubtitle("Vetor 'p' de permutações") << endl;

    float **P_m;
    P_m = new float *[n];
    for (int i = 0; i < n; i++) {
        P_m[i] = new float[1];
        P_m[i][0] = p_m[i];
    }

    cout << Terminal::insertCenteredMatrix(P_m, n, 1) << endl;

    bool willExplode_m = false;
    for (int i = 0; i < n; i++) {
        if (abs(d_m[i][0]) > 2) {
            willExplode_m = true;
        }
    }

    string conclusion_m = willExplode_m ? "" : "NÃO ";
    cout << Terminal::insertSubtitle("CONCLUSÃO: O FOGUETE " + conclusion_m + "IRÁ EXPLODIR") << endl;

    Terminal::insertInput("Pressione <Enter> para continuar...");
    Terminal::clear();

    cout << Terminal::insertTitle("CALIBRANDO O SISTEMA COM OS DADOS ABAIXO") << endl;

    float _Adefault[3][3] = {
        3, -2, 1,
        1, -3, 4,
        9, 4, -5
    };

    float **Adefault;
    Adefault = new float *[3];
    for (int i = 0; i < 3; i++) {
        Adefault[i] = new float[3];
        for (int j = 0; j < 3; j++) {
            Adefault[i][j] = _Adefault[i][j];
        }
    }

    float _Bdefault[3] = {
        8,
        6,
        11
    };

    float **Bdefault;
    Bdefault = new float *[3];
    for (int i = 0; i < 3; i++) {
        Bdefault[i] = new float[1];
        Bdefault[i][0] = _Bdefault[i];
    }

    cout << Terminal::insertCenteredMatrix(Adefault, 3, 3) << endl;
    cout << Terminal::insertCenteredMatrix(Bdefault, 3, 1) << endl;

    int p_d[3];
    float x_d[3];

    PivotingLU calc2(Adefault, p_d, _Bdefault, 3);
    calc2.calculate(x_d);

    cout << Terminal::insertSubtitle("Matriz LU") << endl;

    cout << Terminal::insertCenteredMatrix(Adefault, 3, 3) << endl;

    cout << Terminal::insertSubtitle("Vetor 'd'") << endl;

    float **B_d;
    B_d = new float *[3];
    for (int i = 0; i < 3; i++) {
        B_d[i] = new float[1];
        B_d[i][0] = x_d[i];
    }

    cout << Terminal::insertCenteredMatrix(B_d, 3, 1) << endl;

    cout << Terminal::insertSubtitle("Vetor 'p' de permutações") << endl;

    float **P_d;
    P_d = new float *[3];
    for (int i = 0; i < 3; i++) {
        P_d[i] = new float[1];
        P_d[i][0] = p_d[i];
    }

    cout << Terminal::insertCenteredMatrix(P_d, 3, 1) << endl;
    
    cout << Terminal::insertSubtitle("CONCLUSÃO: O FOGUETE IRÁ EXPLODIR") << endl;

    Terminal::insertInput("Pressione <Enter> para continuar...");
    Terminal::clear();

    return 0;
}