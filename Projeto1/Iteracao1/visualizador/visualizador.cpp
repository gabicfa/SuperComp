/*
 * Copyright (c) 2018 Igor Montagner igordsm@gmail.com
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "visualizador.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL2_gfxPrimitives.h"

#include <stdio.h>
#include <iostream>
#include <math.h>

#include <chrono>
using namespace std;

typedef std::chrono::high_resolution_clock Time;

Visualizador::Visualizador(std::vector<ball> &bodies, int field_width, int field_height, double delta_t, int N, double mu, double alpha_w, double alpha_b):
    delta_t(delta_t),
    field_width(field_width),
    field_height(field_height),
    bodiesAtual(bodies),
    bodiesProximo(bodies),
    mu(mu),
    alpha_b(alpha_b),
    alpha_w(alpha_w),
    num_balls(N){
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    double ratio = (double) field_width / field_height;
    if (ratio > 1) {
        win_width = max_dimension;
        win_height = max_dimension / ratio;
    } else {
        win_width = max_dimension * ratio;
        win_height = max_dimension;
    }
    win = SDL_CreateWindow("Visualizador SUPERCOMP", SDL_WINDOWPOS_CENTERED,
                           SDL_WINDOWPOS_CENTERED, win_width, win_height, 0);
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    iter = 0;
}

Visualizador::~Visualizador() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

void Visualizador::draw() {
    SDL_SetRenderDrawColor(renderer, 160, 160, 185, 255);
    SDL_RenderClear(renderer);
    for (auto i = bodiesAtual.begin(); i != bodiesAtual.end(); i++) {
        filledCircleRGBA(renderer, i->x / field_width * win_width,
                         i->y / field_height* win_height,
                         i->radius / field_width * win_width,
                         255, 0 ,0, 255);
    }
    SDL_RenderPresent(renderer);
}

void Visualizador::run() {
    SDL_ShowWindow(win);
    draw();
    while (!SDL_QuitRequested()) {
        do_iteration();       
        draw();
    }
}

void Visualizador::do_iteration() {

    walk();

    collision();

    update();

    iter++;
}

void Visualizador::walk(){
    for(int b = 0; b<num_balls; b++){
        bodiesProximo[b].x = bodiesAtual[b].x + bodiesAtual[b].vx * delta_t; 
        bodiesProximo[b].y = bodiesAtual[b].y + bodiesAtual[b].vy * delta_t;

        if(bodiesAtual[b].vx>0){
            bodiesProximo[b].vx = bodiesAtual[b].vx - delta_t * bodiesAtual[b].a;
            if(bodiesProximo[b].vx<0){
                bodiesProximo[b].vx = 0;
            }
        }
        
        if(bodiesAtual[b].vy>0){
            bodiesProximo[b].vy = bodiesAtual[b].vy - delta_t * bodiesAtual[b].a;
            if(bodiesProximo[b].vy<0){
                bodiesProximo[b].vy = 0;
            }
        }
        if(bodiesAtual[b].vx<0){
            bodiesProximo[b].vx = bodiesAtual[b].vx + delta_t * bodiesAtual[b].a;
            if(bodiesProximo[b].vx>0){
                bodiesProximo[b].vx = 0;
            }
        }
        if(bodiesAtual[b].vy<0){
            bodiesProximo[b].vy = bodiesAtual[b].vy + delta_t * bodiesAtual[b].a;
            if(bodiesProximo[b].vy>0){
                bodiesProximo[b].vy = 0;
            }
        }
    }
}

void Visualizador::collision(){
    for(int b = 0; b<num_balls; b++){
        if(bodiesProximo[b].x + bodiesProximo[b].radius >= field_width){
            bodiesProximo[b].vx = -bodiesProximo[b].vx;
        }
        if(bodiesProximo[b].x - bodiesProximo[b].radius <= 0){
            bodiesProximo[b].vx = -bodiesProximo[b].vx;
        }
        if(bodiesProximo[b].y + bodiesProximo[b].radius >= field_height){
            bodiesProximo[b].vy = -bodiesProximo[b].vy;
        }
        if(bodiesProximo[b].y - bodiesProximo[b].radius <= 0){
            bodiesProximo[b].vy = -bodiesProximo[b].vy;
        }

        for(int c = 0; c < num_balls; c++){
            if(b == c){
                continue;
            }
            double rx = bodiesProximo[c].x - bodiesProximo[b].x;
            double ry = bodiesProximo[c].y - bodiesProximo[b].y;
            double r = sqrt(pow(rx,2) + pow(ry,2));
            
            if (r < (bodiesProximo[b].radius + bodiesProximo[c].radius)){
                double aB = ((bodiesProximo[b].vx*rx)+(bodiesProximo[b].vy*ry))/r;
                double aC = ((bodiesProximo[c].vx*rx)+(bodiesProximo[c].vy*ry))/r;

                if((aB>=0 && aC<=0)){
                    
                    double vBrx = aB*rx;
                    double vBry = aB*ry;
                    double vBrpx = bodiesProximo[b].vx-vBrx;
                    double vBrpy = bodiesProximo[b].vy-vBry;
                    vBrx = -vBrx;
                    vBry = -vBry;
                    bodiesProximo[b].vx = vBrx-vBrpx;
                    bodiesProximo[b].vy = vBry-vBrpy;

                    double vCrx = aC*rx;
                    double vCry = aC*ry;
                    double vCrpx = bodiesProximo[c].vx-vCrx;
                    double vCrpy = bodiesProximo[c].vy-vCry;
                    vCrx = -vCrx;
                    vCry = -vCry;
                    bodiesProximo[c].vx = vCrx-vCrpx;
                    bodiesProximo[c].vy = vCry-vCrpy;
                }
                else{
                    if(aB>=0 && aC>=0){                    
                        double vBrx = aB*rx;
                        double vBry = aB*ry;
                        double vBrpx = bodiesProximo[b].vx-vBrx;
                        double vBrpy = bodiesProximo[b].vy-vBry;
                        vBrx = -vBrx;
                        vBry = -vBry;
                        bodiesProximo[b].vx = vBrx-vBrpx;
                        bodiesProximo[b].vy = vBry-vBrpy;
                    }
                }
            }
        }
    }
}

void Visualizador::update(){
    bodiesAtual = bodiesProximo;
}