/**
 * @file Picture.h
 * @author Jackson White
 *
 * Picture that holds the wxImage and wxBitmap.
 */
 
#ifndef PICTURE_H
#define PICTURE_H

/**
 * Picture class holds wxImage and wxBitmap.
 */
class Picture {
private:
    /// The wxImage for this picture.
    std::shared_ptr<wxImage> mImage = nullptr;
    /// The wxBitmap for this picture.
    std::shared_ptr<wxBitmap> mBitmap = nullptr;
public:
    Picture(std::wstring imageName);

    /**
     * Get the image of the picture.
     * @return shared pointer to the image.
     */
    std::shared_ptr<wxImage> GetImage() {return mImage;}

    /**
     * Get the bitmap of the picture.
     * @return shared pointer to the bitmap.
     */
    std::shared_ptr<wxBitmap> GetBitmap() {return mBitmap;}
};

#endif //PICTURE_H
