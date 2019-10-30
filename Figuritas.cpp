/*
* GRAFICACION - UNIDAD 2
* CLASE MATEMATICAS TEMA FIGURAS GEOMETRICAS
* CARACTERISTICAS DE AREA Y PERIMETRO
* INTEGRANTES:
* IVAN FRANCO DELGADO
* JESUS EDUARDO SOSA DIAZ
* JOSUE TORRES AVALOS
*/

#include <GL/glut.h> // IMPORTA LA LIBRERIA DE GLUT
#include <cmath>
#include "Vertex.h"
#include "Shapes.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Square.h"
#include "Triangle.h"

// VALORES UTILIZADOS PARA EL TAMANO DE LA
// PANTALLA DEFINIENDO ALTO Y ANCHO
#define HEIGHT 720
#define WIDTH 1280

// PROTOTIPOS DE FUNCIONES
void initializer(void);
void userInterface(void);
void keyInput(unsigned char, int, int);
void mouseControl(int, int, int, int);
bool collisionDetection(int);
bool isInside(int, int, int, int, int, int);

Vertex mouseClic; // ALMACENA EL LUGAR DONDE HACE CLIC
int options = 0;
static long font = (long)GLUT_BITMAP_TIMES_ROMAN_24;
Rectangle rec(200, 650, 200, 100, 1.0, 0.0, 0.0), rec_1(1000, 300, 200, 100, 1.0, 0.0, 0.0), rec_2(600, 300, 200, 100, 1.0, 0.0, 0.0);
Square sq(200, 480, 120, 0.0, 1.0, 0.0), sq_1(1000, 300, 120, 0.0, 1.0, 0.0), sq_2(600, 300, 120, 0.0, 1.0, 0.0);
Triangle tr(200, 280, 150, 120, 0.0, 0.0, 1.0), tr_1(1000, 300, 150, 120, 0.0, 0.0, 1.0), tr_2(600, 300, 150, 120, 0.0, 0.0, 1.0);
Circle cir(200, 100, 75, 1.0, 0.0, 1.0), cir_1(1000, 300, 75, 1.0, 0.0, 1.0), cir_2(600, 300, 75, 1.0, 0.0, 1.0);

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT); // ESTABLECE EL TAMANO DE LA VENTANA
	glutCreateWindow("FIGURAS GEOMETRICAS");

	initializer(); // INICIALIZA LA VENTANA

	glutDisplayFunc(userInterface); // ACTUALIZA LA PANTALLA DE TRAZADO

	glutKeyboardFunc(keyInput); // CAPTURA LOS TECLAZOS
	glutMouseFunc(mouseControl); // CAPTURA LOS CLICS

	glutMainLoop(); // GENERA EL LOOP

	return 0;
}

/*
* FUNCION QUE TOMA EL VALOR DE LA FUENTE Y UNA CADENA COMO PARAMETRO
* RECORRE LA CADENA CARACTER POR CARACTER HASTA QUE LLEGA AL PUNTO FINAL
* IMPRIME EL CARACTER UTILIZANDO EL FONT
*/
void writeBitmapString(void* font, const char* string)
{
	const char* c;
	for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

void keyInput(unsigned char key, int x, int y)
{/*
 switch (key)
 {
 case 27: // esc key
 exit(0);
 case 108: // l which stands for line
 message = "Command active: Line";
 active = true;
 draw = 1;
 glutPostRedisplay();
 break;
 case 114: // r which stands for rectangle
 message = "Command active: Rectangle";
 active = true;
 draw = 2;
 glutPostRedisplay();
 break;
 case 115: // s which stands for square
 message = "Command active: Square";
 active = true;
 draw = 3;
 glutPostRedisplay();
 break;
 case 99: // c which stands for circle
 message = "Command active: Circle";
 active = true;
 draw = 4;
 glutPostRedisplay();
 break;
 case 100: // d which stands for default
 message = "Select a command";
 active = false;
 fillPoints = false;
 draw = -1;
 clics = 0;
 used = false;
 for (size_t i = 0; i < 5; i++)
 {
 position[i] = 0;
 }
 rectangles.clear();
 squares.clear();
 circles.clear();
 lines.clear();
 glutPostRedisplay();
 break;
 default:
 break;
 }*/
}

/*
* FUNCION QUE CAPTURA LOS CLIC DEL RATON
*/
void mouseControl(int button, int state, int x, int y)
{
	// BOTON IZQUIERDO PRESIONADO
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mouseClic.setX(x); // ALMACENA LAS COORDENADAS DEL CLIC
		mouseClic.setY(y);

		if (collisionDetection(1))
		{
			options = 1;
			glutPostRedisplay();
		}
		else if (collisionDetection(2))
		{
			options = 2;
			glutPostRedisplay();
		}
		else if (collisionDetection(3))
		{
			options = 3;
			glutPostRedisplay();
		}
		else if (collisionDetection(4))
		{
			options = 4;
			glutPostRedisplay();
		}
	}
}

