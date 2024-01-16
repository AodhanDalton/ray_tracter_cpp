#ifndef MATERIAL_H
#define MATERIAL_H

#include "common_constants.h"

struct hit_record;

class material{
    public:
        virtual bool scatter(
                ray& r_in, const hit_record& rec, colour& attenuation, ray& scattered
                ) const = 0;
};
#endif
