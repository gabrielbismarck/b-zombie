#ifndef TILEMAP_H
#define TILEMAP_H
#include <vector>
#include <string>
#include <memory>
#include "Component.h"
#include "TileSet.h"

// Constutor da classe TileMap. Herda de component
class TileMap : public Component {
    public:
        TileMap(GameObject& associated, std::string file, TileSet* tileSet);
        
        // CArrega os dados do mapa a partir de um arquivo
        void Load(std::string file);

        // Seta o TileSet a ser usado pelo TileMap
        void SetTileSet(TileSet* tileSet);
        
        //  Métopdo acessor para obter a referência do tile na posição (x, y) e camada z (padrão 0)
        int& At(int x, int y, int z = 0);
        
        // Implementação dos métodos virtuais da classe Component
        void Render() override;
        void Update(float dt) override;

        // Renderiza uma camada específica do mapa
        void RenderLayer(int layer);

        //  REtorna as dimensões do mapa
        int GetWidth();
        int GetHeight();
        int GetDepth();
    
    private:
        // vetor que armazena os indices
        std::vector<int> tileMatrix;
        // Conjunto de tiles usado para renderizar o mapa
        std::unique_ptr<TileSet> tileSet;
        // Dimensões do mapa em tiles
        int mapWidth; // largura do mapa em tiles
        int mapHeight; // altura do mapa em tiles
        int mapDepth; // quantidade de camadas do mapa

};


#endif