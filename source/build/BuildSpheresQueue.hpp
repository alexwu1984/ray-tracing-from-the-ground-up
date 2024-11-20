void World::build(){
    int number_sampes = 16;
    vp.set_vres(800);
    vp.set_hres(800);
    vp.set_pixel_size(0.1);
    vp.set_sampler(new MultiJittered(number_sampes));
    vp.set_max_depth(0);

    background_color = RGBColor(1);

	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.5);
	set_ambient_light(ambient_ptr);

    tracer_ptr = new RayCast(this);

    ThinLens* thin = new ThinLens(Point3D(0, 6, 50), Point3D(0, 6,50));
    thin->set_sampler(new MultiJittered(number_sampes));
    thin->set_view_distance(40.0);
    thin->set_focal_dist(70.0);
    thin->set_lens_radius(1.0);
    thin->compute_uvw();
    camera = thin;

    //Plane* plane_pt = new Plane(Point3D(0), Normal(0, 1, 0));
    //plane_pt->set_color(RGBColor(0));
    //add_object(plane_pt);

	PointLight* point_light = new PointLight(Vector3D(10, 20, 3), 6);
	add_light(point_light);

    Sphere* sphere_pt;
    for(int i = 0; i < 3; i++){
        sphere_pt = new Sphere(Point3D(-150 + i*i*200, 0, -80-140*i), 60);

		Phong* matte_ptr = new Phong;
		matte_ptr->set_ka(0.25);
		matte_ptr->set_kd(0.75);
		matte_ptr->set_ks(0.5);
        RGBColor c = RGBColor(rand_float(), rand_float(), rand_float());
		matte_ptr->set_cd(c);

        sphere_pt->set_material(matte_ptr);
        add_object(sphere_pt);
    }
}