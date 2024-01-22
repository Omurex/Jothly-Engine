#ifndef RAYLIB_CPP_INCLUDE_IMAGE_HPP_
#define RAYLIB_CPP_INCLUDE_IMAGE_HPP_

#include <string>

#include "./raylib.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./RaylibException.hpp"
#include "./Color.hpp"

namespace raylib {
/**
 * Image type, bpp always RGBA (32bit)
 *
 * Data stored in CPU memory (RAM)
 */
class rlb_Image : public ::rlb_Image {
 public:
    rlb_Image(void* data = nullptr,
            int width = 0,
            int height = 0,
            int mipmaps = 1,
            int format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8) : ::rlb_Image{data, width, height, mipmaps, format} {
        // Nothing.
    }

    rlb_Image(const ::rlb_Image& image) {
        set(image);
    }

    /**
     * Load an image from the given file.
     *
     * @throws raylib::RaylibException Thrown if the image failed to load from the file.
     *
     * @see Load()
     */
    rlb_Image(const std::string& fileName) {
        Load(fileName);
    }

    /**
     * Load a raw image from the given file, with the provided width, height, and formats.
     *
     * @throws raylib::RaylibException Thrown if the image failed to load from the file.
     *
     * @see LoadRaw()
     */
    rlb_Image(const std::string& fileName, int width, int height, int format, int headerSize = 0) {
        Load(fileName, width, height, format, headerSize);
    }

    /**
     * Load an animation image from the given file.
     *
     * @throws raylib::RaylibException Thrown if the image failed to load from the file.
     *
     * @see LoadAnim()
     */
    rlb_Image(const std::string& fileName, int* frames) {
        Load(fileName, frames);
    }

    /**
     * Load an image from the given file.
     *
     * @throws raylib::RaylibException Thrown if the image failed to load from the file.
     */
    rlb_Image(const std::string& fileType, const unsigned char* fileData, int dataSize) {
        Load(fileType, fileData, dataSize);
    }

    /**
     * Load an image from the given file.
     *
     * @throws raylib::RaylibException Thrown if the image failed to load from the file.
     */
    rlb_Image(const ::rlb_Texture2D& texture) {
        Load(texture);
    }

    rlb_Image(int width, int height, ::rlb_Color color = {255, 255, 255, 255}) {
        set(::GenImageColor(width, height, color));
    }

    rlb_Image(const std::string& text, int fontSize, ::rlb_Color color = {255, 255, 255, 255}) {
        set(::ImageText(text.c_str(), fontSize, color));
    }

    rlb_Image(const ::rlb_Font& font, const std::string& text, float fontSize, float spacing,
            ::rlb_Color tint = {255, 255, 255, 255}) {
        set(::ImageTextEx(font, text.c_str(), fontSize, spacing, tint));
    }

    rlb_Image(const rlb_Image& other) {
        set(other.Copy());
    }

    rlb_Image(rlb_Image&& other) {
        set(other);

        other.data = nullptr;
        other.width = 0;
        other.height = 0;
        other.mipmaps = 0;
        other.format = 0;
    }

    static ::rlb_Image Text(const std::string& text, int fontSize,
            ::rlb_Color color = {255, 255, 255, 255}) {
        return ::ImageText(text.c_str(), fontSize, color);
    }

    static ::rlb_Image Text(const ::rlb_Font& font, const std::string& text, float fontSize, float spacing,
            ::rlb_Color tint = {255, 255, 255, 255}) {
        return ::ImageTextEx(font, text.c_str(), fontSize, spacing, tint);
    }

    /**
     * Get pixel data from screen buffer and return an Image (screenshot)
     */
    static ::rlb_Image LoadFromScreen() {
        return ::LoadImageFromScreen();
    }

    /**
     * Generate image: plain color
     */
    static ::rlb_Image rlb_Color(int width, int height, ::rlb_Color color = {255, 255, 255, 255}) {
        return ::GenImageColor(width, height, color);
    }

    /**
     * Generate image: linear gradient
     */
    static ::rlb_Image GradientLinear(int width, int height, int direction, ::rlb_Color start, ::rlb_Color end) {
        return ::GenImageGradientLinear(width, height, direction, start, end);
    }

    /**
     * Generate image: radial gradient
     */
    static ::rlb_Image GradientRadial(int width, int height, float density,
            ::rlb_Color inner, ::rlb_Color outer) {
        return ::GenImageGradientRadial(width, height, density, inner, outer);
    }

