#include "GeometricObject.hpp"

#include "../Utilities/Constants.hpp"
#include "../Materials/Material.hpp"
#include "../Samplers/Sampler.hpp"

GeometricObject::GeometricObject(Material* material_p)
	: 	material_ptr(material_p)
{}

GeometricObject::GeometricObject (const GeometricObject& object){
	if(object.material_ptr){
		material_ptr = object.material_ptr->clone();
	}
	else{
		material_ptr = NULL;
	}

	if (sampler_ptr != nullptr) {
		delete sampler_ptr;
	}
	sampler_ptr = object.sampler_ptr->clone();

}	

GeometricObject& GeometricObject::operator= (const GeometricObject& rhs) {
	if (this == &rhs)
		return (*this);

	if(material_ptr){
		delete material_ptr;
		material_ptr = NULL;
	}
	if(rhs.material_ptr){
		material_ptr = rhs.material_ptr->clone();
	}

	if (sampler_ptr != nullptr) {
		delete sampler_ptr;
	}
	sampler_ptr = rhs.sampler_ptr->clone();


	return (*this);
}

BBox GeometricObject::get_bounding_box() const {
	return BBox();
}

GeometricObject::~GeometricObject () 
{
	if(material_ptr != NULL){
		delete material_ptr;
		material_ptr = NULL;
	}

	if (sampler_ptr != nullptr)
	{
		delete sampler_ptr;
		sampler_ptr = nullptr;
	}
}

void GeometricObject::set_material(Material* material_p){
	if(material_ptr != NULL){
		delete material_ptr;
	}
	material_ptr = material_p;
}

void GeometricObject::add_object(GeometricObject* object_ptr){
}

void GeometricObject::set_sampler(Sampler* sampler)
{
	if (sampler_ptr)
	{
		delete sampler_ptr;
		sampler_ptr = nullptr;
	}
	sampler_ptr = sampler;
}

Normal GeometricObject::get_normal() const{
	return Normal();
} 
Normal GeometricObject::get_normal(const Point3D& p) const{
	return Normal();
} 

bool GeometricObject::shadow_hit(const Ray& ray, float& tmin) const { 
	return false;
}

Point3D GeometricObject::sample(){
	return Point3D();
}

float GeometricObject::pdf(const ShadeRec& sr){
	return 1.0;
}