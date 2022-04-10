#include "Camera.h"

glm::vec3 fpsProjection(glm::vec3 vector);

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}
Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Position = glm::vec3(posX, posY, posZ);
	WorldUp = glm::vec3(upX, upY, upZ);
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}
glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position, Position + Front, Up);
}
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	if (direction == FORWARD)
	{
		Position += velocity * fpsProjection(Front);
	}
	if (direction == BACKWARD)
	{
		Position -= velocity * fpsProjection(Front);
	}
	if (direction == LEFT)
	{
		Position -= velocity * fpsProjection(Right);
	}
	if (direction == RIGHT)
	{
		Position += velocity * fpsProjection(Right);
	}
}
void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;
	Yaw += xoffset;
	Pitch = __max(-89.0f, __min(89.0f, Pitch + yoffset));
	updateCameraVectors();
}
void Camera::ProcessMouseScroll(float yoffset)
{
	Zoom = __max(1.0f, __min(45.0f, Zoom - yoffset));
}
void Camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);
	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));
}

glm::vec3 fpsProjection(glm::vec3 vector)
{
#ifdef fpsMode
	return glm::vec3(vector.x, 0, vector.z);
#else
	return vector;
#endif
}