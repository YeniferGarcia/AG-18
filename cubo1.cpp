/*

	Copyright 2015 Ludwin Hernández

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Crear cubo.
*/

#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>

//Definimos variables
double rotate_y=0;
double rotate_x=0;
double rotate_z=0;

GLfloat X = 0.0f;
GLfloat Y = 0.0f;
GLfloat Z = 0.0f;
GLfloat scale = 1.0f;


GLint ancho=800;
GLint alto=600;
int perspectiva = 0;

void reshape(int w, int h)
{
    glViewport(0, 0, w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if(perspectiva)
      gluPerspective(45.0f, (GLfloat)w/(GLfloat)h, 0.2f, 30.0f);
   
    else

    //glOrtho(-4,4,-4, 4, -4, 4);
    //glOrtho(-2, 2, -2, 2, -2, 2);
	glFrustum (-1.0, 1.0, -1.0, 1.0, 2.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
 
    ancho = w;
    alto = h;
}

void cubo(void)
{
	// Primera cara, se identica por multiples colores
    glBegin(GL_POLYGON);
	glColor3f( 1.0, 1.0, 1.0 );
    glVertex3f(  0.5, -0.5, -0.5 );      // V1 Blanco
    glColor3f( 1.0, 1.0, 0.0 );
    glVertex3f(  0.5,  0.5, -0.5 );      // V2 Amarillo
    glColor3f( 0.0, 0.0, 1.0 );
    glVertex3f( -0.5,  0.5, -0.5 );      // V3 es azul
    glColor3f( 1.0, 0.0, 0.0 );
    glVertex3f( -0.5, -0.5, -0.5 );      // V4 rojo

    glEnd();

    // LADO TRASERO: lado blanco
    glBegin(GL_POLYGON);
    glColor3f( 1.0,  1.0, 1.0 );
    glVertex3f( 0.5, -0.5, 0.5 );
    glVertex3f( 0.5,  0.5, 0.5 );
    glVertex3f(-0.5,  0.5, 0.5 );
    glVertex3f(-0.5, -0.5, 0.5 );
    glEnd();

    // LADO DERECHO: lado verde
    glBegin(GL_POLYGON);
    glColor3f( 0.0,  1.0,  0.0 );
    glVertex3f(0.5, -0.5, -0.5 );
    glVertex3f(0.5,  0.5, -0.5 );
    glVertex3f(0.5,  0.5,  0.5 );
    glVertex3f(0.5, -0.5,  0.5 );
    glEnd();

    // LADO IZQUIERDO: lado Amarillo
    glBegin(GL_POLYGON);
    glColor3f(1.0,  1.0,  0.0 );
    glVertex3f(-0.5, -0.5,  0.5 );
    glVertex3f(-0.5,  0.5,  0.5 );
    glVertex3f(-0.5,  0.5, -0.5 );
    glVertex3f(-0.5, -0.5, -0.5 );
    glEnd();

    // LADO SUPERIOR: lado azul
    glBegin(GL_POLYGON);
    glColor3f(0.0,  0.0,  1.0 );
    glVertex3f(0.5,  0.5,  0.5 );
    glVertex3f(0.5,  0.5, -0.5 );
    glVertex3f(-0.5,  0.5, -0.5 );
    glVertex3f(-0.5,  0.5,  0.5 );
    glEnd();

    // LADO INFERIOR: lado rojo
    glBegin(GL_POLYGON);
    glColor3f(1.0,  0.0,  0.0 );
    glVertex3f(0.5, -0.5, -0.5 );
    glVertex3f(0.5, -0.5,  0.5 );
    glVertex3f(-0.5, -0.5,  0.5 );
    glVertex3f(-0.5, -0.5, -0.5 );
    glEnd();
	
}
void display()
{
    //  Borrar pantalla y Z-buffer
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // Resetear transformaciones
    glLoadIdentity();
    // Rotar en el eje X,Y y Z
    glRotatef( rotate_x, 1.0, 0.0, 0.0 );
    glRotatef( rotate_y, 0.0, 1.0, 0.0 );
    glRotatef( rotate_z, 0.0, 0.0, 1.0 );
    //glTranslatef(0.0f, 0.0f, -0.2f);
    glTranslatef(X, Y, Z); 	// Transladar en los 3 ejes
    // Otras transformaciones
    
    gluLookAt(1.0, 2.0, 3.0, //eye (x,y,z)
    0.0, 0.0, 0.0,           //at(x,y,z)
    0.0, 1.0, 0.0);          //up (x,y,z)
    
    /*
    gluLookAt(1.0, 2.0, 3.0, //eye (x,y,z)
    0.0, 0.0, 0.0,           //at(x,y,z)
    0.0, 1.0, 0.0);          //up (x,y,z)
    * */
    glScalef(scale, scale, scale);
    
    cubo();

    glFlush();
    glutSwapBuffers();

}

void init()
{
    glClearColor(0,0,0,0);
    // Habilitar la prueba de profundidad de Z-buffer
    glEnable(GL_DEPTH_TEST);
    ancho = 800;
    alto = 600;
}

// Función para controlar teclas especiales
void specialKeys( int key, int x, int y )
{

    //  Flecha derecha: aumentar rotación 7 grados
    if (key == GLUT_KEY_RIGHT)
        rotate_y += 7;

    //  Flecha izquierda: rotación en eje Y negativo 7 grados
    else if (key == GLUT_KEY_LEFT)
        rotate_y -= 7;
    //  Flecha arriba: rotación en eje X positivo 7 grados
    else if (key == GLUT_KEY_UP)
        rotate_x += 7;
    //  Flecha abajo: rotación en eje X negativo 7 grados
    else if (key == GLUT_KEY_DOWN)
        rotate_x -= 7;
    //  Tecla especial F2 : rotación en eje Z positivo 7 grados
    else if (key == GLUT_KEY_F2)
        rotate_z += 7;
    //  Tecla especial F2 : rotación en eje Z negativo 7 grados
    else if (key == GLUT_KEY_F2)
        rotate_z -= 7;

    //  Solicitar actualización de visualización
    glutPostRedisplay();

}

// Función para controlar teclas normales del teclado.
void keyboard(unsigned char key, int x, int y)
{
    //control de teclas que hacen referencia a Escalar y transladar el cubo en los ejes X,Y,Z.
    switch (key)
    {
    case 's':
        scale=0.5;
        break;
    case 'd':
        scale=1.5;
        break;
    case 'x' :
        X += 0.1f;
        break;
    case 'X' :
        X -= 0.1f;
        break;
    case 'y' :
        Y += 0.1f;
        break;
    case 'Y' :
        Y -= 0.1f;
        break;
    case 'z':
        Z -= 0.1f;
        break;
    case 'Z':
        Z += 0.1f;
        break;
    case 'p':
    case 'P':
      perspectiva=1;
      reshape(ancho,alto);
      break;
 
    case 'o':
    case 'O':
      perspectiva=0;
      reshape(ancho,alto);
      break;
    case 27:
        exit(0);			// exit
    }
    glutPostRedisplay();
}



int main(int argc, char* argv[])
{

    //  Inicializar los parámetros GLUT y de usuario proceso
    glutInit(&argc,argv);

    // Solicitar ventana con color real y doble buffer con Z-buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (800, 600);
    glutInitWindowSize(ancho, alto);
    // Crear ventana
    glutCreateWindow("Cubo controlado por teclas");
	init();
    // Funciones de retrollamada
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);

    // Pasar el control de eventos a GLUT
    glutMainLoop();

    // Regresar al sistema operativo
    return 0;

}
