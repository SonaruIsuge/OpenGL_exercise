#include "Shape.h"

Shape::Shape() {
	shader = nullptr;
	points = nullptr;
	colors = nullptr;
	vtxNum = 0;

	VAO = 0;
	VBO = 0;

	modelViewLoc = 0;
	projLoc = 0;

	model = mat4(1);
	view = mat4(1);
	modelView = mat4(1);
	projection = mat4(1);

	updateProjMat = false;
	
	position = vec3(0);
	rotation = vec3(0);
	scale = vec3(1);
}


Shape::~Shape() {
	if (shader != nullptr) delete[] shader;
	if (points != nullptr) delete[] points;
	if (colors != nullptr) delete[] colors;
}


void Shape::Init(vec4 vColor, mat4 view, mat4 projection) {
	SetSingleColor(vColor);
	SetShader(view, projection);
}


void Shape::SetSingleColor(vec4 color) {
	for (int i = 0; i < vtxNum; i++) {
		colors[i] = color;
	}

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, vtxNum * sizeof(vec4), vtxNum * sizeof(vec4), colors);
}


void Shape::SetShader(mat4 viewMat, mat4 projectionMat) {
	shader = new Shader("./Shader/Simple2D.vs", "./Shader/Simple2D.frag");
	
	GLuint posLoc = glGetAttribLocation(shader->Program, "vPosition");
	glVertexAttribPointer(posLoc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(posLoc);

	GLuint colorLoc = glGetAttribLocation(shader->Program, "vColor");
	glVertexAttribPointer(colorLoc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(vtxNum * sizeof(vec4)));
	glEnableVertexAttribArray(colorLoc);

	modelViewLoc = glGetUniformLocation(shader->Program, "ModelView");
	view = viewMat;
	glUniformMatrix4fv(modelViewLoc, 1, GL_FALSE, value_ptr(view));

	projLoc = glGetUniformLocation(shader->Program, "Projection");
	projection = projectionMat;
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(projection));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void Shape::CreateBuffers() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vtxNum * sizeof(vec4) * 2, NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, vtxNum * sizeof(vec4), points);
	glBufferSubData(GL_ARRAY_BUFFER, vtxNum * sizeof(vec4), vtxNum * sizeof(vec4), colors);
}


void Shape::Draw() {
	shader->Use();
	glBindVertexArray(VAO);

	model = GetTRSMatrix();
	modelView = view * model;

	glUniformMatrix4fv(modelViewLoc, 1, GL_FALSE, value_ptr(modelView));

	if (updateProjMat) {
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(projection));
		updateProjMat = false;
	}

	glDrawArrays(GL_TRIANGLES, 0, vtxNum);
}


void Shape::SetViewMatrix(mat4& viewMat) {
	view = viewMat;
}


void Shape::SetProjectionMatrix(mat4& projMat) {
	projection = projMat;
	updateProjMat = true;
}


mat4 Shape::GetTRSMatrix() {
	// Model = [T][R][S][P] (only rotate with z axis because 2D)
	mat4 mt = mat4(1);

	mt = translate(mt, position) * rotate(mt, rotation.z, vec3(0.0f, 0.0f, 1.0f)) * glm::scale(mt, scale);

	return mt;
}