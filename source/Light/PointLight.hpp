#pragma once

#include "Ambient.hpp"

class PointLight: public Ambient{
public:
    PointLight(Vector3D location = Vector3D(0), float ls_ = 1.0, RGBColor color_ = 1.0, bool shadows_ = false);
    PointLight(PointLight& point);

    Vector3D get_location() const;
    void set_location(const Vector3D location_);

    Vector3D get_direction(ShadeRec& sr);
    RGBColor L(ShadeRec& sr);

private:
    Vector3D location;
};