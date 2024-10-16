#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#ifndef F_PI
#define F_PI		((float)(M_PI))
#define F_2_PI		((float)(2.f*F_PI))
#define F_PI_2		((float)(F_PI/2.f))
#endif


void
TrmptBell(float x_pos, float y_pos, float z_pos_s, float z_pos_e, int verticies, int thinness, float r, float g, float b) {
	glBegin(GL_TRIANGLES);
		glNormal3f(0, 0, 0);
		for (int i = 0; i < verticies; ++i) {
			float sinNum = sin(i * F_2_PI / verticies);
			float cosNum = cos(i * F_2_PI / verticies);
			float sinNumi1 = sin((1 + i) * F_2_PI / verticies);
			float cosNumi1 = cos((1 + i) * F_2_PI / verticies);

			glColor3f(r, g, b);
			glVertex3f(sinNum * 1.5f + x_pos, cosNum * 1.5f + y_pos, z_pos_s);
			glVertex3f(sinNum / (thinness * 2 / 4) + x_pos, cosNum / (thinness * 2 / 4) + y_pos, z_pos_e / 4);
			glVertex3f(sinNumi1 / (thinness * 2 / 4) + x_pos, cosNumi1 / (thinness * 2 / 4) + y_pos, z_pos_e / 4);

			glVertex3f(sinNum / (thinness * 2 / 4) + x_pos, cosNum / (thinness * 2 / 4) + y_pos, z_pos_e / 4);
			glVertex3f(sinNum / thinness + x_pos, cosNum / thinness + y_pos, z_pos_e);
			glVertex3f(sinNumi1 / thinness + x_pos, cosNumi1 / thinness + y_pos, z_pos_e);

			glColor3f(r, g, b);
			glVertex3f(sinNum * 1.5f + x_pos, cosNum * 1.5f + y_pos, z_pos_s);
			glVertex3f(sinNumi1 / (thinness * 2 / 4) + x_pos, cosNumi1 / (thinness * 2 / 4) + y_pos, z_pos_e / 4);
			glVertex3f(sinNumi1 * 1.5f + x_pos, cosNumi1 * 1.5f + y_pos, z_pos_s);

			glVertex3f(sinNum / (thinness * 2 / 4) + x_pos, cosNum / (thinness * 2 / 4) + y_pos, z_pos_e / 4);
			glVertex3f(sinNumi1 / thinness + x_pos, cosNumi1 / thinness + y_pos, z_pos_e);
			glVertex3f(sinNumi1 / (thinness * 2 / 4) + x_pos, cosNumi1 / (thinness * 2 / 4) + y_pos, z_pos_e / 4);
		}
	glEnd();
}

void
TrmptTubeXY(float x_pos, float y_pos, float z_pos_s, float z_pos_e, int verticies, int thinness, float r, float g, float b) {
	glBegin(GL_TRIANGLES);
		glNormal3f(0, 0, 0);
		for (int i = 0; i < verticies; ++i) {
			float sinNum = sin(i * F_2_PI / verticies) / thinness + x_pos;
			float cosNum = cos(i * F_2_PI / verticies) / thinness + y_pos;
			float sinNumi1 = sin((1 + i) * F_2_PI / verticies) / thinness + x_pos;
			float cosNumi1 = cos((1 + i) * F_2_PI / verticies) / thinness + y_pos;

			glColor3f(r, g, b);
			glVertex3f(sinNum, cosNum, z_pos_s);
			glVertex3f(sinNum, cosNum, z_pos_e);
			glVertex3f(sinNumi1, cosNumi1, z_pos_e);

			glColor3f(r, g, b);
			glVertex3f(sinNum, cosNum, z_pos_s);
			glVertex3f(sinNumi1, cosNumi1, z_pos_e);
			glVertex3f(sinNumi1, cosNumi1, z_pos_s);
		}
	glEnd();
}

