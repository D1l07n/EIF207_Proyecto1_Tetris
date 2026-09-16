# Tetris - EIF207

Proyecto I del curso **Estructuras de Datos (EIF207)** — Universidad Nacional de Costa Rica, Sede Regional Brunca, Campus Coto.

**Autor:** Dylan Díaz Quintero

## Descripción

Una versión de Tetris hecha en C++ con SFML, usando estructura propia a mano sin librerías (Colas, Pilas, Listas Dobles y Simples).

Esta versión de Tetris posee tres eventos simples pero cumplidores:
- **Pieza dorada**: da +500 pts si y solo si al colocarse completa una línea.
- **Pieza bomba**: siempre al colocarse elimina todas las piezas de su mismo tipo.
- **Puntos dobles**: durante los próximos 30 segundos después de activarse el evento, cualquier línea que limpies vale el doble.

### Puntos por línea limpiada

| Líneas de una vez | Puntos |
|---|---|
| 1 | 100 |
| 2 | 300 |
| 3 | 500 |
| 4 | 800 |

### Cuándo se activa cada evento

| Evento | Primera vez | Se repite cada |
|---|---|---|
| Pieza dorada | 20s | 60s |
| Pieza bomba | 40s | 90s |
| Puntos dobles | 60s | 120s |

## Controles

### Menú principal
| Tecla / acción | Qué hace |
|---|---|
| `Enter` o click en "JUGAR" | Empieza una partida nueva |
| `T` o click en "PUNTAJES" | Ver la tabla de mejores puntajes |
| `Esc` o click en "SALIR" | Cierra el juego |
| `B` | Corre el benchmark de ordenamiento (resultados en la consola) |

### Durante la partida
| Tecla | Qué hace |
|---|---|
| `←` / `A` | Mover a la izquierda |
| `→` / `D` | Mover a la derecha |
| `↓` / `S` | Bajar más rápido (soft drop) |
| `↑` / `Q` | Rotar |
| `Espacio` | Caída instantánea (hard drop) |
| `C` | Hold (guardar/intercambiar la pieza actual) |
| `Z` | Deshacer el último movimiento |
| `X` | Rehacer |
| `P` | Pausar |
| `Esc` | Volver al menú (la partida no se guarda) |

### Pausa
| Tecla | Qué hace |
|---|---|
| `P` | Continuar |
| `Esc` | Volver al menú |

### Game Over
| Tecla | Qué hace |
|---|---|
| `R` | Ver la repetición completa de la partida |
| `Enter` | Volver al menú |

*(si tu puntaje entra en el top 10, antes de esto te va a pedir que escribas tu nombre — se escribe normal y se confirma con `Enter`)*

### Viendo la tabla de puntajes
| Tecla | Qué hace |
|---|---|
| `1` | Ordenar con Insertion Sort |
| `2` | Ordenar con Merge Sort |
| `Esc` | Volver al menú |

### Viendo la repetición (replay)
| Tecla | Qué hace |
|---|---|
| `Espacio` | Alternar entre reproducción automática y manual |
| `←` / `→` | Retroceder / avanzar un paso (solo en modo manual) |
| `Esc` | Volver al menú |

## Requisitos

- Visual Studio (Community o superior), con soporte de C++.
- SFML 2.6.1, descargada desde la página oficial (no vcpkg).

## Cómo compilar

1. Abrí `Tetris_EIF207.sln` en Visual Studio.
2. Compilá con `Ctrl+Shift+B`.
3. Corré con `F5` (o `Ctrl+F5`).

## Estructura del proyecto

- `config/` — constantes globales
- `core/` — toda la lógica del juego (piezas, cola, pila, tablero, colisión, replay, eventos, tabla de puntajes)
- `render/` — todo lo que se dibuja en pantalla
- `game/` — conecta la lógica con el dibujado y maneja los estados del juego
- `assets/` — sprites, fondos y fuente de texto

## Persistencia

Los mejores puntajes se guardan en `puntajes.txt`, junto al ejecutable — se cargan al iniciar y se actualizan cada vez que alguien entra al top 10.
