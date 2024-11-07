#include "../Tracers/RayCast.hpp"

void World::build(void) {
    vp.set_hres(200);
	vp.set_vres(200);
	vp.set_pixel_size(1);
	vp.set_gamma(1.0);
	vp.set_samples(1);

	Ambient* ambient_light = new Ambient();
	ambient_light->set_color(1, 1, 1);
	ambient_ptr = ambient_light;

	this->tracer_ptr = new RayCast(this);

	Matte* matte_ptr1 = new Matte;
	matte_ptr1->set_ambient_brdf(new Lambertian(1.0, RGBColor(0, 0, 1)));
	matte_ptr1->set_ka(1.0f);
	matte_ptr1->set_kd(1.0);
	
	background_color = black;
	Sphere* sphere_pt = new Sphere();
	sphere_pt->set_center(0);
	sphere_pt->set_radius(85);
	sphere_pt->set_material(matte_ptr1);
	add_object(dynamic_cast <GeometricObject*> (sphere_pt));
}