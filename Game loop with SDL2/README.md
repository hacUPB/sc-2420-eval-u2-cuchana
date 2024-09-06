# Unidad 2:
## Nombre completo: Luciana Gutierrez Posada
## ID: 000507574
# Actividad 1: 

## Ejercicio 1: Reconociendo las Partes del Game Loop
- Objetivo:

Entender las funciones principales de un Game Loop (`Setup()`, `Update()`, `Render()`) y cómo se integran en la función `main()`.

 - Instrucciones:

1. **Identificación de Funciones**:
    - Observa el código fuente y localiza las funciones `Setup()`, `Update()`, y `Render()`.
  
    ```c
    void setup(void) {
        // Initialize the ball object moving down at a constant velocity
        ball.x = 10;
        ball.y = 20;
        ball.width = 20;
        ball.height = 20;
        ball.vel_x = 180;
        ball.vel_y = 140;
    ```
    ```c
    void update(void) {
    // Get delta_time factor converted to seconds to be used to update objects
    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0;

    // Store the milliseconds of the current frame to be used in the next one
    last_frame_time = SDL_GetTicks();

    // Move ball as a function of delta time
    ball.x += ball.vel_x * delta_time;
    ball.y += ball.vel_y * delta_time;

    // Check for ball collision with the window borders
    if (ball.x < 0) {
        ball.x = 0;
        ball.vel_x = -ball.vel_x;
    }
    if (ball.x + ball.height > WINDOW_WIDTH) {
        ball.x = WINDOW_WIDTH - ball.width;
        ball.vel_x = -ball.vel_x;
    }
    if (ball.y < 0) {
        ball.y = 0;
        ball.vel_y = -ball.vel_y;
    }
    if (ball.y + ball.height > WINDOW_HEIGHT) {
        ball.y = WINDOW_HEIGHT - ball.height;
        ball.vel_y = -ball.vel_y;
    }
    ```
    ```c
    void render(void) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw a rectangle for the ball object
    SDL_Rect ball_rect = {
        (int)ball.x,
        (int)ball.y,
        (int)ball.width,
        (int)ball.height
    };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &ball_rect);

    SDL_RenderPresent(renderer);

    ```
    
    - Explica en tus palabras cuál es el propósito de cada una y cómo interactúan dentro del Game Loop.
    1. setup(): Se llama una vez al inicio del programa y se usa para inicializar el estado inicial de los objetod del juego, en este codigo es la pelota, que se llama ball, en esta funcion se establecieron las posiciones iniciales, tamaño y velocidad. La interaccion que tiene con el Game Loop es la preparacion del el juego antes de que entre al ciclo continuo entre update y render.
  
    2. update(): Esta funcion se llama en cada iteracion del Game Loop, lo que hace es actualizar la logica del juego, como la posicion de la pelota en funcion del tiempo y maneja las colisiones con los bordes de la ventana, esta funcion se ejectua constantemente dentro del Loop, despues de process_input() y antes de render(), manteniendo la dinamica del juego.
       
    3. render(): Se encarga de dibujar los elementos que forman el juego en la ventana de compilacion, se limpia la pantalla y despues se dibuja la pelota en la posicion que se indica en update, render() tambien se llama en cada iteracion del bucle, esta va despues de update puesto que muestra visualmente los cambios que sucedieron.

