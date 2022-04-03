#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Dependencies/glm/gtc/type_ptr.hpp"
#include "shaderToolCLass/Renderer.h"
#include "shaderToolCLass/VertexBufferLayout.h"
#include "shaderToolCLass/Camera.h"
#include "shaderToolCLass/Light.h"
#include "../Dependencies/imgui/imgui.h"
#include "../Dependencies//imgui/imgui_impl_glfw.h"
#include "../Dependencies/imgui/imgui_impl_opengl3.h"
#include "shaderToolCLass/UniformManager.h"


void PrcocessInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 900;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool firstMouse = true;

int main()
{
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(SCR_WIDTH,  SCR_HEIGHT, "OpenGL", NULL, NULL);

	glfwSwapInterval(1);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	if (glewInit() != GLEW_OK)
	{
		return -1;
	}

	float pos[] = {
		0.5f,	0.5f, 
		-0.5f, -0.5f,
		0, 0.5f};

	{
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);

		VertexArray vao;
		VertexBuffer vbo(pos, 2 * 3 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		vao.AddBuffer(vbo, layout);
		Shader shader("res/shaders/basic.shader");

		Renderer renderer;

		glm::vec3 color = glm::vec3(1.0f);
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 pro = glm::perspective(glm::radians(camera.Zoom), (float)(SCR_WIDTH) / (float)SCR_HEIGHT, 0.1f, 100.0f);

		UniformManager uniformMan;
		uniformMan.Push("u_color", {UniformType::VEC3, &color});
		uniformMan.Push("u_model", { UniformType::MAT4, &model });
		uniformMan.Push("u_view", { UniformType::MAT4, &view });
		uniformMan.Push("u_pro", { UniformType::MAT4, &pro });

		std::vector<std::string> names = {"u_color", "u_model", "u_view", "u_pro"};

		while (!glfwWindowShouldClose(window))
		{
			view = camera.GetViewMatrix();
			glm::perspective(glm::radians(camera.Zoom), (float)(SCR_WIDTH) / (float)SCR_HEIGHT, 0.1f, 100.0f);

			
			uniformMan.SetUniforms(shader, names);

			renderer.Clear();
			glClearColor(0.5f, 0.4f, 0.3f, 1.0f);
			renderer.Draw(vao, 3, shader);

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			//imgui window
			{
				
				ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				ImGui::ColorEdit3("TriagnleColor", (float*)&color);
				ImGui::End();
			}

			ImGui::Render();

			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			camera.UpdateTime((float)glfwGetTime());

			PrcocessInput(window);

			//Ë«»º´æ½»»»
			glfwSwapBuffers(window);

			glfwPollEvents();
		}

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

	}

	glfwTerminate();
	return 0;

}

void PrcocessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetMouseButton(window, 1) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		camera.enable = true;		
	}
	else
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		camera.enable = false;
	}


	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera::CameraMovement::FORWARD);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera::CameraMovement::BACKWARD);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera::CameraMovement::LEFT);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera::CameraMovement::RIGHT);
}

// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	camera.UpdateView(static_cast<float>(xposIn), static_cast<float>(yposIn));
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}