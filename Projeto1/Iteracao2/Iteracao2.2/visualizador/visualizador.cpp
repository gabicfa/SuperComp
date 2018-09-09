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
    cout << "Comeco iteracao" << '\n';

    cout << "Velocidade antes do walk: " << '\n';

    for(int i = 0; i<num_balls;i++){
        cout << "id bola: " << bodiesAtual[i].id << " velocidade em x: " << bodiesAtual[i].vx << " velocidade em y: " << bodiesAtual[i].vy << '\n'; 
    }

    walk();

    collision();

    cout << "Soma vetores" << '\n';

    somaVetores();

    cout << "Velocidade depois somaVetores: " << '\n';
    for(int i = 0; i<num_balls;i++){
        cout << "id bola: " << bodiesProximo[i].id << " velocidade em x: " << bodiesProximo[i].vx << " velocidade em y: " << bodiesProximo[i].vy << '\n'; 
    }

    update();


    cout << "Velocidade depois update: " << '\n';
    for(int i = 0; i<num_balls;i++){
        cout << "id bola: " << bodiesAtual[i].id << " velocidade em x: " << bodiesAtual[i].vx << " velocidade em y: " << bodiesAtual[i].vy << '\n'; 
    }
    cout << "Fim iteracao" << '\n';

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
        if(bodiesProximo[b].x + bodiesProximo[b].radius >= field_width-1E-9){
            bodiesProximo[b].somaVetoresX.push_back(-bodiesProximo[b].vx);
        }
        if(bodiesProximo[b].x - bodiesProximo[b].radius <= 0+1E-9){
            bodiesProximo[b].somaVetoresX.push_back(-bodiesProximo[b].vx);
        }
        if(bodiesProximo[b].y + bodiesProximo[b].radius >= field_height-1E-9){
            bodiesProximo[b].somaVetoresY.push_back(-bodiesProximo[b].vy);
        }
        if(bodiesProximo[b].y - bodiesProximo[b].radius <= 0+1E-9){
            bodiesProximo[b].somaVetoresY.push_back(-bodiesProximo[b].vy);
        }

        for(int c = b+1; c < num_balls; c++){

            double rx = bodiesProximo[c].x - bodiesProximo[b].x;
            double ry = bodiesProximo[c].y - bodiesProximo[b].y;
            double r = sqrt(pow(rx,2) + pow(ry,2));
            
            if (r < (bodiesProximo[b].radius + bodiesProximo[c].radius)){
                cout<< "colidiu bola b " << bodiesProximo[b].id << " com bola c " << bodiesProximo[c].id << '\n';

                cout<< "rx: " << rx << '\n';
                cout<< "ry: " << ry << '\n';
                cout<< "r: " << r << '\n';

                double vBCx = bodiesProximo[b].vx - bodiesProximo[c].vx;
                double vBCy = bodiesProximo[b].vy - bodiesProximo[c].vy;

                cout<< "vBCx: " << vBCx << '\n';
                cout<< "vBCy: " << vBCy << '\n';

                double aB = ((vBCx*rx)+(vBCy*ry))/r;

                double vBrx = aB*rx/r;
                double vBry = aB*ry/r;

                cout<< "vBrx: " << vBrx << '\n';
                cout<< "vBry: " << vBry << '\n';

                double vBrpx = vBCx-vBrx;
                double vBrpy = vBCy-vBry;

                cout<< "vBrpx: " << vBrpx << '\n';
                cout<< "vBrpy: " << vBrpy << '\n';

                double vBrxn = ((bodiesProximo[b].mass-bodiesProximo[c].mass)/(bodiesProximo[b].mass + bodiesProximo[c].mass))*vBrx;
                double vBryn = ((bodiesProximo[b].mass-bodiesProximo[c].mass)/(bodiesProximo[b].mass + bodiesProximo[c].mass))*vBry;

                cout<< "vBrxn: " << vBrxn << '\n';
                cout<< "vBryn: " << vBryn << '\n';

                double vCrxn = ((2*bodiesProximo[b].mass)/(bodiesProximo[b].mass + bodiesProximo[c].mass))*vBrx;
                double vCryn = ((2*bodiesProximo[b].mass)/(bodiesProximo[b].mass + bodiesProximo[c].mass))*vBry;

                bodiesProximo[b].somaVetoresX.push_back((vBrxn+vBrpx)+bodiesProximo[c].vx);
                bodiesProximo[b].somaVetoresY.push_back((vBryn+vBrpy)+bodiesProximo[c].vy);


                cout<< "vBx: " << (vBrxn+vBrpx)+bodiesProximo[c].vx << '\n';
                cout<< "vBy: " << (vBryn+vBrpy)+bodiesProximo[c].vy << '\n';
                
                bodiesProximo[c].somaVetoresX.push_back(vCrxn+bodiesProximo[c].vx);
                bodiesProximo[c].somaVetoresY.push_back(vCryn+bodiesProximo[c].vy);

                cout<< "vCx: " << vCrxn+bodiesProximo[c].vx << '\n';
                cout<< "vCY: " << vCryn+bodiesProximo[c].vy << '\n';
            } 
        }
        if(bodiesProximo[b].somaVetoresX.size()==0){
            bodiesProximo[b].somaVetoresX.push_back(bodiesProximo[b].vx);
        }
        if(bodiesProximo[b].somaVetoresY.size()==0){
            bodiesProximo[b].somaVetoresY.push_back(bodiesProximo[b].vy);
        }
    }
}

void Visualizador::somaVetores(){
    double vX,vY;
        for(int i = 0; i<num_balls;i++){
            vX=0;
            vY=0;
            cout << "somaVetoresX " << i << " : ";
            for(int j = 0; j<bodiesProximo[i].somaVetoresX.size(); j++){
                cout << bodiesProximo[i].somaVetoresX[j] << ", ";
                vX = vX + bodiesProximo[i].somaVetoresX[j];
            }
            cout<< '\n';
            bodiesProximo[i].vx = vX;
            bodiesProximo[i].somaVetoresX ={};
            cout << "somaVetoresY "<< i << " : ";
            for(int j = 0; j<bodiesProximo[i].somaVetoresY.size(); j++){
                cout << bodiesProximo[i].somaVetoresY[j] << ", ";
                vY = vY + bodiesProximo[i].somaVetoresY[j];
            }
            cout<< '\n';
            bodiesProximo[i].vy = vY;
            bodiesProximo[i].somaVetoresY ={};        
        }
}

void Visualizador::update(){
    bodiesAtual = bodiesProximo;
}