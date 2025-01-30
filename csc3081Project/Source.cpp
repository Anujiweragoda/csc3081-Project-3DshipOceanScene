#include <cstdlib>
#include <GL/glut.h>
#include <vector>
#include <cmath>
#include <SOIL2.h>


const int MESH_SIZE = 100;
const float MESH_SCALE = 200.0f;
const float PI = 3.14159f;

float orbitAngle = 0.0f;
float orbitRadius = 10.0f;  
float fov = 45.0f;  
static float lightBeamAngle = 0.0f;



float shipX = -50.0f;         // Start position (off-screen left)
float shipY = 0.0f;           // Vertical position
float shipRoll = 0.0f;        // Rolling angle
float shipTime = 0.0f;       
float autoMoveSpeed = 0.1f;   
float screenWidth = 100.0f;   
float bobAmplitude = 0.5f;    
float rollAmplitude = 2.0f;


//variables to move the camera
GLfloat camX = 0.0; GLfloat camY = 0.0; GLfloat camZ = 0.0;

//variables to move the scene
GLfloat sceRX = 0.0; GLfloat sceRY = 0.0; GLfloat sceRZ = 0.0;
GLfloat sceTX = 0.0; GLfloat sceTY = 0.0; GLfloat sceTZ = 0.0;

////variables to move the objects
GLfloat objRX = 0.0; GLfloat objRY = 0.0; GLfloat objRZ = 0.0;
GLfloat objTX = 0.0; GLfloat objTY = 0.0; GLfloat objTZ = 0.0;


int width;
int height;

unsigned char* image;
unsigned char* image2;
unsigned char* image3;
unsigned char* image4;
unsigned char* image5;
unsigned char* image6;
unsigned char* image7;
unsigned char* image8;
unsigned char* image9;
unsigned char* image10;
unsigned char* image11;
unsigned char* image12;
unsigned char* image13;

GLuint tex;
GLuint tex2;
GLuint tex3;
GLuint tex4;
GLuint tex5;
GLuint tex6;
GLuint tex7;
GLuint tex8;
GLuint tex9;
GLuint tex10;
GLuint tex11;
GLuint tex12;
GLuint tex13;


void loadTextures() {
    glGenTextures(1, &tex);
    image = SOIL_load_image("wall.jpeg", &width, &height, 0, SOIL_LOAD_RGB);
    if (image == NULL) {
        printf("Error : %s", SOIL_last_result());
    }

    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glGenTextures(1, &tex2);
    image2 = SOIL_load_image("roof3.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    if (image2 == NULL) {
        printf("Error : %s", SOIL_last_result());
    }

    glBindTexture(GL_TEXTURE_2D, tex2);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


    glGenTextures(1, &tex3);
    image3 = SOIL_load_image("rock2.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    if (image3 == NULL) {
        printf("Error : %s", SOIL_last_result());
    }

    glBindTexture(GL_TEXTURE_2D, tex3);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image3);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glGenTextures(1, &tex4);
    image4 = SOIL_load_image("leaves3.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    if (image4 == NULL) {
        printf("Error : %s", SOIL_last_result());
    }

    glBindTexture(GL_TEXTURE_2D, tex4);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image4);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glGenTextures(1, &tex5);
    image5 = SOIL_load_image("side.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    if (image5 == NULL) {
        printf("Error : %s", SOIL_last_result()); 
    }

    glBindTexture(GL_TEXTURE_2D, tex5);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image5);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glGenTextures(1, &tex6);
    image6 = SOIL_load_image("shipcabin.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    if (image6 == NULL) {
        printf("Error : %s", SOIL_last_result());
    }

    glBindTexture(GL_TEXTURE_2D, tex6);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image6);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    
    glGenTextures(1, &tex7);
    image7 = SOIL_load_image("window1.jpeg", &width, &height, 0, SOIL_LOAD_RGB);
    if (image7 == NULL) {
        printf("Error : %s", SOIL_last_result());
    }

    glBindTexture(GL_TEXTURE_2D, tex7);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image7);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glGenTextures(1, &tex8);
    image8 = SOIL_load_image("side2.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    if (image8 == NULL) {
        printf("Error : %s", SOIL_last_result());
    }

    glBindTexture(GL_TEXTURE_2D, tex8);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image8);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


    glGenTextures(1, &tex9);
    image9 = SOIL_load_image("sand.jpeg", &width, &height, 0, SOIL_LOAD_RGB);
    if (image9 == NULL) {
        printf("Error : %s", SOIL_last_result());
    }

    glBindTexture(GL_TEXTURE_2D, tex9);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image9);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


    glGenTextures(1, &tex10);
    image10 = SOIL_load_image("sky.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    if (image10 == NULL) {
        printf("Error : %s", SOIL_last_result());
    }

    glBindTexture(GL_TEXTURE_2D, tex10);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image10);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);



    glGenTextures(1, &tex11);
    image11 = SOIL_load_image("floor3.jpeg", &width, &height, 0, SOIL_LOAD_RGB);
    if (image11 == NULL) {
        printf("Error : %s", SOIL_last_result());
    }

    glBindTexture(GL_TEXTURE_2D, tex11);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image11);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


    glGenTextures(1, &tex12);
    image12 = SOIL_load_image("mountain.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    if (image12 == NULL) {
        printf("Error : %s", SOIL_last_result());
    }

    glBindTexture(GL_TEXTURE_2D, tex12);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image12);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


    glGenTextures(1, &tex13);
    image13 = SOIL_load_image("rope.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    if (image13 == NULL) {
        printf("Error : %s", SOIL_last_result());
    }

    glBindTexture(GL_TEXTURE_2D, tex13);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image13);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

}
   

void setLightingAndShading() {

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);  
    glEnable(GL_LIGHT1);  
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);

    // Set material properties
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glShadeModel(GL_SMOOTH);

    
    GLfloat moonPosition[] = { 50.0f, 80.0f, 30.0f, 0.0f };
    GLfloat moonAmbient[] = { 0.2f, 0.2f, 0.25f, 1.0f };    
    GLfloat moonDiffuse[] = { 0.3f, 0.3f, 0.4f, 1.0f };     
    GLfloat moonSpecular[] = { 0.2f, 0.2f, 0.25f, 1.0f };

    
    GLfloat fillPosition[] = { -50.0f, 100.0f, -50.0f, 0.0f };
    GLfloat fillAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat fillDiffuse[] = { 0.15f, 0.15f, 0.15f, 1.0f };
    GLfloat fillSpecular[] = { 0.1f, 0.1f, 0.1f, 1.0f };


    glLightfv(GL_LIGHT0, GL_POSITION, moonPosition);
    glLightfv(GL_LIGHT0, GL_AMBIENT, moonAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, moonDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, moonSpecular);

    glLightfv(GL_LIGHT1, GL_POSITION, fillPosition);
    glLightfv(GL_LIGHT1, GL_AMBIENT, fillAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, fillDiffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, fillSpecular);

    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.05f);      
    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.01f);   

  
    GLfloat globalAmbient[] = { 0.15f, 0.15f, 0.17f, 1.0f };   
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glShadeModel(GL_SMOOTH);
    glColor3f(1, 1, 1);
}

// Wave parameters
struct Wave {
    float amplitude;  // Height of the wave
    float wavelength; // Distance between wave peaks
    float speed;      // How fast the wave moves
    float direction;  // Direction angle in radians
};

