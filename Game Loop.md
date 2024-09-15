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
      
      Primero declare el angulo y la velocidad de rotacion
      ```c
      // Ángulo de rotación (en radianes)
       float rotation_angle = 0.0f;
      float rotation_speed = 0.05f;
      ```


      Luego con seno y coseno cree una funcion para poder rotar cualquier recta respecto a su centro (chat gpt me la corrigio)
      ```c
      void rotate_point(int* px, int* py, int cx, int cy, float angle) {
      float radians = angle * M_PI / 180.0;
      float cos_angle = cos(radians);
      float sin_angle = sin(radians);
      int x_new = cos_angle * (*px - cx) - sin_angle * (*py - cy) + cx;
      int y_new = sin_angle * (*px - cx) + cos_angle * (*py - cy) + cy;
      *px = x_new;
      *py = y_new;
      }
      ```
      Agregue una linea en update donde el valor del angulo se suma a si mismo con la velocidad de rotacion, despues cree las funciones que se encargan de rotar y renderizar la linea y el rectangulo relleno, honestamente no entendi bien la parte del rectangulo, chat me ayudo a que estuviera relleno e hizo muchos for pero le pedi que me explicara y desgloso el codigo
      ```c
      // Render function to draw the rotated rectangle

      void render_filled_rotated_rectangle(int x, int y, int width, int height, float angle) {
          int cx = x + width / 2;
          int cy = y + height / 2;
      
          SDL_Point points[4] = {
              {x, y},
              {x + width, y},
              {x + width, y + height},
              {x, y + height}
          };
      
          for (int i = 0; i < 4; i++) {
              rotate_point(&points[i].x, &points[i].y, cx, cy, angle);
          }
      
          int min_y = points[0].y;
          int max_y = points[0].y;
          for (int i = 1; i < 4; i++) {
              if (points[i].y < min_y) min_y = points[i].y;
              if (points[i].y > max_y) max_y = points[i].y;
          }
      
          for (int y = min_y; y <= max_y; y++) {
              int min_x = points[0].x;
              int max_x = points[0].x;
              for (int i = 1; i < 4; i++) {
                  if (points[i].y == y) {
                      if (points[i].x < min_x) min_x = points[i].x;
                      if (points[i].x > max_x) max_x = points[i].x;
                  }
                  else {
                      int prev = (i == 0) ? 3 : i - 1;
                      if ((points[i].y <= y && points[prev].y >= y) || (points[i].y >= y && points[prev].y <= y)) {
                          int cross_x = points[i].x + (y - points[i].y) * (points[prev].x - points[i].x) / (points[prev].y - points[i].y);
                          if (cross_x < min_x) min_x = cross_x;
                          if (cross_x > max_x) max_x = cross_x;
                      }
                  }
              }
              SDL_RenderDrawLine(renderer, min_x, y, max_x, y);
          }
      }
      
      
      // Render function to draw the rotated line
      void render_rotated_line(int x1, int y1, int x2, int y2, float angle) {
          int cx = (x1 + x2) / 2;
          int cy = (y1 + y2) / 2;
      
          rotate_point(&x1, &y1, cx, cy, angle);
          rotate_point(&x2, &y2, cx, cy, angle);
      
          SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
      }

      ```
3. **Cambio de Color**:
    - Programa un ciclo de colores para las figuras, haciendo que cambien de color en intervalos regulares.
      Primero estableci variables con el cambio de color
      ```c
      // Variables para el cambio de color
      int color_step = 0;
      int color_recta[3] = { 255, 0, 0 };
      int color_linea [3] = { 0, 255, 0 };
      int color_circulo [3] = { 0, 0, 255 };

      ```
      Luego en update un ciclo de cambio de colores
      ```c
      // Ciclo de colores
      color_step = (color_step + 1) % 255;
      color_recta[0] = (color_recta[0] + 1) % 256;
      color_recta[1] = (color_recta[1] + 2) % 256;
      color_recta[2] = (color_recta[2] + 3) % 256;
      
      color_linea[0] = (color_linea[0] + 3) % 256;
      color_linea[1] = (color_linea[1] + 2) % 256;
      color_linea[2] = (color_linea[2] + 1) % 256;
      
      color_circulo[0] = (color_circulo[0] + 2) % 256;
      color_circulo[1] = (color_circulo[1] + 1) % 256;
      color_circulo[2] = (color_circulo[2] + 3) % 256;
      ```
      Y en render reemplace los valores de SDL_SetRenderColor por los del ciclo de update.
     
