#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Dependencies/glm/gtc/type_ptr.hpp"
#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "Camera.h"
#include "../Dependencies/imgui/imgui.h"
#include "../Dependencies//imgui/imgui_impl_glfw.h"
#include "../Dependencies/imgui/imgui_impl_opengl3.h"
#include "UniformManager.h"
#include "CubeMap.h"
#include "tools/ModelLoader/ModelLoader.h"
#include "Light.h"


void PrcocessInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 900;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

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

	float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	{
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);


		glEnable(GL_DEPTH_TEST);

		Model newmodel("res/models/nanosuit/nanosuit.obj");
		Shader shader("res/shaders/model/model.shader");
		Shader refractShader("res/shaders/EnvironmentMapping/refract.shader");
		Shader reflectShader("res/shaders/EnvironmentMapping/reflection.shader");

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.75f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));

		glm::mat4 origionModel = glm::translate(model, glm::vec3(-5.0f, 0.0f, 0.0f));
		glm::mat4 refractModel = glm::translate(model, glm::vec3(5.0f, 0.0f, 0.0f));
		glm::mat4 reflectModel = glm::translate(model, glm::vec3(15.0f, 0.0f, 0.0f));

		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 pro = glm::perspective(glm::radians(camera.Zoom), (float)(SCR_WIDTH) / (float)SCR_HEIGHT, 0.1f, 100.0f);
		DirLight dirLight;
		glm::vec3 viewPos = camera.Position;
		float ambient = 0.5f;
		int shineness = 32;

		UniformManager uniformMan;
		uniformMan.Push("u_model", {UniformType::MAT4, &model});
		uniformMan.Push("u_view", {UniformType::MAT4, &view});
		uniformMan.Push("u_projection", {UniformType::MAT4, &pro});
		uniformMan.Push("u_dirLight.direction", {UniformType::VEC3, &dirLight.direction});
		uniformMan.Push("u_dirLight.ambient", {UniformType::VEC3, &dirLight.ambient});
		uniformMan.Push("u_dirLight.diffuse", {UniformType::VEC3, &dirLight.diffuse});
		uniformMan.Push("u_dirLight.specular", {UniformType::VEC3, &dirLight.specular});
		uniformMan.Push("u_viewPos", {UniformType::VEC3, &viewPos});
		uniformMan.Push("u_shineness", {UniformType::INT, &shineness});

		uniformMan.SetUniform(shader, "u_model");
		uniformMan.SetUniform(shader, "u_dirLight.ambient");
		uniformMan.SetUniform(shader, "u_dirLight.diffuse");
		uniformMan.SetUniform(shader, "u_dirLight.specular");

		std::vector<std::string> names = {"u_model", "u_view", "u_projection", "u_dirLight.direction", "u_viewPos", "u_dirLight.ambient"};
		std::vector<std::string> refractNames = {"u_model", "u_view", "u_projection", "u_viewPos"};

		VertexBuffer skyboxVBO(skyboxVertices, sizeof(skyboxVertices));
		VertexBufferLayout  skyboxLayout;
		skyboxLayout.Push<float>(3);
		VertexArray skyboxVAO;
		skyboxVAO.AddBuffer(skyboxVBO, skyboxLayout);
		Shader skyboxShader("res/shaders/skybox.shader");
		CubeMap skybox("res/images/skybox", { "right.jpg", "left.jpg", "top.jpg", "bottom.jpg", "back.jpg" ,"front.jpg" });
		std::vector<std::string> skyboxNames = { "u_view", "u_projection" };

		Renderer renderer;

		// Application loop
		while (!glfwWindowShouldClose(window))
		{
			/**********Update data************/
			view = camera.GetViewMatrix();
			pro = glm::perspective(glm::radians(camera.Zoom), (float)(SCR_WIDTH) / (float)SCR_HEIGHT, 0.1f, 100.0f);
			viewPos = camera.Position;
			dirLight.ambient = glm::vec3(ambient);
			model = origionModel;
			uniformMan.SetUniforms(shader, names);
			model = refractModel;
			uniformMan.SetUniforms(refractShader, refractNames);
			model = reflectModel;
			uniformMan.SetUniforms(reflectShader, refractNames);
			view = glm::mat4(glm::mat3(view));
			uniformMan.SetUniforms(skyboxShader, skyboxNames);
			
			/*********Render**********/
			renderer.Clear();

			glDepthMask(GL_FALSE);
			skybox.Bind();
			renderer.Draw(skyboxVAO, 36, skyboxShader);
			glDepthMask(GL_TRUE);

			newmodel.Draw(shader);
			newmodel.Draw(refractShader);
			newmodel.Draw(reflectShader);

			/*********Render**********/

			/*********ImGui*************/
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			//imgui window
			{
				
				ImGui::Begin("Direction Light");                          // Create a window called "Hello, world!" and append into it.
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				ImGui::SliderFloat3("lightDir", &dirLight.direction.x, -1.0f, 1.0f);
				ImGui::SliderFloat("ambient", &ambient, 0.0, 1.0);
				ImGui::SliderInt("shineness", &shineness, 0, 128);
				ImGui::End();
			}

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			/*********ImGui*************/

			camera.UpdateTime((float)glfwGetTime());
			PrcocessInput(window);
			glfwPollEvents();

			//Ë«»º´æ½»»»
			glfwSwapBuffers(window);
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