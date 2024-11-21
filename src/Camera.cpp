#include "Camera.hpp"
#include "App.hpp"

#include <cmath>

using namespace App;

std::vector<Camera *> Camera::cameras;
Camera *Camera::selected;

void Camera::update_values()
{
    this->head.x = this->position.x + this->far_length * std::cos(this->look_angle);
    this->head.y = this->position.y + this->far_length * (-1) * std::sin(this->look_angle);

    this->angle1 = this->look_angle - (this->fov / 2);
    this->angle2 = this->look_angle + (this->fov / 2);
    this->side_length = this->far_length / std::cos(this->fov / 2);

    this->side1.x = this->position.x + this->side_length * std::cos(angle1);
    this->side1.y = this->position.y + this->side_length * (-1) * std::sin(angle1);

    this->side2.x = this->position.x + this->side_length * std::cos(angle2);
    this->side2.y = this->position.y + this->side_length * (-1) * std::sin(angle2);
}

void Camera::set_fov(float fov)
{
    this->fov = fov;
}

void Camera::set_far_length(float far_length)
{
    this->far_length = far_length;
}

void Camera::set_near_length(float near_length)
{
    this->near_length = near_length;
}

void Camera::set_segments(size_t segments)
{
    this->segments.reserve(segments);
}

size_t Camera::get_segments()
{
    return this->segments.size();
}

void Camera::select(Camera &cam)
{
    for (Camera *c : cameras) {
        c->is_selected = false;
    }

    cam.is_selected = true;
    selected = &cam;
}

void Camera::add(Camera &cam)
{
    Camera::cameras.push_back(&cam);
}

void Camera::render()
{
    this->update_values();

    if (this->selected) {
        set_color(0xff0000);
    } else {
        set_color(0xffffff);
    }

    draw_line(this->position, this->head);

    set_color(0xf8f2f2);

    draw_line(this->position, side1);
    draw_line(this->position, side2);
}

