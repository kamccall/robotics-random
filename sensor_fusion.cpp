#include <iostream>
#include <math.h>
using namespace std;

const int mapWidth =  2;
const int mapHeight = 2;

void sensorFusion(double m1[][mapWidth], double m2[][mapWidth])
{
  // uses de morgan's law to combine matrices of sensor measurements
  for (int x = 0; x < mapHeight; x++)
  {
    for (int y = 0; y < mapWidth; y++)
    {
      double p = 1 - (1 - m1[x][y]) * (1 - m2[x][y]);
      cout << p << " ";
    }
    cout << endl;
  }
}

int main()
{
  // do a 2x2 matrix first
  double m1[mapHeight][mapWidth] = { { 0.9, 0.6 }, { 0.1, 0.5 } };
  double m2[mapHeight][mapWidth] = { { 0.3, 0.4 }, { 0.4, 0.3 } };
  sensorFusion(m1, m2);

  // do a 3x3 matrix as well
  double m3;
  double m4;
  sensorFusion(m3, m4);
  return 0;
}
