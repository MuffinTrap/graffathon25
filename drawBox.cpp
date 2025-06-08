#include <mgdl.h>

static void Quad(vec3& a, const vec3& b, const vec3& c, const vec3& d, const::vec3& normal)
{
	// bottom
	glNormal3f(normal.x, normal.y, normal.z);
	glVertex3f(a.x, a.y, a.z);

	// bottom2
	glNormal3f(normal.x, normal.y, normal.z);
	glVertex3f(d.x, d.y, d.z);

	// top 1 and 2
	glNormal3f(normal.x, normal.y, normal.z);
	glVertex3f(c.x, c.y, c.z);

	glNormal3f(normal.x, normal.y, normal.z);
	glVertex3f(b.x, b.y, b.z);
}

void SolidCube(float size)
{
    float hs = size/2.0f;
	vec3 bl = V3f_Create(-hs, -hs, -hs);
	vec3 br = V3f_Create(hs, -hs, -hs);
	vec3 fl = V3f_Create(-hs, -hs, hs);
	vec3 fr = V3f_Create(hs, -hs, hs);

	vec3 tbl = V3f_Create(-hs, hs, -hs);
	vec3 tbr = V3f_Create(hs, hs, -hs);
	vec3 tfl = V3f_Create(-hs, hs, hs);
	vec3 tfr = V3f_Create(hs, hs, hs);

	vec3 R = V3f_Create(1.0f, 0.0f, 0.0f);
	vec3 U = V3f_Create(0.0f, 1.0f, 0.0f);
	vec3 F = V3f_Create(0.0f, 0.0f, 1.0f);

	vec3 nR;
	V3f_Copy(R, nR);

	vec3 nL;
	V3f_Copy(R, nL);
	V3f_Scale(nL, -1.0f, nL);

	vec3 nF = V3f_Create(0.0f, 0.0f, 1.0f);

	vec3 nB;
	V3f_Copy(F, nB); V3f_Scale(nB, -1.0f, nB);

	glBegin(GL_QUADS);
		// left side ok
		Quad(bl, tbl, tfl, fl, nL);
		// Quad(fl, tfl, tbl, bl, nL);
		// front ok
		// Quad(fl, tfl, tfr, fr, nF);
		Quad(fr, tfr, tfl, fl, nF);
		// right ok
		 Quad(fr, tfr, tbr, br, nR);
		// back ??
		 Quad(br, tbr, tbl, bl, nB);

		// top OK
		 Quad(tfl, tbl, tbr, tfr, U);

	glEnd();
}
