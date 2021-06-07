#include "Library/main.h"
#include "Fish.cpp"
#include "Rock.cpp"
#include "Plant.cpp"
#include "Camera.cpp"
#include<vector>

int POS_X, POS_Y;
std::string fish1 = "Models/fish1.obj";
std::string fish2 = "Models/fish2.obj";
std::string fish3 = "Models/fish3.obj";
std::string fish4 = "Models/fish4.obj";
std::string grass = "Models/grass.obj";
std::string ground = "Models/ground.obj";
std::string rock_path = "Models/rock.obj";

std::vector<std::string> renderable = { "Models/fish1.obj" ,"Models/fish2.obj","Models/fish3.obj","Models/fish4.obj", "Models/grass.obj","Models/rock.obj" };

bool stop = false;
bool disable_fog = false;
bool light0_off = false;

Model model_fish1, model_fish2, model_fish3, model_fish4, model_grass, model_ground, model_rock;
Fish fish;
Rock rock;
Plant plant;
Camera camera;

void init() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, 1.0, 5.0, 300.0);
	

	// blue green background colour
	glClearColor(0.0, 0.5, 0.5, 1.0);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat light_pos[] = { 0.0f, 1.0, 1.0f, 0.0f };

	glFogi(GL_FOG_MODE, GL_EXP);
	GLfloat fogColor[4] = { 0.0f, 0.5f, 0.5f, 1.0f };
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, 0.0075);
	glHint(GL_FOG_HINT, GL_NICEST);
	glEnable(GL_FOG);


	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	model_fish1.load(fish1.c_str());
	model_fish2.load(fish2.c_str());
	model_fish3.load(fish3.c_str());
	model_fish4.load(fish4.c_str());
	model_rock.load(rock_path.c_str());
	model_grass.load(grass.c_str());
	model_ground.load(ground.c_str());
	camera.zoom_per_scroll = -model_ground.pos_z / 500.0f;
	rock.show(10);
	plant.show(10);
	fish.show(50);
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();	
	glTranslatef(camera.pos_x, camera.pos_y, camera.pos_z);
	glRotatef(camera.angle_x, 1.0f, 0.0f, 0.0f);
	glRotatef(camera.angle_y, 0.0f, 1.0f, 0.0f);
	model_ground.draw();

	//phần trên là hệ tọa độ gốc
	glPushMatrix();


	for (int i = 0; i < plant.count; i++)
	{
		glPushMatrix();
		glTranslatef(plant.X[i], plant.Y[i], plant.Z[i]);
		model_grass.draw();
		glPopMatrix();
	}

	for (int i = 0; i < rock.count; i++)
	{
		glPushMatrix();
		glTranslatef(rock.X[i], rock.Y[i], rock.Z[i]);
		model_rock.draw();
		glPopMatrix();
	}

	for (int i = 0; i < fish.count; i += 1)
	{
		glPushMatrix();

		if (!stop)
			fish.angle[i] += fish.angle_step[i];

		glRotatef(fish.angle[i], 0, 1, 0);
		glTranslatef(fish.X[i], fish.Y[i], 0);

		if (fish.type[i] == 0)
			model_fish1.draw();
		if (fish.type[i] == 1)
			model_fish2.draw();
		if (fish.type[i] == 2)
			model_fish3.draw();
		if (fish.type[i] == 3)
			model_fish4.draw();
		glPopMatrix();
	}
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case '1':
		fish.add(); break;
	case '2':
		fish.remove(); break;
	case '3':
		plant.add(); break;
	case '4':
		plant.remove(); break;
	case '5':
		rock.add(); break;
	case '6':
		rock.remove(); break;
	case 'u':
		for (int i = 0; i < fish.count; i++)
			if (fish.angle_step[i] + 0.02*fish.direction[i] < 5)
				fish.angle_step[i] += 0.02*fish.direction[i];
		break;
	case 'd':
		for (int i = 0; i < fish.count; i++)
			if (fish.angle_step[i] - 0.02*fish.direction[i] > 0.01)
				fish.angle_step[i] -= 0.02*fish.direction[i];
		break;
	case 's':
		stop = !stop; break;
	case 'f':
		disable_fog = !disable_fog;

		if (disable_fog)
			glDisable(GL_FOG);
		else
			glEnable(GL_FOG); break;
	case 'l':
		light0_off = !light0_off;
		if (light0_off)
			glDisable(GL_LIGHT0);
		else
			glEnable(GL_LIGHT0);
	default:
		break;
	}
}

void timer(int value) {
	if (camera.is_updated) {
		camera.is_updated = false;
		glutPostRedisplay();
	}
	glutTimerFunc(INTERVAL, timer, 0);
}

void mouse(int button, int state, int x, int y) {
	camera.zoom(button, state, x, y);
}

void motion(int x, int y) {
	camera.rotatef(x,y);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutSetOption(GLUT_MULTISAMPLE, 8);
	POS_X = (glutGet(GLUT_SCREEN_WIDTH) - WIDTH) >> 1;
	POS_Y = (glutGet(GLUT_SCREEN_HEIGHT) - HEIGHT) >> 1;
	glutInitWindowPosition(POS_X, POS_Y);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Load Model");
	init();
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMotionFunc(motion);
	glutTimerFunc(0, timer, 0);
	glutMainLoop();
	return 0;
}
