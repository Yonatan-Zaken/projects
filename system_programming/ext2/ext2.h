/*************************
         EXT2
      Header File
    Author : Yonatan Zaken
      Date : 05/04/2020          
*************************/
#ifndef ILRD_RD8081_EX2_H
#define ILRD_RD8081_EX2_H

enum 
{
    SUCCESS,
    FAIL,
    NOT_EXT2
};

int PrintSuperBlock(const char *device);

int PrintGroupDescriptors(const char *device);

int PrintFileContent(const char *device, const char *filename);

#endif /* ILRD_RD8081_EX2_HPP */



