#ifndef FILEUTILITY
#define FILEUTILITY
#include <string>

static std::string GetDirectoryFromFilePath( const std::string& filePath ) {
    int lastSlashPos = static_cast<int>( filePath.rfind( '/' ) );
    return filePath.substr( 0, lastSlashPos );
}

static std::string GetFilenameFromPath( const std::string& filePath ) {
    int lastSlashPos = static_cast<int>( filePath.rfind( '/' ) );
    return filePath.substr( lastSlashPos + 1, filePath.length() - lastSlashPos );
}
#endif // FILEUTILITY

