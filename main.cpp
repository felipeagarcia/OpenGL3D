/**
 * @desc Programa que exibe uma pir�mide sob dois pontos de vista distintos.
 * @author Felipe Garcia
 */
#include <iostream>
#include <GL/glut.h>
#include <stdio.h>

int width = 500;
int height = 500;


typedef struct Point{
  GLfloat x;
  GLfloat y;
  GLfloat z;
}Point;

typedef struct Object{
  int type;
  // type = 0 : cube
  // type = 1 : pyramid

  int num_points;
  Point *points;
  Point center;
}Object;

Object obj;

void drawCube(Point p[8]){
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_LINE_STRIP);
    //top 
    glVertex3f(p[0].x, p[0].y, p[0].z);
    glVertex3f(p[1].x, p[1].y, p[1].z);
    glVertex3f(p[3].x, p[3].y, p[3].z);
    glVertex3f(p[2].x, p[2].y, p[2].z);
    glVertex3f(p[0].x, p[0].y, p[0].z);
    
    //bottom
    glVertex3f(p[4].x, p[4].y, p[4].z);
    glVertex3f(p[5].x, p[5].y, p[5].z);
    glVertex3f(p[7].x, p[7].y, p[7].z);
    glVertex3f(p[6].x, p[6].y, p[6].z);
    glVertex3f(p[4].x, p[4].y, p[4].z);
    
    //sides
    glVertex3f(p[6].x, p[6].y, p[6].z);
    glVertex3f(p[2].x, p[2].y, p[2].z);
    glVertex3f(p[3].x, p[3].y, p[3].z);
    glVertex3f(p[7].x, p[7].y, p[7].z);
    glVertex3f(p[5].x, p[5].y, p[5].z);
    glVertex3f(p[1].x, p[1].y, p[1].z);

  glEnd();
  glFlush();
}

void drawPiramid(Point p[5]){
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_LINE_STRIP);
    glVertex3f(p[0].x, p[0].y, p[0].z);
    glVertex3f(p[1].x, p[1].y, p[1].z);
    glVertex3f(p[3].x, p[3].y, p[3].z);
    glVertex3f(p[2].x, p[2].y, p[2].z);
    glVertex3f(p[0].x, p[0].y, p[0].z);
    glVertex3f(p[4].x, p[4].y, p[4].z);
    glVertex3f(p[1].x, p[1].y, p[1].z);
    glVertex3f(p[3].x, p[3].y, p[3].z);
    glVertex3f(p[4].x, p[4].y, p[4].z);
    glVertex3f(p[2].x, p[2].y, p[2].z);
  glEnd();
  glFlush();
}

/**
 * @desc Desenha eixos de um sistema de coordenadas.
 * @param {float*} basePoint Ponto de origem de um sistema de coordenadas.
 * @param {float*} i Primeiro versor.
 * @param {float*} j Segundo versor.
 * @param {float*} k Terceiro versor.
 */
void drawAxes(float *basePoint, float *i, float *j, float *k)
{
  float currentColor[4];
  /** Armazena cor atual */
  glGetFloatv(GL_CURRENT_COLOR, currentColor);  
  /** Desenha versores */
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_LINES);
    glVertex3f(basePoint[0], basePoint[1], basePoint[2]);
    glVertex3f(i[0], i[1], i[2]);
  glEnd();
  glColor3f(0.0, 1.0, 0.0);
  glBegin(GL_LINES);
    glVertex3f(basePoint[0], basePoint[1], basePoint[2]);
    glVertex3f(j[0], j[1], j[2]);
  glEnd();
  glColor3f(0.0, 0.0, 1.0);
  glBegin(GL_LINES);
    glVertex3f(basePoint[0], basePoint[1], basePoint[2]);
    glVertex3f(k[0], k[1], k[2]);
  glEnd();
  /** Retorna para cor anterior */
  glColor3f(currentColor[0], currentColor[1], currentColor[2]);
}

/**
 * @desc Desenha as coordenadas globais.
 */
void drawWCAxes()
{
  float *basePoint, *i, *j, *k;
  basePoint = new float[3];
  basePoint[0] = basePoint[1] = basePoint[2] = 0.0;
  i = new float[3];
  i[0] = 5.0;
  i[1] = i[2] = 0.0;
  j = new float[3];
  j[0] = j[2] = 0.0;
  j[1] = 5.0;
  k = new float[3];
  k[0] = k[1] = 0.0;
  k[2] = 5.0;
  drawAxes(basePoint, i, j, k);
}

void translate(Object *object, Point dest){
  GLfloat dx, dy, dz;
  dx = dest.x - object->center.x;
  dy = dest.y - object->center.y;
  dz = dest.z - object->center.z;
  for(int i = 0; i < object->num_points; i++){
    (*object).points[i].x += dx;
    (*object).points[i].y += dy;
    (*object).points[i].z += dz;
  }
  (*object).center.x += dx;
  (*object).center.y += dy;
  (*object).center.z += dz;
  glClear(GL_COLOR_BUFFER_BIT);
  drawWCAxes();
  object->type == 0? drawCube(object->points) : drawPiramid(object->points);
}

