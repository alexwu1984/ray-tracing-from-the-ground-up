#include "../Tracers/RayCast.hpp"
#include "../Cameras/Perspective.hpp"

void World::build(void) {
	int num_samples = 16;

	vp.set_hres(400);
	vp.set_vres(400);
	vp.set_samples(num_samples);

	tracer_ptr = new RayCast(this);

	Perspective* perspective_ptr = new Perspective;
	perspective_ptr->set_eye(25, 20, -45);
	perspective_ptr->set_lookat(0, 1, 0);
	perspective_ptr->set_view_distance(5000);
	perspective_ptr->compute_uvw();
	set_camera(perspective_ptr);

	Ambient* ambient_light = new Ambient();
	ambient_light->set_color(1, 1, 1);
	ambient_ptr = ambient_light;

	//tracer_ptr = new MultipleObjects(this); 
	
	background_color = black;
	
	// sphere

	Matte* matte_ptr1 = new Matte;
	matte_ptr1->set_ka(0.8);
	matte_ptr1->set_kd(0.0);
	matte_ptr1->set_cd(1, 1, 0);   // yellow

	Sphere* sphere_ptr = new Sphere(Point3D(0, 1, 0), 1);
	sphere_ptr->set_material(matte_ptr1);
	add_object(sphere_ptr);

	// ground plane

	Matte* matte_ptr2 = new Matte;
	matte_ptr2->set_ka(0.75);
	matte_ptr2->set_kd(0);
	matte_ptr2->set_cd(white);

	Plane* plane_ptr = new Plane(Point3D(0), Normal(0, 1, 0));
	plane_ptr->set_material(matte_ptr2);
	add_object(plane_ptr);
}