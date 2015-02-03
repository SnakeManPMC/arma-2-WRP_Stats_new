// I don't think this works :)


#include <QtCore/QCoreApplication>
#include <QDebug>
#include <QFile>
#include "wrpstatsnew.h"

wrpStatsNew::wrpStatsNew(int argc, char *argv[])
{
    Open_Files(argc, argv);
    Read_Signature();
    Read_Cells();
    Read_Elevations();
    Read_Textures();
    Read_Objects();
    Close_Files();
}


void wrpStatsNew::Open_Files(int argc, char *argv[])
{
    if (argc < 2)
    {
        qDebug() << "Error in parameters, use: WRP_Stats_new.exe WRP_FILE";
        exit(1);
    }

    QFile file(argv[1]);

    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug("Unable to open file!");
        exit(1);
    }

    qDebug() << "Opened file: " << file.fileName();
}


void wrpStatsNew::Read_Signature()
{
    char magic[4];
    file.read( magic, 4 );
    qDebug() << "WRP Signature: " << magic;
}


void wrpStatsNew::Read_Cells()
{
    // 4WVR
    //file.read((char*)&texturegrid, sizeof(texturegrid));
    file.read( reinterpret_cast<char*>(&texturegrid), 4 );
    qDebug() << "Cells: " << texturegrid;
    //file.read((char*)&texturegrid, sizeof(texturegrid));
    file.read( reinterpret_cast<char*>(&texturegrid), 4 );
}


void wrpStatsNew::Read_Elevations()
{
    short materialindex = 0;
    // reading elevations
    for (int i = 0; i < texturegrid * texturegrid; i++)
    {
        // this was elevation before (float), but it supposed to be short??
        //file.read((char*)&materialindex, sizeof(short));
        file.read( reinterpret_cast<char*>(&materialindex), 2 );
    }
}


void wrpStatsNew::Read_Textures()
{
    qDebug() << "Reading texture indexes...";

    // read textures indexes
    for (int i = 0; i < texturegrid * texturegrid; i++)
    {
        short index;
        file.read( reinterpret_cast<char*>(&index), 2 );
    }

    qDebug() << "Reading texture names...";

    // textures 32 char length and total of 512
    for (int ix = 0; ix < 512; ix++)
    {
        char texture[32];
        file.read( texture, 32 );
    }
}


void wrpStatsNew::Read_Objects()
{
    qDebug() << "Reading 3d objects...";

    float dDir = 0;
    ulong dObjIndex = 0;
    char dObjName[76];

    while (!file.atEnd())
    {
        // matrix, 3 x 3 floats
        file.read(reinterpret_cast<char*>(&dDir), sizeof(float));
        file.read(reinterpret_cast<char*>(&dDir), sizeof(float));
        file.read(reinterpret_cast<char*>(&dDir), sizeof(float));
        file.read(reinterpret_cast<char*>(&dDir), sizeof(float));
        file.read(reinterpret_cast<char*>(&dDir), sizeof(float));
        file.read(reinterpret_cast<char*>(&dDir), sizeof(float));
        file.read(reinterpret_cast<char*>(&dDir), sizeof(float));
        file.read(reinterpret_cast<char*>(&dDir), sizeof(float));
        file.read(reinterpret_cast<char*>(&dDir), sizeof(float));

        // x, elevation and z
        file.read(reinterpret_cast<char*>(&dDir), sizeof(float));
        file.read(reinterpret_cast<char*>(&dDir), sizeof(float));
        file.read(reinterpret_cast<char*>(&dDir), sizeof(float));

        // object index
        file.read(reinterpret_cast<char*>(&dObjIndex), sizeof(unsigned int));

        // object name
        file.read(dObjName, 76);
    }

    // should now be at eof
    qDebug() << "Number of P3D objects:";

    qDebug() << "All fine, 4WVR file read, exiting. Have a nice day!";
}


void wrpStatsNew::Close_Files()
{
    file.close();
}
