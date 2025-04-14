// se invocan las librerias necesarias para el correcto funcionamiento del programa
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <typeinfo>

// se le avisa al el estandar std que quiero usar funciones sin necesidad de anteponer std::
using std::cin;
using std::cout;
using std::endl;
using std::invalid_argument;
using std::chrono::seconds;
using std::this_thread::sleep_for;

// creacion de la funcion principal donde se ejecuta el codigo principal del programa
int main()
{
    /*
        -Primero se crean las variables necesarias
        -Luego se inicializan con un valor de 0 para evitar valores basura que hayan quedado en la memoria
        -Decidi crearlas todas en una misma linea porque se me hizo mas practico por las lineas de codigo ahorradas.
    */
    int cantidad_intentos = 0, limite_inferior = 0, limite_superior = 0, numero_aleatorio = 0, posible_numero = 0;
    int intentos_realizados = 0, intentos_restantes = 0;

    /*
        A continuacion se da una breve explicacion de que trata el juego y se procede
        a solicitar los datos necesarios al jugador, cada dato es almacenado en su respectiva variable
    */

    cout << "-------------INICIA EL JUEGO------------" << endl;
    cout << "Bienvenido al juego de adivinanzas, donde el objetivo es que adivines el numero generado de forma aleatoria antes de que se te acaben los intentos :)" << endl;

    cout << "\nAntes de empezar tenes que indicar dentro de que rango de numeros queres que generemos un numero aleatorio para vos" << endl;
    
    /*
        -El bucle while se ejecutara mientras no se rompa su flujo de ejecucion ya que la condicion esta establecida como true, 
        lo que ocasionara que se repita la pregunta hasta que el usuario ingrese un tipo de dato valido y se ejecute el break;
    */
    while(true)
    {
        cout << "ingresa el limite inferior: ";
        cin >> limite_inferior;

        if(cin.fail()) //se verifica si cin.fail() es true, si no hay un error en cin sera false
        {
            cout << "Tenes que ingresar numeros. Cualquier otro tipo de caracter es invalido." << endl;
            cin.clear(); //Se borra el error en cin para que esta funcion se pueda volver a usar normalmente
            cin.ignore(1000, '\n'); //Se "Vacia" el cin ignorando cualquier caracter introducido anteriormente o cualquier salto de linea

        } else if(limite_inferior < 0)
        {
            cout << "El limite inferior no puede ser menor a 0" << endl;
        }
        else {
            break; // rompe el while y la ejecucion vuelve al scope global
        }
    }

    while(true)
    {
        cout << "Ahora ingresa el limite superior: ";
        cin >> limite_superior;

        if(cin.fail()) //se verifica si cin.fail() es true, si no hay un error en cin sera false
        {
            cout << "Tenes que ingresar numeros. Cualquier otro tipo de caracter es invalido." << endl;
            cin.clear(); //Se borra el error en cin para que esta funcion se pueda volver a usar normalmente
            cin.ignore(1000, '\n'); //Se "Vacia" el cin ignorando cualquier caracter introducido anteriormente o cualquier salto de linea

        } else if(limite_superior < limite_inferior)
        {
            cout << "El limite superior no puede ser menor al limite inferior" << endl;
        }
        else {
            break; // rompe el while y la ejecucion vuelve al scope global
        }
    }

    while(true)
    {
        cout << "\nOk. Cuantos intentos queres tener? pueden ser tanto como quieras: ";
        cin >> cantidad_intentos;

        if(cin.fail()) //se verifica si cin.fail() es true, si no hay un error en cin sera false
        {
            cout << "Tenes que ingresar numeros. Cualquier otro tipo de caracter es invalido." << endl;
            cin.clear(); //Se borra el error en cin para que esta funcion se pueda volver a usar normalmente
            cin.ignore(1000, '\n'); //Se "Vacia" el cin ignorando cualquier caracter introducido anteriormente o cualquier salto de linea

        } else if(cantidad_intentos <= 0) //cantidad_intentos no puede ser igual o menor que 0 
        {
            //si cantidad_intentos es igual o menor que 0, se muestra un mensaje al usuario y se ejecuta el bucle hasta que introduzca un cantidad valida
            cout << "La cantidad de intentos maximos debe ser mayor a 0" << endl;
        }
        else {
            break; // rompe el while y devuelve el control de la ejecucion al scope global
        }
    }

    cout << "\nMuy bien, empezaste excelente, elegiste tener" << " " << cantidad_intentos << " " << "intentos" << endl;
    cout << "y el rango que estableciste va desde " << limite_inferior << " hasta " << limite_superior << endl
         << endl;

    cout << "Bueno, preparate porque el juego empieza en: " << endl;

    /*
        Este bucle for simula una cuenta regresiva haciendo uso de la libreria chrono y thread para detener el hilo de ejecucion actual
        la idea es darle unos segundos al jugador para ponerse comodo antes de empezar a adivinar
    */
    for (int i = 5; i >= 1; i--)
    {
        sleep_for(seconds(1));
        cout << i << endl;
    }

    // Con srand() se inicializa la funcion rand(), generando una semilla basada en el reloj para que rand() no repita la misma secuencia de numeros aleatorios
    srand(time(0));

    /*
        -se corrigio la formula para mayor eficacia
        -Ademas ahora la formula se coloco fuera del bucle
        para generar solo un numero random y no varios,
        esto resulta en una mayor probabilidad de adivinar
        -formula para generar numero random en un rango especifico
     */
    numero_aleatorio = rand() % (limite_superior - limite_inferior + 1) + limite_inferior;

    /*
        Este bucle for es el que ejecuta la secuencia de bloques por cada intento del jugador
        contiene un condicional if en su interior que se ejecuta solo si el usuario adivina el numero
    */

    for (int z = cantidad_intentos; z > 0; z--) // Condicion que hace que el bloque se ejecute determinadas veces
    {
        // Por cada vuelta del bucle for se va a evaluar si el jugaro esta introduciendo un tipo de dato valido
        do
        {
            cout << "Cual es el numero secreto?: ";
            cin >> posible_numero;

            /*
                -Cual el jugador introduzca un dato se evaluara si hay un error haciendo uso de cin.fail()
                -Si cin.fail() detecta un tipo de dato invalido su valor sera true entonces se ejecutara el if mostrando un mensaje de advertencia,
                luego se borrara el valor de cin con cin.clear()
                por ultimo con cin.ignore() se eliminan los caracteres introducidos
                o cualquier salto de linea que haya quedado guardado en el para evitar su ejecucion y que nos siga mostrando fallos
            */
            if (cin.fail())
            {
                cout << "Debes introducir numeros. otros caracteres no son validos." << endl;
                cin.clear();
                cin.ignore(1000, '\n');

                // Cada dato mal introducido tambien se contara como intento fallido y se le mostrara la informacion en pantalla
                intentos_realizados++;
                z--; /*Es probable que el while se ejecute varias veces y el for quede pausado, 
                esto ocasionara que z no se decremente tras cada vuelta del ciclo while, lo que podria generar un problema 
                si el jugador de repente introduce un dato valido ya que tendria mas intentos de los que 
                les corresponden, entonces es necesario ir decrementando z manualmente dentro del while para que cuando se 
                rompa el bucle y el control de la ejecucion pase al scope del for 
                el jugador solo cuente con los intentos restantes teniendo en cuenta los que ya gasto dentro del scope del while*/

                cout << "Intentos realizados: " << intentos_realizados << endl;
                cout << "Intentos restantes: " << cantidad_intentos - intentos_realizados << endl;
                cout << "---------------------------------" << endl;

                if (z == 0)
                {
                    cout << "Intentos agotados. Suerte para la proxima" << endl;
                    cout << "-------------FIN DEL JUEGO------------" << endl;
                    cout << "presiona enter para cerrar el juego...";
                    cin.get();
                    return 0; // Finaliza la ejecucion del codigo
                }
            }
            else
            {
                // Si el jugador ingreso un tipo de dato valido entonces se rompe el flujo del while para continuar con el flujo del for
                intentos_realizados++;
                break;
            }

        } while (true);

        /*
            En caso de que el jugador adivine el numero , el condicional ejecuta el mensaje cout
            y lanza un return 0 para finalizar la ejecucion del codigo instantaneamente.
        */
        if (posible_numero == numero_aleatorio)
        {
            cout << "INCREIBLEEEEEE!!!!! LOGRASTE ADIVINAR EL NUMERO SECRETO :D" << endl;
            cout << "Tenias " << cantidad_intentos << " intentos ";
            cout << "y has realizado " << intentos_realizados << endl;

            cout << "-------------FIN DEL JUEGO------------" << endl;
            cin.ignore(); // Limpia el buffer para ignorar el salto de linea que es interpretado como un "enter"
            cout << "Presiona enter para cerrar el juego...";
            cin.get(); // Evita que se cierre la consola
            return 0;  // Finaliza la ejecucion del codigo porque termino el juego
        }

        /*
            -Si el jugador introduce un numero y no adivino el numero secreto entonces se evalua si el numero introducido cumple con las condiciones establecidas
        */
        if (posible_numero > limite_inferior && posible_numero < limite_superior)
        {

            // Si se encuentra dentro del rango establecido entonces se procede a evaluar si es mayor al numero secreto
            if (posible_numero > numero_aleatorio)
            {
                cout << "El numero que ingresaste es mayor que el numero secreto" << endl;
            }
            else if (posible_numero < numero_aleatorio) // Si se encuentra dentro del rango establecido y no es mayor al numero secreto entonces se evalua si es menor
            {
                cout << "El numero que ingresaste es menor que el numero secreto" << endl;
            }
        }
        /*
        En caso de que el numero no se encuentre dentro del rango establecido,
        se evalua si el numero ingresado esta por debajo del limite inferior o por encima del limite superior
        */
        else if (posible_numero < limite_inferior)
        {
            cout << "El numero que ingresaste no se encuentra dentro del rango establecido por que es inferior a " << limite_inferior << endl;
        }
        else if (posible_numero > limite_superior)
        {
            cout << "El numero que ingresaste no se encuentra dentro del rango establecido por que es mayor a " << limite_superior << endl;
        }
        
        cout << "Intentos realizados: " << intentos_realizados << endl;
        cout << "Intentos restantes: " << cantidad_intentos - intentos_realizados << endl;
        cout << "---------------------------------" << endl;
    }

    // Si el se queda sin intentos se lo hacemos saber
    cout << "Intentos agotados. Suerte para la proxima" << endl;

    /*
        -cin.ignore() Limpia el buffer para ignorar el salto de linea que es interpretado como un "enter"
        -cin.get() Evita que se cierre la consola
        -Se reemplazo system("pause") de windows por cin.get() para hacer el codigo mas portable ya que el comando system("pause") es propio de windows
    */
    cout << "-------------FIN DEL JUEGO------------" << endl;
    cin.ignore();
    cout << "\nPresiona enter para cerrar el juego...";
    cin.get();
    return 0; // Finaliza la ejecucion del codigo
}