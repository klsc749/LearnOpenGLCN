#pragma once
#include <string>
#include <vector>
#include "GL/glew.h"

class CubeMap
{
private:
    unsigned int m_ID;
    std::vector<std::string> m_faces;
public:
    CubeMap(const std::string& path, const std::vector<std::string>& faces);
    ~CubeMap();
    void Bind() const;
    void UnBind() const;
};