std::vector<Wave> waves = {
    {0.5f, 10.0f, 4.0f, PI / 4.0f},
    {0.3f, 8.0f, 2.0f, PI / 8.0f},
    {0.2f, 6.0f, 3.0f, PI / 2.0f},
    {0.1f, 4.0f, 1.0f, 3.0f * PI / 4.0f}
};

float time = 0.0f;
float cameraX = 0.0f;
float cameraY = 30.0f;
float cameraZ = 60.0f;
bool wireframeMode = true;

// Color structure for interpolation
struct Color {
    float r, g, b;
    Color(float r, float g, float b) : r(r), g(g), b(b) {}
};

// Define color gradient stops based on height
const std::vector<std::pair<float, Color>> colorGradient = {
    {-2.0f, Color(0.07f, 0.19f, 0.41f)},   // Deep blue for troughs
    {-1.0f, Color(0.11f, 0.32f, 0.58f)},   // Medium blue
    {0.0f, Color(0.15f, 0.45f, 0.75f)},    // Light blue
    {1.0f, Color(0.64f, 0.84f, 0.92f)},    // Light cyan
    {2.0f, Color(0.88f, 0.95f, 0.98f)}     // White for peaks
};

// Interpolate between colors based on height
Color getColorForHeight(float height) {
    // Find the color stops to interpolate between
    size_t i = 0;
    while (i < colorGradient.size() - 1 && height > colorGradient[i + 1].first) {
        i++;
    }

    if (i >= colorGradient.size() - 1) {
        return colorGradient.back().second;
    }

    // Calculate interpolation factor
    float lower = colorGradient[i].first;
    float upper = colorGradient[i + 1].first;
    float factor = (height - lower) / (upper - lower);
    factor = std::max(0.0f, std::min(1.0f, factor));

    // Interpolate between colors
    const Color& c1 = colorGradient[i].second;
    const Color& c2 = colorGradient[i + 1].second;

    return Color(
        c1.r + (c2.r - c1.r) * factor,
        c1.g + (c2.g - c1.g) * factor,
        c1.b + (c2.b - c1.b) * factor
    );
}

// Calculate Gerstner wave position
void calculateWavePoint(float x, float z, float& outX, float& outY, float& outZ) {
    outX = x;
    outY = 0.0f;
    outZ = z;

    for (const Wave& wave : waves) {
        float k = 2.0f * PI / wave.wavelength;
        float dotProduct = x * cos(wave.direction) + z * sin(wave.direction);
        float theta = k * dotProduct - wave.speed * time;

        outX += wave.amplitude * cos(wave.direction) * cos(theta);
        outY += wave.amplitude * sin(theta);
        outZ += wave.amplitude * sin(wave.direction) * cos(theta);
    }
}

void drawWaterMesh() {
    GLenum renderMode = wireframeMode ? GL_LINE_STRIP : GL_TRIANGLES;

    for (int i = 0; i < MESH_SIZE - 1; i++) {
        glBegin(renderMode);
        for (int j = 0; j < MESH_SIZE - 1; j++) {
            float x1 = (i - MESH_SIZE / 2.0f) * (MESH_SCALE / MESH_SIZE);
            float z1 = (j - MESH_SIZE / 2.0f) * (MESH_SCALE / MESH_SIZE);
            float x2 = ((i + 1) - MESH_SIZE / 2.0f) * (MESH_SCALE / MESH_SIZE);
            float z2 = ((j + 1) - MESH_SIZE / 2.0f) * (MESH_SCALE / MESH_SIZE);

            float px1, py1, pz1;
            float px2, py2, pz2;
            float px3, py3, pz3;
            float px4, py4, pz4;

            calculateWavePoint(x1, z1, px1, py1, pz1);
            calculateWavePoint(x2, z1, px2, py2, pz2);
            calculateWavePoint(x1, z2, px3, py3, pz3);
            calculateWavePoint(x2, z2, px4, py4, pz4);

            if (wireframeMode) {
                // In wireframe mode, use height-based colors 
                Color color = getColorForHeight(py1);
           
                float brightness = 0.5f;
                glColor3f(color.r + brightness, color.g + brightness, color.b + brightness);

                glVertex3f(px1, py1, pz1);
                glVertex3f(px2, py2, pz2);
                glVertex3f(px4, py4, pz4);
                glVertex3f(px3, py3, pz3);
                glVertex3f(px1, py1, pz1);  // Close the strip
            }
            else {
                // Use height-based colors for solid mode
                Color color1 = getColorForHeight(py1);
                glColor3f(color1.r, color1.g, color1.b);
                glVertex3f(px1, py1, pz1);

                Color color2 = getColorForHeight(py2);
                glColor3f(color2.r, color2.g, color2.b);
                glVertex3f(px2, py2, pz2);

                Color color3 = getColorForHeight(py3);
                glColor3f(color3.r, color3.g, color3.b);
                glVertex3f(px3, py3, pz3);

                // Second triangle
                glColor3f(color2.r, color2.g, color2.b);
                glVertex3f(px2, py2, pz2);

                Color color4 = getColorForHeight(py4);
                glColor3f(color4.r, color4.g, color4.b);
                glVertex3f(px4, py4, pz4);

                glColor3f(color3.r, color3.g, color3.b);
                glVertex3f(px3, py3, pz3);
            }
        }
        glEnd();
    }
}


/*________________BASIC SHAPES___________________________*/
void cylinder(float baseRadius, float  topRadius, float height) {

    GLUquadric* quad = gluNewQuadric();

    gluQuadricTexture(quad, GLU_TRUE);
    gluCylinder(quad, baseRadius, topRadius, height, 50, 50);

    // Bottom cap
    glPushMatrix();
    glRotatef(180, 1.0f, 0.0f, 0.0f);
    gluDisk(quad, 0.0, baseRadius, 50, 1);
    glPopMatrix();

    // Top cap
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, height);
    gluDisk(quad, 0.0, topRadius, 50, 1);
    glPopMatrix();

    gluDeleteQuadric(quad);
}
void torus(float innerRadius, float outerRadius) {
    glutSolidTorus(innerRadius, outerRadius, 50, 50);
}

void disk(float innerRadius, float outerRadius) {
    GLUquadric* quad = gluNewQuadric();
    gluDisk(quad, innerRadius, outerRadius, 50, 1);
    gluDeleteQuadric(quad);
}

void drawCylindersOnDiskEdge(float diskRadius, float cylinderRadius, float cylinderHeight, int numCylinders) {
    for (int i = 0; i < numCylinders; ++i) {
        // Calculate the angle for each cylinder
        float angle = 2.0f * PI * i / numCylinders;

        // Position the cylinder at the edge of the disk
        float x = diskRadius * cos(angle);
        float z = diskRadius * sin(angle);

        glPushMatrix();
        glTranslatef(x, 0.0f, z); // Move to the calculated position
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // Align cylinder vertically pointing upwards
        cylinder(cylinderRadius, cylinderRadius, cylinderHeight);
        glPopMatrix();
    }
}

void drawSphere(float radius, GLuint tex) {
    GLUquadric* quad = gluNewQuadric();
   
    gluQuadricTexture(quad, GL_TRUE); 

    glEnable(GL_TEXTURE_2D); 
    glBindTexture(GL_TEXTURE_2D, tex); 

    gluSphere(quad, radius, 32, 32); 
    glDisable(GL_TEXTURE_2D); 
    gluDeleteQuadric(quad); 
}

