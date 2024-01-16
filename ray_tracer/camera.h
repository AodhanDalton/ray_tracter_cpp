#ifndef CAMERA_H
#define CAMERA_H

#include "common_constants.h"
#include "vec3.h"

class camera{
    public:
        camera(){
            auto aspect_ratio = 16.0/9.0;
            auto viewport_height = 2.0;
            auto viewport_width = aspect_ratio * viewport_height;
            auto focal_length = 1.0;

            origin = point3(0, 0, 0);
            horizonatal = vec3(viewport_width, 0.0, 0.0);
            vertical = vec3(0.0, viewport_height, 0.0);

            lower_left_corner = origin - horizonatal/2 - vertical/2 - vec3(0, 0, focal_length);
        }
        ray get_ray(double u, double v) const {
            return ray(origin, lower_left_corner + u*horizonatal + v*vertical - origin);
        }
    private:
        point3 origin;
        point3 lower_left_corner;
        vec3 horizonatal;
        vec3 vertical;
};
#endif