void
TrmptTubeXZ(float x_pos, float y_pos_s, float y_pos_e, float z_pos, int verticies, int thinness, float r, float g, float b) {
	glBegin(GL_TRIANGLES);
		glNormal3f(0, 0, 0);
		for (int i = 0; i < verticies; ++i) {
			float sinNum = sin(i * F_2_PI / verticies) / thinness + x_pos;
			float cosNum = cos(i * F_2_PI / verticies) / thinness + z_pos;
			float sinNumi1 = sin((1 + i) * F_2_PI / verticies) / thinness + x_pos;
			float cosNumi1 = cos((1 + i) * F_2_PI / verticies) / thinness + z_pos;

			glColor3f(r, g, b);
			glVertex3f(sinNum, y_pos_s, cosNum);
			glVertex3f(sinNum, y_pos_e, cosNum);
			glVertex3f(sinNumi1, y_pos_e, cosNumi1);

			glColor3f(r, g, b);
			glVertex3f(sinNum, y_pos_s, cosNum);
			glVertex3f(sinNumi1, y_pos_e, cosNumi1);
			glVertex3f(sinNumi1, y_pos_s, cosNumi1);
		}
	glEnd();
}

// Modified OSUtorus to get this result
void
TrmptTubeCurve(float innerRadius, float outerRadius, int nsides, int nrings, float r, float g, float b) {
	float ringDelta = F_PI / (float)nrings;
	float sideDelta = 2.0 * F_PI / (float)nsides;

	float theta = 0.0;
	float cosTheta = 1.0;
	float sinTheta = 0.0;

	for (int i = 0; i < nrings; i++)
	{
		float theta1 = theta + ringDelta;
		float cosTheta1 = cosf(theta1);
		float sinTheta1 = sinf(theta1);

		float phi = 0.0;
		float s0 = 1.f - (float)(i + 0) / (float)nrings;
		float s1 = 1.f - (float)(i + 1) / (float)nrings;

		glBegin(GL_TRIANGLE_STRIP);

		for (int j = 0; j <= nsides; j++)
		{
			float cosPhi = cosf(phi);
			float sinPhi = sinf(phi);
			float dist = outerRadius + innerRadius * cosPhi;

			float t = 1.f - (float)j / (float)nsides;

			glTexCoord2f(s0, t);
			glNormal3f(cosTheta * cosPhi, sinPhi, -sinTheta * cosPhi);
			glColor3f(r, g, b);
			glVertex3f(cosTheta * dist, innerRadius * sinPhi, -sinTheta * dist);

			glTexCoord2f(s1, t);
			glNormal3f(cosTheta1 * cosPhi, sinPhi, -sinTheta1 * cosPhi);
			glColor3f(r, g, b);
			glVertex3f(cosTheta1 * dist, innerRadius * sinPhi, -sinTheta1 * dist);

			phi += sideDelta;
		}

		glEnd();

		theta = theta1;
		cosTheta = cosTheta1;
		sinTheta = sinTheta1;
	}
}

// Modified OSUtorus to get this result
void
TrmptTubeCurveQuarter(float innerRadius, float outerRadius, int nsides, int nrings, float r, float g, float b) {
	float ringDelta = F_PI / 2 / (float)nrings;
	float sideDelta = 2.0 * F_PI / (float)nsides;

	float theta = 0.0;
	float cosTheta = 1.0;
	float sinTheta = 0.0;

	for (int i = 0; i < nrings; i++)
	{
		float theta1 = theta + ringDelta;
		float cosTheta1 = cosf(theta1);
		float sinTheta1 = sinf(theta1);

		float phi = 0.0;
		float s0 = 1.f - (float)(i + 0) / (float)nrings;
		float s1 = 1.f - (float)(i + 1) / (float)nrings;

		glBegin(GL_TRIANGLE_STRIP);

		for (int j = 0; j <= nsides; j++)
		{
			float cosPhi = cosf(phi);
			float sinPhi = sinf(phi);
			float dist = outerRadius + innerRadius * cosPhi;

			float t = 1.f - (float)j / (float)nsides;

			glTexCoord2f(s0, t);
			glNormal3f(cosTheta * cosPhi, sinPhi, -sinTheta * cosPhi);
			glColor3f(r, g, b);
			glVertex3f(cosTheta * dist, innerRadius * sinPhi, -sinTheta * dist);

			glTexCoord2f(s1, t);
			glNormal3f(cosTheta1 * cosPhi, sinPhi, -sinTheta1 * cosPhi);
			glColor3f(r, g, b);
			glVertex3f(cosTheta1 * dist, innerRadius * sinPhi, -sinTheta1 * dist);

			phi += sideDelta;
		}

		glEnd();

		theta = theta1;
		cosTheta = cosTheta1;
		sinTheta = sinTheta1;
	}
}