void scale(Object *object, GLfloat factor){
  int i;
  Point p = object->center;
  Point origin;
  origin.x = origin.y = origin.z = 0;
  translate(object, origin);
  for(i = 0; i < object->num_points; i++){
    (*object).points[i].x = object->points[i].x * factor;
    (*object).points[i].y = object->points[i].y * factor;
    (*object).points[i].z = object->points[i].z * factor;
  }
  translate(object, p);
  glClear(GL_COLOR_BUFFER_BIT);
  drawWCAxes();
  object->type == 0? drawCube(object->points) : drawPiramid(object->points);
}

void rotate(Object *object, GLfloat angle){
  
}

/**
 * @desc Fun��o de callback para desenho na tela.
 */
void displayCallback()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0f, 0.0f, 0.0f);
  glLoadIdentity();
  gluLookAt(2.0, 2.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  drawWCAxes();
  glFlush();
}

/**
 * @desc Fun��o de callback para reshape.
 * @param {int} w Nova largura da janela.
 * @param {int} h Nova altura da janela.
 */
void reshapeCallback(int w, int h)
{
  /** Atualiza os valores da janela */
  width = w;
  height = h;
  /** Define o volume de vista */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(65.0, (GLfloat) width/(GLfloat) height, 1.0, 20.0);
  glMatrixMode(GL_MODELVIEW);
}

void mouseCallback(GLint button, GLint state, GLint x, GLint y){
  if(button == GLUT_LEFT_BUTTON){
    Point *p = (Point*)malloc(8*sizeof(Point));
    int i, x_sign = 1, y_sign = 1, z_sign = 1;
    for(i = 0; i < 8; i++){
      p[i].x = 0.5 * x_sign;
      p[i].y = 0.5 * y_sign;
      p[i].z = 0.5 * z_sign;
      if(x_sign == 1){
        x_sign = -1;
        continue;
      }else if(y_sign == 1){
        y_sign = -1;
        x_sign = 1;
        continue;
      }else{
        z_sign = -1;
        x_sign = 1;
        y_sign = 1;
      }
    }
    obj.points = p;
    obj.type = 0;
    obj.num_points = 8;
    obj.center.x = obj.center.y = obj.center.z = 0;
    glClear(GL_COLOR_BUFFER_BIT);
    drawWCAxes();
    drawCube(p);
  }
    else if(button == GLUT_RIGHT_BUTTON){
      Point *p = (Point*)malloc(5 * sizeof(Point));
      int i, x_sign = 1, y_sign = 1;
      for(i = 0; i < 4; i++){
      p[i].x = 0.5 * x_sign;
      p[i].z = 0.5 * y_sign;
      p[i].y = -0.5;
      if(x_sign == 1){
        x_sign = -1;
        continue;
      }else if(y_sign == 1){
        y_sign = -1;
        x_sign = 1;
      }
    }
    p[4].x = p[4].z = 0;
    p[4].y = 0.5;
    obj.points = p;
    obj.type = 1;
    obj.num_points = 5;
    obj.center.x = obj.center.y = obj.center.z = 0;
    glClear(GL_COLOR_BUFFER_BIT);
    drawWCAxes();
    drawPiramid(p);
  }

}

void keybordCallback(GLubyte key, GLint x, GLint y){
  std::cout << "Key pressed: " << (GLint)key << "\n";
  if((GLint)key == 43 && obj.type != -1)
    scale(&obj, 1.1f);
  else if((GLint)key == 45 && obj.type != -1)
    scale(&obj, 1.0f/1.1f);
  else if((GLint)key == 116 && obj.type != -1){
    Point p;
    p.x = (GLfloat)x/100.0f;
    p.y = (GLfloat)y/100.0f;
    p.z = 0;
    printf("Translated to (%d,%d,0)\n", x, y);
    translate(&obj, p);
  }
}

int main(int argc, char **argv)
{
  /** Passo 1: Inicializa funcoes GLUT */
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(GLUT_SCREEN_WIDTH/2, GLUT_SCREEN_HEIGHT/2);
  glutInitWindowSize(width, height);
  glutCreateWindow("Tarefa 2");
  glLoadIdentity();
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  /** Passo 2: Registra callbacks da OpenGl */
  glutDisplayFunc(displayCallback);
  glutReshapeFunc(reshapeCallback);
  glutMouseFunc(mouseCallback);
  glutKeyboardFunc(keybordCallback);

  obj.type = -1;
  /** Passo 3: Executa o programa */
  glutMainLoop();
  return 0;
}