/**
 * @desc Programa que exibe uma pir�mide sob dois pontos de vista distintos.
 * @author Felipe Garcia
 */
#include <iostream>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

int width = 500;
int height = 500;
float prev_angle = 0;
int type = 0, create = 1;

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
  glPushMatrix();
  glLoadIdentity();
  gluLookAt(2.0, 2.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(65.0, (GLfloat) width/(GLfloat) height, 1.0, 20.0);
  drawWCAxes();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
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
  glPushMatrix();
  glLoadIdentity();
  gluLookAt(2.0, 2.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(65.0, (GLfloat) width/(GLfloat) height, 1.0, 20.0);
  drawWCAxes();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  object->type == 0? drawCube(object->points) : drawPiramid(object->points);
}

void rotate(Object *object, GLfloat angle, int x, int y, int z){
  float M[4][4];
  M[0][0] = x*x*(1 - cos(angle)) + cos(angle);
  M[0][1] = x*y*(1 - cos(angle)) - z*sin(angle);
  M[0][2] = x*z*(1 - cos(angle)) + y*sin(angle);
  M[1][0] = y*x*(1 - cos(angle)) + z*sin(angle);
  M[1][1] = y*y*(1 - cos(angle)) + cos(angle);
  M[1][2] = y*z*(1 - cos(angle)) - x*sin(angle);
  M[2][0] = z*x*(1 - cos(angle)) - y*sin(angle);
  M[2][1] = z*y*(1 - cos(angle)) + x*sin(angle);
  M[2][2] = z*z*(1 - cos(angle)) + cos(angle);
  M[0][3] = M[1][3] = M[2][3] = M[3][0] = M[3][1] = M[3][2] = 0;
  M[3][3] = 1;
  float m[16];
  for(int i = 0; i < 4; i++){
  	for(int j = 0; j < 4; j++){
  		m[i*4 + j] = M[i][j];
  	}
  }
  glClear(GL_COLOR_BUFFER_BIT);
  glPushMatrix();
  glLoadIdentity();
  gluLookAt(2.0, 2.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(65.0, (GLfloat) width/(GLfloat) height, 1.0, 20.0);
  drawWCAxes();
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glMultMatrixf(m);
  object->type == 0? drawCube(object->points) : drawPiramid(object->points);
  glFlush();
}

GLfloat calcNorm(GLfloat v1_x, GLfloat v1_y, GLfloat v1_z,
               GLfloat v2_x, GLfloat v2_y, GLfloat v2_z){
  GLfloat result;
  result = sqrt(pow(v1_x - v2_x, 2) + pow(v1_y - v2_y, 2) + pow(v1_z - v2_z, 2));
  return result;
}

void vectorProduct(GLfloat v1_x, GLfloat v1_y, GLfloat v1_z,
               GLfloat v2_x, GLfloat v2_y, GLfloat v2_z,
               GLfloat *r_x, GLfloat *r_y, GLfloat *r_z){
  *r_x = v1_y * v2_z - v1_z * v2_y;
  *r_y = v1_z * v2_x - v1_x * v2_z;
  *r_z = v1_x * v2_y - v1_y * v2_x;
}

void LookAt(GLfloat ve_x, GLfloat ve_y, GLfloat ve_z,
            GLfloat vt_x, GLfloat vt_y, GLfloat vt_z,
            GLfloat up_x, GLfloat up_y, GLfloat up_z) {

  GLfloat f_x = (ve_x - vt_x)/calcNorm(ve_x, ve_y, ve_z, vt_x, vt_y, vt_z);
  GLfloat f_y = (ve_y - vt_y)/calcNorm(ve_x, ve_y, ve_z, vt_x, vt_y, vt_z);
  GLfloat f_z = (ve_z - vt_z)/calcNorm(ve_x, ve_y, ve_z, vt_x, vt_y, vt_z);
  GLfloat l_x, l_y, l_z, u_x, u_y, u_z;
  vectorProduct(up_x, up_y, up_z, f_x, f_y, f_z, &l_x, &l_y, &l_z);
  GLfloat x = l_x,y = l_y, z = l_z;
  l_x = l_x / calcNorm(x, y, z, 0, 0, 0);
  l_y = l_y / calcNorm(x, y, z, 0, 0, 0);
  l_z = l_z / calcNorm(x, y, z, 0, 0, 0);
  vectorProduct(f_x, f_y, f_z, l_x, l_y, l_z, &u_x, &u_y, &u_z);
  GLfloat T[16] = {1,0,0,-ve_x,
                   0,1,0,-ve_y,
                   0,0,1,-ve_z,
                   0,0,0,1};
  GLfloat R[16] = {l_x,l_y,l_z,0,
                   u_x,u_y,u_z,0,
                   f_x,f_y,f_z,0,
                   0,0,0,1};
  glMultMatrixf(R);
  glTranslated(-ve_x,-ve_y,-ve_z);
}


/**
 * @desc Fun��o de callback para desenho na tela.
 */
void displayCallback()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0f, 0.0f, 0.0f);
  glLoadIdentity();
  LookAt(2.0, 2.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  drawWCAxes();
  glFlush();
}

/**
 * @desc Funcao de callback para reshape.
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
  if(button == GLUT_LEFT_BUTTON && type == 0 && create == 1){
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
	  glLoadIdentity();
	  gluLookAt(2.0, 2.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	  glMatrixMode(GL_PROJECTION);
	  glLoadIdentity();
	  gluPerspective(65.0, (GLfloat) width/(GLfloat) height, 1.0, 20.0);
	  drawWCAxes();
	   drawCube(p);
	  glMatrixMode(GL_MODELVIEW);
	  create = 0;
   
  }
    else if(button == GLUT_LEFT_BUTTON && type == 1 && create == 1){
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
	  glLoadIdentity();
	  gluLookAt(2.0, 2.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	  glMatrixMode(GL_PROJECTION);
	  glLoadIdentity();
	  gluPerspective(65.0, (GLfloat) width/(GLfloat) height, 1.0, 20.0);
	  drawWCAxes();
	  drawPiramid(p);;
	  glMatrixMode(GL_MODELVIEW);
	  create = 0;
    
  }else if(create == 0){
  	Point p;
    p.x = (GLfloat)x/100.0f - 2.5f;
    p.y = 2.5f - (GLfloat)y/100.0f;
    p.z = 0;
    printf("Translated to (%d,%d,0)\n", x, y);
    translate(&obj, p);
    LookAt(p.x, p.y, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  }

}

void keybordCallback(GLubyte key, GLint x, GLint y){
  std::cout << "Key pressed: " << (GLint)key << "\n";
  if((GLint)key == 43 && obj.type != -1)
    scale(&obj, 1.1f);
  else if((GLint)key == 45 && obj.type != -1)
    scale(&obj, 1.0f/1.1f);
else if((GLint)key == 120 && obj.type != -1){
  	rotate(&obj, prev_angle + M_PI/6, 1, 0, 0); // rotate around x
  	prev_angle = prev_angle + M_PI/6;
  }else if((GLint)key == 88 && obj.type != -1){
  	rotate(&obj, prev_angle - M_PI/6, 1, 0, 0); // rotate around x
  	prev_angle = prev_angle - M_PI/6;
  }else if((GLint)key == 121 && obj.type != -1){
  	rotate(&obj, prev_angle + M_PI/6, 0, 1, 0); // rotate around y
  	prev_angle = prev_angle + M_PI/6;
  }else if((GLint)key == 89 && obj.type != -1){
  	rotate(&obj, prev_angle - M_PI/6, 0, 1, 0); // rotate around y
  	prev_angle = prev_angle - M_PI/6;
  }else if((GLint)key == 122 && obj.type != -1){
  	rotate(&obj, prev_angle + M_PI/6, 0, 0, 1); // rotate around z
  	prev_angle = prev_angle + M_PI/6;
  }else if((GLint)key == 90 && obj.type != -1){
  	rotate(&obj, prev_angle - M_PI/6, 0, 0, 1); // rotate around z
  	prev_angle = prev_angle - M_PI/6;
  }
}

void menu_test(GLint item_number)
{
  std::cout<<"Item "<<item_number<<"\n";
  type = item_number - 1;
  create = 1;
  glutPostRedisplay();
}

void test_create_menu()
{
  GLint submenu_id = glutCreateMenu(menu_test);
  glutAddMenuEntry("Subitem 1", 4);
  glutAddMenuEntry("Subitem 2", 5);
  glutAddMenuEntry("Subitem 3", 6);  
  
  glutCreateMenu(menu_test);  
  glutAddMenuEntry("Cube", 1);
  glutAddMenuEntry("Pyramid", 2);
  glutAddSubMenu("Item 3", submenu_id);  
  
  glutAttachMenu(GLUT_RIGHT_BUTTON);
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
  test_create_menu();
  glutRemoveMenuItem(0);
  glutRemoveMenuItem(3);
  glutRemoveMenuItem(6);
  glutRemoveMenuItem(7);
  glutRemoveMenuItem(8);
  obj.type = -1;
  /** Passo 3: Executa o programa */
  glutMainLoop();
  return 0;
}