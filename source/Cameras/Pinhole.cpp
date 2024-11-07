#include "Pinhole.hpp"

#include "../Utilities/Constants.hpp"
#include "../Utilities/Point3D.hpp"
#include "../Utilities/Vector3D.hpp"
#include "../Utilities/Debug.hpp"
#include <math.h>

Pinhole::Pinhole(Point3D eye_p, Point3D lookat):
    Camera(eye_p, lookat),
    d(1),
    zoom(1)
{}

void Pinhole::set_view_distance(const float dist){
    d = dist;
}

float Pinhole::get_distance_from_vp() const{
    return d;
}

void Pinhole::set_zoom(const float zoom){
    this->zoom = zoom;
}

float Pinhole::get_zoom() const{
    return zoom;
}

void Pinhole::render_scene(World& w){
	debug_print("Pinhole rendering.\n");
    RGBColor L;
    ViewPlane* vp = &w.vp;
    Ray ray;
    Point2D sp;
    Point2D pp;
    int depth = 0;
	int n = (int)sqrt(vp->num_samples);

    w.openWindow(vp->hres, vp->vres);
    vp->s /= zoom;
    ray.o = eye;

	debug_print("Joining entering 2d-for.\n");
    for (int r = 0; r < vp->vres; r++) {	
		for (int c = 0; c <= vp->hres; c++) {					

			// PROCESSING STUFF	
			// ANTI ALIASING
			L = black;
			debug_print("Getting anti aliasing samples.\n");
			for(int p = 0; p < n; p++) {
				for(int q = 0; q < n; q++){
					pp.x = vp->s*(c - 0.5*vp->hres + (q+0.5)/n);
					pp.y = vp->s*(r - 0.5*vp->vres + (p+0.5)/n);
					ray.d = ray_direction(pp); 
					L += w.tracer_ptr->trace_ray(ray, depth);
				}
			}
			debug_print("Anti aliasing samples get.\n");
			L /= vp->num_samples;	
			
			// DISPLAYING STUFF
			w.display_pixel(r, c, L);
			w.window->update();
			if(!w.window->isOpen()){
				return;
			}
		}	
	}
	while(w.window->isOpen()){
		w.window->update();
	}	
}

Vector3D Pinhole::ray_direction(const Point2D& pixel_point) const {
    Vector3D dir = pixel_point.x*u + pixel_point.y*v - d*w;
    dir.normalize();
    return dir;
}