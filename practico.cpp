/******************************************************************************\
 * Curso de Programación 1. Curso 2019-20 (adaptado al 2020-21)
 * Autores: Miguel Ángel Latre
 * Última revisión: 22 de diciembre de 2020
 * Resumen: Solución examen práctico de la 2.ª convocatoria de Programación 1
 *          (enunciado adaptado a los cambios hechos en la asignatura en el
 *          curso 2020-21).
 * Nota: El código de este programa no está repartido en varios módulos, por lo
 *       que se puede utilizar la extensión Code Runner de Visual Studio Code
 *       para ejecutarlo (Ctrl + Alt + N).
\******************************************************************************/
#include <cctype>
#include <iostream>
#include <fstream>
using namespace std;

/*
 * Pre:  «linea» no contiene letras que no sean del alfabeto inglés.
 * Post: Si en «linea» simultáneamente, aparece al menos una minúscula y hay 
 *       más letras mayúsculas que minúsculas, ha devuelto true. En caso 
 *       contrario, ha devuelto false.
 */
bool hayQueCorregir(const string linea) {
    unsigned int mayusculas = 0;
    unsigned int minusculas = 0;
    for (unsigned int i = 0; i < linea.length(); i++) {
        if (isupper(linea.at(i))) {
            mayusculas++;
        }
        else if (islower(linea.at(i))) {
            minusculas++;
        }
    }
    return minusculas > 0 && mayusculas > minusculas;
}


/*
 * Pre:  «linea» no contiene letras que no sean del alfabeto inglés.
 * Post: Si en «linea» simultáneamente, aparece al menos una minúscula y hay 
 *       más letras mayúsculas que minúsculas, ha invertido las mayúsculas y 
 *       minúsculas de «linea». En caso contrario, no ha realizado ningún
 *       cambio.
 */
void corregirLinea(string& linea) {
    if (hayQueCorregir(linea)) {
        for (unsigned int i = 0; i < linea.length(); i++) {
            if (isupper(linea.at(i))) {
                linea.at(i) = tolower(linea.at(i));
            }
            else {
                linea.at(i) = toupper(linea.at(i));
            }
        }
    } 
}


/* Pre:  «original» y «corregido» son dos flujos abiertos y asociados con
 *       ficheros externos de texto. El contenido de «original» no contiene
 *       letras que no sean del alfabeto inglés.
 * Post: Ha copiado el contenido de «original» en «corregido», pero
 *       corrigiendo las líneas que supuestamente se han escrito
 *       accidentalmente con la tecla de bloqueo de mayúsculas activada. Se 
 *       considera que esas líneas son aquellas en las que, simultáneamente, 
 *       aparece al menos una minúscula y hay más letras mayúsculas que 
 *       minúsculas. «original» y «corregido» siguen abiertos.
 */
void corregirMayusculas(istream& original, ostream& corregido) {
    string linea;
    while (getline(original, linea)) {
        corregirLinea(linea);
        corregido << linea << endl;
    }
}


/*
 * Programa que solicita al usuario el nombre de un fichero de texto que 
 * no contiene letras que no sean del alfabeto inglés y el nombre de un fichero
 * de texto en el que se va a copiar el contenido del primero, pero corrigiendo 
 * las líneas que supuestamente se hayan escrito accidentalmente con la tecla de 
 * bloqueo de mayúsculas activada. Se considera que esas líneas son aquellas en  
 * las que, simultáneamente, aparece al menos una minúscula y hay más letras
 * mayúsculas que minúsculas. Cuando es ejecutado, si no hay ningún problema 
 * con la apertura y creación de los ficheros involucrados, el programa 
 * informa de que ha podido generar el nuevo fichero correctamente. En el caso
 * de que el programa no pueda abrir el primer fichero o no pueda crear el 
 * segundo, se limitará a escribir un mensaje de error
 */
int main() {
    cout << "Escriba el nombre del fichero original: ";
    string nombreFicheroOriginal;
    getline(cin, nombreFicheroOriginal);
    
    cout << "Escriba el nombre del fichero corregido: ";
    string nombreFicheroCorregido;
    getline(cin, nombreFicheroCorregido);

    ifstream original(nombreFicheroOriginal);
    if (original.is_open()) {
        ofstream corregido(nombreFicheroCorregido);
        if (corregido.is_open()) {
            corregirMayusculas(original, corregido);
            corregido.close();
            cout << "El fichero \"" << nombreFicheroCorregido 
                 << "\" se ha generado correctamente." << endl;
        }
        else {
            cerr << "No ha podido crearse el fichero \"" 
                 << nombreFicheroCorregido << "\"." << endl;        
        }
        original.close();
    }
    else {
        cerr << "No ha podido abrirse el fichero \"" 
             << nombreFicheroOriginal << "\"." << endl;        
    }

    return 0;
}
