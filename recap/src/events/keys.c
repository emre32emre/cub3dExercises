#include "fdf.h"

int				handle_key_press(int key, void *param)
{
    t_scene *scene;
    scene = (t_scene *)param;
    if (key == KEY_ESC)
		exit(0);
    if (key == KEY_W) {
		scene->key_w = true;
	} 
    
    if (key == KEY_A) {
		scene->key_a = true;
	}
    
    if (key == KEY_S) {
		scene->key_s = true;
	}
    
    if (key == KEY_D) {
		scene->key_d = true;
	}
 return (1);
}
int				handle_key_release(int key, void *param)
{
    t_scene *scene;
    scene = (t_scene *)param;
    if (key == KEY_ESC)
		exit(0);
    if (key == KEY_W) {
		scene->key_w = false;
	} 
    
    if (key == KEY_A) {
		scene->key_a = false;
	}
    
    if (key == KEY_S) {
		scene->key_s = false;
	}
    
    if (key == KEY_D) {
		scene->key_d = false;
	}

  return (1);
}