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
using namespace std;

int main(int argc, char ** argv) {
    int W, H, N;
    float mu, alpha_w, alpha_b;

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
    Visualizador v(balls, W, H, 0.01, N, mu, alpha_w, alpha_b);
    
    v.run();

    return 0; 
}
