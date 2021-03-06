﻿/**********************************************************************************************
*
*   raylib 1.6.0 (www.raylib.com)
*
*   A simple and easy-to-use library to learn videogames programming
*
*   Features:
*     Library written in plain C code (C99)
*     Uses C# PascalCase/camelCase notation
*     Hardware accelerated with OpenGL (1.1, 2.1, 3.3 or ES 2.0)
*     Unique OpenGL abstraction layer (usable as standalone module): [rlgl]
*     Powerful fonts module with SpriteFonts support (XNA bitmap fonts, AngelCode fonts, TTF)
*     Multiple textures support, including compressed formats and mipmaps generation
*     Basic 3d support for Shapes, Models, Billboards, Heightmaps and Cubicmaps
*     Materials (diffuse, normal, specular) and Lighting (point, directional, spot) support
*     Powerful math module for Vector, Matrix and Quaternion operations [raymath]
*     Audio loading and playing with streaming support and mixing channels (WAV, OGG, XM, MOD)
*     VR stereo rendering support with configurable HMD device parameters
*     Multiple platforms support: Windows, Linux, Mac, Android, Raspberry Pi, HTML5 and Oculus Rift CV1
*     Custom color palette for fancy visuals on raywhite background
*     Minimal external dependencies (GLFW3, OpenGL, OpenAL)
*
*   Used external libs:
*     GLFW3 (www.glfw.org) for window/context management and input
*     GLAD for OpenGL extensions loading (3.3 Core profile, only PLATFORM_DESKTOP)
*     stb_image (Sean Barret) for images loading (JPEG, PNG, BMP, TGA, PSD, GIF, HDR, PIC)
*     stb_image_write (Sean Barret) for image writting (PNG)
*     stb_vorbis (Sean Barret) for ogg audio loading
*     stb_truetype (Sean Barret) for ttf fonts loading
*     jar_xm (Joshua Reisenauer) for XM audio module loading
*     jar_mod (Joshua Reisenauer) for MOD audio module loading
*     OpenAL Soft for audio device/context management
*     tinfl for data decompression (DEFLATE algorithm)
*
*   Some design decisions:
*     32bit Colors - All defined color are always RGBA (struct Color is 4 byte)
*     One custom default font is loaded automatically when InitWindow()
*     If using OpenGL 3.3 or ES2, several vertex buffers (VAO/VBO) are created to manage lines-triangles-quads
*     If using OpenGL 3.3 or ES2, two default shaders are loaded automatically (internally defined)
*
*   -- LICENSE --
*
*   raylib is licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software:
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#ifndef RAYLIB_H
#define RAYLIB_H

// Choose your platform here or just define it at compile time: -DPLATFORM_DESKTOP
//#define PLATFORM_DESKTOP      // Windows, Linux or OSX
//#define PLATFORM_ANDROID      // Android device
//#define PLATFORM_RPI          // Raspberry Pi
//#define PLATFORM_WEB          // HTML5 (emscripten, asm.js)
//#define RLGL_OCULUS_SUPPORT   // Oculus Rift CV1 (complementary to PLATFORM_DESKTOP)

// Security check in case no PLATFORM_* defined
#if !defined(PLATFORM_DESKTOP) && !defined(PLATFORM_ANDROID) && !defined(PLATFORM_RPI) && !defined(PLATFORM_WEB)
    #define PLATFORM_DESKTOP
#endif

#if defined(PLATFORM_ANDROID)
    typedef struct android_app; // Define android_app struct (android_native_app_glue.h)
#endif

#if defined(_WIN32) && defined(BUILDING_DLL)
    #define RLAPI __declspec(dllexport)         // We are building raylib as a Win32 DLL
#elif defined(_WIN32) && defined(RAYLIB_DLL)
    #define RLAPI __declspec(dllimport)         // We are using raylib as a Win32 DLL
#else
    #define RLAPI   // We are building or using raylib as a static library (or Linux shared library)
#endif

//----------------------------------------------------------------------------------
// Some basic Defines
//----------------------------------------------------------------------------------
#ifndef PI
    #define PI 3.14159265358979323846
#endif

#define DEG2RAD (PI/180.0f)
#define RAD2DEG (180.0f/PI)

// raylib Config Flags
#define FLAG_FULLSCREEN_MODE    1
#define FLAG_SHOW_LOGO          2
#define FLAG_SHOW_MOUSE_CURSOR  4
#define FLAG_CENTERED_MODE      8
#define FLAG_MSAA_4X_HINT      16
#define FLAG_VSYNC_HINT        32

// Keyboard Function Keys
#define KEY_SPACE            32
#define KEY_ESCAPE          256
#define KEY_ENTER           257
#define KEY_BACKSPACE       259
#define KEY_RIGHT           262
#define KEY_LEFT            263
#define KEY_DOWN            264
#define KEY_UP              265
#define KEY_F1              290
#define KEY_F2              291
#define KEY_F3              292
#define KEY_F4              293
#define KEY_F5              294
#define KEY_F6              295
#define KEY_F7              296
#define KEY_F8              297
#define KEY_F9              298
#define KEY_F10             299
#define KEY_F11             300
#define KEY_F12             301
#define KEY_LEFT_SHIFT      340
#define KEY_LEFT_CONTROL    341
#define KEY_LEFT_ALT        342
#define KEY_RIGHT_SHIFT     344
#define KEY_RIGHT_CONTROL   345
#define KEY_RIGHT_ALT       346

// Keyboard Alpha Numeric Keys
#define KEY_ZERO             48
#define KEY_ONE              49
#define KEY_TWO              50
#define KEY_THREE            51
#define KEY_FOUR             52
#define KEY_FIVE             53
#define KEY_SIX              54
#define KEY_SEVEN            55
#define KEY_EIGHT            56
#define KEY_NINE             57
#define KEY_A                65
#define KEY_B                66
#define KEY_C                67
#define KEY_D                68
#define KEY_E                69
#define KEY_F                70
#define KEY_G                71
#define KEY_H                72
#define KEY_I                73
#define KEY_J                74
#define KEY_K                75
#define KEY_L                76
#define KEY_M                77
#define KEY_N                78
#define KEY_O                79
#define KEY_P                80
#define KEY_Q                81
#define KEY_R                82
#define KEY_S                83
#define KEY_T                84
#define KEY_U                85
#define KEY_V                86
#define KEY_W                87
#define KEY_X                88
#define KEY_Y                89
#define KEY_Z                90

// Mouse Buttons
#define MOUSE_LEFT_BUTTON     0
#if defined(PLATFORM_WEB)
    #define MOUSE_RIGHT_BUTTON    2
    #define MOUSE_MIDDLE_BUTTON   1
#else
    #define MOUSE_RIGHT_BUTTON    1
    #define MOUSE_MIDDLE_BUTTON   2
#endif

// Touch points registered
#define MAX_TOUCH_POINTS     2

// Gamepad Number
#define GAMEPAD_PLAYER1       0
#define GAMEPAD_PLAYER2       1
#define GAMEPAD_PLAYER3       2     // Not supported
#define GAMEPAD_PLAYER4       3     // Not supported

// Gamepad Buttons

// PS3 USB Controller
#define GAMEPAD_PS3_BUTTON_A        2
#define GAMEPAD_PS3_BUTTON_B        1
#define GAMEPAD_PS3_BUTTON_X        3
#define GAMEPAD_PS3_BUTTON_Y        4
#define GAMEPAD_PS3_BUTTON_R1       7
#define GAMEPAD_PS3_BUTTON_R2       5
#define GAMEPAD_PS3_BUTTON_L1       6
#define GAMEPAD_PS3_BUTTON_L2       8
#define GAMEPAD_PS3_BUTTON_SELECT   9
#define GAMEPAD_PS3_BUTTON_START   10

// TODO: Add PS3 d-pad axis

// Xbox360 USB Controller Buttons
#define GAMEPAD_XBOX_BUTTON_A       0
#define GAMEPAD_XBOX_BUTTON_B       1
#define GAMEPAD_XBOX_BUTTON_X       2
#define GAMEPAD_XBOX_BUTTON_Y       3
#define GAMEPAD_XBOX_BUTTON_LB      4
#define GAMEPAD_XBOX_BUTTON_RB      5
#define GAMEPAD_XBOX_BUTTON_SELECT  6
#define GAMEPAD_XBOX_BUTTON_START   7

#if defined(PLATFORM_RPI)
    #define GAMEPAD_XBOX_AXIS_DPAD_X    7
    #define GAMEPAD_XBOX_AXIS_DPAD_Y    6
    #define GAMEPAD_XBOX_AXIS_RIGHT_X   3
    #define GAMEPAD_XBOX_AXIS_RIGHT_Y   4
    #define GAMEPAD_XBOX_AXIS_LT        2
    #define GAMEPAD_XBOX_AXIS_RT        5
#else
    #define GAMEPAD_XBOX_BUTTON_UP      10
    #define GAMEPAD_XBOX_BUTTON_DOWN    12
    #define GAMEPAD_XBOX_BUTTON_LEFT    13
    #define GAMEPAD_XBOX_BUTTON_RIGHT   11
    #define GAMEPAD_XBOX_AXIS_RIGHT_X   4
    #define GAMEPAD_XBOX_AXIS_RIGHT_Y   3
    #define GAMEPAD_XBOX_AXIS_LT_RT     2
#endif

#define GAMEPAD_XBOX_AXIS_LEFT_X    0
#define GAMEPAD_XBOX_AXIS_LEFT_Y    1

// Android Physic Buttons
#define ANDROID_BACK            4
#define ANDROID_MENU            82
#define ANDROID_VOLUME_UP       24
#define ANDROID_VOLUME_DOWN     25

// NOTE: MSC C++ compiler does not support compound literals (C99 feature)
// Plain structures in C++ (without constructors) can be initialized from { } initializers.
#ifdef __cplusplus
    #define CLITERAL
#else
    #define CLITERAL    (Color)
#endif

// Some Basic Colors
// NOTE: Custom raylib color palette for amazing visuals on WHITE background
#define LIGHTGRAY  CLITERAL{ 200, 200, 200, 255 }   // Light Gray
#define GRAY       CLITERAL{ 130, 130, 130, 255 }   // Gray
#define DARKGRAY   CLITERAL{ 80, 80, 80, 255 }      // Dark Gray
#define YELLOW     CLITERAL{ 253, 249, 0, 255 }     // Yellow
#define GOLD       CLITERAL{ 255, 203, 0, 255 }     // Gold
#define ORANGE     CLITERAL{ 255, 161, 0, 255 }     // Orange
#define PINK       CLITERAL{ 255, 109, 194, 255 }   // Pink
#define RED        CLITERAL{ 230, 41, 55, 255 }     // Red
#define MAROON     CLITERAL{ 190, 33, 55, 255 }     // Maroon
#define GREEN      CLITERAL{ 0, 228, 48, 255 }      // Green
#define LIME       CLITERAL{ 0, 158, 47, 255 }      // Lime
#define DARKGREEN  CLITERAL{ 0, 117, 44, 255 }      // Dark Green
#define SKYBLUE    CLITERAL{ 102, 191, 255, 255 }   // Sky Blue
#define BLUE       CLITERAL{ 0, 121, 241, 255 }     // Blue
#define DARKBLUE   CLITERAL{ 0, 82, 172, 255 }      // Dark Blue
#define PURPLE     CLITERAL{ 200, 122, 255, 255 }   // Purple
#define VIOLET     CLITERAL{ 135, 60, 190, 255 }    // Violet
#define DARKPURPLE CLITERAL{ 112, 31, 126, 255 }    // Dark Purple
#define BEIGE      CLITERAL{ 211, 176, 131, 255 }   // Beige
#define BROWN      CLITERAL{ 127, 106, 79, 255 }    // Brown
#define DARKBROWN  CLITERAL{ 76, 63, 47, 255 }      // Dark Brown

#define WHITE      CLITERAL{ 255, 255, 255, 255 }   // White
#define BLACK      CLITERAL{ 0, 0, 0, 255 }         // Black
#define BLANK      CLITERAL{ 0, 0, 0, 0 }           // Blank (Transparent)
#define MAGENTA    CLITERAL{ 255, 0, 255, 255 }     // Magenta
#define RAYWHITE   CLITERAL{ 245, 245, 245, 255 }   // My own White (raylib logo)

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
#ifndef __cplusplus
// Boolean type
    #ifndef __APPLE__
        #if !defined(_STDBOOL_H)
            typedef enum { false, true } bool;
            #define _STDBOOL_H
        #endif
    #else
        #include <stdbool.h>
    #endif
#endif

// byte type
typedef unsigned char byte;

// Vector2 type
typedef struct Vector2 {
    float x;
    float y;
} Vector2;

// Vector3 type
typedef struct Vector3 {
    float x;
    float y;
    float z;
} Vector3;

// Matrix type (OpenGL style 4x4 - right handed, column major)
typedef struct Matrix {
    float m0, m4, m8, m12;
    float m1, m5, m9, m13;
    float m2, m6, m10, m14;
    float m3, m7, m11, m15;
} Matrix;

// Color type, RGBA (32bit)
typedef struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} Color;

// Rectangle type
typedef struct Rectangle {
    int x;
    int y;
    int width;
    int height;
} Rectangle;

// Image type, bpp always RGBA (32bit)
// NOTE: Data stored in CPU memory (RAM)
typedef struct Image {
    void *data;             // Image raw data
    int width;              // Image base width
    int height;             // Image base height
    int mipmaps;            // Mipmap levels, 1 by default
    int format;             // Data format (TextureFormat)
} Image;

// Texture2D type, bpp always RGBA (32bit)
// NOTE: Data stored in GPU memory
typedef struct Texture2D {
    unsigned int id;        // OpenGL texture id
    int width;              // Texture base width
    int height;             // Texture base height
    int mipmaps;            // Mipmap levels, 1 by default
    int format;             // Data format (TextureFormat)
} Texture2D;

// RenderTexture2D type, for texture rendering
typedef struct RenderTexture2D {
    unsigned int id;        // Render texture (fbo) id
    Texture2D texture;      // Color buffer attachment texture
    Texture2D depth;        // Depth buffer attachment texture
} RenderTexture2D;

// SpriteFont type, includes texture and charSet array data
typedef struct SpriteFont {
    Texture2D texture;      // Font texture
    int size;               // Base size (default chars height)
    int numChars;           // Number of characters
    int *charValues;        // Characters values array
    Rectangle *charRecs;    // Characters rectangles within the texture
    Vector2 *charOffsets;   // Characters offsets (on drawing)
    int *charAdvanceX;      // Characters x advance (on drawing)
} SpriteFont;

// Camera type, defines a camera position/orientation in 3d space
typedef struct Camera {
    Vector3 position;       // Camera position
    Vector3 target;         // Camera target it looks-at
    Vector3 up;             // Camera up vector (rotation over its axis)
    float fovy;             // Camera field-of-view apperture in Y (degrees)
} Camera;

// Camera2D type, defines a 2d camera
typedef struct Camera2D {
    Vector2 offset;         // Camera offset (displacement from target)
    Vector2 target;         // Camera target (rotation and zoom origin)
    float rotation;         // Camera rotation in degrees
    float zoom;             // Camera zoom (scaling), should be 1.0f by default
} Camera2D;

// Bounding box type
typedef struct BoundingBox {
    Vector3 min;            // minimum vertex box-corner
    Vector3 max;            // maximum vertex box-corner
} BoundingBox;

// Vertex data definning a mesh
typedef struct Mesh {
    int vertexCount;        // number of vertices stored in arrays
    int triangleCount;      // number of triangles stored (indexed or not)
    float *vertices;        // vertex position (XYZ - 3 components per vertex) (shader-location = 0)
    float *texcoords;       // vertex texture coordinates (UV - 2 components per vertex) (shader-location = 1)
    float *texcoords2;      // vertex second texture coordinates (useful for lightmaps) (shader-location = 5)
    float *normals;         // vertex normals (XYZ - 3 components per vertex) (shader-location = 2)
    float *tangents;        // vertex tangents (XYZ - 3 components per vertex) (shader-location = 4)
    unsigned char *colors;  // vertex colors (RGBA - 4 components per vertex) (shader-location = 3)
    unsigned short *indices;// vertex indices (in case vertex data comes indexed)

    unsigned int vaoId;     // OpenGL Vertex Array Object id
    unsigned int vboId[7];  // OpenGL Vertex Buffer Objects id (7 types of vertex data)
} Mesh;

// Shader type (generic shader)
typedef struct Shader {
    unsigned int id;        // Shader program id

    // Vertex attributes locations (default locations)
    int vertexLoc;          // Vertex attribute location point    (default-location = 0)
    int texcoordLoc;        // Texcoord attribute location point  (default-location = 1)
    int texcoord2Loc;       // Texcoord2 attribute location point (default-location = 5)
    int normalLoc;          // Normal attribute location point    (default-location = 2)
    int tangentLoc;         // Tangent attribute location point   (default-location = 4)
    int colorLoc;           // Color attibute location point      (default-location = 3)

    // Uniform locations
    int mvpLoc;             // ModelView-Projection matrix uniform location point (vertex shader)
    int tintColorLoc;       // Diffuse color uniform location point (fragment shader)

    // Texture map locations (generic for any kind of map)
    int mapTexture0Loc;     // Map texture uniform location point (default-texture-unit = 0)
    int mapTexture1Loc;     // Map texture uniform location point (default-texture-unit = 1)
    int mapTexture2Loc;     // Map texture uniform location point (default-texture-unit = 2)
} Shader;

// Material type
typedef struct Material {
    Shader shader;          // Standard shader (supports 3 map textures)

    Texture2D texDiffuse;   // Diffuse texture  (binded to shader mapTexture0Loc)
    Texture2D texNormal;    // Normal texture   (binded to shader mapTexture1Loc)
    Texture2D texSpecular;  // Specular texture (binded to shader mapTexture2Loc)

    Color colDiffuse;       // Diffuse color
    Color colAmbient;       // Ambient color
    Color colSpecular;      // Specular color

    float glossiness;       // Glossiness level (Ranges from 0 to 1000)
} Material;

// Model type
typedef struct Model {
    Mesh mesh;              // Vertex data buffers (RAM and VRAM)
    Matrix transform;       // Local transform matrix
    Material material;      // Shader and textures data
} Model;

// Light type
typedef struct LightData {
    unsigned int id;        // Light unique id
    bool enabled;           // Light enabled
    int type;               // Light type: LIGHT_POINT, LIGHT_DIRECTIONAL, LIGHT_SPOT

    Vector3 position;       // Light position
    Vector3 target;         // Light target: LIGHT_DIRECTIONAL and LIGHT_SPOT (cone direction target)
    float radius;           // Light attenuation radius light intensity reduced with distance (world distance)

    Color diffuse;          // Light diffuse color
    float intensity;        // Light intensity level

    float coneAngle;        // Light cone max angle: LIGHT_SPOT
} LightData, *Light;

// Light types
typedef enum { LIGHT_POINT, LIGHT_DIRECTIONAL, LIGHT_SPOT } LightType;

// Ray type (useful for raycast)
typedef struct Ray {
    Vector3 position;       // Ray position (origin)
    Vector3 direction;      // Ray direction
} Ray;

// Sound source type
typedef struct Sound {
    unsigned int source;    // OpenAL audio source id
    unsigned int buffer;    // OpenAL audio buffer id
} Sound;

// Wave type, defines audio wave data
typedef struct Wave {
    unsigned int sampleCount;   // Number of samples
    unsigned int sampleRate;    // Frequency (samples per second)
    unsigned int sampleSize;    // Bit depth (bits per sample): 8, 16, 32 (24 not supported)
    unsigned int channels;      // Number of channels (1-mono, 2-stereo)
    void *data;                 // Buffer data pointer
} Wave;

// Music type (file streaming from memory)
// NOTE: Anything longer than ~10 seconds should be streamed
typedef struct MusicData *Music;

// Audio stream type
// NOTE: Useful to create custom audio streams not bound to a specific file
typedef struct AudioStream {
    unsigned int sampleRate;    // Frequency (samples per second)
    unsigned int sampleSize;    // Bit depth (bits per sample): 8, 16, 32 (24 not supported)
    unsigned int channels;      // Number of channels (1-mono, 2-stereo)

    int format;                 // OpenAL audio format specifier
    unsigned int source;        // OpenAL audio source id
    unsigned int buffers[2];    // OpenAL audio buffers (double buffering)
} AudioStream;

// Texture formats
// NOTE: Support depends on OpenGL version and platform
typedef enum {
    UNCOMPRESSED_GRAYSCALE = 1,     // 8 bit per pixel (no alpha)
    UNCOMPRESSED_GRAY_ALPHA,        // 16 bpp (2 channels)
    UNCOMPRESSED_R5G6B5,            // 16 bpp
    UNCOMPRESSED_R8G8B8,            // 24 bpp
    UNCOMPRESSED_R5G5B5A1,          // 16 bpp (1 bit alpha)
    UNCOMPRESSED_R4G4B4A4,          // 16 bpp (4 bit alpha)
    UNCOMPRESSED_R8G8B8A8,          // 32 bpp
    COMPRESSED_DXT1_RGB,            // 4 bpp (no alpha)
    COMPRESSED_DXT1_RGBA,           // 4 bpp (1 bit alpha)
    COMPRESSED_DXT3_RGBA,           // 8 bpp
    COMPRESSED_DXT5_RGBA,           // 8 bpp
    COMPRESSED_ETC1_RGB,            // 4 bpp
    COMPRESSED_ETC2_RGB,            // 4 bpp
    COMPRESSED_ETC2_EAC_RGBA,       // 8 bpp
    COMPRESSED_PVRT_RGB,            // 4 bpp
    COMPRESSED_PVRT_RGBA,           // 4 bpp
    COMPRESSED_ASTC_4x4_RGBA,       // 8 bpp
    COMPRESSED_ASTC_8x8_RGBA        // 2 bpp
} TextureFormat;

// Color blending modes (pre-defined)
typedef enum { BLEND_ALPHA = 0, BLEND_ADDITIVE, BLEND_MULTIPLIED } BlendMode;

// Gestures type
// NOTE: It could be used as flags to enable only some gestures
typedef enum {
    GESTURE_NONE        = 0,
    GESTURE_TAP         = 1,
    GESTURE_DOUBLETAP   = 2,
    GESTURE_HOLD        = 4,
    GESTURE_DRAG        = 8,
    GESTURE_SWIPE_RIGHT = 16,
    GESTURE_SWIPE_LEFT  = 32,
    GESTURE_SWIPE_UP    = 64,
    GESTURE_SWIPE_DOWN  = 128,
    GESTURE_PINCH_IN    = 256,
    GESTURE_PINCH_OUT   = 512
} Gestures;

// Camera system modes
typedef enum { CAMERA_CUSTOM = 0, CAMERA_FREE, CAMERA_ORBITAL, CAMERA_FIRST_PERSON, CAMERA_THIRD_PERSON } CameraMode;

// Head Mounted Display devices
typedef enum {
    HMD_DEFAULT_DEVICE = 0,
    HMD_OCULUS_RIFT_DK2,
    HMD_OCULUS_RIFT_CV1,
    HMD_VALVE_HTC_VIVE,
    HMD_SAMSUNG_GEAR_VR,
    HMD_GOOGLE_CARDBOARD,
    HMD_SONY_PLAYSTATION_VR,
    HMD_RAZER_OSVR,
    HMD_FOVE_VR,
} VrDevice;

#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif

//------------------------------------------------------------------------------------
// Global Variables Definition
//------------------------------------------------------------------------------------
// It's lonely here...

//------------------------------------------------------------------------------------
// Window and Graphics Device Functions (Module: core)
//------------------------------------------------------------------------------------
#if defined(PLATFORM_ANDROID)
RLAPI void InitWindow(int width, int height, struct android_app *state);  // Init Android Activity and OpenGL Graphics
#elif defined(PLATFORM_DESKTOP) || defined(PLATFORM_RPI) || defined(PLATFORM_WEB)
RLAPI void InitWindow(int width, int height, const char *title);  // Initialize Window and OpenGL Graphics
#endif

RLAPI void CloseWindow(void);                                     // Close Window and Terminate Context
RLAPI bool WindowShouldClose(void);                               // Detect if KEY_ESCAPE pressed or Close icon pressed
RLAPI bool IsWindowMinimized(void);                               // Detect if window has been minimized (or lost focus)
RLAPI void ToggleFullscreen(void);                                // Fullscreen toggle (only PLATFORM_DESKTOP)
RLAPI int GetScreenWidth(void);                                   // Get current screen width
RLAPI int GetScreenHeight(void);                                  // Get current screen height

RLAPI void ShowCursor(void);                                      // Shows cursor
RLAPI void HideCursor(void);                                      // Hides cursor
RLAPI bool IsCursorHidden(void);                                  // Returns true if cursor is not visible
RLAPI void EnableCursor(void);                                    // Enables cursor
RLAPI void DisableCursor(void);                                   // Disables cursor

RLAPI void ClearBackground(Color color);                          // Sets Background Color
RLAPI void BeginDrawing(void);                                    // Setup drawing canvas to start drawing
RLAPI void EndDrawing(void);                                      // End canvas drawing and Swap Buffers (Double Buffering)

RLAPI void Begin2dMode(Camera2D camera);                          // Initialize 2D mode with custom camera
RLAPI void End2dMode(void);                                       // Ends 2D mode custom camera usage
RLAPI void Begin3dMode(Camera camera);                            // Initializes 3D mode for drawing (Camera setup)
RLAPI void End3dMode(void);                                       // Ends 3D mode and returns to default 2D orthographic mode
RLAPI void BeginTextureMode(RenderTexture2D target);              // Initializes render texture for drawing
RLAPI void EndTextureMode(void);                                  // Ends drawing to render texture

RLAPI Ray GetMouseRay(Vector2 mousePosition, Camera camera);      // Returns a ray trace from mouse position
RLAPI Vector2 GetWorldToScreen(Vector3 position, Camera camera);  // Returns the screen space position from a 3d world space position
RLAPI Matrix GetCameraMatrix(Camera camera);                      // Returns camera transform matrix (view matrix)

RLAPI void SetTargetFPS(int fps);                                 // Set target FPS (maximum)
RLAPI float GetFPS(void);                                         // Returns current FPS
RLAPI float GetFrameTime(void);                                   // Returns time in seconds for one frame

RLAPI Color GetColor(int hexValue);                               // Returns a Color struct from hexadecimal value
RLAPI int GetHexValue(Color color);                               // Returns hexadecimal value for a Color
RLAPI float *ColorToFloat(Color color);                           // Converts Color to float array and normalizes
RLAPI float *VectorToFloat(Vector3 vec);                          // Converts Vector3 to float array
RLAPI float *MatrixToFloat(Matrix mat);                           // Converts Matrix to float array

RLAPI int GetRandomValue(int min, int max);                       // Returns a random value between min and max (both included)
RLAPI Color Fade(Color color, float alpha);                       // Color fade-in or fade-out, alpha goes from 0.0f to 1.0f

RLAPI void SetConfigFlags(char flags);                            // Setup some window configuration flags
RLAPI void ShowLogo(void);                                        // Activates raylib logo at startup (can be done with flags)

RLAPI bool IsFileDropped(void);                                   // Check if a file have been dropped into window
RLAPI char **GetDroppedFiles(int *count);                         // Retrieve dropped files into window
RLAPI void ClearDroppedFiles(void);                               // Clear dropped files paths buffer

RLAPI void StorageSaveValue(int position, int value);             // Storage save integer value (to defined position)
RLAPI int StorageLoadValue(int position);                         // Storage load integer value (from defined position)

//------------------------------------------------------------------------------------
// Input Handling Functions (Module: core)
//------------------------------------------------------------------------------------
#if defined(PLATFORM_DESKTOP) || defined(PLATFORM_RPI) || defined(PLATFORM_WEB)
RLAPI bool IsKeyPressed(int key);                             // Detect if a key has been pressed once
RLAPI bool IsKeyDown(int key);                                // Detect if a key is being pressed
RLAPI bool IsKeyReleased(int key);                            // Detect if a key has been released once
RLAPI bool IsKeyUp(int key);                                  // Detect if a key is NOT being pressed
RLAPI int GetKeyPressed(void);                                // Get latest key pressed
RLAPI void SetExitKey(int key);                               // Set a custom key to exit program (default is ESC)

RLAPI bool IsGamepadAvailable(int gamepad);                   // Detect if a gamepad is available
RLAPI float GetGamepadAxisMovement(int gamepad, int axis);    // Return axis movement value for a gamepad axis
RLAPI bool IsGamepadButtonPressed(int gamepad, int button);   // Detect if a gamepad button has been pressed once
RLAPI bool IsGamepadButtonDown(int gamepad, int button);      // Detect if a gamepad button is being pressed
RLAPI bool IsGamepadButtonReleased(int gamepad, int button);  // Detect if a gamepad button has been released once
RLAPI bool IsGamepadButtonUp(int gamepad, int button);        // Detect if a gamepad button is NOT being pressed
#endif

RLAPI bool IsMouseButtonPressed(int button);                  // Detect if a mouse button has been pressed once
RLAPI bool IsMouseButtonDown(int button);                     // Detect if a mouse button is being pressed
RLAPI bool IsMouseButtonReleased(int button);                 // Detect if a mouse button has been released once
RLAPI bool IsMouseButtonUp(int button);                       // Detect if a mouse button is NOT being pressed
RLAPI int GetMouseX(void);                                    // Returns mouse position X
RLAPI int GetMouseY(void);                                    // Returns mouse position Y
RLAPI Vector2 GetMousePosition(void);                         // Returns mouse position XY
RLAPI void SetMousePosition(Vector2 position);                // Set mouse position XY
RLAPI int GetMouseWheelMove(void);                            // Returns mouse wheel movement Y

RLAPI int GetTouchX(void);                                    // Returns touch position X for touch point 0 (relative to screen size)
RLAPI int GetTouchY(void);                                    // Returns touch position Y for touch point 0 (relative to screen size)
RLAPI Vector2 GetTouchPosition(int index);                    // Returns touch position XY for a touch point index (relative to screen size)

#if defined(PLATFORM_ANDROID)
bool IsButtonPressed(int button);                       // Detect if an android physic button has been pressed
bool IsButtonDown(int button);                          // Detect if an android physic button is being pressed
bool IsButtonReleased(int button);                      // Detect if an android physic button has been released
#endif

//------------------------------------------------------------------------------------
// Gestures and Touch Handling Functions (Module: gestures)
//------------------------------------------------------------------------------------
RLAPI void SetGesturesEnabled(unsigned int gestureFlags);     // Enable a set of gestures using flags
RLAPI bool IsGestureDetected(int gesture);                    // Check if a gesture have been detected
RLAPI int GetGestureDetected(void);                           // Get latest detected gesture
RLAPI int GetTouchPointsCount(void);                          // Get touch points count
RLAPI float GetGestureHoldDuration(void);                     // Get gesture hold time in milliseconds
RLAPI Vector2 GetGestureDragVector(void);                     // Get gesture drag vector
RLAPI float GetGestureDragAngle(void);                        // Get gesture drag angle
RLAPI Vector2 GetGesturePinchVector(void);                    // Get gesture pinch delta
RLAPI float GetGesturePinchAngle(void);                       // Get gesture pinch angle

//------------------------------------------------------------------------------------
// Camera System Functions (Module: camera)
//------------------------------------------------------------------------------------
RLAPI void SetCameraMode(int mode);                               // Set camera mode (multiple camera modes available)
RLAPI void UpdateCamera(Camera *camera);                          // Update camera (player position is ignored)
RLAPI void UpdateCameraPlayer(Camera *camera, Vector3 *position); // Update camera and player position (1st person and 3rd person cameras)

RLAPI void SetCameraPosition(Vector3 position);                   // Set internal camera position
RLAPI void SetCameraTarget(Vector3 target);                       // Set internal camera target
RLAPI void SetCameraFovy(float fovy);                             // Set internal camera field-of-view-y

RLAPI void SetCameraPanControl(int panKey);                       // Set camera pan key to combine with mouse movement (free camera)
RLAPI void SetCameraAltControl(int altKey);                       // Set camera alt key to combine with mouse movement (free camera)
RLAPI void SetCameraSmoothZoomControl(int szKey);                 // Set camera smooth zoom key to combine with mouse (free camera)

RLAPI void SetCameraMoveControls(int frontKey, int backKey,
                           int leftKey, int rightKey,
                           int upKey, int downKey);               // Set camera move controls (1st person and 3rd person cameras)
RLAPI void SetCameraMouseSensitivity(float sensitivity);          // Set camera mouse sensitivity (1st person and 3rd person cameras)

//------------------------------------------------------------------------------------
// Basic Shapes Drawing Functions (Module: shapes)
//------------------------------------------------------------------------------------
RLAPI void DrawPixel(int posX, int posY, Color color);                                                   // Draw a pixel
RLAPI void DrawPixelV(Vector2 position, Color color);                                                    // Draw a pixel (Vector version)
RLAPI void DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color);                // Draw a line
RLAPI void DrawLineV(Vector2 startPos, Vector2 endPos, Color color);                                     // Draw a line (Vector version)
RLAPI void DrawCircle(int centerX, int centerY, float radius, Color color);                              // Draw a color-filled circle
RLAPI void DrawCircleGradient(int centerX, int centerY, float radius, Color color1, Color color2);       // Draw a gradient-filled circle
RLAPI void DrawCircleV(Vector2 center, float radius, Color color);                                       // Draw a color-filled circle (Vector version)
RLAPI void DrawCircleLines(int centerX, int centerY, float radius, Color color);                         // Draw circle outline
RLAPI void DrawRectangle(int posX, int posY, int width, int height, Color color);                        // Draw a color-filled rectangle
RLAPI void DrawRectangleRec(Rectangle rec, Color color);                                                 // Draw a color-filled rectangle
RLAPI void DrawRectangleGradient(int posX, int posY, int width, int height, Color color1, Color color2); // Draw a gradient-filled rectangle
RLAPI void DrawRectangleV(Vector2 position, Vector2 size, Color color);                                  // Draw a color-filled rectangle (Vector version)
RLAPI void DrawRectangleLines(int posX, int posY, int width, int height, Color color);                   // Draw rectangle outline
RLAPI void DrawTriangle(Vector2 v1, Vector2 v2, Vector2 v3, Color color);                                // Draw a color-filled triangle
RLAPI void DrawTriangleLines(Vector2 v1, Vector2 v2, Vector2 v3, Color color);                           // Draw triangle outline
RLAPI void DrawPoly(Vector2 center, int sides, float radius, float rotation, Color color);               // Draw a regular polygon (Vector version)
RLAPI void DrawPolyEx(Vector2 *points, int numPoints, Color color);                                      // Draw a closed polygon defined by points
RLAPI void DrawPolyExLines(Vector2 *points, int numPoints, Color color);                                 // Draw polygon lines

RLAPI bool CheckCollisionRecs(Rectangle rec1, Rectangle rec2);                                           // Check collision between two rectangles
RLAPI bool CheckCollisionCircles(Vector2 center1, float radius1, Vector2 center2, float radius2);        // Check collision between two circles
RLAPI bool CheckCollisionCircleRec(Vector2 center, float radius, Rectangle rec);                         // Check collision between circle and rectangle
RLAPI Rectangle GetCollisionRec(Rectangle rec1, Rectangle rec2);                                         // Get collision rectangle for two rectangles collision
RLAPI bool CheckCollisionPointRec(Vector2 point, Rectangle rec);                                         // Check if point is inside rectangle
RLAPI bool CheckCollisionPointCircle(Vector2 point, Vector2 center, float radius);                       // Check if point is inside circle
RLAPI bool CheckCollisionPointTriangle(Vector2 point, Vector2 p1, Vector2 p2, Vector2 p3);               // Check if point is inside a triangle

//------------------------------------------------------------------------------------
// Texture Loading and Drawing Functions (Module: textures)
//------------------------------------------------------------------------------------
RLAPI Image LoadImage(const char *fileName);                                                             // Load an image into CPU memory (RAM)
RLAPI Image LoadImageEx(Color *pixels, int width, int height);                                           // Load image data from Color array data (RGBA - 32bit)
RLAPI Image LoadImageRaw(const char *fileName, int width, int height, int format, int headerSize);       // Load image data from RAW file
RLAPI Image LoadImageFromRES(const char *rresName, int resId);                                           // Load an image from rRES file (raylib Resource)
RLAPI Texture2D LoadTexture(const char *fileName);                                                       // Load an image as texture into GPU memory
RLAPI Texture2D LoadTextureEx(void *data, int width, int height, int textureFormat);                     // Load a texture from raw data into GPU memory
RLAPI Texture2D LoadTextureFromRES(const char *rresName, int resId);                                     // Load an image as texture from rRES file (raylib Resource)
RLAPI Texture2D LoadTextureFromImage(Image image);                                                       // Load a texture from image data
RLAPI RenderTexture2D LoadRenderTexture(int width, int height);                                          // Load a texture to be used for rendering
RLAPI void UnloadImage(Image image);                                                                     // Unload image from CPU memory (RAM)
RLAPI void UnloadTexture(Texture2D texture);                                                             // Unload texture from GPU memory
RLAPI void UnloadRenderTexture(RenderTexture2D target);                                                  // Unload render texture from GPU memory
RLAPI Color *GetImageData(Image image);                                                                  // Get pixel data from image as a Color struct array
RLAPI Image GetTextureData(Texture2D texture);                                                           // Get pixel data from GPU texture and return an Image
RLAPI void ImageToPOT(Image *image, Color fillColor);                                                    // Convert image to POT (power-of-two)
RLAPI void ImageFormat(Image *image, int newFormat);                                                     // Convert image data to desired format
RLAPI void ImageDither(Image *image, int rBpp, int gBpp, int bBpp, int aBpp);                            // Dither image data to 16bpp or lower (Floyd-Steinberg dithering)
RLAPI Image ImageCopy(Image image);                                                                      // Create an image duplicate (useful for transformations)
RLAPI void ImageCrop(Image *image, Rectangle crop);                                                      // Crop an image to a defined rectangle
RLAPI void ImageResize(Image *image, int newWidth, int newHeight);                                       // Resize and image (bilinear filtering)
RLAPI void ImageResizeNN(Image *image,int newWidth,int newHeight);                                       // Resize and image (Nearest-Neighbor scaling algorithm)
RLAPI Image ImageText(const char *text, int fontSize, Color color);                                      // Create an image from text (default font)
RLAPI Image ImageTextEx(SpriteFont font, const char *text, float fontSize, int spacing, Color tint);     // Create an image from text (custom sprite font)
RLAPI void ImageDraw(Image *dst, Image src, Rectangle srcRec, Rectangle dstRec);                         // Draw a source image within a destination image
RLAPI void ImageDrawText(Image *dst, Vector2 position, const char *text, int fontSize, Color color);     // Draw text (default font) within an image (destination)
RLAPI void ImageDrawTextEx(Image *dst, Vector2 position, SpriteFont font, const char *text, float fontSize, int spacing, Color color); // Draw text (custom sprite font) within an image (destination)
RLAPI void ImageFlipVertical(Image *image);                                                              // Flip image vertically
RLAPI void ImageFlipHorizontal(Image *image);                                                            // Flip image horizontally
RLAPI void ImageColorTint(Image *image, Color color);                                                    // Modify image color: tint
RLAPI void ImageColorInvert(Image *image);                                                               // Modify image color: invert
RLAPI void ImageColorGrayscale(Image *image);                                                            // Modify image color: grayscale
RLAPI void ImageColorContrast(Image *image, float contrast);                                             // Modify image color: contrast (-100 to 100)
RLAPI void ImageColorBrightness(Image *image, int brightness);                                           // Modify image color: brightness (-255 to 255)
RLAPI void GenTextureMipmaps(Texture2D texture);                                                         // Generate GPU mipmaps for a texture
RLAPI void UpdateTexture(Texture2D texture, void *pixels);                                               // Update GPU texture with new data

RLAPI void DrawTexture(Texture2D texture, int posX, int posY, Color tint);                               // Draw a Texture2D
RLAPI void DrawTextureV(Texture2D texture, Vector2 position, Color tint);                                // Draw a Texture2D with position defined as Vector2
RLAPI void DrawTextureEx(Texture2D texture, Vector2 position, float rotation, float scale, Color tint);  // Draw a Texture2D with extended parameters
RLAPI void DrawTextureRec(Texture2D texture, Rectangle sourceRec, Vector2 position, Color tint);         // Draw a part of a texture defined by a rectangle
RLAPI void DrawTexturePro(Texture2D texture, Rectangle sourceRec, Rectangle destRec, Vector2 origin,     // Draw a part of a texture defined by a rectangle with 'pro' parameters
                    float rotation, Color tint);

//------------------------------------------------------------------------------------
// Font Loading and Text Drawing Functions (Module: text)
//------------------------------------------------------------------------------------
RLAPI SpriteFont GetDefaultFont(void);                                                                   // Get the default SpriteFont
RLAPI SpriteFont LoadSpriteFont(const char *fileName);                                                   // Load a SpriteFont image into GPU memory
RLAPI void UnloadSpriteFont(SpriteFont spriteFont);                                                      // Unload SpriteFont from GPU memory

RLAPI void DrawText(const char *text, int posX, int posY, int fontSize, Color color);                    // Draw text (using default font)
RLAPI void DrawTextEx(SpriteFont spriteFont, const char* text, Vector2 position,                         // Draw text using SpriteFont and additional parameters
                float fontSize, int spacing, Color tint);
RLAPI int MeasureText(const char *text, int fontSize);                                                   // Measure string width for default font
RLAPI Vector2 MeasureTextEx(SpriteFont spriteFont, const char *text, int fontSize, int spacing);         // Measure string size for SpriteFont

RLAPI void DrawFPS(int posX, int posY);                                                                  // Shows current FPS on top-left corner
RLAPI const char *FormatText(const char *text, ...);                                                     // Formatting of text with variables to 'embed'
RLAPI const char *SubText(const char *text, int position, int length);                                   // Get a piece of a text string

//------------------------------------------------------------------------------------
// Basic 3d Shapes Drawing Functions (Module: models)
//------------------------------------------------------------------------------------
RLAPI void DrawLine3D(Vector3 startPos, Vector3 endPos, Color color);                                    // Draw a line in 3D world space
RLAPI void DrawCircle3D(Vector3 center, float radius, float rotationAngle, Vector3 rotation, Color color);    // Draw a circle in 3D world space
RLAPI void DrawCube(Vector3 position, float width, float height, float length, Color color);             // Draw cube
RLAPI void DrawCubeV(Vector3 position, Vector3 size, Color color);                                       // Draw cube (Vector version)
RLAPI void DrawCubeWires(Vector3 position, float width, float height, float length, Color color);        // Draw cube wires
RLAPI void DrawCubeTexture(Texture2D texture, Vector3 position, float width, float height, float length, Color color); // Draw cube textured
RLAPI void DrawSphere(Vector3 centerPos, float radius, Color color);                                     // Draw sphere
RLAPI void DrawSphereEx(Vector3 centerPos, float radius, int rings, int slices, Color color);            // Draw sphere with extended parameters
RLAPI void DrawSphereWires(Vector3 centerPos, float radius, int rings, int slices, Color color);         // Draw sphere wires
RLAPI void DrawCylinder(Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color); // Draw a cylinder/cone
RLAPI void DrawCylinderWires(Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color); // Draw a cylinder/cone wires
RLAPI void DrawPlane(Vector3 centerPos, Vector2 size, Color color);                                      // Draw a plane XZ
RLAPI void DrawRay(Ray ray, Color color);                                                                // Draw a ray line
RLAPI void DrawGrid(int slices, float spacing);                                                          // Draw a grid (centered at (0, 0, 0))
RLAPI void DrawGizmo(Vector3 position);                                                                  // Draw simple gizmo
RLAPI void DrawLight(Light light);                                                                       // Draw light in 3D world
//DrawTorus(), DrawTeapot() are useless...

//------------------------------------------------------------------------------------
// Model 3d Loading and Drawing Functions (Module: models)
//------------------------------------------------------------------------------------
RLAPI Model LoadModel(const char *fileName);                          // Load a 3d model (.OBJ)
RLAPI Model LoadModelEx(Mesh data, bool dynamic);                     // Load a 3d model (from mesh data)
RLAPI Model LoadModelFromRES(const char *rresName, int resId);        // Load a 3d model from rRES file (raylib Resource)
RLAPI Model LoadHeightmap(Image heightmap, Vector3 size);             // Load a heightmap image as a 3d model
RLAPI Model LoadCubicmap(Image cubicmap);                             // Load a map image as a 3d model (cubes based)
RLAPI void UnloadModel(Model model);                                  // Unload 3d model from memory

RLAPI Mesh GenMeshCube(float width, float height, float depth);       // Generate mesh: cube

RLAPI Material LoadMaterial(const char *fileName);                    // Load material data (from file)
RLAPI Material LoadDefaultMaterial(void);                             // Load default material (uses default models shader)
RLAPI Material LoadStandardMaterial(void);                            // Load standard material (uses material attributes and lighting shader)
RLAPI void UnloadMaterial(Material material);                         // Unload material textures from VRAM

RLAPI void DrawModel(Model model, Vector3 position, float scale, Color tint);                            // Draw a model (with texture if set)
RLAPI void DrawModelEx(Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint);      // Draw a model with extended parameters
RLAPI void DrawModelWires(Model model, Vector3 position, float scale, Color tint);                      // Draw a model wires (with texture if set)
RLAPI void DrawModelWiresEx(Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint); // Draw a model wires (with texture if set) with extended parameters
RLAPI void DrawBoundingBox(BoundingBox box, Color color);                                                // Draw bounding box (wires)

RLAPI void DrawBillboard(Camera camera, Texture2D texture, Vector3 center, float size, Color tint);                         // Draw a billboard texture
RLAPI void DrawBillboardRec(Camera camera, Texture2D texture, Rectangle sourceRec, Vector3 center, float size, Color tint); // Draw a billboard texture defined by sourceRec

RLAPI BoundingBox CalculateBoundingBox(Mesh mesh);                                                                    // Calculate mesh bounding box limits
RLAPI bool CheckCollisionSpheres(Vector3 centerA, float radiusA, Vector3 centerB, float radiusB);                     // Detect collision between two spheres
RLAPI bool CheckCollisionBoxes(BoundingBox box1, BoundingBox box2);                                                   // Detect collision between two bounding boxes
RLAPI bool CheckCollisionBoxSphere(BoundingBox box, Vector3 centerSphere, float radiusSphere);                        // Detect collision between box and sphere
RLAPI bool CheckCollisionRaySphere(Ray ray, Vector3 spherePosition, float sphereRadius);                              // Detect collision between ray and sphere
RLAPI bool CheckCollisionRaySphereEx(Ray ray, Vector3 spherePosition, float sphereRadius, Vector3 *collisionPoint);   // Detect collision between ray and sphere with extended parameters and collision point detection
RLAPI bool CheckCollisionRayBox(Ray ray, BoundingBox box);                                                            // Detect collision between ray and box
RLAPI Vector3 ResolveCollisionCubicmap(Image cubicmap, Vector3 mapPosition, Vector3 *playerPosition, float radius);   // Detect collision of player radius with cubicmap
                                                                                                                // NOTE: Return the normal vector of the impacted surface
//------------------------------------------------------------------------------------
// Shaders System Functions (Module: rlgl)
// NOTE: This functions are useless when using OpenGL 1.1
//------------------------------------------------------------------------------------
RLAPI Shader LoadShader(char *vsFileName, char *fsFileName);              // Load a custom shader and bind default locations
RLAPI void UnloadShader(Shader shader);                                   // Unload a custom shader from memory

RLAPI Shader GetDefaultShader(void);                                      // Get default shader
RLAPI Shader GetStandardShader(void);                                     // Get standard shader
RLAPI Texture2D GetDefaultTexture(void);                                  // Get default texture

RLAPI int GetShaderLocation(Shader shader, const char *uniformName);              // Get shader uniform location
RLAPI void SetShaderValue(Shader shader, int uniformLoc, float *value, int size); // Set shader uniform value (float)
RLAPI void SetShaderValuei(Shader shader, int uniformLoc, int *value, int size);  // Set shader uniform value (int)
RLAPI void SetShaderValueMatrix(Shader shader, int uniformLoc, Matrix mat);       // Set shader uniform value (matrix 4x4)

RLAPI void SetMatrixProjection(Matrix proj);                              // Set a custom projection matrix (replaces internal projection matrix)
RLAPI void SetMatrixModelview(Matrix view);                               // Set a custom modelview matrix (replaces internal modelview matrix)

RLAPI void BeginShaderMode(Shader shader);                                // Begin custom shader drawing
RLAPI void EndShaderMode(void);                                           // End custom shader drawing (use default shader)
RLAPI void BeginBlendMode(int mode);                                      // Begin blending mode (alpha, additive, multiplied)
RLAPI void EndBlendMode(void);                                            // End blending mode (reset to default: alpha blending)

RLAPI Light CreateLight(int type, Vector3 position, Color diffuse);       // Create a new light, initialize it and add to pool
RLAPI void DestroyLight(Light light);                                     // Destroy a light and take it out of the list

//------------------------------------------------------------------------------------
// VR experience Functions (Module: rlgl)
// NOTE: This functions are useless when using OpenGL 1.1
//------------------------------------------------------------------------------------
RLAPI void InitVrDevice(int vdDevice);            // Init VR device
RLAPI void CloseVrDevice(void);                   // Close VR device
RLAPI bool IsVrDeviceReady(void);                 // Detect if VR device (or simulator) is ready
RLAPI void UpdateVrTracking(void);                // Update VR tracking (position and orientation)
RLAPI void ToggleVrMode(void);                    // Enable/Disable VR experience (device or simulator)

//------------------------------------------------------------------------------------
// Audio Loading and Playing Functions (Module: audio)
//------------------------------------------------------------------------------------
RLAPI void InitAudioDevice(void);                                     // Initialize audio device and context
RLAPI void CloseAudioDevice(void);                                    // Close the audio device and context (and music stream)
RLAPI bool IsAudioDeviceReady(void);                                  // Check if audio device has been initialized successfully

RLAPI Sound LoadSound(char *fileName);                                // Load sound to memory
RLAPI Sound LoadSoundFromWave(Wave wave);                             // Load sound to memory from wave data
RLAPI Sound LoadSoundFromRES(const char *rresName, int resId);        // Load sound to memory from rRES file (raylib Resource)
RLAPI void UnloadSound(Sound sound);                                  // Unload sound
RLAPI void PlaySound(Sound sound);                                    // Play a sound
RLAPI void PauseSound(Sound sound);                                   // Pause a sound
RLAPI void ResumeSound(Sound sound);                                  // Resume a paused sound
RLAPI void StopSound(Sound sound);                                    // Stop playing a sound
RLAPI bool IsSoundPlaying(Sound sound);                               // Check if a sound is currently playing
RLAPI void SetSoundVolume(Sound sound, float volume);                 // Set volume for a sound (1.0 is max level)
RLAPI void SetSoundPitch(Sound sound, float pitch);                   // Set pitch for a sound (1.0 is base level)

RLAPI Music LoadMusicStream(char *fileName);                          // Load music stream from file
RLAPI void UnloadMusicStream(Music music);                            // Unload music stream
RLAPI void PlayMusicStream(Music music);                              // Start music playing (open stream)
RLAPI void UpdateMusicStream(Music music);                            // Updates buffers for music streaming
RLAPI void StopMusicStream(Music music);                              // Stop music playing (close stream)
RLAPI void PauseMusicStream(Music music);                             // Pause music playing
RLAPI void ResumeMusicStream(Music music);                            // Resume playing paused music
RLAPI bool IsMusicPlaying(Music music);                               // Check if music is playing
RLAPI void SetMusicVolume(Music music, float volume);                 // Set volume for music (1.0 is max level)
RLAPI void SetMusicPitch(Music music, float pitch);                   // Set pitch for a music (1.0 is base level)
RLAPI float GetMusicTimeLength(Music music);                          // Get music time length (in seconds)
RLAPI float GetMusicTimePlayed(Music music);                          // Get current music time played (in seconds)

RLAPI AudioStream InitAudioStream(unsigned int sampleRate,
                                  unsigned int sampleSize,
                                  unsigned int channels);             // Init audio stream (to stream audio pcm data)
RLAPI void UpdateAudioStream(AudioStream stream, void *data, int numSamples); // Update audio stream buffers with data
RLAPI void CloseAudioStream(AudioStream stream);                      // Close audio stream and free memory
RLAPI bool IsAudioBufferProcessed(AudioStream stream);                // Check if any audio stream buffers requires refill
RLAPI void PlayAudioStream(AudioStream stream);                       // Play audio stream
RLAPI void PauseAudioStream(AudioStream stream);                      // Pause audio stream
RLAPI void ResumeAudioStream(AudioStream stream);                     // Resume audio stream
RLAPI void StopAudioStream(AudioStream stream);                       // Stop audio stream

#ifdef __cplusplus
}
#endif

#endif // RAYLIB_H
