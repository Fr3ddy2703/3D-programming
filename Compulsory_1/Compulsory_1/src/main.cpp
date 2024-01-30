#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "MathFunction.h"


/* Vertex Shader Source */
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 FragColor;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
" FragColor = aColor;\n"
"}\0";

/* Fragment shader source */
const char *fragmentShaderSource = "#version 330 core\n"
"in vec3 FragColor;"
"out vec4 FinalColor;\n"

"void main()\n"
"{\n"
"	FinalColor = vec4(FragColor, 1.0f);\n"
"}\n\0";

void processInput (GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
		glfwSetWindowShouldClose(window, true);
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(1024, 768, "Compulsory 1", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return -1;
	}

	glViewport(0, 0, 1024, 720);
	glfwSetKeyCallback(window, processInput);

	GLuint VBO, VAO;
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);

	GLfloat borderColor[] = {
		1.0f, 1.f, 0.0f, 1.0f
	};
	glLineWidth(3);

	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint CurrentProgram = glCreateProgram();
	glAttachShader(CurrentProgram, vertexShader);
	glAttachShader(CurrentProgram, fragmentShader);
	glLinkProgram(CurrentProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	Calculations calc;
	/* Task 1 */
	//const std::vector<Vertex> points = calc.PointsInGraph(-10, 30,	0.001f);

	/* Task 2 */
	const std::vector<Vertex> points = calc.Spiral(0.001f);

	/* Task 3 */
	//calc.CreatePlane();

	glBufferData(GL_ARRAY_BUFFER, points.size()*sizeof(Vertex), points.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 1);
	glBindVertexArray(1);

	glfwSwapBuffers(window);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(VAO);
		glUseProgram(CurrentProgram);
		glDrawArrays(GL_LINE_STRIP, 0, points.size());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(CurrentProgram);
	return 0;
}