void drawCuboid(float width, float length, float height) {
    // Front face
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width / 2, -height / 2, length / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(width / 2, -height / 2, length / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(width / 2, height / 2, length / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width / 2, height / 2, length / 2);
    glEnd();

    // Back face
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width / 2, -height / 2, -length / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(width / 2, -height / 2, -length / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(width / 2, height / 2, -length / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width / 2, height / 2, -length / 2);
    glEnd();

    // Left face
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width / 2, -height / 2, -length / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-width / 2, -height / 2, length / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-width / 2, height / 2, length / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width / 2, height / 2, -length / 2);
    glEnd();

    // Right face
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(width / 2, -height / 2, -length / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(width / 2, -height / 2, length / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(width / 2, height / 2, length / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(width / 2, height / 2, -length / 2);
    glEnd();

    // Top face
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width / 2, height / 2, -length / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(width / 2, height / 2, -length / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(width / 2, height / 2, length / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width / 2, height / 2, length / 2);
    glEnd();

    // Bottom face
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width / 2, -height / 2, -length / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(width / 2, -height / 2, -length / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(width / 2, -height / 2, length / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width / 2, -height / 2, length / 2);
    glEnd();
}


void drawPyramid(float baseWidth, float baseLength, float height) {
    float halfWidth = baseWidth / 2.0f;
    float halfLength = baseLength / 2.0f;
    GLfloat vertices[][3] = {
        {  0.0f,  height / 2.0f,  0.0f },
        { -halfWidth, -height / 2.0f,  halfLength }, 
        {  halfWidth, -height / 2.0f,  halfLength }, 
        {  halfWidth, -height / 2.0f, -halfLength }, 
        { -halfWidth, -height / 2.0f, -halfLength }  
    };

    GLfloat normals[][3] = {
     
        {0.0f, -1.0f, 0.0f},
      
        {0.0f, 0.5f, 0.866f},
      
        {0.866f, 0.5f, 0.0f},
      
        {0.0f, 0.5f, -0.866f},
 
        {-0.866f, 0.5f, 0.0f}
    };

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex12);


    glBegin(GL_TRIANGLES);
    glNormal3fv(normals[0]);

    
    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertices[1]);
    glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertices[2]);
    glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertices[3]);

  
    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertices[1]);
    glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertices[3]);
    glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertices[4]);
    glEnd();

    glBegin(GL_TRIANGLES);

    glNormal3fv(normals[1]);
    glTexCoord2f(0.5f, 1.0f); glVertex3fv(vertices[0]);
    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertices[1]);
    glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertices[2]);

   
    glNormal3fv(normals[2]);
    glTexCoord2f(0.5f, 1.0f); glVertex3fv(vertices[0]);
    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertices[2]);
    glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertices[3]);

  
    glNormal3fv(normals[3]);
    glTexCoord2f(0.5f, 1.0f); glVertex3fv(vertices[0]);
    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertices[3]);
    glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertices[4]);


    glNormal3fv(normals[4]);
    glTexCoord2f(0.5f, 1.0f); glVertex3fv(vertices[0]);
    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertices[4]);
    glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertices[1]);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}


/*________________ END BASIC SHAPES___________________________*/


/*___________montaind__________________________________*/

void mountains() {
    // Enable transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // First mountain (closest)
    glPushMatrix();
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);  // Full opacity
    drawPyramid(20, 30, 10);
    glPopMatrix();

    // Second mountain
    glPushMatrix();
    glTranslated(5, 0, 0);
    glColor4f(1.0f, 1.0f, 1.0f, 0.8f);  // 80% opacity
    drawPyramid(20, 30, 20);
    glPopMatrix();

    // Third mountain
    glPushMatrix();
    glTranslated(10, 0, 0);
    glColor4f(1.0f, 1.0f, 1.0f, 0.6f);  // 60% opacity
    drawPyramid(20, 30, 30);
    glPopMatrix();

    // Fourth mountain
    glPushMatrix();
    glTranslated(15, 0, 0);
    glColor4f(1.0f, 1.0f, 1.0f, 0.4f);  // 40% opacity
    drawPyramid(20, 30, 20);
    glPopMatrix();

    // Fifth mountain (farthest)
    glPushMatrix();
    glTranslated(20, 0, 0);
    glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // 20% opacity
    drawPyramid(20, 30, 10);
    glPopMatrix();

    glDisable(GL_BLEND);
}

/*___________ End montaind__________________________________*/


/*________________COCONUT TREE__________________________*/

void triangle() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex4);
    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.5f, 1.0f); glVertex3f(0.0f, 3.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.7f, -0.7f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.7f, -0.7f, 0.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}


void drawTorus(float innerRadius, float outerRadius) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex3);
    glRotated(90.0, 1.0, 0.0, 0.0);
    glColor3f(0.36f, 0.25f, 0.20f);
    glutSolidTorus(innerRadius, outerRadius, 20, 20);
    glDisable(GL_TEXTURE_2D);
}



void drawLeaf() {
    glPushMatrix();
    triangle();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -0.8, 0); // Translate the second triangle to connect with the first
    glRotatef(170, 1, 0, 0); // Rotate the second triangle to face downward
    glScalef(1.5, 1, 0);
    triangle(); // Draw the second triangle
    glPopMatrix();
}

void top() {
    glColor3f(0.36f, 0.25f, 0.20f);
    drawSphere(0.15,0);

    float sphereRadius = 0.15;  // Radius of the sphere
    int numberOfLeaves = 8;     // Adjust to control how many leaves to place
    float angleStep = 360.0f / numberOfLeaves; // Spread leaves evenly

    for (int i = 0; i < numberOfLeaves; i++) {
        glPushMatrix();

        // Calculate the angle for each leaf's position on the sphere's surface
        float angle = i * angleStep;  // Distribute leaves evenly around the sphere

        // Position the leaves around the equator (XY plane) of the sphere
        float x = sphereRadius * cos(angle * PI / 360.0f); 
        float z = sphereRadius * sin(angle * PI / 360.0f); 

   
        glRotatef(-angle, 0, 1, 0); // Rotate around the Y-axis
        glRotatef(75, 1, 0, 0);     // Tilt upward for a natural appearance

        drawLeaf(); // Draw the leaf
        glPopMatrix();

    }
}

void drawTorusStack(int tall) {
    float xOffset = 0.0f;
    float yOffset = 0.0f;
    float innerRadius = 0.2f;
    float outerRadius = 0.3f;

    // Draw trunk
    for (int i = 0; i < tall; ++i) {
        glPushMatrix();
        glTranslatef(xOffset, yOffset, 0.0f);
        glColor3f(1.0, 0.5, 0.0); 
        drawTorus(innerRadius, outerRadius);
        glPopMatrix();

        // Stack with a slight tilt by updating xOffset and yOffset
        yOffset += 0.05f;
        xOffset += 0.01f;  // Adjust for a slight tilt along the X-axis

        // Gradually taper the trunk
        innerRadius -= 0.001f;
        outerRadius -= 0.001f;
    }
    glPushMatrix();
    glTranslatef(xOffset, yOffset, 0.0f);
    top();  // Assuming top() draws the object for the top of the stack
    glPopMatrix();
}
void drawCoconutTree() {
    glPushMatrix();
    drawTorusStack(200);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.6, 0, 0);
    glRotated(160, 0, 1, 0);
    drawTorusStack(240);
    glPopMatrix();
}

