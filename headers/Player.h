#ifndef PLAYER_CLASS_H
#define PLAYER_CLASS_H

#include <raylib.h>
// #include <rcamera.h>

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
        UpdateCamera(&m_cam, CAMERA_FREE); // For now
    }

    const Camera& get_cam() const {
        return m_cam;
    }

private:
    Camera m_cam;
};


#endif // PLAYER_CLASS_H