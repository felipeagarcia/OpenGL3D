/**
 * @desc Programa que exibe uma pir�mide sob dois pontos de vista distintos.
 * @author Felipe Garcia
 */
#include <iostream>
#include <GL/glut.h>

int width = 500;
int height = 500;


typedef struct Point{
  GLfloat x;
  GLfloat y;
  GLfloat z;
}Point;


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
  gluLookAt(3.0, 2.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  drawWCAxes();
  glRotatef(-90.0, 1.0, 0.0, 0.0);
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
      p[i].x = 1 * x_sign;
      p[i].y = 1 * y_sign;
      p[i].z = 1 * z_sign;
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
    drawCube(p);
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
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  /** Passo 2: Registra callbacks da OpenGl */
  glutDisplayFunc(displayCallback);
  glutReshapeFunc(reshapeCallback);
  glutMouseFunc(mouseCallback);

  /** Passo 3: Executa o programa */
  glutMainLoop();
  return 0;
}