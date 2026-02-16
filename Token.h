#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TipoToken {
    PALABRA_RESERVADA,
    TIPO_DATO,
    OPERADOR,
    VARIABLE,
    NUMERO,
    CADENA,
    DESCONOCIDO
};

struct Token {
    TipoToken tipo;
    std::string valor;

    std::string tipoToString() const {
        switch (tipo) {
            case TipoToken::PALABRA_RESERVADA: return "RESERVADA";
            case TipoToken::TIPO_DATO:         return "TIPO";
            case TipoToken::OPERADOR:          return "OPERADOR";
            case TipoToken::VARIABLE:          return "VARIABLE";
            case TipoToken::NUMERO:            return "NUMERO";
            case TipoToken::CADENA:            return "CADENA";
            default:                           return "DESCONOCIDO";
        }
    }
};

#endif