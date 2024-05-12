#include "Shader.h"
#include <iostream>
#include <fstream>

Shader* Shader::Instance()
{
    static Shader* shaderObject = new Shader();
    return shaderObject;
}

Shader::Shader()
{
    this->m_shaderProgramID = 0;
    this->m_vertexShaderID = 0;
    this->m_fragmentShaderID = 0;
}


GLuint Shader::GetShaderProgramID()
{
    return this->m_shaderProgramID;
}

bool Shader::CreateProgram()
{
    this->m_shaderProgramID = glCreateProgram();

    if (this->m_shaderProgramID == 0)
    {
        std::cout << "Error creating shader program" << std::endl;
        return false;
    }

    return true;
}

bool Shader::CreateShaders()
{
    this->m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

    if (this->m_vertexShaderID == 0)
    {
        std::cout << "Error creating vertex shader object" << std::endl;
        return false;
    }


    this->m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    if (this->m_fragmentShaderID == 0)
    {
        std::cout << "Error creating fragment shader object" << std::endl;
        return false;
    }

    return true;
}

bool Shader::CompileShaders(const std::string& filename, ShaderType shaderType)
{
    std::fstream file;
    std::string text;
    std::string sourceCode;


    this->m_shaderID = (shaderType == ShaderType::VERTEX_SHADER) ? m_vertexShaderID : m_fragmentShaderID;

    file.open(filename);
    if (!file)
    {
        std::cout << "Error reading shader file. " << filename << std::endl;
        return false;
    }

    while (!file.eof())
    {
        std::getline(file, text);
        sourceCode += text + "\n";
    }

    //std::cout << "this is sourcefile: " << sourceCode << std::endl;

    file.close();

    const GLchar* finalSourceCode = reinterpret_cast<const GLchar*>(sourceCode.c_str());

    glShaderSource(this->m_shaderID, 1, &finalSourceCode, nullptr); // binding
    glCompileShader(this->m_shaderID);

   
   this->ErrorManagement(Shader::IDType::SHADER_ID);

    return true;
}

void Shader::AttachShaders()
{

    glAttachShader(m_shaderProgramID, m_vertexShaderID);
    glAttachShader(m_shaderProgramID, m_fragmentShaderID);
   
}

bool Shader::LinkProgram()
{
    glLinkProgram(this->m_shaderProgramID);

    glUseProgram(this->m_shaderProgramID);

    this->ErrorManagement(Shader::IDType::PROGRAM_ID);


    return true;
}

void Shader::DetachShaders()
{
    glDetachShader(m_shaderProgramID, m_vertexShaderID);
    glDetachShader(m_shaderProgramID, m_fragmentShaderID);
}

void Shader::DestroyShaders()
{
    glDeleteShader(m_vertexShaderID);
    glDeleteShader(m_fragmentShaderID);
}


void Shader::DestroyProgram()
{
    glDeleteProgram(m_shaderProgramID);
}



bool Shader::ErrorManagement(IDType id)
{
    GLint errorCode;
    // Error Management
    if (id == Shader::IDType::SHADER_ID)
    {
        
        glGetShaderiv(this->m_shaderID, GL_COMPILE_STATUS, &errorCode);

        if (errorCode == GL_TRUE)
        {
            std::cout << "Shader compilation successful!" << std::endl;
            return true;
        }
        else
        {
            GLchar errorMessage[1000];
            GLsizei bufferSize = 1000;

            glGetShaderInfoLog(this->m_shaderID, bufferSize, &bufferSize, errorMessage);
            std::cout << errorMessage << std::endl;
            return false;
        }
    }

    if (id == Shader::IDType::PROGRAM_ID)
    {
        glGetProgramiv(this->m_shaderProgramID, GL_LINK_STATUS, &errorCode);

        if (errorCode == GL_TRUE)
        {
            std::cout << "Shader linking successful!" << std::endl;
            return true;
        }
        else
        {
            GLchar errorMessage[1000];
            GLsizei bufferSize = 1000;

            glGetProgramInfoLog(this->m_shaderProgramID, bufferSize, &bufferSize, errorMessage);
            std::cout << errorMessage << std::endl;
            return false;
        }
    }
}




// ===========================
// Sending uniforms overloads
bool Shader::SendUniformData(const std::string& uniformName, bool data)
{
    GLint ID = glGetUniformLocation(this->m_shaderProgramID, uniformName.c_str());
    if (ID == -1)
    {
        std::cout << "Shader variable " << uniformName << " not found or not used" << std::endl;
        return false;
    }

    glUniform1i(ID, data);

    return true;
}


bool Shader::SendUniformData(const std::string& uniformName, GLint data)
{
    GLint ID = glGetUniformLocation(this->m_shaderProgramID, uniformName.c_str());
    if (ID == -1)
    {
        std::cout << "Shader variable " << uniformName << " not found or not used" << std::endl;
        return false;
    }

    glUniform1i(ID, data);

    return true;
}

bool Shader::SendUniformData(const std::string& uniformName, GLuint data)
{
    GLint ID = glGetUniformLocation(this->m_shaderProgramID, uniformName.c_str());
    if (ID == -1)
    {
        std::cout << "Shader variable " << uniformName << " not found or not used" << std::endl;
        return false;
    }

    glUniform1ui(ID, data);

    return true;
}

bool Shader::SendUniformData(const std::string& uniformName, GLfloat data)
{
    GLint ID = glGetUniformLocation(this->m_shaderProgramID, uniformName.c_str());

    if (ID == -1)
    {
        std::cout << "Shader variable " << uniformName << " not found or not used" << std::endl;
        return false;
    }

    glUniform1f(ID, data);

    return true;
}

bool Shader::SendUniformData(const std::string& uniformName, GLfloat x, GLfloat y)
{
    GLint ID = glGetUniformLocation(this->m_shaderProgramID, uniformName.c_str());
    if (ID == -1)
    {
        std::cout << "Shader variable " << uniformName << " not found or not used" << std::endl;
        return false;
    }

    glUniform2f(ID, x,y);

    return true;
}

bool Shader::SendUniformData(const std::string& uniformName, GLfloat x, GLfloat y, GLfloat z)
{
    GLint ID = glGetUniformLocation(this->m_shaderProgramID, uniformName.c_str());
    if (ID == -1)
    {
        std::cout << "Shader variable " << uniformName << " not found or not used" << std::endl;
        return false;
    }

    glUniform3f(ID, x, y,z);

    return true;
}

bool Shader::SendUniformData(const std::string& uniformName, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    GLint ID = glGetUniformLocation(this->m_shaderProgramID, uniformName.c_str());
    if (ID == -1)
    {
        std::cout << "Shader variable " << uniformName << " not found or not used" << std::endl;
        return false;
    }

    glUniform4f(ID, x, y, z, w);

    return true;
}

bool Shader::SendUniformData(const std::string& uniformName, const glm::mat4& data)
{
    GLint ID = glGetUniformLocation(this->m_shaderProgramID, uniformName.c_str());
    if (ID == -1)
    {
        std::cout << "Shader variable " << uniformName << " not found or not used" << std::endl;
        return false;
    }

    glUniformMatrix4fv(ID,1, GL_FALSE, &data[0][0]); // &data[0][0] is the address of the first element

    return true;
}
