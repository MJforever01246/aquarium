#include<GL/glut.h>
#include<GL/freeglut_std.h>
class Camera {
public:
	bool is_holding_mouse = false;
	bool is_updated = false;
	float pos_x = 0, pos_y = -0, pos_z = -50;
	float x_old, y_old;
	float angle_y = 0, angle_x = 0;
	int current_scroll = 5;
	float zoom_per_scroll;

	void zoom(int button, int state, int x, int y) {
		is_updated = true;

		if (button == GLUT_LEFT_BUTTON) {
			if (state == GLUT_DOWN) {
				x_old = x;
				y_old = y;
				is_holding_mouse = true;
			}
			else
				is_holding_mouse = false;
		}
		else if (state == GLUT_UP) {
			switch (button) {
			case 3:
				if (current_scroll > 0) {
					current_scroll--;
					pos_z += zoom_per_scroll;
				}
				break;
			case 4:
				if (current_scroll < 150) {
					current_scroll++;
					pos_z -= zoom_per_scroll;
				}
				break;
			}
		}
	}

	void rotatef(int x, int y) {
		if (is_holding_mouse) {
			is_updated = true;

			angle_y += (x - x_old);
			x_old = x;
			if (angle_y > 360.0f)
				angle_y -= 360.0f;
			else if (angle_y < 0.0f)
				angle_y += 360.0f;

			angle_x += (y - y_old);
			y_old = y;
			if (angle_x > 90.0f)
				angle_x = 90.0f;
			else if (angle_x < 0.0f)
				angle_x = 0.0f;
		}
	}
};