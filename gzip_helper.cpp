#include "gzip_helper.h"

#include "CCRC32.h"


QByteArray compress(const QByteArray &data)
{
    QByteArray res;
    QByteArray out = qCompress(data,9); //compression
    out.remove(0, 4);
    out.remove(0, 2); // Remove Zlib header
    out.remove(out.size() - 4, 4); // Remove Zlib trailer

    uint len = data.size();
    CCRC32 crc32;
    unsigned long crc = crc32.FullCRC((unsigned char *)data.data(),len);
    const unsigned char gzipheader[10]={0x1f,0x8b,8,0,0,0,0,0,2,255}; //this is valid gzip header - magic number , deflate compression, no extra fields, no timestamp present, maximum compression extra flag and 'other' os

    res.append((char *)gzipheader,10);
    res.append(out);
    res.append((char *)&crc,4);
    res.append((char *)&len,4);

    return res;

}

