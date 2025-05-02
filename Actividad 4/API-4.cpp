// se invocan las librerias necesarias para el correcto funcionamiento del programa
#include <iostream> // Para entrada y salida de datos
#include <chrono>   // para la funcion seconds()
#include <thread>   //para pausar el hilo de ejecucion y simular la cuenta regresiva
#include <cstdlib>  // para usar la funcion rand()
#include <ctime>    // para usar la funcion time() con srand() y generar la semilla para el numero random
#include <cstring>  //Para poder trabajar y crear datos de tipo string

// se le avisa al estandar std que quiero usar funciones sin necesidad de anteponer std::
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::chrono::seconds;
using std::this_thread::sleep_for;


//Esta funcion muestra en pantalla los numeros introducidos
//Se almacena la referencia del arreglo original y se la pasa como argumento en un puntero llamado arreglo
//Luego se pasa como argumento los intentos contabilizados para poder iterar el arreglo esa cantidad de veces
void mostrarNumeros(int* arreglo, int intentos_contados)
{
    cout << "Los numeros que ingresaste se muestran a continuacion ordenados de manera ascendente: ";
    // Con el for recorremos el arreglo para mostrar en pantalla todos los numeros introducidos
    
    for(int i = 0; i < intentos_contados - 1; i++)
    {
        for(int z = 0; z < intentos_contados - 1; z++)
        {
            if(arreglo[z] > arreglo[z + 1])
            {
                int aux = 0;
                aux = arreglo[z + 1];
                arreglo[z + 1] = arreglo[z];
                arreglo[z] = aux;
            }
        }
    }
    for (int j = 0; j < intentos_contados; j++)
    {
        cout << arreglo[j] << " ";
    }
}
// Esta funcion hace que no tengamos que repetir varias veces las mismas lineas de codigo en diferentes partes de la funcion main
// Como lo expresa el nombre la funcion, muestra en pantalla el mensaje que finaliza el juego y precede al return 0;
void printMsgFin()
{
    /*
        -cin.ignore() Limpia el buffer para ignorar el salto de linea que es interpretado como un "enter"
        -cin.get() Evita que se cierre la consola
        -Se reemplazo system("pause") de windows por cin.get() para hacer el codigo mas portable ya que el comando system("pause") es propio de windows
    */
    cout << "\n-------------FIN DEL JUEGO------------" << endl;
    cout << "presiona enter para cerrar el juego...";
    cin.ignore(1000, '\n');
    cin.get();
}
// Funcion que valida que los datos ingresados sean los que se esperan
// La funcion retorna un string "ok" si todo esta bien, de lo contrario si cin.fail() es true, retorna un mensaje de advertencia
string validarDatos()
{

    if (cin.fail())
    {

        cin.clear();            // Se borra el error en cin para que esta funcion se pueda volver a usar normalmente
        cin.ignore(1000, '\n'); // Se "Vacia" el cin ignorando cualquier caracter introducido anteriormente o cualquier salto de linea
        cout << "Haz introducido un tipo de dato invalido. Tenes que ingresar numeros." << endl;

        return "no";
    }
    else
    {
        return "yes";
    }
}

