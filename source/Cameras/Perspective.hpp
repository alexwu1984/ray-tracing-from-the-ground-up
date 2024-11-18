#pragma once

#include "Camera.hpp"
#include "../World/World.hpp"

class Perspective : public Camera{
public:
	Perspective(Point3D eye_p = Point3D(0, 0, 1), Point3D lookat = Point3D(0, 0, -1));

	void set_view_distance(const float dist);
	float get_distance_from_vp() const;

	virtual void render_scene(World& w);
	virtual Vector3D ray_direction(const Point2D& pixel_point) const;

protected:
	float d; // Distance from view-plane
};