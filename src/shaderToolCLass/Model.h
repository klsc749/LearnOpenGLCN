#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include "shader.h"
#include "Mesh.h"

Texture TextureFromFile(const char* path, const std::string& directory);
class Model
{
public:
    // model data 
    std::vector<Texture*> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    bool gammaCorrection;
    /*  ����   */
    Model(const char* path);
    ~Model();
    /// <summary>
    /// ����ģ��
    /// </summary>
    /// <param name="shader"></param>
    void Draw(Shader& shader);
private:
    /*  ģ������  */
    std::vector<Mesh*> m_meshes;
    std::string m_directory;
    /*  ����   */
    
    /// <summary>
    /// ����ģ��
    /// </summary>
    /// <param name="path">ģ�͵�ַ</param>
    void loadModel(const std::string& path);
    /// <summary>
    /// ����ڵ㴢���ģ����Ϣ
    /// </summary>
    /// <param name="node">�ڵ�</param>
    /// <param name="scene">����</param>
    void processNode(aiNode* node, const aiScene* scene);
    /// <summary>
    /// ����������Ϣ
    /// </summary>
    /// <param name="mesh">������Ϣ</param>
    /// <param name="scene">����</param>
    /// <returns>��������ָ��</returns>
    Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
    /// <summary>
    /// ���ز����е���ͼ
    /// </summary>
    /// <param name="mat">����</param>
    /// <param name="type">����</param>
    /// <param name="typeName">��������</param>
    /// <returns>Textures</returns>
    std::vector<Texture*> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};