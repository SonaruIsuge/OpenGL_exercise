#include "Background.h"
#include "../Shapes/GDShape.h"


Background::Background(Camera* camera) {
	for (int i = 0; i < STAR_NUMBER; i++) {
		stars[i] = new GDShape("GeometryData/Rhombic.gd");
		stars[i]->Init(camera->GetViewMatrix(), camera->GetProjMatrix());
		stars[i]->SetSingleColor(STAR_COLOR);

		stars[i]->position = vec3(random.randFloat(-VIEWPORT_HALF_WIDTH, VIEWPORT_HALF_WIDTH), random.randFloat(-VIEWPORT_HALF_HEIGHT, VIEWPORT_HALF_HEIGHT), 0.0f);
		float randomScale = random.randFloat(0.1f, 0.3f);
		stars[i]->scale = vec3(randomScale);

		starsSpeed[i] = random.randFloat(STAR_MIN_SPEED, STAR_MAX_SPEED);
	}
}


Background::~Background() {
	for (auto& star : stars)
		if(star != nullptr) delete star;
}


void Background::Update(float deltaTime) {
	for (int i = 0; i < STAR_NUMBER; i++) {
		stars[i]->position.y += -starsSpeed[i] * deltaTime;
		stars[i]->Draw();

		if (stars[i]->position.y < -VIEWPORT_HALF_HEIGHT) stars[i]->position.y = VIEWPORT_HALF_HEIGHT + 1;
	}
}