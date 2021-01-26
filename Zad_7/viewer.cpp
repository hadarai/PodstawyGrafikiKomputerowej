// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <vector>

// Include GLEW
#include <GL/glew.h>
// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <common/controls.hpp>
#include <common/Window.hpp>
#include <common/objloader.hpp>

#include "objects/Cuboid/Cuboid.hpp"
#include "objects/Sphere/Sphere.hpp"
#include "objects/LoadedObject/LoadedObject.hpp"

Window main_window;
// FILE *model_file;

void Window::MainLoop(char *model_filepath)
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glm::vec3 player_position = glm::vec3(1.0, 1.0, 0.0);
	glm::vec3 upper_light_position = glm::vec3(0.0, 3.0, 0.0);

	// Sphere player_position_representation;
	Cuboid aquarium_cuboid;
	LoadedObject viewed_object(model_filepath);

	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ModelMatrix;
	glm::mat4 MVP;
	do
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		computeMatricesFromInputs(player_position, win());
		// printf("gracz jest: (%f, %f, %f). Gracz bedzie: (%f, %f, %f)\n", player_position.x, player_position.y, player_position.z, new_player_position.x, new_player_position.y, new_player_position.z);

		ProjectionMatrix = getProjectionMatrix();
		ViewMatrix = getViewMatrix();
		ModelMatrix = glm::mat4(1.0);
		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		ViewportOne(0, 0, wd, ht);
		glm::vec3 viewPosition = player_position;

		// printf("Teraz patrze z (%f, %f, %f)\n", viewPosition.x, viewPosition.y, viewPosition.z);
		// aquarium_cuboid.draw(MVP, viewPosition, player_position, upper_light_position);
		viewed_object.draw(MVP, player_position, upper_light_position);

		glfwSwapBuffers(window);
		glfwPollEvents();
		WaitForFixedFPS(1000.0 / 60.0);
	} while (glfwGetKey(window, GLFW_KEY_Q) != GLFW_PRESS &&
			 glfwWindowShouldClose(window) == 0);

	glfwTerminate();
}
int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(stderr, "Please specify file path.\n");
		exit(EXIT_FAILURE);
	}
	if (argc > 2)
	{
		fprintf(stderr, "Too many arguments.\n");
		exit(EXIT_FAILURE);
	}

	char *filepath = argv[1];

	main_window.Init(1280, 720, "Viewer", 0, 33);
	main_window.MainLoop(filepath);
	return 0;
}
