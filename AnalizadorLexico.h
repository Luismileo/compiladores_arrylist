#ifndef ANALIZADOR_LEXICO_H
#define ANALIZADOR_LEXICO_H

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>

#include "Token.h"
#include "arraylist.h"

class AnalizadorLexico {
private:
    std::vector<std::string> palabrasReservadas;
    std::vector<std::string> tiposDatos;
    std::vector<std::string> operadores;

    std::vector<std::string> arregloVariables;
    list<Token> listaTokens;

    static std::string toLowerCopy(std::string s) {
        std::transform(s.begin(), s.end(), s.begin(),
                       [](unsigned char ch) { return (char)std::tolower(ch); });
        return s;
    }

    bool existeEnLista(const std::vector<std::string>& lista, const std::string& valor) {
        return std::find(lista.begin(), lista.end(), valor) != lista.end();
    }

    void agregarToken(TipoToken tipo, int fila, int col, const std::string& valor) {
        Token t{tipo, fila, col, valor};
        listaTokens.add(t);
    }

public:
    AnalizadorLexico() {
        palabrasReservadas = {"begin", "end", "for", "if", "then", "while", "read",
                              "write", "to", "downto", "uses", "var", "do", "else", "program"};

        tiposDatos = {"integer", "string", "boolean", "float", "double", "char", "real"};

        operadores = {":=", "=", "+", "-", "*", "/", "mod", ">", "<", ">=", "<=", "<>",
                      ":", "(", ")", "true", "false", ";", ".", ","};
    }

    void analizar(const std::string& codigo) {
        int i = 0;
        int n = (int)codigo.length();

        int fila = 1;
        int col  = 1;

        auto avanzar = [&](int pasos = 1) {
            while (pasos-- > 0 && i < n) {
                char c = codigo[i];
                i++;
                if (c == '\n') { fila++; col = 1; }
                else { col++; }
            }
        };

        while (i < n) {
            char c = codigo[i];

            if (std::isspace((unsigned char)c)) {
                avanzar(1);
                continue;
            }

            if (std::isalpha((unsigned char)c) || c == '_') {
                int startFila = fila;
                int startCol  = col;

                std::string lexema;
                while (i < n) {
                    char ch = codigo[i];
                    if (std::isalnum((unsigned char)ch) || ch == '_') {
                        lexema += ch;
                        avanzar(1);
                    } else break;
                }

                std::string lexLower = toLowerCopy(lexema);

                if (existeEnLista(palabrasReservadas, lexLower)) {
                    agregarToken(TipoToken::PALABRA_RESERVADA, startFila, startCol, lexema);
                } else if (existeEnLista(tiposDatos, lexLower)) {
                    agregarToken(TipoToken::TIPO_DATO, startFila, startCol, lexema);
                } else if (existeEnLista(operadores, lexLower)) {
                    agregarToken(TipoToken::OPERADOR, startFila, startCol, lexema);
                } else {
                    if (!existeEnLista(arregloVariables, lexema)) {
                        arregloVariables.push_back(lexema);
                    }
                    agregarToken(TipoToken::VARIABLE, startFila, startCol, lexema);
                }
                continue;
            }

            if (c == '\'') {
                int startFila = fila;
                int startCol  = col;

                std::string cadena;
                cadena += codigo[i];
                avanzar(1); 

                while (i < n && codigo[i] != '\'') {
                    cadena += codigo[i];
                    avanzar(1);
                }

                if (i < n && codigo[i] == '\'') {
                    cadena += codigo[i];
                    avanzar(1); 
                }

                agregarToken(TipoToken::CADENA, startFila, startCol, cadena);
                continue;
            }

            if (std::isdigit((unsigned char)c)) {
                int startFila = fila;
                int startCol  = col;

                std::string num;
                while (i < n && std::isdigit((unsigned char)codigo[i])) {
                    num += codigo[i];
                    avanzar(1);
                }
                agregarToken(TipoToken::NUMERO, startFila, startCol, num);
                continue;
            }

            if (i + 1 < n) {
                std::string op2 = codigo.substr(i, 2);
                if (existeEnLista(operadores, op2)) {
                    int startFila = fila;
                    int startCol  = col;
                    agregarToken(TipoToken::OPERADOR, startFila, startCol, op2);
                    avanzar(2);
                    continue;
                }
            }

            {
                std::string op1(1, c);
                if (existeEnLista(operadores, op1)) {
                    int startFila = fila;
                    int startCol  = col;
                    agregarToken(TipoToken::OPERADOR, startFila, startCol, op1);
                    avanzar(1);
                    continue;
                }
            }

            {
                int startFila = fila;
                int startCol  = col;
                agregarToken(TipoToken::DESCONOCIDO, startFila, startCol, std::string(1, c));
                avanzar(1);
            }
        }
    }

    void mostrarResultados() {
        std::cout << "--- LISTA DOBLEMENTE ENLAZADA DE TOKENS ---\n";
        std::cout << "[TIPO | FILA | COLUMNA | CONTENIDO]\n";
        listaTokens.print();

        std::cout << "\n--- ARREGLO DE VARIABLES (DINAMICO) ---\n";
        for (const auto& v : arregloVariables) {
            std::cout << "Var: " << v << "\n";
        }

        std::cout << "\nTotal tokens: " << listaTokens.size() << "\n";
    }
};

#endif