// INICIO DE FUNCION MAIN
//  creacion de la funcion principal donde se ejecuta el codigo principal del programa
int main()
{
    /*
        -Primero se crean las variables necesarias
        -Luego se inicializan con un valor de 0 para evitar valores basura que hayan quedado en la memoria
        -Decidi crearlas todas en una misma linea porque se me hizo mas practico por las lineas de codigo ahorradas.
    */
    int cantidad_intentos = 0, limite_inferior = 0, limite_superior = 0, numero_aleatorio = 0, posible_numero = 0;
    int intentos_realizados = 0, intentos_restantes = 0, indice = 0;
    bool numero_existe = false;

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
    // CICLO WHILE PARA PEDIR LIMITE INFERIOR
    while (true)
    {

        cout << "ingresa el limite inferior: ";
        cin >> limite_inferior;

        // if que evalua lo que retorna la funcion validarDatos()
        if (validarDatos() == "yes")
        {

            if (limite_inferior < 0)
            {
                cout << "El limite inferior no puede ser menor a 0" << endl;
            }
            else
            {
                break; // rompe el while y la ejecucion vuelve al scope global
            }
        }
    }

    // CICLO WHILE PARA PEDIR LIMITE SUPERIOR
    while (true)
    {

        cout << "Ahora ingresa el limite superior: ";
        cin >> limite_superior;

        // if que elavua lo que retorna la funcion validarDatos()
        if (validarDatos() == "yes")
        {

            if (limite_superior < limite_inferior)
            {
                cout << "El limite superior no puede ser menor al limite inferior" << endl;
            }
            else if (limite_superior == limite_inferior)
            {
                cout << "El limite superior no puede ser igual al limite inferior, debe ser mayor" << endl;
            }
            else
            {
                break; // rompe el while y la ejecucion vuelve al scope global
            }
        }
    }

    // CICLO WHILE PARA PEDIR CANTIDAD DE INTENTOS
    while (true)
    {

        cout << "\nCuantos intentos queres tener? pueden ser tanto como quieras: ";
        cin >> cantidad_intentos;

        // if que evalua lo que retorna la funcion validarDatos()
        if (validarDatos() == "yes")
        {

            if (cantidad_intentos <= 0) // cantidad_intentos no puede ser igual o menor que 0
            {
                // si cantidad_intentos es igual o menor que 0, se muestra un mensaje al usuario y se ejecuta el bucle hasta que introduzca un cantidad valida
                cout << "La cantidad de intentos maximos debe ser mayor a 0" << endl;
            }
            else
            {
                // Aqui intentos restantes toma el valor de cantidad_intentos porque despues a esta variable se le ira
                // descontando los intentos y servira para mostrar en pantalla cuantos quedan, tambien se usara como condicion para el while
                intentos_restantes = cantidad_intentos;

                break; // rompe el while y devuelve el control de la ejecucion al scope global
            }
        }
    }

    /*
        -Aqui declaro el arreglo que va a contener los numeros que el usuario ingrese
        -Su longitud dependera de la cantidad de intentos ingresados por el usuario
    /**/
    int numeros_ingresados[cantidad_intentos] = {}; // Se inicializa vacio

    // Aqui le mostramos en pantalla los datos que ha ingresado y posteriormente comenzar el juego
    cout << "\nMuy bien, empezaste excelente, elegiste tener" << " " << cantidad_intentos << " " << "intentos" << endl;
    cout << "y el rango que estableciste va desde " << limite_inferior << " hasta " << limite_superior << endl
         << endl;

    cout << "Bueno, preparate porque el juego empieza en: " << endl;

    /*
        Este bucle for simula una cuenta regresiva haciendo uso de la libreria chrono y thread para detener el hilo de ejecucion actual
        la idea es darle unos segundos al jugador para ponerse comodo antes de empezar a adivinar
    */
    for (int i = 3; i >= 1; i--)
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

    // Por cada vuelta del bucle for se va a evaluar si el jugador esta introduciendo un tipo de dato valido
    do
    {
        cout << "\nCual es el numero secreto?: ";
        cin >> posible_numero;

        // Con este condicional if-else-if validamos si el usuario ingresa o no el tipo de dato que esperamos

        if (validarDatos() == "no")
        {

            validarDatos();
            // Ahora los intentos incorrectos no seran contabilizados
            continue;
        }
        else if (validarDatos() == "yes")
        {
            // AQUI SE EMPIEZA EL JUEGO REALMENTE PORQUE EL JUGADOR YA HA INTRODUCIDO EL PRIMER NUMERO DE MANERA CORRECTA

            /*
            En caso de que el jugador adivine el numero , el condicional ejecuta el mensaje cout
            y lanza un return 0 para finalizar la ejecucion del codigo instantaneamente.
            */

            if (posible_numero == numero_aleatorio)
            {
                intentos_realizados++;                       // Si el jugador adivina el numero debe contarse como intento, ademas esta variable servira en el for
                numeros_ingresados[indice] = posible_numero; // Aca tambien debemos guardar el numero en el arreglo porque si no, no podremos mostrar en pantalla correctamente

                cout << "INCREIBLEEEEEE!!!!! LOGRASTE ADIVINAR EL NUMERO SECRETO :D" << endl;
                cout << "Tenias " << cantidad_intentos << " intentos ";
                cout << "y has realizado " << intentos_realizados << endl;

                mostrarNumeros(numeros_ingresados,intentos_realizados);
                printMsgFin();
                return 0; // Finaliza la ejecucion del codigo porque termino el juego
            }
            /*
                -Si el jugador introduce un numero y no adivino el numero secreto entonces se evalua
                si el numero introducido cumple con las condiciones establecidas en cuanto al rango
            */
            if (posible_numero >= limite_inferior && posible_numero <= limite_superior)
            {
                // Luego de comprobar si el numero esta dentro del rango se comprueba si ya existe en el arreglo,
                // en caso de que ya exista no cuenta como intento valido
                for (int i = 0; i < cantidad_intentos; i++)
                {
                    if (posible_numero == numeros_ingresados[i])
                    {
                        cout << "El numero ya fue ingresado anteriormente, intente con otro." << endl;
                        numero_existe = true; // establecemos que el numero existe dentro del arreglo
                        break;                // Rompemos la ejecucion del for para que el mando vuelva al do-while
                    }

                    // Si el numero no existe, el bucle for deja de recorrer el arreglo y
                    // continua el flujo normal con los siguientes condicionales
                }

                if (numero_existe) // si numero_existe = true
                {
                    numero_existe = false; // reinciamos la variable y la volvemos a false para la proxima iteracion
                    continue;              // saltamos a la siguiente iteracion del bucle do-while
                }

                else
                { // de lo contrario
                    /*
                        -Si ya comprobamos que el numero: Es un dato valido, No existe dentro del arreglo y Esta dentro del rango entonces el intento es valido,
                        podemos contabilizarlo, guardar el numero en el arreglo y continuar ejecutando el bucle
                    */
                    intentos_realizados++;
                    intentos_restantes--;
                    numeros_ingresados[indice] = posible_numero;
                    indice++;

                    // Si se encuentra dentro del rango establecido entonces se procede a evaluar si es mayor al numero secreto
                    if (posible_numero > numero_aleatorio)
                    {
                        cout << "El numero que ingresaste es mayor que el numero secreto" << endl;
                    }
                    else // Si se encuentra dentro del rango establecido y no es mayor al numero secreto entonces es menor asi que lo comunicamos por pantalla
                    {
                        cout << "El numero que ingresaste es menor que el numero secreto" << endl;
                    }
                }
            }
            /*
            En caso de que el numero no se encuentre dentro del rango establecido,
            se evalua si el numero ingresado esta por debajo del limite inferior o por encima del limite superior
            */
            else if (posible_numero < limite_inferior)
            {
                cout << "El numero que ingresaste no se encuentra dentro del rango establecido por que es inferior a " << limite_inferior << endl;
                continue; // Si el numero esta por debajo del limite inferior saltamos la ejecucion restante del bucle do while
            }
            else if (posible_numero > limite_superior)
            {
                cout << "El numero que ingresaste no se encuentra dentro del rango establecido por que es mayor a " << limite_superior << endl;
                continue; // Si el numero esta por encima del limite superior saltamos la ejecucion restante del bucle do while
            }
        }

        cout << "Intentos realizados: " << intentos_realizados << endl;
        cout << "Intentos restantes: " << intentos_restantes << endl;

    } while (intentos_restantes != 0);

    // Si el jugador/a se queda sin intentos se lo hacemos saber
    cout << "Intentos agotados. Suerte para la proxima" << endl;
    mostrarNumeros(numeros_ingresados,intentos_realizados);
    printMsgFin();
    return 0; // Finaliza la ejecucion del codigo
}
