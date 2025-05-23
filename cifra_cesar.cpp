/*
*
*Autor: Joao Carlos Goncalves de Oliveira Filho
*Matricula: 232009511
*
*/

#include <bits/stdc++.h>

using namespace std;

const map<char,double> DIST = {
    {'a', 13.9}, {'b', 1.04}, {'c', 4.4}, {'d', 5.4}, {'e', 12.57},
    {'f', 1.02}, {'g', 1.2}, {'h', 0.8}, {'i', 1.0}, {'j', 0.4},
    {'k', 0.1}, {'l', 2.8}, {'m', 7.2}, {'n', 5.8}, {'o', 11.08},
    {'p', 2.52}, {'q', 1.2}, {'r', 6.53}, {'s', 12.2}, {'t', 4.34},
    {'u', 4.9}, {'v', 1.8}, {'w', 0.01}, {'x', 0.21}, {'y', 0.01},
    {'z', 0.4}
};

/**
 * @brief calcula a frequencia de cada letra em um texto
 * @param texto texto a ser analisado
 * @return mapa com a frequencia de cada letra em porcentagem
 */
map<char,double> calcularFrequencias(string &texto) {
    map<char, double> freq;
    int total_letras = 0;
    for(char &c : texto) {
        if(isalpha(c)) {
            freq[tolower(c)]++;
            total_letras++;
        }
    }
    for(auto &[letra, count] : freq) {
        freq[letra] = (count / total_letras) * 100;
    }
    return freq;
}

/**
 * @brief encontra a chave mais provavel usando analise de frequencia
 * @param cifrado texto cifrado
 * @return chave mais provavel (deslocamento)
 */
int encontrarChavePorFrequencia(string &cifrado) {
    map<char,double> frequencia_cifrado = calcularFrequencias(cifrado);
    int melhor_chave = 0;
    double menor_erro = INFINITY;
    for(int K = 1; K < 26; K++) {
        double erro_total = 0;
        for(auto &[letra, freq_esperada] : DIST) {
            char letra_cifrada = (letra - 'a' + K) % 26 + 'a';
            erro_total += abs(frequencia_cifrado[letra_cifrada] - freq_esperada);
        }   
        if(erro_total < menor_erro) {
            menor_erro = erro_total;
            melhor_chave = K;
        }
    }
    return melhor_chave;
}

/**
 * @brief decodifica um texto usando cifra de cesar
 * @param mensagem_criptografada texto cifrado
 * @param CHAVE chave de deslocamento
 * @return texto decifrado
 */
string decodificaCifraCesar(string &mensagem_criptografada, int CHAVE) {
    string resultado = mensagem_criptografada;
    for(char &c : resultado) {
        if(isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            c = (c - base - CHAVE + 26) % 26 + base;
        }
    }
    return resultado;
}

/**
 * @brief codifica um texto usando cifra de cesar
 * @param mensagem texto original
 * @param CHAVE chave de deslocamento
 * @return texto cifrado
 */
string codificaCifraCesar(string &mensagem, int CHAVE) {
    string mensagem_criptografada = mensagem;
    for(char &c : mensagem_criptografada) {
        if(isalpha(c)) {
            char base = islower(c) ? 'a' : 'A'; 
            c = (c - base + CHAVE) % 26 + base;
        } 
    }
    return mensagem_criptografada;
}

/**
 * @brief realiza ataque por forca bruta na cifra por deslocamento
 * @param alvo texto cifrado
 * @return vetor com todas as possiveis decifracoes e suas chaves
 */
vector<pair<string,int>> ataqueForcaBruta(string &alvo) {
    vector<pair<string,int>> possibilidades;
    for(int K = 1; K < 26; K++) {
        string mensagem_auxiliar = alvo;    
        for(char &c : mensagem_auxiliar) {
            if(isalpha(c)) {
                char base = islower(c) ? 'a' : 'A';
                c = (c - base - K + 26) % 26 + base;
            }
        }
        possibilidades.push_back({mensagem_auxiliar, K});
    }
    return possibilidades;
}

/**
 * @brief exibe os resultados de um ataque por forca bruta
 * @param possibilidades vetor de possiveis decifracoes
 */
void geraResultadosForcaBruta(vector<pair<string,int>> possibilidades) {
    for(auto &[mensagem, chave] : possibilidades) {
        cout << "resultado : " << mensagem << " \n \n | " << " chave utilizada (k) : " << chave << '\n';
        cout << '\n';
    }
}