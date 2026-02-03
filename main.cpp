#include <iostream>
using namespace std;
#include "arraylist.h"
#include "node.h"

void printMenu(){
    cout << "\nMenu Lista\n";
    cout << "1) Anadir elemento\n";
    cout << "2) Eliminar elemento\n";
    cout << "3) Buscar (get) elemento\n";
    cout << "4) Imprimir lista\n";
    cout << "5) Primero\n";
    cout << "6) Ultimo\n";
    cout << "7) Tamano\n";
    cout << "8) Resetear cursor\n";
    cout << "9) Next (cursor)\n";
    cout << "10) Prior (cursor)\n";
    cout << "0) Salir\n";
    cout << "Elige una opcion: ";
}

int main(){
    list<int> l;
    int opt = -1;
    while(true){
        printMenu();
        if(!(cin >> opt)){
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada no valida. Intenta de nuevo.\n";
            continue;
        }

        if(opt == 0) break;

        int val;
        switch(opt){
            case 1:
                cout << "Valor a anadir: ";
                if(cin >> val){
                    l.add(val);
                    cout << "Anadido.\n";
                } else { cout << "Entrada invalida.\n"; cin.clear(); cin.ignore(10000, '\n'); }
                break;
            case 2:
                cout << "Valor a eliminar: ";
                if(cin >> val){
                    l.remove(val);
                    cout << "Si existia, eliminado.\n";
                } else { cout << "Entrada invalida.\n"; cin.clear(); cin.ignore(10000, '\n'); }
                break;
            case 3:
                cout << "Valor a buscar: ";
                if(cin >> val){
                    try{ cout << "Encontrado: " << l.get(val) << "\n"; }
                    catch(const exception &e){ cout << "No encontrado: " << e.what() << "\n"; }
                } else { cout << "Entrada invalida.\n"; cin.clear(); cin.ignore(10000, '\n'); }
                break;
            case 4:
                cout << "Contenido de la lista:\n";
                l.print();
                break;
            case 5:
                try{ cout << "Primero: " << l.first() << "\n"; } catch(const exception &e){ cout << "Error: " << e.what() << "\n"; }
                break;
            case 6:
                try{ cout << "Ultimo: " << l.last() << "\n"; } catch(const exception &e){ cout << "Error: " << e.what() << "\n"; }
                break;
            case 7:
                cout << "Tamano: " << l.size() << "\n";
                break;
            case 8:
                l.reset_cursor();
                cout << "Cursor reseteado al inicio.\n";
                break;
            case 9:
                try{ cout << "Next (valor actual): " << l.next() << "\n"; } catch(const exception &e){ cout << "Error: " << e.what() << "\n"; }
                break;
            case 10:
                try{ cout << "Prior (valor actual): " << l.prior() << "\n"; } catch(const exception &e){ cout << "Error: " << e.what() << "\n"; }
                break;
            default:
                cout << "Opcion no valida.\n";
        }
    }

    cout << "Saliendo. Estado final de la lista:\n";
    l.print();
    cout << "Tamano final: " << l.size() << "\n";
    return 0;
}
