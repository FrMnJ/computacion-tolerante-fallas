#include <iostream>
#include <unordered_set>
#include <iomanip>
#include <locale>
#include <chrono>
#include <thread>
#include <optional>
#include <algorithm>
#include <string_view>

using namespace std;

void menu(double &saldo, string_view name);
void deposito(double &saldo, double cantidad);
void retiro(double &saldo, double cantidad);
string_view pedirNombre();
string_view pedirContrasena();
optional<double> obtenerCantidad();

int main() {
    string_view name;
    string_view password;
    double saldo = 0;

    cout<<endl<<"Banco NovaSol"<<endl<<endl;

    name = pedirNombre();
    password = pedirContrasena();

    this_thread::sleep_for(chrono::seconds(3));
    system("clear");
    menu(saldo, name);

    return 0;
}

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

void menu(double &saldo, string_view name) {
    int opcion;
    double cantidad;
    bool success;
    do {
        success = false;
        cout<<"Bienvenido "<<name<<endl;
        // This line is not working in Ubuntu
        // cout.imbue(locale("en_US.UTF-8"));
        cout<<fixed<<setprecision(2);
        cout<<"Su saldo actual es: $"<<saldo<<endl<<endl;
        cout<<"Seleccione una opción"<<endl;
        cout<<"1. Depositar"<<endl;
        cout<<"2. Retirar"<<endl;
        cout<<"3. Salir"<<endl;
        cout<<"Opcion: ";
        cin>>opcion;

        switch (opcion) {
            case 1:
                if (auto cantidadOpt = obtenerCantidad(); cantidadOpt) {
                    deposito(saldo, *cantidadOpt);
                    success = true;
                } else {
                    cerr<<"Cantidad no válida. Intente de nuevo."<<endl<<endl;
                }
                break;
            case 2:
                if (auto cantidadOpt = obtenerCantidad(); cantidadOpt) {
                    retiro(saldo, *cantidadOpt);
                    success = true;
                } else {
                    cerr<<"Cantidad no válida. Intente de nuevo."<<endl<<endl;
                }
                break;
            case 3:
                cout<<"Gracias por usar nuestros servicios"<<endl<<endl;
                break;
            default:
                cerr<<"Opción no válida"<<endl<<endl;
                break;
        }
        if (success) {
            this_thread::sleep_for(chrono::seconds(3));
            system("clear");
        }
    } while (opcion != 3);
}

void deposito(double &saldo, double cantidad) {
    saldo += cantidad;
    cout<<"Depósito exitoso"<<endl;
}

void retiro(double &saldo, double cantidad) {
    if (cantidad > saldo) {
        cerr<<"Saldo insuficiente"<<endl<<endl;
    } else {
        saldo -= cantidad;
        cout<<"Retiro exitoso"<<endl<<endl;
    }
}

optional<double> obtenerCantidad() {
    string input;
    size_t pos;
    cout<<"Ingrese la cantidad: ";
    cin.ignore();
    getline(cin, input);

    if (input.empty()) {
        cerr<<"No ingresaste nada."<<endl<<endl;
        return nullopt;
    }

    if (input.front() == ' ' || input.back() == ' ') {
        cerr<<"La cantidad no debe contener espacios al inicio o al final."<<endl<<endl;
        return nullopt;
    }

    if (input.find(',') != string::npos) {
        cerr<<"La cantidad no debe contener comas."<<endl<<endl;
        return nullopt;
    }

    if (count(input.begin(), input.end(), '.') > 1) {
        cerr<<"La cantidad no puede tener más de un punto decimal."<<endl<<endl;
        return nullopt;
    }

    for (char c : input) {
        if (!isdigit(c) && c != '.') {
            cerr<<"La cantidad solo puede contener números y un punto decimal."<<endl<<endl;
            return nullopt;
        }
    }
    double cantidad = stod(input, &pos);

    if (pos != input.length()) {
        cerr<<"La cantidad contiene caracteres inválidos."<<endl<<endl;
        return nullopt;
    }

    if (cantidad <= 0) {
        cerr<<"La cantidad debe ser mayor a 0."<<endl<<endl;
        return nullopt;
    }

    if (input.length() > 10) {
        cerr<<"La cantidad es demasiado grande."<<endl<<endl;
        return nullopt;
    }

    return cantidad;
}