/*________________END COCONUT TREE__________________________*/





/*________________LIGHT HOUSE__________________________*/

void drawLightBeam() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);

    glPushMatrix();
   
    glRotatef(lightBeamAngle, 0.0, 1.0, 0.0);  // Rotate beam

    for (int beam = 0; beam < 2; beam++) {
        glRotatef(beam * 180, 0.0, 1.0, 0.0);  // Second beam opposite to first
        glBegin(GL_TRIANGLE_FAN);
        glColor4f(1.0, 1.0, 0.2, 0.4);  // Center color (more intense)
        glVertex3f(0.0, 0.0, 0.0);  // Beam origin

        glColor4f(1.0, 1.0, 0.0, 0.0);  // Outer color (fades to transparent)
        // Create cone shape
        float beamLength = 30.0;
        float beamWidth = 8.0;
        for (float angle = -40.0; angle <= 40.0; angle += 5.0) {
            float rad = angle * PI / 360.0;
            glVertex3f(sin(rad) * beamWidth, -beamLength, cos(rad) * beamWidth);
        }
        glEnd();

        // Add inner beam for more intensity
        glBegin(GL_TRIANGLE_FAN);
        glColor4f(1.0, 1.0, 0.4, 0.6);  // Inner beam (brighter)
        glVertex3f(0.0, 0.0, 0.0);

        glColor4f(1.0, 1.0, 0.2, 0.0);
        beamWidth = 4.0;  // Smaller width for inner beam
        for (float angle = -20.0; angle <= 20.0; angle += 5.0) {
            float rad = angle * PI / 180.0;
            glVertex3f(sin(rad) * beamWidth, -beamLength, cos(rad) * beamWidth);
        }
        glEnd();
    }

    glPopMatrix();
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}

