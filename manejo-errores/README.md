# Banco NovaSol - Manejo de Errores

## Descripción
Este repositorio contiene dos programas diseñados para demostrar el manejo de errores en C++: uno utilizando `try-catch` para capturar excepciones y otro utilizando `optional` para manejar valores que podrían no estar presentes. Ambos programas simulan un sistema bancario donde los usuarios pueden realizar depósitos, retiros y gestionar su saldo.

## Programas

### Manejo de errores con try-catch
Este programa utiliza bloques `try-catch` para capturar excepciones y asegurar que el sistema maneje errores como entradas vacías, caracteres inválidos o valores fuera de rango en las operaciones bancarias. Los usuarios deben ingresar su nombre, contraseña y una cantidad para realizar depósitos y retiros.

### Manejo de errores con optional
En este programa, se utiliza `optional` para manejar cantidades de dinero ingresadas por el usuario que podrían no ser válidas o ausentes. Si el valor es inválido, el sistema no permite continuar con la operación y muestra un mensaje de error.

## Funcionalidades

- **Ingreso de nombre y contraseña**: Los usuarios deben ingresar su nombre y contraseña, con validaciones sobre caracteres permitidos, longitud y complejidad de la contraseña.
- **Operaciones bancarias**: Los usuarios pueden realizar depósitos y retiros, donde se validan las cantidades y el saldo disponible.
- **Validación de entradas**: Ambos programas implementan controles para asegurarse de que las entradas sean correctas, utilizando `try-catch` en el primer caso y `optional` en el segundo.

## Ejemplos
Dentro de la carpeta ejemplos, encontrarás imágenes que muestran el funcionamiento de ambos programas. Las imágenes ilustran cómo se gestionan las excepciones o los valores opcionales al realizar cada operación.

## Requisitos

- **Compilador C++**: Se recomienda usar un compilador que soporte C++11 y C++17.
- **Sistema operativo**: El programa es compatible con sistemas operativos como Windows, macOS y Linux.

## Instrucciones para ejecutar

1. Clona este repositorio.
2. Abre el terminal en la carpeta del proyecto.
3. Compila los archivos C++ con los siguientes comandos:

```bash
clang++ -std=c++17 sistema_bancario_opt.cpp -o sistema_bancario_opt      
clang++ -std=c++11 sistema_bancario_try.cpp -o sistema_bancario_try
```
Y ejecuta los programas

```bash
./banco_try_catch
./banco_optional
```
