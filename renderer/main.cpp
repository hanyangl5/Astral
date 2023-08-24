#include <algorithm>
#include <cfloat>
#include <thread>

#include <argparse/argparse.h>
#include <svpng.inc>

#include "scene.h"
#include <Astral/render.h>

const char* g_output = "output.png";
int g_width = 256;
int g_height = 256;
int g_spp = 16;
int g_thread = 0;
int g_sample_scene_index = -1;
hittable* g_world;

bool parse_args(int argc, const char** argv) {
    const char* path = NULL;
    int perms = 0;
    struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("options"),
        OPT_STRING('o', "output", &g_output, "output, default output.png", NULL,
                   0, 0),
        OPT_INTEGER('w', "width", &g_width, "width, default 256", NULL, 0, 0),
        OPT_INTEGER('h', "height", &g_height, "height, default 256", NULL, 0, 0),
        OPT_INTEGER('s', "spp", &g_spp, "spp, default 16", NULL, 0, 0),
        OPT_INTEGER('t', "thread", &g_thread, "thread count, default max", NULL,
                    0, 0),
        OPT_INTEGER('i', "sample scene index", &g_sample_scene_index,
                    "sample scene index:\n\
1: cornell box\n\
2: cornell smoke\n\
3: scene1\n\
4: triangle",
                  NULL, 0, 0),

      OPT_END(),

    };

    struct argparse argparse;
    argparse_init(&argparse, options, nullptr, 0);

    argc = argparse_parse(&argparse, argc, argv);

    g_world = get_scene(g_sample_scene_index);
    if (g_world == nullptr) {
        std::cout << "invalid scene, run <app> -h for help\n";
        return false;
    }
    return true;
}

int main(int argc, const char** argv) {
    bool res = parse_args(argc, argv);
    if (!res) {
        return 1;
    }
    unsigned char* rgb = new unsigned char[g_width * g_height * 3];
    FILE* fp = fopen(g_output, "wb");

    vec3 lookfrom(278, 278, -800);
    vec3 lookat(278, 278, 0);
    float dist_to_focus = 10.0;
    float aperture = 0.0;
    float vfov = 40.0;

    camera cam(lookfrom, lookat, vec3(0, 1, 0), vfov,
        float(g_width) / float(g_height), aperture, dist_to_focus, 0.0,
        1.0);

    int available_threads = std::thread::hardware_concurrency() - 1;
    int thread_count =
        (g_thread == 0
            ? available_threads
            : (g_thread > available_threads ? available_threads : g_thread));

    std::cout << "image: " << g_output << " width: " << g_width
        << " height: " << g_height << " spp:" << g_spp
        << " threads: " << thread_count << "\n";
    render(g_width, g_height, g_spp, rgb, g_world, &cam, thread_count);

    svpng(fp, g_width, g_height, rgb, 0);
    fclose(fp);
    delete[] rgb;
    return 0;
}
