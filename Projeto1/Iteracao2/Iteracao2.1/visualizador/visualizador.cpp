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

    cout << "Inicio Iteracao" << '\n';

    cout << "Velocidade e espaco atuais antes do walk: " << '\n';
    for(int i = 0; i<num_balls;i++){
        cout << "id bola: " << bodiesAtual[i].id << " velocidade em x: " << bodiesAtual[i].vx << " velocidade em y: " << bodiesAtual[i].vy << '\n'; 
        cout << "id bola: " << bodiesAtual[i].id << " espaco em x: " << bodiesAtual[i].x << " espaco em y: " << bodiesAtual[i].y << '\n'; 
    }

    walk();

    cout << "Possiveis espacos e velocidade depois do walk antes do collision: " << '\n';
    for(int i = 0; i<num_balls;i++){
        cout << "id bola: " << bodiesProximo[i].id << " velocidade em x: " << bodiesProximo[i].vx << " velocidade em y: " << bodiesProximo[i].vy << '\n'; 
        cout << "id bola: " << bodiesProximo[i].id << " espaco em x: " << bodiesProximo[i].x << " espaco em y: " << bodiesProximo[i].y << '\n'; 
    }

    collision();

    cout << "Espacos e Velocidade depois do collision antes do checkMerge: " << '\n';
    for(int i = 0; i<num_balls;i++){
        cout << "id bola: " << bodiesProximo[i].id << " velocidade em x: " << bodiesProximo[i].vx << " velocidade em y: " << bodiesProximo[i].vy << '\n'; 
        cout << "id bola: " << bodiesProximo[i].id << " espaco em x: " << bodiesProximo[i].x << " espaco em y: " << bodiesProximo[i].y << '\n'; 
    }

    checkMerge();

    cout << "Espacos depois do checkMerge: " << '\n';
    for(int i = 0; i<num_balls;i++){
        cout << "id bola: " << bodiesProximo[i].id << " velocidade em x: " << bodiesProximo[i].vx << " velocidade em y: " << bodiesProximo[i].vy << '\n'; 
        cout << "id bola: " << bodiesProximo[i].id << " espaco em x: " << bodiesProximo[i].x << " espaco em y: " << bodiesProximo[i].y << '\n'; 
    }

    update();
    iter++;
    cout << "Fim Iteracao" << '\n';

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
        else{
            bodiesProximo[b].vx = bodiesAtual[b].vx + delta_t * bodiesAtual[b].a;
            if(bodiesProximo[b].vx>0){
                bodiesProximo[b].vx = 0;
            }
        }
        
        if(bodiesAtual[b].vy>0){
            bodiesProximo[b].vy = bodiesAtual[b].vy - delta_t * bodiesAtual[b].a;
            if(bodiesProximo[b].vy<0){
                bodiesProximo[b].vy = 0;
            }
        }
        else{
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
            bodiesProximo[b].vx=-bodiesProximo[b].vx;
        }
        if(bodiesProximo[b].x - bodiesProximo[b].radius <= 0){
            bodiesProximo[b].vx=-bodiesProximo[b].vx;
        }
        if(bodiesProximo[b].y + bodiesProximo[b].radius >= field_height){
            bodiesProximo[b].vy=-bodiesProximo[b].vy;
        }
        if(bodiesProximo[b].y - bodiesProximo[b].radius <= 0){
            bodiesProximo[b].vy=-bodiesProximo[b].vy;
        }

        for(int c = b+1; c < num_balls; c++){


            double rx = bodiesProximo[c].x - bodiesProximo[b].x;
            double ry = bodiesProximo[c].y - bodiesProximo[b].y;
            double r = sqrt(pow(rx,2) + pow(ry,2));

            if (r <= bodiesProximo[b].radius + bodiesProximo[c].radius-1E-9){
                cout << "COLIDIU COLIDIU COLIDIU COLIDIU COLIDIU" << '\n';
                cout << "Bolinha b:" << bodiesAtual[b].id << " colidiu com bolinha c: " << bodiesAtual[c].id << '\n';

                double vBCx = bodiesProximo[b].vx - bodiesProximo[c].vx;
                double vBCy = bodiesProximo[b].vy - bodiesProximo[c].vy;

                double aB = ((vBCx*rx)+(vBCy*ry))/r;
                double vBrx = aB*rx/r;
                double vBry = aB*ry/r;

                double vBrpx = vBCx-vBrx;
                double vBrpy = vBCy-vBry; 

                double vBrxn = ((bodiesProximo[b].mass-bodiesProximo[c].mass)/(bodiesProximo[b].mass + bodiesProximo[c].mass))*vBrx;
                double vBryn = ((bodiesProximo[b].mass-bodiesProximo[c].mass)/(bodiesProximo[b].mass + bodiesProximo[c].mass))*vBry;

                double vCrxn = ((2*bodiesProximo[b].mass)/(bodiesProximo[b].mass + bodiesProximo[c].mass))*vBrx;
                double vCryn = ((2*bodiesProximo[b].mass)/(bodiesProximo[b].mass + bodiesProximo[c].mass))*vBry;

                bodiesProximo[b].vx=((vBrxn+vBrpx)+bodiesProximo[c].vx);
                bodiesProximo[b].vy=((vBryn+vBrpy)+bodiesProximo[c].vy);
                
                bodiesProximo[c].vx=(vCrxn+bodiesProximo[c].vx);
                bodiesProximo[c].vy=(vCryn+bodiesProximo[c].vy);
            } 
        }
    }
}

void Visualizador::checkMerge(){
    for(int b = 0; b< num_balls; b++){
        if(bodiesProximo[b].x + bodiesProximo[b].radius >= field_width){
            bodiesProximo[b].x=bodiesAtual[b].x;
        }
        if(bodiesProximo[b].x - bodiesProximo[b].radius <= 0){
            bodiesProximo[b].x=bodiesAtual[b].x;
        }
        if(bodiesProximo[b].y + bodiesProximo[b].radius >= field_height){
            bodiesProximo[b].y=bodiesAtual[b].y;
        }
        if(bodiesProximo[b].y - bodiesProximo[b].radius <= 0){
            bodiesProximo[b].y=bodiesAtual[b].y;
        }

        for(int c=b+1; c<num_balls; c++){

            double rx = bodiesProximo[c].x - bodiesProximo[b].x;
            double ry = bodiesProximo[c].y - bodiesProximo[b].y;
            double r = sqrt(pow(rx,2) + pow(ry,2));

            if (r < bodiesProximo[b].radius + bodiesProximo[c].radius-1E-9){
                bodiesProximo[b].x = bodiesAtual[b].x;
                bodiesProximo[b].y = bodiesAtual[b].y;
                bodiesProximo[c].x = bodiesAtual[c].x;
                bodiesProximo[c].y = bodiesAtual[c].y;
            }
        }
    }
}

void Visualizador::update(){
    bodiesAtual = bodiesProximo;
}
