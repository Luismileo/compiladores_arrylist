#ifndef ANALIZADOR_LEXICO_H
#define ANALIZADOR_LEXICO_H

#include <vector> 
#include <string>
#include <iostream>
#include <algorithm>
#include "Token.h"

class AnalizadorLexico {
private:
    std::vector<std::string> palabrasReservadas;
    std::vector<std::string> tiposDatos;
    std::vector<std::string> operadores;

    std::vector<std::string> arregloVariables;
    std::vector<Token> arregloTokens;

    bool existeEnLista(const std::vector<std::string>& lista, std::string valor) {
        return std::find(lista.begin(), lista.end(), valor) != lista.end();
    }

public:
    AnalizadorLexico() {
        palabrasReservadas = {"begin", "end", "for", "if", "then", "while", "read", 
                              "write", "to", "downto", "uses", "var", "do", "else", "program"};

        tiposDatos = {"Integer", "String", "Boolean", "Float", "Double", "Char", "Real"};

        operadores = {":=", "=", "+", "-", "*", "/", "mod", ">", "<", ">=", "<=", "<>", 
                      ":", "(", ")", "true", "false"};
    }

    void analizar(std::string codigo) {
        int i = 0;
        int n = codigo.length();

        while (i < n) {
            char c = codigo[i];

            if (isspace(c)) { i++; continue; }
            if (isalpha(c)) {
                std::string lexema = "";
                while (i < n && (isalnum(codigo[i]) || codigo[i] == '_')) {
                    lexema += codigo[i];
                    i++;
                }

                if (existeEnLista(palabrasReservadas, lexema)) {
                    arregloTokens.push_back({TipoToken::PALABRA_RESERVADA, lexema});
                } 
                else if (existeEnLista(tiposDatos, lexema)) {
                    arregloTokens.push_back({TipoToken::TIPO_DATO, lexema});
                }
                else {
                    if (!existeEnLista(arregloVariables, lexema)) {
                        arregloVariables.push_back(lexema);
                    }
                    arregloTokens.push_back({TipoToken::VARIABLE, lexema});
                }
                continue;
            }

            std::string op2 = codigo.substr(i, 2);
            if (existeEnLista(operadores, op2)) {
                arregloTokens.push_back({TipoToken::OPERADOR, op2});
                i += 2;
                continue;
            }

            std::string op1(1, c);
            if (existeEnLista(operadores, op1)) {
                arregloTokens.push_back({TipoToken::OPERADOR, op1});
                i++;
                continue;
            }

            if (c == '\'') {
                std::string cadena = "'";
                i++;
                while (i < n && codigo[i] != '\'') {
                    cadena += codigo[i];
                    i++;
                }
                cadena += "'"; i++;
                arregloTokens.push_back({TipoToken::CADENA, cadena});
                continue;
            }

            if (isdigit(c)) {
                std::string num = "";
                while (i < n && isdigit(codigo[i])) {
                    num += codigo[i];
                    i++;
                }
                arregloTokens.push_back({TipoToken::NUMERO, num});
                continue;
            }

            i++; 
        }
    }

    void mostrarResultados() {
        std::cout << "--- ARREGLO DE TOKENS (DINAMICO) ---\n";
        for (const auto& t : arregloTokens) {
            std::cout << "[" << t.tipoToString() << " | " << t.valor << "]\n";
        }

        std::cout << "\n--- ARREGLO DE VARIABLES (DINAMICO) ---\n";
        for (const auto& v : arregloVariables) {
            std::cout << "Var: " << v << "\n";
        }
    }
};

#endif