4. **Observar Cambios**:
    - Compila y ejecuta el programa. Observa cómo los cambios afectan la visualización de las figuras y cómo interactúan con el Game Loop.
      
      ![image](https://github.com/user-attachments/assets/d22c90a3-9668-4660-834b-05b524eab75f)
      
      El rectangulo sigue raro pero la intencion es lo que cuenta

      
## Ejercicio 6: Rebote de figuras
- Objetivo:

Hacer que las figuras geométricas reboten contra las paredes de la pantalla y/o entre ellas.

- Instrucciones:

1. **Implementar Rebote Contra Paredes**:
    - En la función `Update()`, agrega condiciones que inviertan la dirección de movimiento de las figuras cuando colisionen con los bordes de la pantalla.
    
    Creo las variables de velocidad de movimiento
    ```c
    // Velocidades de movimiento para las figuras
    int recta_vel_x = 2;
    int recta_vel_y = 2;
    int linea_vel_x = 1;
    int linea_vel_y = 1;
    int circulo_vel_x = 3;
    int circulo_vel_y = 3;
    ```
    Luego un bool para las colisiones del rectangulo y otro para las del circulo
    ```c
    bool check_collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
    return x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2;
    }
    bool check_circle_rect_collision(int cx, int cy, int radius, int rx, int ry, int rw, int rh) {
    int closest_x = (cx < rx) ? rx : (cx > rx + rw) ? rx + rw : cx;
    int closest_y = (cy < ry) ? ry : (cy > ry + rh) ? ry + rh : cy;
    int distance_x = cx - closest_x;
    int distance_y = cy - closest_y;
    return (distance_x * distance_x + distance_y * distance_y) < (radius * radius);
    }
    ```
    Todo esto va antes de update(), dentro de la funcion escribi estas lineas, donde revisa si ocurre la colision, y si pasa invierte las direcciones de movimiento de x o y respectivamente
    ```c
     // Comprobar colisión del rectángulo con las paredes
    if (recta_x <= 0 || recta_x + rect_width >= WINDOW_WIDTH) {
        recta_vel_x *= -1;  // Invertir dirección en el eje X
    }
    if (recta_y <= 0 || recta_y + rect_height >= WINDOW_HEIGHT) {
        recta_vel_y *= -1;  // Invertir dirección en el eje Y
    }

    // Comprobar colisión del círculo con las paredes
    if (circulo_x - circle_radius <= 0 || circulo_x + circle_radius >= WINDOW_WIDTH) {
        circulo_vel_x *= -1;
    }
    if (circulo_y - circle_radius <= 0 || circulo_y + circle_radius >= WINDOW_HEIGHT) {
        circulo_vel_y *= -1;
    }
    ```



2. **Rebote Entre Figuras**:
    - Implementa la detección de colisiones entre figuras. Si dos figuras colisionan, invierte sus direcciones de movimiento.

    Para hacer esto creamos dentro de update() el primero
    ```c
     // Colisión entre rectángulo y círculo
    if (check_circle_rect_collision(circulo_x, circulo_y, circle_radius, recta_x, recta_y, rect_width, rect_height)) {
     recta_vel_x *= -1;
     recta_vel_y *= -1;
     circulo_vel_x *= -1;
     circulo_vel_y *= -1;
    }

    // Colisión entre rectángulo y línea
    if (check_collision(recta_x, recta_y, rect_width, rect_height, linea_x1, linea_y1, linea_x2 - linea_x1, 1)) {
     recta_vel_x *= -1;
     recta_vel_y *= -1;
     linea_vel_x *= -1;
     linea_vel_y *= -1;
    }

    // Colisión entre círculo y línea
    if (check_collision(circulo_x - circle_radius, circulo_y - circle_radius, circle_radius * 2, circle_radius * 2, linea_x1, linea_y1, linea_x2 - linea_x1, 1)) {
     circulo_vel_x *= -1;
     circulo_vel_y *= -1;
     linea_vel_x *= -1;
     linea_vel_y *= -1;
    }
    ```

3. **Prueba y Ajuste**:
    - Ejecuta el programa y ajusta las velocidades o direcciones según sea necesario para observar un rebote realista.


## Aplicacion de las actividades 1 y 2: Juego inspirado en brick breaker

Me inspire de brick breaker para hacer el mini juego, para lograrlo use de referencia el codigo fuente de la actividad uno y los ejercicios de ambas actividades, me apoye en chat gpt para los conceptos que no entendia y temas de estructura.

Primero hay que entender lo que debemos hacer, los componentes de este juego son una pelota que se mueve por toda la pantalla y rebota por los laterales de la ventana y la barrita, la barrita que es la cual el jugador va a controlar con la cual va a evitar que la pelota toque el piso (si eso pasa se acaba el juego), los ladrillos van a ser quienes den puntaje, se destruiran cuando la pelota les pegue, para el puntaje hare un contador que aumente de 10 en 10 por cada ladrillo destruido, esto lo mostrare en la consola. 

1. Definir las estructuras/game objects de la pelota, barra y ladrillo 

```c
struct Ball {
    int x, y; // Posición de la bola
    int radius; // Tamaño de la bola, es un cuadrado entonces usamos una sola variable
    int dx, dy; // Dirección en los ejes X y Y
};

// Definimos la estructura de la paleta
struct Paddle {
    int x, y; // Posición de la paleta
    int width, height; // Tamaño de la paleta, rectangulo
    int speed; // Velocidad de movimiento
};

// Definimos los ladrillos
struct Brick {
    int x, y; // Posición del ladrillo
    int width, height; // Tamaño del ladrillo, rectangulo
    bool destroyed; // Indicador si el ladrillo fue destruido
};

```
Todas las variables que definimos acá sol las que usaremos a lo largo del codigo.

2. Inicializacion del juego

Al ya haber definido las variables debemos de darle un valor, para las operaciones y funciones que usaremos mas adelante
```c 
// Inicializamos la bola
struct Ball ball = {400, 300, 10, 5, -5}; // Posición inicial en (400, 300) y velocidad (5, -5)

// Inicializamos la paleta
struct Paddle paddle = {350, 500, 100, 20, 10}; // Posición inicial y tamaño de la barrita

// Inicializamos una matriz de ladrillos
struct Brick bricks[5][10]; // 5 filas, 10 columnas
for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 10; j++) {
        bricks[i][j].x = j * 80;
        bricks[i][j].y = i * 40;
        bricks[i][j].width = 80;
        bricks[i][j].height = 40;
        bricks[i][j].destroyed = false; // Aqui no ha colisionado entonces le damos el valor de false
    }
}

```
3. Movimiento de la bola

La bola estara moviendose constantemente, debemos de tener colisiones controladas con los limites de la pantalla y la barrita, si toca la parte inferior de la pantalla el juego termina.
```c
// Función de actualización del movimiento de la bola, creamos un update especifico
void update_ball(bool* game_is_running) {
    ball.x += ball.dx;
    ball.y += ball.dy;

    // Colisión con los bordes de la pantalla
    if (ball.x <= 0 || ball.x >= WINDOW_WIDTH - ball.radius * 2) {
        ball.dx *= -1; // Cambia la dirección en el eje X
    }
    if (ball.y <= 0) {
        ball.dy *= -1; // Cambia la dirección en el eje Y (parte superior)
    }
    if (ball.y >= WINDOW_HEIGHT - ball.radius * 2) {
    printf("¡La bola cayo! Fin del juego.\n");
    *game_is_running = false; // Termina el juego si la bola cae 
    }
}
```
4. Movimiento de la barrita
Esta es controlada por el jugador al usar la flecha de izquierda y derecha, creamos una funcion con un int de direccion (flecha) y limitamos el movimiento para que no salga de la pantalla
```c
// Movimiento de la paleta usando teclas
void move_paddle(int direction) {
    if (direction == SDLK_LEFT && paddle.x > 0) {
        paddle.x -= paddle.speed;
    }
    if (direction == SDLK_RIGHT && paddle.x < WINDOW_WIDTH - paddle.width) {
        paddle.x += paddle.speed;
    }
}
```
5. Colisiones entre la bola y la barrita
La bola debe de invertir en Y su direccion al tocar la barra, por lo cual creamos una funcion que detecte la colision

```c
// Detectar colisión entre la bola y la paleta
void check_ball_paddle_collision() {
    if (ball.x + ball.radius >= paddle.x &&
        ball.x <= paddle.x + paddle.width &&
        ball.y + ball.radius >= paddle.y &&
        ball.y <= paddle.y + paddle.height) {
        ball.dy *= -1; // Invierte la dirección en el eje Y
    }
}
```
6. Colision de la bola y los ladrillos
Esta funcion tiene dos acciones, la destruccion del ladrillo y el cambio de direccion de la bola, para detectar esta colision usamos el radio de la bola
Chat me ayudo con esta parte y uso el operador logico && qie evalua varias condiciones al mismo tiempo y se asegura de que todas sean verdaderas
```c
// Colisión con los ladrillos
void check_ball_brick_collision() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++) {
            struct Brick *brick = &bricks[i][j];
            if (!brick->destroyed &&
                ball.x + ball.radius >= brick->x &&// Verifica colision con el lado izquierdo
                ball.x <= brick->x + brick->width &&//Verifica si el borde de la bola esta antes o en el lado derecho del ladrillo
                ball.y + ball.radius >= brick->y &&//Verifica si colisiono con la parte superior del ladrillo
                ball.y <= brick->y + brick->height) //Verifica si el borde de la bola esta antes o en la parte inferior 
                {
                brick->destroyed = true; // Destruye el ladrillo
                ball.dy *= -1; // Cambia la dirección de la bola
            }
        }
    }
}
```
El for recorre todos los ladrillos y verifica si la pelota colisiono con uno que no haya sido destruido, si hay colision la variable bool destroyed se marca true

7. Render del juego
Dibuja la bola, barrita y todos los ladrillos sin destruir.
```c
void render_game() {
    render_circle(ball.x, ball.y, ball.radius);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Rect paddle_rect = {paddle.x, paddle.y, paddle.width, paddle.height};
    SDL_RenderFillRect(renderer, &paddle_rect);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++) {
            if (!bricks[i][j].destroyed) {
                SDL_Rect brick_rect = {bricks[i][j].x, bricks[i][j].y, bricks[i][j].width, bricks[i][j].height};
                SDL_RenderFillRect(renderer, &brick_rect);
            }
        }
    }
}

```
8. Entrada del usuario
Ahora el juego espera la entrada del usuario, sea para salir o mover la barrita, usamos SDL_KEYDOWN (Evento cuando se presiona una tecla,detecta la tecla y realiza su funcion dada) y SDL_PollEvent (Funcion que maneja eventos en un ciclo de eventos, como las entradas)
```c
void process_input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) { //evento al cerrar la ventana de juego
            game_is_running = false;
        }
        if (event.type == SDL_KEYDOWN) {
            move_paddle(event.key.keysym.sym);
        }
    }
}
```
9. Bucle principal del juego
Primero procesamos la entrada, se actualiza la posicion de la bola, revisamos colisiones, se actualiza el render y esperamos 16ms 
```c
void game_loop() {
    while (game_is_running) {
        process_input();
        update_ball();
        check_ball_paddle_collision();
        check_ball_brick_collision();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        render_game();
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
}
```





   
   

