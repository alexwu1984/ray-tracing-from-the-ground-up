#include "ThinLens.hpp"
#include "../World/World.hpp"

ThinLens::ThinLens(Point3D eye_p, Point3D lookat):
    Pinhole(eye_p, lookat),
    sampler_ptr(new Jittered(4))
{
    sampler_ptr->map_samples_to_unit_disk();
}

ThinLens::~ThinLens(){
    if(sampler_ptr){
        delete sampler_ptr;
        sampler_ptr = NULL;
    }
}

void ThinLens::set_sampler(Sampler* sp){
    if(sampler_ptr){
        delete sampler_ptr;
        sampler_ptr = NULL;
    }
    sampler_ptr = sp;
    sampler_ptr->map_samples_to_unit_disk();
}

Sampler* ThinLens::get_sampler(){
    return sampler_ptr;
}

void ThinLens::set_lens_radius(const float l_r){
    lens_radius = l_r;
}

float ThinLens::get_lens_radius(){
    return lens_radius;
}

void ThinLens::set_focal_dist(const float focal_d){
    f = focal_d;
}

float ThinLens::get_focal_dist(){
    return f;
}

Vector3D ThinLens::ray_direction(const Point2D& pixel_point, const Point2D& lens_point) const{
    Point2D p;
    p.x = pixel_point.x * f / d;
    p.y = pixel_point.y * f / d;
    Vector3D dir = (p.x - lens_point.x)*u + (p.y - lens_point.y)*v - f*w;
    dir.normalize();

    return dir;
}

void ThinLens::render_scene(World& w){
    RGBColor L;
    Ray ray;
    ViewPlane* vp = &w.vp;
    int depth = 0;

    Point2D sp; // Sample point in unity square
    Point2D pp; // Sample point on pixel
    Point2D dp; // Sample point on unit disk
    Point2D lp; // Sample point on lens

    w.openWindow(vp->hres, vp->vres);
    vp->s /= zoom;
    
    for (int r = 0; r < vp->vres; r++) {	
		for (int c = 0; c <= vp->hres; c++) {					

			// PROCESSING STUFF	
			// ANTI ALIASING
			L = black;
			for(int j = 0; j < vp->num_samples; j++) {
				
                sp = vp->sampler_ptr->sample_unit_square();
				  
                pp.x = vp->s*(c - 0.5*vp->hres + sp.x);
				pp.y = vp->s*(r - 0.5*vp->vres + sp.y);
                
                dp = sampler_ptr->sample_unit_disk();
        
                lp = dp * lens_radius;
                
                ray.o = eye + (lp.x*u + lp.y*v);
				ray.d = ray_direction(pp, lp);
                L += w.tracer_ptr->trace_ray(ray, depth);
			}
         
			L /= vp->num_samples;
            L *= exposure_time;		
			
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