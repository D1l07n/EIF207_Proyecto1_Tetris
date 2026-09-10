#pragma once
#include <string>


constexpr int CELL_SIDE_SIZE = 30;      // pixeles por celda del tablero
constexpr int BOARD_ROWS = 20;
constexpr int BOARD_COLS = 10;
constexpr int CELDA_VACIA = -1;  //celda tablero libre

constexpr int BOARD_WIDTH = BOARD_COLS * CELL_SIDE_SIZE;
constexpr int BOARD_HEIGHT = BOARD_ROWS * CELL_SIDE_SIZE;

constexpr int HUD_WIDTH = 200; // espacio para cola de piezas, hold y puntaje

constexpr int WINDOW_WIDTH = BOARD_WIDTH + HUD_WIDTH;
constexpr int WINDOW_HEIGHT = BOARD_HEIGHT;
const std::string WINDOW_TITLE = "Tetris - EIF207";

constexpr int FPS = 60;

constexpr float RETRASO_INICIAL_MOVIMIENTO = 0.2f;
constexpr float INTERVALO_MOVIMIENTO_LATERAL = 0.05f;
constexpr float INTERVALO_SOFT_DROP = 0.05f;

constexpr float FALL_INTERVAL_INITIAL = 1.0f; // segundos entre cada caida de fila
