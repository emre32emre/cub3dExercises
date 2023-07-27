#include "fdf.h"
#include <math.h>
#define screenWidth 640
#define screenHeight 480
#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

double posX = 22, posY = 12;  //x and y start position
double dirX = -1, dirY = 0; //initial direction vector
double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
double time = 0; //time of current frame
double oldTime = 0; //time of previous frame


static void			clear_frame(t_scene *scene);
void my_mlx_pixel_put(t_scene *scene,int x, int y, int color)
{
	char *dst;

	dst = scene->frame_buf + (y * scene->line_bytes + x * (scene->pixel_bits / 8));
	*(unsigned int*)dst = color;
}
void drawLine(int x1, int x2, int y1, int y2, t_scene *scene)
//void drawLine(t_vector *vec1, t_vector *vec2, t_scene *scene)
{
	int dx, dy, i, e;
	int incx,incy,inc1,inc2;
	int x, y;

	dx = x2 - x1;
	dy = y2 - y1;
	// dx = x2 - x1;
	// dy = y2 - y1;

	if (dx < 0) dx = -dx;
	if (dy < 0) dy = -dy;
	incx = 1;
	if (x2 < x1) incx = -1;
	//if (x2 < x1) incx = -1;
	incy = 1;
	if (y2 < y1) incy = -1;
	//if (y2 < y1) incy = -1;
	x = x1;
	y = y1;
	// x = x1;
	// y = y1;
	if (dx > dy)
	{
		my_mlx_pixel_put(scene, x, y, scene->color);
		e = 2 * dy - dx;
		inc1 = 2*(dy-dx);
		inc2 = 2*dy;
		for(i = 0;i<dx;i++)
		{
			if(e >= 0)
			{
				y += incy;
				e += inc1;
			}
			else
			{
				e += inc2;
			}
			x += incx;
			my_mlx_pixel_put(scene, x, y, scene->color);
		}
	}
	else
	{
		my_mlx_pixel_put(scene, x, y, scene->color);
		e = 2 *dx-dy;
		inc1 = 2*(dx-dy);
		inc2 = 2*dx;
		for(i = 0;i<dy;i++)
		{
			if(e >= 0)
			{
				x+= incx;
				e += inc1;
			}
			else
			{
				e += inc2;
			}
			y += incy;
			my_mlx_pixel_put(scene, x, y, scene->color);
		}
	}
}

int				handle_loop(void *params)
{
	t_scene		*scene;

	scene = (t_scene*)params;
	for(int x = 0; x < WIDTH; x++)
    {
		double cameraX = 2 * x / (double)WIDTH - 1; //x-coordinate in camera space
    	double rayDirX = dirX + planeX * cameraX;
    	double rayDirY = dirY + planeY * cameraX;
		
		int mapX = posX;
		int mapY = posY;

		double sideDistX;
    	double sideDistY;

		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
    	double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

		double perpWallDist;
    	int stepX;
    	int stepY;
 		int hit = 0; //was there a wall hit?
    	int side; //was a NS or a EW wall hit?
    	//calculate step and initial sideDist
    	if(rayDirX < 0)
    	{
    	  stepX = -1;
    	  sideDistX = (posX - mapX) * deltaDistX;
    	}
    	else
    	{
    	  stepX = 1;
    	  sideDistX = (mapX + 1.0 - posX) * deltaDistX;
    	}
    	if(rayDirY < 0)
    	{
    	  stepY = -1;
    	  sideDistY = (posY - mapY) * deltaDistY;
    	}
    	else
    	{
    	  stepY = 1;
    	  sideDistY = (mapY + 1.0 - posY) * deltaDistY;
    	}
    	while(hit == 0)
    	{
    	  //jump to next map square, either in x-direction, or in y-direction
    	  if(sideDistX < sideDistY)
    	  {
    	    sideDistX += deltaDistX;
    	    mapX += stepX;
    	    side = 0;
    	  }
    	  else
    	  {
    	    sideDistY += deltaDistY;
    	    mapY += stepY;
    	    side = 1;
    	  }
    	  //Check if ray has hit a wall
    	  if(worldMap[mapX][mapY] > 0) hit = 1;
    	}
    	if(side == 0) perpWallDist = (sideDistX - deltaDistX);
    	else          perpWallDist = (sideDistY - deltaDistY);	

    	int lineHeight = (int)(HEIGHT / perpWallDist);	
    	//calculate lowest and highest pixel to fill in current stripe
    	int drawStart = -lineHeight / 2 + HEIGHT / 2;
    	if(drawStart < 0) drawStart = 0;
    	int drawEnd = lineHeight / 2 + HEIGHT / 2;
    	if(drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;
		switch(worldMap[mapX][mapY])
    	{
    	  case 1:  scene->color = 0xED1405;    break; //red
    	  case 2:  scene->color = 0x28ed05;  break; //green
    	  case 3:  scene->color = 0x1900ff;   break; //blue
    	  case 4:  scene->color = 0xffffff;  break; //white
    	  default: scene->color = 0xeeff00; break; //yellow
    	}
	  
		drawLine(x,x,drawStart,drawEnd,scene);

	
	}

	double moveSpeed = 0.2; //the constant value is in squares/second
    double rotSpeed = 0.04; //the constant value is in radians/second
	
    if(scene->key_w)
    {
      if(worldMap[(int)(posX + dirX * moveSpeed)][(int)(posY)] == 0) posX += dirX * moveSpeed;
      if(worldMap[(int)(posX)][(int)(posY + dirY * moveSpeed)] == 0) posY += dirY * moveSpeed;
	
	}
	if(scene->key_s)
    {
      if(worldMap[(int)(posX - dirX * moveSpeed)][(int)(posY)] == false) posX -= dirX * moveSpeed;
      if(worldMap[(int)(posX)][(int)(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
    }
    if(scene->key_d)
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = dirX;
      dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
      dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
      double oldPlaneX = planeX;
      planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
      planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
    }
    if(scene->key_a)
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = dirX;
      dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
      dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
      double oldPlaneX = planeX;
      planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
      planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
    }

	mlx_clear_window(scene->mlx, scene->mlx_wdw);
	mlx_put_image_to_window(scene->mlx,scene->mlx_wdw,scene->frame,0,0);
	draw_ui(scene);
	clear_frame(scene);

	//draw(scene);
	return (0);
}


static void			clear_frame(t_scene *scene)
{
	int		x;
	int		y;
	int		pixel;



	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixel = y * scene->line_bytes + x * 4;
			scene->frame_buf[pixel] = 00;
			scene->frame_buf[pixel + 1] = 00;
			scene->frame_buf[pixel + 2] = 00;
			scene->frame_buf[pixel + 3] = 00;
			x++;
		}
		y++;
	}
}