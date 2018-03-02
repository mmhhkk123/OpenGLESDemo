#include <jni.h>
#include <android/log.h>
#include <GLES2/gl2.h>
#include "gl3stub.h"
#include "com_example_zhzl_myapp_GLES3JNILib.h"
#include "Shader.h"
#include "FileUtils.h"
#include "Texture2D.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "SpriteRenderer.h"

// 打印输出
#define LOG_TAG "GLES3JNI"
#define LOG(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

Texture2D           texture;
SpriteRenderer*     renderer;

/////////////////////////////////////////////////////////////////////////

static void printGlString(const char* name, GLenum s) {
    const char* v = (const char*)glGetString(s);
    LOG("GL %s: %s\n", name, v);
}

JNIEXPORT void JNICALL Java_com_example_zhzl_myapp_GLES3JNILib_init(JNIEnv *, jclass) {

	// 打印gl信息
	printGlString("Version", GL_VERSION);
    printGlString("Vendor", GL_VENDOR);
    printGlString("Renderer", GL_RENDERER);
    printGlString("Extensions", GL_EXTENSIONS);

	// 初始化gl3扩展
	if(!gl3stubInit())
		return;

    // load shader
    Data vData = FileUtils::getInstance()->readDataFromAssets("assets/Shaders/sprite.vsh");
    Data fData = FileUtils::getInstance()->readDataFromAssets("assets/Shaders/sprite.fsh");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(1280), static_cast<GLfloat>(720), 0.0f, -1.0f, 1.0f);
    Shader shaderProgram((const char* )vData.getBytes(), vData.getSize(), (const char* )fData.getBytes(), fData.getSize());
    shaderProgram.use();
    shaderProgram.setInt("image", 0);
    shaderProgram.setMat4("projection", projection);

    // load texture
    int width, height, nrChannerls;
    Data imgBuffer = FileUtils::getInstance()->readDataFromAssets("assets/Textures/background.jpg");
    unsigned char* image = stbi_load_from_memory(imgBuffer.getBytes(), imgBuffer.getSize(), &width, &height, &nrChannerls, 0);
    texture.Generate(width, height, image);
    stbi_image_free(image);

    renderer = new SpriteRenderer(shaderProgram);
}

JNIEXPORT void JNICALL Java_com_example_zhzl_myapp_GLES3JNILib_resize(JNIEnv *, jclass, jint, jint) {
	LOG("Java_com_example_gles3jni_GLES3JNILib_resize");
}

JNIEXPORT void JNICALL Java_com_example_zhzl_myapp_GLES3JNILib_step(JNIEnv *, jclass) {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
    renderer->DrawSprite(texture, glm::vec2(0, 0), glm::vec2(1280, 720), 0.0f);
}

JNIEXPORT void JNICALL Java_com_example_zhzl_myapp_GLES3JNILib_nativeOnResume(JNIEnv *, jclass) {
    LOG("Java_com_example_zhzl_myapp_GLES3JNILib_nativeOnResume");
}

JNIEXPORT void JNICALL Java_com_example_zhzl_myapp_GLES3JNILib_nativeOnPause(JNIEnv *, jclass) {
    LOG("Java_com_example_zhzl_myapp_GLES3JNILib_nativeOnPause");
}

JNIEXPORT void JNICALL Java_com_example_zhzl_myapp_GLES3JNILib_nativeTouchesBegin
        (JNIEnv *, jclass, jint id, jfloat x, jfloat y) {

}

JNIEXPORT void JNICALL Java_com_example_zhzl_myapp_GLES3JNILib_nativeTouchesEnd
        (JNIEnv *, jclass, jint id, jfloat x, jfloat y) {

}

JNIEXPORT void JNICALL Java_com_example_zhzl_myapp_GLES3JNILib_nativeTouchesMove
        (JNIEnv *, jclass, jintArray ids, jfloatArray xs, jfloatArray ys) {

}

JNIEXPORT void JNICALL Java_com_example_zhzl_myapp_GLES3JNILib_nativeTouchesCancel
        (JNIEnv *, jclass, jintArray ids, jfloatArray xs, jfloatArray ys) {

}

JNIEXPORT jboolean JNICALL Java_com_example_zhzl_myapp_GLES3JNILib_nativeKeyEvent
        (JNIEnv *, jclass, jint keyCode, jboolean isPressed) {
    LOG("KeyCode:%d is %s", keyCode, (isPressed ? "press down" : "press up"));
    return JNI_TRUE;
}
