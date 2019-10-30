#pragma once
#pragma once
#include "Shapes.h"

// ------- CLASE HIJA / TRIANGULO ----------------------------
class Triangle : public Shapes {

	// ----- ATRIBUTOS PERTENECIENTES A TRIANGULO ------------
private:
	float base;
	float height;
	Vertex vertices[3];

public:
	Triangle() {
		setOrigin(0, 0);
		setColor(1.0, 1.0, 1.0);
		setLineWidth(1);
		setBase(50);
		setHeight(25);
		setNoVertices(3);
		calculateVertex();
	}

	Triangle(float x, float y) {
		setOrigin(x, y);
		setColor(1.0, 1.0, 1.0);
		setLineWidth(1);
		setBase(50);
		setHeight(25);
		area = calculateArea();
		perimeter = calculatePerimeter();
		setNoVertices(3);
		calculateVertex();
	}

	Triangle(float x, float y, float ba, float h) {
		setOrigin(x, y);
		setColor(1.0, 1.0, 1.0);
		setLineWidth(1);
		setBase(ba);
		setHeight(h);
		area = calculateArea();
		perimeter = calculatePerimeter();
		setNoVertices(3);
		calculateVertex();
	}

	Triangle(float x, float y, float ba, float h, float r, float g, float b) {
		setOrigin(x, y);
		setColor(r, g, b);
		setLineWidth(1);
		setBase(ba);
		setHeight(h);
		area = calculateArea();
		perimeter = calculatePerimeter();
		setNoVertices(3);
		calculateVertex();
	}

	Triangle(float x, float y, float ba, float h, float r, float g, float b, int lwidth) {
		setOrigin(x, y);
		setColor(r, g, b);
		setLineWidth(lwidth);
		setBase(ba);
		setHeight(h);
		area = calculateArea();
		perimeter = calculatePerimeter();
		setNoVertices(3);
		calculateVertex();
	}

	Triangle(const Triangle& triangle) {
		Vertex pos = triangle.getOrigin();
		setOrigin(pos.getX(), pos.getY());
		Color col = triangle.getColor();
		setColor(col.getR(), col.getG(), col.getB());
		setLineWidth(triangle.getLineWidth());
		setBase(triangle.getBase());
		setHeight(triangle.getHeight());
		setNoVertices(3);
		calculateVertex();
	};

	void setBase(float b) {
		if (b > 0) { base = b; }
		else { base = 50; }
		area = calculateArea();
		perimeter = calculatePerimeter();
	}

	void setHeight(float h) {
		if (h > 0) { height = h; }
		else { height = 25; }
		area = calculateArea();
		perimeter = calculatePerimeter();
	}

	float getBase() const { return base; }
	float getHeight() const { return height; }
	Vertex getVertices() const { return *vertices; }

	double calculateArea() { return (base * height) / 2; }

	double calculatePerimeter() {
		double side_a = sqrt(pow(base, 2) + pow(height, 2));
		return ((2 * side_a) * base);
	}

	void calculateVertex() {
		Vertex aux_pos = getOrigin();
		float x1 = aux_pos.getX() - (getBase() / 2), y1 = aux_pos.getY() - (getHeight() / 3);
		float x2 = aux_pos.getX(), y2 = aux_pos.getY() + ((getHeight() / 3) * 2);
		float x3 = aux_pos.getX() + (getBase() / 2), y3 = aux_pos.getY() - (getHeight() / 3);
		setVertices(x1, y1, x2, y2, x3, y3);
	}

	void setVertices(float x1, float y1, float x2, float y2, float x3, float y3) {
		vertices[0].setX(x1), vertices[0].setY(y1); // vertice 1
		vertices[1].setX(x2), vertices[1].setY(y2); // vertice 2
		vertices[2].setX(x3), vertices[2].setY(y3); // vertice 3
	}

	void drawShape() {
		Color aux_color = getColor();
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		glLineWidth(getLineWidth());
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < NoVertices; i++)
		{
			glVertex2i(vertices[i].getX(), vertices[i].getY());
		}
		glEnd();
	}

	void drawShapeFill() {
		Color aux_color = getColor();
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		glLineWidth(getLineWidth());
		glBegin(GL_POLYGON);
		for (int i = 0; i < NoVertices; i++)
		{
			glVertex2i(vertices[i].getX(), vertices[i].getY());
		}
		glEnd();
	}

	void moveShape(float _x, float _y) {
		origin.moveVertex(_x, _y);
		calculateVertex();
	}

	void scaleShape(float factor) {
		setBase(factor * getBase());
		setHeight(factor * getHeight());
		calculateVertex();
	}

	void rotateShape(float _x, float _y, double _theta) {
		for (int i = 0; i < NoVertices; i++)
		{
			vertices[i].rotateVertex(_x, _y, _theta);
		}
	}
};