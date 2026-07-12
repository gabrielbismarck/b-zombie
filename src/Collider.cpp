#include "Collider.h"
#include "GameObject.h"
#include <cmath>

#ifdef DEBUG
#include "Camera.h"
#include "Game.h"
#include <SDL2/SDL.h>
#include <cmath>
#endif 
Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset) : Component(associated) {
	this->scale = scale;
	this->offset = offset;
}

void Collider::Update(float dt) {

	box.w = associated.box.w * scale.x;
	box.h = associated.box.h * scale.y;

	Vec2 center = associated.box.GetCenter();

	float angleRad = associated.angleDeg * (M_PI / 180.0f);
	Vec2 rotatedOffset = offset.InclinationRad(angleRad);

	Vec2 finalPos = center + rotatedOffset;

	box.x = finalPos.x - box.w/2.0f;
	box.y = finalPos.y - box.h/2.0f;
}


void Collider::Render() {
#ifdef DEBUG
    Vec2 center(box.GetCenter());
    SDL_Point points[5];

    float angleRad = associated.angleDeg * (M_PI / 180.0f);

    // Ponto 0: Superior esquerdo
    Vec2 point = (Vec2(box.x, box.y) - center).InclinationRad(angleRad) + center - Camera::pos;
    points[0].x = (int)point.x;
    points[0].y = (int)point.y;

    // Ponto 1: Superior direito
    point = (Vec2(box.x + box.w, box.y) - center).InclinationRad(angleRad) + center - Camera::pos;
    points[1].x = (int)point.x;
    points[1].y = (int)point.y;

    // Ponto 2: Inferior direito
    point = (Vec2(box.x + box.w, box.y + box.h) - center).InclinationRad(angleRad) + center - Camera::pos;
    points[2].x = (int)point.x;
    points[2].y = (int)point.y;

    // Ponto 3: Inferior esquerdo
    point = (Vec2(box.x, box.y + box.h) - center).InclinationRad(angleRad) + center - Camera::pos;
    points[3].x = (int)point.x;
    points[3].y = (int)point.y;

    // Ponto 4: fecha o polígono repetindo o primeiro
    points[4] = points[0];

    SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif
}




void Collider::SetScale(Vec2 scale) {
	this->scale = scale;
}

void Collider::SetOffset(Vec2 offset) {
	this->offset = offset;
}

