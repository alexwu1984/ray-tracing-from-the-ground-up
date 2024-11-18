#include "../Tracers/RayCast.hpp"

void World::build(void) {
	vp.set_hres(300);
	vp.set_vres(300);
	vp.set_pixel_size(1.0);
	vp.set_sampler(new NRooks(16));

	Ambient* ambient_light = new Ambient();
	ambient_light->set_color(1, 1, 1);
	ambient_ptr = ambient_light;

	//tracer_ptr = new MultipleObjects(this); 
	
	background_color = black;
	tracer_ptr = new RayCast(this);
	
	// use access functions to set centre and radius

	Matte* matte_ptr1 = new Matte;
	matte_ptr1->set_ambient_brdf(new Lambertian(1.0, RGBColor(1, 0, 0)));
	matte_ptr1->set_ka(1.0f);
	matte_ptr1->set_kd(1.0);
	
	Sphere* sphere_ptr = new Sphere();
	sphere_ptr->set_center(0, -25, 0);
	sphere_ptr->set_radius(80);
	sphere_ptr->set_material(matte_ptr1);  // red
	add_object(sphere_ptr);

	// use constructor to set centre and radius 
	Matte* matte_ptr2 = new Matte;
	matte_ptr2->set_ambient_brdf(new Lambertian(1.0, RGBColor(1, 1, 0)));
	matte_ptr2->set_ka(1.0f);
	matte_ptr2->set_kd(1.0);

	sphere_ptr = new Sphere(Point3D(0, 30, 0), 400);
	sphere_ptr->set_material(matte_ptr2);	// yellow
	add_object(sphere_ptr);
	
	Matte* matte_ptr3 = new Matte;
	matte_ptr3->set_ambient_brdf(new Lambertian(1.0, RGBColor(0.0, 0.3, 0.0)));
	matte_ptr3->set_ka(1.0f);
	matte_ptr3->set_kd(1.0);

	Plane* plane_ptr = new Plane(Point3D(0), Normal(0, 1, 1));
	plane_ptr->set_material(matte_ptr3);	// dark green
	add_object(plane_ptr);
}