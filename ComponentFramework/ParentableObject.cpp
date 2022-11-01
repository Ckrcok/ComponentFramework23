#include "ParentableObject.h"

#include "MMath.h"

ParentableObject::ParentableObject(Mesh *mesh_, Shader *shader_, Texture *texture_):
	parent(nullptr), mesh(mesh_), shader(shader_), texture(texture_) {	
}

ParentableObject::ParentableObject(ParentableObject* parent_, Mesh* mesh_, Shader* shader_, Texture* texture_) :
	parent(parent_), mesh(mesh_), shader(shader_), texture(texture_) {
}

ParentableObject::~ParentableObject() {}

bool ParentableObject::OnCreate() { return true;  }
void ParentableObject::OnDestroy() {}
void ParentableObject::Update(float deltaTime_) {}

void ParentableObject::Render() const {

	Matrix4 parentModelMatrix;
	if(parent != nullptr){
		/// you are the child
		parentModelMatrix = parent->getModelMatrix();
	}
	
	
	glUniformMatrix4fv(shader->getUniformID("modelMatrix"), 1, GL_FALSE, (parentModelMatrix * modelMatrix) );

	Matrix3 normalMatrix = MMath::transpose(MMath::inverse( (parentModelMatrix * modelMatrix) ));
	glUniformMatrix3fv(shader->getUniformID("normalMatrix"), 1, GL_FALSE, normalMatrix);
	
	if (texture) {
		glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
	}
	mesh->Render();

	/// Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

void ParentableObject::HandleEvents(const SDL_Event &event) {} /// Just a stub