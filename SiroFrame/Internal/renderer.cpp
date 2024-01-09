#include <SiroFrame/Internal/renderer.h>
#include <SiroFrame/pencil.h>
#include <glad/glad.h>
#include <stdio.h>

#define RGB_OFF 0,0,0
#define RGB_BLK 0,0,0
#define RGB_DBLU 29, 43, 83
#define RGB_DPUR 126, 37, 83
#define RGB_DGRN 0, 135, 81
#define RGB_BRN 171, 82, 54
#define RGB_DGRY 95, 87, 79
#define RGB_LGRY 194, 195, 199
#define RGB_WHT 255, 241, 232
#define RGB_RED 255, 0, 77
#define RGB_ORN 255, 163, 0
#define RGB_YLW 255, 236, 39
#define RGB_GRN 0, 228, 54
#define RGB_BLU 41, 173, 255
#define RGB_LAV 131, 118, 156
#define RGB_PNK 255, 119, 168
#define RGB_PCH 255, 204, 170

const char* vertex_shader =
"#version 330 core\n"
"layout(location = 0) in vec4 vertexPosition;\n"
"out vec2 UV;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(vertexPosition.x ,vertexPosition.y,0.0f, 1.0f);\n"
"	UV = vec2(vertexPosition.z ,vertexPosition.w);\n"
"};\0";

const char* fragment_shader =
"#version 330 core\n"
"in vec2 UV;\n"
"out vec4 FragColor;\n"
"uniform sampler2D TextureSampler;\n"
"uniform sampler1D PaletteSampler;\n"
"void main()\n"
"{\n"
"   float index = texture2D(TextureSampler, UV).r;\n"
"   vec4 texel = texelFetch(PaletteSampler, int(index * 255), 0);\n"
"	FragColor = texel;\n"
"};\0";

SiroRenderer* SiroRenderer::_instance = 0;

SiroRenderer::SiroRenderer() {
    shaderProgram = 0;
	vertexbuffer = 0;
	TextureSampler = 0;
	PaletteSampler = 0;
	EBO = 0;

    for (int i = 0; i < WIN_WIDTH; i++) {
        for (int j = 0; j < WIN_HEIGHT; j++) {
            pixelbuffer[j][i] = 0;
        }
    }
}

void SiroRenderer::SetupRenderer() {
    // Compile Vertex Shader
    GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertexShader, 1, &vertex_shader, nullptr);
    glCompileShader(VertexShader);

    // Check Vertex Shader
    //glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &Result);
    //glGetShaderiv(VertexShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
    //if (InfoLogLength > 0) {
    //    std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
    //    glGetShaderInfoLog(VertexShader, InfoLogLength, nullptr, &VertexShaderErrorMessage[0]);
    //    printf("%s", &VertexShaderErrorMessage[0]);
    //}

    // Compile Fragment Shader
    GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShader, 1, &fragment_shader, nullptr);
    glCompileShader(FragmentShader);

    // Check Fragment Shader
    //glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &Result);
    //glGetShaderiv(FragmentShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
    //if (InfoLogLength > 0) {
    //    std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
    //    glGetShaderInfoLog(FragmentShader, InfoLogLength, nullptr, &FragmentShaderErrorMessage[0]);
    //    printf("%s", &FragmentShaderErrorMessage[0]);
    //}

    // Link the program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, VertexShader);
    glAttachShader(shaderProgram, FragmentShader);
    glLinkProgram(shaderProgram);

    // Check the program
    //glGetProgramiv(shaderProgram, GL_LINK_STATUS, &Result);
    //glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &InfoLogLength);
    //if (InfoLogLength > 0) {
    //    std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
    //    glGetProgramInfoLog(shaderProgram, InfoLogLength, nullptr, &ProgramErrorMessage[0]);
    //    printf("%s", &ProgramErrorMessage[0]);
    //}

    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);

    glUseProgram(shaderProgram);

    GLuint Init;
    glGenVertexArrays(1, &Init);
    glBindVertexArray(Init);

    static const GLfloat GS_vertex_buffer_data[] = {
        -1.0f,  1.0f,  0.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 1.0f,
    };
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GS_vertex_buffer_data), GS_vertex_buffer_data, GL_STATIC_DRAW);


    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(0, &TextureSampler);
    glBindTexture(GL_TEXTURE_2D, TextureSampler);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, WIN_WIDTH, WIN_HEIGHT, 0, GL_RED, GL_UNSIGNED_BYTE, pixelbuffer);
    glUniform1i(glGetUniformLocation(shaderProgram, "TextureSampler"), 0);

    unsigned char palette[64] = {
        RGB_BLK, RGB_DBLU,RGB_DPUR,RGB_DGRN,RGB_BRN,RGB_DGRY,RGB_LGRY,RGB_WHT,RGB_RED,RGB_ORN,RGB_YLW,RGB_GRN,RGB_BLU,RGB_LAV,RGB_PNK,RGB_PCH 
    };

    glActiveTexture(GL_TEXTURE1);
    glGenTextures(1, &PaletteSampler);
    glBindTexture(GL_TEXTURE_1D, PaletteSampler);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, 16, 0, GL_RGB, GL_UNSIGNED_BYTE, palette);
    glUniform1i(glGetUniformLocation(shaderProgram, "PaletteSampler"), 1);

    glActiveTexture(GL_TEXTURE0);
}

void SiroRenderer::UpdateGameScreen(void) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TextureSampler);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, WIN_WIDTH, WIN_HEIGHT, GL_RED, GL_UNSIGNED_BYTE, pixelbuffer);
}

void SiroRenderer::DrawGameScreen(void) {
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        4,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                   // stride
        (void*)0            // array buffer offset
    );
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(0);
}
