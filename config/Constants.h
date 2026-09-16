#pragma once
#include <string>


constexpr int CELL_SIDE_SIZE = 30;      
constexpr int BOARD_ROWS = 20;
constexpr int BOARD_COLS = 10;
constexpr int CELDA_VACIA = -1;  

constexpr int BOARD_WIDTH = BOARD_COLS * CELL_SIDE_SIZE;
constexpr int BOARD_HEIGHT = BOARD_ROWS * CELL_SIDE_SIZE;

constexpr int HUD_WIDTH = 230; 

constexpr int WINDOW_WIDTH = BOARD_WIDTH + HUD_WIDTH;
constexpr int WINDOW_HEIGHT = BOARD_HEIGHT;
const std::string WINDOW_TITLE = "Tetris - EIF207";

constexpr int FPS = 60;

constexpr float RETRASO_INICIAL_MOVIMIENTO = 0.2f;
constexpr float INTERVALO_MOVIMIENTO_LATERAL = 0.05f;
constexpr float INTERVALO_SOFT_DROP = 0.05f;
constexpr float FALL_INTERVAL_INITIAL = 1.0f; 
constexpr int MINIMO_EN_COLA = 7;

constexpr float TIEMPO_EVENTO_DORADA_INICIAL = 20.0f;
constexpr float TIEMPO_EVENTO_DORADA_REPETICION = 60.0f;
constexpr float TIEMPO_EVENTO_BOMBA_INICIAL = 40.0f;
constexpr float TIEMPO_EVENTO_BOMBA_REPETICION = 90.0f;
constexpr float TIEMPO_EVENTO_PUNTOS_DOBLES_INICIAL = 60.0f;
constexpr float TIEMPO_EVENTO_PUNTOS_DOBLES_REPETICION = 120.0f;
constexpr float DURACION_PUNTOS_DOBLES = 30.0f;
constexpr int PUNTOS_BONUS_DORADA = 500;

constexpr int HUD_MARGIN = 10;
constexpr int HUD_CELL_SIDE_SIZE = 18;
constexpr int HUD_FONT_SIZE = 16;

constexpr int PUNTOS_1_LINEA = 100;
constexpr int PUNTOS_2_LINEAS = 300;
constexpr int PUNTOS_3_LINEAS = 500;
constexpr int PUNTOS_4_LINEAS = 800;

constexpr int MAX_PUNTAJES_GUARDADOS = 10;
const std::string ARCHIVO_PUNTAJES = "puntajes.txt";
constexpr int MAX_LARGO_NOMBRE = 12;
constexpr float INTERVALO_REPRODUCCION_AUTO = 0.3f;
constexpr int TITULO_FONT_SIZE = 32;
constexpr int TEXTO_FONT_SIZE = 20;

constexpr float BOTON_CENTRO_X = 264.0f;
constexpr float BOTON_JUGAR_CENTRO_Y = 178.0f;
constexpr float BOTON_PUNTAJES_CENTRO_Y = 298.0f;
constexpr float BOTON_SALIR_CENTRO_Y = 418.0f;
constexpr float BOTON_ANCHO = 190.0f;
constexpr float BOTON_ALTO = 80.0f;

constexpr float RANKING_COL_POS_X = 45.0f;
constexpr float RANKING_COL_NOMBRE_X = 220.0f;
constexpr float RANKING_COL_PUNTAJE_X = 460.0f;
constexpr float RANKING_Y_HEADER = 22.0f;
constexpr float RANKING_Y_FILAS[10] = {
    93.0f, 161.0f, 214.0f, 265.0f, 318.0f,
    368.0f, 422.0f, 472.0f, 525.0f, 575.0f
};

constexpr float DURACION_ANIMACION_BOMBA = 0.5f;
constexpr float INTERVALO_PARPADEO_BOMBA = 0.1f;
