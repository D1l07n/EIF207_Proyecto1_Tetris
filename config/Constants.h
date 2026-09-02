#pragma once
#include <string>

// --- Ventana ---
constexpr int CELL_SIDE_SIZE = 30;      // pixeles por celda del tablero
constexpr int BOARD_ROWS = 20;
constexpr int BOARD_COLS = 10;

constexpr int BOARD_WIDTH = BOARD_COLS * CELL_SIDE_SIZE;
constexpr int BOARD_HEIGHT = BOARD_ROWS * CELL_SIDE_SIZE;

constexpr int HUD_WIDTH = 200; // espacio para cola de piezas, hold y puntaje

constexpr int WINDOW_WIDTH = BOARD_WIDTH + HUD_WIDTH;
constexpr int WINDOW_HEIGHT = BOARD_HEIGHT;
const std::string WINDOW_TITLE = "Tetris - EIF207";

constexpr int FPS = 60;

// --- Juego ---
constexpr float FALL_INTERVAL_INITIAL = 1.0f; // segundos entre cada caida de fila