    /**
     * Generate image: checked
     */
    static ::rlb_Image Checked(int width, int height, int checksX, int checksY,
            ::rlb_Color col1 = {255, 255, 255, 255}, ::rlb_Color col2 = {0, 0, 0, 255}) {
        return ::GenImageChecked(width, height, checksX, checksY, col1, col2);
    }

    /**
     * Generate image: white noise
     */
    static ::rlb_Image WhiteNoise(int width, int height, float factor) {
        return ::GenImageWhiteNoise(width, height, factor);
    }

    /**
     * Generate image: cellular algorithm. Bigger tileSize means bigger cells
     */
    static ::rlb_Image Cellular(int width, int height, int tileSize) {
        return ::GenImageCellular(width, height, tileSize);
    }

    ~rlb_Image() {
        Unload();
    }

    rlb_Image& operator=(const ::rlb_Image& image) {
        set(image);
        return *this;
    }

    rlb_Image& operator=(const rlb_Image& other) {
        if (this == &other) {
            return *this;
        }

        Unload();
        set(other.Copy());

        return *this;
    }

    rlb_Image& operator=(rlb_Image&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        Unload();
        set(other);

        other.data = nullptr;
        other.width = 0;
        other.height = 0;
        other.mipmaps = 0;
        other.format = 0;

        return *this;
    }

    /**
     * Load image from file into CPU memory (RAM)
     *
     * @throws raylib::RaylibException Thrown if the image failed to load from the file.
     *
     * @see ::LoadImage()
     */
    void Load(const std::string& fileName) {
        set(::LoadImage(fileName.c_str()));
        if (!IsReady()) {
            throw RaylibException("Failed to load Image from file: " + fileName);
        }
    }

    /**
     * Load image from RAW file data.
     *
     * @throws raylib::RaylibException Thrown if the image failed to load from the file.
     *
     * @see ::LoadImageRaw()
     */
    void Load(const std::string& fileName, int width, int height, int format, int headerSize) {
        set(::LoadImageRaw(fileName.c_str(), width, height, format, headerSize));
        if (!IsReady()) {
            throw RaylibException("Failed to load Image from file: " + fileName);
        }
    }

    /**
     * Load image sequence from file (frames appended to image.data).
     *
     * @throws raylib::RaylibException Thrown if the image animation to load from the file.
     *
     * @see ::LoadImageAnim()
     */
    void Load(const std::string& fileName, int* frames) {
        set(::LoadImageAnim(fileName.c_str(), frames));
        if (!IsReady()) {
            throw RaylibException("Failed to load Image from file: " + fileName);
        }
    }

    /**
     * Load image from memory buffer, fileType refers to extension: i.e. "png".
     *
     * @throws raylib::RaylibException Thrown if the image animation to load from the file.
     *
     * @see ::LoadImageFromMemory()
     */
    void Load(
            const std::string& fileType,
            const unsigned char *fileData,
            int dataSize) {
        set(::LoadImageFromMemory(fileType.c_str(), fileData, dataSize));
        if (!IsReady()) {
            throw RaylibException("Failed to load Image data with file type: " + fileType);
        }
    }

    /**
     * Load an image from the given file.
     *
     * @throws raylib::RaylibException Thrown if the image animation to load from the file.
     *
     * @see ::LoadImageFromTexture()
     */
    void Load(const ::rlb_Texture2D& texture) {
        set(::LoadImageFromTexture(texture));
        if (!IsReady()) {
            throw RaylibException("Failed to load Image from texture.");
        }
    }

    /**
     * Unload image from CPU memory (RAM)
     */
    inline void Unload() {
        if (data != nullptr) {
            ::UnloadImage(*this);
            data = nullptr;
        }
    }

    /**
     * Export image data to file, returns true on success
     *
     * @throws raylib::RaylibException Thrown if the image failed to load from the file.
     */
    inline void Export(const std::string& fileName) const {
        if (!::ExportImage(*this, fileName.c_str())) {
            throw RaylibException(TextFormat("Failed to export Image to file: %s", fileName.c_str()));
        }
    }

    /**
     * Export image to memory buffer
     */
    inline unsigned char* ExportToMemory(const char *fileType, int *fileSize) {
        return ::ExportImageToMemory(*this, fileType, fileSize);
    }

