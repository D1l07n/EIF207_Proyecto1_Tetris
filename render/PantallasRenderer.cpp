#include "PantallasRenderer.h"
#include "../config/Constants.h"

void PantallasRenderer::dibujarTexto(sf::RenderWindow& ventana, const sf::Font& fuente, const std::string& texto,
    float x, float y, int tamanio, sf::Color color) const {
    sf::Text textoSf;

    textoSf.setFont(fuente);
    textoSf.setString(texto);
    textoSf.setCharacterSize(tamanio);
    textoSf.setFillColor(color);
    textoSf.setPosition(x, y);
    ventana.draw(textoSf);
}

void PantallasRenderer::dibujarTextoCentrado(sf::RenderWindow& ventana, const sf::Font& fuente, const std::string& texto,
    float centroX, float centroY, int tamanio, sf::Color color) const {
    
    sf::Text textoSf;
    textoSf.setFont(fuente);
    textoSf.setString(texto);
    textoSf.setCharacterSize(tamanio);
    textoSf.setFillColor(color);

    sf::FloatRect bounds = textoSf.getLocalBounds();
    textoSf.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    textoSf.setPosition(centroX, centroY);

    ventana.draw(textoSf);
}

void PantallasRenderer::dibujarFondoOscuro(sf::RenderWindow& ventana, int alpha) const {
   
    sf::RectangleShape fondo(sf::Vector2f(static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT)));
    fondo.setFillColor(sf::Color(0, 0, 0, alpha));
    ventana.draw(fondo);
}

void PantallasRenderer::dibujarMenu(sf::RenderWindow& ventana, const sf::Font& fuente, const GestorTexturas& texturas) const {

    const sf::Texture& texturaFondo = texturas.obtenerTexturaMenu();
    sf::Sprite fondo;
    fondo.setTexture(texturaFondo);
    sf::Vector2u tam = texturaFondo.getSize();
    fondo.setScale(static_cast<float>(WINDOW_WIDTH) / tam.x, static_cast<float>(WINDOW_HEIGHT) / tam.y);
    ventana.draw(fondo);

    dibujarTextoCentrado(ventana, fuente, "TETRIS", WINDOW_WIDTH / 2.0f, 40.0f, TITULO_FONT_SIZE, sf::Color::White);
    dibujarTextoCentrado(ventana, fuente, "JUGAR", BOTON_CENTRO_X, BOTON_JUGAR_CENTRO_Y, TEXTO_FONT_SIZE);
    dibujarTextoCentrado(ventana, fuente, "PUNTAJES", BOTON_CENTRO_X, BOTON_PUNTAJES_CENTRO_Y, TEXTO_FONT_SIZE);
    dibujarTextoCentrado(ventana, fuente, "SALIR", BOTON_CENTRO_X, BOTON_SALIR_CENTRO_Y, TEXTO_FONT_SIZE);
}

void PantallasRenderer::dibujarPausa(sf::RenderWindow& ventana, const sf::Font& fuente) const {

    dibujarFondoOscuro(ventana, 180);
    dibujarTexto(ventana, fuente, "PAUSA", 90, 250, TITULO_FONT_SIZE);
    dibujarTexto(ventana, fuente, "P - Continuar", 60, 320, TEXTO_FONT_SIZE);
}

void PantallasRenderer::dibujarGameOver(sf::RenderWindow& ventana, const sf::Font& fuente, int puntajeFinal) const {

    dibujarFondoOscuro(ventana, 255);
    dibujarTexto(ventana, fuente, "GAME OVER", 40, 80, TITULO_FONT_SIZE);
    dibujarTexto(ventana, fuente, "Puntaje: " + std::to_string(puntajeFinal), 60, 160, TEXTO_FONT_SIZE);
    dibujarTexto(ventana, fuente, "R - Ver repeticion", 60, 220, TEXTO_FONT_SIZE);
    dibujarTexto(ventana, fuente, "ENTER - Volver al menu", 60, 260, TEXTO_FONT_SIZE);
}

void PantallasRenderer::dibujarIngresoNombre(sf::RenderWindow& ventana, const sf::Font& fuente, const std::string& nombreActual) const {

    dibujarFondoOscuro(ventana, 255);
    dibujarTexto(ventana, fuente, "NUEVO RECORD!", 40, 80, TITULO_FONT_SIZE, sf::Color::Yellow);
    dibujarTexto(ventana, fuente, "Escriba su nombre:", 60, 180, TEXTO_FONT_SIZE);
    dibujarTexto(ventana, fuente, nombreActual + "_", 60, 220, TEXTO_FONT_SIZE, sf::Color::Cyan);
    dibujarTexto(ventana, fuente, "ENTER - Confirmar", 60, 280, TEXTO_FONT_SIZE);
}

void PantallasRenderer::dibujarTablaPuntajes(sf::RenderWindow& ventana, const sf::Font& fuente, const TablaPuntajes& tabla, const GestorTexturas& texturas, const std::string& algoritmoActual) const {

    const sf::Texture& texturaFondo = texturas.obtenerTexturaRanking();
    sf::Sprite fondo;
    fondo.setTexture(texturaFondo);
    sf::Vector2u tam = texturaFondo.getSize();
    fondo.setScale(static_cast<float>(WINDOW_WIDTH) / tam.x, static_cast<float>(WINDOW_HEIGHT) / tam.y);
    ventana.draw(fondo);

    dibujarTextoCentrado(ventana, fuente, "POS", RANKING_COL_POS_X, RANKING_Y_HEADER, TEXTO_FONT_SIZE);
    dibujarTextoCentrado(ventana, fuente, "JUGADOR", RANKING_COL_NOMBRE_X, RANKING_Y_HEADER, TEXTO_FONT_SIZE);
    dibujarTextoCentrado(ventana, fuente, "PTS", RANKING_COL_PUNTAJE_X, RANKING_Y_HEADER, TEXTO_FONT_SIZE);

    for (int i = 0; i < tabla.getCantidad(); i++) {
        const RegistroPuntaje& r = tabla.getRegistro(i);
        float yFila = RANKING_Y_FILAS[i];

        dibujarTextoCentrado(ventana, fuente, std::to_string(i + 1), RANKING_COL_POS_X, yFila, TEXTO_FONT_SIZE);
        dibujarTextoCentrado(ventana, fuente, r.nombre, RANKING_COL_NOMBRE_X, yFila, TEXTO_FONT_SIZE);
        dibujarTextoCentrado(ventana, fuente, std::to_string(r.puntaje), RANKING_COL_PUNTAJE_X, yFila, TEXTO_FONT_SIZE);
    }

    dibujarTextoCentrado(ventana, fuente, "ESC - Volver", WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT - 12.0f, 12, sf::Color::Yellow);
    dibujarTextoCentrado(ventana, fuente, "1-Insercion  3-Merge (actual: " + algoritmoActual + ")",
        WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT - 30.0f, 12, sf::Color::Cyan);
}

void PantallasRenderer::dibujarIndicadorReplay(sf::RenderWindow& ventana, const sf::Font& fuente, bool automatico) const {
    std::string modo = automatico ? "AUTOMATICO (ESPACIO = manual)" : "MANUAL (<- -> , ESPACIO = auto)";
    dibujarTexto(ventana, fuente, "REPRODUCCION: " + modo, 5, static_cast<float>(WINDOW_HEIGHT - 25), 14, sf::Color::Yellow);
}