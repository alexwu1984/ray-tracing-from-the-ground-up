#include "Disk.hpp"

Disk::Disk(Material* material_p) 
    : GeometricObject(material_p)
    , center(0)
    , normal(0)
    , radius(0)
    , sampler_ptr(new Regular(1))
{}

Disk::Disk(Point3D center_, Normal normal_, float radius_, Material* material_p)
    : GeometricObject(material_p)
    , center(center_)
    , normal(normal_)
    , radius(radius_)
    , sampler_ptr(new Regular(1)) {
    normal.normalize();
}

Disk::Disk(const Disk& disk)
    : GeometricObject(disk)
    , center(disk.center)
    , normal(disk.normal)
    , radius(disk.radius){     
    normal.normalize();
	if (disk.sampler_ptr) {
		sampler_ptr = disk.sampler_ptr->clone();
	}
	else {
		sampler_ptr = new Regular(1);
	}
}

Disk::~Disk()
{
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}
}

Disk& Disk::operator=(const Disk& rhs){
    if(this == &rhs){
        return(*this);
    }
    GeometricObject::operator=(rhs);
    center = rhs.center;
    normal = rhs.normal;
    normal.normalize();
    radius = rhs.radius;
	if (rhs.sampler_ptr) {
		sampler_ptr = rhs.sampler_ptr->clone();
	}
	else {
		sampler_ptr = new Regular(1);
	}
    return(*this);
}

Disk* Disk::clone() const { 
    return (new Disk(*this));
}

bool Disk::hit(const Ray& ray, float& t, ShadeRec& s) const {
    float t_ = (center-ray.o)*normal / (ray.d*normal);
    if(t_ <= kEpsilon){
        return false;
    }
    Point3D p = ray.o + t_*ray.d;
    if(center.d_squared(p) < (radius*radius)) {
        t = t_;
        s.normal = normal;
        s.local_hit_point = p;
        return true;
    }
    return false;
}

void Disk::set_center(const Point3D center_){
    center = center_;
}

Point3D Disk::get_center() const{
    return center;
}

void Disk::set_radius(const float radius_){
    radius = radius_;
}

float Disk::get_radius() const {
    return radius;
}  

void Disk::set_normal(const Normal normal_){
    normal = normal_;
    normal.normalize();
}

Normal Disk::get_normal() const{
    return normal;
}

void Disk::set_sampler(Sampler* sampler)
{
	if (sampler_ptr) {
		delete sampler_ptr;
	}
	sampler_ptr = sampler;
    if (sampler_ptr)
        sampler_ptr->map_samples_to_unit_disk();
}

Point3D Disk::sample()
{
	Point2D sample_point = sampler_ptr->sample_unit_disk();
	return (center + sample_point.x * radius + sample_point.y * radius);
}

float Disk::pdf(const ShadeRec& sr)
{
    return 1.f / PI;
}
