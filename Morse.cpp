#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <windows.h>
using namespace std;

//tabla de codigo morse
const string abcMorse[26] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..",
    "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-",
    "-.--", "--.."
};
//tabla de alfabeto
const char abcLetra[26] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
    'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z'
};
//ambos arreglos son variables constantes y globales ya que son valores fijos.
//Hecho por Matthew
void sonido(string morse) {
    for (char c : morse) { //lo que hace esta funcion es como los vectores, lee cada caracter que sale del loop
        if (c == '.') {
            Beep(1000, 200); //1000 son los hertz para sonido agudo, 200 son los milisegundos de duracion de beep.
        }
        else if (c == '-') {
            Beep(1000, 600);
        }
        Sleep(200); //Sleep es la pausa entre beeps
    }
}
//Void hecho por Leyra
void LetraAmorse() {
    int correcta = 0, incorrecta = 0; //contador desde cero para la sumatoria
    char opc;
    srand(time(0)); //para que rand funcione

    do {
        //genera letra aleatoria, %26 porque esa es la cantidad de valores
        int index = rand() % 26;
        char letra = abcLetra[index];
        string respCorrecta = abcMorse[index];
        sonido(respCorrecta);

        //respuesta de usuario
        cout << "\nLetra: " << letra << "\n";
        cout << "Escribe el codigo morse (usa puntos y guiones): ";
        string respuestaUsuario;
        cin >> respuestaUsuario;

        //verificacion de la respuesta
        if (respuestaUsuario == respCorrecta) {
            cout << "Muy bien\n";
            correcta++;
        }
        else {
            cout << "Incorrecto, la respuesta correcta era: " << respCorrecta << "\n";
            incorrecta++;
        }
        cout << "Desea jugar otra ronda? (s/n): ";
        cin >> opc;
    } while (opc == 's' || opc == 'S');

    //output de que tan bien (o mal) le fue al usuario
    cout << "\nRondas completadas\n";
    cout << "Respuestas correctas: " << correcta << "\nRespuestas incorrectas: " << incorrecta << "\n"; 
    //se guardan los datos segun lo que el usuario haya sacado, se puede ver en historial, menu
    ofstream archivo("puntajes.txt", ios::app);//lo que hace ios::app es conservar lo que esta en el txt file aunque salgas del mismo. https://en.cppreference.com/w/cpp/io/basic_fstream
    archivo << "En letra a morse sacaste lo siguiente : \nCorrectas : " << correcta << "\nIncorrectas : " << incorrecta << "\n";
    archivo.close();
}
//Hecho por Matthew
void MorseAletra() {
    int correct = 0, incorrect = 0;
    char opc;
    srand(time(0));

    do {
        int morse = rand() % 26;
        string code = abcMorse[morse];
        char respCorrect = abcLetra[morse];

        cout << "\nPalabra: " << code << "\n";
        cout << "Escribe la letra correspondiente: ";
        char capmorse;
        cin >> capmorse;
        capmorse = toupper(capmorse);
        sonido(code);

        if (capmorse == respCorrect) {
            cout << "Muy bien\n";
            correct++;
        }
        else {
            cout << "Incorrecto, la respuesta correcta era: " << respCorrect << "\n";
            incorrect++;
        }

        cout << "Desea jugar  otra ronda? (s/n): ";
        cin >> opc;
    } while (opc == 's' || opc == 'S');

    cout << "\nRondas completadas\n";
    cout << "Respuestas correctas: " << correct << "\nRespuestas incorrectas: " << incorrect << "\n";
    //se guardan los datos segun lo que el usuario haya sacado, se puede ver en historial, menu
    ofstream archivo("puntajes.txt", ios::app);//lo que hace ios::app es leer el archivo e ir directamente al final para seguir escribiendo, en comparacion a ios::ate que puede escribir de cualquier parte del archivo. https://mejorcodigo.com/p/66828.html
    archivo << "En morse a letra sacaste lo siguiente : \nCorrectas : " << correct << "\nIncorrectas : " << incorrect << "\n";
    archivo.close();
}
//Hecho por Matthew y Leyra
void Menu() {
    int opc;
    do {
 cout << "\n----------------------------------------\n";
 cout << "|               MENU                   |\n";
 cout << "----------------------------------------\n";
 cout << "|  1. Letras del abecedario a Morse    |\n";
 cout << "|  2. Morse a letra                    |\n";
 cout << "|  3. Ver historial de puntajes        |\n";
 cout << "|  4. Borrar historial                 |\n";
 cout << "|  5. Salir                            |\n";
 cout << "----------------------------------------\n";
 cout << "Elige una opcion valida: ";
        cin >> opc;
        cin.ignore();

        switch (opc) {
        case 1:
            LetraAmorse();
            break;

        case 2:
            MorseAletra();
            break;

        case 3: { //Hecho por Leyra
            cout << "Historial de puntajes\n";
            string text;
            ifstream archivo("puntajes.txt");//ifstream para leer el contenido del txt
            while (getline(archivo, text)) {//referencia w3schools
                cout << text << endl;
           }
            archivo.close();
            break;
        }
        case 4:{ //Hecho por Matthew
            ofstream archivoBorrar("puntajes.txt", ios::trunc); //trunc borra el contenido al momento que se ejecuta. https://en.cppreference.com/w/cpp/io/basic_fstream
            if (archivoBorrar.is_open()) {
                archivoBorrar.close();
                cout << "Contenido del archivo eliminado" << endl;
            }
            break;
        }

        case 5:
            cout << "Gracias por usar nuestro programa";
            break;

        default:
            cout << "Input invalido, vuelva a intentarlo." << endl;
            break;
        }
    } while (opc != 5);
}

int main() {
    Menu();
    return 0;
}