void drawLighthouse() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor3f(1.0, 1.0, 1.0);

    glPushMatrix();
    glTranslatef(0, 0.0, 0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);
    cylinder(2.5, 1.5, 20);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    torus(0.2, 2.6);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 1.0, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    torus(0.2, 2.6);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0.2, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    torus(0.1, 2.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 20, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    torus(0.2, 1.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.3, 0.3, 0.3);
    glTranslatef(0.0, 20.2, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    disk(0.0, 2.0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);  
    glTranslatef(0.0, 20.2, 0.0);
    drawCylindersOnDiskEdge(2.0, 0.05, 1.5, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 20.2, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    cylinder(1.4, 1.2, 1.0);
    glPopMatrix();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPushMatrix();
    glColor4f(1.0, 1.0, 1.0, 0.5);
    glTranslatef(0.0, 20.4, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glDepthMask(GL_FALSE);
    cylinder(1.3, 1.2, 2.0);
    glDepthMask(GL_TRUE);
    glTranslatef(0.0,0, 1.0);
    glRotated(30, 0, 0, 1);
    drawLightBeam();
    glPopMatrix();

    glPushMatrix();
    glColor4f(1.0, 1.0, 0.0, 1.0);
    glTranslatef(0.0, 20.8, 0.0);
    glutSolidSphere(0.4, 50, 50);
    glPopMatrix();

    glDisable(GL_BLEND);

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(0.0, 20.8, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    torus(0.03, 2.0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(0.0, 21.5, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    torus(0.03, 2.0);
    glPopMatrix();


    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0.0, 22.2, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex2);
    cylinder(1.7, 0.1, 2.5);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.2, 0.2, 0.2);
    glTranslatef(0.0, 24.7, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    cylinder(0.05, 0.05, 1.0);
    glPopMatrix();
}

/*________________ END LIGHT HOUSE__________________________*/



/*___________SHIP______________________*/

void drawFront(float xOffset, float l,float w) {


    // First polygon
    glBegin(GL_POLYGON);
   // glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f(l, 0.01, w/2);
    glVertex3f((5 * l / 4) + xOffset, 0.01, 0);
    glVertex3f((5 * l / 4) + xOffset, 0, 0);
    glVertex3f(l, 0, w/2);
    glEnd();

    // Second polygon
    glBegin(GL_POLYGON);
    //glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f(l, 0,w/2);
    glVertex3f(l + 0.5, 0, w/2);
    glVertex3f((5 * l / 4) + 0.01 + xOffset, 0, 0);
    glVertex3f((5 * l / 4) + xOffset, 0, 0);
    glEnd();

    // Third polygon
    glBegin(GL_POLYGON);
   // glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f(l + 0.5, 0, w/2);
    glVertex3f((5 * l / 4) + 0.5 + xOffset, 0, 0);
    glVertex3f((5 * l / 4) + 0.5 + xOffset, 0.01, 0);
    glVertex3f(l + 0.5, 0.01,w/2);
    glEnd();

    // Fourth polygon
    glBegin(GL_POLYGON);
   // glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f(l + 0.5, 0.01, w/2);
    glVertex3f((5 * l / 4) + 0.2 + xOffset, 0.01, 0);
    glVertex3f((5 * l / 4) + xOffset, 0.01, 0);
    glVertex3f(l, 0.01, w/2);
    glEnd();

    // Fifth polygon
    glBegin(GL_POLYGON);
   // glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f((5 * l / 4) + xOffset, 0.01, 0);
    glVertex3f(l, 0.01, -w/2);
    glVertex3f(l, 0, -w/2);
    glVertex3f((5 * l / 4) + xOffset, 0, 0);
    glEnd();

    // Sixth polygon
    glBegin(GL_POLYGON);
    //glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f((5 * l / 4) + xOffset, 0, 0);
    glVertex3f((5 * l / 4) + 0.5 + xOffset, 0, 0);
    glVertex3f(l + 0.5, 0, -w/2);
    glVertex3f(l, 0, -w/2);
    glEnd();

    // Seventh polygon
    glBegin(GL_POLYGON);
    //glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f((5 * l / 4) + 0.5 + xOffset, 0, 0);
    glVertex3f(l + 0.5, 0, -w/2);
    glVertex3f(l + 0.5, 0.01, -w/2);
    glVertex3f((5 * l / 4) + 0.5 + xOffset, 0.01, 0);
    glEnd();

    // Eighth polygon
    glBegin(GL_POLYGON);
    //glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f((5 * l / 4) + xOffset, 0.01, 0);
    glVertex3f((5 * l / 4) + 0.1 + xOffset, 0.01, 0);
    glVertex3f(l + 0.5, 0.01, -w/2);
    glVertex3f(l, 0.01, -w/2);
    glEnd();

  
}

void drawStackOfFront(int numObjects, float l, float w) {
    float yOffset = 0.0f;
    float xOffset = 0.0f;

    for (int i = 0; i < numObjects; ++i) {
        glPushMatrix();
        glTranslatef(0.0f, yOffset, 0.0f);

        // Set color based on the position in the stack
        if (i < numObjects /4) {
            glColor3f(0.545, 0.0, 0.0); // Dark red
        }
        else {
            glColor3f(0.0f, 0.0f, 0.0f); // Black
        }

        // Draw the object (assumed to be a rectangle or similar)
        drawFront(xOffset, l, w);

        glPopMatrix();
        yOffset += 0.01f;
        xOffset += 0.01f;
    }
}


void drawMiddle( float l, float w) {

    glPushMatrix();
    glBegin(GL_POLYGON);
    //glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5 ,0.01,-w/2);
    glVertex3f(-0.5,0,-w/2);
    glVertex3f(l+0.5, 0, -w / 2);
    glVertex3f(l, 0.01, -w / 2);
    glEnd();

    glBegin(GL_POLYGON);
    //glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5, 0, -w / 2);
    glVertex3f(-0.5, 0,(-w / 2)+0.5 );
    glVertex3f(l+0.5, 0,(-w / 2) +0.5);
    glVertex3f(l, 0, -w / 2);
    glEnd();

    glBegin(GL_POLYGON);
    //glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5, 0.01, (-w / 2) + 0.5);
    glVertex3f(-0.5, 0, (-w / 2) + 0.5);
    glVertex3f(l+0.5, 0.01, (-w / 2) + 0.5);
    glVertex3f(l+0.5, 0, (-w / 2) + 0.5);
    glEnd();

    glBegin(GL_POLYGON);
    //glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5, 0.01, -w/2);
    glVertex3f(-0.5, 0.01, (-w / 2) + 0.5);
    glVertex3f(l+0.5, 0.01, (-w / 2) + 0.5);
    glVertex3f(l+0.5, 0.01, -w / 2);
    glEnd();

    glPopMatrix();
    /*-----------------------------*/

    glBegin(GL_POLYGON);
    //glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5, 0.01, w / 2);
    glVertex3f(-0.5, 0, w / 2);
    glVertex3f(l+0.5, 0, w / 2);
    glVertex3f(l+0.5, 0.01, w / 2);
    glEnd();

    glBegin(GL_POLYGON);
    //glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5, 0, w / 2);
    glVertex3f(-0.5, 0, (w / 2) - 0.5);
    glVertex3f(l+0.5, 0, (w / 2) - 0.5);
    glVertex3f(l+0.5, 0, w / 2);
    glEnd();

    glBegin(GL_POLYGON);
    //glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5, 0.01, (w / 2) - 0.5);
    glVertex3f(-0.5, 0, (w / 2) - 0.5);
    glVertex3f(l+0.5, 0.01, (w / 2) - 0.5);
    glVertex3f(l+0.5, 0, (w / 2) - 0.5);
    glEnd();

    glBegin(GL_POLYGON);
    //glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5, 0.01, w / 2);
    glVertex3f(-0.5, 0.01, (w / 2) - 0.5);
    glVertex3f(l+0.5, 0.01, (w / 2) - 0.5);
    glVertex3f(l+0.5, 0.01, w / 2);
    glEnd();


}

void drawStackOfMiddle(int numObjects, float l, float w) {
    float yOffset = 0.0f;

    for (int i = 0; i < numObjects; ++i) {
        glPushMatrix();
        glTranslatef(0.0f, yOffset, 0.0f);

        // Set color based on the position in the stack
        if (i < numObjects / 4) {
            glColor3f(0.545, 0.0, 0.0); // Dark red
        }
        else {
            glColor3f(0.0f, 0.0f, 0.0f); // Black
        }

        // Draw the object
        drawMiddle(l, w);

        glPopMatrix();
        yOffset += 0.01f;
    }
}


void drawRear(float zOffset,float l,float w) {


    glBegin(GL_POLYGON);
   // glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f((- l / 4)-0.5, 0, (-w / 4)-zOffset);
    glVertex3f((-l / 4), 0, (-w / 4) - zOffset);
    glVertex3f(0,0,-w/2);
    glVertex3f(-0.5, 0, -w / 2);
    glEnd();

    glBegin(GL_POLYGON);
    //glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f((-l / 4) - 0.5, 0, (-w / 4) - zOffset);
    glVertex3f((-l / 4) - 0.5, 0.01, (-w / 4) - zOffset);
    glVertex3f(-0.5, 0.01, -w / 2);
    glVertex3f(-0.5, 0, -w / 2);
    glEnd();

    glBegin(GL_POLYGON);
    //glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f((-l / 4), 0, (-w / 4) - zOffset);
    glVertex3f(0,0,-w/2);
    glVertex3f(0,0.01,-w/2);
    glVertex3f((-l / 4), 0.01, (-w / 4) - zOffset);
    glEnd();

    glBegin(GL_POLYGON);
   // glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f((-l / 4)-0.5, 0.01, (-w / 4) - zOffset);
    glVertex3f((-l / 4), 0.01, (-w / 4) - zOffset);
    glVertex3f(0,0.01,-w/2);
    glVertex3f(-0.5,0.01,-w/2);
    glEnd();


   /* ------------------ -*/
    glBegin(GL_POLYGON);
    //glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f((-l / 4) - 0.5, 0, (w / 4) + zOffset);
    glVertex3f((-l / 4) - 0.5, 0.01, (w / 4) + zOffset);
    glVertex3f((-l / 4) - 0.5, 0.01, (-w / 4) - zOffset);
    glVertex3f((-l / 4)-0.5, 0, (-w / 4) - zOffset);
    glEnd();

    glBegin(GL_POLYGON);
    //glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f((-l / 4) - 0.5, 0, (w / 4) + zOffset);
    glVertex3f((-l / 4) , 0, (w / 4) + zOffset);
    glVertex3f((-l / 4), 0, (-w / 4) - zOffset);
    glVertex3f((-l / 4)-0.5, 0, (-w / 4) - zOffset);
    glEnd();

    glBegin(GL_POLYGON);
    //glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f((-l / 4) , 0, (w / 4) + zOffset);
    glVertex3f((-l / 4), 0.01, (w / 4) + zOffset);
    glVertex3f((-l / 4), 0.01, (-w / 4) - zOffset);
    glVertex3f((-l / 4), 0, (-w / 4) - zOffset);
    glEnd();

    glBegin(GL_POLYGON);
    //glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f((-l / 4)-0.5, 0.01, (w / 4) + zOffset);
    glVertex3f((-l / 4), 0.01, (w / 4) + zOffset);
    glVertex3f((-l / 4), 0.01, (-w / 4) - zOffset);
    glVertex3f((-l / 4)-0.5, 0.01, (-w / 4) - zOffset);
    glEnd();

/*----------------------*/ 
    glBegin(GL_POLYGON);
    //glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f((-l / 4) - 0.5, 0, (w / 4) + zOffset);
    glVertex3f((-l / 4), 0, (w / 4) + zOffset);
    glVertex3f(0, 0, w / 2);
    glVertex3f(-0.5, 0, w / 2);
    glEnd();

    glBegin(GL_POLYGON);
    //glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f((-l / 4) - 0.5, 0, (w / 4) + zOffset);
    glVertex3f((-l / 4) - 0.5, 0.01, (w / 4) + zOffset);
    glVertex3f(-0.5, 0.01, w / 2);
    glVertex3f(-0.5, 0, w / 2);
    glEnd();

    glBegin(GL_POLYGON);
    //glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f((-l / 4), 0, (w / 4) + zOffset);
    glVertex3f(0, 0, w / 2);
    glVertex3f(0, 0.01, w / 2);
    glVertex3f((-l / 4), 0.01, (w / 4) + zOffset);
    glEnd();

    glBegin(GL_POLYGON);
    //glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f((-l / 4) - 0.5, 0.01, (w / 4) + zOffset);
    glVertex3f((-l / 4), 0.01, (w / 4) + zOffset);
    glVertex3f(0, 0.01, w / 2);
    glVertex3f(-0.5, 0.01, w / 2);
    glEnd();

}

void drawStackOfRear(int numObjects, float l, float w) {
    float yOffset = 0.0f;
    float zOffset = 0.0f;

    for (int i = 0; i < numObjects; ++i) {
        glPushMatrix();
        glTranslatef(0.0f, yOffset, 0.0f);

        // Set color based on the position in the stack
        if (i < numObjects / 4) {
            glColor3f(0.545, 0.0, 0.0); // Dark red
        }
        else {
            glColor3f(0.0f, 0.0f, 0.0f); // Black
        }

        // Draw the object (assumed to be a rectangle or similar)
        drawRear(zOffset, l, w);

        glPopMatrix();

        yOffset += 0.01f;
        zOffset += 0.01f;
    }
}



void drawBase(float xOffset, float zOffset, float w, float l, GLuint textureID) {
    // Enable texturing
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID); // Bind the texture

    glBegin(GL_POLYGON);
    // Define the vertices of the polygon with texture coordinates
    glTexCoord2f(1.0f, 1.0f); glVertex3f(l, 0.0f, -w / 2);               // Top-right
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, -w / 2);            // Top-left
    glTexCoord2f(0.0f, 0.5f); glVertex3f(-l / 4, 0.0f, (-w / 4) - zOffset);  // Offset back-left
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-l / 4, 0.0f, (w / 4) + zOffset);   // Offset front-left
    glTexCoord2f(0.5f, 0.0f); glVertex3f(0.0f, 0.0f, w / 2);             // Bottom-left
    glTexCoord2f(1.0f, 0.0f); glVertex3f(l, 0.0f, w / 2);                // Bottom-right
    glTexCoord2f(1.0f, 0.5f); glVertex3f(5.0f * l / 4 + xOffset, 0.0f, 0.0f); // Forward extension
    glEnd();

    // Disable texturing (optional)
    glDisable(GL_TEXTURE_2D);

    // Reset color to white
    glColor3f(1.0f, 1.0f, 1.0f);
}

void drawStackOfBase(int numObjects, float l, float w) {
    float yOffset = 0.0f;  // Increment for height
    float zOffset = 0.0f;  // Increment for depth
    float xOffset = 0.0f;  // Increment for forward extension

    for (int i = 0; i < numObjects; ++i) {
        glPushMatrix();

        // Apply translation for stacking
        glTranslatef(0.0f, yOffset, 0.0f);

        // Draw individual base
        drawBase(xOffset, zOffset, w, l,tex11);

        glPopMatrix();

        // Increment offsets for stacking
        xOffset += 0.01f;  // Slightly move forward
        yOffset += 0.01f;  // Increase height
        zOffset += 0.01f;  // Adjust depth
    }
}



void cabin(float length, float width, float height,GLuint tex) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);

    glBegin(GL_QUADS);

    // Front face
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width, -height, length);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(width, -height, length);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(width, height, length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width, height, length);

    // Back face
    glTexCoord2f(0.0f, 1.0f); glVertex3f(width, -height, -length);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-width, -height, -length);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-width, height, -length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(width, height, -length);

    // Left face
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width, -height, -length);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-width, -height, length);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-width, height, length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width, height, -length);

    // Right face
    glTexCoord2f(0.0f, 1.0f); glVertex3f(width, -height, length);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(width, -height, -length);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(width, height, -length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(width, height, length);

    // Top face
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width, height, length);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(width, height, length);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(width, height, -length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width, height, -length);

    // Bottom face
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width, -height, -length);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(width, -height, -length);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(width, -height, length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width, -height, length);

    glEnd();

    glDisable(GL_TEXTURE_2D);

}


