#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2
#define ROAD_COLOR Grey
#define BALL_COLOR Orange
#define FAN_COLOR Red
#define LIMIT_COLOR Green
#define ROAD_HEIGHT 0.1f

struct Fan {

	Fan() {}
	Fan(Cube c, Cube c2, PhysBody3D* bc, PhysBody3D* bc2) : cube(c), cube2(c2), body_cube(bc), body_cube2(bc2) {}

	Cube cube;
	Cube cube2;
	PhysBody3D* body_cube = nullptr;
	PhysBody3D* body_cube2 = nullptr;

};

struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void CreateMap();
	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);
	void CreateNormalFloor(float width, float height, float large, float x, float y, float z, Color color = ROAD_COLOR);
	void CreateRamp(float width, float height, float large, float x, float y, float z, float degree, vec3 axis, Color color = ROAD_COLOR);
	void CreateFan(float x, float y, float z, Color color = FAN_COLOR);
	void CreateGoal(float x, float y, float z, bool isgoal = false);
	void CreateLowerLimit(float width, float height, float large, float x, float y, float z, Color color = LIMIT_COLOR);


public:
	/*
	PhysBody3D* pb_snake[MAX_SNAKE];
	Sphere s_snake[MAX_SNAKE];

	PhysBody3D* pb_snake2[MAX_SNAKE];
	Sphere s_snake2[MAX_SNAKE];
	*/

	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;


	Cube dark_floor;
	p2List<Cube> road;
	p2List<Fan> fan;
};
