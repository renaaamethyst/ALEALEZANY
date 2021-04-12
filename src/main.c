#include <SDL.h>
#include <stdbool.h>
#include <stdlib.h>

#define ArrayLength(array) (sizeof(array) / sizeof(array[0])
#define internal static

internal void SetRendererColor(SDL_Renderer* renderer, SDL_Color color) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

int main() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("Logic Gate Thing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
	if (window == NULL) {
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return 1;
	}

	SDL_Color backgroundColor = {25, 75, 160, 255};
	SDL_Color gridLineColor = {60, 110, 200, 255};

	const int gridLineThickness = 2;
	const int baseGridLineAmount = 60;

	int screenWidth, screenHeight;
	SDL_GetRendererOutputSize(renderer, &screenWidth, &screenHeight);

	float aspectRatio = (float)screenHeight / (float)screenWidth;
	int numVerticalGridLines = baseGridLineAmount;
	int numHorizontalGridLines = (int)((float)baseGridLineAmount * aspectRatio);

	SDL_FRect* verticalGridlines = malloc(sizeof(SDL_FRect) * numVerticalGridLines);
	SDL_FRect* horizontalGridlines = malloc(sizeof(SDL_FRect) * numHorizontalGridLines);

	int gridLineSpacing = (int)ceilf((float)(screenWidth - (gridLineThickness * numVerticalGridLines)) / (float)numVerticalGridLines);

	for (int i = 0; i < numVerticalGridLines; ++i) {
		verticalGridlines[i].w = (float)gridLineThickness;
		verticalGridlines[i].h = (float)screenHeight;
		verticalGridlines[i].x = (float)(i * (gridLineThickness + gridLineSpacing));
		verticalGridlines[i].y = 0;
	}

	for (int i = 0; i < numHorizontalGridLines; ++i) {
		horizontalGridlines[i].w = (float)screenWidth;
		horizontalGridlines[i].h = (float)gridLineThickness;
		horizontalGridlines[i].x = 0;
		horizontalGridlines[i].y = (float)(i * (gridLineThickness + gridLineSpacing));
	}

	while (true) {
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				break;
			}
		}

		SetRendererColor(renderer, backgroundColor);
		SDL_RenderClear(renderer);

		SetRendererColor(renderer, gridLineColor);
		SDL_RenderFillRectsF(renderer, verticalGridlines, numVerticalGridLines);
		SDL_RenderFillRectsF(renderer, horizontalGridlines, numHorizontalGridLines);

		SDL_RenderPresent(renderer);
	}

	free(horizontalGridlines);
	free(verticalGridlines);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
