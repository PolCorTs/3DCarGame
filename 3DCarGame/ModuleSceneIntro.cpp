#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePhysics3D.h"
#include "PhysVehicle3D.h"

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

	//dark_floor.Render();
	for (p2List_item<Cube>* item = road.getFirst(); item; item = item->next)
	{
		item->data.Render();
	}
	for (p2List_item<Fan>* item = fan.getFirst(); item; item = item->next)
	{
		btQuaternion quat = item->data.body_cube2->GetRotation();
		quat = quat.normalized();
		float angle = 2 * acos(quat.w()) * 180 / 3.14;
		float den = sqrt(1 - quat.w() *quat.w());
		item->data.cube2.SetRotation(angle, { quat.x() / den,quat.y() / den,quat.z() / den });
		item->data.cube2.SetPos(item->data.body_cube2->GetPos().x(), item->data.body_cube2->GetPos().y(), item->data.body_cube2->GetPos().z());
		item->data.cube2.Render();
	}
	
	if (App->player->vehicle->GetPosition().y < 9) {
		App->player->RespawnCar();
	}

	if (App->player->vehicle->GetPosition().z < -91) {
		App->player->Win();

	}
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{

}


void ModuleSceneIntro:: CreateMap() {

	CreateLowerLimit(1000, 1, 1000, 0, 9, 0,Black);
	//1st line
	CreateNormalFloor(10, ROAD_HEIGHT, 180.f, 0, 10, 80 ,ROAD_COLOR);
	CreateFan(0, 24, 30);

	CreateFan(0, 24, 50);
	CreateFan(0, 24, 70);

	CreateRamp(3, ROAD_HEIGHT, 10, 0, 10, 25, 90, { 1,0,0 }, BALL_COLOR); //center

	CreateRamp(3, ROAD_HEIGHT, 10, 3, 10, 60, 90, { 1,0,0 }, BALL_COLOR); //left
	CreateRamp(3, ROAD_HEIGHT, 10, -3, 10, 60, 90, { 1,0,0 }, BALL_COLOR); //right

	CreateRamp(3, ROAD_HEIGHT, 10, 0, 10,90, 90, { 1,0,0 }, BALL_COLOR); //center

	
	CreateRamp(5, ROAD_HEIGHT, 10, -3, 10, 110, -45, { 1,0,1 }, BALL_COLOR); //Right inclinated
	CreateRamp(5, ROAD_HEIGHT, 10, 3, 10, 110, 45, { 0,1,1 }, BALL_COLOR); //left inclinated
	
	CreateFan(0, 24, 130);
	
	CreateRamp(5, ROAD_HEIGHT, 10, -3, 10, 140, -45, { 1,0,1 }, BALL_COLOR); //Right inclinated
	CreateRamp(5, ROAD_HEIGHT, 10, 3, 10, 140, 45, { 0,1,1 }, BALL_COLOR); //left inclinated

	CreateFan(0, 24, 150);

	//2nd line
	CreateNormalFloor(190, ROAD_HEIGHT, 10, -90, 10, 175, ROAD_COLOR);

	CreateRamp(10, ROAD_HEIGHT, 3, -10, 10, 175, 90, { 0,0,1 }, BALL_COLOR); //center
	CreateRamp(10, ROAD_HEIGHT, 3,-25, 10, 178, 90, { 0,0,1 }, BALL_COLOR); //left
	CreateRamp(10, ROAD_HEIGHT, 3, -35, 10, 172, 90, { 0,0,1 }, BALL_COLOR); //right

	CreateRamp(10, ROAD_HEIGHT, 3, -42, 10, 175, 90, { 0,0,1 }, BALL_COLOR); //center
	CreateRamp(10, ROAD_HEIGHT, 3, -50, 10, 178, 90, { 0,0,1 }, BALL_COLOR); //left
	CreateRamp(10, ROAD_HEIGHT, 3, -54, 10, 172, 90, { 0,0,1 }, BALL_COLOR); //right

	CreateRamp(10, ROAD_HEIGHT, 3, -60, 10, 175, 90, { 0,0,1 }, BALL_COLOR); //center
	CreateRamp(10, ROAD_HEIGHT, 3, -68, 10, 178, 90, { 0,0,1 }, BALL_COLOR); //left
	CreateRamp(10, ROAD_HEIGHT, 3, -73, 10, 172, 90, { 0,0,1 }, BALL_COLOR); //right

	CreateRamp(10, ROAD_HEIGHT, 3, -78, 10, 175, 90, { 0,0,1 }, BALL_COLOR); //center
	CreateRamp(10, ROAD_HEIGHT, 3, -84, 10, 172, 90, { 0,0,1 }, BALL_COLOR); //right
	CreateRamp(10, ROAD_HEIGHT, 3, -90, 10, 178, 90, { 0,0,1 }, BALL_COLOR); //left
	
	CreateRamp(10, ROAD_HEIGHT, 3, -98, 10, 175, 90, { 0,0,1 }, BALL_COLOR); //center
	CreateRamp(10, ROAD_HEIGHT, 3, -104, 10, 172, 90, { 0,0,1 }, BALL_COLOR); //right
	CreateRamp(10, ROAD_HEIGHT, 3, -108, 10, 178, 90, { 0,0,1 }, BALL_COLOR); //left
	
	CreateRamp(10, ROAD_HEIGHT, 3, -114, 10, 172, 90, { 0,0,1 }, BALL_COLOR); //right
	CreateRamp(10, ROAD_HEIGHT, 3, -120, 10, 178, 90, { 0,0,1 }, BALL_COLOR); //left
	CreateRamp(10, ROAD_HEIGHT, 3, -128, 10, 175, 90, { 0,0,1 }, BALL_COLOR); //center
	
	CreateRamp(10, ROAD_HEIGHT, 3, -134, 10, 172, 90, { 0,0,1 }, BALL_COLOR); //right
	CreateRamp(10, ROAD_HEIGHT, 3, -140, 10, 178, 90, { 0,0,1 }, BALL_COLOR); //left
	CreateRamp(10, ROAD_HEIGHT, 3, -144, 10, 175, 90, { 0,0,1 }, BALL_COLOR); //center
	
	CreateRamp(10, ROAD_HEIGHT, 3, -150, 10, 175, 90, { 0,0,1 }, BALL_COLOR); //center
	CreateRamp(10, ROAD_HEIGHT, 3, -154, 10, 178, 90, { 0,0,1 }, BALL_COLOR); //left
	CreateRamp(10, ROAD_HEIGHT, 3, -159, 10, 172, 90, { 0,0,1 }, BALL_COLOR); //right

	CreateRamp(10, ROAD_HEIGHT, 3, -163, 10, 172, 90, { 0,0,1 }, BALL_COLOR); //right
	CreateRamp(10, ROAD_HEIGHT, 3, -167, 10, 178, 90, { 0,0,1 }, BALL_COLOR); //left
	CreateRamp(10, ROAD_HEIGHT, 3, -170, 10, 175, 90, { 0,0,1 }, BALL_COLOR); //center

	//3rd line
	CreateNormalFloor(10, ROAD_HEIGHT, 40.f, -180, 10, 160, ROAD_COLOR);
	CreateFan(-175, 24, 172);
	CreateRamp(3, ROAD_HEIGHT, 10, -180, 10, 170, 90, { 1,0,0 }, BALL_COLOR); //center
	CreateFan(-175, 24, 165);
	CreateRamp(3, ROAD_HEIGHT, 10, -180, 10, 160, 90, { 1,0,0 }, BALL_COLOR); //center
	CreateFan(-175, 24, 155);
	CreateRamp(3, ROAD_HEIGHT, 10, -180, 10, 150, 90, { 1,0,0 }, BALL_COLOR); //center
	
	 //4th line
	CreateNormalFloor(60, ROAD_HEIGHT, 10.f, -145, 10, 145, ROAD_COLOR);

	//5th line
	CreateNormalFloor(10, ROAD_HEIGHT, 60.f, -120, 10, 120, ROAD_COLOR);

	CreateRamp(3, ROAD_HEIGHT, 10, -120, 10, 130, 90, { 1,0,0 }, BALL_COLOR); //center
	CreateRamp(3, ROAD_HEIGHT, 10, -123, 10, 127, 90, { 1,0,0 }, BALL_COLOR); //right
	CreateFan(-115, 24, 125.5);
	CreateRamp(3, ROAD_HEIGHT, 10, -117, 10, 124, 90, { 1,0,0 }, BALL_COLOR); //left
	CreateRamp(3, ROAD_HEIGHT, 10, -120, 10, 121, 90, { 1,0,0 }, BALL_COLOR); //center
	CreateFan(-115, 24, 117);
	CreateRamp(3, ROAD_HEIGHT, 10, -123, 10, 115, 90, { 1,0,0 }, BALL_COLOR); //right
	CreateRamp(3, ROAD_HEIGHT, 10, -117, 10, 118, 90, { 1,0,0 }, BALL_COLOR); //left
	CreateFan(-115, 24, 113);
	CreateRamp(3, ROAD_HEIGHT, 10, -120, 10, 110, 90, { 1,0,0 }, BALL_COLOR); //center
	CreateFan(-115, 24, 107);


	//6th line
	CreateNormalFloor(60, ROAD_HEIGHT, 10.f, -145, 10, 85, ROAD_COLOR);

	//7th line
	CreateNormalFloor(10, ROAD_HEIGHT, 40.f, -180, 10, 70, ROAD_COLOR);

	CreateFan(-175, 24, 55);
	CreateRamp(3, ROAD_HEIGHT, 10, -180, 10, 60, 90, { 1,0,0 }, BALL_COLOR); //center
	CreateFan(-175, 24, 65);
	CreateRamp(3, ROAD_HEIGHT, 10, -180, 10, 70, 90, { 1,0,0 }, BALL_COLOR); //center
	CreateFan(-175, 24, 75);
	CreateRamp(3, ROAD_HEIGHT, 10, -180, 10, 80, 90, { 1,0,0 }, BALL_COLOR); //center
	CreateFan(-175, 24, 85);

	//8th line
	CreateNormalFloor(80, ROAD_HEIGHT, 10.f, -145, 10, 50, ROAD_COLOR);

	//9th line
	CreateNormalFloor(10, ROAD_HEIGHT, 160.f, -110, 10, -25, ROAD_COLOR);

	CreateFan(-105, 24, 41); 
	CreateRamp(3, ROAD_HEIGHT, 10, -113, 10, 39, 90, { 1,0,0 }, BALL_COLOR);
	CreateRamp(3, ROAD_HEIGHT, 10, -107, 10, 39, 90, { 1,0,0 }, BALL_COLOR);
	CreateFan(-105, 24, 37);
	CreateRamp(3, ROAD_HEIGHT, 10, -110, 10, 35, 90, { 1,0,0 }, BALL_COLOR);
	CreateFan(-105, 24, 33);
	CreateRamp(3, ROAD_HEIGHT, 10, -113, 10, 30, 90, { 1,0,0 }, BALL_COLOR);
	CreateRamp(3, ROAD_HEIGHT, 10, -107, 10, 30, 90, { 1,0,0 }, BALL_COLOR);
	CreateFan(-105, 24, 28);
	CreateRamp(3, ROAD_HEIGHT, 10, -110, 10, 26, 90, { 1,0,0 }, BALL_COLOR);
	CreateFan(-105, 24, 24);
	CreateRamp(3, ROAD_HEIGHT, 10, -113, 10, 22, 90, { 1,0,0 }, BALL_COLOR);
	CreateRamp(3, ROAD_HEIGHT, 10, -107, 10, 22, 90, { 1,0,0 }, BALL_COLOR);
	CreateRamp(3, ROAD_HEIGHT, 10, -110, 10, 18, 90, { 1,0,0 }, BALL_COLOR);
	CreateFan(-105, 24, 16);
	CreateRamp(3, ROAD_HEIGHT, 10, -107, 10, 14, 90, { 1,0,0 }, BALL_COLOR);
	CreateRamp(3, ROAD_HEIGHT, 10, -110, 10, 14, 90, { 1,0,0 }, BALL_COLOR);
	CreateFan(-105, 24, 10);
	CreateRamp(3, ROAD_HEIGHT, 10, -110, 10, 8, 90, { 1,0,0 }, BALL_COLOR);
	CreateFan(-105, 24, 6);
	CreateRamp(3, ROAD_HEIGHT, 10, -113, 10, 0, 90, { 1,0,0 }, BALL_COLOR);
	CreateRamp(3, ROAD_HEIGHT, 10, -107, 10, 0, 90, { 1,0,0 }, BALL_COLOR);
	CreateFan(-105, 24, -2);
	CreateFan(-105, 24, -4);
	CreateFan(-105, 24, -6);
	CreateRamp(3, ROAD_HEIGHT, 10, -113, 10, -8, 90, { 1,0,0 }, BALL_COLOR);
	CreateRamp(3, ROAD_HEIGHT, 10, -107, 10, -8, 90, { 1,0,0 }, BALL_COLOR);
	CreateFan(-105, 24, -12);
	CreateFan(-105, 24, -16);
	CreateRamp(3, ROAD_HEIGHT, 10, -110, 10, -20, 90, { 1,0,0 }, BALL_COLOR);
	CreateRamp(3, ROAD_HEIGHT, 10, -113, 10, -23, 90, { 1,0,0 }, BALL_COLOR);
	CreateRamp(3, ROAD_HEIGHT, 10, -107, 10, -23, 90, { 1,0,0 }, BALL_COLOR);
	
	CreateRamp(3, ROAD_HEIGHT, 10, -110, 10, -25, 90, { 1,0,0 }, BALL_COLOR); //center

	CreateFan(-105, 24, -27);
	CreateFan(-105, 24, -30);

	CreateRamp(3, ROAD_HEIGHT, 10, -110, 10, -33, 90, { 1,0,0 }, BALL_COLOR);
	CreateRamp(3, ROAD_HEIGHT, 10, -113, 10, -36, 90, { 1,0,0 }, BALL_COLOR);
	CreateRamp(3, ROAD_HEIGHT, 10, -107, 10, -39, 90, { 1,0,0 }, BALL_COLOR);

	CreateFan(-105, 24, -43);
	CreateFan(-105, 24, -46);
	CreateFan(-105, 24, -50);
	
	CreateRamp(3, ROAD_HEIGHT, 10, -113, 10, -53, 90, { 1,0,0 }, BALL_COLOR);
	CreateRamp(3, ROAD_HEIGHT, 10, -110, 10, -56, 90, { 1,0,0 }, BALL_COLOR);
	CreateRamp(3, ROAD_HEIGHT, 10, -107, 10, -60, 90, { 1,0,0 }, BALL_COLOR);
	CreateFan(-105, 24, -63);

	CreateRamp(3, ROAD_HEIGHT, 10, -110, 10, -68, 90, { 1,0,0 }, BALL_COLOR);
	CreateFan(-105, 24, -72);
	CreateFan(-105, 24, -75);
	CreateFan(-105, 24, -78);

	CreateRamp(3, ROAD_HEIGHT, 10, -113, 10, -82, 90, { 1,0,0 }, BALL_COLOR);
	CreateRamp(3, ROAD_HEIGHT, 10, -107, 10, -82, 90, { 1,0,0 }, BALL_COLOR);
	CreateRamp(3, ROAD_HEIGHT, 10, -113, 10, -84, 90, { 1,0,0 }, BALL_COLOR);
	CreateRamp(3, ROAD_HEIGHT, 10, -107, 10, -84, 90, { 1,0,0 }, BALL_COLOR);
	CreateRamp(3, ROAD_HEIGHT, 10, -113, 10, -86, 90, { 1,0,0 }, BALL_COLOR);
	CreateRamp(3, ROAD_HEIGHT, 10, -107, 10, -86, 90, { 1,0,0 }, BALL_COLOR);

	CreateGoal(-110, 20.5, -92, true);
}