    /**
     * Export image as code file defining an array of bytes, returns true on success
     *
     * @throws raylib::RaylibException Thrown if the image failed to load from the file.
     */
    inline void ExportAsCode(const std::string& fileName) const {
        if (!::ExportImageAsCode(*this, fileName.c_str())) {
            throw RaylibException(TextFormat("Failed to export Image code to file: %s", fileName.c_str()));
        }
    }

    GETTERSETTER(void*, Data, data)
    GETTERSETTER(int, Width, width)
    GETTERSETTER(int, Height, height)
    GETTERSETTER(int, Mipmaps, mipmaps)
    GETTERSETTER(int, Format, format)

    /**
     * Retrieve the width and height of the image.
     */
    inline ::rlb_Vector2 GetSize() const {
        return {static_cast<float>(width), static_cast<float>(height)};
    }

    /**
     * Create an image duplicate (useful for transformations)
     */
    inline ::rlb_Image Copy() const {
        return ::ImageCopy(*this);
    }

    /**
     * Create an image from another image piece
     */
    inline ::rlb_Image FromImage(::rlb_Rectangle rec) const {
        return ::ImageFromImage(*this, rec);
    }

    /**
     * Convert image data to desired format
     */
    inline rlb_Image& Format(int newFormat) {
        ::ImageFormat(this, newFormat);
        return *this;
    }

    /**
     * Convert image to POT (power-of-two)
     */
    inline rlb_Image& ToPOT(::rlb_Color fillColor) {
        ::ImageToPOT(this, fillColor);
        return *this;
    }

    /**
     * Crop an image to area defined by a rectangle
     */
    inline rlb_Image& Crop(::rlb_Rectangle crop) {
        ::ImageCrop(this, crop);
        return *this;
    }

    /**
     * Crop image depending on alpha value
     */
    inline rlb_Image& AlphaCrop(float threshold) {
        ::ImageAlphaCrop(this, threshold);
        return *this;
    }

    /**
     * Clear alpha channel to desired color
     */
    inline rlb_Image& AlphaClear(::rlb_Color color, float threshold) {
        ::ImageAlphaClear(this, color, threshold);
        return *this;
    }

    /**
     * Apply alpha mask to image
     */
    inline rlb_Image& AlphaMask(const ::rlb_Image& alphaMask) {
        ::ImageAlphaMask(this, alphaMask);
        return *this;
    }

    /**
     * Premultiply alpha channel
     */
    inline rlb_Image& AlphaPremultiply() {
        ::ImageAlphaPremultiply(this);
        return *this;
    }

    /**
     * Crop an image to a new given width and height.
     */
    inline rlb_Image& Crop(int newWidth, int newHeight) {
        return Crop(0, 0, newWidth, newHeight);
    }

    /**
     * Crop an image to a new given width and height based on a vector.
     */
    inline rlb_Image& Crop(::rlb_Vector2 size) {
        return Crop(0, 0, static_cast<int>(size.x), static_cast<int>(size.y));
    }

    /**
     * Crop an image to area defined by a rectangle
     */
    inline rlb_Image& Crop(int offsetX, int offsetY, int newWidth, int newHeight) {
        ::rlb_Rectangle rect{
            static_cast<float>(offsetX),
            static_cast<float>(offsetY),
            static_cast<float>(newWidth),
            static_cast<float>(newHeight)
        };
        ::ImageCrop(this, rect);
        return *this;
    }

    /**
     * Resize and image to new size
     */
    inline rlb_Image& Resize(int newWidth, int newHeight) {
        ::ImageResize(this, newWidth, newHeight);
        return *this;
    }

    /**
     * Resize and image to new size using Nearest-Neighbor scaling algorithm
     */
    inline rlb_Image& ResizeNN(int newWidth, int newHeight) {
        ::ImageResizeNN(this, newWidth, newHeight);
        return *this;
    }

    /**
     * Resize canvas and fill with color
     */
    inline rlb_Image& ResizeCanvas(int newWidth, int newHeight, int offsetX = 0, int offsetY = 0,
            ::rlb_Color color = {255, 255, 255, 255}) {
        ::ImageResizeCanvas(this, newWidth, newHeight, offsetX, offsetY, color);
        return *this;
    }

    /**
     * Generate all mipmap levels for a provided image
     */
    inline rlb_Image& Mipmaps() {
        ::ImageMipmaps(this);
        return *this;
    }