bool collisionDetection(int figure) {
	switch (figure) // DEPENDIENDO LA FIGURA SELECCIONADA HACE LA COMPARACION
	{
	case 1: {
		float x1 = rec.getOrigin().getX() - (rec.getBase() / 2), x2 = x1 + rec.getBase();
		float y1 = HEIGHT - (rec.getOrigin().getY() - (rec.getHeight() / 2)), y2 = y1 - rec.getHeight();
		// COMPARA LAS COORDENADAS EN EJE X E Y
		bool collisionX = (x1 <= mouseClic.getX() && x2 >= mouseClic.getX());
		bool collisionY = (y1 >= mouseClic.getY() && y2 <= mouseClic.getY());
		return collisionX && collisionY;
	}
	case 2: {
		float x1 = sq.getOrigin().getX() - (sq.getSide() / 2), x2 = x1 + sq.getSide();
		float y1 = HEIGHT - (sq.getOrigin().getY() - (sq.getSide() / 2)), y2 = y1 - sq.getSide();
		bool collisionX = (x1 <= mouseClic.getX() && x2 >= mouseClic.getX());
		bool collisionY = (y1 >= mouseClic.getY() && y2 <= mouseClic.getY());
		return collisionX && collisionY;
	}
	case 3: {
		Vertex aux_pos = tr.getOrigin();
		int x1 = aux_pos.getX() - (tr.getBase() / 2), y1 = aux_pos.getY() - (tr.getHeight() / 3);
		int x2 = aux_pos.getX(), y2 = aux_pos.getY() + ((tr.getHeight() / 3) * 2);
		int x3 = aux_pos.getX() + (tr.getBase() / 2), y3 = aux_pos.getY() - (tr.getHeight() / 3);

		return isInside(x1, y1, x2, y2, x3, y3);
	}
	case 4: {
		Vertex aux_pos = cir.getOrigin();
		return sqrt((mouseClic.getX() - aux_pos.getX())*(mouseClic.getX() - aux_pos.getX()) +
			(HEIGHT - mouseClic.getY() - aux_pos.getY())*(HEIGHT - mouseClic.getY() - aux_pos.getY())) < cir.getRadius();
	}
	default:
		return false;
	}
}

/*
* CALCULA EL AREA PARA LOS VERTICES DADOS
*/
float area(int x1, int y1, int x2, int y2, int x3, int y3)
{
	return abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
}

/*
* DETERMINA SI EL PUNTO ESTA DENTRO DEL TRIANGULO EN CUALQUIERA DE LAS 3 AREAS
*/
bool isInside(int x1, int y1, int x2, int y2, int x3, int y3)
{
	float A = area(x1, y1, x2, y2, x3, y3);
	float A1 = area(mouseClic.getX(), HEIGHT - mouseClic.getY(), x2, y2, x3, y3);
	float A2 = area(x1, y1, mouseClic.getX(), HEIGHT - mouseClic.getY(), x3, y3);
	float A3 = area(x1, y1, x2, y2, mouseClic.getX(), HEIGHT - mouseClic.getY());

	return (A == A1 + A2 + A3);
}

