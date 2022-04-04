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
    /// ����˶�����
    /// </summary>
    enum class CameraMovement {
        FORWARD, BACKWARD, LEFT, RIGHT
    };

    // �������
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // ŷ����
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    //����Ƿ��˶�
    bool enable = false;

private:
    //��¼ÿ֡���ʱ��
    float m_lastTime;
    float m_deltaTime;
    //��¼����ϴε�λ��
    float m_lastX = 400;
    float m_lastY = 300;
public:
    // constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);


    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    /// <summary>
    /// ��ȡ�۲����
    /// </summary>
    /// <returns></returns>
    inline glm::mat4 GetViewMatrix() const
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    /// <summary>
    /// �������뵼�µ�����ƶ�
    /// </summary>
    /// <param name="direction"></param>
    void ProcessKeyboard(CameraMovement direction);

    /// <summary>
    /// ��������ƶ����µľ�ͷת��
    /// </summary>
    /// <param name="xoffset"></param>
    /// <param name="yoffset"></param>
    /// <param name="constrainPitch"></param>
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

    /// <summary>
    /// �������
    /// </summary>
    /// <param name="yoffset"></param>
    void ProcessMouseScroll(float yoffset);

    /// <summary>
    /// ����֡ʱ��
    /// </summary>
    /// <param name="currentTime"></param>
    void UpdateTime(float currentTime);

    /// <summary>
    /// ���¹۲����
    /// </summary>
    /// <param name="xPos"></param>
    /// <param name="yPos"></param>
    void UpdateView(float xPos, float yPos);

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();
};






