#include <iostream>
#include <stdexcept> 
#include <unordered_set>
#include <iomanip> 
#include <locale>
#include <chrono>
#include <thread>

using namespace std;

void menu(double &saldo, string name);
void deposito(double &saldo, double cantidad);
void retiro(double &saldo, double cantidad);
string pedirNombre();
string pedirContrasena();
double obtenerCantidad();

int main() {
    string name;
    string password;
    double saldo = 0;

    cout<<endl<<"Banco NovaSol"<<endl<<endl;

    name = pedirNombre();
    password = pedirContrasena();

    menu(saldo, name);

    return 0;
}

string pedirNombre() {
    string name;
    try {
        cout<<"Ingrese su nombre: ";
        getline(cin, name);

        if (name.empty()) {
            throw invalid_argument("No ingresaste nada.");
        }

        for (char c : name) {
            if (!isalpha(c) && c != ' ') {
                throw invalid_argument("El nombre debe contener solo letras.");
            }
        }
        
        if (name.length() < 3){
            throw invalid_argument("El nombre debe tener al menos 3 caracteres");
        }

        if (name.length() > 20){
            throw invalid_argument("El nombre debe tener máximo 20 caracteres");
        }

        return name;
    }
    catch (const invalid_argument &e) {
        cerr<<e.what()<<endl;
        return pedirNombre();
    }
    catch (const exception &e) {
        cerr<<e.what()<<endl;
        return pedirNombre();
    }
}

string pedirContrasena() {
    string password;
    try {
        bool tieneMayuscula = false, tieneMinuscula = false, tieneNumero = false, tieneEspecial = false;
        unordered_set<char> caracteresEspeciales = {'!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '_', '=',
                                                    '+', '[', ']', '{', '}', '|', ';', ':', '\'', '"', ',', '.', '<',
                                                    '>', '?', '/'};
        cout<<"Ingrese su contraseña:";
        getline(cin, password);

        if (password.empty()) {
            throw invalid_argument("No ingresaste nada.");
        }

        if (password.length() < 8) {
            throw invalid_argument("La contraseña debe tener al menos 8 caracteres.");
        }

        if (password.length() > 20) {
            throw invalid_argument("La contraseña no debe exceder los 20 caracteres.");
        }

        for (char c : password) {
            if (isupper(c)) tieneMayuscula = true;
            if (islower(c)) tieneMinuscula = true;
            if (isdigit(c)) tieneNumero = true;
            if (caracteresEspeciales.count(c)) tieneEspecial = true;
        }

        if (!tieneMayuscula) {
            throw invalid_argument("La contraseña debe contener al menos una letra mayúscula.");
        }

        if (!tieneMinuscula) {
            throw invalid_argument("La contraseña debe contener al menos una letra minúscula.");
        }

        if (!tieneNumero) {
            throw invalid_argument("La contraseña debe contener al menos un número.");
        }

        if (!tieneEspecial) {
            throw invalid_argument("La contraseña debe contener al menos un carácter especial (!@#$%^&*).");
        }
        cout<<"Ingresando..."<<endl<<endl;
        return password;
    }
    catch (const invalid_argument &e) {
        cerr<<e.what()<<endl;
        return pedirContrasena();
    }
    catch (const exception &e) {
        cerr<<e.what()<<endl;
        return pedirContrasena(); 
    }
}

void menu(double &saldo, string name) {
    int opcion;
    double cantidad;
    bool success;
    do{
        success = false;
        cout<<"Bienvenido "<<name<<endl;
        cout.imbue(locale("en_US.UTF-8"));
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
                cantidad = obtenerCantidad();
                deposito(saldo, cantidad);
                success = true;
                break;
            case 2:
                cantidad = obtenerCantidad();
                retiro(saldo, cantidad);
                success = true;
                break;
            case 3:
                cout<<"Gracias por usar nuestros servicios"<<endl;
                break;
            default:
                cerr<<"Opción no valida"<<endl;
                break;
        }
        if (success) {
            this_thread::sleep_for(chrono::seconds(3));
            system("clear");
        }
    } while (opcion != 3);
}

void deposito(double &saldo, double cantidad) {
    try {
        saldo += cantidad;
        cout<<"Deposito exitoso"<<endl;
    }
    catch (const invalid_argument &e) {
        cerr<<e.what()<< endl<<endl;
    }
    catch (const exception &e) {
        cerr<<e.what()<<endl<<endl;
    }
}

void retiro(double &saldo, double cantidad) {
    try {
        if (cantidad > saldo) {
            throw invalid_argument("Saldo insuficiente");
        }
        saldo -= cantidad;
        cout<<"Retiro exitoso"<<endl;
    }
    catch (const invalid_argument &e) {
        cerr<< e.what()<<endl<<endl;
    }
    catch (const exception &e) {
        cerr<< e.what()<<endl<<endl;
    }
}

double obtenerCantidad() {
    string input;
    size_t pos;
    double cantidad;

    try {
        cout<<endl<<"Ingrese la cantidad: ";
        getline(cin, input); 

        if (input.empty()) {
            throw invalid_argument("No ingresaste nada. Por favor, ingrese un número.");
        }

        if (input.front() == ' ' || input.back() == ' ') {
            throw invalid_argument("La cantidad no debe contener espacios al inicio o al final.");
        }

        if (input.find(',') != string::npos) {
            throw invalid_argument("La cantidad no debe contener comas. Use un punto (.) como separador decimal.");
        }

        if (count(input.begin(), input.end(), '.') > 1) {
            throw invalid_argument("La cantidad no puede tener más de un punto decimal.");
        }

        for (char c : input) {
            if (!isdigit(c) && c != '.') {
                throw invalid_argument("La cantidad solo puede contener números y un punto decimal.");
            }
        }

        cantidad = stod(input, &pos);

        if (pos != input.length()) {
            throw invalid_argument("La cantidad contiene caracteres inválidos.");
        }

        if (cantidad <= 0) {
            throw invalid_argument("La cantidad debe ser mayor a 0.");
        }

        if (input.length() > 10) {
            throw invalid_argument("La cantidad es demasiado grande. Por favor, ingrese un número más pequeño.");
        }

        return cantidad;
    } 
    catch (const invalid_argument &e) {
        cerr<<e.what()<<endl<<endl;
        return obtenerCantidad();
    } 
    catch (const exception &e) {
        cerr<<e.what()<<endl<<endl;
        return obtenerCantidad();
    }
}

