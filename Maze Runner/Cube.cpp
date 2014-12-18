#include "cube.h"
#include "main.h"
#include "Glee.h"

Cube::Cube() {
    center.set(0, 0, 0, 1);
    model2world.identity();

}

Cube::Cube(double s) {
	center.set(0, 0, 0, 1);
	scale.set(s*0.5, s*0.5, s*0.5,0);
	size = s;
    model2world.identity();
}

void Cube::render(bool shade) {
	double i = size / 2;
	glEnable(GL_TEXTURE_2D);
	// Make sure no bytes are padded:
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Select GL_MODULATE to mix texture with polygon color for shading:
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Use bilinear interpolation:
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3d(1, 1, 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glUniform1i(glGetUniformLocation(Globals::texShader->getPid(), "texture"), 0);
	if (shade)
		Globals::texShader->bind();
	else
		Globals::texShader->unbind();

	glBegin(GL_QUADS);
	glNormal3d(0, 0, 1);
	glTexCoord2d(0, 0);
	glVertex3d(-i, -i, i);
	glTexCoord2d(1, 0);
	glVertex3d(i, -i, i);
	glTexCoord2d(1, 1);
	glVertex3d(i, i, i);
	glTexCoord2d(0, 1);
	glVertex3d(-i, i, i);
	glEnd();
	Globals::texShader->unbind();

	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glUniform1i(glGetUniformLocation(Globals::texShader->getPid(), "texture"), 0);
	if (shade)
		Globals::texShader->bind();
	else
		Globals::texShader->unbind();
	glBegin(GL_QUADS);
	glNormal3d(1, 0, 0);
	glTexCoord2d(0, 0);
	glVertex3d(-i, -i, -i);
	glTexCoord2d(1, 0);
	glVertex3d(-i, -i, i);
	glTexCoord2d(1, 1);
	glVertex3d(-i, i, i);
	glTexCoord2d(0, 1);
	glVertex3d(-i, i, -i);
	glEnd();
	Globals::texShader->unbind();

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glUniform1i(glGetUniformLocation(Globals::texShader->getPid(), "texture"), 0);
	if (shade)
		Globals::texShader->bind();
	else
		Globals::texShader->unbind();

	glBegin(GL_QUADS);
	glNormal3d(0, 0, -1);
	glTexCoord2d(0, 0);
	glVertex3d(i, -i, -i);
	glTexCoord2d(1, 0);
	glVertex3d(-i, -i, -i);
	glTexCoord2d(1, 1);
	glVertex3d(-i, i, -i);
	glTexCoord2d(0, 1);
	glVertex3d(i, i, -i);
	glEnd();
	Globals::texShader->unbind();

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glUniform1i(glGetUniformLocation(Globals::texShader->getPid(), "texture"), 0);
	if (shade)
		Globals::texShader->bind();
	else
		Globals::texShader->unbind();

	glBegin(GL_QUADS);
	glNormal3d(-1, 0, 0);
	glTexCoord2d(0, 0);
	glVertex3d(i, -i, i);
	glTexCoord2d(1, 0);
	glVertex3d(i, -i, -i);
	glTexCoord2d(1, 1);
	glVertex3d(i, i, -i);
	glTexCoord2d(0, 1);
	glVertex3d(i, i, i);
	glEnd();
	Globals::texShader->unbind();

	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glUniform1i(glGetUniformLocation(Globals::texShader->getPid(), "texture"), 0);
	if (shade)
		Globals::texShader->bind();
	else
		Globals::texShader->unbind();

	glBegin(GL_QUADS);
	glNormal3d(0, 1, 0);
	glTexCoord2d(0, 0);
	glVertex3d(-i, i, i);
	glTexCoord2d(1, 0);
	glVertex3d(i, i, i);
	glTexCoord2d(1, 1);
	glVertex3d(i, i, -i);
	glTexCoord2d(0, 1);
	glVertex3d(-i, i, -i);
	glEnd();
	Globals::texShader->unbind();

	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glUniform1i(glGetUniformLocation(Globals::texShader->getPid(), "texture"), 0);
	if (shade)
		Globals::texShader->bind();
	else
		Globals::texShader->unbind();

	glBegin(GL_QUADS);
	glNormal3d(0, -1, 0);
	glTexCoord2d(0, 0);
	glVertex3d(-i, -i, i);
	glTexCoord2d(1, 0);
	glVertex3d(i, -i, i);
	glTexCoord2d(1, 1);
	glVertex3d(i, -i, -i);
	glTexCoord2d(0, 1);
	glVertex3d(-i, -i, -i);
	glEnd();
	Globals::texShader->unbind();

	//glActiveTexture(GL_TEXTURE1);
	glDisable(GL_TEXTURE_2D);
}

void Cube::render(Matrix4 C, bool shade) {
	double i = size / 2;
	glEnable(GL_TEXTURE_2D);
	// Make sure no bytes are padded:
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Select GL_MODULATE to mix texture with polygon color for shading:
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Use bilinear interpolation:
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3d(1, 1, 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glUniform1i(glGetUniformLocation(Globals::texShader->getPid(), "texture"), 0);
	if (shade)
		Globals::texShader->bind();
	else
		Globals::texShader->unbind();

	glBegin(GL_QUADS);
	glNormal3d(0, 0, 1);
	glTexCoord2d(0, 0);
	glVertex3d(-i, -i, i);
	glTexCoord2d(1, 0);
	glVertex3d(i, -i, i);
	glTexCoord2d(1, 1);
	glVertex3d(i, i, i);
	glTexCoord2d(0, 1);
	glVertex3d(-i, i, i);
	glEnd();
	Globals::texShader->unbind();

	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glUniform1i(glGetUniformLocation(Globals::texShader->getPid(), "texture"), 0);
	if (shade)
		Globals::texShader->bind();
	else
		Globals::texShader->unbind();
	glBegin(GL_QUADS);
	glNormal3d(1, 0, 0);
	glTexCoord2d(0, 0);
	glVertex3d(-i, -i, -i);
	glTexCoord2d(1, 0);
	glVertex3d(-i, -i, i);
	glTexCoord2d(1, 1);
	glVertex3d(-i, i, i);
	glTexCoord2d(0, 1);
	glVertex3d(-i, i, -i);
	glEnd();
	Globals::texShader->unbind();

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glUniform1i(glGetUniformLocation(Globals::texShader->getPid(), "texture"), 0);
	if (shade)
		Globals::texShader->bind();
	else
		Globals::texShader->unbind();

	glBegin(GL_QUADS);
	glNormal3d(0, 0, -1);
	glTexCoord2d(0, 0);
	glVertex3d(i, -i, -i);
	glTexCoord2d(1, 0);
	glVertex3d(-i, -i, -i);
	glTexCoord2d(1, 1);
	glVertex3d(-i, i, -i);
	glTexCoord2d(0, 1);
	glVertex3d(i, i, -i);
	glEnd();
	Globals::texShader->unbind();

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glUniform1i(glGetUniformLocation(Globals::texShader->getPid(), "texture"), 0);
	if (shade)
		Globals::texShader->bind();
	else
		Globals::texShader->unbind();

	glBegin(GL_QUADS);
	glNormal3d(-1, 0, 0);
	glTexCoord2d(0, 0);
	glVertex3d(i, -i, i);
	glTexCoord2d(1, 0);
	glVertex3d(i, -i, -i);
	glTexCoord2d(1, 1);
	glVertex3d(i, i, -i);
	glTexCoord2d(0, 1);
	glVertex3d(i, i, i);
	glEnd();
	Globals::texShader->unbind();

	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glUniform1i(glGetUniformLocation(Globals::texShader->getPid(), "texture"), 0);
	if (shade)
		Globals::texShader->bind();
	else
		Globals::texShader->unbind();

	glBegin(GL_QUADS);
	glNormal3d(0, 1, 0);
	glTexCoord2d(0, 0);
	glVertex3d(-i, i, i);
	glTexCoord2d(1, 0);
	glVertex3d(i, i, i);
	glTexCoord2d(1, 1);
	glVertex3d(i, i, -i);
	glTexCoord2d(0, 1);
	glVertex3d(-i, i, -i);
	glEnd();
	Globals::texShader->unbind();

	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glUniform1i(glGetUniformLocation(Globals::texShader->getPid(), "texture"), 0);
	if (shade)
		Globals::texShader->bind();
	else
		Globals::texShader->unbind();

	glBegin(GL_QUADS);
	glNormal3d(0, -1, 0);
	glTexCoord2d(0, 0);
	glVertex3d(-i, -i, i);
	glTexCoord2d(1, 0);
	glVertex3d(i, -i, i);
	glTexCoord2d(1, 1);
	glVertex3d(i, -i, -i);
	glTexCoord2d(0, 1);
	glVertex3d(-i, -i, -i);
	glEnd();
	Globals::texShader->unbind();

	//glActiveTexture(GL_TEXTURE1);
	glDisable(GL_TEXTURE_2D);
}


void Cube::setMatrix(Matrix4 temp) {
	model2world = temp;
}

Matrix4 Cube::getModelView() {
    return model2world;
}


void Cube::setTexture(GLuint tex[6]) {
    for (int i = 0; i < 6; i++) {
        texture[i] = tex[i];
    }
}