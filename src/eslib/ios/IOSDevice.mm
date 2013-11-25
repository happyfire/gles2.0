#import "eslib/Device.h"

NS_ESLIB_BEGIN


Device::Device()
{
    
}

Device::~Device()
{
    
}

stringc Device::getReadFilePath()
{
    char path[PATH_MAX];
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    ESL_ASSERT(mainBundle);
    
    CFURLRef mainBundleURL = CFBundleCopyBundleURL(mainBundle);
    ESL_ASSERT(mainBundleURL);
    
    CFStringRef cfStringRef = CFURLCopyFileSystemPath( mainBundleURL, kCFURLPOSIXPathStyle);
    ESL_ASSERT(cfStringRef);
    
    CFStringGetCString(cfStringRef, path, PATH_MAX, kCFStringEncodingASCII);
    
    CFRelease(mainBundleURL);
    CFRelease(cfStringRef);
    
    return stringc(path) + '/';
}


NS_ESLIB_END
