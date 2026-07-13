#include "Text.h"
#include "Resources.h"
#include "Game.h"
#include "Camera.h"
#include <iostream>

// Inicializa os atributos e gera a textura inicial
Text::Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color) 
    : Component(associated), fontFile(fontFile), fontSize(fontSize), style(style), text(text), color(color) {
    texture = nullptr;
    RemakeTexture(); // Gera a textura a partir dos parâmetros iniciais
}

// Libera a memória da textura SDL
Text::~Text() {
    if (texture != nullptr) {
        texture = nullptr;
    }
}

void Text::Update(float dt) {}

// Desenha o texto na tela considerando a posição da câmera
void Text::Render() {
    if (texture != nullptr) {
        // Define o retângulo de destino ajustado pela câmera
        SDL_Rect dstRect = { (int)(associated.box.x - Camera::pos.x), (int)(associated.box.y - Camera::pos.y), (int)associated.box.w, (int)associated.box.h };
        SDL_Rect clipRect = { 0, 0, (int)associated.box.w, (int)associated.box.h };

        // Renderiza com suporte a rotação do GameObject
        SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture.get(), &clipRect, &dstRect, associated.angleDeg, nullptr, SDL_FLIP_NONE);
    }
}

// Métodos Set: Alteram os atributos e forçam a recriação da textura
void Text::SetText(std::string text) { this->text = text; RemakeTexture(); }
void Text::SetColor(SDL_Color color) { this->color = color; RemakeTexture(); }
void Text::SetStyle(TextStyle style) { this->style = style; RemakeTexture(); }
void Text::SetFontFile(std::string fontFile) { this->fontFile = fontFile; RemakeTexture(); }
void Text::SetFontSize(int fontSize) { this->fontSize = fontSize; RemakeTexture(); }

// RemakeTexture: Transforma a string em uma textura renderizável
void Text::RemakeTexture() {
    // Ao atribuir nullptr, o shared_ptr decrementa a contagem e chama o deleter se for o último
    texture = nullptr;

    // Ajustado para receber o shared_ptr vindo do novo Resources
    std::shared_ptr<TTF_Font> font = Resources::GetFont(fontFile, fontSize);
    if (font == nullptr) return;

    // Renderiza o texto em uma Surface temporária baseada no estilo escolhido
    SDL_Surface* surface = nullptr;
    if (style == SOLID) {
        // Usamos font.get() para passar o ponteiro cru que a função da SDL exige
        surface = TTF_RenderText_Solid(font.get(), text.c_str(), color);
    } else if (style == SHADED) {
        SDL_Color bg = {0, 0, 0, 255};
        surface = TTF_RenderText_Shaded(font.get(), text.c_str(), color, bg);
    } else if (style == BLENDED) {
        surface = TTF_RenderText_Blended(font.get(), text.c_str(), color);
    }

    if (surface != nullptr) {
        // Converte Surface (Software) para Texture (Hardware/GPU)
        SDL_Texture* rawTexture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);
        
        // Criamos o shared_ptr da textura com um lambda para garantir a destruição via SDL
        texture = std::shared_ptr<SDL_Texture>(rawTexture, [](SDL_Texture* t) { SDL_DestroyTexture(t); });
        
        // Ajusta as dimensões da box do GameObject para as dimensões do texto gerado
        associated.box.w = surface->w;
        associated.box.h = surface->h;

        // Libera a surface temporária
        SDL_FreeSurface(surface);
    }
}
