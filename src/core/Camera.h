#pragma once
#include "../../Dependencies/glm/glm.hpp"
#include "../../Dependencies/glm/gtc/matrix_transform.hpp"


//Default values of camera
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


class Camera
{
public:
    /// <summary>
    /// 相机运动方向
    /// </summary>
    enum class CameraMovement {
        FORWARD, BACKWARD, LEFT, RIGHT
    };

    // 相机属性
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // 欧拉角
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    //相机是否运动
    bool enable = false;

private:
    //记录每帧间隔时间
    float m_lastTime;
    float m_deltaTime;
    //记录鼠标上次的位置
    float m_lastX = 400;
    float m_lastY = 300;
public:
    // constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);


    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    /// <summary>
    /// 获取观察矩阵
    /// </summary>
    /// <returns></returns>
    inline glm::mat4 GetViewMatrix() const
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    /// <summary>
    /// 处理输入导致的相机移动
    /// </summary>
    /// <param name="direction"></param>
    void ProcessKeyboard(CameraMovement direction);

    /// <summary>
    /// 处理鼠标移动导致的镜头转动
    /// </summary>
    /// <param name="xoffset"></param>
    /// <param name="yoffset"></param>
    /// <param name="constrainPitch"></param>
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

    /// <summary>
    /// 处理放缩
    /// </summary>
    /// <param name="yoffset"></param>
    void ProcessMouseScroll(float yoffset);

    /// <summary>
    /// 更新帧时间
    /// </summary>
    /// <param name="currentTime"></param>
    void UpdateTime(float currentTime);

    /// <summary>
    /// 更新观察矩阵
    /// </summary>
    /// <param name="xPos"></param>
    /// <param name="yPos"></param>
    void UpdateView(float xPos, float yPos);

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();
};






