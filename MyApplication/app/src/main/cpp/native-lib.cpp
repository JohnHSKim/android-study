#include <jni.h>
#include <string>
#include <android/bitmap.h>
#include <android/log.h>

#define LOG_TAG     "Android_tags"
#define LOGI(...)   __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGD(...)   __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...)   __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#define MAKE_RGB565(r,g,b)  ((((r) >> 3) << 11) | (((g) >> 2 ) << 5) | ((b) >> 3))

#define MAKE_ARGB(a,r,g,b) ((a&0xff) << 24) | ((r&0xff)<<16) | ((g&0xff)<<8) | (b&0xff)

#define RGB565_R(p) ((((p) & 0xF800) >> 11) << 3)
#define RGB565_G(p) ((((p) & 0x7E0) >> 5) << 2)
#define RGB565_B(p) (((p) & 0x1F) << 3)

#define RGB8888_A(p)    (p & (0xff<<24) >> 24)
#define RGB8888_R(p)    (p & (0xff<<16) >> 16)
#define RGB8888_G(p)    (p & (0xff<<6) >> 8)
#define RGB8888_B(p)    (p & (0xff))

extern "C" JNIEXPORT void JNICALL
Java_com_example_myapplication_MainActivity_nativeProcessBitmap(JNIEnv *env, jobject instance, jobject bitmap) {
    if (bitmap == NULL) {
        LOGE("bitmap is null\n");
        return;
    }

    AndroidBitmapInfo bitmapInfo;
    memset(&bitmapInfo, 0, sizeof(bitmapInfo));

    AndroidBitmap_getInfo(env, bitmap, &bitmapInfo);

    void *pixels = NULL;
    int res = AndroidBitmap_lockPixels(env, bitmap, &pixels);

    int a, r, g, b, sum;
    int offset = 500;
    void *pixel;

    for (int y = 0; y < bitmapInfo.height; ++y) {
        for (int x = 0; x < bitmapInfo.width; ++x) {
            if (bitmapInfo.format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
                pixel = ((uint32_t *) pixels + y * bitmapInfo.width + x);
                uint32_t v = *((uint32_t *) pixel);

                r = RGB8888_R(v);
                g = RGB8888_G(v);
                b = RGB8888_B(v);
                sum = r + g + b + offset;

                *((uint32_t *)pixel) = MAKE_ARGB(0x1f, sum/3, sum/3, sum/3);
            } else if (bitmapInfo.format == ANDROID_BITMAP_FORMAT_RGB_565) {
                pixel = ((uint16_t *)pixels) + y * bitmapInfo.width + x;
                uint16_t v = *((uint16_t *)pixel);

                r = RGB565_R(v);
                g = RGB565_G(v);
                b = RGB565_B(v);
                sum = r + g + b + offset;

                *((uint16_t *)pixel) = MAKE_RGB565(sum/3, sum/3, sum/3);
            } else {
                LOGE("not support Image Format\n");
                AndroidBitmap_unlockPixels(env, bitmap);
                return;
            }

        }
    }
}
