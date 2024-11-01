#include <GL/glut.h>
#include <vector>
#include <cmath>

const int MESH_SIZE = 100;
const float MESH_SCALE = 50.0f;
const float PI = 3.14159f;

// Wave parameters
struct Wave {
    float amplitude;  // Height of the wave
    float wavelength; // Distance between wave peaks
    float speed;      // How fast the wave moves
    float direction;  // Direction angle in radians
};

std::vector<Wave> waves = {
    {0.5f, 8.0f, 4.0f, PI / 1.0f},
    //{0.3f, 4.0f, 0.5f, PI / 8.0f},
    {0.2f, 2.0f, 6.0f, PI / 4.0f}

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
    {-2.0f, Color(0.0f, 0.0f, 0.6f)},    // Deep blue for troughs
    {-1.0f, Color(0.0f, 0.2f, 0.8f)},    // Medium blue
    {0.0f, Color(0.0f, 0.4f, 1.0f)},     // Light blue
    {1.0f, Color(0.0f, 0.8f, 1.0f)},     // Cyan
    {2.0f, Color(1.0f, 1.0f, 1.0f)}      // White for peaks
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

    drawWaterMesh();

    glutSwapBuffers();
}

void update(int value) {
    time += 0.016f;
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
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
    case 'r':
        cameraX = 0.0f;
        cameraY = 30.0f;
        cameraZ = 60.0f;
        break;
    case 27:
        exit(0);
        break;
    }
    glutPostRedisplay();
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.2f, 1.0f);

    // Disable lighting as we're using custom colors
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
    glutCreateWindow("Gerstner Waves - Height-Based Colors");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}