#include "Input.h"

string_view pedirNombre() {
    string name;
    cout<<"Ingrese su nombre: ";
    getline(cin, name);

    if (name.empty())
    {
        cerr<<"No ingresaste nada."<<endl<<endl;
        return pedirNombre();
    }

    for (char c : name) {
        if (!isalpha(c) && c != ' ') {
            cerr << "El nombre debe contener solo letras."<<endl<<endl;
            return pedirNombre();
        }
    }

    if (name.length() < 3) {
        cerr<<"El nombre debe tener al menos 3 caracteres"<<endl<<endl;
        return pedirNombre();
    }

    if (name.length() > 20) {
        cerr<<"El nombre debe tener máximo 20 caracteres"<<endl<<endl;
        return pedirNombre();
    }

    return name;
}

string_view pedirContrasena() {
    string password;
    bool tieneMayuscula = false, tieneMinuscula = false, tieneNumero = false, tieneEspecial = false;
    unordered_set<char> caracteresEspeciales = {'!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '_', '=',
                                                '+', '[', ']', '{', '}', '|', ';', ':', '\'', '"', ',', '.', '<',
                                                '>', '?', '/'};

    cout<<"Ingrese su contraseña:";
    getline(cin, password);

    if (password.empty()) {
        cerr<<"No ingresaste nada."<<endl<<endl;
        return pedirContrasena();
    }

    for (char c : password) {
        if (isupper(c)) tieneMayuscula = true;
        if (islower(c)) tieneMinuscula = true;
        if (isdigit(c)) tieneNumero = true;
        if (caracteresEspeciales.count(c)) tieneEspecial = true;
    }

    if (password.length() < 8 ) {
        cerr<<"La contraseña debe tener al menos 8 caracteres"<<endl<<endl;
        return pedirContrasena();
    }

    if (!tieneMayuscula || !tieneMinuscula || !tieneNumero || !tieneEspecial) {
        cerr<<"La contraseña debe contener al menos una mayúscula, una minúscula, un número y un carácter especial."<<endl<<endl;
        return pedirContrasena();
    } 

    cout<<"Ingresando..."<<endl<<endl;
    return password;
}
