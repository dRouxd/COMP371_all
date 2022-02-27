
#include "Output.h"

#include "util.hpp"

Output::Output(nlohmann::json j)
{
    this->camera = new Camera(j);
    this->outputFilename = std::string(j["filename"].get<std::string>());
    
    this->ai = JsonArrayToRGB(j["ai"]);
    this->bkc = JsonArrayToRGB(j["bkc"]);

    this->raysPerPixel = NULL;
    this->raysPerPixelSize = 0;
    if(j.contains("raysperpixel"))
    {
        this->raysPerPixelSize = j["raysperpixel"].size();
        if(this->raysPerPixelSize > 0)
        {
            this->raysPerPixel = new unsigned int[this->raysPerPixelSize];
            
            int i = 0;
            for(auto it = j["raysperpixel"].begin(); it != j["raysperpixel"].end(); ++it, ++i)
            {
                this->raysPerPixel[i] = (*it).get<unsigned int>();
            }
        }            
    }

    this->speedup = 0;
    if(j.contains("speedup"))
    {
        this->speedup = j["speedup"].get<unsigned int>();
    }
    
    this->antialiasing = false;
    if(j.contains("antialiasing"))
    {
        this->antialiasing = j["antialiasing"].get<bool>();
    }

    this->twosiderender = true;
    if(j.contains("twosiderender"))
    {
        this->twosiderender = j["twosiderender"].get<bool>();
    }


    if(j.contains("globalillum"))
    {
        this->globalillum = j["globalillum"].get<bool>();
    }
    this->globalillum = false;
}

Output::~Output()
{
    delete this->camera;
    delete this->raysPerPixel;
}