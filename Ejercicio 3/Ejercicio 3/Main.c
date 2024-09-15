#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <math.h>
#include "./constants.h"
// Variables globales
int game_is_running = false;
int last_frame_time = 0;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

// Posiciones iniciales de las figuras
int recta_x = 300;
int recta_y = 150;
int linea_x1 = 150;
int linea_y1 = 50;
int linea_x2 = 150;
int linea_y2 = 400;
int circulo_x = 500;
int circulo_y = 300;

// Tamaños iniciales de las figuras
int rect_width = 100;
int rect_height = 50;
int line_length = 350;
int circle_radius = 50;

// Variables para controlar el crecimiento o reducción de las figuras
int escala_rectangulo = 1;
int escala_linea = 1;
int escala_circulo = 1;

// Ángulo de rotación (en radianes)
float rotation_angle = 0.0f;
float rotation_speed = 0.05f;

// Variables para el cambio de color
int color_step = 0;
int color_recta[3] = { 255, 0, 0 };
int color_linea[3] = { 0, 255, 0 };
int color_circulo[3] = { 0, 0, 255 };

// Velocidades de movimiento para las figuras
int recta_vel_x = 2;
int recta_vel_y = 2;
int linea_vel_x = 1;
int linea_vel_y = 1;
int circulo_vel_x = 3;
int circulo_vel_y = 3;



// Function to initialize our SDL window
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

// Function to poll SDL events and process keyboard input
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

// Setup function called once at the start
void setup(void) {
    // Inicialmente no hay nada que configurar
}

// Funcion para rotar un punto respecto a un centro
void rotate_point(int* px, int* py, int cx, int cy, float angle) {
    float radians = angle * M_PI / 180.0;
    float cos_angle = cos(radians);
    float sin_angle = sin(radians);
    int x_new = cos_angle * (*px - cx) - sin_angle * (*py - cy) + cx;
    int y_new = sin_angle * (*px - cx) + cos_angle * (*py - cy) + cy;
    *px = x_new;
    *py = y_new;
}
// Detectar colisión entre dos rectángulos
bool check_collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
    return x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2;
}

// Detectar colisión entre un rectángulo y un círculo
bool check_circle_rect_collision(int cx, int cy, int radius, int rx, int ry, int rw, int rh) {
    int closest_x = (cx < rx) ? rx : (cx > rx + rw) ? rx + rw : cx;
    int closest_y = (cy < ry) ? ry : (cy > ry + rh) ? ry + rh : cy;
    int distance_x = cx - closest_x;
    int distance_y = cy - closest_y;
    return (distance_x * distance_x + distance_y * distance_y) < (radius * radius);
}



void update(void)
{
    // Mover el rectángulo
    recta_x += recta_vel_x;
    recta_y += recta_vel_y;

    // Mover la línea
    linea_x1 += linea_vel_x;
    linea_x2 += linea_vel_x;
    linea_y1 += linea_vel_y;
    linea_y2 += linea_vel_y;

    // Mover el círculo
    circulo_x += circulo_vel_x;
    circulo_y += circulo_vel_y;

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

        // Cambiar los tamaños de las figuras
        rect_width += escala_rectangulo;
        rect_height += escala_rectangulo;
        line_length += escala_linea;
        circle_radius += escala_circulo;

        // Invertir dirección si los tamaños salen de los límites
        if (rect_width >= 150 || rect_width <= 50) {
            escala_rectangulo *= -1;
        }
        if (line_length >= 400 || line_length <= 200) {
            escala_linea *= -1;
        }
        if (circle_radius >= 75 || circle_radius <= 25) {
            escala_circulo *= -1;
        }

        // Actualizar la posición final de la línea según su longitud
        linea_y2 = linea_y1 + line_length;

        // Incrementar el ángulo de rotación
        rotation_angle += rotation_speed;

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
    

}

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
// Function to render a circle
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

    // Dibujar un rectángulo 
   
    SDL_SetRenderDrawColor(renderer, color_recta[0], color_recta[1], color_recta[2], 255);
    render_filled_rotated_rectangle(recta_x, recta_y, rect_width, rect_height, rotation_angle);



    // Dibujar una línea 
    
    SDL_SetRenderDrawColor(renderer, color_linea[0], color_linea[1], color_linea[2], 255); // Color ciclado
    render_rotated_line(linea_x1, linea_y1, linea_x2, linea_y2, rotation_angle);

    // Dibujar un círculo azul
    SDL_SetRenderDrawColor(renderer, color_circulo[0], color_circulo[1], color_circulo[2], 255); // Color ciclado
    render_circle(circulo_x, circulo_y, circle_radius); // Llamar la función del círculo con posición actualizada

    // Presentar la renderización
    SDL_RenderPresent(renderer);
}

// Function to destroy SDL window and renderer
void destroy_window(void)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// Main function
int main(int argc, char* args[])
{
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


