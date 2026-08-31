#ifndef PLAYER_CLASS_H
#define PLAYER_CLASS_H

#include <raylib.h>
#include <iostream>
#include <rcamera.h>

class Player {
public:
    Player() {
        m_cam.position = Vector3{ 0.f, 0.f, 0.f };
        m_cam.up = Vector3{ 0.f, 1.f, 0.f };
        m_cam.fovy = 90.f;
        m_cam.projection = CAMERA_PERSPECTIVE;
        m_cam.target = Vector3{ 1.f, 0.f, 0.f };
    }

    void update(float delta) {
        // Rotate camera
        const Vector2 mouse = GetMouseDelta();
        CameraYaw(&m_cam, -mouse.x * m_sensitivity, false);
        CameraPitch(&m_cam, -mouse.y * m_sensitivity, true, false, false);

        // Speed increase with L_CTRL
        float speed = m_speed;
        if(IsKeyDown(KEY_LEFT_CONTROL)) speed *= 3.f;

        // Camera movement
        if(IsKeyDown(KEY_A)) CameraMoveRight(&m_cam, -speed * delta, true);
        if(IsKeyDown(KEY_D)) CameraMoveRight(&m_cam,  speed * delta, true);
        if(IsKeyDown(KEY_W)) CameraMoveForward(&m_cam,  speed * delta, true);
        if(IsKeyDown(KEY_S)) CameraMoveForward(&m_cam, -speed * delta, true);
        if(IsKeyDown(KEY_SPACE)) CameraMoveUp(&m_cam,  speed * delta);
        if(IsKeyDown(KEY_LEFT_SHIFT)) CameraMoveUp(&m_cam, -speed * delta);
    }

    const Camera& get_cam() const {
        return m_cam;
    }

private:
    Camera m_cam;
    float m_sensitivity = 0.003f;
    float m_speed = 8.f;
};


#endif // PLAYER_CLASS_H