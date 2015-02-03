#ifndef WRPSTATSNEW_H
#define WRPSTATSNEW_H
#include <QFile>

class wrpStatsNew
{
public:
    wrpStatsNew(int argc, char *argv[]);
    void Open_Files(int argc, char *argv[]);
    void Read_Signature();
    void Read_Cells();
    void Read_Elevations();
    void Read_Textures();
    void Read_Objects();
    void Close_Files();

private:
    int texturegrid;
    QFile file;
};

#endif // WRPSTATSNEW_H