void drawFence() {
    // Fence parameters
    double postRadius = 0.05;  // Radius of the vertical posts (cylinders)
    double postHeight = 1.0;  // Height of the vertical posts
    double barWidth = 0.01;    // Thickness of the horizontal bars
    double barHeight = 0.1;   // Height of the horizontal bars
    double cuboidSize = 9.9; // Size of the cuboid (length and width)

    // Draw vertical posts (cylinders) at the corners
    for (double x = -cuboidSize / 2; x <= cuboidSize / 2; x += cuboidSize) {
        for (double z = -cuboidSize / 2; z <= cuboidSize / 2; z += cuboidSize) {
            glPushMatrix();
            glTranslated(x, 0, z);       // Position at corner
            glRotated(-90, 1, 0, 0);    // Rotate cylinder to stand vertically
            cylinder(postRadius, postRadius, postHeight);
            glPopMatrix();
        }
    }

    // Draw horizontal bars along the edges
    for (double y = postHeight / 3; y < postHeight; y += barHeight * 1.5) {
        // Horizontal bars along the X-axis
        for (double z = -cuboidSize / 2; z <= cuboidSize / 2; z += cuboidSize) {
            glPushMatrix();
            glTranslated(0, y, z); // Position the bar
            drawCuboid(cuboidSize + postRadius * 2, barWidth, barWidth); // Extra width to span the corners
            glPopMatrix();
        }

        // Horizontal bars along the Z-axis
        for (double x = -cuboidSize / 2; x <= cuboidSize / 2; x += cuboidSize) {
            glPushMatrix();
            glTranslated(x, y, 0); // Position the bar
            glRotated(90, 0, 1, 0); // Rotate to align along Z-axis
            drawCuboid(cuboidSize + postRadius * 2, barWidth, barWidth);
            glPopMatrix();
        }
    }
}

void drawCuboidWithSelectiveTextures(double width, double height, double depth, GLuint texture) {
    // Enable texturing
    glEnable(GL_TEXTURE_2D);

    // Front face with texture1
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-width / 2, -height / 2, depth / 2);
    glTexCoord2f(1.0, 0.0); glVertex3f(width / 2, -height / 2, depth / 2);
    glTexCoord2f(1.0, 1.0); glVertex3f(width / 2, height / 2, depth / 2);
    glTexCoord2f(0.0, 1.0); glVertex3f(-width / 2, height / 2, depth / 2);
    glEnd();

    // Back face with texture 
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);glVertex3f(-width / 2, -height / 2, -depth / 2);
    glTexCoord2f(1.0, 0.0);glVertex3f(width / 2, -height / 2, -depth / 2);
    glTexCoord2f(1.0, 1.0);glVertex3f(width / 2, height / 2, -depth / 2);
    glTexCoord2f(0.0, 1.0);glVertex3f(-width / 2, height / 2, -depth / 2);
    glEnd();

    // Right face with texture2
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(width / 2, -height / 2, -depth / 2);
    glTexCoord2f(1.0, 0.0); glVertex3f(width / 2, -height / 2, depth / 2);
    glTexCoord2f(1.0, 1.0); glVertex3f(width / 2, height / 2, depth / 2);
    glTexCoord2f(0.0, 1.0); glVertex3f(width / 2, height / 2, -depth / 2);
    glEnd();


    // Remaining faces without texture
    glDisable(GL_TEXTURE_2D);
    // Left face 
    glBegin(GL_QUADS);
    glVertex3f(-width / 2, -height / 2, -depth / 2);
    glVertex3f(-width / 2, -height / 2, depth / 2);
    glVertex3f(-width / 2, height / 2, depth / 2);
    glVertex3f(-width / 2, height / 2, -depth / 2);
    glEnd();

    glBegin(GL_QUADS);
    // Top face
    glVertex3f(-width / 2, height / 2, -depth / 2);
    glVertex3f(width / 2, height / 2, -depth / 2);
    glVertex3f(width / 2, height / 2, depth / 2);
    glVertex3f(-width / 2, height / 2, depth / 2);
    // Bottom face
    glVertex3f(-width / 2, -height / 2, -depth / 2);
    glVertex3f(width / 2, -height / 2, -depth / 2);
    glVertex3f(width / 2, -height / 2, depth / 2);
    glVertex3f(-width / 2, -height / 2, depth / 2);
    glEnd();
}



