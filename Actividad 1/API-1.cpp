#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>

using std::cin;
using std::cout;
using std::endl;
using std::chrono::seconds;
using std::this_thread::sleep_for;

int main()
{

    // Primero se crean las variables necesarias, decidi crearlas todas en una misma linea porque se me hizo mas practico por las lineas de codigo ahorradas.

    int cantidad_intentos, limite_inferior, limite_superior, numero_aleatorio, posible_numero;

    /*
        A continuacion una breve explicacion de que trata el juego y se procede
        a solicitar los datos necesarios al jugador, cada datos es almacenado en su respectiva variable
    */
    cout << "Bienvenido al juego de adivinanzas, donde el objetivo es que adivines el numero generado de forma aleatoria antes de que se te acaben los intentos :)" << endl;

    cout << "\nAntes de empezar tenes que indicar dentro de que rango de numeros queres que generemos un numero aleatorio para vos, ingresa el limite inferior: ";
    cin >> limite_inferior;

    cout << "Perfecto, ahora necesitamos que ingreses el limite superior, es decir el tope maximo para este rango de numeros: ";
    cin >> limite_superior;

    cout << "\nAhora tenes que ingresar cuantos intentos que queres tener, pueden ser tanto como quieras, ingresalo a continuacion: ";
    cin >> cantidad_intentos;

    cout << "\nMuy bien, empezaste excelente, elegiste tener" << " " << cantidad_intentos << " " << "intentos." << endl;
    cout << "y el rango que estableciste va desde " << limite_inferior << " hasta " << limite_superior << endl << endl;

    cout << "Bueno, preparate porque el juego empieza en: " << endl;

    /*
        Este bucle for simula un contador haciendo uso de la libreria chrono y thread para detener el hilo de ejecucion actual
        la idea es darle unos segundos al jugador para ponerse comodo antes de empezar a adivinar
    */
    for (int i = 5; i >= 1; i--)
    {
        sleep_for(seconds(1));
        cout << i << endl;
    }

    srand(time(0)); // Inicializa la funcion rand(), generando una semilla basada en el reloj para que rand() no repita la misma secuencia de numeros aleatorios

    /*
        Este bucle for es el que ejecuta la secuencia de bloques por cada intento del jugador
        contiene un condicional if en su interior que se ejecuta solo si el usuario adivina el numero
    */
    for (int z = cantidad_intentos; z > 0; z--)//Condicion que hace que el bloque se ejecute determinadas veces
    {
        numero_aleatorio = rand() % limite_superior + limite_inferior; // formula para generar numero random en un rango especifico

        cout << "Cual es el numero secreto?: ";
        cin >> posible_numero;

        // En caso de que el jugador adivine el condicional ejecuta el mensaje cout y lanza un return 0 para finalizar la ejecucion del codigo instantaneamente.
        if (posible_numero == numero_aleatorio)
        {
            cout << "INCREIBLEEEEEE!!!!! LOGRASTE ADIVINAR EL NUMERO SECRETO :D";

            return 0;
        }
        else //En el caso contrario se le muestra cual era el numero aleatorio
        {
            cout << "Fallaste, el numero era " << numero_aleatorio << endl;
        }
    }

    cout << "Que lastima, no adivinaste el numero y ya te quedaste sin intentos, suerte la proxima :) \n";

    system("pause"); //Evita que se cierre la consola despues del return
}