    /**
     * Dither image data to 16bpp or lower (Floyd-Steinberg dithering)
     */
    inline rlb_Image& Dither(int rBpp, int gBpp, int bBpp, int aBpp) {
        ::ImageDither(this, rBpp, gBpp, bBpp, aBpp);
        return *this;
    }

    /**
     * Flip image vertically
     */
    inline rlb_Image& FlipVertical() {
        ::ImageFlipVertical(this);
        return *this;
    }

    /**
     * Flip image horizontally
     */
    inline rlb_Image& FlipHorizontal() {
        ::ImageFlipHorizontal(this);
        return *this;
    }

    /**
     * Rotate image by input angle in degrees (-359 to 359)
     */
    inline rlb_Image& Rotate(int degrees) {
        ::ImageRotate(this, degrees);
        return *this;
    }

    /**
     * Rotate image clockwise 90deg
     */
    inline rlb_Image& RotateCW() {
        ::ImageRotateCW(this);
        return *this;
    }

    /**
     * Rotate image counter-clockwise 90deg
     */
    inline rlb_Image& RotateCCW() {
        ::ImageRotateCCW(this);
        return *this;
    }

    /**
     * Modify image color: tint
     */
    inline rlb_Image& ColorTint(::rlb_Color color = {255, 255, 255, 255}) {
        ::ImageColorTint(this, color);
        return *this;
    }

    /**
     * Modify image color: invert
     */
    inline rlb_Image& ColorInvert() {
        ::ImageColorInvert(this);
        return *this;
    }

    /**
     * Modify image color: grayscale
     */
    inline rlb_Image& ColorGrayscale() {
        ::ImageColorGrayscale(this);
        return *this;
    }

    /**
     * Modify image color: contrast
     *
     * @param contrast Contrast values between -100 and 100
     */
    inline rlb_Image& ColorContrast(float contrast) {
        ::ImageColorContrast(this, contrast);
        return *this;
    }

    /**
     * Modify image color: brightness
     *
     * @param brightness Brightness values between -255 and 255
     */
    inline rlb_Image& ColorBrightness(int brightness) {
        ::ImageColorBrightness(this, brightness);
        return *this;
    }

    /**
     * Modify image color: replace color
     */
    inline rlb_Image& ColorReplace(::rlb_Color color, ::rlb_Color replace) {
        ::ImageColorReplace(this, color, replace);
        return *this;
    }

    /**
     * Get image alpha border rectangle
     *
     * @param threshold Threshold is defined as a percentatge: 0.0f -> 1.0f
     */
    inline rlb_Rectangle GetAlphaBorder(float threshold) const {
        return ::GetImageAlphaBorder(*this, threshold);
    }

    /**
     * Get image pixel color at (x, y) position
     */
    inline raylib::rlb_Color GetColor(int x = 0, int y = 0) const {
        return ::GetImageColor(*this, x, y);
    }

    /**
     * Get image pixel color at vector position
     */
    inline raylib::rlb_Color GetColor(::rlb_Vector2 position) const {
        return ::GetImageColor(*this, static_cast<int>(position.x), static_cast<int>(position.y));
    }

    /**
     * Clear image background with given color
     */
    inline rlb_Image& ClearBackground(::rlb_Color color = {0, 0, 0, 255}) {
        ::ImageClearBackground(this, color);
        return *this;
    }

    /**
     * Draw pixel within an image
     */
    inline void DrawPixel(int posX, int posY, ::rlb_Color color = {255, 255, 255, 255}) {
        ::ImageDrawPixel(this, posX, posY, color);
    }

    inline void DrawPixel(::rlb_Vector2 position, ::rlb_Color color = {255, 255, 255, 255}) {
        ::ImageDrawPixelV(this, position, color);
    }

    inline void DrawLine(int startPosX, int startPosY, int endPosX, int endPosY,
            ::rlb_Color color = {255, 255, 255, 255}) {
        ::ImageDrawLine(this, startPosX, startPosY, endPosX, endPosY, color);
    }

    inline void DrawLine(::rlb_Vector2 start, ::rlb_Vector2 end, ::rlb_Color color = {255, 255, 255, 255}) {
        ::ImageDrawLineV(this, start, end, color);
    }

    inline void DrawCircle(int centerX, int centerY, int radius,
            ::rlb_Color color = {255, 255, 255, 255}) {
        ::ImageDrawCircle(this, centerX, centerY, radius, color);
    }

