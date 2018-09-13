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
#include <omp.h>
#include <stdlib.h>    
#include <chrono>
#include <tuple>

using namespace std;
char* gui= getenv ("GUI");
     
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

    if(atof(gui) == 1){
        win = SDL_CreateWindow("Visualizador SUPERCOMP", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_width, win_height, 0);
        renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    }

    T=0;
    Tacs =0;
    iter = 0;
    fim =0;
}

Visualizador::~Visualizador() {
    if(atof(gui) == 1){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);
    }
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
    if(atof(gui) == 1){ //se o visualizador estiver habilitado, ele é desenhado
        SDL_ShowWindow(win);
        draw();
        while(!SDL_QuitRequested()){
            fim = do_iteration();
            draw();
        }
    }
    else{
        while (fim == 0) { //caso contrário simulação para quando corpos param
            fim = do_iteration(); 
        }
    }
}

int Visualizador::do_iteration() {

    if(atof(gui) != 1){ //caso o visualizador não esteja habilitado
        fim = checkIfEnded(); //checar se todas as bolinhas pararam
        if(fim && atof(gui)==0){
            T = guiMode(1, delta_t);//printar as posições finais    
        }
    }

    if(fim == 0){ //Se a simulação não tiver terminado
        walk();
        collision();
        checkMerge();
        update();
        if(atof(gui) == 0){
            T = guiMode(T, delta_t);
        }
        iter++;
    } 
    return fim;
}

void Visualizador::walk(){
    #pragma omp parallel for
    for(int b = 0; b<num_balls; b++){
        bodiesProximo[b].x = bodiesAtual[b].x + bodiesAtual[b].vx * delta_t; 
        bodiesProximo[b].y = bodiesAtual[b].y + bodiesAtual[b].vy * delta_t;

        // Análise das velocidade para checar se bolinhas irão pararam 
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

        //Análise de colisão com as bordas
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

        //Análise de colisão com as outras bolas
        for(int c = b+1; c < num_balls; c++){
            double rx = bodiesProximo[c].x - bodiesProximo[b].x;
            double ry = bodiesProximo[c].y - bodiesProximo[b].y;
            double r = sqrt(pow(rx,2) + pow(ry,2));//raio entre os corpos

            
            if (r <= bodiesProximo[b].radius + bodiesProximo[c].radius){
                //Corpos colidiram
                if(atof(gui) == 0){
                    choques.push_back(make_tuple(bodiesProximo[b].id, bodiesProximo[c].id, delta_t*iter));
                }

                //Velocidade do corpo B em relação ao corpo C
                double vBCx = bodiesProximo[b].vx - bodiesProximo[c].vx;
                double vBCy = bodiesProximo[b].vy - bodiesProximo[c].vy;

                //Projeção da velocidade de B em relacao a C no raio de colisão
                double aB = ((vBCx*rx)+(vBCy*ry))/r;
                double vBrx = aB*rx/r;
                double vBry = aB*ry/r;

                //Vetor perpendicular ao vetor projetado no raio de colisão
                double vBrpx = vBCx-vBrx;
                double vBrpy = vBCy-vBry; 

                //Cálculos das novas velocidades
                double vBrxn = ((bodiesProximo[b].mass-bodiesProximo[c].mass)/(bodiesProximo[b].mass + bodiesProximo[c].mass))*vBrx;
                double vBryn = ((bodiesProximo[b].mass-bodiesProximo[c].mass)/(bodiesProximo[b].mass + bodiesProximo[c].mass))*vBry;
                double vCrxn = ((2*bodiesProximo[b].mass)/(bodiesProximo[b].mass + bodiesProximo[c].mass))*vBrx;
                double vCryn = ((2*bodiesProximo[b].mass)/(bodiesProximo[b].mass + bodiesProximo[c].mass))*vBry;

                //Novas velocidades em relação ao sistema de coordenadas
                bodiesProximo[b].vx=(vBrxn+vBrpx)+bodiesProximo[c].vx;
                bodiesProximo[b].vy=(vBryn+vBrpy)+bodiesProximo[c].vy;
                bodiesProximo[c].vx=vCrxn+bodiesProximo[c].vx;
                bodiesProximo[c].vy=vCryn+bodiesProximo[c].vy;
            } 
        }
    }
}

//Checar se as bolas se fundiram
void Visualizador::checkMerge(){
    #pragma omp parallel for
    for(int b = 0; b< num_balls; b++){

        //Verifica se corpo ficou preso nas bordas
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
                //Caso elas tenham se fundido a posição não é atualizada
                bodiesProximo[b].x = bodiesAtual[b].x;
                bodiesProximo[b].y = bodiesAtual[b].y;
                bodiesProximo[c].x = bodiesAtual[c].x;
                bodiesProximo[c].y = bodiesAtual[c].y;
            }
        }
    }
}

void Visualizador::update(){
    //Atualização das posições e das velocidades de todas as bolinhas
    #pragma omp parallel for
    for(int b=0; b<num_balls; b++){
        bodiesAtual[b] = bodiesProximo[b];
    }
}

double Visualizador::guiMode(double T, double t){
    //Caso GUI=0, a cada 1 segundo de simulação são printadas as posições e as velocidades dos corpos,
    //além de printar os choques que aconteceram durante aquele segundo
    T = T+t;
    if(T>=1){
        Tacs+=1;
        for(int i =0; i<choques.size(); i++){
            cout << "CHOQUE " << get<0>(choques[i]) << " " << get<1>(choques[i]) << " " << get<2>(choques[i]) << '\n';
        }
        cout << '\n';
        cout << "Tempo atual da simulacao: " << Tacs << " segundos"<<'\n';
        choques.clear();
        for(int i = 0; i<num_balls;i++){
            cout << bodiesProximo[i].id << " " << bodiesProximo[i].radius << " " << bodiesProximo[i].mass << " " << bodiesProximo[i].x << " " << bodiesProximo[i].y << " " << bodiesProximo[i].vx << " " << bodiesProximo[i].vy << '\n';      
        }
        cout << '\n';
        T=0;
    }
    return T;
}

bool Visualizador::checkIfEnded(){
    //Avalia se as velocidades de todas as bolinhas são iguais a zero, indicando que a simulação terminou
    bool f = true; 
    #pragma omp parallel for reduction (&:f)
    for(int b=0; b<num_balls; b++){
        if(bodiesAtual[b]. vx != 0 || bodiesAtual[b].vy !=0){
            f = f & false;
        }
        else{
            f=f & true;
        }
    }
    return f;
}