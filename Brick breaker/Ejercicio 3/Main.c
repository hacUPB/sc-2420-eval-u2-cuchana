#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>
#include <stdio.h> // Necesario para printf (para mostrar puntaje)

// Definimos la estructura de la bola
struct Ball {
    int x, y; // Posición de la bola
    int radius; // Radio de la bola
    int dx, dy; // Velocidad de la bola (dirección en los ejes x e y)
};

// Definimos la estructura de la paleta
struct Paddle {
    int x, y; // Posición de la paleta
    int width, height; // Tamaño de la paleta
    int speed; // Velocidad de movimiento
};

// Definimos los ladrillos
struct Brick {
    int x, y; // Posición del ladrillo
    int width, height; // Tamaño del ladrillo
    bool destroyed; // Indicador si el ladrillo fue destruido
};

// Declaramos las variables globales
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Inicializamos la bola
struct Ball ball = { 400, 300, 10, 3, -3 }; // Velocidad de la bola

// Inicializamos la paleta
struct Paddle paddle = { 350, 500, 100, 20, 15 }; // Velocidad de la paleta

// Inicializamos una matriz de ladrillos
struct Brick bricks[5][10];

// Inicialización de la ventana y el renderer
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

// Inicializamos SDL y la ventana
bool initialize_window() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("No se pudo inicializar SDL: %s\n", SDL_GetError());
        return false;
    }
    window = SDL_CreateWindow("Brick Breaker", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("No se pudo crear la ventana: %s\n", SDL_GetError());
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("No se pudo crear el renderer: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

// Variables para el puntaje
int score = 0;

// Función de actualización del movimiento de la bola
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
        *game_is_running = false; // Termina el juego si la bola cae por debajo de la pantalla
    }
}

// Movimiento de la paleta usando teclas
void move_paddle(int direction) {
    if (direction == SDLK_LEFT && paddle.x > 0) {
        paddle.x -= paddle.speed;
    }
    if (direction == SDLK_RIGHT && paddle.x < WINDOW_WIDTH - paddle.width) {
        paddle.x += paddle.speed;
    }
}

// Detectar colisión entre la bola y la paleta
void check_ball_paddle_collision() {
    if (ball.x + ball.radius >= paddle.x &&
        ball.x <= paddle.x + paddle.width &&
        ball.y + ball.radius >= paddle.y &&
        ball.y <= paddle.y + paddle.height) {
        ball.dy *= -1; // Invierte la dirección en el eje Y
    }
}

// Colisión con los ladrillos
void check_ball_brick_collision() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++) {
            struct Brick* brick = &bricks[i][j];
            if (!brick->destroyed &&
                ball.x + ball.radius >= brick->x &&
                ball.x <= brick->x + brick->width &&
                ball.y + ball.radius >= brick->y &&
                ball.y <= brick->y + brick->height) {
                brick->destroyed = true; // Destruye el ladrillo
                ball.dy *= -1; // Cambia la dirección de la bola
                score += 10; // Incrementa el puntaje
                printf("Puntaje: %d\n", score); // Muestra el puntaje en la consola
            }
        }
    }
}

// Renderizamos la bola, paleta y ladrillos
void render_game() {
    // Dibujar la bola
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Blanco
    SDL_Rect ball_rect = { ball.x, ball.y, ball.radius * 2, ball.radius * 2 };
    SDL_RenderFillRect(renderer, &ball_rect);

    // Dibujar la paleta
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Verde
    SDL_Rect paddle_rect = { paddle.x, paddle.y, paddle.width, paddle.height };
    SDL_RenderFillRect(renderer, &paddle_rect);
    // Dibujar los ladrillos con contorno
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++) {
            if (!bricks[i][j].destroyed) {
                // Dibujar el contorno blanco
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Blanco
                SDL_Rect brick_contour_rect = { bricks[i][j].x - 2, bricks[i][j].y - 2, bricks[i][j].width + 4, bricks[i][j].height + 4 };
                SDL_RenderFillRect(renderer, &brick_contour_rect);

                // Dibujar el ladrillo interior (rojo)
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rojo
                SDL_Rect brick_rect = { bricks[i][j].x, bricks[i][j].y, bricks[i][j].width, bricks[i][j].height };
                SDL_RenderFillRect(renderer, &brick_rect);
            }
        }
    }
}

// Procesar la entrada del usuario
void process_input(bool* game_is_running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            *game_is_running = false;
        }
        if (event.type == SDL_KEYDOWN) {
            move_paddle(event.key.keysym.sym);
        }
    }
}

// Función principal del juego
int main() {
    if (!initialize_window()) {
        return -1;
    }

    // Inicializamos los ladrillos
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++) {
            bricks[i][j].x = j * 80;
            bricks[i][j].y = i * 40;
            bricks[i][j].width = 80;
            bricks[i][j].height = 40;
            bricks[i][j].destroyed = false;
        }
    }

    bool game_is_running = true;
    while (game_is_running) {
        process_input(&game_is_running); // Procesa la entrada del jugador
        update_ball(&game_is_running); // Actualiza el movimiento de la bola
        check_ball_paddle_collision(); // Verifica colisiones con la paleta
        check_ball_brick_collision(); // Verifica colisiones con los ladrillos

        // Limpiar pantalla
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        render_game(); // Renderiza la bola, la paleta y los ladrillos

        // Actualizar pantalla
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // Esperar un pequeño intervalo de tiempo (~60 FPS)
    }

    // Limpiar recursos
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
