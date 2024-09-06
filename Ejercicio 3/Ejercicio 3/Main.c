#include <stdio.h>
#include <stdbool.h>


#include <SDL.h>
#include "./constants.h"

// Variables globales
int game_is_running = false;
int last_frame_time = 0;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
// Posiciones iniciales de las figuras
int rect_x = 300;
int rect_y = 150;
int line_x1 = 150;
int line_y1 = 50;
int line_x2 = 150;
int line_y2 = 400;
int circle_x = 500;
int circle_y = 300;

// Function to initialize our SDL window (la copie de el codigo fuente)

int initialize_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
    }
    window = SDL_CreateWindow(
        "A simple game loop using C & SDL",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0
    );
    if (!window) {
        fprintf(stderr, "Error creating SDL Window.\n");
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "Error creating SDL Renderer.\n");
        return false;
    }
    return true;
}

// Function to poll SDL events and process keyboard input (tambien la copie)

void process_input(void) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            game_is_running = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                game_is_running = false;
            }
            break;
        }
    }
}


// Setup() la funcion que llamamos la primera vez al correr el programa

void setup(void) {
    // Quite la bola
}


// Update function with a fixed time step

void update(void) {

    if (rect_x > 0) {
        rect_x -= 1;
    }
    if (line_x1 > 0) {
        line_x1 -= 1;
        line_x2 -= 1;
    }
    if (circle_x - 50 > 0) {  // Restamos el radio del círculo para limitar correctamente
        circle_x -= 1;
    }
}



// Funcion para renderizar un circulo

void render_circle(int x_center, int y_center, int radius) {
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, x_center + dx, y_center + dy);
            }
        }
    }
}

// Render function to draw the shapes
void render(void) {
    // Limpiar la pantalla con color negro
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Dibujar un rectángulo rojo
    SDL_Rect red_rect = { rect_x, rect_y, 100, 50 }; // Posición y tamaño actualizados
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rojo
    SDL_RenderFillRect(renderer, &red_rect);

    // Dibujar una línea verde
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Verde
    SDL_RenderDrawLine(renderer, line_x1, line_y1, line_x2, line_y2); // Línea con posiciones actualizadas

    // Dibujar un círculo azul
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Azul
    render_circle(circle_x, circle_y, 50); // Llamar la función del círculo con posición actualizada

    // Presentar la renderización
    SDL_RenderPresent(renderer);
}


// Function to destroy SDL window and renderer

void destroy_window(void) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


// Main function

int main(int argc, char* args[]) {
    game_is_running = initialize_window();

    setup();

    while (game_is_running) {
        process_input();
        update();
        render();
    }

    destroy_window();

    return 0;
}
