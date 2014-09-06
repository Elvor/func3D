#include "FDrawer.hpp"
#include "SFML/OpenGL.hpp"
#include <stdexcept>

std::valarray<double> CrossProduct(const std::valarray<double>& v1, const std::valarray<double>& v2) {
  std::valarray<double> p(3);
  p[0] = v1[1] * v2[2] - v1[2] * v2[1];
  p[1] = v1[2] * v2[0] - v1[0] * v2[2];
  p[2] = v1[0] * v2[1] - v1[1] * v2[0];
  return p;
}



void FDrawerOpenGL1::Draw(const std::vector<std::valarray<double> > &array, int xRowLen) {
  glColor4d(1.0, 0.0, 0.0, 0.9);
  if(array.size() % xRowLen) throw std::logic_error("domain isn't a rectangle");
  int nrows = array.size() / xRowLen;
  --nrows;
  for(int i = 0; i < nrows - 1; i++) {
    glColor3d(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(50.0, 0.0, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(0.0, 50.0, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(0.0, 0.0, 50.0);
    glEnd();
    glColor3d(0.0, 0.6, 0.6);
    //glBegin(GL_TRIANGLE_STRIP);
    glBegin(GL_TRIANGLES);
    for(int j = 0; j < xRowLen - 1; j++) {                        //    4    3
      std::valarray<double> v1 = array[xRowLen * i + j];          //    * <- *
      std::valarray<double> v2 = array[xRowLen * i + j + 1];      //     t / ^
      std::valarray<double> v3 = array[xRowLen * (i+1) + j + 1];  //     / d |
      std::valarray<double> v4 = array[xRowLen * (i+1) + j];      //    * -> *
      std::valarray<double> vc1(3);                               //    1    2
      std::valarray<double> vc2(3);
      std::valarray<double> nor1(3);
      std::valarray<double> nor2(3);
      for(int i = 0; i < 3; i++) {
        vc1[i] = v2[i] - v1[i];
        vc2[i] =  v3[i] - v2[i];
      }
      nor1 = CrossProduct(vc1, vc2);
      for(int i = 0; i < 3; i++) {
        vc1[i] = v4[i] - v3[i];
        vc2[i] =  v1[i] - v4[i];
      }
      nor2 = CrossProduct(vc1, vc2);

      glNormal3d(nor1[0], nor1[1], nor1[2]);
      glVertex3d(v1[0], v1[1], v1[2]);
      glVertex3d(v2[0], v2[1], v2[2]);
      glVertex3d(v3[0], v3[1], v3[2]);


      glNormal3d(nor2[0], nor2[1], nor2[2]);
      glVertex3d(v3[0], v3[1], v3[2]);
      glVertex3d(v4[0], v4[1], v4[2]);
      glVertex3d(v1[0], v1[1], v1[2]);

      //glEnd();
    }
    glEnd();
  }
}
