#pragma once

void World::build(){
	int num_samples = 16;

	vp.set_hres(400);
	vp.set_vres(400);
	vp.set_pixel_size(0.5);
	vp.set_sampler(new Jittered(num_samples));  

	background_color = white;
	tracer_ptr = new RayCast(this);	
	
	//Pinhole* pinhole_ptr = new Pinhole;
	//pinhole_ptr->set_eye(Point3D(0, 0, 100));
	//pinhole_ptr->set_lookat(Point3D(0.0));   
	//pinhole_ptr->set_distance(150);	
	//pinhole_ptr->compute_uvw(); 
 //   camera = pinhole_ptr;

	ThinLens* thin_len = new ThinLens(Point3D(0, 0, 100), Point3D(0, 0, -100));
	thin_len->set_sampler(new Jittered(100));
	thin_len->set_view_distance(150);
	thin_len->set_focal_dist(180);
	thin_len->set_up(Vector3D(0, 1, 0));
	thin_len->set_lens_radius(1.0);
	thin_len->compute_uvw();
	camera = thin_len;

	Ambient* ambient_light = new Ambient();
	ambient_light->set_color(1.0f);
	ambient_ptr = ambient_light;

	PointLight* light = new PointLight(Vector3D(100, 50, 150), 3.0);
	light->set_shadows(true);
	add_light(light);

	// colors

	RGBColor yellow(1, 1, 0);										// yellow
	RGBColor brown(0.71, 0.40, 0.16);								// brown
	RGBColor dark_green(0.0, 0.41, 0.41);							// dark_green
	RGBColor orange(1, 0.75, 0);									// orange
	RGBColor green(0, 0.6, 0.3);									// green
	RGBColor light_green(0.65, 1, 0.30);							// light green
	RGBColor dark_yellow(0.61, 0.61, 0);							// dark yellow
	RGBColor light_purple(0.65, 0.3, 1);							// light purple
	RGBColor dark_purple(0.5, 0, 1);								// dark purple
	
	
	// Matt material reflection coefficients
	
	float ka = 0.25;
	float kd = 0.75;
		
	// spheres
	Matte* matte_ptr1 = new Matte;
	
	matte_ptr1->set_ka(ka);
	
	matte_ptr1->set_kd(kd);

	matte_ptr1->set_cd(yellow);				
	
	Sphere*	sphere_ptr1 = new Sphere(Point3D(5, 3, 0), 30); 
	sphere_ptr1->set_material(matte_ptr1);	   							// yellow
	add_object(sphere_ptr1);
	

	Matte* matte_ptr2 = new Matte;
	matte_ptr2->set_ka(ka);	
	matte_ptr2->set_kd(kd);
	matte_ptr2->set_cd(brown);
	Sphere*	sphere_ptr2 = new Sphere(Point3D(45, -7, -10), 20); 
	sphere_ptr2->set_material(matte_ptr2);								// brown
	add_object(sphere_ptr2);
	

	Matte* matte_ptr3 = new Matte;
	matte_ptr3->set_ka(ka);	
	matte_ptr3->set_kd(kd);
	matte_ptr3->set_cd(dark_green);	
	Sphere*	sphere_ptr3 = new Sphere(Point3D(40, 43, -20), 17); 
	sphere_ptr3->set_material(matte_ptr3);								// dark green
	add_object(sphere_ptr3);
	
	Matte* matte_ptr4 = new Matte;
	matte_ptr4->set_ka(ka);	
	matte_ptr4->set_kd(kd);
	matte_ptr4->set_cd(orange);
	Sphere*	sphere_ptr4 = new Sphere(Point3D(-20, 28, -35), 20); 
	sphere_ptr4->set_material(matte_ptr4);								// orange
	add_object(sphere_ptr4);
	
	Matte* matte_ptr5 = new Matte;
	matte_ptr5->set_ka(ka);	
	matte_ptr5->set_kd(kd);
	matte_ptr5->set_cd(green);
	Sphere*	sphere_ptr5 = new Sphere(Point3D(-25, -7, -45), 27); 			
	sphere_ptr5->set_material(matte_ptr5);								// green
	add_object(sphere_ptr5);
	
}