void shipBridge() {
    glPushMatrix();
    cabin(5, 2.5, 8,tex6);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.8, 0.8, 0.8);
    glTranslated(0, 8.2, 0);
    glRotated(90,0,1,0);
    drawCuboid(20, 2.5, 2.5);
    glColor3f(1, 1, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, 4.0, 4.8);
    glRotated(-45, 1, 0, 0);
    cylinder(0.5, 0.5, 6);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, 7.2, -7.8);
    glRotated(45, 1, 0, 0);
    cylinder(0.5, 0.5, 6);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,9, 0);
    glRotated(90, 1, 0, 0);
    drawCuboid(10, 1.0, 10);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslated(0, 9, 0);
    drawFence();
    glColor3f(1, 1, 1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.8, 0.8, 0.8);
    glTranslated(0, 10.0, 0);
    drawCuboidWithSelectiveTextures(9.4, 2.0, 9.4,tex7);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,11, 0);
    glRotated(90, 1, 0, 0);
    drawCuboid(10, 0.5, 10);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.8, 0.8, 0.8);
    glTranslated(0, 11, 0);
    drawFence();
    glColor3f(1, 1, 1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.8, 0.8, 0.8);
    glTranslated(0, 11, 0);
    glRotated(-90, 1, 0, 0);
    cylinder(0.3, 0.1, 2.0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, 13, -0.5);     
    glTranslated(0, 0, 0.5);      
    glRotatef(objRY, 0, 1, 0);    
    glTranslated(0, 0, -0.5);      
    cylinder(0.2, 0.2, 1.0);      
    glPopMatrix();

    glPushMatrix();
    glTranslated(2, 11, -0.5);
    glRotated(-90, 1, 0, 0);
    cylinder(0.3, 0.1, 7.0);
    glTranslated(0,0,5.0);
    drawSphere(0.3, 0);
    glPopMatrix();



}

void drawContainer(double width, double height, double depth, GLuint texture) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    // Draw the container as a textured cuboid
    glBegin(GL_QUADS);
    // Front face
    glTexCoord2f(0.0, 0.0); glVertex3f(-width / 2, -height / 2, depth / 2);
    glTexCoord2f(1.0, 0.0); glVertex3f(width / 2, -height / 2, depth / 2);
    glTexCoord2f(1.0, 1.0); glVertex3f(width / 2, height / 2, depth / 2);
    glTexCoord2f(0.0, 1.0); glVertex3f(-width / 2, height / 2, depth / 2);

    // Back face
    glTexCoord2f(0.0, 0.0); glVertex3f(-width / 2, -height / 2, -depth / 2);
    glTexCoord2f(1.0, 0.0); glVertex3f(width / 2, -height / 2, -depth / 2);
    glTexCoord2f(1.0, 1.0); glVertex3f(width / 2, height / 2, -depth / 2);
    glTexCoord2f(0.0, 1.0); glVertex3f(-width / 2, height / 2, -depth / 2);

    // Right face
    glTexCoord2f(0.0, 0.0); glVertex3f(width / 2, -height / 2, -depth / 2);
    glTexCoord2f(1.0, 0.0); glVertex3f(width / 2, -height / 2, depth / 2);
    glTexCoord2f(1.0, 1.0); glVertex3f(width / 2, height / 2, depth / 2);
    glTexCoord2f(0.0, 1.0); glVertex3f(width / 2, height / 2, -depth / 2);

    // Left face
    glTexCoord2f(0.0, 0.0); glVertex3f(-width / 2, -height / 2, -depth / 2);
    glTexCoord2f(1.0, 0.0); glVertex3f(-width / 2, -height / 2, depth / 2);
    glTexCoord2f(1.0, 1.0); glVertex3f(-width / 2, height / 2, depth / 2);
    glTexCoord2f(0.0, 1.0); glVertex3f(-width / 2, height / 2, -depth / 2);

    // Top face
    glTexCoord2f(0.0, 0.0); glVertex3f(-width / 2, height / 2, -depth / 2);
    glTexCoord2f(1.0, 0.0); glVertex3f(width / 2, height / 2, -depth / 2);
    glTexCoord2f(1.0, 1.0); glVertex3f(width / 2, height / 2, depth / 2);
    glTexCoord2f(0.0, 1.0); glVertex3f(-width / 2, height / 2, depth / 2);

    // Bottom face
    glTexCoord2f(0.0, 0.0); glVertex3f(-width / 2, -height / 2, -depth / 2);
    glTexCoord2f(1.0, 0.0); glVertex3f(width / 2, -height / 2, -depth / 2);
    glTexCoord2f(1.0, 1.0); glVertex3f(width / 2, -height / 2, depth / 2);
    glTexCoord2f(0.0, 1.0); glVertex3f(-width / 2, -height / 2, depth / 2);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}
void drawContainerStack(){
    glPushMatrix();
    glTranslated(-0.2, 0, 0);
    drawContainer(6, 2, 4, tex5);

    glTranslated(6, 0, 0);
    drawContainer(6, 2, 4, tex5);

    glTranslated(6.5, 0, 0);
    drawContainer(7, 2, 4, tex8);

    glTranslated(-6, 1.72, 0);
    drawContainer(6, 1.5, 4, tex8);

    glTranslated(-14, -1.5, 0);
    drawContainer(4, 2, 4, tex5);


    glPopMatrix(); 
   
}



void drawShip(float l,float w) {

    glPushMatrix();

    glRotatef(shipRoll, 0, 0, 1);

    // Draw ship components
    drawStackOfFront(200, l, w);
    drawStackOfRear(200, l, w);
    drawStackOfMiddle(150, l, w);
    drawStackOfBase(130, l, w);

    // Draw bridge
    glPushMatrix();
    glColor3f(0.8, 0.8, 0.8);
    glTranslatef(0.5, 3.0, 0.0);
    glScalef(0.2, 0.2, 0.3);
    shipBridge();
    glPopMatrix();

    // Draw container stack
    glPushMatrix();
    glTranslatef(5.0, 2.0, 0.0);
    drawContainerStack();
    glPopMatrix();
    glPopMatrix();


    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex13);
    glTranslatef(23.0, 1.0, -0.4);
    cylinder(0.3, 0.3, 0.7);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    glPopMatrix();
   
  
    
}


/*_______________________END SHIP___________________________*/

/*--------------Island--------------------*/

void island() {
    glPushMatrix();

    glTranslated(0, -0.5, 0);

    glPushMatrix();
    glTranslated(0, 1.0, 0);
    glScalef(1.5, 0.3, 0.7);
    drawSphere(5.0,tex3);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, 0.0, 2.0);
    glRotated(90, 0, 1, 0);
    glScalef(2.0, 1.5,1.1);
    drawSphere(2.0, tex3);
    glPopMatrix();

    glPushMatrix();
    glTranslated(3.5, 0.8, 1.5);
    glScalef(0.7, 0.3,0.8);
    drawSphere(5.0, tex9);
    glPopMatrix();

    glPushMatrix();
    glTranslated(4.0,1.0, 3.0);
    glScalef(2.0,0.8, 0.9);
    drawSphere(2.0, tex3);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-0.7, 0.0, -2.0);
    glScalef(2.0, 2.0, 1.5);
    drawSphere(2.0, tex3);
    glPopMatrix();

    glPopMatrix();




}


