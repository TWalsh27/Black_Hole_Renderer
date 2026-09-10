#include <cfloat>
#include <SDL3/SDL.h>
#include <iostream>
#include "Classes/Vec3.h"
#include <vector>
#include <cstdint>
#include "Classes/Ray.h"
#include "Classes/Camera.h"
#include "Classes/Sphere.h"
#include "Classes/Window.h"
#include "HitRecord.h"

// Main helper functions:

uint32_t get_pixel(const double r, const double g, const double b)
{
    // cast them to uint8_t
    uint8_t a = 255;
    uint8_t casted_r = static_cast<uint8_t> (r * 255);
    uint8_t casted_g = static_cast<uint8_t> (g * 255);
    uint8_t casted_b = static_cast<uint8_t> (b * 255);

    // bit shift them into uint32 value
    uint32_t pixel = (a << 24) | (casted_r << 16) | (casted_g << 8) | casted_b;

    return pixel;
}

double get_closest_positive_t(const std::pair<double, double>& intersects)
{
    double chosen_intersect = -1;

    if (intersects.first > 0)
        chosen_intersect = intersects.first;

    if (intersects.second > 0 &&
        (chosen_intersect < 0 || intersects.second < chosen_intersect))
    {
        chosen_intersect = intersects.second;
    }

    return chosen_intersect;
}

HitRecord find_closest_hit(const Ray& test_ray, const std::vector<Sphere>& sphere_container)
{
    HitRecord empty_hit_record;

    const Sphere * closest_sphere = nullptr;

    double closest_t = DBL_MAX;

    // loop over objects in scene to get closest sphere
    for (const Sphere& curr : sphere_container)
    {
        std::pair<double, double> intersects = curr.ray_sphere_intersection(test_ray);
        double chosen_intersect = get_closest_positive_t(intersects);

        if (chosen_intersect < closest_t && chosen_intersect > 0)
        {
            closest_t = chosen_intersect;
            closest_sphere = &curr;
        }
    }

    if (closest_sphere == nullptr)
        return empty_hit_record; // exit early, miss

    // get remaining hit record data
    Vec3 hit_point = test_ray.at(closest_t);
    Vec3 normal = (hit_point - closest_sphere->get_center()).normalize();

    HitRecord full_hit_record(true, closest_t, hit_point, normal, closest_sphere);

    // return after init of full hit record
    return full_hit_record;
}

const int WIDTH = 800, HEIGHT = 600;

int main(int argc, char* argv[]) {

    Camera camera(Vec3(0,0,0), 800, 600, 90);

    // currently testing multiple temporary spheres

    Sphere sphere1(Vec3(-1,0,-4), 1, 0xFFFF0000);
    Sphere sphere2(Vec3(2,1,-5), 1, 0xFF00FF00);

    std::vector<Sphere> sphere_container {
        sphere1,
        sphere2,
    };

    Vec3 light_position(-6, -2, 0);

    // Allocate memory for pixel buffer
    std::vector<uint32_t> buffer_Mem(WIDTH * HEIGHT);

    // Render objects and gradient onto frame
    for (double y = 0; y < HEIGHT; y++) {
        for (double x = 0; x < WIDTH; x++) {
            int index = y * WIDTH + x;

            Ray current_ray = camera.get_ray_for_pixel(x,y);

            HitRecord hit_record = find_closest_hit(current_ray, sphere_container);

            Vec3 current_direction = current_ray.get_direction();

            if (hit_record.get_hit_status()) { // hit

                // init shadow ray
                Vec3 shadow_origin = hit_record.get_hit_point() + hit_record.get_normal() * 0.001;
                Vec3 light_direction = (light_position - hit_record.get_hit_point()).normalize();
                Ray shadow_ray(shadow_origin, light_direction);

                HitRecord shadow_hit_record = find_closest_hit(shadow_ray, sphere_container);

                double light_distance = (light_position - hit_record.get_hit_point()).get_length();

                bool in_shadow;

                if (shadow_hit_record.get_hit_status() && shadow_hit_record.get_t() < light_distance)
                    in_shadow = true;
                else
                    in_shadow = false;

                // get reflection ray component
                Vec3 incoming_direction = current_ray.get_direction();
                Vec3 reflection_direction = incoming_direction.reflect(hit_record.get_normal());
                Vec3 reflection_origin = hit_record.get_hit_point() + hit_record.get_normal() * 0.001;

                // init reflection ray
                Ray reflection_ray(reflection_origin, reflection_direction);

                HitRecord reflection_hit_record = find_closest_hit(reflection_ray, sphere_container);

                double reflected_r;
                double reflected_g;
                double reflected_b;

                if (reflection_hit_record.get_hit_status()) // reflection hit
                {
                    uint32_t reflected_color = reflection_hit_record.get_hit_object()->get_color();

                    reflected_r = ((reflected_color >> 16) & 0xFF) / 255.0;
                    reflected_g = ((reflected_color >> 8) & 0xFF) / 255.0;
                    reflected_b = (reflected_color & 0xFF) / 255.0;
                }
                else // reflection miss
                {
                    Vec3 reflected_direction = reflection_ray.get_direction();

                    reflected_r = (reflected_direction.get_x() + 1) / 2;
                    reflected_g = (reflected_direction.get_y() + 1) / 2;
                    reflected_b = (reflected_direction.get_z() + 1) / 2;
                }

                // init brightness to 0 (in shadow)
                double brightness = 0;

                // correct brightness if not in shadow
                if (!in_shadow)
                {
                    brightness = std::max(0.0, hit_record.get_normal().dot(light_direction));
                }

                uint32_t local_color = hit_record.get_hit_object()->get_color();

                double reflectivity = 0.3; // temporary reflectivity value

                auto local_r = ((local_color >> 16) & 0xFF) / 255.0 * brightness;
                auto local_g = ((local_color >> 8) & 0xFF) / 255.0 * brightness;
                auto local_b = (local_color & 0xFF) / 255.0 * brightness;

                auto final_r = (1 - reflectivity) * local_r + reflectivity * reflected_r;
                auto final_g = (1 - reflectivity) * local_g + reflectivity * reflected_g;
                auto final_b = (1 - reflectivity) * local_b + reflectivity * reflected_b;

                uint32_t pixel = get_pixel(final_r,final_g,final_b);

                // Write pixel data to memory and map onto frame
                buffer_Mem[index] = pixel;
            }
            else
            {
                // miss
                auto r = (current_direction.get_x() + 1) / 2;
                auto g = (current_direction.get_y() + 1) / 2;
                auto b = (current_direction.get_z() + 1) / 2;

                uint32_t pixel = get_pixel(r,g,b);

                buffer_Mem[index] = pixel; // map onto frame
            }
        }
    }

    Window Test_Window("Test Window", WIDTH, HEIGHT);

    Test_Window.initialize();

    SDL_Texture * texture = SDL_CreateTexture(Test_Window.getRenderer(),
                                    SDL_PIXELFORMAT_ARGB8888,
                                    SDL_TEXTUREACCESS_STREAMING,
                                    WIDTH, HEIGHT);

    SDL_UpdateTexture(texture, nullptr, buffer_Mem.data(), WIDTH * sizeof(uint32_t));

    bool running = true;

    SDL_Event event;

    while (running) {
        Test_Window.clear();
        SDL_RenderTexture(Test_Window.getRenderer(), texture, nullptr, nullptr);
        Test_Window.present();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT)
                running = false;
        }
    }

    return 0;
}