2. **Inserta un `printf()`**:
    - En cada una de las funciones (`Setup()`, `Update()`, `Render()`), inserta un `printf()` que imprima un mensaje cuando la función sea llamada.
    - Ejecuta el programa y observa en la consola cómo se llaman estas funciones continuamente.

   ![image](https://github.com/user-attachments/assets/411b6715-b3b6-4792-a051-07e542cc0440)

## Ejercicio 2: Calculando el Tiempo de Ejecución
- Objetivo:

Calcular el tiempo que transcurre entre cada llamada a las funciones `Update()` y `Render()` para entender la frecuencia de actualización del Game Loop.

- Instrucciones:

1. **Agregar Cronometrado**:
    - Utiliza la función `SDL_GetTicks()` para obtener el tiempo en milisegundos antes y después de cada llamada a `Update()` y `Render()`.
    - Calcula el tiempo transcurrido y muestra este valor en la consola.
      
      Muestra linea de codigo:
      
    ![image](https://github.com/user-attachments/assets/942a2980-5d36-437b-b028-9b4fe3a01faf)

      Consola:
    ![image](https://github.com/user-attachments/assets/496a8837-de75-4520-a5f1-ef2640103573)
      
2. **Analizar el Resultado**:
    - Ejecuta el programa durante unos segundos y anota los tiempos que se imprimen.
    - Discute cómo estos tiempos afectan la fluidez del juego y por qué es importante mantener una frecuencia de actualización constante.

    ![image](https://github.com/user-attachments/assets/7c185dbb-ff43-47ba-9d9a-d088121f9e8a)
    Al iniciar el programa los tiempos son entre 3, 0 y 1, tras dejarlo correr un rato suben a 7, 6, 14 y 32

![image](https://github.com/user-attachments/assets/00a3979e-5dc4-4675-b1c1-a8aec6a3701b)

En la imagen se puede ver como en update se alcanza un pico de 32ms lo cual le quito fluidez y genero un pequeño lag, por eso decidi para la ejecucion en ese punto para poder observar que ocurria, teniendo en cuenta la relacion de los tiempos de ejecucion y los fps, entendi la causa de esto. La importancia de una actualizacion constante se relaciona principalmente con la experiencia que tiene el usuario, por los lags, la fluidez del programa, en caso de tener inputs como teclado, mouse, control, estas funciones deben de mantener una frecuencia para lo geeneral delay en las acciones del usuario. 

## Ejercicio 3: Creación de Figuras Geométricas:

- Objetivo:

Crear figuras geométricas básicas (círculos, líneas, rectángulos) y entender cómo se renderizan en pantalla.

- Instrucciones:

1. **Dibuja Figuras**:
    - Utiliza las funciones de SDL para dibujar un círculo, una línea y un rectángulo en la pantalla dentro de la función `Render()`.
    - Asegúrate de que las figuras se dibujen en posiciones distintas y visibles.
![image](https://github.com/user-attachments/assets/5d11f806-a188-4cc0-8364-8c41004be306)
![image](https://github.com/user-attachments/assets/cd3adece-7815-40ff-9364-1737570e8d52)

2. **Colorear las Figuras**:
    - Modifica el código para que cada figura tenga un color diferente. Usa `SDL_SetRenderDrawColor()` antes de dibujar cada figura.
    ![image](https://github.com/user-attachments/assets/3e62badb-564a-4c9d-b513-8e02b808655f)
3. **Guardar y Compilar**:
    - Guarda los cambios y compila el programa. Observa las figuras en la pantalla y asegúrate de que se dibujen correctamente.
![image](https://github.com/user-attachments/assets/85c4f3c4-9b4e-4ea7-902e-ae9124c78920)

## Ejercicio 4: Movimiento de figuras en pantalla 
- Objetivo:

Hacer que las figuras geométricas se muevan a través de la pantalla.

- Instrucciones:

1. **Actualizar Posiciones**:
    - Modifica la función `Update()` para que las posiciones de las figuras cambien ligeramente en cada ciclo del Game Loop.
    - Implementa un desplazamiento lineal en una dirección específica (e.g., hacia la derecha).
   
   Primero declare las posiciones iniciales de las figuras que seran a las que le reste -1 para lograr que se muevan a la izquierda

![image](https://github.com/user-attachments/assets/07d6a383-53ee-40b7-946e-1066b53d3552)

Luego en Update llame las posiciones en x y les reste 1

![image](https://github.com/user-attachments/assets/5f707d38-ed5b-489b-bd9f-e60517d1a8f5)

En render reemplaze los numeros por la variables que van a estarse actualizando


2. **Ejecutar y Observar**:
    - Ejecuta el programa y observa cómo las figuras se mueven en la pantalla. Anota cualquier problema que ocurra, como si las figuras desaparecen de la pantalla.
      Logré que se movieran pero al ser un moviento a la izquierda ilimitado salen de la pantalla y no vuelven a aparecer, por lo cual arregle el update con condicionales, cuando x=0 deja de moverse
      ![image](https://github.com/user-attachments/assets/2c73bef3-26aa-49ac-9310-4710839e3d96)
      ![image](https://github.com/user-attachments/assets/8de02e8a-a099-4a3c-a6c1-181d64fd0abf)

## Ejercicio 5: Modificación de Tamaño, Orientación y Color

- Objetivo:

Hacer que las figuras cambien de tamaño, orientación, y color durante la ejecución del programa.

- Instrucciones:

1. **Cambio de Tamaño**:
    - Modifica el código para que el tamaño de las figuras aumente o disminuya con cada ciclo del Game Loop.
 Para hacer esto declare unas variables para el resto de medidas, como lo hice para la posicion, agregue variables para la escala en Y y el radio (las cuales reemplace en render) y una variable para el cambio de tamaño, la razon por la 
 que no le sume 1 directamente, si no que cree una variable es porque en update agregue dos momentos, en el que crece hasta cierto tamaño y luego decrece para que no se salga de la pantalla ni se sobrepongan. En update hay dos bucles, de crecimiento y disminucion.

 ![image](https://github.com/user-attachments/assets/aca5ae4b-8d76-4e61-8467-d38ba8bb7296) ![image](https://github.com/user-attachments/assets/72418b8d-a9d1-4a3a-9c0a-009d56a91f7f)

      
2. **Cambio de Orientación**:
    - Implementa un giro de las figuras. Por ejemplo, rota un rectángulo o cambia la dirección de una línea.
      
3. **Cambio de Color**:
    - Programa un ciclo de colores para las figuras, haciendo que cambien de color en intervalos regulares.
4. **Observar Cambios**:
    - Compila y ejecuta el programa. Observa cómo los cambios afectan la visualización de las figuras y cómo interactúan con el Game Loop.
      






   
   