void ModuleSceneIntro::CreateNormalFloor(float width, float height, float large, float x, float y, float z, Color color)
{
	Cube ret(width, height, large);
	ret.SetPos(x, y, z);
	ret.color = ROAD_COLOR;

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

void ModuleSceneIntro::CreateLowerLimit(float width, float height, float large, float x, float y, float z, Color color) {
	Cube ret(width, height, large);
	ret.SetPos(x, y, z);
	ret.color = LIMIT_COLOR;


	road.add(ret);

	//App->physics->AddBody(ret, 0, SceneObjectType::Floor);

	PhysBody3D* pbody = App->physics->AddBody(ret, 0, SceneObjectType::Floor);
	pbody->SetSensor();
	pbody->collision_listeners.add(this);
}

void ModuleSceneIntro::CreateGoal(float x, float y, float z, bool isgoal) {

	Cube ret(20, 20, 0.3f);
	ret.SetPos(x, y, z);
	ret.color = Green;
	road.add(ret);
	
	PhysBody3D* pbody = App->physics->AddBody(ret, 0, SceneObjectType::Goal);
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
	c2.color = color;
	

	App->physics->AddConstraintHinge(*c_body, *c2_body, { 0,0,0 }, { 0,8,0 }, { 0,0,1 }, { 1,0,0 }, true);

	Fan bl(c, c2, c_body, c2_body);
	fan.add(bl);
}
