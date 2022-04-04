#include "Mesh.h"

/// <summary>
/// 初始化顶点，索引，纹理数据
/// </summary>
/// <param name="vertices"></param>
/// <param name="indices"></param>
/// <param name="textures"></param>
Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture*>& textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
	SetUpMesh();
}

/// <summary>
/// 设置缓冲
/// </summary>
void Mesh::SetUpMesh()
{
    m_vertexLayout.Push<float>(3);
    m_vertexLayout.Push<float>(3);
    m_vertexLayout.Push<float>(2);
    m_vertexLayout.Push<float>(3);
    m_vertexLayout.Push<float>(3);

    m_VBO.SetData(&vertices[0], vertices.size() * sizeof(Vertex));
    m_IBO.SetData(&indices[0], indices.size());
    m_VAO.AddBuffer(m_VBO, m_vertexLayout);
}

/// <summary>
/// 绘制面
/// </summary>
/// <param name="shader"></param>
void Mesh::Draw(Shader& shader)
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    //绑定纹理图片到相对位置
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        std::string number;
        std::string name = textures[i]->GetTextureType();
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++);

        shader.SetFloat((name + number).c_str(), i);
       

        textures[i]->Bind(i);
    }

    //绘制网格
    Renderer renderer;
    renderer.Draw(m_VAO, m_IBO, shader);
}

Mesh::~Mesh()
{
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        delete textures[i];
    }
}