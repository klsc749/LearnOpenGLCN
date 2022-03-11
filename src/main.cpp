#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Dependencies/glm/gtc/type_ptr.hpp"
#include "shaderToolCLass/Renderer.h"
#include "shaderToolCLass/VertexBufferLayout.h"
#include "shaderToolCLass/Camera.h"
#include "../Dependencies/imgui/imgui.h"
#include "../Dependencies//imgui/imgui_impl_glfw.h"
#include "../Dependencies/imgui/imgui_impl_opengl3.h"



void PrcocessInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 900;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastTime = 0.0f;

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

	// tell GLFW to capture our mouse
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (glewInit() != GLEW_OK)
	{
		return -1;
	}

	float vertices[] = {
 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

		
	{
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))


		VertexArray cubeVAO;
		VertexBufferLayout cubeLayout;
		cubeLayout.Push<float>(3);
		cubeLayout.Push<float>(3);

		//设置纹理
		Texture texture("res/images/container.jpg", 0);
		texture.Bind(0);

		//设置顶点缓冲对象
		VertexBuffer cubeVBO(vertices, sizeof(vertices));
		cubeVAO.AddBuffer(cubeVBO, cubeLayout);


		//设置着色器程序
		Shader cubeProgram("res/shaders/basic.shader");


		VertexArray lightVAO;
		lightVAO.AddBuffer(cubeVBO, cubeLayout);

		Shader lightShader("res/shaders/light.shader");

		glEnable(GL_DEPTH_TEST);


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

		glm::vec3 lightColor = glm::vec3(1.0f);
		glm::vec3 lightPos(1.0f, 0.017f, -0.148f);
		glm::vec3 cubeColor(1.0f, 1.0f, 1.0f);
		float ambientStrength = 0.1f;
		float specularStrength = 0.5f;
		while (!glfwWindowShouldClose(window))
		{

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			//opengl use
			{
				//清理缓冲区
				glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				//处理输入
				PrcocessInput(window);

				//projection transformation
				glm::mat4 projection = glm::mat4(1.0f);
				projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
				
				// camera/view transformation
				glm::mat4 view = camera.GetViewMatrix();
				
				//move transformation
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::rotate(model,glm::radians(float(45)), glm::vec3(0, 1.0f, 0.0f));


				cubeProgram.Bind();

				cubeProgram.SetMat4f("model", model);
				cubeProgram.SetMat4f("projection", projection);
				cubeProgram.SetMat4f("view", view);
				cubeProgram.SetVec3("u_light", lightColor.x, lightColor.y, lightColor.z);
				cubeProgram.SetVec3("u_objColor", cubeColor.x, cubeColor.y, cubeColor.z);
				cubeProgram.SetFloat("u_ambientStrength", ambientStrength);
				cubeProgram.SetFloat("u_specularStrength", specularStrength);
				cubeProgram.SetVec3("u_lightPos", lightPos.x, lightPos.y, lightPos.z);
				cubeProgram.SetVec3("u_viewPos", camera.Position.x, camera.Position.y, camera.Position.z);

				cubeVAO.Bind();
				glDrawArrays(GL_TRIANGLES, 0, 36);
				cubeVAO.UnBind();

				model = glm::mat4(1.0f);
				model = glm::translate(model, lightPos);
				model = glm::scale(model, glm::vec3(0.2f));
				lightShader.Bind();
				lightShader.SetMat4f("model", model);
				lightShader.SetMat4f("projection", projection);
				lightShader.SetMat4f("view", view);
				lightShader.SetVec3("u_light", lightColor.x, lightColor.y, lightColor.z);
				lightVAO.Bind();
				glDrawArrays(GL_TRIANGLES, 0, 36);
				lightVAO.UnBind();
			}

			//imgui window
			{

				ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				ImGui::ColorEdit3("light color", (float*)&lightColor);
				ImGui::ColorEdit3("obj color", (float*)&cubeColor);
				ImGui::SliderFloat3("light positin", (float*)&lightPos, -5.0f, 5.0f);
				ImGui::SliderFloat("Ambient strength", (float*)&ambientStrength, 0.0f, 1.0f);
				ImGui::SliderFloat("specular strength", (float*)&specularStrength, 0.0f, 1.0f);
				ImGui::End();
			}

			ImGui::Render();

			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			float currentTime = (float)glfwGetTime();
			deltaTime = currentTime - lastTime;
			lastTime = currentTime;

			//双缓存交换
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
		camera.ProcessKeyboard(Camera::CameraMovement::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera::CameraMovement::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera::CameraMovement::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera::CameraMovement::RIGHT, deltaTime);
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
	if (camera.enable)
	{
		float xpos = static_cast<float>(xposIn);
		float ypos = static_cast<float>(yposIn);


		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

		lastX = xpos;
		lastY = ypos;

		camera.ProcessMouseMovement(xoffset, yoffset);
	}

}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}