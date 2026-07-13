#ifndef TEXT_H
#define TEXT_H

#define INCLUDE_SDL
#define INCLUDE_SDL_TTF
#include "SDL_include.h"

#include "Component.h"
#include <string>
#include <memory>

class Text : public Component {
public:
    enum TextStyle { SOLID, SHADED, BLENDED };

    // Inicializa atributos e gera a primeira textura
    Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color);
    
    // Destrói a textura se ela existir
    ~Text();

    // Atualiza lógica (vazio no momento)
    void Update(float dt) override;
    
    // Desenha o texto na tela usando a RenderCopyEx com suporte a rotação
    void Render() override;

    void SetText(std::string text);
    void SetColor(SDL_Color color);
    void SetStyle(TextStyle style);
    void SetFontFile(std::string fontFile);
    void SetFontSize(int fontSize);

private:
    // Recria a textura SDL a partir da fonte e parâmetros atuais
    void RemakeTexture();

    std::shared_ptr<TTF_Font> font;
    std::shared_ptr<SDL_Texture> texture; 

    std::string text;     // O conteúdo do texto
    TextStyle style;      // Estilo (Solid, Shaded ou Blended)
    std::string fontFile; // Caminho do arquivo .ttf
    int fontSize;         // Tamanho da fonte em pts
    SDL_Color color;      // Cor (RGBA)
};

#endif