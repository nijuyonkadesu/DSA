#include<SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include<iostream>
#include<random>
#include<ranges>
#include<algorithm>

// c++ -lSDL2 sort_visualizer.cpp

using namespace std;

void drawState(vector<int>& v, SDL_Renderer* renderer, int red, int blue){
    int xAxis= 0;
    for(int yAxis: v){
        if(xAxis == red)
            SDL_SetRenderDrawColor(renderer, 255 ,0 ,0 ,255);
        else if(xAxis == blue)
            SDL_SetRenderDrawColor(renderer, 0 ,0 , 255, 255);
        else
           SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        // Origin is top left (inverted y axis for historical reasons)
        // Cartesian quadrant 4
        SDL_RenderDrawLine(renderer, xAxis, 100, xAxis, 100 - yAxis);
        xAxis++;
    }

}

int main(){
    random_device rd;
    // the numbers tell the size of pixel
    uniform_int_distribution<> d(1,100);
    vector<int> v(100);
    // populate vector
    generate(v.begin(), v.end(), [&](){ return d(rd); });

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_CreateWindowAndRenderer(100*10, 100*10, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, 10, 10);

    // sort algorithm
    for(int i = 0; i != v.size(); i++){
        for(int j = i + 1; j != v.size(); j++){
            // Clear screen
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            // Update screen
            drawState(v, renderer, i, j);
            SDL_RenderPresent(renderer);
            SDL_Delay(10);
            if(v[i] > v[j] ){
                swap(v[i] , v[j]);
            }
        }
    }
    SDL_Delay(1000);
}
