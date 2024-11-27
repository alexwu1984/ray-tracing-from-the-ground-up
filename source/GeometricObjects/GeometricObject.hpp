#pragma once

#include "../Utilities/Point3D.hpp"
#include "../Utilities/Ray.hpp"
#include "../Utilities/ShadeRec.hpp"
#include "../GeometricObjects/BBox.hpp"
	
class Sampler;

class GeometricObject {
public:

	GeometricObject(Material* material_p = nullptr);
	virtual ~GeometricObject();
	
	GeometricObject(const GeometricObject& go);

	GeometricObject& operator=(const GeometricObject& go);

	virtual GeometricObject* clone() const = 0;

	virtual bool hit(const Ray& ray, float& t, ShadeRec& s) const = 0;

	virtual bool shadow_hit(const Ray& ray, float& tmin) const;

	Material* get_material() const;

	void set_material(Material* mPtr);

	void set_color(const RGBColor& c);

	void set_color(const float r, const float g, const float b);

	RGBColor get_color();

	virtual BBox get_bounding_box() const;

	// TODO: virtual? pure or implemented here?
	void set_shadows(bool _shadows);

	virtual void add_object(GeometricObject* object_ptr);

	// the following functions are used when the rectangle is a light source
	// todo: implement them in rectangle, disk and sphere

	virtual void set_sampler(Sampler* sampler);

	virtual Point3D sample();

	virtual Normal get_normal() const;

	virtual Normal get_normal(const Point3D& p) const;

	virtual float pdf(const ShadeRec& sr);

protected:

	RGBColor color = RGBColor::black;

	// From the book, chapter 16.7 Shadowing Options
	// Specify whether an object casts shadows or not.
	// This is essential for performing ambient occlusion with environment lights (see Section 18.10).
	bool shadows = true;

	// mutable allows Compound::hit, Instance::hit and Grid::hit to assign to material_ptr. hit functions are const
	mutable Material* material_ptr = nullptr;

	Sampler* sampler_ptr = nullptr;
};

inline Material* GeometricObject::get_material() const { return material_ptr; }

inline void GeometricObject::set_color(const RGBColor& c) { color = c; }

inline void GeometricObject::set_color(const float r, const float g, const float b) {
	color.r = r;
	color.b = b;
	color.g = g;
}

inline RGBColor GeometricObject::get_color() { return color; }

inline void GeometricObject::set_shadows(bool _shadows) { shadows = _shadows; }