/*-------------- end Island--------------------*/

void drawSkybox() {
    glPushMatrix();
    
    glDepthMask(GL_FALSE);

    glTranslatef(cameraX, cameraY, cameraZ);

    glDisable(GL_LIGHTING);

    float radius = 100.0f; 
    int slices = 32;       
    int stacks = 32;        

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex10);


    GLUquadric* quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    gluQuadricNormals(quadric, GLU_SMOOTH);

   
    glRotated(100, 1, 0, 0);
    glRotated(220, 0, 0, 1);
    glRotated(20, 1, 0, 0);
    glScalef(-1.0f, 1.0f, 1.0f);  // Flip the sphere inside out
    glTranslated(0, -90, 0);
    gluSphere(quadric, radius, slices, stacks);

    gluDeleteQuadric(quadric);

    // Clean up states
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glDepthMask(GL_TRUE);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    gluLookAt(cameraX, cameraY, cameraZ,
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);

    drawSkybox();
    

    glRotatef(sceRX, 1.0f, 0.0f, 0.0f);
    glRotatef(sceRY, 0.0f, 1.0f, 0.0f);
    glRotatef(sceRZ, 0.0f, 0.0f, 1.0f);
    glTranslatef(sceTX, sceTY, sceTZ);

    drawWaterMesh();
    glPushMatrix();
    glScalef(1.5, 1.5, 1.5);

    glPushMatrix();
    glTranslated(-35, 0, 20);
    glRotated(100,0,1,0);
    glPushMatrix();
    glColor3f(1, 1, 1);
    glScalef(1, 1, 1.5);
    island();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.8,2.0, 0.0);
    glScalef(0.5, 0.5, 0.5);
    drawLighthouse();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(4.2, 1.7, 1.8);
    glRotatef(80, 0, 1, 0);
    glScalef(0.3, 0.3, 0.3);
    drawCoconutTree();
    glPopMatrix();

    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-5.0, 0,-40.0);
    glScalef(0.9, 0.9, 0.9);

    glTranslatef(shipX, shipY, 0);

    shipRoll = sin(shipTime) * rollAmplitude;
    drawShip(20, 5);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(25.0,0, 45.0);
    glScalef(0.7, 0.7, 0.7);
    drawShip(20, 5);
    glPopMatrix();

    glPopMatrix();
    glTranslatef(-90.0, 0, 95.0);
    mountains();
    glPushMatrix();

    glPopMatrix();


    glPopMatrix();
    glTranslatef(-5.0, 0,0);
    glRotated(90, 0, 1, 0);
    glScalef(2, 1, 1);
    mountains();
    glPushMatrix();

    glPopMatrix();

   
    
    glutSwapBuffers();
}


void updateShip() {
    shipTime += 0.05f;
    
    shipX += autoMoveSpeed;
    
    if (shipX > screenWidth / 2) {
        shipX = -screenWidth / 2;
    }
    shipY = sin(shipTime * 0.5f) * bobAmplitude;
    
    glutPostRedisplay();
}


void update(int value) {
    time += 0.016f;
    lightBeamAngle += 1.0f;
   objRY += 2.0f;  
    if (lightBeamAngle >= 360.0f) {
        lightBeamAngle = 0.0f;
    }
   
    if (objRY >= 360.0f) {
       objRY = 0.0f; 
    }
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
    updateShip();


   
}

void updateCamera(int value) {
    glutPostRedisplay();
    glutTimerFunc(16, updateCamera, 0); 
}

void keyboardSpecial(int key, int x, int y) {
    float cameraSpeed = 2.0f;
    if (key == GLUT_KEY_UP)
        camY += cameraSpeed;

    if (key == GLUT_KEY_DOWN)
        camY -= cameraSpeed;

    if (key == GLUT_KEY_RIGHT)
        sceTX += 1;

    if (key == GLUT_KEY_LEFT)
        sceTX -= 1;

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    float cameraSpeed = 2.0f;
    float rotationSpeed = 1.0;

    switch (key) {
    case 'w':
    case 'W':
        wireframeMode = !wireframeMode;
        break;
    case 'a':
        cameraX -= cameraSpeed;
        break;
    case 'd':
        cameraX += cameraSpeed;
        break;
    case 's':   
        cameraY -= cameraSpeed;
        break;
    case 'e':
        cameraY += cameraSpeed;
        break;
    case 'q':
        cameraZ -= cameraSpeed;
        break;
    case 'z':
        cameraZ += cameraSpeed;
        break;
    case'y':
        sceRY += 1.0;
        break;  
    case 'r':
        cameraX = 80.0f;
        cameraY = 1.9f;
        cameraZ = -80.0f;
        break;

    case 't': 
        cameraX += 0.5f;
        glutTimerFunc(16, updateCamera, 0);  // Smooth motion over time
        break;
    case 'g':  // Reverse tracking shot
        cameraX -= 0.5f;
        glutTimerFunc(16, updateCamera, 0);
        break;
    case 'c':  // Crane up shot
        cameraY += 0.5f;
        cameraZ -= 0.5f;  // Move slightly backward while rising
        break;
    case 'v':  // Crane down shot
        cameraY -= 0.5f;
        cameraZ += 0.5f;  // Move slightly forward while descending
        break;
    case 'b':  // Dolly zoom (vertigo effect)
        cameraZ -= 0.5f;
        fov += 0.5f;  // Gradually increase field of view
        break;
    case 'o':  // Orbit right
        cameraX = cos(orbitAngle) * orbitRadius;
        cameraZ = sin(orbitAngle) * orbitRadius;
        orbitAngle += 0.02f;
        break;
    case 'p':  // Orbit left
        cameraX = cos(orbitAngle) * orbitRadius;
        cameraZ = sin(orbitAngle) * orbitRadius;
        orbitAngle -= 0.02f;
        break;
    case '[':  // Establish shot (pull back and up)
        cameraY += 0.05f;
        cameraZ += 0.5f;
        break;
    case ']':  // Push in shot
        cameraZ -= 0.08f;
        break;

    case '1':
        waves[0].amplitude = 0.5f;
        waves[0].wavelength = 10.0f;
        waves[0].speed = 4.0f;
        waves[0].direction = PI / 4.0f;
        break;
    case '2':
        waves[1].amplitude = 0.3f;
        waves[1].wavelength = 8.0f;
        waves[1].speed = 2.0f;
        waves[1].direction = PI / 8.0f;
        break;
    case '3':
        waves[2].amplitude = 0.2f;
        waves[2].wavelength = 6.0f;
        waves[2].speed = 3.0f;
        waves[2].direction = PI / 2.0f;
        break;
    case '4':
        waves[3].amplitude = 0.1f;
        waves[3].wavelength = 4.0f;
        waves[3].speed = 1.0f;
        waves[3].direction = 3.0f * PI / 4.0f;
        break;
    }
    glutPostRedisplay();
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
    glClearDepth(1.0);
    glDisable(GL_LIGHTING);
    loadTextures();


}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / h, 0.1f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
}

int main(void) {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Ocean");

    init();
    setLightingAndShading();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboardSpecial);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}
