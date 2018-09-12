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
#include <iostream>
#include <vector>
#include <stdlib.h>  
#include <chrono>


using namespace std;
using namespace std::chrono;


int main(int argc, char ** argv) {

    int W, H, N;
    float mu, alpha_w, alpha_b;
    char* dt;
    double t;

    cin >> W >> H >> N;
    cin >> mu >> alpha_w >> alpha_b;
    vector<ball> balls;

    int i = 0;
    while(i < N){
        _ball curr_ball;
        cin >> curr_ball.id >> curr_ball.radius >> curr_ball.mass >> curr_ball.x >> curr_ball.y >> curr_ball.vx >> curr_ball.vy;
        curr_ball.a = mu*curr_ball.mass*9.8;
        balls.push_back(curr_ball);
        i++;
    }
    
    dt = getenv ("DELTA_T");
    if (dt==NULL){
        t = 0.01;
    }
    else{
        t = atof(dt);
    }
    
    Visualizador v(balls, W, H, t, N, mu, alpha_w, alpha_b);
    
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    v.run();
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double> >(t2 - t1);

    cout << "DURATION: " << time_span.count() << '\n';
    return 0; 
}
