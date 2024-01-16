#include <iostream>
#include <memory>
#include "camera.h"
#include "common_constants.h"
#include "colour.h"
#include "hittable_list.h"
#include "sphere.h"
#include "vec3.h"


double hit_sphere(const point3& center, double radius, const ray& r){
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;

    if (discriminant < 0){
        return -1.0;
    }
    else{
        return (-b - sqrt(discriminant) / (2.0*a)); 
    }
}


colour ray_colour(const ray& r, const hittable& world, int depth) {
    hit_record rec;

     // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return colour(0,0,0);

    if (world.hit(r, 0.001, infinity, rec)) {
        // point3 target = rec.p + rec.normal + random_unit_vector();
        point3 target = rec.p + random_in_hemisphere(rec.normal);
        return 0.5 * ray_colour(ray(rec.p, target - rec.p), world, depth-1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*colour(1.0, 1.0, 1.0) + t*colour(0.5, 0.7, 1.0);
}

int main(){
    //image
    const auto aspect_ratio = 16.0/9.0;
    const int image_width = 1000;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int depth_max = 50;

    //World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    //Camera
    camera cam; 


    //Renderer
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for(int j=image_height-1; j>=0; --j){
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for(int i=0; i<image_width; ++i){
            colour pixel_colour(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s){
                auto u = (i + random_double())  / (image_width-1);
                auto v = (j + random_double()) / (image_height-1);
                ray r = cam.get_ray(u, v);
                pixel_colour += ray_colour(r, world, depth_max);
            }
            write_colour(std::cout, pixel_colour, samples_per_pixel);
        }
    }
    std::cerr << "\nDone.\n";
    return 0;
}
