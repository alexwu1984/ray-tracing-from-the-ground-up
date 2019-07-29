#include "World.hpp"
#include "../Utilities/Constants.hpp"

// geometric objects
#include "../GeometricObjects/Plane.hpp"
#include "../GeometricObjects/Sphere.hpp"

// tracers
#include "../Tracers/SingleSphere.hpp"
#include "../Tracers/MultipleObjects.hpp"

// utilities
#include "../Utilities/Vector3D.hpp"
#include "../Utilities/Point3D.hpp"
#include "../Utilities/Normal.hpp"
#include "../Utilities/ShadeRec.hpp"
#include "../Utilities/Maths.hpp"

// build functions
#include "../build/BuildSingleSphere.cpp"
//#include "BuildMultipleObjects.cpp"
//#include "BuildBBCoverPic.cpp"

World::World(void)
	:  	background_color(black),
		tracer_ptr(NULL),
		window(NULL)
{}

World::~World(void) {		
	if(tracer_ptr) {
		delete tracer_ptr;
		tracer_ptr = NULL;
	}	
	if(window){
		window->close();
		delete window;
		window = NULL;
	}
	delete_objects();	
}

// This uses orthographic viewing along the zw axis
void World::render_scene(void) const {
	RGBColor	pixel_color;	 	
	Ray			ray;					
	int 		hres 	= vp.hres;
	int 		vres 	= vp.vres;
	float		s		= vp.s;
	float		zw		= 100.0;			// hardwired in
	
	window = new Window(vres, hres);
	ray.d = Vector3D(0, 0, -1);
	
	for (int r = 0; r < vres && !window->shouldClose(); r++)			// up
		for (int c = 0; c <= hres && !window->shouldClose(); c++) {		// across 					
			ray.o = Point3D(s * (c - hres / 2.0 + 0.5), s * (r - vres / 2.0 + 0.5), zw);
			pixel_color = tracer_ptr->trace_ray(ray);
			display_pixel(r, c, pixel_color);
		}	
	while(!window->shouldClose()){ // wait }
}  

RGBColor World::max_to_one(const RGBColor& c) const  {
	float max_value = max(c.r, max(c.g, c.b));
	
	if (max_value > 1.0)
		return (c / max_value);
	else
		return (c);
}

// Set color to red if any component is greater than one
RGBColor World::clamp_to_color(const RGBColor& raw_color) const {
	RGBColor c(raw_color);
	
	if (raw_color.r > 1.0 || raw_color.g > 1.0 || raw_color.b > 1.0) {
		c.r = 1.0; c.g = 0.0; c.b = 0.0;
	}
		
	return (c);
}

// raw_color is the pixel color computed by the ray tracer
// its RGB floating point components can be arbitrarily large
// mapped_color has all components in the range [0, 1], but still floating point
// display color has integer components for computer display
// the Mac's components are in the range [0, 65535]
// a PC's components will probably be in the range [0, 255]
// the system-dependent code is in the function convert_to_display_color
// the function SetCPixel is a Mac OS function
void World::display_pixel(const int row, const int column, const RGBColor& raw_color) const {
	RGBColor mapped_color;

	if (vp.show_out_of_gamut)
		mapped_color = clamp_to_color(raw_color);
	else
		mapped_color = max_to_one(raw_color);
	
	if (vp.gamma != 1.0)
		mapped_color = mapped_color.powc(vp.inv_gamma);
	
   //have to start from max y coordinate to convert to screen coordinates
   int x = column;
   int y = vp.vres - row - 1;

   window->setPixel(x, y, (int)(mapped_color.r * 255),
                          (int)(mapped_color.g * 255),
                          (int)(mapped_color.b * 255));
}

ShadeRec World::hit_bare_bones_objects(const Ray& ray) {
	ShadeRec	sr(*this); 
	double		t; 			
	float		tmin 			= kHugeValue;
	int 		num_objects 	= objects.size();
	
	for (int j = 0; j < num_objects; j++)
		if (objects[j]->hit(ray, t, sr) && (t < tmin)) {
			sr.hit_an_object	= true;
			tmin 				= t; 
			sr.color			= objects[j]->get_color(); 
		}
		
	return (sr);   
}

// Deletes the objects in the objects array, and erases the array.
// The objects array still exists, because it's an automatic variable, but it's empty 
void World::delete_objects(void) {
	int num_objects = objects.size();
	
	for (int j = 0; j < num_objects; j++) {
		delete objects[j];
		objects[j] = NULL;
	}	
	
	objects.erase (objects.begin(), objects.end());
}

void World::add_object(GeometricObject* object_ptr) {  
	objects.push_back(object_ptr);	
}