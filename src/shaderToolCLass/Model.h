#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include "shader.h"
#include "Mesh.h"


class Model
{
public:
    /*  ����   */
    Model(char* path);
    void Draw(Shader& shader);
private:
    /*  ģ������  */
    std::vector<Mesh> m_meshes;
    std::string m_directory;
    /*  ����   */
    void loadModel(const std::string& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};