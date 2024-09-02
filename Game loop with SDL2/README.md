# Unidad 2:
## Nombre completo: Luciana Gutierrez Posada
## ID: 000507574

# Ejercicio 1: 
## Objetivo:

Entender las funciones principales de un Game Loop (`Setup()`, `Update()`, `Render()`) y cómo se integran en la función `main()`.

## Instrucciones:

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
      1. update()
      2. 


2. **Inserta un `printf()`**:
    - En cada una de las funciones (`Setup()`, `Update()`, `Render()`), inserta un `printf()` que imprima un mensaje cuando la función sea llamada.
    - Ejecuta el programa y observa en la consola cómo se llaman estas funciones continuamente.
