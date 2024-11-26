//#include <cstdlib>
#include <GL/glut.h>
#include <vector>
#include <cmath>
#include <SOIL2.h>


const int MESH_SIZE = 100;
const float MESH_SCALE = 50.0f;
const float PI = 3.14159f;



//variables to move the camera
GLfloat camX = 0.0; GLfloat camY = 0.0; GLfloat camZ = 0.0;

//variables to move the scene
GLfloat sceRX = 0.0; GLfloat sceRY = 0.0; GLfloat sceRZ = 0.0;
GLfloat sceTX = 0.0; GLfloat sceTY = 0.0; GLfloat sceTZ = 0.0;

////variables to move the objects
GLfloat objRX = 0.0; GLfloat objRY = 0.0; GLfloat objRZ = 0.0;
GLfloat objTX = 0.0; GLfloat objTY = 0.0; GLfloat objTZ = 0.0;





void setLightingAndShading() {
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);  
    glEnable(GL_LIGHT1);  

 
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

   
    glShadeModel(GL_SMOOTH);

    GLfloat sunPosition[] = { 10.0f, 20.0f, 20.0f, 0.0f };  


    GLfloat sunAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };     
    GLfloat sunDiffuse[] = { 1.0f, 0.95f, 0.85f, 1.0f };  
    GLfloat sunSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };   


    GLfloat fillPosition[] = { -10.0f, 5.0f, -10.0f, 0.0f };
    GLfloat fillAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat fillDiffuse[] = { 0.3f, 0.3f, 0.4f, 1.0f };   

    glLightfv(GL_LIGHT0, GL_POSITION, sunPosition);
    glLightfv(GL_LIGHT0, GL_AMBIENT, sunAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sunDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, sunSpecular);

    glLightfv(GL_LIGHT1, GL_POSITION, fillPosition);
    glLightfv(GL_LIGHT1, GL_AMBIENT, fillAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, fillDiffuse);

   
    GLfloat globalAmbient[] = { 0.2f, 0.2f, 0.3f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

   
    glEnable(GL_DEPTH_TEST);
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
                // In wireframe mode, use height-based colors but brighter
                Color color = getColorForHeight(py1);
                // Brighten the wireframe colors
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



void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(cameraX, cameraY, cameraZ,
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f);

    glRotatef(sceRX, 1.0f, 0.0f, 0.0f);
    glRotatef(sceRY, 0.0f, 1.0f, 0.0f);
    glRotatef(sceRZ, 0.0f, 0.0f, 1.0f);
    glTranslatef(sceTX, sceTY, sceTZ);

    drawWaterMesh();
    glutSwapBuffers();
}

void update(int value) {
    time += 0.016f;
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void keyboardSpecial(int key, int x, int y) {
    if (key == GLUT_KEY_UP)
        camY += 1;

    if (key == GLUT_KEY_DOWN)
        camY -= 1;

    if (key == GLUT_KEY_RIGHT)
        sceTX += 1;

    if (key == GLUT_KEY_LEFT)
        sceTX -= 1;

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    float cameraSpeed = 2.0f;
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
        cameraX = 0.0f;
        cameraY = 30.0f;
        cameraZ = 60.0f;
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
    glDisable(GL_LIGHTING);


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
