#include "Classes/Vec3.h"
#include "Classes/Ray.h"
#include "Classes/Camera.h"
#include "Classes/Sphere.h"
#include "Classes/Window.h"
#include "Classes/HitRecord.h"
#include "Classes/Material.h"
#include "Classes/Scene.h"
#include <iostream>
#include <ctime>
#include <vector>
#include <cfloat>
#include <SDL3/SDL.h>
#include <algorithm>

// Main helper functions:

// Takes in an RGB value and returns a unint32_t
uint32_t get_pixel(const double r, const double g, const double b)
{
    // clamp RGB values for edge cases
    const double clamped_r = std::clamp(r, 0.00, 1.00);
    const double clamped_g = std::clamp(g, 0.00, 1.00);
    const double clamped_b = std::clamp(b, 0.00, 1.00);

    // cast them to uint8_t
    uint8_t a = 255;
    uint8_t casted_r = static_cast<uint8_t> (clamped_r * 255);
    uint8_t casted_g = static_cast<uint8_t> (clamped_g * 255);
    uint8_t casted_b = static_cast<uint8_t> (clamped_b * 255);

    // bit shift them into uint32 value
    uint32_t pixel = (a << 24) | (casted_r << 16) | (casted_g << 8) | casted_b;

    return pixel;
}

// Takes in a pair of intersects and determines the closest valid t value
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

// Takes in a ray and a container of all spheres in the scene. Returns the closest hit of said ray on the spheres
HitRecord find_closest_hit(const Ray& test_ray, const std::vector<Sphere>& sphere_container)
{
    HitRecord empty_hit_record;

    const Sphere * closest_sphere = nullptr;

    double closest_t = DBL_MAX;

    // loop over objects in scene to get closest sphere
    for (const Sphere& curr : sphere_container)
    {
        std::optional<std::pair<double, double>> intersects = curr.ray_sphere_intersection(test_ray);

        if (intersects) {
            double chosen_intersect = get_closest_positive_t(intersects.value());

            if (chosen_intersect < closest_t && chosen_intersect > 0)
            {
                closest_t = chosen_intersect;
                closest_sphere = &curr;
            }
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

Vec3 get_normalized_color(const uint32_t color) {
    auto r = (color >> 16 & 0xFF) / 255.0;
    auto g = (color >> 8 & 0xFF) / 255.0;
    auto b = (color & 0xFF) / 255.0;

    Vec3 color_vector(r,g,b);

    return color_vector;
}

Vec3 get_background_color(const Vec3& direction) {
    auto r = (direction.get_x() + 1) / 2;
    auto g = (direction.get_y() + 1) / 2;
    auto b = (direction.get_z() + 1) / 2;

    Vec3 color_vector(r,g,b);

    return color_vector;
}

Vec3 trace_ray(const Ray& ray, const Scene& scene, int depth)
{
    Vec3 current_direction = ray.get_direction();

    const std::vector<Sphere>& sphere_container = scene.get_sphere_container();
    const Vec3& light_position = scene.get_light_position();

    HitRecord hit_record = find_closest_hit(ray, sphere_container);

    if (hit_record.get_hit_status())
    {
        // hit

        // init shadow ray
        Vec3 shadow_origin = hit_record.get_hit_point() + hit_record.get_normal() * 0.001;
        Vec3 light_direction = (light_position - hit_record.get_hit_point()).normalize();
        Ray shadow_ray(shadow_origin, light_direction);

        HitRecord shadow_hit_record = find_closest_hit(shadow_ray, sphere_container);

        double light_distance = (light_position - hit_record.get_hit_point()).get_length();

        bool in_shadow = shadow_hit_record.get_hit_status() && shadow_hit_record.get_t() < light_distance;

        // init brightness to .15 (in shadow)
        double brightness = .15;

        // correct brightness if not in shadow
        if (!in_shadow)
            brightness = brightness + .85 * std::max(0.0, hit_record.get_normal().dot(light_direction));

        Material sphere_material = hit_record.get_hit_object()->get_material();

        Vec3 local_rgb = sphere_material.get_base_color() * brightness;

        if (depth <= 0 || sphere_material.get_reflectivity() == 0)
            return local_rgb;

        // get reflection ray component
        Vec3 incoming_direction = current_direction;
        Vec3 reflection_direction = incoming_direction.reflect(hit_record.get_normal());
        Vec3 reflection_origin = hit_record.get_hit_point() + hit_record.get_normal() * 0.001;

        // init reflection ray
        Ray reflection_ray(reflection_origin, reflection_direction);

        Vec3 reflection_color_vector = trace_ray(reflection_ray, scene, depth - 1);

        Vec3 final_rgb = local_rgb * (1 - sphere_material.get_reflectivity()) + (reflection_color_vector * sphere_material.get_reflectivity());

        return final_rgb;
    }

    // miss

    Vec3 final_rgb = get_background_color(current_direction);

    return final_rgb;
}

int main(int argc, char* argv[]) {

    // start trackers for time calculations
    std::clock_t start, end;

    volatile long long sum = 0;
    long outer_limit = 10000;
    long inner_limit = 50000;

    const int WIDTH = 800, HEIGHT = 600;

    Camera camera(Vec3(0,0,0), 800, 600, 90, 90);

    // currently testing multiple temporary spheres

    Material sphere1_material(.3, Vec3(1,0,0));
    Sphere sphere1(Vec3(-1,0,-4), 1, sphere1_material);

    Material sphere2_material(.7, Vec3(0,1,0));
    Sphere sphere2(Vec3(2,1,-5), 1, sphere2_material);

    std::vector<Sphere> sphere_container {
        sphere1,
        sphere2,
    };

    Vec3 light_position(-4, -8, 0);

    Scene scene(sphere_container, light_position);

    int depth = 3;

    // Allocate memory for pixel buffer
    std::vector<uint32_t> buffer_mem(WIDTH * HEIGHT);

    // start timer
    start = std::clock();

    // Render objects and gradient onto frame
    for (double y = 0; y < HEIGHT; y++) {
        for (double x = 0; x < WIDTH; x++) {
            int index = y * WIDTH + x;

            Vec3 color_sum;

            for (int j = 0; j < 4; j++)
            {
                double offset_x = 0.25 + 0.5 * (j % 2);
                double offset_y = 0.25 + 0.5 * (j / 2);

                Ray current_ray = camera.get_ray_for_pixel(x + offset_x, y + offset_y);

                color_sum = color_sum + trace_ray(current_ray, scene, depth);
            }

            color_sum = color_sum / 4;

            uint32_t pixel = get_pixel(color_sum.get_x(), color_sum.get_y(), color_sum.get_z());

            buffer_mem[index] = pixel;
        }
    }

    // end timer and calculate, then print to terminal
    end = std::clock();

    double time_taken = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    printf ("Image rendered in %lf seconds ", time_taken);

    // The code below is used for the window, and it thus not related to the logic above

    Window Test_Window("Test Window", WIDTH, HEIGHT);

    Test_Window.initialize();

    SDL_Texture * texture = SDL_CreateTexture(Test_Window.getRenderer(),
                                    SDL_PIXELFORMAT_ARGB8888,
                                    SDL_TEXTUREACCESS_STREAMING,
                                    WIDTH, HEIGHT);

    SDL_UpdateTexture(texture, nullptr, buffer_mem.data(), WIDTH * sizeof(uint32_t));

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
