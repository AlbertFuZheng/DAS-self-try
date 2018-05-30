#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <random>
#include "test.h"
using namespace std;
static int n, m;



int main() {
   std::default_random_engine engine;
   //k controls the range of random number generated
   int k = 20;
   std::uniform_int_distribution<int> dist{ 0 - (1 << k),(1 << k) };
   //std::uniform_int_distribution<int> dist{ -5, 5 };
   //n is the number of observatories
   //n = 64 * 13 * 3;
   n = 100;
   //m is the number of queries
   //m = 1000;
   m = 200;

   int *x = new int[n];
   int *y = new int[n];
   int *temp = new int[n];

   int *xx = new int[n];
   int *yy = new int[n];
   int *tempt = new int[n];

   //Generate observatory data
   for (int i = 0; i < n; i++) {
      x[i] = dist(engine);
      xx[i] = x[i];
      y[i] = dist(engine);
      yy[i] = y[i];
      temp[i] = dist(engine);
      tempt[i] = temp[i];
   }

   cout << n << " " << m << endl;

   for (int i = 0; i < n; i++) {
      cout << x[i] << " " << y[i] << " " << temp[i] << endl;
   }

   for (int i = 0; i < m; i++) {
      int x1 = dist(engine);
      int y1 = dist(engine);
      int x2 = dist(engine);
      int y2 = dist(engine);
      cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
   }

}