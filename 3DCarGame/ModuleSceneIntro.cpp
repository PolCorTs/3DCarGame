#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePhysics3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));
	App->audio->PlayMusic("audio/music.ogg");
	
	CreateMap();
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

void ModuleSceneIntro:: CreateMap() {

	CreateNormalFloor(10, ROAD_HEIGHT, 400.f, 0, 10, 10 /*ROAD_COLOR*/);
	CreateFan(0, 24, 30);

}

void ModuleSceneIntro::CreateNormalFloor(float width, float height, float large, float x, float y, float z, Color color)
{
	Cube ret(width, height, large);
	ret.SetPos(x, y, z);
	ret.color = color;

	road.add(ret);

	App->physics->AddBody(ret, 0);
}

void ModuleSceneIntro::CreateRamp(float width, float height, float large, float x, float y, float z, float degree, vec3 axis, Color color) {
	Cube ret(width, height, large);
	ret.SetPos(x, y, z);
	ret.color = color;
	ret.SetRotation(degree, axis);

	road.add(ret);

	App->physics->AddBody(ret, 0);
}

void ModuleSceneIntro::CreateGoal(float x, float y, float z, bool isgoal) {

	Cube ret(0.3f, 20, 20);
	ret.SetPos(x, y, z);

	SceneObjectType type;

	if (isgoal) {
		type = Goal;
	}
	else {
		type = LapSensor;
	}
	PhysBody3D* pbody = App->physics->AddBody(ret, 0, type);

	pbody->SetSensor();
	pbody->collision_listeners.add(this);
}

void ModuleSceneIntro::CreateFan(float x, float y, float z, Color color) {

	Cube c(1, 1, 1);
	c.SetPos(x, y, z);
	PhysBody3D* c_body = App->physics->AddBody(c, 0);

	Cube c2(0.1f, 9.5f, 1);
	c2.SetPos(x + 2, y, z);
	PhysBody3D* c2_body = App->physics->AddBody(c2, 1000, SceneObjectType::Floor);
	c2.color = Red;
	

	App->physics->AddConstraintHinge(*c_body, *c2_body, { 0,0,0 }, { 0,8,0 }, { 0,0,1 }, { 1,0,0 }, true);

	Fan bl(c, c2, c_body, c2_body);
	fan.add(bl);
}