    inline void DrawCircle(::rlb_Vector2 center, int radius,
            ::rlb_Color color = {255, 255, 255, 255}) {
        ::ImageDrawCircleV(this, center, radius, color);
    }

    inline void DrawRectangle(int posX, int posY, int width, int height,
            ::rlb_Color color = {255, 255, 255, 255}) {
        ::ImageDrawRectangle(this, posX, posY, width, height, color);
    }

    inline void DrawRectangle(rlb_Vector2 position, rlb_Vector2 size,
            ::rlb_Color color = {255, 255, 255, 255}) {
        ::ImageDrawRectangleV(this, position, size, color);
    }

    inline void DrawRectangle(::rlb_Rectangle rec, ::rlb_Color color = {255, 255, 255, 255}) {
        ::ImageDrawRectangleRec(this, rec, color);
    }

    inline void DrawRectangleLines(::rlb_Rectangle rec, int thick = 1,
            ::rlb_Color color = {255, 255, 255, 255}) {
        ::ImageDrawRectangleLines(this, rec, thick, color);
    }

    inline void Draw(const ::rlb_Image& src, ::rlb_Rectangle srcRec, ::rlb_Rectangle dstRec,
            ::rlb_Color tint = {255, 255, 255, 255}) {
        ::ImageDraw(this, src, srcRec, dstRec, tint);
    }

    inline void DrawText(const std::string& text, ::rlb_Vector2 position, int fontSize,
            ::rlb_Color color = {255, 255, 255, 255}) {
        ::ImageDrawText(this,
            text.c_str(),
            static_cast<int>(position.x),
            static_cast<int>(position.y),
            fontSize,
            color);
    }

    inline void DrawText(const std::string& text, int x, int y, int fontSize,
            ::rlb_Color color = {255, 255, 255, 255}) {
        ::ImageDrawText(this, text.c_str(), x, y, fontSize, color);
    }

    inline void DrawText(const ::rlb_Font& font, const std::string& text, ::rlb_Vector2 position,
            float fontSize, float spacing, ::rlb_Color tint = {255, 255, 255, 255}) {
        ::ImageDrawTextEx(this, font, text.c_str(), position, fontSize, spacing, tint);
    }

    /**
     * Load color data from image as a Color array (RGBA - 32bit)
     */
    inline ::rlb_Color* LoadColors() const {
        return ::LoadImageColors(*this);
    }

    /**
     * Load colors palette from image as a Color array (RGBA - 32bit)
     */
    inline ::rlb_Color* LoadPalette(int maxPaletteSize, int *colorsCount) const {
        return ::LoadImagePalette(*this, maxPaletteSize, colorsCount);
    }

    /**
     * Unload color data loaded with LoadImageColors()
     */
    inline void UnloadColors(::rlb_Color* colors) const {
        ::UnloadImageColors(colors);
    }

    /**
     * Unload colors palette loaded with LoadImagePalette()
     */
    inline void UnloadPalette(::rlb_Color* colors) const {
        ::UnloadImagePalette(colors);
    }

    /**
     * Load texture from image data.
     */
    inline ::rlb_Texture2D LoadTexture() const {
        return ::LoadTextureFromImage(*this);
    }

    /**
     * Loads a texture from the image data.
     *
     * @see LoadTexture()
     */
    inline operator ::rlb_Texture2D() {
        return LoadTexture();
    }

    /**
     * Get pixel data size in bytes for certain format
     */
    static int GetPixelDataSize(int width, int height, int format = PIXELFORMAT_UNCOMPRESSED_R32G32B32A32) {
        return ::GetPixelDataSize(width, height, format);
    }

    /**
     * Returns the pixel data size based on the current image.
     *
     * @return The pixel data size of the image.
     */
    inline int GetPixelDataSize() const {
        return ::GetPixelDataSize(width, height, format);
    }

    /**
     * Retrieve whether or not the Image has been loaded.
     *
     * @return True or false depending on whether the Image has been loaded.
     */
    inline bool IsReady() const {
        return ::IsImageReady(*this);
    }

 protected:
    void set(const ::rlb_Image& image) {
        data = image.data;
        width = image.width;
        height = image.height;
        mipmaps = image.mipmaps;
        format = image.format;
    }
};
}  // namespace raylib

using RImage = raylib::rlb_Image;

#endif  // RAYLIB_CPP_INCLUDE_IMAGE_HPP_
