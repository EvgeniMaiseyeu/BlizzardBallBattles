#include "shader.h"

Shader::Shader(const GLchar *vertexPath, const GLchar *fragmentPath) {
  //1. Retrieve the vertex/fragment source code from filePath
  string vertexCode, fragmentCode;
  ifstream vShaderFile, fShaderFile;

  //Ensure ifstream objects can throw exceptions
  vShaderFile.exceptions(ifstream::badbit);
  fShaderFile.exceptions(ifstream::badbit);

  try {
    //Open files for reading
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);
    stringstream vShaderStream, fShaderStream;

    //Read file's buffer contents into the streams
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    vShaderFile.close();
    fShaderFile.close();

    //Stream to string
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
  }
  catch (ifstream::failure e) {
    cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << endl;
  }
  const GLchar* vShaderCode = vertexCode.c_str();
  const GLchar* fShaderCode = fragmentCode.c_str();

  //2. Compile shaders
  GLuint vertex, fragment;
  GLint success;
  GLchar infoLog[512];

  //Vertex Shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);

  //Error check
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
  }

  //Fragmemt Shader
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);

  //Error check
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
  }

  //Create Shader Program
  this->Program = glCreateProgram();
  glAttachShader(this->Program, vertex);
  glAttachShader(this->Program, fragment);
  glLinkProgram(this->Program);

  //Error check
  glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
    cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
  }

  //Delete shaders as they're linked
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

void Shader::Use() {
  glUseProgram(this->Program);
}