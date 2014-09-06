#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "FDrawer.hpp"


using namespace std;
double rot = 0.0;
GLfloat mspec[] = { 0.6, 0.6, 0.6, 1.0};
GLfloat mdif[] = { 0.7, 0.7, 0.3, 1.0};
GLfloat sh[] = { 100.0 };
GLfloat wl[] = { 1.0, 1.0, 1.0, 1.0};
GLfloat lpos[] = { 0.0, 0.0, 3.0, 1.0};

double function(double x1, double x2) {
  return sqrt((x1 * x1) + (x2 * x2));
  //return x1 + x2;
  //return 0.5;
}

int main() {



  sf::VideoMode vm(800, 600);
  sf::ContextSettings cs;
  cs.antialiasingLevel = 4;
  sf::RenderWindow window(vm, "vm1", sf::Style::Default, cs);
  window.setVerticalSyncEnabled(true);
  double dist = 0.0;
  glEnable(GL_NORMALIZE);
  glShadeModel(GL_SMOOTH);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mspec);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mdif);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, sh);
  glLightfv(GL_LIGHT0, GL_POSITION, lpos);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, wl);
  glLightfv(GL_LIGHT0, GL_SPECULAR, wl);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  double x1 = 0.;
  double x2 = 1.0;
  double y1 = 0.0;
  double y2 = 1.0;
  int xnum = 100;
  int ynum = 100;
  FDrawerOpenGL1 fd;

  std::vector<valarray<double> > vec;
  for(int i = 0; i < xnum; i++) {
    for(int j = 0; j < ynum; j++) {
      valarray<double> vl(3);
      vl[0] = x1 + (x2 - x1) / xnum * j;
      vl[1] = y1 + (y2 - y1) / ynum * i;
      vl[2] = function(vl[0], vl[1]);
      vec.push_back(vl);
    }
  }



  while(window.isOpen()) {
    sf::Event event;
    window.pollEvent(event);
    if(event.type == sf::Event::KeyPressed) {
      if(event.key.code == sf::Keyboard::Escape) {
        window.close();
      } else
      if(event.key.code == sf::Keyboard::Up) {
        dist += 0.01;
      } else
      if(event.key.code == sf::Keyboard::Down) {
        dist -= 0.01;
      } else
      if(event.key.code == sf::Keyboard::Left) {
        rot += 1;
      } else
      if(event.key.code == sf::Keyboard::Right) {
        rot -= 1;
      }
    } else
    if (event.type == sf::Event::Resized) {
      glViewport(0, 0, 800, 800);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluPerspective(60, window.getSize().x / window.getSize().y, 1.0, 10.0);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
    }
    glLoadIdentity();

    glTranslated(0, -1.0, -5.0);
    glTranslated(0, 0, dist);
    glRotated(rot, 0.0, 1.0, 0.0);
    glRotated(-90.0, 1.0, 0.0, 0.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1.0, 0.0, 0.0);
    /*glBegin(GL_TRIANGLE_STRIP);
    glVertex3d(1.0, 0.0, 0.0);
    glColor3d(0.0, 1.0, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glColor3d(0.0, 0.0, 1.0);
    glVertex3d(0.0, 1.0, 0.0);
    glEnd();*/
    fd.Draw(vec, xnum);

    //glFlush();
    window.display();
  }
}

