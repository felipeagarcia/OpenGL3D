/**
 * @desc Programa que exibe uma pir�mide sob dois pontos de vista distintos.
 * @author Diego Cintra
 */
#include <iostream>
#include <GL/glut.h>
#include <math.h>

int width = 500;
int height = 500;

/**
 * @desc Desenha eixos de um sistema de coordenadas.
 * @param {float*} basePoint Ponto de origem de um sistema de coordenadas.
 * @param {float*} i Primeiro versor.
 * @param {float*} j Segundo versor.
 * @param {float*} k Terceiro versor.
 */





void LookAt(GLfloat ve_x, GLfloat ve_y, GLfloat ve_z,
            GLfloat vt_x, GLfloat vt_y, GLfloat vt_z,
            GLfloat up_x, GLfloat up_y, GLfloat up_z) {
  int i;
  GLfloat f[3], l[3], u[3], norm;
  ve_x = - ve_x;
  ve_y = - ve_y;
  f[0] = ve_x - vt_x;
  f[1] = ve_y - vt_y;
  f[2] = ve_z - vt_z;
  norm = sqrt(pow(f[0], 2) + pow(f[1], 2) + pow(f[2], 2));
  for(i = 0; i < 3; i++)
    f[i] /= norm;
  l[0] = up_y * f[2] - up_z * f[1];
  l[1] = up_z * f[0] - up_x * f[2];
  l[2] = up_x * f[1] - up_y * f[0];
  norm = sqrt(pow(l[0], 2) + pow(l[1], 2) + pow(l[2], 2));
  for(i = 0; i < 3; i++)
    l[i] /= norm;
  u[0] = f[1] * l[2] - f[2] * l[1];
  u[1] = f[2] * l[0] - f[0] * l[2];
  u[2] = f[0] * l[1] - f[1] * l[0];
  GLfloat T[16] = {1,0,0,-ve_x,
                 0,1,0,-ve_y,
                 0,0,1,-ve_z,
                 0,0,0,1};
  GLfloat R[16] = {l[0],l[1],l[2],0,
               u[0],u[1],u[2],0,
               f[0],f[1],f[2],0,
               0,0,0,1};

  glMultMatrixf(R);
  glTranslated(ve_x, ve_y, -ve_z);
}

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

/**
 * @desc Fun��o de callback para desenho na tela.
 */
void displayCallback()
{
  /** Limpa a janela APENAS uma vez */
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(1.0f, 0.0f, 0.0f);
  /** Desenha a janela mais a esquerda */
  glViewport(0, 0, width/2, height);
  glLoadIdentity();
  LookAt(3.0, 2.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  drawWCAxes();
  glRotatef(-90.0, 1.0, 0.0, 0.0);
  glutWireCone(1.0, 2.0, 4, 4);
  /** Desenha a janela mais a direita */
  glViewport(width/2, 0, width/2, height);
  glLoadIdentity();
  LookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  drawWCAxes();
  glRotatef(-90.0, 1.0, 0.0, 0.0);
  glutWireCone(1.0, 2.0, 4, 4);

  /** Dispara os comandos APENAS uma vez */
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

int main(int argc, char **argv)
{
  /** Passo 1: Inicializa fun��es GLUT */
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(width, height);
  glutCreateWindow("Duas viewports");
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  /** Passo 2: Registra callbacks da OpenGl */
  glutDisplayFunc(displayCallback);
  glutReshapeFunc(reshapeCallback);

  /** Passo 3: Executa o programa */
  glutMainLoop();
  return 0;
}