void initializer(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0); // COLOR CANVAS
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT); // TAMANO DE MANTA
}

/*
* INTERFAZ DE USUARIO O PANTALLA DONDE ES PINTADO TODO
* CADA VEZ QUE ES LLAMADA, SE LIMPIA LA PANTALLA
*/
void userInterface(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2f(500, 680);
	writeBitmapString((void*)font, "Clase Matematicas Tema Figuras Geometricas");
	glRasterPos2f(570, 640);
	writeBitmapString((void*)font, "Caracteristicas de Area y Perimetro");

	// SIEMPRE PINTA LAS FIGURAS GEOMETRICAS
	rec.drawShapeFill();
	sq.drawShapeFill();
	tr.drawShapeFill();
	cir.drawShapeTrig();

	switch (options) {
	case 1: // ENTRA AL RECTANGULO
	{
		glColor3f(1.0, 0.0, 0.0);
		glRasterPos2f(570, 600);
		writeBitmapString((void*)font, "Figura Seleccionada: Rectangulo");
		glColor3f(0.0, 0.0, 0.0);
		glRasterPos2f(550, 400);
		writeBitmapString((void*)font, "Lado");
		glRasterPos2f(400, 300);
		writeBitmapString((void*)font, "Altura");
		glRasterPos2f(915, 400);
		writeBitmapString((void*)font, "Area: Base * Altura");
		glRasterPos2f(915, 175);
		writeBitmapString((void*)font, "Perimetro: 2*Base + 2*Altura");
		rec_1.drawShape();
		rec_2.drawShapeFill();

		break;
	}
	case 2: // ENTRA AL CUADRADO
	{
		glColor3f(0.0, 1.0, 0.0);
		glRasterPos2f(570, 600);
		writeBitmapString((void*)font, "Figura Seleccionada: Cuadrado");
		glColor3f(0.0, 0.0, 0.0);
		glRasterPos2f(550, 400);
		writeBitmapString((void*)font, "Lado");
		glRasterPos2f(915, 400);
		writeBitmapString((void*)font, "Area: Lado * Lado");
		glRasterPos2f(915, 175);
		writeBitmapString((void*)font, "Perimetro: Lado*4");
		sq_1.drawShape();
		sq_2.drawShapeFill();
		break;
	}
	case 3: // ENTRA AL TRIANGULO
	{
		glColor3f(0.0, 0.0, 1.0);
		glRasterPos2f(570, 600);
		writeBitmapString((void*)font, "Figura Seleccionada: Triangulo");
		glColor3f(0.0, 0.0, 0.0);
		glRasterPos2f(550, 210);
		writeBitmapString((void*)font, "Lado");
		glRasterPos2f(400, 300);
		writeBitmapString((void*)font, "Altura");
		glRasterPos2f(915, 400);
		writeBitmapString((void*)font, "Area: (Base * Altura)/2");
		glRasterPos2f(900, 175);
		writeBitmapString((void*)font, "Perimetro: LadoA + LadoB + LadoC");
		tr_1.drawShape();
		tr_2.drawShapeFill();
		break;
	}
	case 4: // ENTRA AL CIRCULO
	{
		glColor3f(1.0, 0.0, 1.0);
		glRasterPos2f(570, 600);
		writeBitmapString((void*)font, "Figura Seleccionada: Circulo");
		glColor3f(0.0, 0.0, 0.0);
		glRasterPos2f(550, 400);
		writeBitmapString((void*)font, "Radio");
		glRasterPos2f(915, 400);
		writeBitmapString((void*)font, "Area: PI * Radio ^ 2");
		glRasterPos2f(915, 175);
		writeBitmapString((void*)font, "Perimetro: 2PI * Radio");
		cir_1.drawShape();
		cir_2.drawShapeTrig();
		break;
	}
	}

	glutSwapBuffers();
	glFlush();
}