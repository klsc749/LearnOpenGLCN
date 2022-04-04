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
    /*  函数   */
    Model(const char* path);
    ~Model();
    /// <summary>
    /// 绘制模型
    /// </summary>
    /// <param name="shader"></param>
    void Draw(Shader& shader);
private:
    /*  模型数据  */
    std::vector<Mesh*> m_meshes;
    std::string m_directory;
    /*  函数   */
    
    /// <summary>
    /// 加载模型
    /// </summary>
    /// <param name="path">模型地址</param>
    void loadModel(const std::string& path);
    /// <summary>
    /// 处理节点储存的模型信息
    /// </summary>
    /// <param name="node">节点</param>
    /// <param name="scene">场景</param>
    void processNode(aiNode* node, const aiScene* scene);
    /// <summary>
    /// 处理网格信息
    /// </summary>
    /// <param name="mesh">网格信息</param>
    /// <param name="scene">场景</param>
    /// <returns>返回网格指针</returns>
    Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
    /// <summary>
    /// 加载材质中的贴图
    /// </summary>
    /// <param name="mat">材质</param>
    /// <param name="type">类型</param>
    /// <param name="typeName">类型名称</param>
    /// <returns>Textures</returns>
    std::vector<Texture*> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};